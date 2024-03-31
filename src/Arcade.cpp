/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include "graphic/IGraphic.hpp"
#include "game/IGame.hpp"
#include "graphic/Ncurses.hpp"
#include "game/Snake.hpp"
#include "graphic/Sdl.hpp"
#include <chrono>
#include <thread>
#include <dlfcn.h>


static void print_events(std::queue<state::Event> events)
{
    while (!events.empty()) {
        std::cout << "events.front().getType() = " << events.front().getType() << std::endl;
        events.pop();
    }
}

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
    _game = new game::Snake(_keys);
    // _graphic = new graphic::Ncurses(_keys);
    _graphic = new graphic::Sdl(_keys);
    std::queue<state::Event> events;

    using clock = std::chrono::steady_clock;
    std::chrono::milliseconds timestep(1000 / 5);
    auto next_tick = clock::now() + timestep;

    while (1) {
        _graphic->updateKeybinds();
        events = _game->tick();
        _graphic->draw(events);
        std::this_thread::sleep_until(next_tick);
        next_tick += timestep;
    }
    return 0;
}

int main ()
{
    arcade::CoreProgram core;
    core.loop();
    return 0;
}
