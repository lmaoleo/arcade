/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

    #include "../Event.hpp"
    #include <queue>
    #include <map>

namespace game {
    class IGame {
        public:
            virtual ~IGame() = default;
            virtual std::queue<std::tuple<EventType, eventData>> tick(double delta) = 0;
    };
}

#endif /* !GAME_HPP_ */
