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

    for (std::size_t i = 0; i < pattern.size(); i++) {
        if (pattern[i] == '#') {
            cube |= (1 << i);
        }
    }
    return cube;
}

short game::AGame::rotateRight(short cube)
{
    short rotatedCube = 0;

    for (int i = 0; i < 16; i++) {
        if (cube & (1 << i)) {
            rotatedCube |= (1 << ((i + 4) % 16));
        }
    }
    return rotatedCube;
}

short game::AGame::rotateLeft(short cube)
{
    short rotatedCube = 0;

    for (int i = 0; i < 16; i++) {
        if (cube & (1 << i)) {
            rotatedCube |= (1 << ((i + 12) % 16));
        }
    }
    return rotatedCube;
}
