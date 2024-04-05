##
## EPITECH PROJECT, 2024
## B-OOP-400-TLS-4-1-arcade-matthias.soual
## File description:
## Makefile
##

CC = g++

ERRORS_FLAGS = -Wall -Wextra
SHARED_FLAGS = -fPIC -shared

NAMES = core \
		ncurses \
		sdl \
		sfml \
		snake \
		pacman \
		menu

NAME = arcade

CORE_FILES = Arcade.cpp \

GRAPHIC_FILES = IGraphic.cpp \
			AGraphic.cpp \

GAME_FILES = AGame.cpp \

NCURSES_FILES = Ncurses.cpp \

SNAKE_FILES = Snake.cpp \

SDL_FILES = Sdl.cpp \

MENU_FILES = Menu.cpp \

PACMAN_FILES = Pacman.cpp \

SFML_FILES = Sfml.cpp \

SRC_FILES := $(addprefix src/, $(SRC_FILES))
CORE_FILES := $(addprefix src/, $(CORE_FILES))
GRAPHIC_FILES := $(addprefix src/graphic/, $(GRAPHIC_FILES))
GAME_FILES := $(addprefix src/game/, $(GAME_FILES))
NCURSES_FILES := $(addprefix src/graphic/, $(NCURSES_FILES))
SDL_FILES := $(addprefix src/graphic/, $(SDL_FILES))
SFML_FILES := $(addprefix src/graphic/, $(SFML_FILES))
SNAKE_FILES := $(addprefix src/game/, $(SNAKE_FILES))
PACMAN_FILES := $(addprefix src/game/, $(PACMAN_FILES))
MENU_FILES := $(addprefix src/game/, $(MENU_FILES))

GRAPHIC_LIB_FILES = $(SRC_FILES) $(GRAPHIC_FILES)
GAME_LIB_FILES = $(SRC_FILES) $(GAME_FILES)
PUT_LIB = ./lib/

all: $(NAMES)

core: $(CORE_FILES)
	$(CC) $(ERRORS_FLAGS) -o $(NAME) $(CORE_FILES)

graphicals: ncurses sdl sfml

ncurses: $(NCURSES_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) -lncursesw -o $(PUT_LIB)arcade_ncurses.so $(GRAPHIC_LIB_FILES) $(NCURSES_FILES)

sdl: $(SDL_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) `sdl2-config --ERRORS_FLAGS --libs` -lSDL2 -lSDL2_ttf -lSDL2_image -o $(PUT_LIB)arcade_sdl2.so $(GRAPHIC_LIB_FILES) $(SDL_FILES)

sfml: $(SFML_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) -lsfml-graphics -lsfml-window -lsfml-system -o $(PUT_LIB)arcade_sfml.so $(GRAPHIC_LIB_FILES) $(SFML_FILES)

snake: $(SNAKE_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) -o $(PUT_LIB)arcade_snake.so -Iinclude $(SNAKE_FILES) $(GAME_LIB_FILES)

pacman: $(PACMAN_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) -o $(PUT_LIB)arcade_pacman.so -Iinclude $(PACMAN_FILES) $(GAME_LIB_FILES)

menu: $(MENU_FILES)
	$(CC) $(ERRORS_FLAGS) $(SHARED_FLAGS) -o $(PUT_LIB)arcade_menu.so -Iinclude $(MENU_FILES) $(GAME_LIB_FILES)

clean:
	rm -f $(addsuffix .o, $(NAMES))

fclean: clean
	rm -f $(addsuffix *, $(PUT_LIB))
	rm -f $(NAME)

re: fclean all

debug: SHARED_FLAGS += -g
debug: re

.PHONY: all clean
