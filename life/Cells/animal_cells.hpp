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
        _is_shrink = true;
    }

    void relax() {
        _is_shrink = false;
    }

private:
    bool _is_shrink;
};

struct Neurons
            : AnimalCell
{
    Neurons(std::shared_ptr<Neurons> n) {
        _sinaps.left_neighbor = n;
        n->_sinaps.right_neighbor = std::shared_ptr(this);
    }

    void send_signal(int& signal) {                   // transfer information to another cell
        _sinaps->right_neighbor->send_signal(signal);
    }
    
    void response_to_irritant (int& irritant) {       // Feel the touch
        _sinaps->right_neighbor->send_signal(irritant);
    }

    void information_processing(int& new_info) {
        _info.push_back(new_info);
        _sinaps->righ_neighbor->information_processing(new_info);
    }

private:
    struct sinaps {
        Neurons std::shared_ptr<right_neighbor>;
        Neurons std::shhared_ptr<left_neighbor>;
    };

private:
    bool _is_live;
    sinaps   _sinaps;
    std::vector<int> _info;
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
