/* Routines from winrott needed for the highres support for the SDL port */
#include <stdlib.h>
#include <string.h>
#include "WinRott.h"
#include "modexlib.h"

//typedef unsigned char byte;

int iGLOBAL_SCREENWIDTH  = 640;//bna val 800
int iGLOBAL_SCREENHEIGHT = 480;//bna val 600
int iGLOBAL_SCREENBWIDE ;
int iGLOBAL_WINDOWWIDTH = 640;
int iGLOBAL_WINDOWHEIGHT = 480;
int iG_SCREENWIDTH;// default screen width in bytes

int iGLOBAL_HEALTH_X;
int iGLOBAL_HEALTH_Y;
int iGLOBAL_AMMO_X;
int iGLOBAL_AMMO_Y;

int iGLOBAL_FOCALWIDTH;
double dGLOBAL_FPFOCALWIDTH;

int iGLOBAL_FOCALWIDTH_USER = 0;

double dTopYZANGLELIMIT;

int iG_X_center;
int iG_Y_center;

boolean iG_aimCross = 0;

extern int  viewheight;
extern int  viewwidth;

//----------------------------------------------------------------------
#define FINEANGLES                        2048
void SetRottScreenRes (int Width, int Height) 
{
	
	iGLOBAL_SCREENWIDTH = Width;
	iGLOBAL_SCREENHEIGHT = Height;


    iGLOBAL_SCREENBWIDE = iGLOBAL_SCREENWIDTH*(96/320);
	iG_SCREENWIDTH = iGLOBAL_SCREENWIDTH*(96/320);;// default screen width in bytes

	if (iGLOBAL_SCREENWIDTH == 320) {
		iGLOBAL_FOCALWIDTH = 160;
		dGLOBAL_FPFOCALWIDTH = 160.0; 
		iGLOBAL_HEALTH_X = 20;
		iGLOBAL_HEALTH_Y = 185;
		iGLOBAL_AMMO_X = 300;
		iGLOBAL_AMMO_Y = 184;

		dTopYZANGLELIMIT = (44*FINEANGLES/360);
	}
	if (iGLOBAL_SCREENWIDTH == 640) {
		iGLOBAL_FOCALWIDTH = 180;
		dGLOBAL_FPFOCALWIDTH = 180.0 ;
		iGLOBAL_HEALTH_X = 40;//20*2;
		iGLOBAL_HEALTH_Y = 466;//(185*2)+16;
		iGLOBAL_AMMO_X = 600;//300*2;
		iGLOBAL_AMMO_Y = 464;//480-16;

		dTopYZANGLELIMIT = (42*FINEANGLES/360);
	}
	if (iGLOBAL_SCREENWIDTH == 800) {
		iGLOBAL_FOCALWIDTH = 160;
		dGLOBAL_FPFOCALWIDTH = 160.0 ;
		iGLOBAL_HEALTH_X = 40;//20*2;
		iGLOBAL_HEALTH_Y = 585;//(185/200)*600;
		iGLOBAL_AMMO_X = 750;//(300/320)*800;
		iGLOBAL_AMMO_Y = 584;//600-16;
	
		dTopYZANGLELIMIT = (90*FINEANGLES/360);
	}

	else {

		int RoundedScreenWidth = iGLOBAL_SCREENWIDTH - (iGLOBAL_SCREENWIDTH % 320);
		int RoundedScreenHeight = iGLOBAL_SCREENHEIGHT - (iGLOBAL_SCREENHEIGHT % 200);

		int ScaleFactorX = (int)(RoundedScreenWidth / 320);
		int ScaleFactorY = (int)(RoundedScreenHeight / 200);

		iGLOBAL_FOCALWIDTH = 160;
		dGLOBAL_FPFOCALWIDTH = 160.0;

		iGLOBAL_HEALTH_X = 20 * ScaleFactorX;
		iGLOBAL_HEALTH_Y = (185/200)*RoundedScreenHeight;
		iGLOBAL_AMMO_X = (300/320)*RoundedScreenWidth;
		iGLOBAL_AMMO_Y = RoundedScreenHeight-16;
	}

	iGLOBAL_FOCALWIDTH_USER = 0;

}

//----------------------------------------------------------------------
//luckey for me that I am not programmin a 386 or the next
//4 function would never have worked. bna++
//todo: fix this :(
extern int     viewsize;
void MoveScreenUpLeft()
{
	int startX,startY,startoffset;
    byte  *Ycnt,*b;
    b=(byte *)bufferofs;
	b += (((iGLOBAL_SCREENHEIGHT-viewheight)/2)*iGLOBAL_SCREENWIDTH)+((iGLOBAL_SCREENWIDTH-viewwidth)/2);
	if (viewsize == 8) {b += 8*iGLOBAL_SCREENWIDTH;}
	startX = 3; //take 3 pixels to the right
	startY = 3; //take 3 lines down
	startoffset = (startY*iGLOBAL_SCREENWIDTH)+startX;

	for (Ycnt=b;Ycnt<b+((viewheight-startY)*iGLOBAL_SCREENWIDTH);Ycnt+=iGLOBAL_SCREENWIDTH){
		memcpy(Ycnt,Ycnt+startoffset, viewwidth-startX);
	}
}
//----------------------------------------------------------------------
void MoveScreenDownLeft()
{
	int startX,startY,startoffset;
    byte  *Ycnt,*b;
    b=(byte *)bufferofs;
	b += (((iGLOBAL_SCREENHEIGHT-viewheight)/2)*iGLOBAL_SCREENWIDTH)+((iGLOBAL_SCREENWIDTH-viewwidth)/2);
	if (viewsize == 8) {b += 8*iGLOBAL_SCREENWIDTH;}
	startX = 3; //take 3 pixels to the right
	startY = 3; //take 3 lines down
	startoffset = (startY*iGLOBAL_SCREENWIDTH);//+startX;

	//Ycnt starts in botton of screen and copys lines upwards
	for (Ycnt=b+((viewheight-startY-1)*iGLOBAL_SCREENWIDTH);Ycnt>b;Ycnt-=iGLOBAL_SCREENWIDTH){
		memcpy(Ycnt+startoffset,Ycnt+startX,viewwidth-startX);
	}
}
//----------------------------------------------------------------------
void MoveScreenUpRight()
{
	int startX,startY,startoffset;
    byte  *Ycnt,*b;
    b=(byte *)bufferofs;

	b += (((iGLOBAL_SCREENHEIGHT-viewheight)/2)*iGLOBAL_SCREENWIDTH)+((iGLOBAL_SCREENWIDTH-viewwidth)/2);
	if (viewsize == 8) {b += 8*iGLOBAL_SCREENWIDTH;}
	startX = 3; //take 3 pixels to the right
	startY = 3; //take 3 lines down
	startoffset = (startY*iGLOBAL_SCREENWIDTH);//+startX;

	for (Ycnt=b;Ycnt<b+((viewheight-startY)*iGLOBAL_SCREENWIDTH);Ycnt+=iGLOBAL_SCREENWIDTH){
		memcpy(Ycnt+startX,Ycnt+startoffset, viewwidth-startX);
	}
}
//----------------------------------------------------------------------
void MoveScreenDownRight()
{
	int startX,startY,startoffset;
    byte  *Ycnt,*b;
    b=(byte *)bufferofs;

	b += (((iGLOBAL_SCREENHEIGHT-viewheight)/2)*iGLOBAL_SCREENWIDTH)+((iGLOBAL_SCREENWIDTH-viewwidth)/2);
	if (viewsize == 8) {b += 8*iGLOBAL_SCREENWIDTH;}
	startX = 3; //take 3 pixels to the right
	startY = 3; //take 3 lines down
	startoffset = (startY*iGLOBAL_SCREENWIDTH)+startX;

	//Ycnt starts in botton of screen and copys lines upwards
	for (Ycnt=b+((viewheight-startY-1)*iGLOBAL_SCREENWIDTH);Ycnt>b;Ycnt-=iGLOBAL_SCREENWIDTH){
		memcpy(Ycnt+startoffset,Ycnt,viewwidth-startX);
	}
}

//todo: refactor the above four functions into something generic
void BumpScreen(void) {
#if 0
	uint32_t startX   = (-3) + (rand() % 3) * 3;
	uint32_t startY   = (-3) + (rand() % 3) * 3;
	uint32_t startOfs = startY * iGLOBAL_SCREENWIDTH + startX;
	uint8_t* Ycnt;
	uint8_t* buf = (uint8_t*) bufferofs;

	buf += (((iGLOBAL_SCREENHEIGHT - viewheight) / 2) * iGLOBAL_SCREENWIDTH) + (iGLOBAL_SCREENWIDTH - viewwidth) / 2;

	if (viewsize == 8) buf += 8 * iGLOBAL_SCREENWIDTH;

#endif
}