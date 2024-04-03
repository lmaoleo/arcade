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
    #include <map>
    #include <queue>
    #include <tuple>
    #include <iostream>

namespace graphic {
    class IGraphic {
        public:
            class packetError : public std::exception {
                public:
                    const char *what(void) const noexcept;
            };
            virtual ~IGraphic() = default;
            virtual void updateKeybinds() = 0;
            virtual std::queue<std::tuple<EventType, eventData>> draw() = 0;
            virtual void flushscreen() = 0;
            virtual void readEvent(std::queue<std::tuple<EventType, eventData>> &event) = 0;
    };
}

#endif /* !GRAPHIC_HPP_ */
