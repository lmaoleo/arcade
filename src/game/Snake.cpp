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
    "####################",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "####################"
};

static const std::map<char, std::string> charmap = {
    {'#', "wall"},
    {'d', "snake_head_down"},
    {'u', "snake_head_up"},
    {'l', "snake_head_left"},
    {'r', "snake_head_right"},
    {'b', "snake_body"},
    {'f', "food"},
    {' ', "empty"},
};

game::Snake::Snake()
{
}

game::Snake::~Snake()
{
}

static void create_draw_event(std::queue<state::Event> &events, std::size_t x, std::size_t y, std::string type)
{
    state::Event event;
    event.setEventType(state::EventType::DRAW);
    state::Event packetX = state::Event(state::EventType::DATA, x);
    state::Event packetY = state::Event(state::EventType::DATA, y);
    state::Event packetType = state::Event(state::EventType::DATA, type);
    state::Event event2;
    event.setEventType(state::EventType::DRAW);
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetType);
    events.push(event2);
}

static std::queue<state::Event> transform_map_to_events(std::vector<std::string> map)
{
    std::queue<state::Event> events;
    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            create_draw_event(events, x, y, charmap.at(map[y][x]));
        }
    }
    std::cout << "events.size() = " << events.size() << std::endl;
    std::cout << "events.front().getType() = " << events.front().getType() << std::endl;
    return events;
}

std::queue<state::Event> game::Snake::tick()
{
    std::queue<state::Event> events = transform_map_to_events(map);
    return events;
}
