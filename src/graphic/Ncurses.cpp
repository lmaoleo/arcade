/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include <ncurses.h>
#include <wchar.h>
#include <locale.h>
#include "Ncurses.hpp"

static const std::map<std::string, wchar_t> charmap = {
    {"wall", L'🧱'},
    {"snake_head_down", L'🐍'},
    {"snake_head_up", L'🐍'},
    {"snake_head_left", L'🐍'},
    {"snake_head_right", L'🐍'},
    {"snake_body", L'🟩'},
    {"food", L'🍔'},
    {"empty", L' '},
};

graphic::Ncurses::Ncurses()
{
    std::string action;

    initscr();
    noecho();
    curs_set(0);
    setlocale(LC_ALL, "");
    keypad(stdscr, TRUE);
    action = "UP";
    _keys.bindKey(action, KEY_UP);
    action = "DOWN";
    _keys.bindKey(action, KEY_DOWN);
    action = "LEFT";
    _keys.bindKey(action, KEY_LEFT);
    action = "RIGHT";
    _keys.bindKey(action, KEY_RIGHT);
    action = "ESC";
    _keys.bindKey(action, 27);
}

graphic::Ncurses::~Ncurses()
{
    endwin();
}

void graphic::Ncurses::updateKeybinds()
{
    std::string action;
    int key = getch();

    if (key == KEY_UP) {
        action = "UP";
        _keys.keyPressed(action, true);
    }
    if (key == KEY_DOWN) {
        action = "DOWN";
        _keys.keyPressed(action, true);
    }
    if (key == KEY_LEFT) {
        action = "LEFT";
        _keys.keyPressed(action, true);
    }
    if (key == KEY_RIGHT) {
        action = "RIGHT";
        _keys.keyPressed(action, true);
    }
    if (key == 27) {
        action = "ESC";
        _keys.keyPressed(action, true);
    }
}

std::queue<state::Event> graphic::Ncurses::draw() {
    clear();

    for (const auto& item : _draw) {
        std::size_t x, y;
        std::string type;
        std::tie(x, y, type) = item;

        auto charIt = charmap.find(type);
        if (charIt != charmap.end()) {
            wchar_t symbol = charIt->second;
            mvaddwstr(y, x, &symbol);
        }
    }

    refresh();
    _draw.clear();
    return std::queue<state::Event>();
}
