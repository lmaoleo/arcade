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
    game::Menu *createGame(std::shared_ptr<std::map<std::string, bool>> &keybinds, int &score, std::string &username)
    {
        return new game::Menu(keybinds, score, username);
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

game::Menu::Menu(std::shared_ptr<std::map<std::string, bool>> &key, int &score, std::string &username) : _user_input_text(username) , _iscore(score)
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
            std::get<1>(_libs[i]) = false;
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
        if (_user_input == false) {
            send_packet(_typeSelected, _libs, events);
            _typeSelected = 0;
        }
    }
    if (_keys->at("TAB") == true) {
        _user_input = !_user_input;
    }
    if (_user_input == true) {
        if (_keys->at("A") == true) {
            _user_input_text += "A";
        }
        if (_keys->at("B") == true) {
            _user_input_text += "B";
        }
        if (_keys->at("C") == true) {
            _user_input_text += "C";
        }
        if (_keys->at("D") == true) {
            _user_input_text += "D";
        }
        if (_keys->at("E") == true) {
            _user_input_text += "E";
        }
        if (_keys->at("F") == true) {
            _user_input_text += "F";
        }
        if (_keys->at("G") == true) {
            _user_input_text += "G";
        }
        if (_keys->at("H") == true) {
            _user_input_text += "H";
        }
        if (_keys->at("I") == true) {
            _user_input_text += "I";
        }
        if (_keys->at("J") == true) {
            _user_input_text += "J";
        }
        if (_keys->at("K") == true) {
            _user_input_text += "K";
        }
        if (_keys->at("L") == true) {
            _user_input_text += "L";
        }
        if (_keys->at("M") == true) {
            _user_input_text += "M";
        }
        if (_keys->at("N") == true) {
            _user_input_text += "N";
        }
        if (_keys->at("O") == true) {
            _user_input_text += "O";
        }
        if (_keys->at("P") == true) {
            _user_input_text += "P";
        }
        if (_keys->at("Q") == true) {
            _user_input_text += "Q";
        }
        if (_keys->at("R") == true) {
            _user_input_text += "R";
        }
        if (_keys->at("S") == true) {
            _user_input_text += "S";
        }
        if (_keys->at("T") == true) {
            _user_input_text += "T";
        }
        if (_keys->at("U") == true) {
            _user_input_text += "U";
        }
        if (_keys->at("V") == true) {
            _user_input_text += "V";
        }
        if (_keys->at("W") == true) {
            _user_input_text += "W";
        }
        if (_keys->at("X") == true) {
            _user_input_text += "X";
        }
        if (_keys->at("Y") == true) {
            _user_input_text += "Y";
        }
        if (_keys->at("Z") == true) {
            _user_input_text += "Z";
        }
        if (_keys->at("SPACE") == true) {
            _user_input_text += " ";
        }
        if (_keys->at("BACKSPACE") == true) {
            if (_user_input_text.size() > 0) {
                _user_input_text.pop_back();
            }
        }
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
    std::string to_print = "";
    if (_user_input_text == "") {
        to_print = "No name";
    } else {
        to_print = _user_input_text;
    }
    create_draw_string_event(events, 0, 0, "Menu", false);
    create_draw_string_event(events, 0, 1, "Select a game and a graphic", false);
    create_draw_string_event(events, 0, 2, "Press 'TAB' to enter a name", false);
    create_draw_string_event(events, 0, 3, "NAME:", _user_input);
    create_draw_string_event(events, 0, 4, to_print, _user_input);
    create_draw_string_event(events, 0, 5, "Last score: " + std::to_string(_iscore), false);
    create_draw_string_event(events, 20, 0, "To select top of game press '>'", false);
    create_draw_string_event(events, 20, 1, "To select top of graphic press '<'", false);
    create_draw_string_event(events, 20, 2, "To select next press 'V'", false);
    create_draw_string_event(events, 20, 3, "In the games to move the keybinds are:", false);
    create_draw_string_event(events, 20, 4, "UP: '^'", false);
    create_draw_string_event(events, 20, 5, "DOWN: 'V'", false);
    create_draw_string_event(events, 20, 6, "LEFT: '<'", false);
    create_draw_string_event(events, 20, 7, "RIGHT: '>'", false);
    create_draw_string_event(events, 20, 8, "F3: change lib graphique", false);
    create_draw_string_event(events, 20, 9, "F2: change lib game", false);
    create_draw_string_event(events, 20, 10, "ESC: exit", false);
    create_draw_string_event(events, 20, 11, "R: reload game", false);

    create_draw_string_event(events, 10, 13, "Games", false);
    create_draw_string_event(events, 30, 13, "Graphics", false);
    int i_games = 1;
    int i_graphics = 1;

    for (std::size_t i = 0; i < _libs.size(); i++) {
        if (std::get<2>(_libs[i]) == 1) {
            create_draw_string_event(events, 10, 13 + i_games, std::get<0>(_libs[i]), std::get<1>(_libs[i]));
            i_games++;
        } else {
            create_draw_string_event(events, 30, 13 + i_graphics, std::get<0>(_libs[i]), std::get<1>(_libs[i]));
            i_graphics++;
        }
    }
}

std::queue<std::tuple<EventType, eventData>> game::Menu::tick(double delta)
{
    _moveTime += delta;

    _events = std::queue<std::tuple<EventType, eventData>>();

    handle_key_events(_events);
    display_menu(_events);
    return _events;
}
