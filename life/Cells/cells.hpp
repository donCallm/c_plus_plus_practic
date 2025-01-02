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


/*
    Что бы сделать какое-то действие
    клетке нужен кислород.
    Эукариоты будут получать ее через
    специальные клетки (кровь и устьица).
    Прокариоты будут дышать сами.
*/

#define NotEnoughEnergy nullptr
#define WrongType nullptr

constexpr const size_t MIN_CELL_ENERGY = 6;
constexpr const size_t MIN_CELL_OXYGEN = 6;
constexpr const size_t INCREASE_TO_SPLIT = 2;

struct Cell;
struct Eukaryotes;
struct Prokaryotes;
struct CancerCell;

using Nutrients = std::vector<std::unique_ptr<DefaultEnergySource>>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename EukaryotesType = Eukaryotes>
struct CytoplasmThread {                          // для соединения клеток одного типа
    bool has_two_neighbors()  { return (right_neighbor != nullptr && left_neighbor != nullptr) ? true : false; }
    bool has_right_neighbor() { return (right_neighbor != nullptr) ? true : false; }
    bool has_left_neighbor()  { return (left_neighbor != nullptr) ? true : false; }

    std::shared_ptr<EukaryotesType> right_neighbor = nullptr;
    std::shared_ptr<EukaryotesType> left_neighbor = nullptr;
};

struct CellFactory {
    friend struct Cell;

    template <typename EukaryotesType = Eukaryotes>
    std::shared_ptr<Cell> splitting_eukaryotes(std::shared_ptr<Cell> other);
    std::shared_ptr<Cell> splitting_prokaryotes(std::shared_ptr<Cell> other);

private:
    template <typename EukaryotesType = Eukaryotes>
    void add_thread(std::shared_ptr<EukaryotesType> old_cell, std::shared_ptr<EukaryotesType> new_cell) {
        old_cell->thread.right_neighbor = new_cell;
        new_cell->thread.left_neighbor = old_cell;
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Cell
            : std::enable_shared_from_this<Cell>
{
    enum Shape {
        Circle,
        Square,
        RodShaped,
        SpiralShaped,
        Elongated
    };

    enum Type {
        Prokaryotes,
        CancerCell,
        Animal,
        Plant
    };

    Cell(Shape shape = Shape::Circle, Type type_ = Type::Prokaryotes)
        : _cf(std::make_unique<CellFactory>()),
        _shape(shape),
        _type(type_),
        _ata(MIN_CELL_ENERGY),
        _oxygen_amount(MIN_CELL_OXYGEN)
    {}

    Cell(std::shared_ptr<Cell> other)
        : _cf(std::make_unique<CellFactory>()),
        _shape(other->_shape),
        _type(other->_type),
        _ata(MIN_CELL_ENERGY),
        _oxygen_amount(MIN_CELL_OXYGEN)
    {
        other->split_reduction();
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
    virtual void feed(Nutrients&) = 0;
    virtual std::shared_ptr<Cell> splitting() = 0;

    void breath(size_t molecules_count) {
        _oxygen_amount += molecules_count;
    }
    size_t ata() {
        return _ata;
    }
    size_t oxygen() {
        return _oxygen_amount;
    }
    bool enough_energy() {
        return (_ata - MIN_CELL_ENERGY) > MIN_CELL_ENERGY;
    }
    bool enough_oxygen() {
        return (_oxygen_amount - MIN_CELL_OXYGEN) > MIN_CELL_OXYGEN;
    }

protected:
    void split_reduction() {
        _ata -= MIN_CELL_ENERGY;
        _oxygen_amount -= MIN_CELL_OXYGEN;
    }
    void increace_energy(size_t count) { _ata += count; }

protected:
    std::unique_ptr<CellFactory> _cf;
    Shape                        _shape;
    Type                         _type;
    size_t                       _ata;
    size_t                       _oxygen_amount;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Prokaryotes
            : Cell
{
    Prokaryotes()
        : Cell(Cell::Shape::Circle, Cell::Type::Prokaryotes)
    {}

    Prokaryotes(std::shared_ptr<Cell> other)
        : Cell(other)
    {}

    std::shared_ptr<Cell> splitting() override {
        return _cf->splitting_prokaryotes(shared_from_this());
    }

    void feed(Nutrients& nuts) override {
        for (auto& nut : nuts)
            increace_energy(nut->value());
    }
};

struct Eukaryotes
            : Cell
{
    Eukaryotes()
        : Cell(Cell::Shape::Circle, Cell::Type::Plant)
    {}

    Eukaryotes(Cell::Shape shape, Cell::Type type)
        : Cell(shape, type)
    {}

    Eukaryotes(std::shared_ptr<Cell> other)
        : Cell(other)
    {}

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

    virtual void feed(Nutrients&) override = 0;
    virtual std::shared_ptr<Cell> splitting() override = 0;

public:
    CytoplasmThread<Eukaryotes> thread;

protected:
    std::string _core;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CancerCell
        : Eukaryotes
{
    CancerCell()
        : Eukaryotes(Shape::Circle, Type::CancerCell)
    {}

    CancerCell(std::shared_ptr<Cell> other)
        : Eukaryotes(other)
    {}

    std::shared_ptr<Cell> splitting() override {
        return _cf->splitting_eukaryotes<CancerCell>(shared_from_this());
    }

    void feed(Nutrients& _nuts) override {
        size_t i = _nuts.size();
        while (i > 0) {
            if (this->thread.right_neighbor && this->thread.right_neighbor->ata() < this->ata()) {
                this->thread.right_neighbor->feed(_nuts);
                return;
            }
            --i;
            std::unique_ptr<DefaultEnergySource> nut = std::move(_nuts[i]);
            _nuts.erase(_nuts.begin() + i);
            size_t temp = nut->value();
            this->increace_energy(temp);
        }
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename EukaryotesType>
std::shared_ptr<Cell> CellFactory::splitting_eukaryotes(std::shared_ptr<Cell> other) {
    if (auto cell = std::dynamic_pointer_cast<EukaryotesType>(other)) {
        if (!cell->enough_energy() || !cell->enough_oxygen())
            return NotEnoughEnergy;

        auto new_cell = std::make_shared<EukaryotesType>(other);
        add_thread(cell, new_cell);
        return new_cell;
    }
    return WrongType;
}

std::shared_ptr<Cell> CellFactory::splitting_prokaryotes(std::shared_ptr<Cell> other) {
    if (auto cell = std::dynamic_pointer_cast<Prokaryotes>(other)) {
        if (!cell->enough_energy() || !cell->enough_oxygen())
            return NotEnoughEnergy;
        return std::make_shared<Prokaryotes>(cell);
    }
    return WrongType;
}
