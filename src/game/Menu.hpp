/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include "AGame.hpp"
#include <queue>

namespace game {
    class Menu : public AGame {
        public:
            Menu(std::shared_ptr<std::map<std::string, bool>> &key);
            ~Menu();
            std::queue<std::tuple<EventType, eventData>> tick();
            std::vector<std::tuple<std::size_t, std::size_t>> changeSnakePos();
            void changeGame();
            void display_menu(std::queue<std::tuple<EventType, eventData>> &events);
            void handle_key_events(std::queue<std::tuple<EventType, eventData>> &events);
            std::queue<std::tuple<EventType, eventData>> transform_libs_to_events(std::vector<std::string> map);

        private:
            std::shared_ptr<std::map<std::string, bool>> _keys;
            std::vector<std::string> _lib_files;
            std::vector<std::string> _game_files;
            std::size_t _ticks;
            std::string _selected_game;
            std::string _selected_graphic;
    };
};

#endif /* !MENU_HPP_ */
