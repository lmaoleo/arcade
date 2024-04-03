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
#include <string>

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

game::Snake::Snake(std::shared_ptr<std::map<std::string, bool>> &keybinds)
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
    game::Snake *createGame(std::shared_ptr<std::map<std::string, bool>> &keybinds)
    {
        return new game::Snake(keybinds);
    }
}

// static void print_map(std::vector<std::string> map)
// {
//     for (std::size_t i = 0; i < map.size(); i++) {
//         std::cout << map[i] << std::endl;
//     }
// }

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

static void create_draw_event(std::queue<std::tuple<EventType, eventData>> &events, std::size_t x, std::size_t y, std::string type)
{
    std::tuple<EventType, eventData> event = {EventType::DRAW, false};
    std::tuple<EventType, eventData> packetX = {EventType::DATA, x};
    std::tuple<EventType, eventData> packetY = {EventType::DATA, y};
    std::tuple<EventType, eventData> packetType = {EventType::DATA, type};
    std::tuple<EventType, eventData> event2 = {EventType::DRAW, false};
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetType);
    events.push(event2);
}

static void create_draw_string_event(std::queue<std::tuple<EventType, eventData>> &events, std::size_t x, std::size_t y, std::string score)
{
    std::tuple<EventType, eventData> event = {EventType::DRAW_STRING, false};
    std::tuple<EventType, eventData> packetX = {EventType::DATA, x};
    std::tuple<EventType, eventData> packetY = {EventType::DATA, y};
    std::tuple<EventType, eventData> packetScore = {EventType::DATA, score};
    std::tuple<EventType, eventData> eventselect = {EventType::DATA, false};
    std::tuple<EventType, eventData> event2 = {EventType::DRAW_STRING, false};
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetScore);
    events.push(eventselect);
    events.push(event2);
}

std::queue<std::tuple<EventType, eventData>> game::Snake::transform_map_to_events(std::vector<std::string> map)
{
    std::queue<std::tuple<EventType, eventData>> events;
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
    if (_keys->at("UP") && std::get<1>(_direction) != 1) {
        _direction = {0, -1};
        _headDirection = "snake_head_up";
        _keys->at("UP") = false;
    }
    if (_keys->at("DOWN") && std::get<1>(_direction) !=   static_cast<unsigned long>(-1)) {
        _direction = {0, 1};
        _headDirection = "snake_head_down";
        _keys->at("DOWN") = false;
    }
    if (_keys->at("LEFT") && std::get<0>(_direction) != 1) {
        _direction = {-1, 0};
        _headDirection = "snake_head_left";
        _keys->at("LEFT") = false;
    }
    if (_keys->at("RIGHT") && std::get<0>(_direction) != static_cast<unsigned long>(-1)) {
        _direction = {1, 0};
        _headDirection = "snake_head_right";
        _keys->at("RIGHT") = false;
    }
    _keys->at("UP") = false;
    _keys->at("DOWN") = false;
    _keys->at("LEFT") = false;
    _keys->at("RIGHT") = false;
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

std::string game::Snake::determine_body_orientation(int i)
{
    std::tuple<std::size_t, std::size_t> past_snake = _snake[i + 1];
    std::tuple<std::size_t, std::size_t> current_snake = _snake[i];
    std::tuple<std::size_t, std::size_t> next_snake = _snake[i - 1];

    std::size_t past_x = std::get<0>(past_snake);
    std::size_t past_y = std::get<1>(past_snake);
    std::size_t current_x = std::get<0>(current_snake);
    std::size_t current_y = std::get<1>(current_snake);
    std::size_t next_x = std::get<0>(next_snake);
    std::size_t next_y = std::get<1>(next_snake);

    if ((past_x < current_x && current_x < next_x) || (past_x > current_x && current_x > next_x)) {
        return "horizontal_snake_body";
    } else if ((past_y < current_y && current_y < next_y) || (past_y > current_y && current_y > next_y)) {
        return "vertical_snake_body";
    } else if ((past_x < current_x && current_y < next_y) || (next_x < current_x && current_y < past_y)) {
        return "angle_left_down_snake_body";
    } else if ((past_x < current_x && current_y > next_y) || (next_x < current_x && current_y > past_y)) {
        return "angle_left_up_snake_body";
    } else if ((past_x > current_x && current_y < next_y) || (next_x > current_x && current_y < past_y)) {
        return "angle_right_down_snake_body";
    } else if ((past_x > current_x && current_y > next_y) || (next_x > current_x && current_y > past_y)) {
        return "angle_right_up_snake_body";
    }
    return "snake_body";
}

std::string game::Snake::determine_tail_orientation(int i)
{
    std::tuple<std::size_t, std::size_t> past_snake = _snake[i + 1];
    std::tuple<std::size_t, std::size_t> current_snake = _snake[i];

    std::size_t past_x = std::get<0>(past_snake);
    std::size_t past_y = std::get<1>(past_snake);
    std::size_t current_x = std::get<0>(current_snake);
    std::size_t current_y = std::get<1>(current_snake);

    if (past_y < current_y) {
        return "snake_tail_up";
    } else if (past_y > current_y) {
        return "snake_tail_down";
    } else if (past_x < current_x) {
        return "snake_tail_left";
    } else if (past_x > current_x) {
        return "snake_tail_right";
    }
    return "snake_body";
}

void game::Snake::add_snake_to_events(std::queue<std::tuple<EventType, eventData>> &event)
{
    std::string body_orientation;
    std::string tail_orientation;

    tail_orientation = determine_tail_orientation(_snake.size() - 1);
    create_draw_event(event, std::get<0>(_snake[0]), std::get<1>(_snake[0]), _headDirection);
    for (std::size_t i = 1; i < _snake.size() - 1; i++) {
        body_orientation = determine_body_orientation(i);
        create_draw_event(event, std::get<0>(_snake[i]), std::get<1>(_snake[i]), body_orientation);
    }
    create_draw_event(event, std::get<0>(_snake[_snake.size() - 1]), std::get<1>(_snake[_snake.size() - 1]), tail_orientation);
}

void game::Snake::add_score_to_events(std::queue<std::tuple<EventType, eventData>> &events)
{
    std::string score = "Score: " + std::to_string(_score);
    create_draw_string_event(events, 0, 20, score);
}

void game::Snake::add_food_to_events(std::queue<std::tuple<EventType, eventData>> &events)
{
    create_draw_event(events, std::get<0>(_food), std::get<1>(_food), "food");
}

std::queue<std::tuple<EventType, eventData>> game::Snake::tick()
{
    changeDirection();
    std::vector<std::string> newMap = map;
    if (_lose != true) {
        changeSnakePos();
    }
    add_snake_to_map(newMap, _snake);
    add_food_to_map(newMap, _food);
    std::queue<std::tuple<EventType, eventData>> events = transform_map_to_events(newMap);
    if (checkCollision()) {
        std::tuple<EventType, eventData> event = {EventType::LOSE, false};
        events.push(event);
        std::tuple<EventType, eventData> event2 = {EventType::DATA, true};
        events.push(event2);
        std::tuple<EventType, eventData> event3 = {EventType::LOSE, false};
        events.push(event3);
        std::cout << "You lost" << std::endl;
        _lose = true;
        return events;
    }
    add_score_to_events(events);
    checkFood();
    _ticks++;
    return events;
}
