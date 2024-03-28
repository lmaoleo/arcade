/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Event
*/

#include "Event.hpp"

state::EventPacket::EventPacket()
{
    str = "";
    nb = 0;
    decimal = 0;
    boolean = false;
}

state::EventPacket::~EventPacket()
{
}

state::Event::Event(EventType type, std::string data)
{
    _type = type;
    _packet.str = data;
}

state::Event::Event(EventType type, std::size_t data)
{
    _type = type;
    _packet.nb = data;
}

state::Event::Event(EventType type, double data)
{
    _type = type;
    _packet.decimal = data;
}

state::Event::Event(EventType type, bool data)
{
    _type = type;
    _packet.boolean = data;
}

state::Event::~Event()
{
}

state::EventType state::Event::getType() const
{
    return _type;
}

std::string state::Event::getPacketStr() const
{
    return _packet.str;
}

std::size_t state::Event::getPacketNb() const
{
    return _packet.nb;
}

double state::Event::getPacketDecimal() const
{
    return _packet.decimal;
}

bool state::Event::getPacketBool() const
{
    return _packet.boolean;
}

void state::Event::setEventType(EventType type)
{
    _type = type;
}
