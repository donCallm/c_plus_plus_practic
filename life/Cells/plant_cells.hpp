#pragma once

#include "cells.hpp"

struct PlantCell
            : Eukaryotes
{
    PlantCell splitting() override {

    }
    void feed(Nutrients<LightEnergi>& _nuts) override {
            size_t i = _nuts.size();
            while (i > 0) {
                if (this->_tread.right_neighbor->_ata < this->_ata) {
                    this->_tread.right_neighbor->feed(_nuts);
                    return;
                }
                --i;
                std::unique_ptr<DefaultNutrient> nut = _nuts.pop_back();
                increace_energy(nut->value());
            }   
        }

private:
    std::string _vacuole;
    std::string _chloroplast;
};

// struct ParenchymaCells
//             : PlantCell
// {
//     void stock_up() {
        
//     }

//     void photosynthesis() {

//     }

// private:
//     size_t _call_count
// };

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
