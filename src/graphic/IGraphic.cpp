/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-arcade-matthias.soual
** File description:
** IGraphic
*/

#include "IGraphic.hpp"

const char *graphic::IGraphic::packetError::what(void) const noexcept
{
    return "Packet error";
}