class NPC;

class State {
public:
    virtual State* doState(NPC* npc) = 0;
    virtual ~State() {}
};

class PeacefulState: public State {
    State* doState(NPC* npc) override {
        if (npc->hungry < 50) {
            npc->energy = 100;
            npc->power = 100;
            return npc->_atackState;
        }
        return npc->_peacefulState;
    }
};


class AtackState: public State {
    State* doState(NPC* npc) override {
        if (npc->hungry > 50) {
            npc->energy = 0;
            npc->power = 0;
            return npc->_peacefulState;
        }
        return npc->_atackState;
    }
};

class NPC {
public:
    friend class AtackState;
    friend class PeacefulState;

public:
    NPC() {
        _peacefulState = new PeacefulState;
        _atackState = new AtackState;
        _currentState = _peacefulState;
    }

    ~NPC() {
        delete _currentState;
        delete _atackState;
        delete _peacefulState;
    }

public:
    void update() {
        _currentState = _currentState->doState(this);
    }
    
private:
    int hungry = 100;
    int power = 0;
    int energy = 0;

    State* _peacefulState;
    State* _atackState;
    State* _currentState;
};
