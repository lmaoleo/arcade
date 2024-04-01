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
#include "game/Menu.hpp"
#include "graphic/Sdl.hpp"
#include <chrono>
#include <thread>
#include <dlfcn.h>


// static void print_events(std::queue<state::Event> events)
// {
//     while (!events.empty()) {
//         std::cout << "events.front().getType() = " << events.front().getType() << std::endl;
//         events.pop();
//     }
// }

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


template<typename T>
std::shared_ptr<T> loadComponent(const std::string& path, const std::string& creatorFunction, std::shared_ptr<state::Keybinds>& keybinds) {
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }

    dlerror();
    using CreatorFunc = T* (*)(std::shared_ptr<state::Keybinds>&);
    CreatorFunc create = (CreatorFunc)dlsym(handle, creatorFunction.c_str());

    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << dlsym_error << std::endl;
        dlclose(handle);
        return nullptr;
    }

    if (!create) {
        std::cerr << "Failed to load symbol" << std::endl;
        dlclose(handle);
        return nullptr;
    }

    std::shared_ptr<T> component(create(keybinds));
    return component;
}

void arcade::CoreProgram::loadGame(const std::string& game) {
    _game = loadComponent<game::AGame>(game, "createGame", _keys);
}

void arcade::CoreProgram::loadGraphic(const std::string& graphic) {
    _graphic = loadComponent<graphic::AGraphic>(graphic, "createGraphix", _keys);
}
int arcade::CoreProgram::loop()
{
    loadGame("lib/arcade_pacman.so");
    if (!_game || !_graphic) {
        std::cerr << "Failed to load game or graphic" << std::endl;
        return -1;
    }
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

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade path_to_graphic_lib" << std::endl;
        return 84;
    }
    arcade::CoreProgram core;
    core.loadGraphic(av[1]);
    if (core.loop() == -1)
        return 84;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
