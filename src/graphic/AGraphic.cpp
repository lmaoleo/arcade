/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Agraphic
*/

#include "AGraphic.hpp"

static const std::map<EventType, void (graphic::AGraphic::*)(std::queue<std::tuple<EventType, eventData>> &)> eventFuncs = {
    {DATA, &graphic::AGraphic::packetError},
    {DRAW, &graphic::AGraphic::readDraw},
    {DRAW_STRING, &graphic::AGraphic::readDrawString},
    {SET_GAME, &graphic::AGraphic::readSetGame},
    {SET_GRAPHIC, &graphic::AGraphic::readSetGraphic},
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

void graphic::AGraphic::readDraw(std::queue<std::tuple<EventType, eventData>> &event)
{
    std::tuple<size_t, size_t, short, unsigned int> tmp;

    std::cout << "readDraw" << std::endl;
    event.pop();
    for (std::size_t i = 0; i < 3; i++) {
        if (event.empty() == true)
            throw IGraphic::packetError();
        if (std::get<0>(event.front()) != DATA)
            throw IGraphic::packetError();
        if (i == 0) {
            std::get<0>(tmp) = std::get<std::size_t>(std::get<1>(event.front()));
        }
        if (i == 1) {
            std::get<1>(tmp) = std::get<std::size_t>(std::get<1>(event.front()));
        }
        if (i == 2) {
            std::get<2>(tmp) = std::get<short>(std::get<1>(event.front()));
        }
        event.pop();
    }
    std::get<3>(tmp) = _color;
    _draw.push_back(tmp);
    event.pop();

    std::cout << "readDraw end" << std::endl;
}

void graphic::AGraphic::readDrawString(std::queue<std::tuple<EventType, eventData>> &event)
{

    // std::cout << "readDrawString" << std::endl;
    std::tuple<size_t, size_t, std::string, bool> tmp;

    // std::cout << "draw str" << std::endl;
    event.pop();
    for (std::size_t i = 0; i < 4; i++) {
        if (event.empty() == true)
            throw IGraphic::packetError();
        if (std::get<0>(event.front()) != DATA)
            throw IGraphic::packetError();
        if (i == 0) {
            std::get<0>(tmp) = std::get<std::size_t>(std::get<1>(event.front()));
        }
        if (i == 1) {
            std::get<1>(tmp) = std::get<std::size_t>(std::get<1>(event.front()));
        }
        if (i == 2) {
            std::get<2>(tmp) = std::get<std::string>(std::get<1>(event.front()));
        }
        if (i == 3) {
            std::get<3>(tmp) = std::get<bool>(std::get<1>(event.front()));
        }
        event.pop();
    }
    _draw_str.push_back(tmp);
    event.pop();
    // std::cout << "succes" << std::endl;
    // std::cout << "readDrawString end" << std::endl;
}

void graphic::AGraphic::readSetGame(std::queue<std::tuple<EventType, eventData>> &event)
{
    event.pop();
    event.pop();
    event.pop();
}

void graphic::AGraphic::readSetGraphic(std::queue<std::tuple<EventType, eventData>> &event)
{
    event.pop();
    event.pop();
    event.pop();
}

void graphic::AGraphic::readColor(std::queue<std::tuple<EventType, eventData>> &event)
{
    std::cout << "readColor" << std::endl;
    event.pop();
    if (std::get<EventType>(event.front()) != DATA)
        return packetError(event);
    short packetColor = std::get<unsigned int>(std::get<1>(event.front()));
    _color = packetColor;
    event.pop();
    event.pop();
    std::cout << "readColor end" << std::endl;
}

void graphic::AGraphic::packetError(std::queue<std::tuple<EventType, eventData>> &event)
{
    std::cerr << "Packet error" << std::endl;
}
