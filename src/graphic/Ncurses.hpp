/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "AGraphic.hpp"

namespace graphic {
    class Ncurses : public graphic::AGraphic {
    public:
        void updateKeybinds() final;
        std::queue<state::Event> draw() final;
    };
}; 


#endif /* !NCURSES_HPP_ */
