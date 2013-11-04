// FREAKOUT.CPP - break game demo

// INCLUDES ///////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN // include all macros
#define INITGUID            // include all GUIDs 

#include <iostream>       // include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>

#include "blackbox.h"     // game library includes
#include "SnakeGame.h"
#include "windows_stuff.h"

using namespace SnakeGame;

// DEFINES ////////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME "WIN3DCLASS"  // class name


//GLOBALS ////////////////////////////////////////////////////
HWND main_window_handle  = NULL; // save the window handle
HINSTANCE main_instance  = NULL; // save the instance

//windows structures to use
WNDCLASS winclass;	// this will hold the class we create
HWND	 hwnd;		// generic window handle
MSG		 msg;		// generic message
HDC      hdc;       // generic dc
PAINTSTRUCT ps;     // generic paintstruct

//Helper function define
int init_window(HINSTANCE hinstance);

int WINAPI WinMain(	HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int ncmdshow)
{

	init_window(hinstance);
	Game_Init();

	// enter main event loop
	while(1)
	{
		check_messages(msg);
		Game_Main(NULL,main_window_handle);
	}

	Game_Shutdown();

	// show mouse
	ShowCursor(TRUE);

	// return to Windows like this
	return(msg.wParam);

} // end WinMain



//Helpers
int init_window(HINSTANCE hinstance)
{
	// first fill in the window class stucture
	winclass.style			= CS_DBLCLKS | CS_OWNDC | 
		CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; 
	winclass.lpszClassName	= WINDOW_CLASS_NAME;

	// register the window class
	if (!RegisterClass(&winclass))
		return(0);

	// create the window, note the use of WS_POPUP
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME,    // class
		"nirvawolf game studio.",	// title
		WS_POPUP | WS_VISIBLE,
		0,0,	                // initial x,y
		GetSystemMetrics(SM_CXSCREEN),  // intial width
		GetSystemMetrics(SM_CYSCREEN),  // initial height
		NULL,	    // handle to parent 
		NULL,	    // handle to menu
		hinstance,// instance
		NULL)))	// creation parms
		return(0);

	// hide mouse
	ShowCursor(FALSE);

	// save the window handle and instance in a global
	main_window_handle = hwnd;
	main_instance      = hinstance;
}

