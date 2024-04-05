/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Agraphic
*/

#include "AGraphic.hpp"

static const std::map<EventType, void (graphic::AGraphic::*)(std::queue<std::tuple<EventType, eventData>> &)> eventFuncs = {
    {DATA, &graphic::AGraphic::packetError},
    {WIN, &graphic::AGraphic::readWin},
    {LOSE, &graphic::AGraphic::readLose},
    {PAUSE, &graphic::AGraphic::readPause},
    {DRAW, &graphic::AGraphic::readDraw},
    {DRAW_STRING, &graphic::AGraphic::readDrawString},
    {DELTA_TIME, &graphic::AGraphic::readTime},
    {SET_GAME, &graphic::AGraphic::readSetElm},
    {SET_GRAPHIC, &graphic::AGraphic::readSetElm},
    {CHANGE_COLOR, &graphic::AGraphic::readColor},
};

void graphic::AGraphic::readEvent(std::queue<std::tuple<EventType, eventData>> &event)
{
    while (!event.empty()) {
        auto it = eventFuncs.find(std::get<EventType>(event.front()));
        if (it != eventFuncs.end()) {
            (this->*it->second)(event);
        } else {
            packetError(event);
        }
    }
}

void graphic::AGraphic::readWin(std::queue<std::tuple<EventType, eventData>> &event)
{
    event.pop();
    _win = std::get<bool>(std::get<1>(event.front()));
    event.pop();
    event.pop();
}

void graphic::AGraphic::readLose(std::queue<std::tuple<EventType, eventData>> &event)
{
    event.pop();
    _lose = std::get<bool>(std::get<1>(event.front()));
    event.pop();
    event.pop();
}

void graphic::AGraphic::readPause(std::queue<std::tuple<EventType, eventData>> &event)
{
    event.pop();
    _pause = std::get<bool>(std::get<1>(event.front()));
    event.pop();
    event.pop();
}

void graphic::AGraphic::readDraw(std::queue<std::tuple<EventType, eventData>> &event)
{
    if (event.size() < 3)
        return packetError(event);
    event.pop();
    if (std::get<0>(event.front()) != DATA)
        return packetError(event);

    std::size_t packetNb = std::get<std::size_t>(std::get<1>(event.front()));
    event.pop();

    if (std::get<0>(event.front()) != DATA)
        return packetError(event);
    std::size_t packetNb2 = std::get<std::size_t>(std::get<1>(event.front()));
    event.pop();

    if (std::get<0>(event.front()) != DATA)
        return packetError(event);
    short packetStr = std::get<short>(std::get<1>(event.front()));
    event.pop();

    std::tuple draw = std::make_tuple(packetNb, packetNb2, packetStr, _color);
    _draw.push_back(draw);
    event.pop();
}

void graphic::AGraphic::readDrawString(std::queue<std::tuple<EventType, eventData>> &event)
{
    if (event.size() < 3)
        return packetError(event);
    event.pop();
    if (std::get<EventType>(event.front()) != DATA)
        return packetError(event);

    std::size_t packetNb = std::get<std::size_t>(std::get<1>(event.front()));
    event.pop();

    if (std::get<0>(event.front()) != DATA)
        return packetError(event);
    std::size_t packetNb2 = std::get<std::size_t>(std::get<1>(event.front()));
    event.pop();

    if (std::get<0>(event.front()) != DATA)
        return packetError(event);
    std::string packetStr = std::get<std::string>(std::get<1>(event.front()));
    event.pop();

    if (std::get<0>(event.front()) != DATA)
        return packetError(event);
    bool packetBool = std::get<bool>(std::get<1>(event.front()));
    event.pop();

    std::tuple draw = std::make_tuple(packetNb, packetNb2, packetStr, packetBool);
    _draw_str.push_back(draw);
    event.pop();
}

void graphic::AGraphic::readTime(std::queue<std::tuple<EventType, eventData>> &event)
{
    event.pop();
    if (std::get<EventType>(event.front()) != DATA)
        return packetError(event);
    double packetDecimalPtr = std::get<double>(std::get<1>(event.front()));
    _time = packetDecimalPtr;
    event.pop();
    event.pop();
}

void graphic::AGraphic::readSetElm(std::queue<std::tuple<EventType, eventData>> &event)
{
    event.pop();
    if (std::get<EventType>(event.front()) != DATA)
        return packetError(event);
    std::string packetStr = std::get<std::string>(std::get<1>(event.front()));
    event.pop();
    event.pop();
}

void graphic::AGraphic::readColor(std::queue<std::tuple<EventType, eventData>> &event)
{
    event.pop();
    if (std::get<EventType>(event.front()) != DATA)
        return packetError(event);
    short packetColor = std::get<unsigned int>(std::get<1>(event.front()));
    _color = packetColor;
    event.pop();
    event.pop();
}

void graphic::AGraphic::packetError(std::queue<std::tuple<EventType, eventData>> &event)
{
    std::cerr << "Packet error" << std::endl;
}
