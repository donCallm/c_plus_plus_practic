#pragma once

#include <variant>
#include <typeinfo>
#include "cells.hpp"
#include <iostream>
#include <mutex>

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
            : virtual Eukaryotes
{
    AnimalCell()
        : Eukaryotes(Shape::Circle, Type::Animal)
    {}

    AnimalCell(std::shared_ptr<Cell> other)
        : Eukaryotes(other)
    {}

    virtual std::shared_ptr<Cell> splitting() override = 0;

    void feed(std::unique_ptr<DefaultEnergySource> nut) override {
        std::lock_guard<std::mutex> lock(_m);
        if (nut == nullptr) {
            return;
        }

        const std::type_info& nut_id = nut->get_type();
        if (nut_id != PROTEIN_ID && nut_id != FAT_ID && nut_id != CARB_ID) {
            return;
        }
        
        if (this->thread.has_right_neighbor() && this->thread.right_neighbor->ata() < this->ata()) {
            this->thread.right_neighbor->feed(std::move(nut));
            return;
        }
        this->increace_energy(nut->value());
    }

private:
    std::mutex _m;
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

struct MuscleCell
            : AnimalCell
{
    MuscleCell()
        : AnimalCell()
    {}

    MuscleCell(std::shared_ptr<Cell> other)
        : Cell(other),
        AnimalCell(other)
    {}

    std::shared_ptr<Cell> splitting() override {
        std::lock_guard<std::mutex> lock(_m);
        return _cf->splitting_eukaryotes<MuscleCell>(shared_from_this());
    }

    void shrink() {
        std::lock_guard<std::mutex> lock(_m);
        _is_shrink = true;
        while (_is_shrink && _oxygen_amount > MIN_CELL_OXYGEN && _ata > MIN_CELL_ENERGY) {
            spend_energy_for_work();
        }
        relax();
    }

    void relax() {
        _is_shrink = false;
    }

private:
    void spend_energy_for_work() {
        _oxygen_amount -= 2;
        _oxygen_amount -= 2;
    }

private:
    std::mutex _m;
    bool       _is_shrink;
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
