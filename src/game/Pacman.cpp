/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** Pacman
*/

#include "Pacman.hpp"

static std::vector<std::string> PacManFoodMap = {
    "###################",
    "#........#........#",
    "#.##.###.#.###.##.#",
    "#.................#",
    "#.##.#.#####.#.##.#",
    "#....#...#...#....#",
    "####.###.#.###.####",
    "   #.#.......#.#   ",
    "####.#.#####.#.####",
    "    ...#   #...    ",
    "####.#.#####.#.####",
    "   #.#.......#.#   ",
    "####.#.#####.#.####",
    "#........#........#",
    "#.##.###.#.###.##.#",
    "#..#...........#..#",
    "##.#.#.#####.#.#.##",
    "#....#...#...#....#",
    "#.######.#.######.#",
    "#.................#",
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
    "#### # ##### # ####",
    "       #   #       ",
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
    {'P', "pacman"},
    {'.', "pac_food"},
    {' ', "empty"},
};

extern "C" {
    game::Pacman *createGame(std::shared_ptr<state::Keybinds> &keybinds)
    {
        return new game::Pacman(keybinds);
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
        }
    }
    _food = food;
    return food;
}

game::Pacman::Pacman(std::shared_ptr<state::Keybinds> &key)
{
    _keys = key;
    _score = 0;
    _direction = std::make_tuple(1, 0);
    _headDirection = "pac_right";
    _Pacman = std::make_tuple(9, 15);
    generateFood();
    _ticks = 0;
    _ghosts = {{8, 9}, {9, 9}, {10, 9}};
}

game::Pacman::~Pacman()
{
}

void game::Pacman::changeDirection()
{
    if (_keys->isKeyPressed("UP")) {
        _direction = std::make_tuple(0, -1);
        _headDirection = "pac_up";
    }
    if (_keys->isKeyPressed("DOWN")) {
        _direction = std::make_tuple(0, 1);
        _headDirection = "pac_down";
    }
    if (_keys->isKeyPressed("LEFT")) {
        _direction = std::make_tuple(-1, 0);
        _headDirection = "pac_left";
    }
    if (_keys->isKeyPressed("RIGHT")) {
        _direction = std::make_tuple(1, 0);
        _headDirection = "pac_right";
    }
    _keys->keyPressed("UP", false);
    _keys->keyPressed("DOWN", false);
    _keys->keyPressed("LEFT", false);
    _keys->keyPressed("RIGHT", false);
}

bool game::Pacman::checkCollision(std::tuple<std::size_t, std::size_t> pos)
{
    if (PacManMap[std::get<1>(pos)][std::get<0>(pos)] == '#') {
        return false;
    }
    return true;
}

void game::Pacman::checkFood()
{
    for (std::size_t i = 0; i < _food.size(); i++) {
        if (_Pacman == std::make_tuple(std::get<0>(_food[i]), std::get<1>(_food[i])) && std::get<2>(_food[i]) == false) {
            _score++;
            _food[i] = std::make_tuple(std::get<0>(_food[i]), std::get<1>(_food[i]), true);
        }
    }
    if (_score % 177 == 0 && _score != 0) {
        generateFood();
    }
}

void game::Pacman::changePacmanPos()
{
    std::tuple newPacmanPos = std::make_tuple(std::get<0>(_Pacman) + std::get<0>(_direction), std::get<1>(_Pacman) + std::get<1>(_direction));
    if (checkCollision(newPacmanPos)) {
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

void add_Pacman_to_map(std::vector<std::string> &map, std::tuple<std::size_t, std::size_t> Pacman)
{
    map[std::get<1>(Pacman)][std::get<0>(Pacman)] = 'P';
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

static void create_draw_event(std::queue<state::Event> &events, std::size_t x, std::size_t y, std::string type)
{
    state::Event event;
    event.setEventType(state::EventType::DRAW);
    state::Event packetX = state::Event(state::EventType::DATA, x);
    state::Event packetY = state::Event(state::EventType::DATA, y);
    state::Event packetType = state::Event(state::EventType::DATA, type);
    state::Event event2;
    event2.setEventType(state::EventType::DRAW);
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetType);
    events.push(event2);
}

static void create_draw_string_event(std::queue<state::Event> &events, std::size_t x, std::size_t y, std::string score)
{
    state::Event event;
    event.setEventType(state::EventType::DRAW_STRING);
    state::Event packetX = state::Event(state::EventType::DATA, x);
    state::Event packetY = state::Event(state::EventType::DATA, y);
    state::Event packetType = state::Event(state::EventType::DATA, score);
    state::Event selected = state::Event(state::EventType::DATA, false);
    state::Event event2;
    event2.setEventType(state::EventType::DRAW_STRING);
    events.push(event);
    events.push(packetX);
    events.push(packetY);
    events.push(packetType);
    events.push(selected);
    events.push(event2);
}

std::queue<state::Event> game::Pacman::transform_map_to_events(std::vector<std::string> map)
{
    std::queue<state::Event> events;
    for (std::size_t y = 0; y < map.size(); y++) {
        for (std::size_t x = 0; x < map[y].size(); x++) {
            if (std::get<0>(_Pacman) == x && std::get<1>(_Pacman) == y) {
                create_draw_event(events, x, y, _headDirection);
                continue;
            }
            create_draw_event(events, x, y, charmap.at(map[y][x]));
        }
    }
    return events;
}

void game::Pacman::add_score_to_events(std::queue<state::Event> &events)
{
    std::string score = "Score: " + std::to_string(_score);
    create_draw_string_event(events, 0, 22, score);
}

std::queue<state::Event> game::Pacman::tick()
{
    changeDirection();
    std::vector<std::string> newMap = PacManMap;
    changePacmanPos();
    add_food_to_map(newMap, _food);
    add_ghosts_to_map(newMap, _ghosts);
    add_Pacman_to_map(newMap, _Pacman);
    std::queue<state::Event> events = transform_map_to_events(newMap);
    add_score_to_events(events);
    checkFood();
    _ticks++;
    return events;
}
