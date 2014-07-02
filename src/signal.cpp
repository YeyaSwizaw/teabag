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
//// File: src/signal.cpp
//// Author: Samuel Sleight <samuel(dot)sleight(at)gmail(dot)com>
///////////////////////////////////////////////////////////////////////////////

#include "inc/signal.hpp"

TEABAG_NS

VoidSignal& GameSignals::tick() {
    return sigTick;
} 

VoidSignal& GameSignals::close() {
    return sigClose;
} 

IntIntSignal& GameSignals::resize() {
    return sigResize;
} 

VoidSignal& GameSignals::focusLoss() {
    return sigFocusLoss;
} 

VoidSignal& GameSignals::focusGain() {
    return sigFocusGain;
} 

UintSignal& GameSignals::textEntry() {
    return sigTextEntry;
} 

KeyCodeSignal& GameSignals::keyPress() {
    return sigKeyPress;
} 

KeyCodeSignal& GameSignals::keyRelease() {
    return sigKeyRelease;
} 

IntIntIntSignal& GameSignals::mouseWheel() {
    return sigMouseWheel;
} 

MouseButSignal& GameSignals::mousePress() {
    return sigMousePress;
} 

MouseButSignal& GameSignals::mouseRelease() {
    return sigMouseRelease;
} 

IntIntSignal& GameSignals::mouseMove() {
    return sigMouseMove;
} 

VoidSignal& GameSignals::mouseEntry() {
    return sigMouseEntry;
} 

VoidSignal& GameSignals::mouseLeave() {
    return sigMouseLeave;
} 

UintUintSignal& GameSignals::joystickPress() {
    return sigJoystickPress;
} 

UintUintSignal& GameSignals::joystickRelease() {
    return sigJoystickRelease;
} 

JoyAxisSignal& GameSignals::joystickMove() {
    return sigJoystickMove;
} 

UintSignal& GameSignals::joystickConnect() {
    return sigJoystickConnect;
} 

UintSignal& GameSignals::joystickDisconnect() {
    return sigJoystickDisconnect;
} 

void GameSignals::handleEvent(sf::Event& e) {
    switch(e.type) {
        case sf::Event::Closed:
            sigClose.call();
            break;

        case sf::Event::Resized:
            sigResize.call(e.size.width, e.size.height);
            break;

        case sf::Event::LostFocus:
            sigFocusLoss.call();
            break;

        case sf::Event::GainedFocus:
            sigFocusGain.call();
            break;

        case sf::Event::TextEntered:
            sigTextEntry.call(e.text.unicode);
            break;

        case sf::Event::KeyPressed:
            sigKeyPress.call(e.key.code, e.key.alt, e.key.shift, e.key.control, e.key.system);
            break;

        case sf::Event::KeyReleased:
            sigKeyRelease.call(e.key.code, e.key.alt, e.key.shift, e.key.control, e.key.system);
            break;

        case sf::Event::MouseWheelMoved:
            sigMouseWheel.call(e.mouseWheel.delta, e.mouseWheel.x, e.mouseWheel.y);
            break;

        case sf::Event::MouseButtonPressed:
            sigMousePress.call(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
            break;

        case sf::Event::MouseButtonReleased:
            sigMouseRelease.call(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
            break;

        case sf::Event::MouseMoved:
            sigMouseMove.call(e.mouseMove.x, e.mouseMove.y);
            break;

        case sf::Event::MouseEntered:
            sigMouseEntry.call();
            break;

        case sf::Event::MouseLeft:
            sigMouseLeave.call();
            break;

        case sf::Event::JoystickButtonPressed:
            sigJoystickPress.call(e.joystickButton.joystickId, e.joystickButton.button);
            break;

        case sf::Event::JoystickButtonReleased:
            sigJoystickRelease.call(e.joystickButton.joystickId, e.joystickButton.button);
            break;

        case sf::Event::JoystickMoved:
            sigJoystickMove.call(e.joystickMove.joystickId, e.joystickMove.axis, e.joystickMove.position);
            break;

        case sf::Event::JoystickConnected:
            sigJoystickConnect.call(e.joystickConnect.joystickId);
            break;

        case sf::Event::JoystickDisconnected:
            sigJoystickDisconnect.call(e.joystickConnect.joystickId);
            break;

        default:
            break;
    } 
} 

StringSignal& WorldSignals::levelLoad() {
    return sigLevelLoad;
} 

CollisionSignal& EntitySignals::collision() {
    return sigCollision;
} 

TEABAG_NS_END
