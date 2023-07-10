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
// RT_FLOOR.C

#include "rt_def.h"
#include "watcom.h"
#include "rt_floor.h"
#include "rt_fc_a.h"
#include "_rt_floo.h"
#include "rt_draw.h"
#include "rt_util.h"
#include "engine.h"
#include "rt_main.h"
#include "w_wad.h"
#include "z_zone.h"
#include "rt_view.h"
#include "rt_ted.h"
#include "rt_cfg.h"
#include "rt_actor.h"
#include <string.h>
#include "isr.h"
#include "modexlib.h"
#include "rt_playr.h"
#include "rt_sound.h"
#include "rt_rand.h"
#include "memcheck.h"   //MED

//
// global variables
//

int      sky;
int		mr_rowofs;
int		mr_count;
int		mr_xstep;
int		mr_ystep;
int		mr_xfrac;
int		mr_yfrac;
byte *   mr_dest;
byte *   mr_src;

//
// local variables
//

static byte     *floor;
static byte     *ceiling;
static int xstarts[1440];           //[*** FREERES SUPPORT ***]
static byte * skysegs[MAXSKYSEGS];
static byte * skydata[MAXSKYDATA];
static int      horizonheight;
static int      centerskypost;
static int      oldsky=-1;


//bna fixit skyerror by 800x600 clouds not big enough

void DrawSky(void) {
    byte* src;
    int dest;
    int height;
    int ang;
    int angle;
    int ofs;

    angle = viewangle;

    if (!fog && lightning) shadingtable = colormap + ((basemaxshade - 6 - lightninglevel) << 8);
    else shadingtable = colormap + (1 << 12);

    ofs = (((maxheight)-(player->z)) >> 3) + (centery * 200 / iGLOBAL_SCREENHEIGHT - ((viewheight * 200 / iGLOBAL_SCREENHEIGHT) >> 1));

    if (ofs > centerskypost) ofs = centerskypost;
    else if (((centerskypost - ofs) + viewheight * 200 / iGLOBAL_SCREENHEIGHT) > 1799) ofs = -(1799 - (centerskypost + viewheight * 200 / iGLOBAL_SCREENHEIGHT));

    for (dest = 0; dest < viewwidth; dest++) {
        if ((height = posts[dest].ceilingclip) <= 0) continue;

        ang = (angle + pixelangle[dest]) & (FINEANGLES - 1);
        src = skysegs[ang] - ofs;
        DrawSkyPost((byte*)bufferofs + dest, src, height);
    }
}

/*
===================
=
= DrawFullSky
=
===================
*/
void DrawFullSky(void) {

    byte* src;
    int dest;
    int plane;
    int ang;
    int angle;
    int ofs;

    angle = viewangle;

    if (!fog && lightning) shadingtable = colormap + ((basemaxshade - 5 - lightninglevel) << 8);
    else shadingtable = colormap + (1 << 12);

    ofs = (((maxheight)-(player->z)) >> 3) + (centery - (viewheight >> 1));

    if (ofs > centerskypost) ofs = centerskypost;
    else if (((centerskypost - ofs) + viewheight) > 599) ofs = -(599 - (centerskypost + viewheight));

    bufferofs += screenofs;

    for (dest = 0; dest < viewwidth; dest++) {
        ang = (angle + pixelangle[dest]) & (FINEANGLES - 1);
        src = skysegs[ang] - ofs;
        DrawSkyPost((byte*)bufferofs + dest, src, viewheight);
    }
    bufferofs -= screenofs;
}

/*
===================
=
= MakeSkyTile
=
===================
*/
void MakeSkyTile(byte* tile) {
    int srcstep = 200 << 10;
    int src;

    for (int i = 0; i < 64; i++) {

        src = 0;
        for (int j = 0; j < 64; j++) {
            *(tile + (i << 6) + j) = *(skysegs[(i << 2)] + (src >> 16));
            src += srcstep;
        }
    }
}

/*
===================
=
= MakeSkyData
=
===================
*/
void MakeSkyData (void) {

   byte * temp=SafeMalloc(256*800);
   byte * ptr=temp;

   for (int c = 0; c < 256; c++) {
       memcpy(ptr, skydata[1] + (c * 200), 200);
       ptr += 200;

       memcpy(ptr, skydata[0] + (c * 200), 200);
       ptr += 200;
   }

   skydata[0]=temp;
}

/*
===================
=
= GetFloorCeilingLump
=
===================
*/
int GetFloorCeilingLump(int num) {

   int lump;

   //wip - generalize some more
   char lumpname[9] = "FLRCL\0\0\0\0";

   if (num < 10) {
       lumpname[5] = '0' + num;
       lumpname[6] = '\0';
   }
   else if (num < 20) {
       lumpname[5] = '1';
       lumpname[6] = '0' + (num % 10);
   }
   else if (num < 30) {
       lumpname[5] = '2';
       lumpname[6] = '0' + (num % 10);
   }
   else if (num < 40) {
       lumpname[5] = '3';
       lumpname[6] = '0' + (num % 10);
   }
   else if (num < 50) {
       lumpname[5] = '4';
       lumpname[6] = '0' + (num % 10);
   }
   else if (num < 60) {
       lumpname[5] = '5';
       lumpname[6] = '0' + (num % 10);
   }
   else if (num < 70) {
       lumpname[5] = '6';
       lumpname[6] = '0' + (num % 10);
   }
   else if (num < 80) {
       lumpname[5] = '7';
       lumpname[6] = '0' + (num % 10);
   }
   else if (num < 90) {
       lumpname[5] = '8';
       lumpname[6] = '0' + (num % 10);
   }
   else if (num < 100) {
       lumpname[5] = '9';
       lumpname[6] = '0' + (num % 10);
   }
   lump = W_GetNumForName(lumpname);
   return lump;
}

/*
===================
=
= RT_SkyExists
=
===================
*/

#define TILE_FIRSTSKY   233
#define TILE_LIGHTNING  377

int32_t RT_SkyExists(void) {
    int32_t skyvalue;

    skyvalue = MAPSPOT(1, 0, 0) - TILE_FIRSTSKY;
    if (skyvalue > 0) return skyvalue;
    else return 0;
}

/*
===================
=
= RT_SetPlaneViewSize
=
===================
*/

void RT_SetPlaneViewSize (void)
{
   int      x;
   int      i;
   int      s;
   int      floornum;
   int      ceilingnum;
   int      skytop;
   int      skybottom;
   int16_t crud;

   sky=0;

   if (oldsky>0)
      {
      SafeFree(skydata[0]);     //[TODO]: make Z_Free safe
      oldsky=-1;
      }

   lightning=false;

   sky = RT_SkyExists();
   if (sky)
   {
       if ((sky < 1) || (sky > 6)) Error("Illegal Sky Tile = %d\n", sky);
       ceilingnum = 1;
       crud = (int16_t)MAPSPOT(1, 0, 1);
       if ((crud >= 90) && (crud <= 97)) horizonheight = crud - 89;
       else if ((crud >= 450) && (crud <= 457)) horizonheight = crud - 450 + 9;
       else horizonheight = 9;
       //I_Warning("RT_SetPlaneViewSize: missing or unknown horizon height icon");

      // Check for lightning icon

       /*
       crud=(word)MAPSPOT(4,0,1);
       if (crud==377)
         lightning=true;
      */

       lightning = (MAPSPOT(4, 0, 1) == TILE_LIGHTNING);
   }

	else
	 ceilingnum = MAPSPOT(1,0,0)-197;

	floornum = MAPSPOT(0,0,0)-(179);

   floornum = GetFloorCeilingLump ( floornum );
   //ceilingnum = GetFloorCeilingLump ( ceilingnum );

   floor = W_CacheLumpNum(floornum,PU_LEVELSTRUCT, Cvt_patch_t, 1);
   floor +=8;

   if (sky==0)  // Don't cache in if not used
      {
      ceilingnum = GetFloorCeilingLump ( ceilingnum );
      ceiling = W_CacheLumpNum(ceilingnum,PU_LEVELSTRUCT, Cvt_patch_t, 1);
      ceiling +=8;
      } else {
      	ceiling = NULL;
      }

	s = W_GetNumForName("SKYSTART");

   switch (sky)
      {
      case 1:
         skytop=s+1;
         skybottom=s+2;
         break;
      case 2:
         skytop=s+3;
         skybottom=s+4;
         break;
      case 3:
         skytop=s+5;
         skybottom=s+6;
         break;
      case 4:
         skytop=s+7;
         skybottom=s+8;
         break;
      case 5:
         skytop=s+9;
         skybottom=s+10;
         break;
      case 6:
         skytop=s+11;
         skybottom=s+12;
         break;
      }
      if (sky!=0)
         {
         skydata[0]=W_CacheLumpNum(skytop,PU_STATIC, CvtNull, 1);
         skydata[1]=W_CacheLumpNum(skybottom,PU_STATIC, CvtNull, 1);
         centerskypost=MINSKYHEIGHT-(horizonheight*6);
         oldsky=sky;
         MakeSkyData();
         W_CacheLumpNum(skytop,PU_CACHE, CvtNull, 1);
         W_CacheLumpNum(skybottom,PU_CACHE, CvtNull, 1);
         x=511;
         for (i=0;i<MAXSKYSEGS;i++)
            {
            skysegs[i]=skydata[0]+((x>>1)*400)+centerskypost;
            x--;
            if (x==-1)
               {
               x=511;
               }
            } /* endfor */
         }
}

/*
==========================
=
= SetFCLightLevel
=
==========================
*/
void SetFCLightLevel(int height)
{
    int i;

    if (MISCVARS->GASON == 1) {
        shadingtable = greenmap + (MISCVARS->gasindex << 8);
        return;
    }
    if (fulllight) {
        shadingtable = colormap + (1 << 12);
        return;
    }
    if (fog) {
        i = ((height * 200 / iGLOBAL_SCREENHEIGHT) >> normalshade) + minshade;
        if (i > maxshade) i = maxshade;
        shadingtable = colormap + (i << 8);
    }
    else {
        i = maxshade - (height >> normalshade);
        if (i < minshade) i = minshade;
        shadingtable = colormap + (i << 8);
    }
}



void DrawHLine (int xleft, int xright, int yp)
{
   int plane;
   byte * buf;
   byte * dest;
   int startxfrac;
   int startyfrac;
   int height;
//   int length;
   int ofs;

   if (yp==centery)
      return;
   if (yp>centery)
      {
      int hd;

      buf=floor;
      hd=yp-centery;
      height=(hd<<13)/(maxheight-pheight+32);
      }
   else
      {
      int hd;

      /* ROTT bug? It'd draw when there was no ceiling. - SBF */
      if (ceiling == NULL) return;
      
      buf=ceiling;
      
      hd=centery-yp;
      height=(hd<<13)/pheight;
      }
   SetFCLightLevel(height>>(8-HEIGHTFRACTION-1));
	mr_xstep = ((viewsin<<8)/(height));
	mr_ystep = ((viewcos<<8)/(height));

	startxfrac = ((viewx>>1) + FixedMulShift(mr_ystep,scale,2))-
                FixedMulShift(mr_xstep,(centerx-xleft),2);

	startyfrac = ((viewy>>1) - FixedMulShift(mr_xstep,scale,2))-
                FixedMulShift(mr_ystep,(centerx-xleft),2);

   dest=(byte *)bufferofs+ylookup[yp];

/* TODO: horizontal isn't as easy as vertical in packed */
         mr_dest=dest+xleft;
         mr_xfrac = startxfrac;
         mr_yfrac = startyfrac;

        // back off the pixel increment (orig. is 4x)
        mr_xstep >>= 2;
        mr_ystep >>= 2;
        mr_count = xright-xleft+1;
        if (mr_count)  DrawRow(mr_count,mr_dest,buf);

}

void DrawPlanes(void) {
    int x, y;
    int twall;
    int bwall;

    if (sky) DrawSky();
    else {
        y = 0;
        for (x = 0; x < viewwidth; x++) {
            twall = posts[x].ceilingclip;
            while (y < twall) xstarts[y++] = x;
            while (y > twall)  DrawHLine(xstarts[--y], x - 1, y);
        }
        while (y > 0) DrawHLine(xstarts[--y], viewwidth - 1, y);
    }
    y = viewheight - 1;

    for (x = 0; x < viewwidth; x++) {
        bwall = posts[x].floorclip;
        while (y > bwall) xstarts[y--] = x;
        while (y < bwall) DrawHLine(xstarts[++y], x - 1, y);
    }
    while (y < viewheight - 1) DrawHLine(xstarts[++y], viewwidth - 1, y);
}

void DrawRow(int count, byte* dest, byte* src) {
    unsigned frac, fracstep;
    int coord;

    frac = (mr_yfrac << 16) + (mr_xfrac & 0xffff);
    fracstep = (mr_ystep << 16) + (mr_xstep & 0xffff);

    while (count--) {
        /* extract the x/y coordinates */
        coord = ( (frac >> 25) | (frac >> 9) << 7) & 16383;    //32-5, 32-23
        *dest++ = shadingtable[src[coord]];
        frac += fracstep;
    }
}
