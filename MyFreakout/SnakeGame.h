#include <windows.h>        // include important windows stuff
#include <windowsx.h> 

// states for game loop
#define GAME_STATE_INIT         0
#define GAME_STATE_START_LEVEL  1
#define GAME_STATE_RUN          2
#define GAME_STATE_SHUTDOWN     3
#define GAME_STATE_EXIT         4 


namespace SnakeGame{
int Game_Init(void *parms=NULL);
int Game_Shutdown(void *parms=NULL);
int Game_Main(void *parms=NULL , HWND main_window_handle=NULL);
}