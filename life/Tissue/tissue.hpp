#pragma once

#include <list>
#include <vector>
#include <future>
#include "../Cells/animal_cells.hpp"

constexpr size_t DEFAULT_MAX_CELLS_COUNT = 100;

struct Tissue {
    const size_t MAX_CELLS_COUNT;

    Tissue(size_t max_cells = DEFAULT_MAX_CELLS_COUNT)
        : MAX_CELLS_COUNT(max_cells),
        _cells(MAX_CELLS_COUNT)
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

protected:
    std::list<std::shared_ptr<Eukaryotes>> _cells;
};

struct Muscles
            : Tissue
{
    Muscles()
        : Tissue()
    {}

    void shrink() {
        std::vector<std::future<void>> futures;
        for (std::shared_ptr<Eukaryotes> c : _cells) {
            std::shared_ptr<MuscleCells> temp = std::static_pointer_cast<MuscleCells>(c);
            futures.push_back(std::async(std::launch::async, &MuscleCells::shrink, &(*temp)));
        }
        for(auto& f : futures) {
            f.get();
        }
    }

    void relax() {
        std::vector<std::future<void>> futures;
        for (std::shared_ptr<Eukaryotes> c : _cells) {
            std::shared_ptr<MuscleCells> temp = std::static_pointer_cast<MuscleCells>(c);
            futures.push_back(std::async(std::launch::async, &MuscleCells::relax, &(*temp)));
        }
        for(auto& f : futures) {
            f.get();
        }
    }
};
