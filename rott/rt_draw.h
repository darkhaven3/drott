/*
Copyright (C) 1994-1995 Apogee Software, Ltd.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#ifndef _rt_draw_public
#define _rt_draw_public

#include <stdint.h>

//***************************************************************************
//
//    RT_DRAW.C - Draw-o-rama
//
//***************************************************************************


#define MAXVISIBLE              2048		//max visible scaled sprites. raised from 256 -> 2048
#define MAXVISIBLEDOORS         256	        //changed from 30->256

#define SCALECONSTANT			0x8000	//:thinking:

//idmypos-like -- R_DrawPlayerLocation
#define R_DRAWTHINGLOCATION_X  296
#define R_DRAWTHINGLOCATION_Y  16

//=========================== macros =============================

#define LightSourceAt(x,y)    (*(lights+((x)<<7)+(y)))
#define SetLight(x,y,level)   (LightSourceAt((x),(y))|=(unsigned long)(level))

//viewdim_t
// holds the X and Y dimensions of the size of the render viewport.
// used to replace the original implementation of viewsizes[].
typedef struct {
    uint32_t size_x;
    uint32_t size_y;
} viewdim_t;

typedef struct {
    int32_t viewheight;
    int32_t viewx;
    int32_t shapenum;
    int32_t altshapenum;
    int32_t shapesize;
    int32_t x1, x2, h1, h2;
    int32_t texturestart;
    int32_t textureend;
    uint8_t* colormap;
} visobj_t;

//
// global imports
//
extern  uint8_t   *shadingtable;                // Shading table for DrawPost
extern  uint16_t  tilemap[MAPSIZE][MAPSIZE];    // wall values only
extern  uint8_t   spotvis[MAPSIZE][MAPSIZE];
extern  int32_t   tics;
extern  int32_t   wstart;
extern  int32_t   fandc;

// math tables
extern int16_t      tantable[FINEANGLES];
extern fixed32_t    sintable[FINEANGLES+FINEANGLEQUAD+1];
extern fixed32_t    *costable;

// refresh variables
extern fixed32_t   viewx,viewy;             // the focal point
extern int32_t     viewangle;
extern fixed32_t   viewsin,viewcos;

// ray tracing variables
extern visobj_t vislist[MAXVISIBLE];
extern visobj_t *visptr,*visstep,*farthest;

extern int32_t   xintercept,yintercept;
extern uint8_t   mapseen[MAPSIZE][MAPSIZE];
extern uint32_t* lights;

extern int32_t hp_startfrac;
extern int32_t hp_srcstep;
extern int32_t levelheight;
extern int32_t maxheight;
extern int32_t nominalheight;

extern int32_t actortime;
extern int32_t drawtime;
extern int32_t c_startx;
extern int32_t c_starty;

extern int32_t firstcoloffset;

//constants
extern const int32_t dirangle8[9];
extern const int32_t dirangle16[16];

//=========================== functions =============================

void BuildTables(void);
void CalcTics(void);
void ThreeDRefresh(void);
void FlipPage(void);
void TurnShakeOff(void);
void AdaptDetail(void);
int  CalcHeight(void);
void DoLoadGameSequence(void);
void RotateBuffer(int startangle, int endangle, int startscale, int endscale, int time);
void ApogeeTitle(void);
void DopefishTitle(void);
void RotationFun(void);
void GetRainBoundingBox(int* xmin, int* xmax, int* ymin, int* ymax);
void StartupScreenSaver(void);
void ShutdownScreenSaver(void);
void UpdateScreenSaver(void);
void DoEndCinematic(void);
void DoCreditScreen(void);
void DoMicroStoryScreen(void);
void DoInBetweenCinematic(int yoffset, int lump, int delay, char* string);
void SetColorLightLevel(int x, int y, visobj_t* sprite, int dir, int color, int fullbright);
void DrawRotatedScreen(int cx, int cy, byte* destscreen, int angle, int scale, int masked);     // :thinking:
void InterpolateMaskedWall(visobj_t* plane);
void InterpolateDoor(visobj_t* plane);
void InterpolateWall(visobj_t* plane);
void R_RefreshClear(void);
void R_DrawWallColumn(byte* buf);
void DrawMenuPost(int height, byte* src, byte* buf); // IN rt_dr_a.asm	//?
void DrawMapPost(int height, byte* src, byte* buf); // IN rt_dr_a.asm	//?

#endif
