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

static const std::map<std::string, bool> keys = {
        {"UP", false},
        {"DOWN", false},
        {"LEFT", false},
        {"RIGHT", false},
        {"SPACE", false},
        {"ENTER", false},
        {"ESC", false},
        {"A", false},
        {"Z", false},
        {"E", false},
        {"R", false},
        {"T", false},
        {"Y", false},
        {"U", false},
        {"I", false},
        {"O", false},
        {"P", false},
        {"Q", false},
        {"S", false},
        {"D", false},
        {"F", false},
        {"G", false},
        {"H", false},
        {"J", false},
        {"K", false},
        {"L", false},
        {"M", false},
        {"W", false},
        {"X", false},
        {"C", false},
        {"V", false},
        {"B", false},
        {"N", false}
    };

arcade::CoreProgram::CoreProgram()
{
    _score = 0;
    _keys = std::make_shared<std::map<std::string, bool>>(keys);
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
std::shared_ptr<T> loadComponent(const std::string& path, const std::string& creatorFunction, std::shared_ptr<std::map<std::string, bool>>& keybinds) {
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }

    dlerror();
    using CreatorFunc = T* (*)(std::shared_ptr<std::map<std::string, bool>>&);
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
    if (_game != nullptr) {
        _game.reset();
    }
    _game = loadComponent<game::AGame>(game, "createGame", _keys);
}

void arcade::CoreProgram::loadGraphic(const std::string& graphic) {
    if (_graphic != nullptr) {
        _graphic.reset();
    }
    _graphic = loadComponent<graphic::AGraphic>(graphic, "createGraphic", _keys);
}

void arcade::CoreProgram::loadMenu()
{
    _game = loadComponent<game::AGame>("lib/arcade_menu.so", "createGame", _keys);
}

bool arcade::CoreProgram::checkForEventChangeThing(std::queue<std::tuple<EventType, eventData>> events)
{
    while (!events.empty()) {
        if (std::get<EventType>(events.front()) == EventType::SET_GRAPHIC) {
            events.pop();
            loadGame(std::get<std::string>(std::get<1>(events.front())));
            _events = _game->tick();
            _graphic->flushscreen();
            return true;
        } else if (std::get<EventType>(events.front()) == EventType::SET_GAME) {
            events.pop();
            loadGraphic(std::get<std::string>(std::get<1>(events.front())));
            _events = _game->tick();
            _graphic->flushscreen();
            return true;
        }
        events.pop();
    }
    return false;
}

int arcade::CoreProgram::loop()
{
    loadGame("lib/arcade_snake.so");
    if (!_game || !_graphic) {
        std::cerr << "Failed to load game or graphic" << std::endl;
        return -1;
    }

    using clock = std::chrono::steady_clock;
    std::chrono::milliseconds timestep(1000 / 8);
    auto next_tick = clock::now() + timestep;

    while (1) {
        _graphic->updateKeybinds();
        _events = _game->tick();
        if (!checkForEventChangeThing(_events)) {
            _graphic->readEvent(_events);
            _events = _graphic->draw();
        }
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
