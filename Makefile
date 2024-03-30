##
## EPITECH PROJECT, 2024
## B-OOP-400-TLS-4-1-arcade-matthias.soual
## File description:
## Makefile
##

CC = g++

ERRORS_FLAGS = -Wall -Wextra -Werror
SHARED_FLAGS = -fPIC -shared

NAMES = core \
		ncurses \
		sdl \
		sfml \

SRC_FILES =	Event.cpp \
			Keybinds.cpp \

CORE_FILES = Arcade.cpp

GRAPHIC_FILES = IGraphic.cpp \
			AGraphic.cpp \

GAME_FILES = IGame.cpp \
			AGame.cpp \

NCURSES_FILES = Ncurses.cpp \

SDL_FILES = SDL.cpp \

SFML_FILES = SFML.cpp \

SRC_FILES := $(addprefix src/, $(SRC_FILES))
CORE_FILES := $(addprefix src/, $(CORE_FILES))
GRAPHIC_FILES := $(addprefix src/graphic/, $(GRAPHIC_FILES))
GAME_FILES := $(addprefix src/game/, $(GAME_FILES))
NCURSES_FILES := $(addprefix src/graphic/, $(NCURSES_FILES))
SDL_FILES := $(addprefix src/graphic/, $(SDL_FILES))
SFML_FILES := $(addprefix src/graphic/, $(SFML_FILES))

GRAPHIC_LIB_FILES = $(SRC_FILES) $(GRAPHIC_FILES)

all: $(NAMES)

core: $(CORE_FILES)
	$(CC) $(ERRORS_FLAGS) -o $@ $(CORE_FILES)

ncurses: $(NCURSES_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) -lncurses -o $@.so $(GRAPHIC_LIB_FILES) $(NCURSES_FILES)

sdl: $(SDL_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) `sdl2-config --ERRORS_FLAGS --libs` -o $@.so $(GRAPHIC_LIB_FILES) $(SDL_FILES)

sfml: $(SFML_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) -lsfml-graphics -lsfml-window -lsfml-system -o $@.so $(GRAPHIC_LIB_FILES) $(SFML_FILES)

clean:
	rm -f $(addsuffix .o, $(NAMES))

fclean: clean
	rm -f $(addsuffix .so, $(NAMES))

re: fclean all

.PHONY: all clean
