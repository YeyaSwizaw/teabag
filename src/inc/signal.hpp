#ifndef TEABAG_SIGNAL_HPP
#define TEABAG_SIGNAL_HPP

#include "defines.hpp"

#include <vector>
#include <functional>

#include <SFML/Window.hpp>

TEABAG_NS

class Game;
class GameSignals;

/**
 * This class stores a vector of functions to be called whenever a
 * specific even happens.
 */
template<typename ...Args>
class Signal {
public:
    typedef std::function<void(Args...)> FuncType;

    void connect(FuncType func);
    void clear();

private:
    friend class Game;
    friend class GameSignals;

    std::vector<FuncType> funcs;

    void call(Args... args);
};

// Template implementation
template<typename ...Args>
void Signal<Args...>::connect(FuncType func) {
    funcs.push_back(func);
} 

template<typename ...Args>
void Signal<Args...>::clear() {
    funcs.clear();
} 

template<typename ...Args>
void Signal<Args...>::call(Args... args) {
    for(FuncType& func : funcs) {
        func(args...);
    } 
} 

// Convinience typedefs
typedef Signal<> VoidSignal;
typedef Signal<int, int> IntIntSignal;
typedef Signal<int, int, int> IntIntIntSignal;
typedef Signal<unsigned int> UintSignal;
typedef Signal<unsigned int, unsigned int> UintUintSignal;
typedef Signal<sf::Mouse::Button, int, int> MouseButSignal;
typedef Signal<sf::Keyboard::Key, bool, bool, bool, bool> KeyCodeSignal;
typedef Signal<unsigned int, sf::Joystick::Axis, float> JoyAxisSignal;

// Storage structs
class GameSignals {
public:
    VoidSignal& tick();
    VoidSignal& close();
    IntIntSignal& resize();
    VoidSignal& focusLoss();
    VoidSignal& focusGain();
    UintSignal& textEntry();
    KeyCodeSignal& keyPress();
    KeyCodeSignal& keyRelease();
    IntIntIntSignal& mouseWheel();
    MouseButSignal& mousePress();
    MouseButSignal& mouseRelease();
    IntIntSignal& mouseMove();
    VoidSignal& mouseEntry();
    VoidSignal& mouseLeave();
    UintUintSignal& joystickPress();
    UintUintSignal& joystickRelease();
    JoyAxisSignal& joystickMove();
    UintSignal& joystickConnect();
    UintSignal& joystickDisconnect();

private:
    friend class Game;

    void handleEvent(sf::Event& e);

    VoidSignal sigTick;
    VoidSignal sigClose;
    IntIntSignal sigResize;
    VoidSignal sigFocusLoss;
    VoidSignal sigFocusGain;
    UintSignal sigTextEntry;
    KeyCodeSignal sigKeyPress;
    KeyCodeSignal sigKeyRelease;
    IntIntIntSignal sigMouseWheel;
    MouseButSignal sigMousePress;
    MouseButSignal sigMouseRelease;
    IntIntSignal sigMouseMove;
    VoidSignal sigMouseEntry;
    VoidSignal sigMouseLeave;
    UintUintSignal sigJoystickPress;
    UintUintSignal sigJoystickRelease;
    JoyAxisSignal sigJoystickMove;
    UintSignal sigJoystickConnect;
    UintSignal sigJoystickDisconnect;
}; 

TEABAG_NS_END

#endif
