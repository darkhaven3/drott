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
#ifndef _cin_efct_public
#define _cin_efct_public

#include "cin_glob.h"
#include "cin_def.h"

flicevent * SpawnCinematicFlic ( char * name, boolean loop, boolean usefile );
spriteevent * SpawnCinematicSprite ( char * name,
                                     int duration,
                                     int numframes,
                                     int framedelay,
                                     int x,
                                     int y,
                                     int scale,
                                     int endx,
                                     int endy,
                                     int endscale
                                   );
backevent * SpawnCinematicBack ( char * name,
                                 int duration,
                                 int width,
                                 int startx,
                                 int endx,
                                 int yoffset
                               );

backevent * SpawnCinematicMultiBack ( char * name,
                                      char * name2,
                                      int duration,
                                      int startx,
                                      int endx,
                                      int yoffset
                                    );
paletteevent * SpawnCinematicPalette ( char * name );
void DrawFlic ( flicevent * flic );
void DrawCinematicBackdrop ( backevent * back );
void DrawCinematicBackground ( backevent * back );
void DrawCinematicSprite ( spriteevent * sprite );
void DrawClearBuffer ( void );
void DrawBlankScreen ( void );
boolean DrawCinematicEffect ( enum_eventtype type, void * effect );
boolean UpdateCinematicBack ( backevent * back );
boolean UpdateCinematicSprite ( spriteevent * sprite );
boolean UpdateCinematicEffect ( enum_eventtype type, void * effect );
void PrecacheCinematicEffect ( enum_eventtype type, void * effect );
void ProfileDisplay ( void );
void DrawPostPic ( int lumpnum );

#endif

