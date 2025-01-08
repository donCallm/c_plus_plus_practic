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
        _tf(std::make_shared<TissueFactory>())
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
    std::shared_ptr<TissueFactory>   _tf;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename AnimalCellType>
struct AnimalTissue
            : Tissue<AnimalCell>
{
    AnimalTissue()
        : Tissue<AnimalCell>()
    {}

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
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Muscles
            : AnimalTissue<MuscleCells>
{
    Muscles()
        : AnimalTissue<MuscleCells>()
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
            throw std::runtime_error("Some cell is null");

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
