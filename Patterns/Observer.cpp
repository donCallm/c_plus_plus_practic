#include <iostream>
#include <vector>
#include <algorithm>

class Event;

class Observer {
public:
    virtual void onUpdate(Event* event) = 0;
    virtual void onSome(Event* event)   = 0;
    virtual ~Observer() {}
};

class Display: public Observer {
public:
    void onUpdate(Event* event) override {
        std::cout << "Display something\n";
    }

    void onSome(Event* event) override {
        std::cout << "Display something else\n";
    }
};

class Handler: public Observer {
public:
    void onUpdate(Event* event) override {
        std::cout << "Handle something\n";
    }
    
    void onSome(Event* event) override {
        std::cout << "Handle something else\n";
    }
};

class Event {
public:
    void subscribe(Observer* obs) {
        _followers.push_back(obs);
    }

    void unsubscribe(Observer* obs) {
        _followers.erase(std::find(_followers.begin(), _followers.end(), obs));
    }

    void update() {
        onUpdateNotify();
    }

    void doSome() {
        onSomeNotify();
    }

private:
    void onUpdateNotify() {
        for(size_t i = 0; i < _followers.size(); ++i) {
            _followers[i]->onUpdate(this);
        }
    }

    void onSomeNotify() {
        for(size_t i = 0; i < _followers.size(); ++i) {
            _followers[i]->onSome(this);
        }
    }
    
private:
    std::vector<Observer*> _followers;
};
