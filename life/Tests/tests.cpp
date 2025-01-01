#include "tests.hpp"
#include "../Cells/animal_cells.hpp"
#include <iostream>
#include <assert.h>

template <typename T>
void fill_nuts(std::vector<std::unique_ptr<DefaultNutrient>>& nuts, const size_t count) {
    if (count == 0) return;
    
    for (size_t i = 0; i < count; ++i)
        nuts.push_back(std::unique_ptr<DefaultNutrient>(std::make_unique<T>()));
}

void default_functional() {
    std::cout << "DefaultFunctional\n";

    std::vector<std::unique_ptr<DefaultNutrient>> nuts;
    fill_nuts<DefaultNutrient>(nuts, 1);

    // try create cell
    std::shared_ptr<CancerCell> cell = std::make_shared<CancerCell>();
    assert(cell->ata() == 6);
    
    // try feed
    cell->feed(nuts);
    assert(cell->ata() == 7);

    // try split cell witout energy
    {
        std::shared_ptr<CancerCell> new_cell = std::static_pointer_cast<CancerCell>(cell->splitting());
        assert(new_cell == nullptr);
    }

    fill_nuts<DefaultNutrient>(nuts, 10);
    cell->feed(nuts);

    // try split cell with enought energy
    {
        std::shared_ptr<CancerCell> new_cell = std::static_pointer_cast<CancerCell>(cell->splitting());
        assert(new_cell != nullptr);
    }

    std::cout << "\t:complete;\n";
}

void test_animal_cells() {
    std::cout << "TestAnimalCells\n";

    std::vector<std::unique_ptr<DefaultNutrient>> nuts;
    fill_nuts<Protein>(nuts, 1);

    // try create cell
    std::shared_ptr<MuscleCells> m_cell = std::make_shared<MuscleCells>();
    assert(m_cell->ata() == 6);

    // try feed
    m_cell->feed(nuts);
    assert(m_cell->ata() == 10);

    // try split cell witout energy
    {
        std::shared_ptr<MuscleCells> new_cell = std::static_pointer_cast<MuscleCells>(m_cell->splitting());
        assert(new_cell == nullptr);
    }

    fill_nuts<Protein>(nuts, 10);
    m_cell->feed(nuts);

    // try split cell with enought energy
    {
        std::shared_ptr<MuscleCells> new_cell = std::static_pointer_cast<MuscleCells>(m_cell->splitting());
        assert(new_cell != nullptr);
    }

    std::cout << "\t:complete;\n";
}

void test() {
    default_functional();
    test_animal_cells();
}
