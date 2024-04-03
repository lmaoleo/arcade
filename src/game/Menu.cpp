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
#include "Menu.hpp"

static const std::vector<std::string> lib_files = {
    "lib_arcade_ncurses.so",
    "lib_arcade_sfml.so",
    "lib_arcade_sdl.so"
    };

static const std::vector<std::string> game_files = {
    "lib_arcade_nibbler.so",
    "lib_arcade_pacman.so",
    "lib_arcade_qix.so"
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
    std::tuple<EventType, eventData> event = {EventType::DRAW, nullptr};
    std::tuple<EventType, eventData> packetX = {EventType::DATA, x};
    std::tuple<EventType, eventData> packetY = {EventType::DATA, y};
    std::tuple<EventType, eventData> packetScore = {EventType::DATA, score};
    std::tuple<EventType, eventData> eventselect = {EventType::DATA, false};
    std::tuple<EventType, eventData> event2 = {EventType::DRAW, selected};
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetScore);
    events.push(eventselect);
    events.push(event2);
}

game::Menu::Menu(std::shared_ptr<std::map<std::string, bool>> &key)
{
    _keys = key;
    _lib_files = getFilesInDirectory("lib");
}

game::Menu::~Menu()
{
}

void game::Menu::handle_key_events(std::queue<std::tuple<EventType, eventData>> &events)
{
    if (_keys->at("UP") == true) {
    }
    if (_keys->at("DOWN") == true) {
    }
    if (_keys->at("LEFT") == true) {
    }
}

void game::Menu::display_menu(std::queue<std::tuple<EventType, eventData>> &events)
{
    create_draw_string_event(events, 0, 0, "Menu\n", true);
    for (std::size_t i = 0; i < _lib_files.size(); i++) {
        create_draw_string_event(events, 10, i * 4, _lib_files[i] + "\n");
    }
}

std::queue<std::tuple<EventType, eventData>> game::Menu::tick()
{
    std::queue<std::tuple<EventType, eventData>> events;
    display_menu(events);
    return events;
}
