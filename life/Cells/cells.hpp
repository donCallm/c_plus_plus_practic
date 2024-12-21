#pragma once

#include <string>
#include <vector>
#include <memory.h>
#include "../Nutrients/nutrients.hpp"

// constexpr const size_t MIN_CALL_IN_DAY = 7;
template <class Nut = DefaultNutrient>
using Nutrients = std::vector<std::unique_ptr<Nut>>;

struct Cell {
    Cell(Shape shape)
        : _shape(shape)
    {}

    virtual ~Cell() {}
    
    virtual Cell splitting() = 0;
    virtual void feed(Nutrients<DefaultNutrient>) = 0;

    enum Shape {
        circle,
        square,
        rod_shaped,
        spiral_shaped
    };

protected:
    void add_call(size_t count) { _call_count += count; }

protected:
    Shape _shape;
    size_t _call_count;
};

struct Prokaryotes
            : Cell
{
    Prokaryotes splitting() override {

    }
    void feed(Nutrients<DefaultNutrient> nuts) override {
        for (auto nut : nuts)
            add_call(nut->_call_value)
    }
private:
    
};

struct Eukaryotes
            : Cell
{
    virtual Eukaryotes splitting() = 0;
    virtual void feed(Nutrients<DefaultNutrient> nuts) = 0;

protected:
    std::string _core;
    
};
