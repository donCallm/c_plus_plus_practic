#include <iostream>
#include <queue>

class Action {
public:
    virtual void doAction() = 0;
    virtual ~Action() {}
};

class Move: public Action {
public:
    void doAction() override {
        std::cout << "Move\n";
    }
};

class Atack: public Action {
public:
    void doAction() override {
        std::cout << "Atack\n";
    }
};

class Talk: public Action {
public:
    void doAction() override {
        std::cout << "Talk\n";
    }
};

class IUnit {
public:
    IUnit(Action* act)
        : _action(act)
    {}

protected:
    Action* _action;
};

class Warrior: public IUnit {
public:
    Warrior()
        : IUnit(new Atack)
    {}

public:
    void atack() {
        _action->doAction();
    }
};

class Runner: public IUnit {
public:
    Runner()
        : IUnit(new Move)
    {}

public:
    void move() {
        _action->doAction();
    }
};

class Negotiator: public IUnit {
    Negotiator()
        : IUnit(new Talk)
    {}

public:
    void talk() {
        _action->doAction();
    }
};
