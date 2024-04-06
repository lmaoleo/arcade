/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Sdl
*/

#include "Sdl.hpp"
#include <iostream>

std::map<SDL_Keycode, std::string> _keyMap;


extern "C" {
    graphic::Sdl *createGraphic(std::shared_ptr<std::map<std::string, bool>> &keybinds)
    {
        return new graphic::Sdl(keybinds);
    }
};

graphic::Sdl::Sdl(std::shared_ptr<std::map<std::string, bool>> &key) : _keys(key) {
    std::string action;
    if (TTF_Init() == -1) {
        std::cerr << TTF_GetError() << std::endl;
    }

    _font = TTF_OpenFont("assets/ARCADE_I.ttf", 24);
    if (_font == nullptr) {
        std::cerr << TTF_GetError() << std::endl;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << SDL_GetError() << std::endl;
    }
    else {
        _window = SDL_CreateWindow("Arcade DE ZINZIN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
        if (_window == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
        }
        else {
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
            if (_renderer == nullptr) {
                std::cerr <<SDL_GetError() << std::endl;
            }
        }
    }
    _keyMap = {
            {SDLK_UP, "UP"}, {SDLK_DOWN, "DOWN"}, {SDLK_LEFT, "LEFT"}, {SDLK_RIGHT, "RIGHT"},
            {SDLK_ESCAPE, "ESC"}, {SDLK_RETURN, "ENTER"}, {SDLK_SPACE, "SPACE"},
            {SDLK_a, "A"}, {SDLK_z, "Z"}, {SDLK_e, "E"}, {SDLK_r, "R"},
            {SDLK_t, "T"}, {SDLK_y, "Y"}, {SDLK_u, "U"}, {SDLK_i, "I"},
            {SDLK_o, "O"}, {SDLK_p, "P"}, {SDLK_q, "Q"}, {SDLK_s, "S"},
            {SDLK_g, "G"}, {SDLK_h, "H"}, {SDLK_j, "J"}, {SDLK_k, "K"},
            {SDLK_l, "L"}, {SDLK_m, "M"}, {SDLK_w, "W"}, {SDLK_x, "X"},
            {SDLK_d, "D"}, {SDLK_f, "F"}, {SDLK_TAB, "TAB"},
            {SDLK_c, "C"}, {SDLK_v, "V"}, {SDLK_b, "B"}, {SDLK_n, "N"},
            {SDLK_F1, "F1"}, {SDLK_F2, "F2"}, {SDLK_F3, "F3"}, {SDLK_F4, "F4"},
    };
}

graphic::Sdl::~Sdl() {
    if (_font != nullptr) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
    TTF_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void graphic::Sdl::drawText(const std::string &text, const int &x, const int &y, bool selected) {
    if (text == "empty")
        return;
    std::string textp = text;
    if (selected) {
        textp = ">> " + textp + " <<";
    }
    SDL_Color color = {255, 255, 255, 255}; // white
    SDL_Surface* surface = TTF_RenderText_Solid(_font, textp.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(_renderer, texture, nullptr, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void graphic::Sdl::updateKeybinds() {
    SDL_Event e;

    for (auto& key : *_keys) {
            key.second = false;
    }

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            _keys->at("ESC") = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            auto found = _keyMap.find(e.key.keysym.sym);
            if (found != _keyMap.end()) {
                if (_keys->find(found->second) != _keys->end()) {
                    _keys->at(found->second) = true;
                }
            }
        }
    }

}

std::tuple<short, short, short, short> graphic::Sdl::intToRgb(unsigned int color)
{
    short a = (color >> 24) & 0xFF; // Correctly masks the alpha component
    short r = (color >> 16) & 0xFF; // Correctly masks the red component
    short g = (color >> 8) & 0xFF;  // Correctly masks the green component
    short b = color & 0xFF;         // Correctly masks the blue component

    return std::make_tuple(a, r, g, b);
}

void graphic::Sdl::createPixels(std::size_t x, std::size_t y, short pixel_form, unsigned int colorpat)
{
    std::vector<SDL_Rect> pixel;
    std::tuple<short, short, short, short> cw = intToRgb(colorpat);
    int scale = 10;
    int rectSize = 10 * scale;
    int sx = x * 4 * scale;
    int sy = y * 4 * scale;

    for (int i = 0; i < 16; i++) {
        SDL_Rect rect = {
            static_cast<int>(sx + (i % 4) * scale),
            static_cast<int>(sy + (i / 4) * scale),
            rectSize,
            rectSize
        };
        if (pixel_form & (1 << i)) {
            const SDL_Color& color = {static_cast<Uint8>(std::get<1>(cw)), static_cast<Uint8>(std::get<2>(cw)), static_cast<Uint8>(std::get<3>(cw)), static_cast<Uint8>(std::get<0>(cw))};
            SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(_renderer, &rect);
        } else {
            const SDL_Color& color = {0, 0, 0, 255};
            SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(_renderer, &rect);
        }
    }
}

void graphic::Sdl::flushscreen() {
    SDL_RenderClear(_renderer);
}

std::queue<std::tuple<EventType, eventData>> graphic::Sdl::draw() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    for (const auto& item : _draw) {
        std::size_t x, y;
        short pixel;
        unsigned int color;
        std::tie(x, y, pixel, color) = item;
        createPixels(x, y, pixel, color);
    }
    for (const auto& item : _draw_str) {
        std::size_t x, y;
        std::string str;
        bool selected;
        x = std::get<0>(item);
        y = std::get<1>(item);
        str = std::get<2>(item);
        selected = std::get<3>(item);
        drawText(str, static_cast<int>(x * 40), static_cast<int>(y * 40), selected);
    }
    SDL_RenderPresent(_renderer);

    _draw_str.clear();
    _draw.clear();
    return std::queue<std::tuple<EventType, eventData>>();
}
