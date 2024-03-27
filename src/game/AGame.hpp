/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-raphael.castres
** File description:
** AGame
*/

#ifndef AGAME_HPP_
    #define AGAME_HPP_

    #include "IGame.hpp"
    #include "../Keybinds.hpp"

namespace game {
    class AGame : public IGame {
        public:
            virtual ~AGame();
            virtual std::queue<state::Event> tick() = 0;

        private:
            state::Keybinds _keys;
            std::size_t _ticks;
    };
};

#endif /* !AGAME_HPP_ */
