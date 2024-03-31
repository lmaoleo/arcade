/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "AGame.hpp"
#include <queue>

namespace game {
    class Pacman : public AGame {
        public:
            Pacman(std::shared_ptr<state::Keybinds> &key);
            ~Pacman();
            std::queue<state::Event> tick();
            std::vector<std::tuple<std::size_t, std::size_t>> changePacmanPos();
            void add_food_to_events(std::queue<state::Event> &events);
            void add_Pacman_to_events(std::queue<state::Event> &event);
            void changeDirection();
            bool checkCollision();
            void checkFood();
            void generateFood();
            std::queue<state::Event> transform_map_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<state::Keybinds> _keys;
            std::size_t _ticks;
            std::size_t _score;
            std::tuple<std::size_t, std::size_t> _lastTailPos;
            std::tuple<std::size_t, std::size_t> _direction;
            std::string _headDirection;
            std::vector<std::tuple<std::size_t, std::size_t>> _Pacman;
            std::tuple<std::size_t, std::size_t> _food;
    };
};

#endif /* !Pacman_HPP_ */
