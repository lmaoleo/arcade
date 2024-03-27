/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#pragma once

#include "AGraphic.hpp"

namespace graphic {
    class Ncurses : public graphic::AGraphic {
    public:
        Ncurses();
        ~Ncurses();
        void updateKeybinds() final;
        std::queue<state::Event> draw() final;
    };
}; 
