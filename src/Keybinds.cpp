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

bool state::Keybinds::isKeyPressed(const std::string &action) const
{
    auto it = _pressed.find(action);
    return (it != _pressed.end()) ? it->second : false;
}

void state::Keybinds::keyPressed(const std::string &action, bool pressed)
{
    _pressed[action] = pressed;
}

void state::Keybinds::bindKey(const std::string &action, int key)
{
    _binds[action] = key;
}
