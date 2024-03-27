/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Agraphic
*/

#include "AGraphic.hpp"

static const std::map<state::EventType, void (graphic::AGraphic::*)(std::queue<state::Event> &)> eventFuncs = {
    {state::WIN, &graphic::AGraphic::readWin},
    {state::LOSE, &graphic::AGraphic::readLose},
    {state::PAUSE, &graphic::AGraphic::readPause},
    {state::DRAW, &graphic::AGraphic::readDraw},
    {state::PLAY_SOUND, &graphic::AGraphic::readSound},
    {state::DELTA_TIME, &graphic::AGraphic::readTime},
};

graphic::AGraphic::AGraphic()
{
    _win = false;
    _lose = false;
    _pause = false;
    _time = 0;
}

graphic::AGraphic::AGraphic(state::Keybinds &keys)
{
    _keys = keys;
    _win = false;
    _lose = false;
    _pause = false;
    _time = 0;
}

graphic::AGraphic::~AGraphic()
{
}

void graphic::AGraphic::readEvent(std::queue<state::Event> event)
{
    while (!event.empty()) {
        auto it = eventFuncs.find(event.front().getType());
        if (it != eventFuncs.end())
            (this->*it->second)(event);
        else
            packetError(event);
    }
}

void graphic::AGraphic::readWin(std::queue<state::Event> &event)
{
    event.pop();
    _win = event.front().getPacketBool();
    event.pop();
}

void graphic::AGraphic::readLose(std::queue<state::Event> &event)
{
    event.pop();
    _lose = event.front().getPacketBool();
    event.pop();
}

void graphic::AGraphic::readPause(std::queue<state::Event> &event)
{
    event.pop();
    _pause = event.front().getPacketBool();
    event.pop();
}

void graphic::AGraphic::readDraw(std::queue<state::Event> &event)
{
    event.pop();
    
}
