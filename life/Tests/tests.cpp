#include "tests.hpp"
#include "../Cells/animal_cells.hpp"
#include <iostream>
#include <assert.h>

/*
    Смерть клетки от нехватки нутриентов
    или кислорода нужно проверить уже в тканях.
*/

template <typename T>
void fill_nuts(std::vector<std::unique_ptr<DefaultEnergySource>>& nuts, const size_t count) {
    if (count == 0) return;
    
    for (size_t i = 0; i < count; ++i)
        nuts.push_back(std::unique_ptr<DefaultEnergySource>(std::make_unique<T>()));
}

void default_functional() {
    std::cout << "DefaultFunctional\n";

    try
    {
        std::vector<std::unique_ptr<DefaultEnergySource>> nuts;
        fill_nuts<DefaultEnergySource>(nuts, 1);

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

        fill_nuts<DefaultEnergySource>(nuts, 10);
        cell->feed(nuts);

        // try split cell without oxygen
        {
            std::shared_ptr<CancerCell> new_cell = std::static_pointer_cast<CancerCell>(cell->splitting());
            assert(new_cell == nullptr);
        }

        cell->breath(10);

        // success split
        {
            std::shared_ptr<CancerCell> new_cell = std::static_pointer_cast<CancerCell>(cell->splitting());
            assert(new_cell != nullptr);
            cell->thread.right_neighbor = nullptr;
        }

        std::cout << "\t:complete;\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "\t:error;\n";
    }
}

void test_prokaryotes() {
    std::cout << "TestProcaryotes\n";

    try
    {
        std::vector<std::unique_ptr<DefaultEnergySource>> nuts;
        fill_nuts<DefaultEnergySource>(nuts, 1);

        // try create cell
        std::shared_ptr<Prokaryotes> cell = std::make_shared<Prokaryotes>();
        assert(cell->ata() == 6);
        
        // try feed
        cell->feed(nuts);
        assert(cell->ata() == 7);

        // try split cell witout energy
        {
            std::shared_ptr<Prokaryotes> new_cell = std::static_pointer_cast<Prokaryotes>(cell->splitting());
            assert(new_cell == nullptr);
        }

        fill_nuts<DefaultEnergySource>(nuts, 10);
        cell->feed(nuts);

        // try split cell without oxygen
        {
            std::shared_ptr<Prokaryotes> new_cell = std::static_pointer_cast<Prokaryotes>(cell->splitting());
            assert(new_cell == nullptr);
        }

        cell->breath(10);

        // success split
        {
            std::shared_ptr<Prokaryotes> new_cell = std::static_pointer_cast<Prokaryotes>(cell->splitting());
            assert(new_cell != nullptr);
        }

        std::cout << "\t:complete;\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "\t:error;\n";
    }
}

void test_animal_cells() {
    std::cout << "TestAnimalCells\n";
    bool has_errors = false;
    try
    {
        std::vector<std::unique_ptr<DefaultEnergySource>> nuts;
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

        // try split cell without oxygen
        {
            std::shared_ptr<MuscleCells> new_cell = std::static_pointer_cast<MuscleCells>(m_cell->splitting());
            assert(new_cell == nullptr);
        }

        m_cell->breath(10);

        // success split
        {
            std::shared_ptr<MuscleCells> new_cell = std::static_pointer_cast<MuscleCells>(m_cell->splitting());
            assert(new_cell != nullptr);
            m_cell->thread.right_neighbor = nullptr;
        }

        std::shared_ptr<BloodCells> b_cell = std::make_shared<BloodCells>();
        // try breath without oxygen pool
        b_cell->substance_transfer(m_cell);
        assert(m_cell->oxygen() == 10);

        // success breath
        b_cell->get_oxygen(10);
        b_cell->substance_transfer(m_cell);
        assert(m_cell->oxygen() == 20);
    }
    catch(const std::exception& e)
    {
        std::cout << "\t:MusclesCells - error;\n";
        has_errors = true;
    }
    
    
    if (!has_errors) {
        std::cout << "\t:complete;\n";
    }
}

void test_cells() {
    default_functional();
    test_prokaryotes();
    test_animal_cells();
}

void test() {
    test_cells();
}
