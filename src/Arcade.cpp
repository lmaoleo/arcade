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
#include <iostream>
#include <dirent.h>
#include <algorithm>

static const std::map<std::string, bool> keys = {
        {"UP", false},
        {"DOWN", false},
        {"LEFT", false},
        {"RIGHT", false},
        {"SPACE", false},
        {"ENTER", false},
        {"ESC", false},
        {"TAB", false},
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

static const std::vector<std::string> lib_files = {
    "arcade_ncurses.so",
    "arcade_sfml.so",
    "arcade_sdl2.so",
    "arcade_allegro.so",
    "arcade_libcaca.so",
    "arcade_opengl.so"
    };

static const std::vector<std::string> game_files = {
    "arcade_nibbler.so",
    "arcade_pacman.so",
    "arcade_snake.so",
    "arcade_centipede.so",
    "arcade_solarfox.so",
    "arcade_qix.so"
    };

std::vector<std::string> getFilesInDirectory(const std::string &directory)
{
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] != '.')
                files.push_back(ent->d_name);
        }
        closedir(dir);
    } else {
        perror("");
    }
    return files;
}

std::vector<std::tuple<std::string, bool, int>> order_libs(std::vector<std::string> &libs)
{
    std::vector<std::tuple<std::string, bool, int>> ordered_libs;
    for (std::size_t i = 0; i < libs.size(); i++) {
        if (std::find(lib_files.begin(), lib_files.end(), libs[i]) != lib_files.end()) {
            ordered_libs.push_back({libs[i], false, 0});
        } else if (std::find(game_files.begin(), game_files.end(), libs[i]) != game_files.end()) {
            ordered_libs.push_back({libs[i], false, 1});
        }
    }
    return ordered_libs;
}

arcade::CoreProgram::CoreProgram()
{
    _score = 0;
    _keys = std::make_shared<std::map<std::string, bool>>(keys);
    _game = nullptr;
    _graphic = nullptr;
    _lib_files = getFilesInDirectory("lib");
    _libs = order_libs(_lib_files);
}

arcade::CoreProgram::~CoreProgram()
{
}

void printLibs(std::vector<std::tuple<std::string, bool, int>> &libs)
{
    std::string selected;

    for (auto &lib : libs) {
        if (std::get<1>(lib)) {
            selected = "true";
        } else {
            selected = "false";
        }
        std::cout << std::get<0>(lib) << " " << selected << " " << std::get<2>(lib) << std::endl;
    }
}

void arcade::CoreProgram::selectNext(int type) {
    if (_libs.empty()) return;

    int currentIndex = -1;
    for (int i = 0; i < static_cast<int>(_libs.size()); i++) {
        if (std::get<2>(_libs[i]) == type && std::get<1>(_libs[i])) {
            std::get<1>(_libs[i]) = false;
            currentIndex = i;
            break;
        }
    }

    if (currentIndex == -1) return;

    int startIndex = (currentIndex + 1) % _libs.size();
    for (int i = startIndex; ; i = (i + 1) % _libs.size()) {
        if (i == currentIndex) break;

        if (std::get<2>(_libs[i]) == type) {
            std::get<1>(_libs[i]) = true;
            break;
        }
    }
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

    for (auto &lib : _libs) {
        if (std::get<2>(lib) == 1) {
            std::get<1>(lib) = false;
        }
        if (".lib/" + std::get<0>(lib) == game) {
            std::get<1>(lib) = true;
        }
    }
}

void arcade::CoreProgram::loadGraphic(const std::string& graphic) {
    if (_graphic != nullptr) {
        _graphic.reset();
    }

    _graphic = loadComponent<graphic::AGraphic>(graphic, "createGraphic", _keys);

    for (auto &lib : _libs) {
        if (std::get<2>(lib) == 0) {
            std::get<1>(lib) = false;
        }
        if (".lib/" + std::get<0>(lib) == graphic) {
            std::get<1>(lib) = true;
        }
    }
}

void arcade::CoreProgram::loadMenu()
{
    _game = loadComponent<game::AGame>(".lib/arcade_menu.so", "createGame", _keys);
}

bool arcade::CoreProgram::checkForEventChangeThing(std::queue<std::tuple<EventType, eventData>> events)
{
    while (!events.empty()) {
        if (std::get<EventType>(events.front()) == EventType::SET_GAME) {
            events.pop();
            if (std::get<std::string>(std::get<1>(events.front())) == "next") {
                selectNext(1);
                for (auto &lib : _libs) {
                    if (std::get<1>(lib) && std::get<2>(lib) == 1) {
                        loadGame(".lib/" + std::get<std::string>(lib));
                        return true;
                    }
                }
            } else {
                loadGame(std::get<std::string>(std::get<1>(events.front())));
                return true;
            }
        } else if (std::get<EventType>(events.front()) == EventType::SET_GRAPHIC) {
            events.pop();
            if (std::get<std::string>(std::get<1>(events.front())) == "next") {
                selectNext(0);
                for (auto &lib : _libs) {
                    if (std::get<1>(lib) && std::get<2>(lib) == 0) {
                        loadGraphic(".lib/" + std::get<std::string>(lib));
                        return true;
                    }
                }
            } else {
                loadGraphic(std::get<std::string>(std::get<1>(events.front())));
                return true;
            }
            return true;
        }
        events.pop();
    }
    return false;
}

int arcade::CoreProgram::loop()
{
    loadGame(".lib/arcade_menu.so");
    if (!_game || !_graphic) {
        std::cerr << "Failed to load game or graphic" << std::endl;
        return -1;
    }
    clock_t cl = std::clock();

    while (1) {
        _graphic->updateKeybinds();
        _events = _game->tick(static_cast<double>(std::clock() - cl) / CLOCKS_PER_SEC * 10);
        cl = std::clock();
        if (!checkForEventChangeThing(_events)) {
            _graphic->readEvent(_events);
            _events = _graphic->draw();
        }
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
    return 0;
}
