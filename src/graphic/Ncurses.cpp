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
    initscr();
    noecho();
    curs_set(0);
    setlocale(LC_ALL, "");
    keypad(stdscr, TRUE);
    _keys.bindKey("UP", KEY_UP);
    _keys.bindKey("DOWN", KEY_DOWN);
    _keys.bindKey("LEFT", KEY_LEFT);
    _keys.bindKey("RIGHT", KEY_RIGHT);
    _keys.bindKey("ESC", 27);
}

void graphic::Ncurses::updateKeybinds()
{
    std::string action;
    int key = getch();
    if (key == KEY_UP)
        action = "UP";
        _keys.keyPressed(action, true);
    if (key == KEY_DOWN)
        action = "DOWN";
        _keys.keyPressed(action, true);
    if (key == KEY_LEFT)
        action = "LEFT";
        _keys.keyPressed(action, true);
    if (key == KEY_RIGHT)
        action = "RIGHT";
        _keys.keyPressed(action, true);
    if (key == 27)
        action = "ESC";
        _keys.keyPressed(action, true);
}

std::queue<state::Event> graphic::Ncurses::draw()
{

}
