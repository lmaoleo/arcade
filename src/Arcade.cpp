/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include <dlfcn.h>

arcade::CoreProgram::CoreProgram()
{
    _score = 0;
    _keys = std::make_shared<state::Keybinds>();
    _game = nullptr;
    _graphic = nullptr;
}

arcade::CoreProgram::~CoreProgram()
{
}

int &arcade::CoreProgram::getScore()
{
    return _score;
}


void arcade::CoreProgram::loadGame(std::string game)
{
    void *handle = dlopen(game.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to open " << game << ": " << dlerror() << std::endl;
    } else {
        //use dlsym to load symbols/functions
    }
}

void arcade::CoreProgram::loadGraphic(std::string graphic)
{
    void *handle = dlopen(graphic.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to open " << graphic << ": " << dlerror() << std::endl;
    } else {
        //use dlsym to load symbols/functions
    }
}

int arcade::CoreProgram::loop()
{
    while (1) {
        // Here you can call the update functions of the game and the graphic
        // You can also call the event functions
    }
}