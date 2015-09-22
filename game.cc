#include "game.h"
#include "timer.h"
#include "menu.h"
#include "level.h"
#include "newlevel.h"

Game::Game()
{
  /** The game constructor Initializes SDL Video & Audio,
   *  the audio mixer, and true type font system.
   */
  if (SDL_Init(SDL_INIT_EVERYTHING ) == -1) {
    std::cerr << "Error initializing SDL (Error 1)" << std::endl;
    SDL_Quit();
    exit(1);
  }

  else
  {
	  std::cout << "Initializing SDL_VIDEO | SDL_AUDIO " << std::endl;
  }

  // Set screen mode
  screen = SDL_SetVideoMode(getScreenWidth(), getScreenHeight(), SCREENBITSPERPIXEL, SDL_SWSURFACE|SDL_DOUBLEBUF);
  if (screen == NULL) {
    std::cerr << "Error setting resolution (Error 2)" << std::endl;
    SDL_FreeSurface(screen);
    exit(2);
  }

  else
  {
	  std::cout << "Current SDL_VIDEO_MODE: screen(" << getScreenWidth() << " px, " << getScreenHeight() << " px) " << "bits-per-pixel: " << SCREENBITSPERPIXEL << std::endl;
  }

  // Initialize the SDL_Mixer for audio
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
  {
	  std::cerr << "Error initializing audio (Error 3)" << std::endl;
	  Mix_Quit();
	  exit(3);
  }
  else
  {
	  std::cout << "Opened SDL_MIXER" << std::endl;
  }

  if (TTF_Init() == -1 )
  {
	  std::cerr << "Error initializing TTF (Error TTF)" << std::endl;
	  TTF_Quit();
	  exit(6);
  }

  // Screen caption
  SDL_WM_SetCaption("Deadroom, stay inside and just survive!", 0);
}

Game::~Game()
{
	/**
	 * Game destructor makes sure to free surfaces and pointers before
	 * shutting down the Mixer, TTF system and SDL
	 */

	std::cout << "game engine destroyed" << std::endl;
	gameState = EXIT;
	SDL_FreeSurface(screen);
	delete fps;
	delete level;
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Game::setGameState(int newGameState) {
	/**
	 * SetGameState can take a new state and change the game's
	 * state to what the function recieved.
	 */

	gameState = newGameState;
}

int Game::getGameState() const
{
	/**
	 * GetGameState simply returns the current state the game
	 * is in.
	 */

	return gameState;
}

Uint8* Game::getKeystates() const
{
	/**
	 * GetKeystates returns a pointer holding all keystates.
	 * this is a pointer to an array of keys. It is used to
	 * determine if a key is pressed or not.
	 */

	return keystates;
}
int Game::getScreenWidth() const
{
	/**
	 * Returns screen width.
	 */
	return SCREENWIDTH;
}
int Game::getScreenHeight() const
{
	/**
	 * Returns screen height.
	 */
	return SCREENHEIGHT;
}
int Game::getFramesPerSecond() const
{
	/**
	 * Returns frames per second.
	 */

	return FRAMESPERSECOND;
}

void Game::SDL_EVENTS()
{
	/**
	 * SDL_EVENTS handle polling of game events,
	 * such as exiting the game, lowering the game music
	 * volume / raising the volume.
	 * It is also nessecary in order for the keystates to
	 * properly work.
	 */

	while(SDL_PollEvent(&gameEvent)) {
          if((gameEvent.type == SDL_QUIT || gameEvent.key.keysym.sym == SDLK_ESCAPE) && gameEvent.type == SDL_KEYDOWN)
		{
			setGameState(EXIT);
		}
	}
}

void Game::loadLevel()
{
	/**
	 * LoadLevel loads a new level, creates a timer
	 * and starts the timer.
	 */

	fps = new Timer;
	fps->Start();
	level = new Newlevel(this);

}

void Game::runLevel()
{
	/**
	 * RunLevel runs the level just loaded, gameplay begins
	 * in this function.
	 */
	if (gameState == PLAY)
	{
		SDL_EVENTS();
		level->events();
		level->collision_detection();
		level->update();
		level->blit();
	}
	else if (gameState == COMPLETELEVEL)
	{
		std::cout << "COMPLETE LEVEL" << std::endl;
		gameState = PLAY;
		fps->Stop();
		delete fps;
		delete level;
		loadLevel();
	}
	else if (gameState == GAMEOVER || gameState == EXIT)
	{
		return;
	}
	draw();
}

void Game::loadMenu()
{
	/**
	 * LoadMenu creates the menu, starts menu music,
	 * handles start and exit states.
	 */

	menu = new Menu(this);
	playMusic(menu->getMenuMusic());

	while (gameState == MENU)
	{
		SDL_EVENTS();
		menu->events();
		applyImage(0, 0 , menu->getMenuBackground(), screen);
		applyImage(menu->getMenuPosition().x, menu->getMenuPosition().y, menu->getMenuArrow(), screen);
		draw();
	}
	delete menu;
}
void Game::run() {

	/**
	 * This is the main function that runs the game
	 * we load the menu, then the level and as long as we dont
	 * exit or get gameover, we can continue playing.
	 */

	loadMenu();
	// if we chose to exit in the menu, return thus exiting the game
	if (gameState == EXIT)
	{
		return;
	}

	loadLevel();
	while(gameState != 0 && gameState !=4)
	{
		runLevel();
		if (fps->get_ticks() < (2000 / getFramesPerSecond())) {
			SDL_Delay( ( 2000 / getFramesPerSecond() ) - fps->get_ticks() );
		}
	}
}

void Game::draw() {
	/**
	 * Flips the back buffer and draws what is in memory
	 * to the screen surface.
	 */

	SDL_Flip(screen);
}

SDL_Surface* Game::loadImage(std::string filename)
{
	/**
	 * Creates a temporary surface then optimizes the
	 * loaded image and returns the new optimized surface
	 */

	// Load a temporary storage for the image
	SDL_Surface* loadedImage = nullptr;

	// Make a optimized image that will be used
	SDL_Surface* optimizedImage = nullptr;

	// Load the image
	loadedImage = IMG_Load(filename.c_str() );

	if (loadedImage == nullptr)
	{
		std::cerr << "Error loading image (Error 4): " << filename << std::endl;
		SDL_FreeSurface(loadedImage);
		exit(4);
	}

	else
	{
		/** Optimize the loaded image and colorkey the image
		 * Also make sure that we use displayformatalpha for images
		 * that has transparency needs like the menuarrow
        */
		std::cout << "Loaded " << filename << std::endl;
		optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

		// Free the temporary image
		SDL_FreeSurface( loadedImage );
		if (optimizedImage == nullptr)
		{
			std::cerr << "Error optimizing image (Error 5)" << std::endl;
			SDL_FreeSurface(optimizedImage);
			exit(5);
		}
	}
	return optimizedImage;
}

void Game::applyImage(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* spriteClip )
{
	/**
	 * this is the actual drawing function the function creates
	 * a temporary rectangle offset and used that to blit the surface
	 * onto the destination surface.
	 */

	// Create an temporary offset for the coordinates x and y
	SDL_Rect offset;

	// Store values in offsets
	offset.x = x;
	offset.y = y;

	// Now blit the surface
	SDL_BlitSurface( source, spriteClip, destination, &offset);
}

void Game::playMusic(Mix_Music* song) const {
	/**
	 * returns a state variable that is less than 0 if
	 * something went wrong.
	 */

    int state{0};
	Mix_PlayMusic(song, 1);
	if (state < 0)
    {
        std::cerr << "There was an error playing a song!" << std::endl;
    }
}

void Game::playChunk(Mix_Chunk* effect) const {
	/**
	 * plays a sound effect, returns a state variable
	 * that is less than 0 if something went wrong.
	 */

	int state{0};
	state = Mix_PlayChannel(2, effect, 0 );
    if (state < 0)
    {
        std::cerr << "There was an error playing a sound effect!" << std::endl;
    }
}

Mix_Music* Game::loadMusic(std::string filename) {
	/**
	 * loadMusic takes a filename and tries to open
	 * that media into the game.
	 */

	Mix_Music* songStorage = Mix_LoadMUS(filename.c_str());
	if ( songStorage == NULL)
	{
		std::cerr << "Error loading music (Error 6)" << std::endl;
		Mix_FreeMusic(songStorage);
		exit(6);
	}
	else
	{
		std::cout << "Loaded " << filename << std::endl;
	}
	return songStorage;
}

Mix_Chunk* Game::loadChunk(std::string filename) {
	/**
	 * loadChunk takes a filename to a sound effect and
	 * tries to open that media into the game.
	 */

	Mix_Chunk* chunkStorage = Mix_LoadWAV(filename.c_str());
	if ( chunkStorage == NULL)
	{
		std::cerr << "Error loading chunk (Error 7)" << std::endl;
		Mix_FreeChunk(chunkStorage);
		exit(7);
	}
	else
	{
		std::cout << "Loaded " << filename << std::endl;
	}
	return chunkStorage;
}
