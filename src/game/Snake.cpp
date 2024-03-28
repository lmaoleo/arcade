/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Snake
*/

#include "Snake.hpp"

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

game::Snake::Snake()
{
}

game::Snake::~Snake()
{
}

static void create_draw_event(std::queue<state::Event> &events, std::size_t x, std::size_t y, std::string type)
{
    state::Event event = state::Event(state::EventType::DRAW, type);
}

static std::queue<state::Event> transform_map_to_events(std::vector<std::string> map)
{
    std::queue<state::Event> events;

    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < map[i].size(); j++) {
        }
    }
    return events;
}

std::queue<state::Event> game::Snake::tick()
{
    std::queue<state::Event> events;
    return events;
}
