CC=g++
CFLAGS=-Wall -Wextra -Weffc++ -pedantic -g -std=c++11
NAME=deadroom
SDLFLAGS=-lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
FILES=arrow.o game.o level.o menu.o newlevel.o player.o sprite.o timer.o UI.o zombie.o main.o

$(NAME): $(FILES)
	$(CC) $(FILES) -o $(NAME) $(SDLFLAGS)

main.o:
	$(CC) $(CFLAGS) -c main.cc

game.o:
	$(CC) $(CFLAGS) -c game.cc

arrow.o:
	$(CC) $(CFLAGS) -c arrow.cc

level.o:
	$(CC) $(CFLAGS) -c level.cc

menu.o:
	$(CC) $(CFLAGS) -c menu.cc

newlevel.o:
	$(CC) $(CFLAGS) -c newlevel.cc

player.o:
	$(CC) $(CFLAGS) -c player.cc

sprite.o:
	$(CC) $(CFLAGS) -c sprite.cc

timer.o:
	$(CC) $(CFLAGS) -c timer.cc

UI.o:
	$(CC) $(CFLAGS) -c UI.cc

zombie.o:
	$(CC) $(CFLAGS) -c zombie.cc




