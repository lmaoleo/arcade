/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"


static const std::map<std::string, wchar_t> charmap = {
    {"wall", L'🛑'},
    {"snake_head_down", L'🦯'},
    {"snake_head_up", L'🦺'},
    {"snake_head_left", L'🕺'},
    {"snake_head_right", L'💃'},
    {"snake_body", L'🟩'},
    {"food", L'🍔'},
    {"empty", L'🧱'},
};

extern "C" {
    graphic::Ncurses *createGraphix(std::shared_ptr<state::Keybinds> &keybinds)
    {
        return new graphic::Ncurses(keybinds);
    }
};

graphic::Ncurses::Ncurses(std::shared_ptr<state::Keybinds> &key)
{
    std::string action;
    _keys = key;
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    setlocale(LC_ALL, "");
    keypad(stdscr, TRUE);
    action = "UP";
    _keys.get()->bindKey(action, KEY_UP);
    action = "DOWN";
    _keys.get()->bindKey(action, KEY_DOWN);
    action = "LEFT";
    _keys.get()->bindKey(action, KEY_LEFT);
    action = "RIGHT";
    _keys.get()->bindKey(action, KEY_RIGHT);
    action = "ESC";
    _keys.get()->bindKey(action, 27);
}

graphic::Ncurses::~Ncurses()
{
    endwin();
}

void graphic::Ncurses::updateKeybinds()
{
    int key = getch();

    if (key == KEY_UP) {
        _keys->keyPressed("UP", true);
    } else if (key == KEY_DOWN) {
        _keys->keyPressed("DOWN", true);
    } else if (key == KEY_LEFT) {
        _keys->keyPressed("LEFT", true);
    } else if (key == KEY_RIGHT) {
        _keys->keyPressed("RIGHT", true);
    } else if (key == 27) {
        _keys->keyPressed("ESC", true);
    }
    if (key == ERR) {
        _keys->keyPressed("UP", false);
        _keys->keyPressed("DOWN", false);
        _keys->keyPressed("LEFT", false);
        _keys->keyPressed("RIGHT", false);
        _keys->keyPressed("ESC", false);
    }
}

std::queue<state::Event> graphic::Ncurses::draw(std::queue<state::Event> &event) {
    clear();

    readEvent(event);
    for (const auto& item : _draw) {
        std::size_t x, y;
        std::string type;
        std::tie(x, y, type) = item;

        auto charIt = charmap.find(type);
        if (charIt != charmap.end()) {
            wchar_t symbol = charIt->second;
            mvaddwstr(y, x, &symbol);
        } else {
            wprintw(stdscr, "Score: %s", type.c_str());
        }
    }

    refresh();
    _draw.clear();
    event = std::queue<state::Event>();
    return event;
}
