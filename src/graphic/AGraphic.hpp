/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-raphael.castres
** File description:
** AGraphic
*/

#ifndef AGRAPHIC_HPP_
    #define AGRAPHIC_HPP_

    #include <tuple>
    #include "IGraphic.hpp"
    #include "../Event.hpp"
    #include <memory>
    #include <iostream>

namespace graphic {
    class AGraphic : public IGraphic {
            public:
                virtual void updateKeybinds() = 0;
                virtual std::queue<std::tuple<EventType, eventData>> draw() = 0;
                virtual void flushscreen() = 0;

                virtual void readEvent(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void readWin(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void readLose(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void readPause(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void readDraw(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void readDrawString(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void readTime(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void readSetElm(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void readColor(std::queue<std::tuple<EventType, eventData>> &event) final;
                virtual void packetError(std::queue<std::tuple<EventType, eventData>> &event) final;

            protected:
                std::shared_ptr<std::map<std::string, bool>> _keys;
                bool _win;
                bool _lose;
                bool _pause;
                unsigned int _color;
                std::vector<std::tuple<std::size_t, std::size_t, short, unsigned int>> _draw;
                std::vector<std::tuple<std::size_t, std::size_t, std::string, bool >> _draw_str;
                std::vector<std::string> _sound;
                double _time;
        };
};

#endif /* !AGRAPHIC_HPP_ */