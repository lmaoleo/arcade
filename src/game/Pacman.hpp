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
    class Ghost {
        public:
            Ghost(std::size_t x, std::size_t y);
            ~Ghost();
            std::tuple<std::size_t, std::size_t> getPos();
            void setPos(std::size_t x, std::size_t y);
            void move();
        private:
            std::tuple<std::size_t, std::size_t> _pos;
    };
    class Pacman : public AGame {
        public:
            Pacman(std::shared_ptr<state::Keybinds> &key);
            ~Pacman();
            std::queue<state::Event> tick();
            void changePacmanPos();
            std::vector<std::tuple<std::size_t, std::size_t, bool>> generateFood();
            void add_score_to_events(std::queue<state::Event> &events);
            void changeDirection();
            bool checkCollision(std::tuple<std::size_t, std::size_t> pos);
            void checkFood();
            std::queue<state::Event> transform_map_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<state::Keybinds> _keys;
            std::size_t _ticks;
            std::size_t _score;
            std::tuple<std::size_t, std::size_t> _direction;
            std::string _headDirection;
            std::tuple<std::size_t, std::size_t> _Pacman;
            std::vector<std::tuple<std::size_t, std::size_t, bool>> _food;
            std::vector<std::shared_ptr<game::Ghost>> _ghosts;
    };
};

#endif /* !Pacman_HPP_ */
