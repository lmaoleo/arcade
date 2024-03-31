/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2
*/

#pragma once

#include <wchar.h>
#include <locale.h>
#include <SDL2/SDL.h>
#include "AGraphic.hpp"

namespace graphic {
    class Sdl : public graphic::AGraphic {
    public:
        Sdl(std::shared_ptr<state::Keybinds> &key);
        ~Sdl();
        void updateKeybinds() final;
        std::queue<state::Event> draw(std::queue<state::Event> &event) final;

    private:
        std::shared_ptr<state::Keybinds> _keys;
        SDL_Window *_window;
        SDL_Renderer *_renderer;
    };
};
