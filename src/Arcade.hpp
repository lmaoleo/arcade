/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** arcade
*/

#ifndef ARCADE_HPP_
    #define ARCADE_HPP_

    #include "graphic/IGraphic.hpp"
    #include "game/IGame.hpp"
    #include "Event.hpp"
    #include "Keybinds.hpp"
    #include <memory>

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
            std::shared_ptr<state::Keybinds> _keys;
            game::IGame *_game;
            graphic::IGraphic *_graphic;
    };
}

#endif /* !ARCADE_HPP_ */
