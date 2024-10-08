/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Pacman
*/

#include "Pacman.hpp"
#include <iostream>

static std::vector<std::string> PacManFoodMap = {
    "###################",
    "#..o.....#......o.#",
    "#.##.###.#.###.##.#",
    "#.................#",
    "#.##.#.#####.#.##.#",
    "#....#...#...#....#",
    "####.###.#.###.####",
    "   #.#.......#.#   ",
    "####.#.#####.#.####",
    "    ...#   #...    ",
    "####.#.#####.#.####",
    "   #.#...o...#.#   ",
    "####.#.#####.#.####",
    "#........#........#",
    "#.##.###.#.###.##.#",
    "#.o#...........#..#",
    "##.#.#.#####.#.#.##",
    "#....#...#...#....#",
    "#.######.#.######.#",
    "#..............o..#",
    "###################"
};

static std::vector<std::string> PacManMap = {
    "###################",
    "#        #        #",
    "# ## ### # ### ## #",
    "#                 #",
    "# ## # ##### # ## #",
    "#    #   #   #    #",
    "#### ### # ### ####",
    "   # #       # #   ",
    "#### # ##h## # ####",
    " X     #   #    X  ",
    "#### # ##### # ####",
    "   # #       # #   ",
    "#### # ##### # ####",
    "#        #        #",
    "# ## ### # ### ## #",
    "#  #           #  #",
    "## # # ##### # # ##",
    "#    #   #   #    #",
    "# ###### # ###### #",
    "#                 #",
    "###################"
};

static const std::map<char, std::string> charmap = {
    {'#', "pac_wall"},
    {'d', "pac_down"},
    {'u', "pac_up"},
    {'l', "pac_left"},
    {'>', "pac_right"},
    {'G', "ghost"},
    {'.', "pac_food"},
    {' ', "empty"},
    {'h', "door"},
    {'X', "bad_wall"},
    {'o', "pac_gum"}
};

static const std::map<std::string, char> reverseCharMap = {
    {"pac_wall", '#'},
    {"pac_down", 'd'},
    {"pac_up", 'u'},
    {"pac_left", 'l'},
    {"pac_right", '>'},
    {"ghost", 'G'},
    {"pac_food", '.'},
    {"empty", ' '},
    {"door", 'h'},
    {"bad_wall", 'X'},
    {"pac_gum", 'o'}
};

static const std::tuple<std::string, unsigned int> pac_food = {
    "    "\
    " ## "\
    " ## "\
    "    ",
    rgbToInt(255, 255, 255, 255)
};

static const std::tuple<std::string, unsigned int> pac_wall = {
    "####"\
    "#  #"\
    "#  #"\
    "####",
    rgbToInt(0, 200, 150, 255)
};

static const std::tuple<std::string, unsigned int> empty = {
    "    "\
    "    "\
    "    "\
    "    ",
    rgbToInt(0, 0, 0, 0)
};

static const std::tuple<std::string, unsigned int> pac_right = {
    "####"\
    "##  "\
    "##  "\
    "####",
    rgbToInt(255, 255, 255, 0)
};

static const std::tuple<std::string, unsigned int> pac_left = {
    "####"\
    "  ##"\
    "  ##"\
    "####",
    rgbToInt(255, 255, 255, 0)
};

static const std::tuple<std::string, unsigned int> pac_up = {
    "#  #"\
    "#  #"\
    "####"\
    "####",
    rgbToInt(255, 255, 255, 0)
};

static const std::tuple<std::string, unsigned int> pac_down = {
    "####"\
    "####"\
    "#  #"\
    "#  #",
    rgbToInt(255, 255, 255, 0)
};

static const std::tuple<std::string, unsigned int> ghost = {
    "####"\
    "#  #"\
    "#  #"\
    "#  #",
    rgbToInt(233, 0, 150, 100)
};

static const std::tuple<std::string, unsigned int> door = {
    "####"\
    "#  #"\
    "####"\
    "####",
    rgbToInt(128,128,250,128)
};

static const std::tuple<std::string, unsigned int> pac_gum = {
    " #  "\
    " ##"\
    " ## "\
    "  # ",
    rgbToInt(255, 255, 255, 255)
};

static const std::tuple<std::string, unsigned int> bad_wall = {
    "    "\
    "    "\
    "    "\
    "    ",
    rgbToInt(0, 0, 0, 0)
};

static const std::map<std::string, std::tuple<std::string, unsigned int>> charToTile = {
    {".", pac_food},
    {"#", pac_wall},
    {" ", empty},
    {">", pac_right},
    {"l", pac_left},
    {"u", pac_up},
    {"d", pac_down},
    {"h", door},
    {"G", ghost},
    {"o", pac_gum},
    {"X", bad_wall}
};

static unsigned int rgbToInt(unsigned int a, unsigned short r, unsigned short g, unsigned short b)
{
    return (a << 24) + (r << 16) + (g << 8) + b;
}

extern "C" {
    game::Pacman *createGame(std::shared_ptr<std::map<std::string, bool>> &keybinds, int &score, std::string &username)
    {
        (void)username;
        return new game::Pacman(keybinds, score, username);
    }
}

std::vector<std::tuple<std::size_t, std::size_t, bool>> game::Pacman::generateFood()
{
    std::vector<std::tuple<std::size_t, std::size_t, bool>> food;
    for (std::size_t i = 0; i < PacManFoodMap.size(); i++) {
        for (std::size_t j = 0; j < PacManFoodMap[i].size(); j++) {
            if (PacManFoodMap[i][j] == '.') {
                food.push_back(std::make_tuple(j, i, false));
            }
            if (PacManFoodMap[i][j] == 'o') {
                _pacgums.push_back(std::make_tuple(j, i, false));
            }
        }
    }
    _food = food;
    return food;
}

game::Pacman::Pacman(std::shared_ptr<std::map<std::string, bool>> &key, int &score, std::string &username) : _iscore(score), _username(username)
{
    _keys = key;
    _score = 0;
    _direction = std::make_tuple(1, 0);
    _headDirection = "pac_right";
    _Pacman = std::make_tuple(9, 15);
    generateFood();
    _ticks = 0;
    _ghosts = {{8, 9}, {9, 9}, {9, 9}, {10, 9}};
    _ghostsOrigins = {{8, 9}, {9, 9}, {9, 9}, {10, 9}};
    _startTime = std::chrono::high_resolution_clock::now();
    _pacmanDelay = 0.08;
    _ghostDelay = 0.08;
    _pacmanMoveTime = 0;
    _ghostMoveTime = 0;
    _gumstate = 0;
}

game::Pacman::~Pacman()
{
}

double game::Pacman::getElapsedTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - _startTime;
    return elapsedTime.count();
}

void game::Pacman::send_packet(int type, std::vector<std::tuple<std::string, bool, int>> &libs, std::queue<std::tuple<EventType, eventData>> &events)
{
    EventType to_send = EventType::SET_GAME;
    if (type == 1) {
        to_send = EventType::SET_GRAPHIC;
    }
    for (std::size_t i = 0; i < libs.size(); i++) {
        if (std::get<1>(libs[i]) == true && std::get<2>(libs[i]) == type) {
            std::tuple<EventType, eventData> event = {to_send, false};
            std::tuple<EventType, eventData> packet = {EventType::DATA, "lib/" + std::get<0>(libs[i])};
            std::tuple<EventType, eventData> event2 = {to_send, false};
            events.push(event);
            events.push(packet);
            events.push(event2);
        }
    }
}

void game::Pacman::changeDirection()
{
    if (_keys->at("UP") == true) {
        _direction = std::make_tuple(0, -1);
        _headDirection = "pac_up";
    }
    if (_keys->at("DOWN") == true) {
        _direction = std::make_tuple(0, 1);
        _headDirection = "pac_down";
    }
    if (_keys->at("LEFT") == true ) {
        _direction = std::make_tuple(-1, 0);
        _headDirection = "pac_left";
    }
    if (_keys->at("RIGHT") == true) {
        _direction = std::make_tuple(1, 0);
        _headDirection = "pac_right";
    }
    if (_keys->at("R") == true) {
        _score = 0;
        _iscore = 0;
        _Pacman = std::make_tuple(9, 15);
        _direction = std::make_tuple(1, 0);
        _ghosts = {{8, 9}, {9, 9}, {9, 9}, {10, 9}};
        _ghostsOrigins = {{8, 9}, {9, 9}, {9, 9}, {10, 9}};
        _startTime = std::chrono::high_resolution_clock::now();
        _pacmanMoveTime = 0.08;
        _ghostMoveTime = 0.08;
        _headDirection = "pac_right";
        _food = generateFood();
        _ghosts = _ghostsOrigins;
        _lose = false;
    }
}

bool game::Pacman::isGameOver()
{
    for (std::size_t i = 0; i < _ghosts.size(); i++) {
        if (_Pacman == _ghosts[i]) {
            if (_gumstate > 0) {
                _ghosts[i] = _ghostsOrigins[i];
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

bool game::Pacman::checkCollision(std::tuple<std::size_t, std::size_t> pos)
{
    if (PacManMap[std::get<1>(pos)][std::get<0>(pos)] == '#') {
        return false;
    }
    if (PacManMap[std::get<1>(pos)][std::get<0>(pos)] == 'X') {
        return false;
    }
    return true;
}

void game::Pacman::checkFood()
{
    for (std::size_t i = 0; i < _food.size(); i++) {
        if (_Pacman == std::make_tuple(std::get<0>(_food[i]), std::get<1>(_food[i])) && std::get<2>(_food[i]) == false) {
            _score++;
            _iscore = _score;
            _food[i] = std::make_tuple(std::get<0>(_food[i]), std::get<1>(_food[i]), true);
        }
        if (_Pacman == std::make_tuple(std::get<0>(_pacgums[i]), std::get<1>(_pacgums[i])) && std::get<2>(_pacgums[i]) == false) {
            _score += 1;
            _iscore = _score;
            _gumstate = 0.02;
            _moveTime = 0;
            _pacgums[i] = std::make_tuple(std::get<0>(_pacgums[i]), std::get<1>(_pacgums[i]), true);
        }
    }
    if (_score % 177 == 0 && _score != 0) {
        generateFood();
    }
}

bool checkCollisionPac(std::tuple<std::size_t, std::size_t> pos)
{
    if (PacManMap[std::get<1>(pos)][std::get<0>(pos)] == '#' || PacManMap[std::get<1>(pos)][std::get<0>(pos)] == 'h') {
        return false;
    }
    return true;
}

void game::Pacman::changePacmanPos()
{
    std::tuple newPacmanPos = std::make_tuple(std::get<0>(_Pacman) + std::get<0>(_direction), std::get<1>(_Pacman) + std::get<1>(_direction));
    if (checkCollisionPac(newPacmanPos)) {
        if (std::get<0>(newPacmanPos) == 0 && std::get<1>(newPacmanPos) == 9 && std::get<0>(_direction) == static_cast<unsigned long>(-1)) {
            _Pacman = std::make_tuple(19, 9);
            _direction = std::make_tuple(-1, 0);
            _headDirection = "pac_left";
        } else if (std::get<0>(newPacmanPos) == 19 && std::get<1>(newPacmanPos) == 9 && std::get<0>(_direction) == 1) {
            _Pacman = std::make_tuple (0, 9);
            _direction = std::make_tuple(1, 0);
            _headDirection = "pac_right";
        } else {
            _Pacman = newPacmanPos;
        }
    }
}

void game::Pacman::add_Pacman_to_map(std::vector<std::string> &map, std::tuple<std::size_t, std::size_t> Pacman)
{
    map[std::get<1>(Pacman)][std::get<0>(Pacman)] = reverseCharMap.at(_headDirection);
}

void add_ghosts_to_map(std::vector<std::string> &map, std::vector<std::tuple<std::size_t, std::size_t>> ghosts)
{
    for (std::size_t i = 0; i < ghosts.size(); i++) {
        map[std::get<1>(ghosts[i])][std::get<0>(ghosts[i])] = 'G';
    }
}

void add_food_to_map(std::vector<std::string> &map, std::vector<std::tuple<std::size_t, std::size_t, bool>> food)
{
    for (std::size_t i = 0; i < food.size(); i++) {
        if (std::get<2>(food[i]) == false) {
            map[std::get<1>(food[i])][std::get<0>(food[i])] = '.';
        }
    }
}

void add_pacgums_to_map(std::vector<std::string> &map, std::vector<std::tuple<std::size_t, std::size_t, bool>> pacgums)
{
    for (std::size_t i = 0; i < pacgums.size(); i++) {
        if (std::get<2>(pacgums[i]) == false) {
            map[std::get<1>(pacgums[i])][std::get<0>(pacgums[i])] = 'o';
        }
    };
}

static void create_draw_event(std::queue<std::tuple<EventType, eventData>> &events, std::size_t x, std::size_t y, short tile, unsigned int color = 0)
{
    std::tuple<EventType, eventData> color_event_start = {EventType::CHANGE_COLOR, false};
    std::tuple<EventType, eventData> packetColor = {EventType::DATA, color};
    std::tuple<EventType, eventData> color_event_end = {EventType::CHANGE_COLOR, false};
    std::tuple<EventType, eventData> draw_event_start = {EventType::DRAW, false};
    std::tuple<EventType, eventData> packetX = {EventType::DATA, x};
    std::tuple<EventType, eventData> packetY = {EventType::DATA, y};
    std::tuple<EventType, eventData> packetType = {EventType::DATA, tile};
    std::tuple<EventType, eventData> draw_event_end = {EventType::DRAW, false};
    events.push(color_event_start);
    events.push(packetColor);
    events.push(color_event_end);
    events.push(draw_event_start);
    events.push(packetX);
    events.push(packetY);
    events.push(packetType);
    events.push(draw_event_end);
}

static void create_draw_string_event(std::queue<std::tuple<EventType, eventData>> &events, std::size_t x, std::size_t y, std::string score)
{
    std::tuple<EventType, eventData> event = {EventType::DRAW_STRING, false};
    std::tuple<EventType, eventData> packetX = {EventType::DATA, x};
    std::tuple<EventType, eventData> packetY = {EventType::DATA, y};
    std::tuple<EventType, eventData> packetScore = {EventType::DATA, score};
    std::tuple<EventType, eventData> eventselect = {EventType::DATA, false};
    std::tuple<EventType, eventData> event2 = {EventType::DRAW_STRING, false};
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetScore);
    events.push(eventselect);
    events.push(event2);
}

std::queue<std::tuple<EventType, eventData>> game::Pacman::transform_map_to_events(std::vector<std::string> map)
{
    std::queue<std::tuple<EventType, eventData>> events;
    std::tuple<std::string, unsigned int> drawingTile;

    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            drawingTile = charToTile.at(std::string(1, map[y][x]));
            create_draw_event(events, x, y, stringToShort(std::get<0>(drawingTile)), std::get<1>(drawingTile));
        }
    }
    return events;
}

void game::Pacman::add_score_to_events(std::queue<std::tuple<EventType, eventData>> &events)
{
    std::string score = "Score: " + std::to_string(_score);
    create_draw_string_event(events, 0, 22, score);
}

void game::Pacman::movesGhostsRandomDirections()
{
    for (std::size_t i = 0; i < _ghosts.size(); i++) {
        std::size_t random = rand() % 4;
        if (random == 0) {
            if (checkCollision(std::make_tuple(std::get<0>(_ghosts[i]) + 1, std::get<1>(_ghosts[i])))) {
                _ghosts[i] = std::make_tuple(std::get<0>(_ghosts[i]) + 1, std::get<1>(_ghosts[i]));
            }
        } else if (random == 1) {
            if (checkCollision(std::make_tuple(std::get<0>(_ghosts[i]) - 1, std::get<1>(_ghosts[i])))) {
                _ghosts[i] = std::make_tuple(std::get<0>(_ghosts[i]) - 1, std::get<1>(_ghosts[i]));
            }
        } else if (random == 2) {
            if (checkCollision(std::make_tuple(std::get<0>(_ghosts[i]), std::get<1>(_ghosts[i]) + 1))) {
                _ghosts[i] = std::make_tuple(std::get<0>(_ghosts[i]), std::get<1>(_ghosts[i]) + 1);
            }
        } else if (random == 3) {
            if (checkCollision(std::make_tuple(std::get<0>(_ghosts[i]), std::get<1>(_ghosts[i]) - 1))) {
                _ghosts[i] = std::make_tuple(std::get<0>(_ghosts[i]), std::get<1>(_ghosts[i]) - 1);
            }
        }
    }
}

std::queue<std::tuple<EventType, eventData>> displayLoseScreen(int score, std::string username)
{
    std::queue<std::tuple<EventType, eventData>> events;

    create_draw_string_event(events, 10, 10, username + " You lost...");
    create_draw_string_event(events, 10, 11, "Press R to restart");
    create_draw_string_event(events, 10, 12, "Score: " + std::to_string(score));
    return events;
}

std::queue<std::tuple<EventType, eventData>> game::Pacman::tick(double delta)
{
    if (_gumstate != 0) {
        _moveTime += delta;
    }
    _beforeMoveTime += delta;
    _pacmanMoveTime += delta;
    _ghostMoveTime += delta;

    changeDirection();
    _lose = isGameOver();
    if (_lose == true) {
        return displayLoseScreen(_score, _username);
    }
    std::vector<std::string> newMap = PacManMap;
    if (_moveTime > 5) {
        _gumstate = 0;
        _moveTime = 0;
    }
    if (_pacmanMoveTime > _pacmanDelay - _gumstate) {
        changePacmanPos();
        _pacmanMoveTime = 0;
    }
    if (_beforeMoveTime > 10) {
        if (_ghostMoveTime > _ghostDelay + _gumstate) {
            movesGhostsRandomDirections();
            _ghostMoveTime = 0;
        }
    }
    add_food_to_map(newMap, _food);
    add_pacgums_to_map(newMap, _pacgums);
    add_ghosts_to_map(newMap, _ghosts);
    add_Pacman_to_map(newMap, _Pacman);
    _events = transform_map_to_events(newMap);
    add_score_to_events(_events);
    checkFood();
    _ticks++;
    return _events;
}
