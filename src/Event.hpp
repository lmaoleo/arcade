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
        WIN,            /* 0 packet  */
        LOSE,           /* 0 packet  */
        PAUSE,          /* 1 packet  */
        DRAW,           /* 3 packets */
        PLAY_SOUND,     /* 1 packet  */
        DELTA_TIME,     /* 1 packet  */
    };

    typedef union EventPacket {
        std::string str;
        std::size_t nb;
        double decimal;
        bool boolean;
        EventPacket();
        ~EventPacket();
    } EventPacket;

    class Event {
        public:
            Event(EventType type, std::string data);
            Event(EventType type, std::size_t data);
            Event(EventType type, double data);
            Event(EventType type, bool data);
            ~Event();

            EventType getType() const;

            std::string getPacketStr() const;
            std::size_t getPacketNb() const;
            double getPacketDecimal() const;
            bool getPacketBool() const;

        private:
            EventType _type;
            EventPacket _packet;
    };
}

#endif /* !EVENT_HPP_ */