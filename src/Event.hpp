/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

    #include <iostream>
    #include <map>
    #include <variant>
    #include <optional>

/*
    graphic_next
    graphic_prev
    game_next
    game_prev
    pause
    quit
    up
    down
    left
    right
    action_1
    action_2
*/

namespace state {
    enum EventType {
        DATA,           /*   packet  */
        WIN,            /* 1 packet  */
        LOSE,           /* 1 packet  */
        PAUSE,          /* 1 packet  */
        DRAW,           /* 3 packets */
        PLAY_SOUND,     /* 1 packet  */
        DELTA_TIME,     /* 1 packet  */
    };

    class Event {
        public:
        typedef std::variant<std::nullopt_t, std::string, std::size_t, double, bool> EventPacket;

        Event();
        Event(EventType type, const std::string& data);
        Event(EventType type, std::size_t data);
        Event(EventType type, double data);
        Event(EventType type, bool data);
        virtual ~Event();

        EventType getType() const;

        const std::string getPacketStr() const;
        const std::size_t getPacketNb() const;
        const double getPacketDecimal() const;
        const bool getPacketBool() const;

        void setEventType(EventType type);

        private:
            EventType _type;
            EventPacket _packet;
    };
}

#endif /* !EVENT_HPP_ */