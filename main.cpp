#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "locale.h"
#include "player.h"
#include "uimanager.h"
#include "enums.h"
#include "info.h"
#include "objectmanager.h"
#include "enemy.h"
#include "enemymanager.h"
using namespace std;
int main(){
	Locale::mLocale = "en";
	SDL_Init( SDL_INIT_VIDEO );
	IMG_Init( IMG_INIT_PNG );
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* surface = NULL;

	window = SDL_CreateWindow( "t",0,0,500,500, SDL_WINDOW_SHOWN );
	Info::mWindowHeight = 500; // Must Have
	Info::mWindowWidth = 500;  // Set Info So That Other Class Could Use It.

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0xFF, 0xFF );
	surface = IMG_Load( "player.png" );
	Player player( renderer, surface, 5 );
	player.SetPlayerScale( 50,50 );
	player.SetPlayerPosition( 100, 350 );
	player.mSpeed = 5;
	SDL_FreeSurface( surface );

	surface = IMG_Load( "background.png" );
	UIManager uimanager( renderer, surface );
	uimanager.UpdatePlayerScore( &player, +50 );
	ObjectManager::mUIManager = uimanager; // MUST HAVE, UIManager will be handled by ObjectManager
		// Thus ObjectManager can handle objects
		// using UIManager's Background Functions

	EnemyManager enemymanager( renderer ); // MUST HAVE, responsible for ALL enemy stuffs
	

	SDL_Event e;
	bool quit = false;
	uint32_t current_ticks = 0;
	uint32_t last_ticks = 0;
	uint8_t const *keystate = NULL;
	while( !quit ){
		SDL_PollEvent( &e );
		keystate = SDL_GetKeyboardState( NULL );
		if( e.type == SDL_KEYDOWN ){
			std::cout<<"Key Down"<<std::endl;
		}
		player.HandleUserInput( keystate );
		if( e.type == SDL_KEYDOWN && keystate[ SDL_SCANCODE_SPACE ] ){
			player.HandleUserInputJump();
		}
		
		if( e.type == SDL_QUIT ) quit = true;
		SDL_RenderClear( renderer );

		ObjectManager::mUIManager.RenderBackground();
		ObjectManager::mUIManager.RenderPlayerScore( &player );
		player.RenderPlayerClip();
		SDL_RenderPresent( renderer );
	}

	return 0;
}
