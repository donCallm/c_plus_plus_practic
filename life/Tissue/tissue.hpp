#pragma once

#include <list>
#include <vector>
#include <future>
#include <unistd.h>
#include "../Cells/animal_cells.hpp"
#include "../Cells/transport_cells.hpp"
// #include "../Cells/plant_cells.hpp"

constexpr size_t DEFAULT_MAX_CELLS_COUNT = 10;

using Nutrients = std::vector<std::unique_ptr<DefaultEnergySource>>;

template <typename CellType>
using Cells = std::vector<std::shared_ptr<CellType>>;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TissueFactory {
    template <typename CellType>
    Cells<TransportCell> build_ts_fluid(size_t count) {
        Cells<CellType> cells;
        auto first_cell = std::shared_ptr<CellType>(std::make_shared<CellType>());
        cells.push_back(first_cell);
        
        for (size_t i = 0; i < count - 1; ++i) {
            if constexpr (std::is_same<CellType, BloodCell>::value) {
                cells[i]->feed(std::make_unique<Fat>());
            } else if constexpr (std::is_same<CellType, PhloemJuice>::value) {
                cells[i]->feed(std::make_unique<LightEnergy>());
            }
            cells[i]->breath(10);

            auto new_cell = std::dynamic_pointer_cast<CellType>(cells[i]->splitting());
            if (new_cell == nullptr) {
                throw std::runtime_error("NULL");
            }
            cells.push_back(new_cell);
        }

        Cells<TransportCell> res;
        for (size_t i = 0; i < count; ++i) {
            if (auto new_cell = std::dynamic_pointer_cast<TransportCell>(cells[i])) {
                res.push_back(new_cell);    
            } else {
                throw std::runtime_error("NULL");
            }
        }
        return res;
    }

    template <typename CellType>
    Cells<AnimalCell> build_animal(size_t count);

    // template <typename CellType>
    // Cells<PlantCell> build_plant(size_t count);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename CellType>
struct Tissue {
    const size_t MAX_CELLS_COUNT;

    Tissue(size_t max_cells = DEFAULT_MAX_CELLS_COUNT)
        : MAX_CELLS_COUNT(max_cells),
        _tf(std::make_unique<TissueFactory>())
    {}

    void recovery() {
        if (_cells.size() != MAX_CELLS_COUNT) {
            for (std::shared_ptr<Eukaryotes> c : _cells) {
                if (auto new_cell = std::static_pointer_cast<Eukaryotes>(c->splitting()))
                    _cells.push_back(new_cell);
                else
                    break;
            }
        }
    }

    size_t cells_count() { return _cells.size(); }

    size_t ts_cells_count() { return _ts_fluid.size(); }

    void get_oxygen(std::vector<Oxygen>& pool) {
        if (pool.size() == 0) {
            return;
        }

        for (size_t i = 0; i < _ts_fluid.size(); i++)
        {
            size_t j = 0;
            while(true) {
                if (_ts_fluid[j]->oxygen_pool < _ts_fluid[j + 1]->oxygen_pool) {
                    _ts_fluid[j]->oxygen_pool += pool[i];
                    break;
                } else {
                    if (++j <_ts_fluid.size() -1)
                        break;
                }
            }
        }
    }

    void breath() {
        std::vector<std::future<void>> pool;
        for (size_t i = 0; i < _cells.size(); ++i) {
            pool.push_back(std::async(std::launch::async, &TransportCell::transfer_oxygen, &(*_ts_fluid[0]), _cells[i]));
        }
        for(auto& f : pool) {
            f.get();
        }
    }

    void feed() {
        std::vector<std::future<void>> pool;

        for (size_t i = 0; i < _cells.size(); ++i) {
            pool.push_back(std::async(std::launch::async, &TransportCell::transfer_nutrients, &(*_ts_fluid[0]), _cells[i]));
        }
        for(auto& f : pool) {
            f.get();
        }
    }

    virtual void get_nuts(Nutrients& nuts) = 0;

protected:
    Cells<CellType>                  _cells;
    std::unique_ptr<TissueFactory>   _tf;
    Cells<TransportCell>             _ts_fluid;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AnimalTissue
            : Tissue<AnimalCell>
{
    AnimalTissue()
        : Tissue<AnimalCell>()
    {
        this->_ts_fluid = this->_tf->build_ts_fluid<BloodCell>(DEFAULT_MAX_CELLS_COUNT);
    }

    void get_nuts(Nutrients& nuts) override {
        if (nuts.size() == 0) {
            return;
        }

        size_t i = 0;
        while (nuts.size() != 0) {
            std::unique_ptr<DefaultEnergySource> nut = std::move(*(nuts.end() - 1));
            nuts.erase(nuts.end() - 1);

            const std::type_info& type = nut->get_type();
            if (type != PROTEIN_ID && type != FAT_ID && type != CARB_ID) {
                throw std::runtime_error("Is not animal nutrient");
            }

            for (; i < _ts_fluid.size(); ++i)
            {
                if (_ts_fluid[i]->nut_pool == nullptr) {    
                    _ts_fluid[i]->nut_pool = std::move(nut);
                    break;
                }
            }

            if (i == _ts_fluid.size()) {
                break;
            }
        }
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Muscles
            : AnimalTissue
{
    Muscles()
        : AnimalTissue()
    {
        this->_cells = this->_tf->build_animal<MuscleCell>(DEFAULT_MAX_CELLS_COUNT);
    }

    void shrink() {
        std::vector<std::future<void>> pool;
        for (size_t i = 0; i < _cells.size(); ++i)
        {
            std::shared_ptr<MuscleCell> m_c = std::static_pointer_cast<MuscleCell>(_cells[i]);
            pool.push_back(std::async(std::launch::async, &MuscleCell::shrink, &(*m_c)));
        }
        for(auto& f : pool) {
            f.get();
        }
    }

    void relax() {
        std::vector<std::future<void>> pool;
        for (size_t i = 0; i < _cells.size(); ++i)
        {
            std::shared_ptr<MuscleCell> m_c = std::static_pointer_cast<MuscleCell>(_cells[i]);
            pool.push_back(std::async(std::launch::async, &MuscleCell::relax, &(*m_c)));
        }
        for(auto& f : pool) {
            f.get();
        }
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename CellType>
Cells<AnimalCell> TissueFactory::build_animal(size_t count) {
    Cells<AnimalCell> cells;
    auto first_cell = std::dynamic_pointer_cast<AnimalCell>(std::make_shared<CellType>());
    cells.push_back(first_cell);

    for (size_t i = 0; i < count - 1; ++i) {
        cells[i]->feed(std::unique_ptr<Fat>(std::make_unique<Fat>()));
        cells[i]->breath(10);

        auto new_cell = std::dynamic_pointer_cast<AnimalCell>(cells[i]->splitting());
        if (new_cell == nullptr)
            throw std::runtime_error("Some animal cell is null");

        cells.push_back(new_cell);
    }

    return cells;
}

// template <typename CellType>
// Cells<PlantCell> TissueFactory::build_plant(size_t count) {
//     Cells<PlantCell> cells;
//     auto first_cell = std::static_pointer_cast<PlantCell>(std::make_shared<CellType>());
//     cells.push_back(first_cell);

//     for (size_t i = 0; i < count; ++i) {
//         std::vector<std::unique_ptr<DefaultEnergySource>> nuts;
//         nuts.push_back(std::unique_ptr<LightEnergi>(std::make_unique<LightEnergi>()));

//         cells[i]->feed(nuts);
//         auto new_cell = std::static_pointer_cast<PlantCell>(cells[i]->splitting());
//         if (new_cell == nullptr)
//             throw std::runtime_error("Some cell is null");

//         cells.push_back(new_cell);
//     }

//     return cells;
// }
