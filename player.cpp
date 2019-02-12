#include "player.h"
#include <SDL2/SDL.h>
#include "enums.h"
#include "info.h"
#include "objectmanager.h"

void Player::UpdatePlayerClip( void ){
	++mIndexCurrentClip %= mClipAmount;
}
void Player::RenderPlayerClip( void ){
	if( mJumpRender ) JumpLeftover();
	SDL_RenderCopy( mRenderer, mPlayerTextureFull, &mPlayerClip[ mIndexCurrentClip ], &mPlayerPositionScale );
}
Player::Player( SDL_Renderer* renderer, SDL_Surface* player_surface, int clip_amount  )
	: mPlayerClip( NULL ), mClipAmount( clip_amount ), mIndexCurrentClip( 0 ), mPlayerTextureFull( NULL ), mScore( 60 ), mJumpSpeedMax( 20 ), mJumpSpeedDelta( 3 ), mJumpRender( false ), mJumpSpeedCurrent( mJumpSpeedMax ), mSpeed( 5 )
{
	if( renderer != NULL )
		mRenderer = renderer;
	if( renderer != NULL && player_surface != NULL ){
		int single_clip_width = player_surface->w / mClipAmount;
		int single_clip_height = player_surface->h;
		mPlayerClip = new SDL_Rect[ mClipAmount ];
		for( int index=0 ; index < mClipAmount ; ++index ){
			mPlayerClip[ index ].x = single_clip_width * index;
			mPlayerClip[ index ].y = 0;
			mPlayerClip[ index ].w = single_clip_width;
			mPlayerClip[ index ].h = single_clip_height;
		}
		EnableColorKey( player_surface );
		mPlayerTextureFull = SDL_CreateTextureFromSurface( mRenderer, player_surface );
	}
}
void Player::EnableColorKey( SDL_Surface* surface ){
	SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB(  surface->format, 0xFF, 0xFF, 0xFF ) );
}
void Player::SetPlayerPosition( int x, int y ){
	mPlayerPositionScale.x = x;
	mPlayerPositionScale.y = y;
}
void Player::SetPlayerScale( int w, int h ){
	mPlayerPositionScale.w = w;
	mPlayerPositionScale.h = h;
}
void Player::UpdatePlayerPosition( int x, int y ){
	mPlayerPositionScale.x += x;
	mPlayerPositionScale.y += y;
}
bool Player::MoveBounded( int player_speed, int direction ){
	// basic movement with window-edge detection
	// this will be called by "void HandleUserInput( keystate )"
	bool can_move = false;
	if( direction == DIRECTION_UP ){
		if( mPlayerPositionScale.y - player_speed > 0 ){
			UpdatePlayerPosition( 0, -player_speed );
		}
		can_move = true;
	}
	if( direction == DIRECTION_DOWN ){
		if( mPlayerPositionScale.y + player_speed < Info::mWindowHeight - mPlayerPositionScale.h ){
			UpdatePlayerPosition( 0, player_speed );
		}
		can_move = true;
	}
	if( direction == DIRECTION_LEFT ){
		if( mPlayerPositionScale.x - player_speed > 0 ){
			UpdatePlayerPosition( -player_speed, 0 );
		}
		can_move = true;
	}
	if( direction == DIRECTION_RIGHT ){
		if( mPlayerPositionScale.x + player_speed < Info::mWindowWidth - mPlayerPositionScale.w ){
			UpdatePlayerPosition( player_speed, 0 );
		}
		can_move = true;
	}
	if( can_move ){
		UpdatePlayerClip();
		return can_move;
	}

	switch( direction ){
		case DIRECTION_UP:
			mPlayerPositionScale.y = 0;
			break;
		case DIRECTION_DOWN:
			mPlayerPositionScale.y = Info::mWindowHeight - mPlayerPositionScale.h;
			break;
		case DIRECTION_LEFT:
			mPlayerPositionScale.x = 0;
			break;
		case DIRECTION_RIGHT:
			mPlayerPositionScale.x = Info::mWindowWidth - mPlayerPositionScale.w;
			break;
		default:
			break;
			//NONE SHALL REACH
	}
	return false;
}
void Player::HandleUserInput( const uint8_t* keystate ){
	if( keystate[ SDL_SCANCODE_A ] ){
		//If player is in the middle of the screen
		//	try to scroll background first
		//		can't scroll? move player
		//If player not in middle
		//	move player
		if( mPlayerPositionScale.x > Info::mWindowWidth/2 - mPlayerPositionScale.w/2 &&
				mPlayerPositionScale.x < Info::mWindowWidth/2 + mPlayerPositionScale.w/2 ){
			if( !ObjectManager::mUIManager.ScrollBackground( mSpeed, DIRECTION_LEFT ) )
				MoveBounded( mSpeed, DIRECTION_LEFT );
			else
				UpdatePlayerClip();
		}
		else MoveBounded( mSpeed, DIRECTION_LEFT );
	}
	if( keystate[ SDL_SCANCODE_D ] ){
		if( mPlayerPositionScale.x > Info::mWindowWidth/2 - mPlayerPositionScale.w/2 &&
				mPlayerPositionScale.x < Info::mWindowWidth/2 + mPlayerPositionScale.w/2 ){
			if( !ObjectManager::mUIManager.ScrollBackground( mSpeed, DIRECTION_RIGHT ) )
				MoveBounded( mSpeed, DIRECTION_RIGHT );
			else
				UpdatePlayerClip();
		}
		else MoveBounded( mSpeed, DIRECTION_RIGHT );
	}
}
void Player::HandleUserInputJump( void ){
	JumpBounded();
}
bool Player::JumpLeftover( void ){
	// true:  player is jumping or falling
	// false: player is on ground
	
	if( mJumpDirection == DIRECTION_UP ){
		// jump up move
		MoveBounded( mJumpSpeedCurrent, DIRECTION_UP );
		// decrease by delta
		// the higher, the slower
		mJumpSpeedCurrent -= mJumpSpeedDelta;
		// check if on top aka. speed is 0
		if( mJumpSpeedCurrent <= 0 ){
			mJumpDirection = DIRECTION_DOWN;
			mJumpSpeedBeforeDown = mJumpSpeedCurrent + mJumpSpeedDelta; 
			mJumpSpeedCurrent = 0;
		}
		return true;
	}
	if( mJumpDirection == DIRECTION_DOWN && mJumpSpeedCurrent != mJumpSpeedMax ){
		if( mJumpSpeedCurrent == 0 ){
			// started going down just now
			mJumpSpeedCurrent = mJumpSpeedBeforeDown;
		}
		else{
			mJumpSpeedCurrent += mJumpSpeedDelta;
		}

		MoveBounded( mJumpSpeedCurrent, DIRECTION_DOWN );
		return true;
	}

	mJumpRender = false;
	return false;
}
bool Player::JumpBounded( void ){
	// First Jump From Ground
	// If current speed recovered to max speed
	if( mJumpSpeedCurrent == mJumpSpeedMax ){
		mJumpDirection = DIRECTION_UP;
		mJumpRender = true;
	}
	return false;
}
Player::~Player(){
	if( mPlayerClip != NULL )
		delete [] mPlayerClip;
	if( mPlayerTextureFull != NULL );
		SDL_DestroyTexture( mPlayerTextureFull );
}
