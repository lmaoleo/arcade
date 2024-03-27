/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-raphael.castres
** File description:
** Keybinds
*/

#ifndef KEYBINDS_HPP_
    #define KEYBINDS_HPP_

#include "Event.hpp"

namespace state {
    class Keybinds {
        public:
            Keybinds();
            ~Keybinds();
            bool isKeyPressed(std::string &action);
            void bindKey(std::string &action, unsigned short key);
            void keyPressed(std::string &action, bool pressed);

        private:
            std::map<std::string, std::size_t> _binds;
            std::map<std::string, bool> _pressed;
    };
};

#endif /* !KEYBINDS_HPP_ */