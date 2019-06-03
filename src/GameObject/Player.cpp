/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(irr::IrrlichtDevice* device, std::vector<std::string> path_text, std::string &path_mesh, irr::u16 pos_x, irr::u16 pos_y)
{
    _device = device;
    irr::core::vector3df pos(pos_x, pos_y, 0);
    this->getDisplayInfo().setPosition(pos);
    this->getDisplayInfo().setRotation(irr::core::vector3df(90,0,0));
    this->getDisplayInfo().setMesh(_device->getSceneManager(), _device->getVideoDriver(), path_text, path_mesh);
}

void Player::update(MyEventReceiver event)
{
    this->getPlayerController().action(event);
}