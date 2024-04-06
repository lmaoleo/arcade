/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

std::map<int, std::string> _keyMap;

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
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    keypad(stdscr, TRUE);
    _keyMap = {
            {KEY_UP, "UP"}, {KEY_DOWN, "DOWN"}, {KEY_LEFT, "LEFT"}, {KEY_RIGHT, "RIGHT"},
            {27, "ESC"}, {10, "ENTER"}, {32, "SPACE"},
            {97, "A"}, {122, "Z"}, {101, "E"}, {114, "R"},
            {116, "T"}, {121, "Y"}, {117, "U"}, {105, "I"},
            {111, "O"}, {112, "P"}, {113, "Q"}, {115, "S"},
            {100, "D"}, {102, "F"}, {KEY_BTAB, "TAB"}
            // Add more mappings as needed
    };
}

graphic::Ncurses::~Ncurses()
{
    endwin();
}

void graphic::Ncurses::updateKeybinds()
{
    int key = getch();

    for (auto& key : *_keys) {
            key.second = false;
    }

    auto it = _keyMap.find(key);
    if (it != _keyMap.end()) {
        if (_keys->find(it->second) != _keys->end()) {
            _keys->at(it->second) = true;
        }
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

    int nc_r = r * 1000 / 255;
    int nc_g = g * 1000 / 255;
    int nc_b = b * 1000 / 255;

    init_color(8 + i, nc_r, nc_g, nc_b);
}

std::queue<std::tuple<EventType, eventData>> graphic::Ncurses::draw() {
    int color = 0;
    erase();
    for (const auto& item : _draw) {
        std::size_t x, y;
        short pixel;
        unsigned int colora;
        std::tie(x, y, pixel, colora) = item;
        createNewColor(colora, color);
        init_pair(color + 1, 8 + color, COLOR_BLACK);
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
    _draw_str.clear();
    return std::queue<std::tuple<EventType, eventData>>();
}

std::tuple<short, short, short, short> graphic::Ncurses::intToRgb(unsigned int color)
{
    short a = (color >> 24) & 0xFF; // Correctly masks the alpha component
    short r = (color >> 16) & 0xFF; // Correctly masks the red component
    short g = (color >> 8) & 0xFF;  // Correctly masks the green component
    short b = color & 0xFF;         // Correctly masks the blue component

    return std::make_tuple(a, r, g, b);
}

void graphic::Ncurses::printPixel(std::size_t x, std::size_t y, int color)
{
    attron(COLOR_PAIR(color + 1));
    mvprintw(y, x, "■");
    attroff(COLOR_PAIR(color + 1));
}

void graphic::Ncurses::printTile(std::size_t gx, std::size_t gy, short pattern, int color)
{
    int sx = gx * 4;
    int sy = gy * 4;
    for (int i = 0; i < 16; i++) {
        if (pattern & (1 << i)) {
            printPixel(sx + i % 4, sy + i / 4, color);
        }
    }
}
