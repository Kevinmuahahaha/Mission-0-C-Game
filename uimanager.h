#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "enums.h"
class Player;
// UIManager:
// 	Manages Background Scrolling
// 	Manages Score Displaying
class Player;
class UIManager{
	friend class Player;
	public:
		UIManager( SDL_Renderer* renderer=NULL, SDL_Surface* surface=NULL );
		void UpdatePlayerScore( Player *player, int score );
		void RenderPlayerScore( const Player *player );
		bool RenderBackground( void );
		bool ScrollBackground( int player_speed, int direction );
		// false : when the clip can't fit screen
		// 	( refuse the render on false )
		// true  : successfully rendered the background
	private:
		SDL_Surface* CreateSurfaceFromText( const char* cstring );
		SDL_Renderer* mRenderer;
		bool Scrollable( AXIS axis );
		SDL_Texture* mBackgroundTextureFull;
		SDL_Rect mBackgroundClip;
		SDL_Rect mBackgroundClipLast;
		SDL_Rect mBackgroundClipFull;
		int mWindowWidth;
		int mWindowHeight;
		TTF_Font* mDefaultFont;
		SDL_Color mDefaultFontColor;
};
#endif
