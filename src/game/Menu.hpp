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
#include <chrono>

namespace game {
    class Menu : public AGame {
        public:
            Menu(std::shared_ptr<std::map<std::string, bool>> &key, int &score, std::string &username);
            ~Menu();
            std::queue<std::tuple<EventType, eventData>> tick(double delta);
            std::vector<std::tuple<std::size_t, std::size_t>> changeSnakePos();
            void selectNext(int type);
            void selectPrev(int type);
            void selectFirstGraphic();
            void selectFirstGame();
            void send_packet(int type, std::vector<std::tuple<std::string, bool, int>> &libs, std::queue<std::tuple<EventType, eventData>> &events);
            void display_menu(std::queue<std::tuple<EventType, eventData>> &events);
            void handle_key_events(std::queue<std::tuple<EventType, eventData>> &events);

        private:
            std::shared_ptr<std::map<std::string, bool>> _keys;
            std::queue<std::tuple<EventType, eventData>> _events;
            double _moveTime;
            std::vector<std::tuple<std::string, bool, int>> _libs;
            std::vector<std::string> _lib_files;
            int _typeSelected;
            std::size_t _ticks;
            std::string _selected_game;
            std::string _selected_graphic;
            bool _user_input = false;
            std::string &_user_input_text;
            int &_iscore;
    };
};

#endif /* !MENU_HPP_ */
