/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

    #include "Event.hpp"
    #include <queue>

namespace game {
    class IGame {
        public:
            virtual ~IGame() = default;
            virtual void tick();

            virtual void transform_map_to_events(std::vector<std::string> map);
    };
}

#endif /* !GAME_HPP_ */
