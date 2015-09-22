/*
 * Menu.cc
 *
 *  Created on: Nov 22, 2013
 *      Author: Harald
 *      		Elias
 */

#include "menu.h"

Menu::Menu(Game* gamePointer) : game(gamePointer),
						  	  	 menuPositionRect()
{
	/**
	 * the menu constructor loads all menu images, music and also sets the default
	 * option in the game menu.
	 */
	gameMenuBackground = game->loadImage("assets/gamemenubackground.png");
	gameMenuArrow = game->loadImage("assets/gamemenuarrow.png");
	menuPositionRect.x = 250; //px
	menuPositionRect.y = game->getScreenHeight() - 430; //px

	menu_music = game->loadMusic("assets/menumusikspel.mp3");
	menu_effect = game->loadChunk("assets/button-20.wav");
	menu_accept_effect = game->loadChunk("assets/button-21.wav");
}
Menu::~Menu()
{
	/**
	 * menu is responsible for freeing its surfaces and music.
	 */
	SDL_FreeSurface(gameMenuBackground);
	SDL_FreeSurface(gameMenuArrow);
	Mix_FreeMusic(menu_music);
	Mix_FreeChunk(menu_effect);
	Mix_FreeChunk(menu_accept_effect);
	std::cout << "Running menu destructor" << std::endl;
}

void Menu::start() {
	/**
	 * updates the games state to its play-state.
	 */
	game->setGameState(game->PLAY);
}

void Menu::quit() {
	/**
	 * updates the games state to its exit-state.
	 */
	game->setGameState(game->EXIT);
}

void Menu::events()
{
	/**
	 * handles the menu events, such as moving up / down in the menu
	 * and choosing either start or exit.
	 */
    if (game->getKeystates()[SDLK_UP])
        {
            menuPositionRect.y = game->getScreenHeight() - 430;
            menuChoice_ = menuchoices::START;
            Mix_PlayChannel(-1, menu_effect, 1);
            //game->playChunk(menu_effect);
        }
    else if (game->getKeystates()[SDLK_DOWN])
        {
            menuPositionRect.y = game->getScreenHeight() - 335;
            menuChoice_ = menuchoices::EXIT;
            Mix_PlayChannel(-1, menu_effect, 1);
            //game->playChunk(menu_effect);
        }
    else if (game->getKeystates()[SDLK_RETURN])
        {
            if (menuChoice_ == menuchoices::START)
            {
                //game->playChunk(menu_accept_effect);
            	Mix_PlayChannel(-1, menu_accept_effect, 1);
                start();
            }
            else
            {
                quit();
            }
        }
}

Mix_Music* Menu::getMenuMusic() const{
	/**
	 * returns the menu music.
	 */
    return menu_music;
}
Mix_Chunk* Menu::getMenuOptionEffect() const{
	/**
	 * returns the sound effect when switching menu option.
	 */
    return menu_effect;
}
Mix_Chunk* Menu::getMenuAcceptEffect() const{
	/**
	 * returns the sound effect when choosing a menu option.
	 */
    return menu_accept_effect;
}

const SDL_Rect& Menu::getMenuPosition() const
{
	/**
	 * gets the current position in the menu (the menu arrow).
	 */
	return menuPositionRect;
}

SDL_Surface* Menu::getMenuBackground() const
{
	/**
	 * returns the surface of the menu background.
	 */
	return gameMenuBackground;
}

SDL_Surface* Menu::getMenuArrow() const
{
	/**
	 * returns the surface of the menu arrow.
	 */
	return gameMenuArrow;
}
