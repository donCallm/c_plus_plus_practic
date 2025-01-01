#pragma once

#include <variant>
#include <typeinfo>
#include "cells.hpp"
#include <iostream>

using warmth = size_t;
using sweat = size_t;

// добавить возможность при делении стать раковой и подумать о логике
constexpr const size_t NORMAL_TEMP = 36;
constexpr const size_t MAX_TEMP = 42;
constexpr const size_t MIN_TEMP = 24;

const std::type_info& PROTEIN_ID = typeid(Protein);
const std::type_info& FAT_ID = typeid(Fat);
const std::type_info& CARB_ID = typeid(Carb);

struct AnimalCell
            : Eukaryotes
{
    AnimalCell()
        : Eukaryotes(MIN_CELL_ENERGY, Shape::Circle, Type::Animal)
    {}

    AnimalCell(std::shared_ptr<AnimalCell> other)
        : Eukaryotes((other->_ata / 2), other->_shape, other->_type)
    {
        other->energy_reduction();
    }

    virtual std::shared_ptr<Cell> splitting() override = 0;
    void feed(Nutrients& _nuts) override {
        if (_nuts.size() < 0)
            return;

        const std::type_info& nut_id = _nuts[0]->get_type();
        if (nut_id != PROTEIN_ID && nut_id != FAT_ID && nut_id != CARB_ID) {
            std::cout << "HERE" << std::endl;
            return;
        }
        
        size_t i = _nuts.size();
        while (i > 0) {
            if (this->thread.right_neighbor && this->thread.right_neighbor->ata() < this->ata()) {
                this->thread.right_neighbor->feed(_nuts);
                return;
            }
            --i;
            std::unique_ptr<Nutrient> nut = std::unique_ptr<Nutrient>(static_cast<Nutrient*>(_nuts[i].release()));
            _nuts.erase(_nuts.begin() + i);
            size_t temp = nut->value();
            this->increace_energy(temp);
        }
    }
};

// struct EpithalialCells
//             : AnimalCell
// {
//     void highlight() { // example: to excrete saliva 

//     }

//     void clear() {     // example: the lungs are cleaned of dust 

//     }
    
//     void feel() {      // exampl: to smell or taste
    
//     }
// };

struct MuscleCells
            : AnimalCell
{
    MuscleCells()
        : AnimalCell()
    {}

    MuscleCells(std::shared_ptr<MuscleCells> other)
        : AnimalCell(other)
    {}

    std::shared_ptr<Cell> splitting() override {
        return _cf->splitting_eukaryotes<MuscleCells>(std::static_pointer_cast<MuscleCells>(shared_from_this()));
    }

    void shrink() {
        _is_shrink = true;
    }

    void relax() {
        _is_shrink = false;
    }

private:
    bool _is_shrink;
};

// struct Neurons
//             : AnimalCell
// {
//     Neurons(std::shared_ptr<Neurons> n) {
//         _sinaps.left_neighbor = n;
//         n->_sinaps.right_neighbor = std::shared_ptr(this);
//     }

//     void send_signal(int& signal) {                   // transfer information to another cell
//         _sinaps->right_neighbor->send_signal(signal);
//     }
    
//     void response_to_irritant (int& irritant) {       // Feel the touch
//         _sinaps->right_neighbor->send_signal(irritant);
//     }

//     void information_processing(int& new_info) {
//         _info.push_back(new_info);
//         _sinaps->righ_neighbor->information_processing(new_info);
//     }

// private:
//     struct sinaps {
//         Neurons std::shared_ptr<right_neighbor>;
//         Neurons std::shhared_ptr<left_neighbor>;
//     };

// private:
//     bool _is_live;
//     sinaps   _sinaps;
//     std::vector<int> _info;
// };

// struct BloodCells
//             : AnimalCell
// {
//     void substance_transfer() { // apply oxygen or opiates

//     }
// };

// struct ConnectiveCells
//             : AnimalCell
// {
//     void synthesis_recovery_substance() {

//     }
// };

// struct StemCells
//             : AnimalCell
// {
//     void generating_desired_cell() { // The cell must become the right type of cell.

//     }
// };

// struct PigmentCells
//             : AnimalCell
// {
//     enum Collor {
//         black,
//         white
//     };

//     void temperature_control() {

//     }
// };

// struct ImmuneCells
//             : AnimalCell
// {
//     void recognize_malicious_cells(std::shared_ptr<Cell> suspicious_cell) {
//         if (is_correct_cell(typeid(*checked).name())) {
//             return;
//         }
//         destroy_harmful_cells(std::shared_ptr<Cell> suspicious_cell);
//     }

    

// private:
//     void destroy_harmful_cells(std::shared_ptr<Cell> cell) {        // нужно сделать так, что бы из листа удалялись клетки, у которых нет соседей
//         cell->_thread.right_neighbor = cell->_thread.left_neighbor;
//         cell->_thread.right_neighbor = nullptr;
//         cell->_thread.lef_neighbor = cell->_thread.right_neighbor;
//         cell->_thread.lef_neighbor = nullptr;
//     }
// };

// struct SkinCells
//             : AnimalCell
// {
//     void get_irritant(int signal) {
//         if (_neuron->_is_live)
//             _neuron->response_to_irritant(signal);
//     }

//     std::variant<warmth, sweat> temperature_control() {
//         if (_temp == NORMAL_TEMP)
//             return;
//         else if (_temp > NORMAL_TEMP && _temp < MAX_TEMP)
//             // выделить пот
//         else if ()
//             tremble();
//     }

// private:
//     warmth tremble() {

//     }

// private:
//     std::shared_ptr<Neurons>         _neuron; // по идее должен быть еще промежуточный слой в виде рецптора, но не вижу пока смысла усложнять
//     std::shared_ptr<EpithalialCells> _epithalial;
//     size_t                          _temp;
// };
