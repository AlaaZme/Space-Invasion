#include "stdafx.h"
#include "Display.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <ctime>
#include <thread>
#include <time.h>  
#include "Enemey.h"
#include <time.h>
#include <vector>
#include<windows.h>
#include "mmsystem.h"
#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 720
#define Meter 3
int direction = 7;
int EnemyNum = 30;
bool bosslevel = false;
SDL_Texture* NTexture;
//const int SCREEN_BPP = 32;
bool PlayerAlive = true;
int once = 1;
//SDL_Renderer* renderer;
SDL_Rect bos;
SDL_Rect t, En, BG;
SDL_Window* gWindow = NULL;//The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL;//The surface contained by the window
//SDL_Surface* LoadImage = NULL;//The image we will load and show on the screen
int numshot;


static Uint32 wav_length; // length of our sample
static Uint8 *wav_buffer; // buffer containing our audio file
static SDL_AudioSpec wav_spec;

SDL_Texture* loadTexture(std::string path);
SDL_Renderer* gRenderer = NULL;
SDL_Renderer* Renemy = NULL;//   enemies
Enemey boss(SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Texture* Boss = NULL;
SDL_Texture* Enemeyq = NULL;
SDL_Texture* Enemeyt = NULL;
SDL_Texture* playerRocket = NULL;
SDL_Texture* eTexture1 = NULL;//Current displayed texture
SDL_Texture* Healthexture = NULL;//Current displayed texture
SDL_Texture* gTexture = NULL;//Current displayed texture
SDL_Texture* scoreTexture = NULL;//Current displayed texture
SDL_Texture* eTexture = NULL;//Current displayed texture
SDL_Texture* bg = NULL;//Current displayed texture
SDL_Texture* BoomTexture = NULL;//Current displayed texture
SDL_Texture* EnemeyShot = NULL;//Current displayed texture
SDL_Texture* Winner = NULL;//Current displayed texture



SDL_Rect N;
SDL_Rect S;
bool drawn = false;
bool delay = true;
int currENum = 1;
std::vector<Enemey> ships;// Vector with enemies num created;
SDL_Rect ShotPos;
node* head;
node* ptr;
node* headShot;
Display::Display(){
	gWindow = SDL_CreateWindow("_Space Invasion v1.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		printf("Window Couldn't be created!! ");
		success = false;
	}
	else
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL){
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0x00);

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)){
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}
	}
	// bg = loadTexture("space 1.png");
	bg = loadTexture("space2.png");
	eTexture = loadTexture("rocket2.png");
	//	 Display::NTexture = loadTexture("VS.png");
	NTexture = loadTexture("VS.png");
	BoomTexture = loadTexture("Nuke.png");
	Healthexture = loadTexture("HealthFull.png");
	scoreTexture = loadTexture("score.png");
	Enemeyt = loadTexture("ship3.png");
	Enemeyq = loadTexture("ship4.png");
	Boss = loadTexture("e1.png");
	EnemeyShot = loadTexture("blueball1.png");
	playerRocket = loadTexture("rocket.png");
	Winner = loadTexture("winner.png");
	eTexture1 = eTexture;






	SDL_LoadWAV("Fireball3.wav", &wav_spec, &wav_buffer, &wav_length);
	// set the callback function

	// set our global static variables
	

	t.x = SCREEN_WIDTH / 2;//player coords
	t.h = 80;
	t.y = SCREEN_HEIGHT - t.h * 2;
	t.w = 70;

	N.x = 0;
	N.y = 0;//enemy coords
	N.h = 60;
	N.w = 80;

	S = N;
	S.x = SCREEN_WIDTH - S.w - S.w / 2;

	En.x = 100;//shot coords
	En.y = 100;
	En.h = 55;
	En.w = 55;

	BG.x = 50; // background
	BG.y = 200;
	BG.h = 400;
	BG.w = 1100;
	ships.resize(EnemyNum);
	Enemey ship(SCREEN_WIDTH, SCREEN_HEIGHT / 4);
	ships[0] = ship;
	ships[0].Alive = true;
	for (int i = 0; i < EnemyNum; i++) {
		Enemey ship(SCREEN_WIDTH, SCREEN_HEIGHT/4);
	
		ships[i] = ship;
		if (i % 2 == 0)
		ships[i].speed = 12;
		if (ships[i].shoot == true)
			ships[i].speed = 10;
	}
	head = new node;
	head = NULL;

}
Display::~Display() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}
bool Display::getImage(std::string fileName) {//for later we can get in putfrom user.

	gTexture = loadTexture(fileName);
	return success;
}
void Display::update() {
	SDL_Delay(20);
	//Render teture to screen
	SDL_RenderClear(gRenderer);
	if (BG.y > SCREEN_HEIGHT / 2 - 50)
		BG.y -= 10;
	else
		BG.y = SCREEN_HEIGHT;

	SDL_RenderCopy(gRenderer, bg, &BG, NULL);
	//	SDL_RenderCopy(gRenderer, Healthexture, NULL, &N);//health bar
       
	SDL_RenderCopy(gRenderer, scoreTexture, NULL, &S);//health bar
													  //SDL_RenderCopy(gRenderer, bg, NULL, NULL);//background draw
	SDL_RenderCopy(gRenderer, Healthexture, NULL, &N);//health bar
										
	if (head != NULL) {//draw players shots
		if (head->y < 0)
			head = head->next;
		//else if(head->ShotPos.y)
		else {
			ptr = head;
			while (ptr->next) {
				ptr->y -= 7;
				ShotPos.x = ptr->x;
				ShotPos.y = ptr->y;
				ShotPos.h = ptr->h;
				ShotPos.w = ptr->w;
				if (ptr->hit == false) {
					if (ships[13].Alive)
						SDL_RenderCopy(gRenderer, eTexture1, NULL, &ShotPos);//the shot
					else
						SDL_RenderCopy(gRenderer, playerRocket, NULL, &ShotPos);
				}
				ptr = ptr->next;
			}
		}
	}
	ptr = headShot;//draw enemey shots
	
	drawEnemies(head);
	//Render texture to screen
	SDL_RenderCopy(gRenderer, gTexture, NULL, &t);//player
												  //Update screen
	SDL_RenderPresent(gRenderer);
}
bool Display::chkPress() {    //quit???
	SDL_Event e;
	//int once=1;
	if (SDL_PollEvent(&e) != 0) {
		SDL_Keycode keyPressed = e.key.keysym.sym;
		if (e.type == SDL_KEYDOWN) {
			//	SDL_Keycode keyPressed = e.key.keysym.sym;
			if (keyPressed == SDLK_SPACE && once == 1) {
				node *newNode = new node;
				newNode->hit = false;
				newNode->x = t.x;
				newNode->y = t.y;
				newNode->h = En.h;
				newNode->w = En.w;
				
				moveShot(newNode);
				
				once = 0;
				return false;
			}
		}
		if (e.type == SDL_KEYUP) {
			if (keyPressed == SDLK_SPACE)
				once = 1;
		}
		if (e.type == SDL_QUIT)
			return true;

		else if (ships[0].bossDead ) {
			if (PlayerAlive) {
		
				//BoomTexture = loadTexture("winner.png");
		    	SDL_RenderCopy(gRenderer, BoomTexture, NULL, NULL);

				SDL_RenderCopy(gRenderer, Winner, NULL, NULL);

				//	bosslevel = true;
				SDL_RenderPresent(gRenderer);
				SDL_Delay(1000);
			}
			return true;
		}
	}
	const Uint8 *KeyStates = SDL_GetKeyboardState(NULL);
	if (KeyStates[SDL_SCANCODE_DOWN]) {
		if (t.y + Meter + t.h < SCREEN_HEIGHT)
			t.y += Meter * 3;
	}
	if (KeyStates[SDL_SCANCODE_UP]) {
		if (t.y - Meter > 0)
			t.y -= Meter * 3;
	}
	if (KeyStates[SDL_SCANCODE_LEFT]) {
		if (t.x - Meter > 0)
			t.x -= Meter * 3;
	}
	if (KeyStates[SDL_SCANCODE_RIGHT]) {
		if (t.x + Meter + t.w < SCREEN_WIDTH)
			t.x += Meter * 3;
	}
	return false;
}
SDL_Texture* loadTexture(std::string path){
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	else	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface 
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
bool Display::Win() {
	if (!ships[0].bossDead)
		for (int i = 0; i < EnemyNum; i++) {
			if (ships[i].Alive)
				return false;
		}
}
void Display::moveShot(node* newNode) {
	//PlaySound(TEXT("soundrocket.wav"), NULL, 1);
	//PlaySound(TEXT("Fireball3.wav"), NULL, SND_ASYNC);
	SDL_OpenAudio(&wav_spec, NULL);
	node *tempNode;
	newNode->next = NULL;
	if (head == NULL) {
		head = newNode;
	}
	else {
		tempNode = head;
		tempNode->next = head->next;
		newNode->next = tempNode;
		head = newNode;
	}
	update();
}
void Display::drawEnemies(node* shot) {
	//int direction = 5;
	int Mforward = 8;
	int Mback = -1;

	


	if (Win() && !ships[0].bossDead) {
		bosslevel = true;
		ships[0] = boss;
		ships[0].speed = 8;
		ships[0].shoot = true;
		ships[0].Alive = true;
		ships[0].EnemeyPos.x = SCREEN_WIDTH / 2;
		ships[0].EnemeyPos.y = SCREEN_HEIGHT / 8;
	}
	if (bosslevel) { //the bos movment + draw
		ships[0].EnemeyPos.h = 175;
		ships[0].EnemeyPos.w = 175;
		if (ships[0].EnemeyPos.x + ships[0].EnemeyPos.w >= SCREEN_WIDTH)
			direction *= -1;
		if (ships[0].EnemeyPos.x < 10)
			direction *= -1;
		ships[0].EnemeyPos.x += direction;

		if (ships[0].EnemeyPos.y > SCREEN_HEIGHT + ships[0].EnemeyPos.h || ships[0].EnemeyPos.y < 0)
			ships[0].speed *= -1;
		ships[0].EnemeyPos.y += ships[0].speed;

		if (ships[0].health < 1) {  //boss is dead
			ships[0].bossDead = true;
			ships[0].Alive = false;
			bosslevel = false;
			//SDL_Delay(500);
		}
		//ships.resize(EnemyNum++);
		if (ships[0].health % 2 == 0) {
			ships[ships[0].health].Alive = true;
			ships[ships[0].health].speed = 10;
			ships[ships[0].health].EnemeyPos.x = ships[0].EnemeyPos.x + ships[0].EnemeyPos.w/4;
			ships[ships[0].health].EnemeyPos.y = ships[0].EnemeyPos.y;

			ships[ships[0].health].EnemeyPos.w =150;
			ships[ships[0].health].EnemeyPos.h= 150;
			
		}
		drawn = 1;
		//  SDL_RenderCopy(gRenderer, Boss, NULL, &ships[0].EnemeyPos);
	}
		for (int i = 0; i < EnemyNum; i++) {//small enemey shots




			if (ships[i].Alive&&ships[i].shoot&&ships[i].EnemeyPos.y < SCREEN_HEIGHT / 4 && ships[i].EnemeyPos.y>100&&!ships[i].fired) {
				ships.resize(EnemyNum+=1);
				Enemey s = Enemey(SCREEN_WIDTH, SCREEN_HEIGHT);
				s.EnemeyPos.x = ships[i].EnemeyPos.x + ships[i].EnemeyPos.w/3;
				s.EnemeyPos.y = ships[i].EnemeyPos.y;
				s.EnemeyPos.w = ships[i].EnemeyPos.w/2 ;
				s.EnemeyPos.h = ships[i].EnemeyPos.h;
				s.Alive = true;
				s.shoot = false;
				s.speed = 15;
				ships[EnemyNum -= 1]=s;
				EnemyNum++;
				ships[i].fired = true;
			}

			//if the player got hit

		if ((ships[i].Alive) && (t.x + t.w / 2 > ships[i].EnemeyPos.x&&t.x < ships[i].EnemeyPos.x + ships[i].EnemeyPos.w / 2) &&
			(t.y < ships[i].EnemeyPos.y + ships[i].EnemeyPos.h - Meter && t.y > ships[i].EnemeyPos.y + Meter)) {
			
			ships[i].Alive = false;   // To Kill CHANGER HERE
			if (i == 13)
				eTexture1 = playerRocket;
			PlayerAlive = false;
			SDL_RenderCopy(gRenderer, BoomTexture, NULL, NULL);
			SDL_RenderPresent(gRenderer);
			SDL_Delay(250);
			BoomTexture = loadTexture("loser.png");
			SDL_RenderCopy(gRenderer, BoomTexture, NULL, NULL);
			SDL_RenderPresent(gRenderer);
			SDL_Delay(250);
			gRenderer = NULL;
		}
		
 		ptr = shot;
	//	node* prev = shot;
		while (ptr!= NULL) {//check if ship was hit

			if (ptr != NULL&&ships[i].Alive && (ptr->x + ptr->w / 2 > ships[i].EnemeyPos.x&& ptr->x<ships[i].EnemeyPos.x + ships[i].EnemeyPos.w / 2) &&
				(ptr->y > ships[i].EnemeyPos.y + ships[i].EnemeyPos.h  && ptr->y < ships[i].EnemeyPos.y + ships[i].EnemeyPos.h + ptr->h / 2)) {
			//	ptr->hit = true;
			//	PlaySound(TEXT("soundrocket.wav"), NULL, 1);
				if (!bosslevel&&ptr->hit==false) {
					PlaySound(TEXT("EXPL.wav"), NULL, SND_ASYNC);
					ships[i].Alive = false;   // To Kill CHANGER HERE
				//	prev->next = ptr->next;
				}
				if (bosslevel && i==0) {
					ships[0].health -= 1;
					PlaySound(TEXT("EXPL.wav"), NULL, 1);
				}
				if(ptr->hit==false)
				SDL_RenderCopy(gRenderer, BoomTexture, NULL, &ships[i].EnemeyPos);
				SDL_RenderPresent(gRenderer);
				SDL_Delay(3);
				ptr->hit = true;
			}
		
			ptr = ptr->next;
		}

		if (ships[i].Alive == true ) {//redraw enemines in start of screen
			if (ships[i].EnemeyPos.y < SCREEN_WIDTH)
				ships[i].EnemeyPos.y += ships[i].speed;//with movment down
			else {
				while (ships[i].EnemeyPos.y != 0 && i < 30&&!bosslevel) {
				
						ships[i].EnemeyPos.y -= 1;
			

				/*	if (ships[currENum-1].EnemeyPos.y > 50 && !bosslevel)
						delay = true;
			*/
				}
				if (i > 29)
					ships[i].Alive = false;
				    ships[i].fired = false;
			}
		/*	if (i == 0)
				ships[i].fired = false;*/

	

			if ((bosslevel&&i!=0)||i>29)
				SDL_RenderCopy(gRenderer, EnemeyShot, NULL, &ships[i].EnemeyPos);
			else if (ships[i].shoot == true)
				SDL_RenderCopy(gRenderer, Enemeyq, NULL, &ships[i].EnemeyPos);
			else if (i % 2 == 1)//draws the enemies
				SDL_RenderCopy(gRenderer, NTexture, NULL, &ships[i].EnemeyPos);
		//	else if(bosslevel)
		//		SDL_RenderCopy(gRenderer, EnemeyShot, NULL, &ships[i].EnemeyPos);
			else //(i % 2 == 0)
				SDL_RenderCopy(gRenderer, Enemeyt, NULL, &ships[i].EnemeyPos);
			//else if(i%3==0)
			//	SDL_RenderCopy(gRenderer, Enemeyq, NULL, &ships[i].EnemeyPos);
		}
	}
}







/*	for (int i = 0; i<level; i++) {
		if ((En.x + En.w > ships[i].EnemeyPos.x&& En.x<ships[i].EnemeyPos.x + ships[i].EnemeyPos.w + En.w) &&
			(En.y > ships[i].EnemeyPos.y + En.h && En.y < ships[i].EnemeyPos.y + ships[i].EnemeyPos.h + En.h / 2)) 
			ships[i].Alive = false;

		if (ships[i].Alive == true) {
			SDL_RenderCopy(gRenderer, NTexture, NULL, &ships[i].EnemeyPos);
			SDL_RenderPresent(gRenderer);
		}

	}
	*/
//}


/*implement keys by Listener //single press check.

/*	switch (keyPressed) {
//	if (e.type == SDL_KEYDOWN) {
//		SDL_Keycode keyPressed = e.key.keysym.sym;

case SDLK_DOWN:
t.y += 20;
printf("DOWN/n");
return false;
case SDLK_UP:
//	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
t.y -= 10;
printf("UP\n");
return false;
case SDLK_LEFT:
//	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0x00);
t.x -= 10;
printf("LEFT\n");
return false;
case SDLK_RIGHT:
//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
t.x += 10;
printf("RIGHT\n");
return false;

case SDLK_SPACE:
En.x = t.x + En.w / 2;
En.y = t.y - En.h / 2;
std::thread t1(&Display::moveShot, this);
t1.join();
printf("space");
//return false;
}
}
}*/
void Display::Delay() {

	SDL_Delay(1);
}