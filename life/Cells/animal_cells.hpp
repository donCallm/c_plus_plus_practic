#pragma once

#include "cells.hpp"

// добавить возможность при делении стать раковой и подумать о логике

struct AnimalCell
            : Eukaryotes
{
    virtual AnimalCell splitting() = 0;
    void feed(Nutrients<Nutrient> nuts) override {
        for (auto nut : nuts)
            add_call(nut->_call_value)
    }
};

struct EpithalialCells
            : AnimalCell
{
    void highlight() { // example: to excrete saliva 

    }

    void clear() {     // example: the lungs are cleaned of dust 

    }
    
    void feel() {      // exampl: to smell or taste
    

    }
};

struct MuscleCells
            : AnimalCell
{
    void shrink() {

    }
};

struct Neurons
            : AnimalCell
{
    void send_signal() {            // transfer information to another cell

    }
    
    void response_to_irritant () {  // Feel the touch

    }

    void information_processing() {

    }

private:
    vector<> _info;
};

struct BloodCells
            : AnimalCell
{
    void substance_transfer() { // apply oxygen or opiates

    }
};

struct ConnectiveCells
            : AnimalCell
{
    void synthesis_recovery_substance() {

    }
};

struct StemCells
            : AnimalCell
{
    void generating_desired_cell() { // The cell must become the right type of cell.

    }
};

struct PigmentCells
            : AnimalCell
{
    enum Collor {
        black,
        white
    };

    void temperature_control() {

    }
};

struct ImmuneCells
            : AnimalCell
{
    void recognize_malicious_cells() {

    }

    void destroy_harmful_cells() {

    }
};

struct SkinCells
            : AnimalCell
{
    void get_irritant() {

    }

    void temperature_control() {

    }
};
