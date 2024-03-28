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
    if (event.size() < 3)
        return packetError(event);
    event.pop();
    if (event.front().getType() != state::DATA)
        return packetError(event);
    std::size_t packetNb = event.front().getPacketNb();
    event.pop();
    if (event.front().getType() != state::DATA)
        return packetError(event);
    std::size_t packetNb2 = event.front().getPacketNb();
    event.pop();
    if (event.front().getType() != state::DATA)
        return packetError(event);
    std::string packetStr = event.front().getPacketStr();
    std::tuple draw = std::make_tuple(packetNb, packetNb2, packetStr);
    _draw.push_back(draw);
    event.pop();
    event.pop();
}

void graphic::AGraphic::readSound(std::queue<state::Event> &event)
{
    event.pop();
    if (event.front().getType() != state::DATA)
        return packetError(event);
    _sound.push_back(event.front().getPacketStr());
    event.pop();
}

void graphic::AGraphic::readTime(std::queue<state::Event> &event)
{
    event.pop();
    if (event.front().getType() != state::DATA)
        return packetError(event);
    _time = event.front().getPacketDecimal();
    event.pop();
}

void graphic::AGraphic::packetError(std::queue<state::Event> &event)
{
    std::cerr << "Error: Packet error" << std::endl;
}
