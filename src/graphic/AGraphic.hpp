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
    #include "../Keybinds.hpp"
    #include "../Event.hpp"
    #include <memory>

namespace graphic {
    class AGraphic : public IGraphic {
            public:
                virtual void updateKeybinds() = 0;
                virtual std::queue<state::Event> draw() = 0;
                virtual void readEvent(std::queue<state::Event> &event) final;

                virtual void readWin(std::queue<state::Event> &event) final;
                virtual void readLose(std::queue<state::Event> &event) final;
                virtual void readPause(std::queue<state::Event> &event) final;
                virtual void readDraw(std::queue<state::Event> &event) final;
                virtual void readDrawString(std::queue<state::Event> &event) final;
                virtual void readSound(std::queue<state::Event> &event) final;
                virtual void readTime(std::queue<state::Event> &event) final;
                virtual void packetError(std::queue<state::Event> &event) final;
                virtual void setWin(bool win) { _win = win; };
                virtual void setLose(bool lose) { _lose = lose; };
                virtual void setPause(bool pause) { _pause = pause; };
                virtual void setDraw(std::tuple<std::size_t, std::size_t, std::string> draw) { _draw.push_back(draw); };
                virtual void setDrawStr(std::tuple<std::size_t, std::size_t, std::string, bool > draw_str) {_draw_str.push_back(draw_str);};
                virtual void setSound(std::string sound) { _sound.push_back(sound); };
                virtual void setTime(double time) { _time = time; };
            protected:
                std::shared_ptr<state::Keybinds> _keys;
                bool _win;
                bool _lose;
                bool _pause;
                std::vector<std::tuple<std::size_t, std::size_t, std::string>> _draw;
                std::vector<std::tuple<std::size_t, std::size_t, std::string, bool >> _draw_str;
                std::vector<std::string> _sound;
                double _time;
        };
};

#endif /* !AGRAPHIC_HPP_ */