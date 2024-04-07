/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#pragma once


#include <ncurses.h>
#include <wchar.h>
#include <locale.h>
#include "AGraphic.hpp"

namespace graphic {
    class Ncurses : public graphic::AGraphic {
    public:
        Ncurses(std::shared_ptr<std::map<std::string, bool>> &key);
        ~Ncurses();
        void updateKeybinds() final;
        std::queue<std::tuple<EventType, eventData>> draw() final;

        void initialiseAllColors();
        std::tuple<short, short, short, short> intToRgb(unsigned int color);
        void printPixel(std::size_t x, std::size_t y, int color);
        void printTile(std::size_t gx, std::size_t gy, short pattern, int color);
        void createNewColor(unsigned int color, int i);

    private:
        std::shared_ptr<std::map<std::string, bool>> _keys;
    };
};
