#include "stdafx.h"
#include "Enemey.h"

#define EnemeyWidth  70;
#define EnemyHeight 60;

Enemey::Enemey(int width,int height)
{
	int boundries = width - EnemeyWidth;
	
		 EnemeyPos.x =rand() % boundries + 10;
		 EnemeyPos.y =  0;// height;
	     EnemeyPos.h = EnemyHeight;
		 EnemeyPos.w = EnemeyWidth


			 speed = 8;
		 Alive = true;
		 fired = false;
		 health = 16;
		 bossDead = false;
		 if (rand() % 10 <=3)
			 shoot = true;
		 else
			 shoot = false;
	
}



Enemey::Enemey() {

}
Enemey::~Enemey()
{
}