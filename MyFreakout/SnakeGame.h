#include <windows.h>        // include important windows stuff
#include <windowsx.h> 

namespace SnakeGame{
int Game_Init(void *parms=NULL);
int Game_Shutdown(void *parms=NULL);
int Game_Main(void *parms=NULL , HWND main_window_handle=NULL);
}