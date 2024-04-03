/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"


static const std::map<std::string, wchar_t> charmap = {
    {"wall", L'🧱'},
    {"snake_head_down", L'🦯'},
    {"snake_head_up", L'🦺'},
    {"snake_head_left", L'🕺'},
    {"snake_head_right", L'💃'},
    {"snake_body", L'🟩'},
    {"horizontal_snake_body", L'🟩'},
    {"vertical_snake_body", L'🟩'},
    {"angle_left_down_snake_body", L'🟩'},
    {"angle_right_down_snake_body", L'🟩'},
    {"angle_left_up_snake_body", L'🟩'},
    {"angle_right_up_snake_body", L'🟩'},
    {"snake_tail_down", L'🟩'},
    {"snake_tail_up", L'🟩'},
    {"snake_tail_left", L'🟩'},
    {"snake_tail_right", L'🟩'},
    {"food", L'🍔'},
    {"pac_wall", L'🧱'},
    {"pac_down", L'👇'},
    {"pac_up", L'👆'},
    {"pac_left", L'👈'},
    {"pac_right", L'👉'},
    {"ghost", L'👻'},
    {"pac_food", L'🍔'},
    {"empty", L' '},
};

extern "C" {
    graphic::Ncurses *createGraphic(std::shared_ptr<std::map<std::string, bool>> &keybinds)
    {
        return new graphic::Ncurses(keybinds);
    }
};

graphic::Ncurses::Ncurses(std::shared_ptr<std::map<std::string, bool>> &key)
{
    std::string action;
    _keys = key;
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    setlocale(LC_ALL, "");
    keypad(stdscr, TRUE);
}

graphic::Ncurses::~Ncurses()
{
    endwin();
}

void graphic::Ncurses::updateKeybinds()
{
    int key = getch();

    _keys->at("UP") = false;
    _keys->at("DOWN") = false;
    _keys->at("LEFT") = false;
    _keys->at("RIGHT") = false;
    if (key == KEY_UP) {
        if (_keys->find("UP") != _keys->end())
            _keys->at("UP") = true;
    } else if (key == KEY_DOWN) {
        if (_keys->find("DOWN") != _keys->end())
            _keys->at("DOWN") = true;
    } else if (key == KEY_LEFT) {
        if (_keys->find("LEFT") != _keys->end())
            _keys->at("LEFT") = true;
    } else if (key == KEY_RIGHT) {
        if (_keys->find("RIGHT") != _keys->end())
                _keys->at("RIGHT") = true;
    } else if (key == 27) {
        if (_keys->find("ESC") != _keys->end())
            _keys->at("ESC") = true;
    }
}

std::queue<std::tuple<EventType, eventData>> graphic::Ncurses::draw() {
    clear();

    for (const auto& item : _draw) {
    std::size_t x, y;
    std::string type;
    std::tie(x, y, type) = item;

    auto charIt = charmap.find(type);
    if (charIt != charmap.end()) {
        wchar_t symbol = charIt->second;
        if (type == "empty") {
            attron(COLOR_PAIR(1));
            mvaddch(y, x * 2, ' ');
            mvaddch(y, x * 2 + 1, ' ');
            attroff(COLOR_PAIR(1));
        } else {
            mvaddwstr(y, x * 2, &symbol);
        }
    }
}
    for (const auto& item : _draw_str) {
        std::size_t x, y;
        std::string str;
        bool selected;
        std::tie(x, y, str, selected) = item;

        if (selected) {
            attron(A_REVERSE);
            mvprintw(y, x, str.c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(y, x, str.c_str());
        }
    }

    refresh();
    _draw.clear();
    return std::queue<std::tuple<EventType, eventData>>();
}
