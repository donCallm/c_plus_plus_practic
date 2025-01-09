#pragma once

#include <list>
#include <vector>
#include <future>
#include <unistd.h>
#include "../Cells/animal_cells.hpp"
// #include "../Cells/plant_cells.hpp"

constexpr size_t DEFAULT_MAX_CELLS_COUNT = 10;

using Nutrients = std::vector<std::unique_ptr<DefaultEnergySource>>;

template <typename CellType>
using Cells = std::vector<std::shared_ptr<CellType>>;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TissueFactory {
    Cells<BloodCells> build_blood(size_t count) {
        Cells<BloodCells> cells;
        auto first_cell = std::shared_ptr<BloodCells>(std::make_shared<BloodCells>());
        if (first_cell == nullptr) {
            throw std::runtime_error("First blood cell is null");
        }
        cells.push_back(first_cell);

        for (size_t i = 0; i < count - 1; ++i) {
            cells[i]->feed(std::unique_ptr<Fat>(std::make_unique<Fat>()));
            cells[i]->breath(10);

            auto new_cell = std::static_pointer_cast<BloodCells>(cells[i]->splitting());
            if (new_cell == nullptr) {
                throw std::runtime_error("Some blood cell is null");
            }

            cells.push_back(new_cell);
        }

        return cells;
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

    virtual void feed(Nutrients& nuts) = 0;

protected:
    Cells<CellType>                  _cells;
    std::unique_ptr<TissueFactory>   _tf;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AnimalTissue
            : Tissue<AnimalCell>
{
    AnimalTissue()
        : Tissue<AnimalCell>()
    {
        _blood = this->_tf->build_blood(DEFAULT_MAX_CELLS_COUNT);
    }

    void get_oxygen(std::vector<Oxygen>& pool) {
        if (pool.size() == 0) {
            return;
        }
        
        for (size_t i = 0; i < _blood.size(); i++)
        {
            size_t j = 0;
            while(true) {
                if (_blood[j]->oxygen_pool < _blood[j + 1]->oxygen_pool) {
                    _blood[j]->oxygen_pool += pool[i];
                    break;
                } else {
                    if (++j <_blood.size() -1)
                        break;
                }
            }
        }        
    }

    void get_nuts(Nutrients& nuts) {
        if (nuts.size() == 0) {
            return;
        }

        while (nuts.size() != 0) {
            size_t i = 0;
            while (true) {
                if (_blood[i]->nut_pool == nullptr) {
                    std::unique_ptr<DefaultEnergySource> nut = std::move(*(nuts.end() - 1));
                    nuts.erase(nuts.end() - 1);

                    const std::type_info& type = nut->get_type();
                    if (type != PROTEIN_ID && type != FAT_ID && type != CARB_ID) {
                        break;
                    }
                    
                    _blood[i]->nut_pool = std::move(nut);
                    break;
                }
                if (++i == _blood.size()) {
                    break;
                }
            }
        }
    }

    void breath() {
        std::vector<std::future<void>> pool;

        for (size_t i = 0; i < _cells.size(); ++i) {
            pool.push_back(std::async(std::launch::async, &BloodCells::transfer_oxygen, &(*_blood[0]), _cells[i]));
        }
        for(auto& f : pool) {
            f.get();
        }
    }

    // TODO: нужно переделать два этот метод, что бы он не принимал нутриенты,
    // а что бы все получалось из крови
    void feed(Nutrients& nuts) override {
        std::vector<std::future<void>> pool;
        size_t it = 1;
        for (size_t i = nuts.size(); i != 0; --i) {
            std::unique_ptr<DefaultEnergySource> nut = std::move(*(nuts.end() - 1));
            nuts.erase(nuts.end() - 1);
            pool.push_back(std::async(std::launch::async, &AnimalCell::feed, &(*_cells[0]), std::move(nut)));
        }
        for(auto& f : pool) {
            f.get();
        }
    }

    size_t blood_cells_count() { return _blood.size(); }

protected:
    Cells<BloodCells> _blood;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Muscles
            : AnimalTissue
{
    Muscles()
        : AnimalTissue()
    {
        this->_cells = this->_tf->build_animal<MuscleCells>(DEFAULT_MAX_CELLS_COUNT);
    }

    void shrink() {
        std::vector<std::future<void>> pool;
        for (size_t i = 0; i < _cells.size(); ++i)
        {
            std::shared_ptr<MuscleCells> m_c = std::static_pointer_cast<MuscleCells>(_cells[i]);
            pool.push_back(std::async(std::launch::async, &MuscleCells::shrink, &(*m_c)));
        }
        for(auto& f : pool) {
            f.get();
        }
    }

    void relax() {
        std::vector<std::future<void>> pool;
        for (size_t i = 0; i < _cells.size(); ++i)
        {
            std::shared_ptr<MuscleCells> m_c = std::static_pointer_cast<MuscleCells>(_cells[i]);
            pool.push_back(std::async(std::launch::async, &MuscleCells::relax, &(*m_c)));
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
    auto first_cell = std::static_pointer_cast<AnimalCell>(std::make_shared<CellType>());
    cells.push_back(first_cell);

    for (size_t i = 0; i < count - 1; ++i) {
        cells[i]->feed(std::unique_ptr<Fat>(std::make_unique<Fat>()));
        cells[i]->breath(10);

        auto new_cell = std::static_pointer_cast<AnimalCell>(cells[i]->splitting());
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
