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
    {"food", {255, 255, 0, 255}},
    {"pac_wall", {255, 0, 0, 255}},
    {"pac_down", {0, 255, 255, 255}},
    {"pac_up", {0, 255, 255, 255}},
    {"pac_left", {0, 255, 255, 255}},
    {"pac_right", {0, 255, 255, 255}},
    {"ghost", {255, 255, 255, 255}},
    {"pac_food", {255, 255, 0, 255}},
    {"empty", {255, 255, 255, 255}}
};

extern "C" {
    graphic::Sdl *createGraphix(std::shared_ptr<state::Keybinds> &keybinds)
    {
        return new graphic::Sdl(keybinds);
    }
};

void graphic::Sdl::drawGameElement(SDL_Renderer* renderer, const SDL_Rect& destRect, const std::string& elementType) {
    auto spriteIt = spriteMap.find(elementType);
    if (spriteIt != spriteMap.end()) {
        SDL_Texture* spriteTexture = spriteIt->second.first;
        SDL_Rect& spriteSourceRect = spriteIt->second.second;
        SDL_RenderCopy(renderer, spriteTexture, &spriteSourceRect, &destRect);
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
    SDL_Texture* spriteSheetTexture = loadSprite("assets/snake-graphics.png.png");
    SDL_Rect wallRect = { /* x, y, width, height */ };
    SDL_Rect snakeHeadDownRect = { /* x, y, width, height */ };
    SDL_Rect snakeHeadUpRect = { /* x, y, width, height */ };
    SDL_Rect snakeHeadLeftRect = { /* x, y, width, height */ };
    SDL_Rect snakeHeadRightRect = { /* x, y, width, height */ };
    SDL_Rect snakeHorizontalRect = { /* x, y, width, height */ };
    SDL_Rect snakeVerticalRect = { /* x, y, width, height */ };
    SDL_Rect snakeAngleLeftDownRect = { /* x, y, width, height */ };
    SDL_Rect snakeAngleRightDownRect = { /* x, y, width, height */ };
    SDL_Rect snakeAngleLeftUpRect = { /* x, y, width, height */ };
    SDL_Rect snakeAngleRightUpRect = { /* x, y, width, height */ };
    SDL_Rect snakeTailDownRect = { /* x, y, width, height */ };
    SDL_Rect snakeTailUpRect = { /* x, y, width, height */ };
    SDL_Rect snakeTailLeftRect = { /* x, y, width, height */ };
    SDL_Rect snakeTailRightRect = { /* x, y, width, height */ };
    SDL_Rect foodRect = { /* x, y, width, height */ };
    SDL_Rect pacWallRect = { /* x, y, width, height */ };
    SDL_Rect pacDownRect = { /* x, y, width, height */ };
    SDL_Rect pacUpRect = { /* x, y, width, height */ };
    SDL_Rect pacLeftRect = { /* x, y, width, height */ };
    SDL_Rect pacRightRect = { /* x, y, width, height */ };
    SDL_Rect ghostRect = { /* x, y, width, height */ };
    SDL_Rect pacFoodRect = { /* x, y, width, height */ };
    SDL_Rect emptyRect = { /* x, y, width, height */ };

    spriteMap["snake_head_down"] = std::make_pair(spriteSheetTexture, snakeHeadDownRect);
    spriteMap["snake_head_up"] = std::make_pair(spriteSheetTexture, snakeHeadUpRect);
    spriteMap["snake_head_left"] = std::make_pair(spriteSheetTexture, snakeHeadLeftRect);
    spriteMap["snake_head_right"] = std::make_pair(spriteSheetTexture, snakeHeadRightRect);
    spriteMap["snake_body"] = std::make_pair(spriteSheetTexture, snakeHorizontalRect);
    spriteMap["horizontal_snake_body"] = std::make_pair(spriteSheetTexture, snakeHorizontalRect);
    spriteMap["vertical_snake_body"] = std::make_pair(spriteSheetTexture, snakeVerticalRect);
    spriteMap["angle_left_down_snake_body"] = std::make_pair(spriteSheetTexture, snakeAngleLeftDownRect);
    spriteMap["angle_right_down_snake_body"] = std::make_pair(spriteSheetTexture, snakeAngleRightDownRect);
    spriteMap["angle_left_up_snake_body"] = std::make_pair(spriteSheetTexture, snakeAngleLeftUpRect);
    spriteMap["angle_right_up_snake_body"] = std::make_pair(spriteSheetTexture, snakeAngleRightUpRect);
    spriteMap["snake_tail_down"] = std::make_pair(spriteSheetTexture, snakeTailDownRect);
    spriteMap["snake_tail_up"] = std::make_pair(spriteSheetTexture, snakeTailUpRect);
    spriteMap["snake_tail_left"] = std::make_pair(spriteSheetTexture, snakeTailLeftRect);
    spriteMap["snake_tail_right"] = std::make_pair(spriteSheetTexture, snakeTailRightRect);
    spriteMap["food"] = std::make_pair(spriteSheetTexture, foodRect);
    spriteMap["pac_wall"] = std::make_pair(spriteSheetTexture, pacWallRect);
    spriteMap["pac_down"] = std::make_pair(spriteSheetTexture, pacDownRect);
    spriteMap["pac_up"] = std::make_pair(spriteSheetTexture, pacUpRect);
    spriteMap["pac_left"] = std::make_pair(spriteSheetTexture, pacLeftRect);
    spriteMap["pac_right"] = std::make_pair(spriteSheetTexture, pacRightRect);
    spriteMap["ghost"] = std::make_pair(spriteSheetTexture, ghostRect);
    spriteMap["pac_food"] = std::make_pair(spriteSheetTexture, pacFoodRect);
    spriteMap["empty"] = std::make_pair(spriteSheetTexture, emptyRect);
}

graphic::Sdl::Sdl(std::shared_ptr<state::Keybinds> &key) : _keys(key) {
    std::string action;
    if (TTF_Init() == -1) {
        std::cerr << TTF_GetError() << std::endl;
    }

    _font = TTF_OpenFont("src/graphic/ARCADE_I.ttf", 24);
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
    action = "UP";
    _keys.get()->bindKey(action, SDLK_UP);
    action = "DOWN";
    _keys.get()->bindKey(action, SDLK_DOWN);
    action = "LEFT";
    _keys.get()->bindKey(action, SDLK_LEFT);
    action = "RIGHT";
    _keys.get()->bindKey(action, SDLK_RIGHT);
    action = "ESC";
    _keys.get()->bindKey(action, SDL_QUIT);
    IMG_Init(IMG_INIT_PNG);
    loadSprites();
}

graphic::Sdl::~Sdl() {
    if (_font != nullptr) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
    for (auto& pair : spriteMap) {
        SDL_DestroyTexture(pair.second);
    }
    spriteMap.clear();
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
    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(_font, textp.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(_renderer, texture, nullptr, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void graphic::Sdl::updateKeybinds() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            _keys->keyPressed("ESC", true);
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:    _keys->keyPressed("UP", true); break;
                case SDLK_DOWN:  _keys->keyPressed("DOWN", true); break;
                case SDLK_LEFT:  _keys->keyPressed("LEFT", true); break;
                case SDLK_RIGHT: _keys->keyPressed("RIGHT", true); break;
            }
        }
    }
}

std::queue<state::Event> graphic::Sdl::draw(std::queue<state::Event> &event) {
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    readEvent(event);
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

    _draw.clear();
    event = std::queue<state::Event>();
    return event;
}
