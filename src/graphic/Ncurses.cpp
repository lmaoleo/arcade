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
    setlocale(LC_ALL, "");
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

void graphic::Ncurses::createNewColor(unsigned int color, int i)
{
    short a, r, g, b;
    std::tie(a, r, g, b) = intToRgb(color);

    init_color(8 + i, r, g, b);
}

std::queue<std::tuple<EventType, eventData>> graphic::Ncurses::draw() {
    int color = 0;
    clear();
    for (const auto& item : _draw) {
        std::size_t x, y;
        short pixel;
        unsigned int colora;
        std::tie(x, y, pixel, colora) = item;

        printTile(x, y, pixel, color);
        color++;
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

std::tuple<short, short, short, short> graphic::Ncurses::intToRgb(unsigned int color)
{
    short a = (color >> 24) & 0;
    short r = (color >> 16) & 0;
    short g = (color >> 8) & 0;
    short b = color & 0;

    return std::make_tuple(a, r, g, b);
}

void graphic::Ncurses::printPixel(std::size_t x, std::size_t y, unsigned int color)
{
    mvprintw(y, x, "#");
}

void graphic::Ncurses::printTile(std::size_t gx, std::size_t gy, short pattern, int color)
{
    int sx = gx * 4;
    int sy = gy * 4;
    for (int i = 0; i < 16; i++) {
        if (pattern & (1 << i)) {
            std::cout << "x: " << sx + i % 4 << " y: " << sy + i / 4 << std::endl;
            printPixel(sx + i % 4, sy + i / 4, color);
        }
    }
}
