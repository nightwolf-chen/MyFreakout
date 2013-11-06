#pragma once

#include <dsound.h>
#include <windows.h> 
#include <mmsystem.h>

// digital sound object state defines
#define SOUND_NULL     0 // " "
#define SOUND_LOADED   1
#define SOUND_PLAYING  2
#define SOUND_STOPPED  3
#define MAX_SOUNDS     256 // max number of sounds in system at once 

#ifndef DSBCAPS_CTRLDEFAULT
#define DSBCAPS_CTRLDEFAULT (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME )
#endif

void playBackgroundMusic(HWND main_window_handle);

