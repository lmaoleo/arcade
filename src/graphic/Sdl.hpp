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
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "AGraphic.hpp"

namespace graphic {
    class Sdl : public graphic::AGraphic {
    public:
        Sdl(std::shared_ptr<std::map<std::string, bool>> &key);
        ~Sdl();
        void updateKeybinds() final;
        void drawGameElement(SDL_Renderer* renderer, const SDL_Rect& rect, const std::string& elementType);
        SDL_Texture* loadSprite(const std::string& filePath);
        void loadSprites();
        std::tuple<short, short, short, short> intToRgb(unsigned int color);
        void createPixels(std::size_t x, std::size_t y, short pixel_form, unsigned int colorpat);
        void drawText(const std::string &text, const int &x, const int &y, bool selected);
        std::queue<std::tuple<EventType, eventData>> draw() final;

    private:
        std::shared_ptr<std::map<std::string, bool>> _keys;
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        TTF_Font* _font;
        bool _spriteLoaded;
    };
};
