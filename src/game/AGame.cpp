/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual [WSL: Fedora]
** File description:
** AGame
*/

#include "AGame.hpp"

short game::AGame::stringToShort(std::string pattern)
{
    short cube = 0;

    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i] == '#') {
            cube |= (1 << i);
        }
    }
    return cube;
}

short game::AGame::rotateRight(short pixel)
{
    return 0;
}

short game::AGame::rotateLeft(short pixel)
{
    return 0;
}
