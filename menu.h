/*
 *  Menu.h
 *
 *  Created on: Nov 22, 2013
 *      Author: Harald
 *      Author: Elias
 */

#ifndef MENU_H_
#define MENU_H_

#include "game.h"

class Game;

class Menu {
public:
  Menu(Game* game);
  Menu(const Menu&) = delete;
  Menu& operator=(const Menu&) = delete;
  ~Menu();

  void events();
  void print();
  void quit();
  void start();
  Mix_Music* getMenuMusic() const;
  Mix_Chunk* getMenuOptionEffect() const;
  Mix_Chunk* getMenuAcceptEffect() const;
  const SDL_Rect& getMenuPosition() const;
  SDL_Surface* getMenuBackground() const;
  SDL_Surface* getMenuArrow() const;

private:
  Game* game;
  enum menuchoices {START, EXIT};
  int menuChoice_{menuchoices::START};
  SDL_Rect menuPositionRect;
  SDL_Surface* gameMenuArrow{nullptr};
  SDL_Surface* gameMenuBackground{nullptr};
  Mix_Music* menu_music{nullptr};
  Mix_Chunk* menu_effect{nullptr};
  Mix_Chunk* menu_accept_effect{nullptr};
};
#endif // MENU_H
