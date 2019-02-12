#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include "enums.h"
class UIManager;
class Player{
	friend class UIManager;
	public:
		Player( SDL_Renderer* renderer, SDL_Surface* player_surface, int clip_amount ); // Obtain mRenderer, mPlayerTextureFull. Create mPlayerClip
		void UpdatePlayerClip( void ); // Animate Player Clip
		void RenderPlayerClip( void ); // Render Player to Renderer, With Current Clip & Scale & Position
		void SetPlayerPosition( int x, int y);
		void SetPlayerScale( int w, int h );
		void HandleUserInput( const uint8_t* keystate );
		void HandleUserInputJump( void );
		~Player();
		int mSpeed; // left & right speed
	private:
		bool MoveBounded( int player_speed, int direction ); // true: can move. false: stuck on edge
		bool JumpBounded( void );
		bool JumpLeftover( void );
		int mJumpSpeedMax;
		int mJumpSpeedDelta;
		int mJumpSpeedCurrent;
		int mJumpSpeedBeforeDown;
		DIRECTION mJumpDirection;
		bool mJumpRender;
		void UpdatePlayerPosition( int x, int y ); 
		void EnableColorKey( SDL_Surface* surface );
		SDL_Rect* mPlayerClip;
		SDL_Rect  mPlayerPositionScale;
		const int mClipAmount;
		int mIndexCurrentClip;
		SDL_Renderer* mRenderer;
		SDL_Texture* mPlayerTextureFull;
		int mScore;
		
		
};
#endif
