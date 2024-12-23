#pragma once

#include <string>
#include <vector>
#include <memory.h>
#include <optional>
#include "../Nutrients/nutrients.hpp"

/*
    Клетки будут строить не много новых,
    а только следующую за собой клетку.
    Если она уже поделилась, то больше
    она делиться не может.
    Прокариоты могут делиться сколько
    угодно раз.
*/

// constexpr const size_t MIN_CALL_IN_DAY = 7;
constexpr const float INCREASE_TO_SPLIT = 2.5

template <class Nut = DefaultNutrient>
using Nutrients = std::vector<std::unique_ptr<Nut>>;

struct Cell {
    Cell(size_t ata, Shape shape = Shape::Circle, Type type_ = Type::Prokaryotes)
        : _shape(shape),
        _type(type_)
    {
        _ata = ata - (ata / INCREASE_TO_SPLIT);
    }

    virtual ~Cell() {}

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

    template <typename NewCell = std::shared_ptr<Cell>>
    virtual NewCell splitting() = 0;
    virtual void feed(Nutrients<DefaultNutrient>) = 0

protected:
    void increace_energy(size_t count) { _call_count += count; }

protected:
    Shape  _shape;
    Type   _type;
    size_t _ata;
};

struct Prokaryotes
            : Cell, std::enable_shared_from_this<Prokaryotes>
{
    using NewProkaryotes = std::optional<std::unique_ptr<Prokaryotes>>;
    using NotEnoughEnergy = std::nullopt;

    Prokaryotes(std::shared_ptr<Prokaryotes> other)
        : Cell(other->_ata, other->_shape, other->_type)
    {
        other->_ata /= INCREASE_TO_SPLIT;
    }

    NewProkaryotes splitting() override {
        if ()
        return std::make_unique<Prokaryotes>(shared_from_this());
    }

    void increace_energy(Nutrients<DefaultNutrient> nuts) override {
        for (auto nut : nuts)
            add_call(nut->_call_value)
    }
private:
    
};

struct Eukaryotes
            : Cell, std::enable_shared_from_this<Eukaryotes>;

struct CytoplasmThread {                          // нужно у всех клеток реализовать соединение через них
    std::shared_ptr<Eukaryotes> right_neighbor;
    std::shared_ptr<Eukaryotes> left_neighbor;
};

struct Eukaryotes
            : Cell
{
    Eukaryotes(Type type, Shape shape = Shape::Circle)
        : Cell(shape, type)
    {}

    virtual Eukaryotes splitting() override = 0;
    virtual void increace_energy(Nutrients<DefaultNutrient> nuts) override = 0;

protected:
    std::string     _core;
    CytoplasmThread _thread;
};

struct CancerCell
        : Eukaryotes
{
    CancerCell(std::shared_ptr<CancerCell> other)
        : Eukaryotes(Shape::Circle, Type::CancerCell)
    {

    }


};
