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
        Ncurses(std::shared_ptr<state::Keybinds> &key);
        ~Ncurses();
        void updateKeybinds() final;
        std::queue<state::Event> draw() final;

    private:
        std::shared_ptr<state::Keybinds> _keys;
    };
};
