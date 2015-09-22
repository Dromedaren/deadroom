#include "UI.h"

Ui::Ui(Game* gamePointer, Player* player)
    : Sprite(gamePointer, "User Interface", game->loadImage("hpbars.png")),
      game(gamePointer),
      player(player),
      playerHealth(player->getHealth())
{

	/**
	 * the user interface draws the players health bar, the text on screen,
	 * it also opens the true type font system.
	 */
	font = TTF_OpenFont("8bit.ttf", 12);
	if (font == nullptr)
	{
		std::cerr << "Error opening a font with TTF_OpenFont";
		exit(7);
	}
	else
	{
		hpbarStatusMessage = TTF_RenderText_Solid(font, "Player Health", textColor);
		spritePosition.x = 35;
		spritePosition.y = 20;
		spriteSheetRect.x = animations.at("fullHealthAnimation").first;
		spriteSheetRect.y = 0;
		spriteSheetRect.w = 56;
		spriteSheetRect.h = 20;
	}
}

Ui::~Ui()
{
	/**
	 * the destructor is resposible for freeing the surfaces and closing the true type font system.
	 */
	SDL_FreeSurface(hpbarStatusMessage);
	TTF_CloseFont(font);
}

void Ui::events()
{
	/**
	 * we have to call on the user interface event function to update the player health bar.
	 */
	playerHealth = player->getHealth();

	if (playerHealth == 10)
		{
			spriteSheetRect.x = animations.at("fullHealthAnimation").first;
		}
		else if (playerHealth >= 7 && playerHealth < 10)
		{
			spriteSheetRect.x = animations.at("almostfullHealthAnimation").first;
		}
		else if (playerHealth >=4 && playerHealth < 7 )
		{
			spriteSheetRect.x = animations.at("mediumHealthAnimation").first;
		}
		else if (playerHealth > 0 && playerHealth < 4)
		{
			spriteSheetRect.x = animations.at("lowHealthAnimation").first;
		}
}

bool Ui::collision(){return false;}

SDL_Surface* Ui::getUIText() const
{
	/**
	 * returns the surface that holds the player health text message.
	 */
	return hpbarStatusMessage;
}
