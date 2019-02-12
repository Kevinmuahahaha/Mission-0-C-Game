#ifndef ENEMY_H
#define ENEMY_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
class EnemyManager;
class Enemy{
	friend class EnemyManager;
	public:
		int mDamage;
		Enemy();
		~Enemy();
	private:
		int mXSpeed;
		int mYSpeed;
		SDL_Rect mPositionScale;
		SDL_Texture* mTexture;
		static TTF_Font* mDefaultFont;
		static SDL_Color mDefaultFontColor;
		SDL_Surface* CreateSurfaceFromText( const char* cstring );
};
#endif
