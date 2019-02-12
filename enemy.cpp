#include "enemy.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "info.h"
#include "enemymanager.h"
#include <sstream>
TTF_Font* Enemy::mDefaultFont = NULL;
SDL_Color Enemy::mDefaultFontColor = { 128,128,128, 255 };
Enemy::Enemy( ){
	mDamage = EnemyManager::GenerateDamage();
	EnemyManager::GenerateXYSpeed( &mXSpeed, &mYSpeed );
	std::stringstream damage_value;
	damage_value << mDamage;

	// Use It's Damager Value as Texture
	SDL_Surface* surface = CreateSurfaceFromText( damage_value.str().c_str() );
	mTexture = SDL_CreateTextureFromSurface( EnemyManager::mRenderer, surface );
	SDL_FreeSurface( surface );

	mPositionScale.w = 30;
	mPositionScale.h = 30;
	mPositionScale.x = EnemyManager::GenerateRandom( 0, Info::mWindowWidth );
	mPositionScale.y = 0 - mPositionScale.w;
	mTexture = SDL_CreateTextureFromSurface( EnemyManager::mRenderer, surface );
}

SDL_Surface* Enemy::CreateSurfaceFromText( const char* cstring ){
	TTF_Init();
	if( mDefaultFont == NULL ){
		mDefaultFont == TTF_OpenFont( "font_default.ttf", 13 );
	}
	SDL_Surface* surface_return = NULL;
	surface_return = TTF_RenderUTF8_Solid( mDefaultFont, cstring, mDefaultFontColor );
}


Enemy::~Enemy(){
	if( mTexture != NULL ) SDL_DestroyTexture( mTexture );
}
