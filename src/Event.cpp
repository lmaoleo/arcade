/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Event
*/

#include "Event.hpp"

state::Event::Event() : _packet(std::nullopt) {}

state::Event::Event(EventType type, const std::string& data) : _type(type), _packet(data) {}

state::Event::Event(EventType type, std::size_t data) : _type(type), _packet(data) {}

state::Event::Event(EventType type, double data) : _type(type), _packet(data) {}

state::Event::Event(EventType type, bool data) : _type(type), _packet(data) {}

state::Event::~Event() {
};

const std::string state::Event::getPacketStr() const {
    return *std::get_if<std::string>(&_packet);
}

const std::size_t state::Event::getPacketNb() const {
    return *std::get_if<std::size_t>(&_packet);
}

const double state::Event::getPacketDecimal() const {
    return *std::get_if<double>(&_packet);
}

const bool state::Event::getPacketBool() const {
    return *std::get_if<bool>(&_packet);
}

void state::Event::setEventType(EventType type) {
    _type = type;
}

state::EventType state::Event::getType() const {
    return _type;
}