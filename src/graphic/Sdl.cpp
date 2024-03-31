#include "Sdl.hpp"
#include <iostream>

std::map<std::string, SDL_Color> colorMap = {
    {"wall", {255, 0, 0, 255}},
    {"snake_head_down", {0, 255, 255, 255}},
    {"snake_head_up", {0, 255, 255, 255}},
    {"snake_head_left", {0, 255, 255, 255}},
    {"snake_head_right", {0, 255, 255, 255}},
    {"snake_body", {0, 255, 0, 255}},
    {"food", {255, 255, 0, 255}}
};


static void drawGameElement(SDL_Renderer* renderer, const SDL_Rect& rect, const std::string& elementType) {
    auto colorIt = colorMap.find(elementType);
    if (colorIt != colorMap.end()) {
        const SDL_Color& color = colorIt->second;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

graphic::Sdl::Sdl(std::shared_ptr<state::Keybinds> &key) : _keys(key) {
    std::string action;

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
}

graphic::Sdl::~Sdl() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
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

    SDL_RenderPresent(_renderer);

    _draw.clear();
    event = std::queue<state::Event>();
    return event;
}
