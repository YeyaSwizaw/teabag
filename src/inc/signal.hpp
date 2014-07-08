////////////////////////////////////////////////////////////////////////////////
//// Copyright 2014 Samuel Sleight
////
//// Licensed under the Apache License, Version 2.0 (the "License");
//// you may not use this file except in compliance with the License.
//// You may obtain a copy of the License at
////
//// 		http://www.apache.org/licenses/LICENSE-2.0
////
//// Unless required by applicable law or agreed to in writing, software
//// distributed under the License is distributed on an "AS IS" BASIS,
//// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//// See the License for the specific language governing permissions and
//// limitations under the License.
///////////////////////////////////////////////////////////////////////////////
//// Project: Teabag
//// File: src/inc/signal.hpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#ifndef TEABAG_SIGNAL_HPP
#define TEABAG_SIGNAL_HPP

#include "defines.hpp"
#include "collision.hpp"

#include <vector>
#include <functional>

#include <SFML/Window.hpp>

TEABAG_NS

class Entity;
class World;
class Game;
class GameSignals;

/**
 * This class stores a vector of functions to be called whenever a
 * specific event happens.
 */
template<typename ...Args>
class Signal {
public:
    /**
     * The type of the callback functions for this signal.
     */
    typedef std::function<void(Args...)> FuncType;

    /**
     * Add a function to be called when the signal is called.
     */
    void connect(FuncType func);

    /**
     * Remove all callbacks from this signal.
     */
    void clear();

private:
    friend class Game;
    friend class GameSignals;
    friend class World;

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
typedef Signal<std::string> StringSignal;
typedef Signal<Collision> CollisionSignal;

// Storage structs
class TEABAG_API GameSignals {
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

class TEABAG_API WorldSignals {
public:
    StringSignal& levelLoad();

private:
    friend class World;

    StringSignal sigLevelLoad;
}; 

class TEABAG_API EntitySignals {
public:
    CollisionSignal& collision();

private:
    friend class World;
    friend class Entity;

    CollisionSignal sigCollision;
}; 

TEABAG_NS_END

#endif
