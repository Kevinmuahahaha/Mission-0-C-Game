#include <SDL2/SDL_ttf.h>
#include "text.h"
#include "locale.h"
#include "info.h"
#include "uimanager.h"
#include "player.h"
#include "enums.h"
#include <sstream>
#include <iostream>
UIManager::UIManager( SDL_Renderer* renderer, SDL_Surface* background_surface_full )
	: mRenderer( NULL ), mBackgroundTextureFull( NULL )
{
	// Obtain informations, assign member variables
	if( renderer != NULL ) mRenderer = renderer;
	if( background_surface_full != NULL && renderer != NULL ){
		mBackgroundTextureFull = SDL_CreateTextureFromSurface( mRenderer, background_surface_full );
		mBackgroundClipFull.x=0;
		mBackgroundClipFull.y=0;
		mBackgroundClipFull.w=background_surface_full->w;
		mBackgroundClipFull.h=background_surface_full->h;

		mBackgroundClip.x = 0;
		mBackgroundClip.y = mBackgroundClipFull.w/4;
		mBackgroundClip.w = Info::mWindowWidth;
		mBackgroundClip.h = Info::mWindowHeight;
	}

	mWindowWidth = Info::mWindowWidth;
	mWindowHeight = Info::mWindowHeight;



	TTF_Init();
	mDefaultFont = TTF_OpenFont("font_default.ttf", 13);
	mDefaultFontColor = { 0xFF,0xFF,0xFF,0xFF };
}
void UIManager::UpdatePlayerScore( Player *player, int score ){
	player->mScore += score;
	// score is -5, player's score decrease
	// score is +5, player's score increase
}
void UIManager::RenderPlayerScore( const Player* player ){
	
	
	std::stringstream text;
	text.str("");
	if( Locale::mLocale == "en" )
		text << TEXT_ONSCREEN_USER_SCORE_EN << player->mScore ;
	else if( Locale::mLocale == "cn" )
		text << TEXT_ONSCREEN_USER_SCORE_CN << player->mScore ;
	
	
	SDL_Surface* surface = NULL;
	surface = CreateSurfaceFromText( text.str().c_str() );
		SDL_Rect score_position_scale = { 0, 0, mWindowWidth, (int)(((float)surface->h/(float)surface->w)*(float)mWindowWidth) };
		score_position_scale.x = mWindowWidth/2 - score_position_scale.w/2;
		score_position_scale.y = mWindowHeight/2 - score_position_scale.h/2;
	SDL_Texture* texture = SDL_CreateTextureFromSurface( mRenderer, surface );
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	SDL_SetTextureAlphaMod(  texture, 128 );

	SDL_RenderCopy( mRenderer, texture, NULL, &score_position_scale );

	SDL_FreeSurface( surface );
	SDL_DestroyTexture( texture );
}
SDL_Surface* UIManager::CreateSurfaceFromText( const char* cstring ){
	TTF_Init();
	SDL_Surface* surface_return = NULL;
	surface_return = TTF_RenderUTF8_Solid( mDefaultFont, cstring, mDefaultFontColor );
}
bool UIManager::RenderBackground( void ){
	return SDL_RenderCopy( mRenderer, mBackgroundTextureFull, &mBackgroundClip, NULL) >= 0;
}

bool UIManager::Scrollable( AXIS axis ){
	if( axis == AXIS_X ){
		return mBackgroundClipFull.w - mBackgroundClip.x >= mWindowWidth && mBackgroundClip.x >= 0 ;
	}
	if( axis == AXIS_Y ){
		return 	mBackgroundClipFull.h - mBackgroundClip.y >= mWindowHeight && mBackgroundClip.y >= 0 ;
	}
}


bool UIManager::ScrollBackground( int player_speed, int direction ){
	// false : when the clip reaches the edge of screen
	// 	( refuse to scroll )
	// true  : successfully scrolled the background
	mBackgroundClipLast = mBackgroundClip;
	if( direction == DIRECTION_UP ){
		mBackgroundClip.y -= player_speed;
	}
	else if( direction == DIRECTION_DOWN ){
		mBackgroundClip.y += player_speed;
	}
	else if( direction == DIRECTION_LEFT ){
		mBackgroundClip.x -= player_speed;
	}
	else if( direction == DIRECTION_RIGHT ){
		mBackgroundClip.x += player_speed;
	}

	if( ( direction == DIRECTION_LEFT || direction == DIRECTION_RIGHT ) && !Scrollable( AXIS_X ) ){
		mBackgroundClip = mBackgroundClipLast;
		switch( direction ){
			case DIRECTION_LEFT:
				mBackgroundClip.x = 0;
				break;
			case DIRECTION_RIGHT:
				if( mBackgroundClipFull.w - mWindowWidth > 0 )
					mBackgroundClip.x = mBackgroundClipFull.w - mWindowWidth;
				break;
			default:
				// Non Shall Reach
				break;
		}
		return false;

	}
	if( ( direction == DIRECTION_UP || direction == DIRECTION_DOWN ) && !Scrollable( AXIS_Y ) ){
		mBackgroundClip = mBackgroundClipLast;
		switch( direction ){
			case DIRECTION_UP: 
				// Can't go further up, set background clip to top
				mBackgroundClip.y = 0;
				break;
			case DIRECTION_DOWN:
				if( mBackgroundClipFull.h - mWindowHeight > 0 )
					mBackgroundClip.y = mBackgroundClipFull.h - mWindowHeight;
				break;
			default:
				// Non Shall Reach
				break;
		}
		return false;
	}
	else return true;
}
