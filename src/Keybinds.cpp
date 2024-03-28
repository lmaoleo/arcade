/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Keybinds
*/

#include "Keybinds.hpp"

state::Keybinds::Keybinds()
{
}

state::Keybinds::~Keybinds()
{
}

bool state::Keybinds::isKeyPressed(const std::string &action)
{
    return _pressed[action];
}

void state::Keybinds::bindKey(const std::string &action, unsigned short key)
{
    _binds[action] = key;
}

void state::Keybinds::keyPressed(const std::string &action, bool pressed)
{
    _pressed[action] = pressed;
}
