/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

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
    _keys->at("ESC") = false;
    _keys->at("ENTER") = false;
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
    } else if (key == 10) {
        if (_keys->find("ENTER") != _keys->end())
            _keys->at("ENTER") = true;
    }
}

void graphic::Ncurses::flushscreen()
{
    clear();
    refresh();
}

std::queue<std::tuple<EventType, eventData>> graphic::Ncurses::draw() {
    clear();

    for (const auto& item : _draw) {
        std::size_t x, y;
        short pixel;
        unsigned int color;
        std::tie(x, y, pixel, color) = item;

        printCube(x, y, pixel, color);
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

static void printPixel(std::size_t x, std::size_t y, unsigned int color)
{
    attron(COLOR_PAIR(color));
    mvprintw(y, x, " ");
    attroff(COLOR_PAIR(color));
}

static void printCube(std::size_t gx, std::size_t gy, short pattern, unsigned int color)
{
    // gx and gy are the grid coordinates, sx and sy are the screen (normal) coordinates
    int sx = gx * 4;
    int sy = gy * 4;
    // Grid is 4x4 so 16 characters
    for (int i = 0; i < 16; i++) {
        if (pattern & (1 << i)) {
            printPixel(sx + i % 4, sy + i / 4, color);
        }
    }
}
