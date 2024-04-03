/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual [WSL: Fedora]
** File description:
** Sfml
*/

#include "Sfml.hpp"

std::map<std::string, std::pair<sf::Texture *, sf::IntRect>> spriteMap;

std::map<std::string, sf::Color> colorMap = {
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
    graphic::Sfml *createGraphic(std::shared_ptr<std::map<std::string, bool>> &keybinds)
    {
        return new graphic::Sfml(keybinds);
    }
};

graphic::Sfml::Sfml(std::shared_ptr<std::map<std::string, bool>> &key) : _keys(key)
{
    _keys = key;
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade DE ZINZIN");
    _font = new sf::Font();
    if (!_font->loadFromFile("assets/ARCADE_I.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    if (!_window->isOpen()) {
        std::cerr << "Failed to create window!" << std::endl;
    }
    loadSprites();
}

graphic::Sfml::~Sfml()
{
    _window->close();
    delete _window;
    delete _font;
}

void graphic::Sfml::loadSprites() {
    sf::Texture *spriteSheetTextureSnake = loadSprite("assets/snake-graphics.png");
    sf::Texture *spriteSheetTexturePac = loadSprite("assets/spritemap_pacman.png");

    sf::Rect<int> wallRect(26, 219, 21, 20);
    sf::Rect<int> snakeHeadDownRect(256, 64, 64, 64);
    sf::Rect<int> snakeHeadUpRect(192, 0, 64, 64);
    sf::Rect<int> snakeHeadLeftRect(192, 64, 64, 64);
    sf::Rect<int> snakeHeadRightRect(256, 0, 64, 64);
    sf::Rect<int> snakeHorizontalRect(64, 0, 64, 64);
    sf::Rect<int> snakeVerticalRect(128, 64, 64, 64);
    sf::Rect<int> snakeAngleLeftDownRect(0, 0, 64, 64);
    sf::Rect<int> snakeAngleRightDownRect(128, 0, 64, 64);
    sf::Rect<int> snakeAngleLeftUpRect(128, 128, 64, 64);
    sf::Rect<int> snakeAngleRightUpRect(0, 64, 64, 64);
    sf::Rect<int> snakeTailDownRect(256, 128, 64, 64);
    sf::Rect<int> snakeTailUpRect(192, 128, 64, 64);
    sf::Rect<int> snakeTailLeftRect(192, 192, 64, 64);
    sf::Rect<int> snakeTailRightRect(256, 128, 64, 64);
    sf::Rect<int> foodRect(0, 192, 64, 64);
    sf::Rect<int> pacWallRect(0, 96, 24, 24);
    sf::Rect<int> pacDownRect(120, 71, 24, 24);
    sf::Rect<int> pacUpRect(71, 71, 24, 24);
    sf::Rect<int> pacLeftRect(0, 71, 24, 24);
    sf::Rect<int> pacRightRect(96, 71, 24, 24);
    sf::Rect<int> ghostRect(0, 143, 24, 24);
    sf::Rect<int> pacFoodRect(192, 0, 12, 12);
    sf::Rect<int> emptyRect(303, 136, 24, 24);

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

void graphic::Sfml::updateKeybinds()
{
    sf::Event event;
    _keys->at("UP") = false;
    _keys->at("DOWN") = false;
    _keys->at("LEFT") = false;
    _keys->at("RIGHT") = false;
    _keys->at("ESC") = false;
    _keys->at("ESC") = false;
    _keys->at("ENTER") = false;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Up :
                _keys->at("UP") = true;
                break;
            case sf::Keyboard::Down :
                _keys->at("DOWN") = true;
                break;
            case sf::Keyboard::Left :
                _keys->at("LEFT") = true;
                break;
            case sf::Keyboard::Right :
                _keys->at("RIGHT") = true;
                break;
            case sf::Keyboard::Escape :
                _keys->at("ESC") = true;
                break;
            case sf::Keyboard::Return :
                _keys->at("ENTER") = true;
                break;
            default:
                break;
            }
        }
    }
}

void graphic::Sfml::drawGameElement(sf::RenderWindow &window, const sf::IntRect &rect, const std::string &elementType)
{
    auto spriteIt = spriteMap.find(elementType);
    if (spriteIt != spriteMap.end()) {
        sf::Texture *spriteTexture = spriteIt->second.first;
        sf::IntRect &spriteSourceRect = spriteIt->second.second;
        sf::Sprite sprite(*spriteTexture, spriteSourceRect);
        sprite.setPosition(rect.left, rect.top);
        sprite.setScale(rect.width / 64.0, rect.height / 64.0);
        window.draw(sprite);
    }
}

sf::Texture *graphic::Sfml::loadSprite(const std::string &filePath)
{
    sf::Texture *texture = new sf::Texture();
    if (!texture->loadFromFile(filePath)) {
        std::cerr << "Failed to load sprite!" << std::endl;
    }
    return texture;
}

void graphic::Sfml::drawText(const std::string &text, const int &x, const int &y, bool selected)
{
    sf::Text textToDraw = sf::Text(text, *_font, 24);

    textToDraw.setPosition(x * 40, y * 40);
    if (selected) {
        textToDraw.setFillColor(sf::Color::Red);
    }
    _window->draw(textToDraw);
}

std::queue<std::tuple<EventType, eventData>> graphic::Sfml::draw()
{
    std::size_t x, y = 0;
    std::string type = "";

    _window->clear();
    for (auto &item : _draw) {
        x = std::get<0>(item);
        y = std::get<1>(item);
        type = std::get<2>(item);
        sf::IntRect rect(x * 40, y * 40, 40, 40);
        drawGameElement(*_window, rect, type);
    }
    for (auto &item : _draw_str) {
        x = std::get<0>(item);
        y = std::get<1>(item);
        std::string str = std::get<2>(item);
        bool selected = std::get<3>(item);
        drawText(str, x, y, selected);
    }
    _window->display();
    _draw.clear();
    _draw_str.clear();
    return std::queue<std::tuple<EventType, eventData>>();
}