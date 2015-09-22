/*
 * UI.h
 * Created on : Dec 2, 2013
 *  Author: bleh
*/

#ifndef UI_H
#define UI_H
#define WHITE {255,255,255}
#include <SDL/SDL_ttf.h>
#include "player.h"

class Ui: public Sprite
{
public:
    Ui(Game* game, Player* player);
    Ui(const Ui&) = delete;
    Ui& operator=(const Ui&) = delete;
    ~Ui();
    void events();
    bool collision();
    SDL_Surface* getUIText() const;

private:
    Game* game;
    Player* player;
    int playerHealth{0};
    SDL_Surface* hpbarStatusMessage{nullptr};
    TTF_Font *font{nullptr};
    SDL_Color textColor = {Uint8(255), Uint8(255) ,Uint8(255), Uint8(0)};
};
#endif // UI_H
