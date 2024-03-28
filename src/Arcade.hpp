/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** arcade
*/

#ifndef ARCADE_HPP_
    #define ARCADE_HPP_

    #include "IGraphic.hpp"
    #include "IGame.hpp"
    #include "Event.hpp"
    #include "Keybinds.hpp"

namespace arcade {
    class CoreProgram {
        public:
            CoreProgram();
            ~CoreProgram();
            int &getScore();
            void loadGame(std::string game);
            void loadGraphic(std::string graphic);
            int loop();

        private:
            int _score;
            state::Keybinds _keys;
            game::IGame *_game;
            graphic::IGraphic *_graphic;
    };
}

#endif /* !ARCADE_HPP_ */
