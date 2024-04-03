/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Sdl
*/

#include "Sdl.hpp"
#include <iostream>

std::map<std::string, std::pair<SDL_Texture *, SDL_Rect>> spriteMap;

std::map<std::string, SDL_Color> colorMap = {
    {"wall", {255, 0, 0, 255}},
    {"snake_head_down", {0, 255, 255, 255}},
    {"snake_head_up", {0, 255, 255, 255}},
    {"snake_head_left", {0, 255, 255, 255}},
    {"snake_head_right", {0, 255, 255, 255}},
    {"snake_body", {0, 255, 0, 255}},
    {"horizontal_snake_body", {0, 255, 0, 255}},
    {"vertical_snake_body", {0, 255, 0, 255}},
    {"angle_left_down_snake_body", {0, 255, 0, 255}},
    {"angle_right_down_snake_body", {0, 255, 0, 255}},
    {"angle_left_up_snake_body", {0, 255, 0, 255}},
    {"angle_right_up_snake_body", {0, 255, 0, 255}},
    {"snake_tail_down", {0, 255, 255, 255}},
    {"snake_tail_up", {0, 255, 255, 255}},
    {"snake_tail_left", {0, 255, 255, 255}},
    {"snake_tail_right", {0, 255, 255, 255}},
    {"pac_wall", {15, 46, 215, 255}},
    {"pac_down", {255, 255, 0, 255}},
    {"pac_up", {255, 255, 0, 255}},
    {"pac_left", {255, 255, 0, 255}},
    {"pac_right", {255, 255, 0, 255}},
    {"ghost", {255, 0, 0, 255}},
    {"pac_food", {231, 154, 149, 255}},
    {"food", {255, 255, 0, 255}}
};

extern "C" {
    graphic::Sdl *createGraphic(std::shared_ptr<std::map<std::string, bool>> &keybinds)
    {
        return new graphic::Sdl(keybinds);
    }
};

void graphic::Sdl::drawGameElement(SDL_Renderer* renderer, const SDL_Rect& destRect, const std::string& elementType) {
    if (_spriteLoaded == false) {
        auto colorIt = colorMap.find(elementType);
        if (colorIt != colorMap.end()) {
            const SDL_Color& color = colorIt->second;
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &destRect);
            }
    } else  {
        auto spriteIt = spriteMap.find(elementType);
        if (spriteIt != spriteMap.end()) {
            SDL_Texture* spriteTexture = spriteIt->second.first;
            SDL_Rect& spriteSourceRect = spriteIt->second.second;
            SDL_RenderCopy(renderer, spriteTexture, &spriteSourceRect, &destRect);
        }
    }
}

SDL_Texture* graphic::Sdl::loadSprite(const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Error loading sprite: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Error creating texture from surface: " << SDL_GetError() << std::endl;
    }
    return texture;
}

void graphic::Sdl::loadSprites() {
    SDL_Texture* spriteSheetTextureSnake = loadSprite("assets/snake-graphics.png");
    SDL_Texture* spriteSheetTexturePac = loadSprite("assets/spritemap_pacman.png");
    SDL_Rect wallRect = {26, 219, 21, 20};
    SDL_Rect snakeHeadDownRect = {256, 64, 64, 64};
    SDL_Rect snakeHeadUpRect = {192, 0, 64, 64};
    SDL_Rect snakeHeadLeftRect = {192, 64, 64, 64};
    SDL_Rect snakeHeadRightRect = {256, 0, 64, 64};
    SDL_Rect snakeHorizontalRect = {64, 0, 64, 64};
    SDL_Rect snakeVerticalRect = {128, 64, 64, 64};
    SDL_Rect snakeAngleLeftDownRect = {0, 0, 64, 64};
    SDL_Rect snakeAngleRightDownRect = {128, 0, 64, 64};
    SDL_Rect snakeAngleLeftUpRect = {128, 128, 64, 64};
    SDL_Rect snakeAngleRightUpRect = {0, 64, 64, 64};
    SDL_Rect snakeTailDownRect = {256, 128, 64, 64};
    SDL_Rect snakeTailUpRect = {192, 128, 64, 64};
    SDL_Rect snakeTailLeftRect = {192, 192, 64, 64};
    SDL_Rect snakeTailRightRect = {256, 128, 64, 64};
    SDL_Rect foodRect = {0, 192, 64, 64};
    SDL_Rect pacWallRect = {0, 96, 24, 24};
    SDL_Rect pacDownRect = {120, 71, 24, 24};
    SDL_Rect pacUpRect = {71, 71, 24, 24};
    SDL_Rect pacLeftRect = {0, 71, 24, 24};
    SDL_Rect pacRightRect = {96, 71, 24, 24};
    SDL_Rect ghostRect = {0, 143, 24, 24};
    SDL_Rect pacFoodRect = {192, 0, 12, 12};
    SDL_Rect emptyRect = {303, 136, 24, 24};

    spriteMap["snake_head_down"] = std::make_pair(spriteSheetTextureSnake, snakeHeadDownRect);
    spriteMap["snake_head_up"] = std::make_pair(spriteSheetTextureSnake, snakeHeadUpRect);
    spriteMap["snake_head_left"] = std::make_pair(spriteSheetTextureSnake, snakeHeadLeftRect);
    spriteMap["snake_head_right"] = std::make_pair(spriteSheetTextureSnake, snakeHeadRightRect);
    spriteMap["snake_body"] = std::make_pair(spriteSheetTextureSnake, snakeHorizontalRect);
    spriteMap["horizontal_snake_body"] = std::make_pair(spriteSheetTextureSnake, snakeHorizontalRect);
    spriteMap["vertical_snake_body"] = std::make_pair(spriteSheetTextureSnake, snakeVerticalRect);
    spriteMap["angle_right_down_snake_body"] = std::make_pair(spriteSheetTextureSnake, snakeAngleLeftDownRect);
    spriteMap["angle_left_down_snake_body"] = std::make_pair(spriteSheetTextureSnake, snakeAngleRightDownRect);
    spriteMap["angle_left_up_snake_body"] = std::make_pair(spriteSheetTextureSnake, snakeAngleLeftUpRect);
    spriteMap["angle_right_up_snake_body"] = std::make_pair(spriteSheetTextureSnake, snakeAngleRightUpRect);
    spriteMap["snake_tail_down"] = std::make_pair(spriteSheetTextureSnake, snakeTailDownRect);
    spriteMap["snake_tail_up"] = std::make_pair(spriteSheetTextureSnake, snakeTailUpRect);
    spriteMap["snake_tail_left"] = std::make_pair(spriteSheetTextureSnake, snakeTailLeftRect);
    spriteMap["snake_tail_right"] = std::make_pair(spriteSheetTextureSnake, snakeTailRightRect);
    spriteMap["food"] = std::make_pair(spriteSheetTextureSnake, foodRect);
    spriteMap["pac_wall"] = std::make_pair(spriteSheetTexturePac, pacWallRect);
    spriteMap["pac_down"] = std::make_pair(spriteSheetTexturePac, pacDownRect);
    spriteMap["pac_up"] = std::make_pair(spriteSheetTexturePac, pacUpRect);
    spriteMap["pac_left"] = std::make_pair(spriteSheetTexturePac, pacLeftRect);
    spriteMap["pac_right"] = std::make_pair(spriteSheetTexturePac, pacRightRect);
    spriteMap["ghost"] = std::make_pair(spriteSheetTexturePac, ghostRect);
    spriteMap["pac_food"] = std::make_pair(spriteSheetTexturePac, pacFoodRect);
    spriteMap["empty"] = std::make_pair(spriteSheetTexturePac, emptyRect);
    spriteMap["wall"] = std::make_pair(spriteSheetTextureSnake, wallRect);
}

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
    loadSprites();
    if (spriteMap.empty()) {
        _spriteLoaded = false;
    } else {
        _spriteLoaded = true;
    }
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
    _keys->at("UP") = false;
    _keys->at("DOWN") = false;
    _keys->at("LEFT") = false;
    _keys->at("RIGHT") = false;
    _keys->at("ESC") = false;
    _keys->at("ESC") = false;
    _keys->at("ENTER") = false;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            if (_keys->find("ESC") != _keys->end())
                _keys->at("ESC") = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    if (_keys->find("UP") != _keys->end())
                        _keys->at("UP") = true;
                    break;
                case SDLK_DOWN:
                    if (_keys->find("DOWN") != _keys->end())
                        _keys->at("DOWN") = true;
                    break;
                case SDLK_LEFT:
                    if (_keys->find("LEFT") != _keys->end())
                        _keys->at("LEFT") = true;
                    break;
                case SDLK_RIGHT:
                    if (_keys->find("RIGHT") != _keys->end())
                        _keys->at("RIGHT") = true;
                    break;
                case SDLK_ESCAPE:
                    if (_keys->find("ESC") != _keys->end())
                        _keys->at("ESC") = true;
                    break;
                case SDLK_RETURN:
                    if (_keys->find("ENTER") != _keys->end())
                        _keys->at("ENTER") = true;
                    break;
            }
        }
    }
}

std::queue<std::tuple<EventType, eventData>> graphic::Sdl::draw() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    for (const auto& item : _draw) {
        std::size_t x, y;
        std::string type;
        x = std::get<0>(item);
        y = std::get<1>(item);
        type = std::get<2>(item);
        SDL_Rect rect = {static_cast<int>(x * 40),static_cast<int>(y * 40), 40, 40};
        drawGameElement(_renderer, rect, type);
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
