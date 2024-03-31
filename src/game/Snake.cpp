/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Snake
*/

#include "Snake.hpp"
#include <iostream>
#include <queue>
#include <map>
#include <ncurses.h>

static std::vector<std::string> map = {
    "##################################",
    "#                                #",
    "#                                #",
    "#                                #",
    "#                                #",
    "#                                #",
    "#                                #",
    "#                                #",
    "#                                #",
    "#                                #",
    "#                                #",
    "#                                #",
    "##################################"
};

static const std::map<char, std::string> charmap = {
    {'#', "wall"},
    {'d', "snake_head_down"},
    {'u', "snake_head_up"},
    {'l', "snake_head_left"},
    {'>', "snake_head_right"},
    {'b', "snake_body"},
    {'f', "food"},
    {' ', "empty"},
};

game::Snake::Snake(std::shared_ptr<state::Keybinds> &keybinds)
{
    _ticks = 0;
    _score = 0;
    _direction = {1, 0};
    _snake = {{5, 7}, {4, 7}, {3, 7}};
    _food = {15, 7};
    _lastTailPos = {2, 7};
    _headDirection = "snake_head_right";
    _keys = keybinds;
}

game::Snake::~Snake()
{
}

extern "C" {
    game::Snake *createGame(std::shared_ptr<state::Keybinds> &keybinds)
    {
        return new game::Snake(keybinds);
    }
}

static void print_map(std::vector<std::string> map)
{
    for (std::size_t i = 0; i < map.size(); i++) {
        std::cout << map[i] << std::endl;
    }
}

static void add_snake_to_map(std::vector<std::string> &map, std::vector<std::tuple<std::size_t, std::size_t>> snake)
{
    for (std::size_t i = 0; i < snake.size(); i++) {
        std::size_t x = std::get<0>(snake[i]);
        std::size_t y = std::get<1>(snake[i]);
        map[y][x] = 'b';
    }
}

static void add_food_to_map(std::vector<std::string> &map, std::tuple<std::size_t, std::size_t> food)
{
    std::size_t x = std::get<0>(food);
    std::size_t y = std::get<1>(food);
    map[y][x] = 'f';
}

static void create_draw_event(std::queue<state::Event> &events, std::size_t x, std::size_t y, std::string type)
{
    state::Event event;
    event.setEventType(state::EventType::DRAW);
    state::Event packetX = state::Event(state::EventType::DATA, x);
    state::Event packetY = state::Event(state::EventType::DATA, y);
    state::Event packetType = state::Event(state::EventType::DATA, type);
    state::Event event2;
    event2.setEventType(state::EventType::DRAW);
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetType);
    events.push(event2);
}

std::queue<state::Event> game::Snake::transform_map_to_events(std::vector<std::string> map)
{
    std::queue<state::Event> events;
    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            if (std::get<0>(_snake[0]) == x && std::get<1>(_snake[0]) == y) {
                create_draw_event(events, x, y, _headDirection);
                continue;
            }
            create_draw_event(events, x, y, charmap.at(map[y][x]));
        }
    }
    return events;
}

void game::Snake::changeDirection()
{
    if (_keys->isKeyPressed("UP") && std::get<1>(_direction) != 1) {
        _direction = {0, -1};
        _headDirection = "snake_head_up";
        _keys->keyPressed("UP", false);
    }
    if (_keys->isKeyPressed("DOWN") && std::get<1>(_direction) != -1) {
        _direction = {0, 1};
        _headDirection = "snake_head_down";
        _keys->keyPressed("DOWN", false);
    }
    if (_keys->isKeyPressed("LEFT") && std::get<0>(_direction) != 1) {
        _direction = {-1, 0};
        _headDirection = "snake_head_left";
        _keys->keyPressed("LEFT", false);
    }
    if (_keys->isKeyPressed("RIGHT") && std::get<0>(_direction) != -1) {
        _direction = {1, 0};
        _headDirection = "snake_head_right";
        _keys->keyPressed("RIGHT", false);
    }
}

void game::Snake::generateFood()
{
    std::size_t x = rand() % (map[0].size() - 2) + 1;
    std::size_t y = rand() % (map.size() - 2) + 1;
    _food = {x, y};
}

bool game::Snake::checkCollision()
{
    std::tuple<std::size_t, std::size_t> head = _snake[0];
    if (std::get<0>(head) == 0 || std::get<0>(head) == map[0].size() - 1 || std::get<1>(head) == 0 || std::get<1>(head) == map.size() - 1) {
        return true;
    }
    for (std::size_t i = 1; i < _snake.size(); i++) {
        if (_snake[i] == head) {
            return true;
        }
    }
    return false;
}

void game::Snake::checkFood()
{
    std::tuple<std::size_t, std::size_t> head = _snake[0];
    if (head == _food) {
        _score++;
        _snake.push_back(_lastTailPos);
        generateFood();
    }
}

std::vector<std::tuple<std::size_t, std::size_t>> game::Snake::changeSnakePos()
{
    _lastTailPos = _snake[_snake.size() - 1];
    for (std::size_t i = _snake.size() - 1; i > 0; i--) {
        _snake[i] = _snake[i - 1];
    }
    std::tuple<std::size_t, std::size_t> newHead = {std::get<0>(_snake[0]) + std::get<0>(_direction), std::get<1>(_snake[0]) + std::get<1>(_direction)};
    _snake[0] = newHead;
    return _snake;
}

void game::Snake::add_snake_to_events(std::queue<state::Event> &event)
{
    create_draw_event(event, std::get<0>(_snake[0]), std::get<1>(_snake[0]), _headDirection);
    for (std::size_t i = 1; i < _snake.size(); i++) {
        create_draw_event(event, std::get<0>(_snake[i]), std::get<1>(_snake[i]), "snake_body");
    }
}

void game::Snake::add_food_to_events(std::queue<state::Event> &events)
{
    create_draw_event(events, std::get<0>(_food), std::get<1>(_food), "food");
}

std::queue<state::Event> game::Snake::tick()
{
    changeDirection();
    std::vector<std::string> newMap = map;
    changeSnakePos();
    add_snake_to_map(newMap, _snake);
    add_food_to_map(newMap, _food);
    std::queue<state::Event> events = transform_map_to_events(newMap);
    if (checkCollision()) {
        state::Event event;
        event.setEventType(state::EventType::LOSE);
        events.push(event);
        std::cout << "You lost" << std::endl;
        return events;
    }
    checkFood();
    _ticks++;
    return events;
}

static void print_events(std::queue<state::Event> events)
{
    while (!events.empty()) {
        events.pop();
    }
}