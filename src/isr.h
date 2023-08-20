/*
Copyright (C) 1994-1995  Apogee Software, Ltd.
Copyright (C) 2002-2015  icculus.org, GNU/Linux port
Copyright (C) 2017-2018  Steven LeVesque

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef _isr_public
#define _isr_public

#include "keyb.h"

//***************************************************************************
//
//    ISR.C - Interrupt Service Routines (Keyboard, timer)
//
//***************************************************************************

//***************************************************************************
//
//    ISR Constants
//
//***************************************************************************

#define VBLCOUNTER   35


#define KEYQMAX      256
#define MAXKEYBOARDSCAN         128

#define scroll_lock  0
#define num_lock     1
#define caps_lock    2

extern volatile int KeyboardQueue[KEYQMAX];
extern volatile int Keyhead;
extern volatile int Keytail;

extern volatile int Keyboard[MAXKEYBOARDSCAN];   // Keyboard status array
extern volatile int Keystate[MAXKEYBOARDSCAN];   // Keyboard state array

int GetTicCount (void);
int GetFastTics (void);

void SetFastTics(int);

extern int KeyboardStarted;

extern const int ASCIINames[];   // Ascii -> scan code conversion
extern const int ShiftNames[];   // Shifted Ascii->scancode conversion
extern volatile boolean PausePressed;  //Game paused variable
extern volatile boolean PanicPressed;  //Panic key variable

void I_StartupTimer (void);        // Start up timer isr
void I_ShutdownTimer (void);       // Shutdown timer isr
void I_StartupKeyboard (void);     // Startup Keyboard isr
void I_ShutdownKeyboard (void);    // Shutdown keyboard isr
void I_Delay ( int delay );
void ISR_SetTime(int settime);

#endif
