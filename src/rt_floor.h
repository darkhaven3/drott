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
#ifndef _rt_floor_public
#define _rt_floor_public

//***************************************************************************
//
//    RT_FLOOR.C - Floor and Ceiling stuff
//
//***************************************************************************

#define TILE_FIRSTFLOOR 179
#define TILE_FIRSTCEIL  197
#define TILE_FIRSTSKY   233
#define TILE_LIGHTNING  377

extern int		mr_xstep;
extern int		mr_ystep;
extern int		mr_xfrac;
extern int		mr_yfrac;

extern int     sky;      //Whether Parallax is on or off
void DrawPlanes (void);
void SetPlaneViewSize( void );
void MakeSkyTile (byte * tile);
void DrawFullSky( void );
int32_t F_SkyExists(void);

#endif



