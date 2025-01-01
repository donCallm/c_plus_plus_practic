#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "../Nutrients/nutrients.hpp"
#include <iostream>

/*
    Клетки будут строить не много новых,
    а только следующую за собой клетку.
    Если она уже поделилась, то больше
    она делиться не может.
    Прокариоты могут делиться сколько
    угодно раз.
*/

#define NotEnoughEnergy std::nullopt

constexpr const size_t MIN_CELL_ENERGY = 7;
constexpr const float INCREASE_TO_SPLIT = 2.5;

template <typename T>
struct Cell;
template <typename T>
struct Eukaryotes;
struct Prokaryotes;
struct CancerCell;

template <class Nut = DefaultNutrient>
using Nutrients = std::vector<std::unique_ptr<Nut>>;

using NewProkaryotes = std::optional<std::shared_ptr<Prokaryotes>>;

template <typename EukaryotesType>
using NewEukaryotes = std::optional<std::shared_ptr<EukaryotesType>>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename EukaryotesType = Eukaryotes<CancerCell>>
struct CytoplasmThread {                          // для соединения клеток одного типа
    bool has_two_neighbors()  { return (right_neighbor && left_neighbor) ? true : false; }
    bool has_right_neighbor() { return (right_neighbor) ? true : false; }
    bool has_left_neighbor()  { return (left_neighbor) ? true : false; }

    std::shared_ptr<EukaryotesType> right_neighbor = nullptr;
    std::shared_ptr<EukaryotesType> left_neighbor = nullptr;
};


struct CellFactory {
    friend struct Cell<Prokaryotes>;

    template <typename Type>
    NewEukaryotes<Type> splitting_eukaryotes(std::shared_ptr<Type> other);

    NewProkaryotes splitting_prokaryotes(std::shared_ptr<Prokaryotes> other);

private:
    template <typename EukaryotesType = Eukaryotes<CancerCell>>
    void add_thread(std::shared_ptr<EukaryotesType> old_cell, std::shared_ptr<EukaryotesType> new_cell) {
        old_cell->thread.right_neighbor = new_cell;
        new_cell->thread.left_neighbor = old_cell;
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct Cell
            : std::enable_shared_from_this<T>
{
    using NewCell = std::optional<std::shared_ptr<Cell<T>>>;

    enum Shape {
        Circle,        // default
        Square,
        RodShaped,
        SpiralShaped
    };

    enum Type {
        Prokaryotes,  // default
        CancerCell,
        Animal,
        Plant
    };

    Cell(size_t ata, Shape shape = Shape::Circle, Type type_ = Type::Prokaryotes)
        : _shape(shape),
        _type(type_)
    {
        _ata = ata - (ata / INCREASE_TO_SPLIT);
    }

    virtual ~Cell() {}
    /*
        Клетка будет принимать вектор
        нутриентов и есть их по одному.
        Если у следующей клетки меньше
        энергии, то набор нутриентов
        переходит ей. Количество
        нутриентов будет делиться равно
        для каждой ткани. Когда набралось
        достаточное количество энергии и
        размер ткани составляет нужное
        число клеток, они будут по умирать.
        Прокариоты просто будут есть
        и делится, если поделилсь какое-то
        число раз, наберут нужное количество
        энергии и умрут.
    */
    virtual void feed(Nutrients<>&) = 0;
    virtual NewCell splitting() = 0;
    size_t ata() { return _ata; }
    bool enough_energy() {
        return (_ata / INCREASE_TO_SPLIT) >= MIN_CELL_ENERGY;
    }

protected:
    void energy_reduction() { _ata /= INCREASE_TO_SPLIT; }
    void increace_energy(size_t count) { _ata += count; }

protected:
    std::unique_ptr<CellFactory> _cf;
    Shape                        _shape;
    Type                         _type;
    size_t                       _ata;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Prokaryotes
            : Cell<Prokaryotes>
{
    Prokaryotes()
        : Cell(MIN_CELL_ENERGY, Cell<Prokaryotes>::Shape::Circle, Cell<Prokaryotes>::Type::Prokaryotes)
    {}

    Prokaryotes(std::shared_ptr<Prokaryotes> other)
        : Cell(other->_ata, other->_shape, other->_type)
    {
        other->energy_reduction();
    }

    NewCell splitting() override {
        return _cf->splitting_prokaryotes(shared_from_this());
    }

    void feed(Nutrients<DefaultNutrient>& nuts) override {
        for (auto& nut : nuts)
            increace_energy(nut->value());
    }
};

template <typename U>
struct Eukaryotes
            : Cell<U>
{
    Eukaryotes()
        : Cell<U>(MIN_CELL_ENERGY, Cell<U>::Shape::Circle, Cell<U>::Type::Plant)
    {}

    Eukaryotes(size_t ata, Cell<U>::Shape shape, Cell<U>::Type type)
        : Cell<U>(ata, shape, type)
    {}

    Eukaryotes(std::shared_ptr<Eukaryotes> other)
        : Cell<U>(other->_ata, other->_shape, other->_type)
    {
        other->energy_reduction();
    }

    ~Eukaryotes() {
        if (!thread.has_two_neighbors()) {
            return;
        } else if (thread.has_two_neighbors()) {
            this->thread.right_neighbor->thread.left_neighbor = this->thread.left_neighbor;
            this->thread.left_neighbor->thread.right_neighbor = this->thread.right_neighbor;
        } else if (thread.has_left_neighbor()) {
            this->thread.left_neighbor->thread.right_neighbor = nullptr;
        } else if (thread.has_right_neighbor()) {
            this->thread.right_neighbor->thread.left_neighbor = nullptr;
        }
    }

    virtual void feed(Nutrients<>&) override = 0;
    virtual Cell<U>::NewCell splitting() override = 0;

public:
    CytoplasmThread<Eukaryotes> thread;

protected:
    std::string _core;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CancerCell
        : Eukaryotes<CancerCell>
{
    CancerCell()
        : Eukaryotes(10, Shape::Circle, Type::CancerCell)
    {}

    CancerCell(std::shared_ptr<CancerCell> other)
        : Eukaryotes(other->_ata, Shape::Circle, Type::CancerCell)
    {
        other->energy_reduction();
    }

    NewCell splitting() override {
        return _cf->splitting_eukaryotes<CancerCell>(shared_from_this());
    }

    void feed(Nutrients<DefaultNutrient>& _nuts) override {
        size_t i = _nuts.size();
        while (i > 0) {
            if (this->thread.right_neighbor && this->thread.right_neighbor->ata() < this->ata()) {
                this->thread.right_neighbor->feed(_nuts);
                return;
            }
            --i;
            std::unique_ptr<DefaultNutrient> nut = std::move(_nuts[i]);
            _nuts.erase(_nuts.begin() + i);
            size_t temp = nut->value();
            this->increace_energy(temp);
        }
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Type>
NewEukaryotes<Type> CellFactory::splitting_eukaryotes(std::shared_ptr<Type> other) {
        if (!other->enough_energy()) {
        return NotEnoughEnergy;
    }

    auto new_cell = std::make_shared<Type>(other);
    add_thread(other, new_cell); // может это нужно делать в конструкторе?
    return new_cell;
}

NewProkaryotes CellFactory::splitting_prokaryotes(std::shared_ptr<Prokaryotes> other) {
    if (auto prokaryote = std::dynamic_pointer_cast<Prokaryotes>(other)) {
        if (!prokaryote->enough_energy()) {
            return std::make_shared<Prokaryotes>(other);
        }
        return NotEnoughEnergy;
    }
    return NotEnoughEnergy;
}
