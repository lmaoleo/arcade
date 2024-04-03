/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-raphael.castres
** File description:
** AGame
*/

#ifndef AGAME_HPP_
    #define AGAME_HPP_

    #include "IGame.hpp"
    #include "../Event.hpp"
    #include <memory>

namespace game {
    class AGame : public IGame {
        public:
            virtual ~AGame() = default;
            virtual std::queue<std::tuple<EventType, eventData>> tick() = 0;

        private:
            std::shared_ptr<std::map<std::string, bool>> _keys;
            std::size_t _ticks;
    };
};

#endif /* !AGAME_HPP_ */
