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
    #include <memory>

namespace arcade {
    class CoreProgram {
        public:
            CoreProgram();
            ~CoreProgram();
            int &getScore();
            void loadGame(const std::string& game);
            void loadGraphic(const std::string& graphic);
            void loadMenu();
            void selectNext(int type);
            void selectNextGame();
            void selectNextGraphic();
            bool checkForEventChangeThing(std::queue<std::tuple<EventType, eventData>> events);
            int loop(void);

        private:
            int _score;
            std::string _username;
            std::queue<std::tuple<EventType, eventData>> _events;
            std::shared_ptr<std::map<std::string, bool>> _keys;
            std::vector<std::tuple<std::string, bool, int>> _libs;
            std::vector<std::string> _lib_files;
            std::shared_ptr<game::IGame> _game;
            std::shared_ptr<graphic::IGraphic> _graphic;
    };
}

#endif /* !ARCADE_HPP_ */
