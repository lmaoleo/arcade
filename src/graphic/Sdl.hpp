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
#include <SDL2/SDL_ttf.h>
#include "AGraphic.hpp"

namespace graphic {
    class Sdl : public graphic::AGraphic {
    public:
        Sdl(std::shared_ptr<state::Keybinds> &key);
        ~Sdl();
        void updateKeybinds() final;
        void drawGameElement(SDL_Renderer* renderer, const SDL_Rect& rect, const std::string& elementType);
        void drawText(const std::string &text, const int &x, const int &y, bool selected);
        std::queue<state::Event> draw() final;

    private:
        std::shared_ptr<state::Keybinds> _keys;
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        TTF_Font* _font;
    };
};
