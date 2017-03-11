#pragma once

//#include <SDL.h>
#include <iostream>
//#include <SDL.h>
//#include <glew.h>

//dest.x = 500;
struct node {
	//SDL_Rect ShotPos;
	int x;
	int y;
	int h;
	int  w;
	int speed;
	bool hit;
	node *next;
	node *prev;
};
class Display
{
public:
	
	Display();
	~Display();
	bool getImage(std::string fileName);
	bool Win();
	bool chkPress();
	void update();
	void moveShot(node*);
	bool hit = false;
	//SDL_Texture* loadTexture(std::string path);
	//bool move();
	void Display::Delay();
	bool success = true;
	void drawEnemies(node* shot);
	//SDL_Texture* NTexture;// = loadTexture("VS.png");// NULL;
private:
};

