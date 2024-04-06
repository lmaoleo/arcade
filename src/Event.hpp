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
    DATA,           /*   packet  */
    DRAW,           /* 3 packets */
    DRAW_STRING,    /* 4 packets */
    CHANGE_COLOR,   /* 1 packet  */
    SET_GAME,       /* 1 packet  */
    SET_GRAPHIC     /* 1 packet  */
};

typedef std::variant<std::nullopt_t, std::string, std::size_t, short, double, bool, unsigned int> eventData;

#endif /* !EVENT_HPP_ */