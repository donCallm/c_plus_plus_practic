#include <assert.h>
#include "tests.hpp"
#include "../Cells/animal_cells.hpp"
#include "../Cells/plant_cells.hpp"
#include "../Tissue/tissue.hpp"
#include <iostream>

/*
    Смерть клетки от нехватки нутриентов
    или кислорода нужно проверить уже в тканях.
*/

/*
    Стараться использовать ссылки,
    а не указатели. Ссылки не требуют проверок.
    Ссылка непосредственно указывает на объект,
    а указатель содержит адрес, который нужно прочитать.
    (Попробовать сделать так)
*/

void default_functional() {
    std::cout << "DefaultFunctional\n";

    try
    {
        // try create cell
        std::shared_ptr<CancerCell> cell = std::make_shared<CancerCell>();
        assert(cell->ata() == 6);
        
        // try feed
        cell->feed(std::unique_ptr<DefaultEnergySource>(std::make_unique<DefaultEnergySource>()));
        assert(cell->ata() == 7);

        // try split cell witout energy
        {
            std::shared_ptr<CancerCell> new_cell = std::static_pointer_cast<CancerCell>(cell->splitting());
            assert(new_cell == nullptr);
        }

        for (size_t i = 0; i < 10; ++i)
            cell->feed(std::unique_ptr<DefaultEnergySource>(std::make_unique<DefaultEnergySource>()));

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

        std::cout << "\t:complete\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "\t:error\n";
    }
}

void test_prokaryotes() {
    std::cout << "TestProcaryotes\n";

    try
    {
        // try create cell
        std::shared_ptr<Prokaryotes> cell = std::make_shared<Prokaryotes>();
        assert(cell->ata() == 6);
        
        // try feed
        cell->feed(std::unique_ptr<DefaultEnergySource>(std::make_unique<DefaultEnergySource>()));
        assert(cell->ata() == 7);

        // try split cell witout energy
        {
            std::shared_ptr<Prokaryotes> new_cell = std::static_pointer_cast<Prokaryotes>(cell->splitting());
            assert(new_cell == nullptr);
        }

        for (size_t i = 0; i < 10; ++i)
            cell->feed(std::unique_ptr<DefaultEnergySource>(std::make_unique<DefaultEnergySource>()));

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

        std::cout << "\t:complete\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "\t:error\n";
    }
}

void test_animal_cells() {
    std::cout << "TestAnimalCells\n";
    bool has_errors = false;
    try
    {
        // try create cell
        std::shared_ptr<MuscleCells> m_cell = std::make_shared<MuscleCells>();
        assert(m_cell->ata() == 6);

        // try feed
        m_cell->feed(std::unique_ptr<Protein>(std::make_unique<Protein>()));
        assert(m_cell->ata() == 10);

        // try split cell witout energy
        {
            std::shared_ptr<MuscleCells> new_cell = std::static_pointer_cast<MuscleCells>(m_cell->splitting());
            assert(new_cell == nullptr);
        }

        for (size_t i = 0; i < 10; ++i)
            m_cell->feed(std::unique_ptr<Protein>(std::make_unique<Protein>()));

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
        b_cell->oxygen_pool += 10;
        b_cell->substance_transfer(m_cell);
        assert(m_cell->oxygen() == 20);
    }
    catch(const std::exception& e)
    {
        std::cerr << "\t:AnimalCells::error(" << e.what() << ")\n";
        has_errors = true;
    }
    
    
    if (!has_errors) {
        std::cout << "\t:complete\n";
    }
}

/*
    Кровь долджна принимать прнимать вещества
    и потом отдавать в специализированные клетки
    (в каждой ткани должен быть массив крови).
*/

void test_animal_tissue() {
    std::cout << "TestTissueCells\n";
    try
    {
        std::shared_ptr<Muscles> m_tissue = std::make_shared<Muscles>();
        assert(m_tissue->cells_count() == 10);
        assert(m_tissue->blood_cells_count() == 10);

        std::vector<std::unique_ptr<DefaultEnergySource>> nuts;
        for (size_t i = 0; i < 10; ++i) {
            nuts.push_back(std::unique_ptr<Protein>(std::make_unique<Protein>()));
        }
        m_tissue->feed(nuts);

        m_tissue->shrink();
        m_tissue->relax();

        std::vector<Oxygen> o_pool = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
        m_tissue->get_oxygen(o_pool);
        m_tissue->breath();

        for (size_t i = 0; i < 10; ++i)
            nuts.push_back(std::unique_ptr<Protein>(std::make_unique<Protein>()));
        assert(nuts.size() == 10);

        m_tissue->get_nuts(nuts);
        assert(nuts.size() == 0);
        

        std::cout << "\t:complete\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "\t:Tissue::error(" << e.what() << ")\n";
    }
    
}

void test_plant_tissue() {

}

void test_cells() {
    default_functional();
    test_prokaryotes();
    test_animal_cells();
}

void test_tissue() {
    test_animal_tissue();
    test_plant_tissue();
}

void test() {
    test_cells();
    test_tissue();
}
