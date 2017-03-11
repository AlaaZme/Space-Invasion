// SpaceInv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include  "Display.h"
//#include <SDL.h>
#include <thread>
#include <ctime>



int main()
{
	bool quit = false;
	Display dsp; 
	dsp.getImage("player2.png");
	while (!quit) {
//	dsp.Delay();
    quit= dsp.chkPress();

	dsp.update();


	}

    return 0;
}

