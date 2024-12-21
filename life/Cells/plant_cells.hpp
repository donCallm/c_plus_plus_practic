#pragma once

#include "cells.hpp"

struct PlantCell
            : Eukaryotes
{
    PlantCell splitting() override {

    }
    void feed(Nutrients<LightEnergi> nuts) override {
        for (auto nut : nuts)
            add_call(nut->_call_value)
    }

private:
    std::string _vacuole;
    std::string _chloroplast;
};

struct ParenchymaCells
            : PlantCell
{
    void stock_up() {
        
    }

    void photosynthesis() {

    }

private:
    size_t _call_count
};

struct CollenchymaCells // for new part
            : PlantCell
{
    size_t _endurance;
};

struct SclerenchymaCells // for old part
            : PlantCell
{
    size_t _endurance;
};

struct EpidermisCells
            : PlantCell
{
    features;               // roughness, spikes
};

struct VascularTissueCells
            : PlantCell
{
    void substance_transfer() { // apply oxygen or opiates

    }
};

struct MeristemicCells
            : PlantCell
{
    void regenerate() {
        
    }
};
