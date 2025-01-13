#pragma once

#include "animal_cells.hpp"
#include "plant_cells.hpp"

struct TransportCell
            : virtual Eukaryotes
{
    TransportCell()
        : Eukaryotes(),
        oxygen_pool(0),
        nut_pool(nullptr)
    {}
    
    virtual void feed(std::unique_ptr<DefaultEnergySource>) override = 0;
    virtual std::shared_ptr<Cell> splitting() override = 0;

    virtual void transfer_nutrients(std::shared_ptr<Cell> c) = 0;
    virtual void transfer_oxygen(std::shared_ptr<Cell> c) = 0;

    Oxygen                               oxygen_pool;
    std::unique_ptr<DefaultEnergySource> nut_pool;
};

struct BloodCell
            : TransportCell, AnimalCell
{
    BloodCell()
        : Cell(),
        TransportCell(),
        AnimalCell()
    {}

    BloodCell(std::shared_ptr<Cell> other)
        : Cell(other),
        TransportCell(),
        AnimalCell()
    {}

    std::shared_ptr<Cell> splitting() override {
        std::lock_guard<std::mutex> lock(_m);
        return _cf->splitting_eukaryotes<BloodCell>(shared_from_this());
    }

    void feed(std::unique_ptr<DefaultEnergySource> nut) override {
        AnimalCell::feed(std::move(nut));
    }

    void transfer_nutrients(std::shared_ptr<Cell> c) override {
        std::lock_guard<std::mutex> lock(_m);
        std::shared_ptr<AnimalCell> a_cell = std::dynamic_pointer_cast<AnimalCell>(c);
        if (c == nullptr || nut_pool == nullptr) {
            return;
        }
        c->feed(std::move(nut_pool));
        nut_pool = nullptr;
    }

    void transfer_oxygen(std::shared_ptr<Cell> c) override {
        std::lock_guard<std::mutex> lock(_m);
        std::shared_ptr<AnimalCell> a_cell = std::dynamic_pointer_cast<AnimalCell>(c);
        if (a_cell == nullptr || oxygen_pool == 0) {
            return;
        }
        a_cell->breath(oxygen_pool);
        oxygen_pool = 0;
    }

private:
    std::mutex _m;
};

struct PhloemJuice
            : TransportCell, PlantCell
{
    PhloemJuice()
        : TransportCell(),
        PlantCell()
    {}

    PhloemJuice(std::shared_ptr<Cell> other)
        : PlantCell(other)
    {}

    std::shared_ptr<Cell> splitting() override {
        std::lock_guard<std::mutex> lock(_m);
        return _cf->splitting_eukaryotes<ParenchymaCells>(shared_from_this());
    }

    void feed(std::unique_ptr<DefaultEnergySource> nut) override {
        PlantCell::feed(std::move(nut));
    }

    void transfer_nutrients(std::shared_ptr<Cell> c) override {
        std::lock_guard<std::mutex> lock(_m);
        std::shared_ptr<AnimalCell> p_cell = std::dynamic_pointer_cast<AnimalCell>(c);
        if (p_cell == nullptr || oxygen_pool == 0) {
            return;
        }
    }

    void transfer_oxygen(std::shared_ptr<Cell> c) override {
        std::lock_guard<std::mutex> lock(_m);
        std::shared_ptr<AnimalCell> a_cell = std::dynamic_pointer_cast<AnimalCell>(c);
        if (c == nullptr || oxygen_pool == 0) {
            return;
        }
    }

private:
    std::mutex _m;
};
