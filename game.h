/*
 * Menu.cc
 *
 *  Created on: Nov 22, 2013
 *      Author: Harald
 *      		Elias
 */

//Game.h with SDL initiation

#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include <string>
#include <iostream>
#include <map>
#include <list>
#include <random>
#include <chrono>

class Timer;
class Menu;
class Level;

class Game
{
public:
  Game();
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  ~Game();

  void draw();
  void run();
  void runLevel();
  void loadLevel();
  void loadMenu();

  SDL_Surface* loadImage(std::string filename);
  void applyImage(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* spriteClip = NULL );

  void playMusic(Mix_Music* song) const;
  void playChunk(Mix_Chunk* effect) const;
  Mix_Music* loadMusic(std::string filename);
  Mix_Chunk* loadChunk(std::string filename);

  void setGameState(int newGameState);

  int  getGameState() const;
  Uint8* getKeystates() const;
  int getScreenWidth() const;
  int getScreenHeight() const;
  int getFramesPerSecond() const;

  void SDL_EVENTS();
public:
  Timer* fps{nullptr};
  Level* level{nullptr};
  SDL_Surface* screen{nullptr};
  SDL_Event gameEvent{};

  std::default_random_engine random_generator{seed};
  enum States{EXIT, MENU, PLAY, COMPLETELEVEL, GAMEOVER};

private:
  Menu* menu{nullptr};
  Uint8 *keystates{SDL_GetKeyState(NULL)};
  int gameState{MENU};
  const int SCREENWIDTH{800};
  const int SCREENHEIGHT{800};
  const int SCREENBITSPERPIXEL{32};
  const int FRAMESPERSECOND{30};
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
};
#endif // GAME_H
