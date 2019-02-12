#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include "player.h"
class Enemy;
class EnemyManager{
	friend class Enemy;
	public:
		EnemyManager( SDL_Renderer* renderer );
		static void SeedRandom( void );
		static int GenerateDamage( void );
		static void GenerateXYSpeed( int* x_speed, int* y_speed );
		void RenderVectorEnemy( void );// Render Each Generated Enemy TODO
		std::pair<int, Player*>  DetectCollision( void );
			// DetectCollision, return damage & ptr to victim( if there's any. TODO )
			// < 0, NULL > means no collistion
		
	private:
		std::vector<Enemy> mVectorEnemy;
		static int GenerateRandom( int min, int max );
		static bool mSeeded;
		static SDL_Renderer* mRenderer;
		// Renderer Shared Between Enemy(s)
};
#endif
