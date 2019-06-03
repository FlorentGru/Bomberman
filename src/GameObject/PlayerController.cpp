/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** PlayerController.cpp
*/

#include <iostream>
#include "PlayerController.hpp"

PlayerController::PlayerController(GraphicalElements &displayInfos) : _displayInfo(displayInfos)
{
}

PlayerController::PlayerController(KeyMap keyMap, GraphicalElements &displayInfos) : _displayInfo(displayInfos)
{
    _keyMap = keyMap;
}

PlayerController::~PlayerController()
{
}

const KeyMap &PlayerController::getKeyMap() const
{
    return (_keyMap);
}

void PlayerController::setKeyMap(KeyMap &keyMap)
{
    _keyMap = keyMap;
}

GraphicalElements &PlayerController::getDisplayInfo()
{
    return (_displayInfo);
}

void PlayerController::action(MyEventReceiver &events, irr::u16 speed)
{
    if (events.IsKeyDown(_keyMap.getBackward())) {
        setRotation(irr::EKA_MOVE_BACKWARD);
        move(irr::EKA_MOVE_BACKWARD, speed);
    }
    if (events.IsKeyDown(_keyMap.getForward())) {
        setRotation(irr::EKA_MOVE_FORWARD);
        move(irr::EKA_MOVE_FORWARD, speed);
    }
    if (events.IsKeyDown(_keyMap.getLeft())) {
        setRotation(irr::EKA_STRAFE_LEFT);
        move(irr::EKA_STRAFE_LEFT, speed);
    }
    if (events.IsKeyDown(_keyMap.getRight())) {
        setRotation(irr::EKA_STRAFE_RIGHT);
        move(irr::EKA_STRAFE_RIGHT, speed);
    }
}

void PlayerController::setRotation(irr::EKEY_ACTION action)
{
    irr::core::vector3df rotation = _displayInfo.getRotation();

    switch (action)
    {
    case irr::EKA_MOVE_BACKWARD:
        rotation.Z = 0;
        break;
    
    case irr::EKA_MOVE_FORWARD:
        rotation.Z = -180;
        break;
    
    case irr::EKA_STRAFE_LEFT:
        rotation.Z = 90;
        break;

    case irr::EKA_STRAFE_RIGHT:
        rotation.Z = -90;
        break;
    default:
        return;
    }
    _displayInfo.setRotation(rotation);
}

void PlayerController::move(irr::EKEY_ACTION action, irr::u16 speed)
{
    irr::core::vector3df position = _displayInfo.getPosition();
    irr::s16 offset = 1;

    std::cout << position.X << " " << position.Y << " " << position.Z << std::endl;
    switch (action)
    {
    case irr::EKA_MOVE_BACKWARD:
        position.Y -= offset * speed;
        break;
    
    case irr::EKA_MOVE_FORWARD:
        position.Y += offset * speed;
        break;
    
    case irr::EKA_STRAFE_LEFT:
        position.X += offset * speed;
        break;

    case irr::EKA_STRAFE_RIGHT:
        position.X -= offset * speed;
        break;
    default:
        return;
    }
    std::cout << position.X << " " << position.Y << " " << position.Z << std::endl;
    _displayInfo.setPosition(position);
}