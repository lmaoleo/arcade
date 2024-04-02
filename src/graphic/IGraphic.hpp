/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** graphic
*/

#ifndef GRAPHIC_HPP_
    #define GRAPHIC_HPP_

    #include <queue>
    #include "../Event.hpp"

namespace graphic {
    class IGraphic {
        public:
            class packetError : public std::exception {
                public:
                    const char *what(void) const noexcept;
            };
            virtual ~IGraphic() = default;
            virtual void updateKeybinds() = 0;
            virtual void readEvent(std::queue<state::Event> &event) = 0;
            virtual std::queue<state::Event> draw() = 0;
    };
}

#endif /* !GRAPHIC_HPP_ */
