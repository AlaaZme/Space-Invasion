#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
class Enemey
{


public:
	Enemey(int, int);
	Enemey();
	~Enemey();
	SDL_Rect EnemeyPos;
   // SDL_Texture* NTexture = NULL; 
	bool Alive;
	int health;
	bool bossDead;
	bool shoot;
	bool fired;
	int speed;
	
};

