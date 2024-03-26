##
## EPITECH PROJECT, 2024
## B-OOP-400-TLS-4-1-arcade-matthias.soual [WSL: Fedora]
## File description:
## Makefile
##

NAME = arcade

SRC = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)

OBJ = $(SRC:.cpp=.o)

GPPFLAGS = -Wall -Wextra

GPP = g++

all: $(NAME)

$(NAME): $(OBJ)
        $(GPP) -o $(NAME) $(OBJ) $(GPPFLAGS)

%.o: %.cpp
        $(GPP) -o $@ -c $< $(GPPFLAGS)

clean:
        rm -f $(OBJ)

fclean: clean
        rm -f $(NAME)

re: fclean all

debug: GPPFLAGS += -g
debug: re

.PHONY: all clean fclean re