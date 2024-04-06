/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

    #include <variant>
    #include <optional>
    #include <string>

enum EventType {
    DATA = 0,           /*   packet  */
    DRAW = 1,           /* 3 packets */
    DRAW_STRING = 2,    /* 4 packets */
    CHANGE_COLOR = 3,   /* 1 packet  */
    SET_GAME = 4,       /* 1 packet  */
    SET_GRAPHIC = 5     /* 1 packet  */
};

typedef std::variant<std::nullopt_t, std::string, std::size_t, short, double, bool, unsigned int> eventData;

#endif /* !EVENT_HPP_ */