/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-raphael.castres
** File description:
** AGraphic
*/

#ifndef AGRAPHIC_HPP_
    #define AGRAPHIC_HPP_

    #include "IGraphic.hpp"
    #include "Keybinds.hpp"
    #include "Event.hpp"

namespace graphic {
    class AGraphic : public IGraphic {
            public:
                AGraphic();
                AGraphic(state::Keybinds &keys);
                virtual ~AGraphic();
                virtual void updateKeybinds() = 0;
                virtual std::queue<state::Event> draw() = 0;
                virtual void readEvent(std::queue<state::Event> event) final;

                virtual void readWin(std::queue<state::Event> &event) = 0;
                virtual void readLose(std::queue<state::Event> &event) = 0;
                virtual void readPause(std::queue<state::Event> &event) = 0;
                virtual void readDraw(std::queue<state::Event> &event) = 0;
                virtual void readSound(std::queue<state::Event> &event) = 0;
                virtual void readTime(std::queue<state::Event> &event) = 0;
                virtual void packetError(std::queue<state::Event> &event) final;
            protected:
                state::Keybinds _keys;
                bool _win;
                bool _lose;
                bool _pause;
                std::vector<std::tuple<int, int, std::string>> _draw;
                std::vector<std::string> _sound;
                double _time;
            private:
        };
};

#endif /* !AGRAPHIC_HPP_ */
