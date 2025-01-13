#pragma once

#include <mutex>
#include "cells.hpp"

struct PlantCell
            : Eukaryotes
{
    PlantCell()
        : Eukaryotes(Shape::Circle, Type::Plant)
    {}

    PlantCell(std::shared_ptr<Cell> other)
        : Eukaryotes(other)
    {}

    virtual std::shared_ptr<Cell> splitting() override = 0;

    void feed(std::unique_ptr<DefaultEnergySource> nut) override {
        std::lock_guard<std::mutex> lock(_m);
        if (nut == nullptr) {
            return;
        }

        if (this->thread.has_right_neighbor() && this->thread.right_neighbor->ata() < this->ata()) {
            this->thread.right_neighbor->feed(std::move(nut));
            return;
        }

        increace_energy(nut->value());
    }

private:
    std::mutex _m;
};

struct ParenchymaCells
            : PlantCell
{
    ParenchymaCells()
        : PlantCell()
    {}

    ParenchymaCells(std::shared_ptr<Cell> other)
        : PlantCell(other)
    {}

    void photosynthesis(std::unique_ptr<LightEnergy> eng) {
        this->feed(std::move(eng));
    }

    std::shared_ptr<Cell> splitting() override {
        std::lock_guard<std::mutex> lock(_m);
        return _cf->splitting_eukaryotes<ParenchymaCells>(shared_from_this());
    }

private:
    std::mutex _m;
};

// struct CollenchymaCells // for new part
//             : PlantCell
// {
//     size_t _endurance;
// };

// struct SclerenchymaCells // for old part
//             : PlantCell
// {
//     size_t _endurance;
// };

// struct EpidermisCells
//             : PlantCell
// {
//     features;               // roughness, spikes
// };

// struct VascularTissueCells
//             : PlantCell
// {
//     void substance_transfer() { // apply oxygen or opiates

//     }
// };

// struct MeristemicCells
//             : PlantCell
// {
//     void regenerate() {
        
//     }
// };
