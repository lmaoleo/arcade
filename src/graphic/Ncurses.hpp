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
        void flushscreen() final;
        std::queue<std::tuple<EventType, eventData>> draw() final;

    private:
        std::shared_ptr<std::map<std::string, bool>> _keys;
    };
};
