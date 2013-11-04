#include <windows.h>        // include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>

int check_messages(MSG &msg);
LRESULT CALLBACK WindowProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);