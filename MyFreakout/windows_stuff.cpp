#include "windows_stuff.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,WPARAM wparam,LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT	ps;		   // used in WM_PAINT
	HDC			hdc;	   // handle to a device context

	// what is the message 
	switch(msg)
	{	
	case WM_CREATE: 
		{
			// do initialization stuff here
			return(0);
		} break;

	case WM_PAINT:
		{
			// start painting
			hdc = BeginPaint(hwnd,&ps);

			// the window is now validated 

			// end painting
			EndPaint(hwnd,&ps);
			return(0);
		} break;

	case WM_DESTROY: 
		{
			// kill the application			
			PostQuitMessage(0);
			return(0);
		} break;

	default:break;

	} // end switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

int check_messages(MSG &msg){
	// generic message
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{ 
		// test if this is a quit
		if (msg.message == WM_QUIT)
			return 0;

		// translate any accelerator keys
		TranslateMessage(&msg);

		// send the message to the window proc
		DispatchMessage(&msg);
	} // end if

	return 0;
}