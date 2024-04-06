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
#include <chrono>

namespace game {
    class Pacman : public AGame {
        public:
            Pacman(std::shared_ptr<std::map<std::string, bool>> &key);
            ~Pacman();
            std::queue<std::tuple<EventType, eventData>> tick(double delta);
            void changePacmanPos();
            std::vector<std::tuple<std::size_t, std::size_t, bool>> generateFood();
            void add_score_to_events(std::queue<std::tuple<EventType, eventData>> &events);
            void changeDirection();
            bool checkCollision(std::tuple<std::size_t, std::size_t> pos);
            void add_Pacman_to_map(std::vector<std::string> &map, std::tuple<std::size_t, std::size_t> Pacman);
            void checkFood();
            void movesGhostsRandomDirections();
            double getElapsedTime();
            bool isGameOver();
            void send_packet(int type, std::vector<std::tuple<std::string, bool, int>> &libs, std::queue<std::tuple<EventType, eventData>> &events);
            std::queue<std::tuple<EventType, eventData>> transform_map_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<std::map<std::string, bool>> _keys;
            std::size_t _ticks;
            std::size_t _score;
            std::tuple<std::size_t, std::size_t> _direction;
            std::string _headDirection;
            std::tuple<std::size_t, std::size_t> _Pacman;
            std::vector<std::tuple<std::size_t, std::size_t, bool>> _food;
            std::vector<std::tuple<std::size_t, std::size_t>> _ghosts;
            std::vector<std::tuple<std::size_t, std::size_t>> _ghostsOrigins;
            std::chrono::high_resolution_clock::time_point _startTime;
            std::queue<std::tuple<EventType, eventData>> _events;
            double _moveTime;
    };
};

static unsigned int rgbToInt(unsigned int a, unsigned short r, unsigned short g, unsigned short b);

#endif /* !Pacman_HPP_ */
