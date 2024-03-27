/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include <ncurses.h>
#include "Ncurses.hpp"

graphic::Ncurses::Ncurses()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    _keys.bindKey("UP", KEY_UP);
    _keys.bindKey("DOWN", KEY_DOWN);
    _keys.bindKey("LEFT", KEY_LEFT);
    _keys.bindKey("RIGHT", KEY_RIGHT);
    _keys.bindKey("ESC", 27);
}

void graphic::Ncurses::updateKeybinds()
{
    int key = getch();
    
}

std::queue<state::Event> graphic::Ncurses::draw()
{

}
