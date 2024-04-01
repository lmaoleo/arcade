/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Menu
*/

#include "Menu.hpp"

game::Menu::Menu(std::shared_ptr<state::Keybinds> &key)
{
    _keys = key;
}

game::Menu::~Menu()
{
}

std::queue<state::Event> game::Menu::tick()
{
    std::queue<state::Event> events;
    return events;
}
