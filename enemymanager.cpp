#include <SDL2/SDL.h>
#include "enemymanager.h"
#include "enemy.h"
bool EnemyManager::mSeeded = false;
SDL_Renderer* EnemyManager::mRenderer = NULL;


EnemyManager::EnemyManager( SDL_Renderer* renderer ){
	mRenderer = renderer;
}
void EnemyManager::SeedRandom( void ){
	if( !mSeeded ){
		srand( time( NULL ) );
	}
}
int EnemyManager::GenerateRandom( int min, int max ){
	// This Function Only Takes Numbers > 0 
	if( min > max || min <= 0 || max <= 0 ) return 0;
	if( !mSeeded ) SeedRandom();
	int random_ret = 0;
	while( random_ret < min ){
		random_ret += rand();
	}
	if( random_ret > max ) random_ret = random_ret % max;
	return random_ret;
}
int EnemyManager::GenerateDamage( void ){
	return GenerateRandom( 5, 20 );
}
void EnemyManager::GenerateXYSpeed( int* x_speed, int* y_speed ){
	*x_speed = GenerateRandom( 2, 6 );
	*y_speed = GenerateRandom( 2, 6 );
}
