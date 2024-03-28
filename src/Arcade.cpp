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
    _keys = state::Keybinds();
    _game = std::unique_ptr<game::IGame>();
    _graphic = std::unique_ptr<graphic::IGraphic>();
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
        // You can now use dlsym to load symbols/functions from the library
    }
}

void arcade::CoreProgram::loadGraphic(std::string graphic)
{
    void *handle = dlopen(graphic.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to open " << graphic << ": " << dlerror() << std::endl;
    } else {
        // You can now use dlsym to load symbols/functions from the library
    }
}

int arcade::CoreProgram::loop()
{
    while (1) {
        // Here you can call the update functions of the game and the graphic
        // You can also call the event functions
    }
}