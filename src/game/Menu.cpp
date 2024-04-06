/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Menu
*/

#include <dirent.h>
#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>
#include "Menu.hpp"

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

extern "C" {
    game::Menu *createGame(std::shared_ptr<std::map<std::string, bool>> &keybinds)
    {
        return new game::Menu(keybinds);
    }
}

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

static void create_draw_string_event(std::queue<std::tuple<EventType, eventData>> &events, std::size_t x, std::size_t y, std::string score, bool selected = false)
{
    std::tuple<EventType, eventData> event = {EventType::DRAW_STRING, false};
    std::tuple<EventType, eventData> packetX = {EventType::DATA, x};
    std::tuple<EventType, eventData> packetY = {EventType::DATA, y};
    std::tuple<EventType, eventData> packetScore = {EventType::DATA, score};
    std::tuple<EventType, eventData> eventselect = {EventType::DATA, selected};
    std::tuple<EventType, eventData> event2 = {EventType::DRAW_STRING, false};
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetScore);
    events.push(eventselect);
    events.push(event2);
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

game::Menu::Menu(std::shared_ptr<std::map<std::string, bool>> &key)
{
    _keys = key;
    _lib_files = getFilesInDirectory("lib");
    _libs = order_libs(_lib_files);
    std::get<1>(_libs[0]) = true;
}

game::Menu::~Menu()
{
}

void game::Menu::selectNext(int type) {
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

void game::Menu::selectPrev(int type) {
    if (_libs.empty()) return;

    int currentIndex = -1;
    for (int i = 0; i < static_cast<int>(_libs.size()); i++) {
        if (std::get<2>(_libs[i]) == type && std::get<1>(_libs[i])) {
            std::get<1>(_libs[i]) = false; // Deselect it.
            currentIndex = i;
            break;
        }
    }

    if (currentIndex == -1) return;

    int libsSize = static_cast<int>(_libs.size());
    int startIndex = (currentIndex - 1 + libsSize) % libsSize;
    for (int i = startIndex; ; i = (i - 1 + libsSize) % libsSize) {
        if (i == currentIndex) break;

        if (std::get<2>(_libs[i]) == type) {
            std::get<1>(_libs[i]) = true;
            break;
        }

        if (i == (currentIndex - 1 + libsSize) % libsSize) break;
    }
}


void game::Menu::selectFirstGame()
{
    for (std::size_t i = 0; i < _libs.size(); i++) {
        if (std::get<1>(_libs[i]) == true) {
            std::get<1>(_libs[i]) = false;
            break;
        }
    }
    for (std::size_t i = 0; i < _libs.size(); i++) {
        if (std::get<2>(_libs[i]) == 0) {
            std::get<1>(_libs[i]) = true;
            break;
        }
    }
}

void game::Menu::selectFirstGraphic()
{
    for (std::size_t i = 0; i < _libs.size(); i++) {
        if (std::get<1>(_libs[i]) == true) {
            std::get<1>(_libs[i]) = false;
            break;
        }
    }
    for (std::size_t i = 0; i < _libs.size(); i++) {
        if (std::get<2>(_libs[i]) == 1) {
            std::get<1>(_libs[i]) = true;
            break;
        }
    }
}

void game::Menu::send_packet(int type, std::vector<std::tuple<std::string, bool, int>> &libs, std::queue<std::tuple<EventType, eventData>> &events)
{
    EventType to_send = EventType::SET_GRAPHIC;
    if (type == 1) {
        to_send = EventType::SET_GAME;
    }
    for (std::size_t i = 0; i < libs.size(); i++) {
        if (std::get<1>(libs[i]) == true && std::get<2>(libs[i]) == type) {
            std::tuple<EventType, eventData> event = {to_send, false};
            std::tuple<EventType, eventData> packet = {EventType::DATA, "lib/" + std::get<0>(libs[i])};
            std::tuple<EventType, eventData> event2 = {to_send, false};
            events.push(event);
            events.push(packet);
            events.push(event2);
        }
    }
}

void game::Menu::handle_key_events(std::queue<std::tuple<EventType, eventData>> &events)
{
    if (_keys->at("UP") == true) {
        selectPrev(_typeSelected);
    }
    if (_keys->at("DOWN") == true) {
        selectNext(_typeSelected);
    }
    if (_keys->at("LEFT") == true) {
        selectFirstGraphic();
        _typeSelected = 1;
    }
    if (_keys->at("RIGHT") == true) {
        selectFirstGame();
        _typeSelected = 0;
    }
    if (_keys->at("ENTER") == true) {
        send_packet(_typeSelected, _libs, events);
        _typeSelected = 0;
    }
    if (_keys->at("ESC") == true) {
        exit(0);
    }
    _keys->at("UP") = false;
    _keys->at("DOWN") = false;
    _keys->at("LEFT") = false;
    _keys->at("RIGHT") = false;
    _keys->at("ESC") = false;
    _keys->at("ENTER") = false;
}

void game::Menu::display_menu(std::queue<std::tuple<EventType, eventData>> &events)
{
    create_draw_string_event(events, 0, 0, "Menu", false);
    create_draw_string_event(events, 12, 0, "To select top of game press '>'", false);
    create_draw_string_event(events, 12, 1, "To select top of graphic press '<'", false);
    create_draw_string_event(events, 12, 2, "To select next press 'V'", false);
    create_draw_string_event(events, 12, 3, "In the games to move the keybinds are:", false);
    create_draw_string_event(events, 12, 4, "UP: '^'", false);
    create_draw_string_event(events, 12, 5, "DOWN: 'V'", false);
    create_draw_string_event(events, 12, 6, "LEFT: '<'", false);
    create_draw_string_event(events, 12, 7, "RIGHT: '>'", false);
    create_draw_string_event(events, 12, 8, "L: change lib graphique", false);
    create_draw_string_event(events, 12, 9, "G: change lib game", false);
    create_draw_string_event(events, 12, 10, "ESC: exit/menu", false);

    create_draw_string_event(events, 10, 12, "Games", false);
    create_draw_string_event(events, 30, 12, "Graphics", false);
    int i_games = 1;
    int i_graphics = 1;

    for (std::size_t i = 0; i < _libs.size(); i++) {
        if (std::get<2>(_libs[i]) == 1) {
            create_draw_string_event(events, 10, 12 + i_games, std::get<0>(_libs[i]), std::get<1>(_libs[i]));
            i_games++;
        } else {
            create_draw_string_event(events, 30, 12 + i_graphics, std::get<0>(_libs[i]), std::get<1>(_libs[i]));
            i_graphics++;
        }
    }
}

std::queue<std::tuple<EventType, eventData>> game::Menu::tick()
{
    std::queue<std::tuple<EventType, eventData>> events;
    handle_key_events(events);
    display_menu(events);
    return events;
}
