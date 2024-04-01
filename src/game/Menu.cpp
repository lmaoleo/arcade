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

extern "C" {
    game::Menu *createGame(std::shared_ptr<state::Keybinds> &keybinds)
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

static void create_draw_string_event(std::queue<state::Event> &events, std::size_t x, std::size_t y, std::string score, bool selected = false)
{
    state::Event event;
    event.setEventType(state::EventType::DRAW_STRING);
    state::Event packetX = state::Event(state::EventType::DATA, x);
    state::Event packetY = state::Event(state::EventType::DATA, y);
    state::Event packetType = state::Event(state::EventType::DATA, score);
    state::Event packetselected = state::Event(state::EventType::DATA, selected);
    state::Event event2;
    event2.setEventType(state::EventType::DRAW_STRING);
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetType);
    events.push(packetselected);
    events.push(event2);
}

game::Menu::Menu(std::shared_ptr<state::Keybinds> &key)
{
    _keys = key;
    _lib_files = getFilesInDirectory("lib");
}

game::Menu::~Menu()
{
}

void game::Menu::display_menu(std::queue<state::Event> &events)
{
    create_draw_string_event(events, 0, 0, "Menu\n", true);
    for (std::size_t i = 0; i < _lib_files.size(); i++) {
        create_draw_string_event(events, 10, i * 4, _lib_files[i] + "\n");
    }
}

std::queue<state::Event> game::Menu::tick()
{
    std::queue<state::Event> events;
    display_menu(events);
    return events;
}
