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
#ifndef _rt_draw_private
#define _rt_draw_private

#define MINZ                            0x2700
#define MAXBOB                          0x9000

#define GOLOWER  0x38000		//dma -- uhh??
#define GOHIGHER 0x20000

#define MAXDRAWNTICS                    40

#define W_CHANGE  (WEAPONUPTICS || WEAPONDOWNTICS)
#define SGN(x)          ((x>0) ? (1) : ((x==0) ? (0) : (-1)))

//screensaver
#define SPINSIZE  40
#define MAXSPEED  8

//apogee screen stuff
#define APOGEEXANGLE 913
#define APOGEEXMAG   180
#define APOGEESTARTY 0
#define APOGEEENDY   100
#define APOGEESCALESTART (FINEANGLES<<4)
#define APOGEESCALEEND (FINEANGLES)
#define APOGEESONGTIME (124-1)

//missile stuff? why is this here?
#define NUMEXPLOSIONTYPES 4

//default colors for when no sky or floor
#define CEILINGCOLOR 24
#define FLOORCOLOR 32

//DrawScaleds()
#define HF_1 (24)
#define HF_2 (72)

//[SHAR]
#if (SHAREWARE == 0)
    #define NUMWEAPGRAPHICS 16
    #define MAXTRANSMITTEREXPLOSIONS 30
#else
    #define NUMWEAPGRAPHICS 9
    #define NUMENDMESSAGES 24
#endif

//???
#define DHEIGHTFRACTION 8
#define HFRACTION (6+HEIGHTFRACTION)

//transparency?
#define FIXEDTRANSLEVEL (30)

typedef struct {
    int x;
    int y;
    int angle;
    int scale;
    int dx;
    int dy;
    int dangle;
    int dscale;
    int phase;
    int time;
    int pausetime;
    int pausex;
    int pausey;
} screensaver_t;

typedef struct {
    char  name[11];
    byte  numframes;
} explosioninfo_t;

#if (SHAREWARE==1)
char* EndCinematicPicNames[5] =
{
"lwgshoo2",
"hg2shoo2",
"ankshoo1",
"ligrise4",
"tritoss5",

};

char* EndCinematicText[NUMENDMESSAGES] =
{
"You've won the battle, Cassatt.\n"
"But when the Oscuridos return,\n"
"will you be ready as they wage\n"
"their Dark War?",

"Armed with only a pistol and 30\n"
"bucks, you must stop the minions of\n"
"El Oscuro before they kill millions\n"
"of innocent people.",

"But for now, hey, enjoy the medal\n"
"you received and take a vacation.\n"
"You've earned it. Maybe on \n"
"San Nicolas Island . . ." ,

"Thanks for playing. If you liked\n"
"\"The HUNT Begins\", check Ordering\n"
"Info for information about \n"
"continuing your adventure.",

"Okay, you can stop reading now.",

"Press a key. That's all there is.\n"
"Thanks.",

"Are you lazy, or illiterate?\n"
"PRESS A KEY.",

"Look, this is pointless. You\n"
"are done. Push off.",

"Okay, show's over.  Nothing\n"
"more to see here.",

"Wow, you must like this fine\n"
"background screen.",

"For waiting this long, you get . . .\n"
"nothing!  Go away!",

"I mean, I like you as a friend,\n"
"but . . .",

"\"Bob\"",

"All right, um . . . you found the\n"
"secret message! Congratulations!",

"Didn't work, huh?  Okay, how about\n"
"this . . .",

"THE END",

"Dang. Thought I had you there.",

"Stop watching.",

"You know that if you registered,\n"
"there would be a lot more cool\n"
"stuff happening right now.",

"Episode IV: A New Hope\n",

"Just think of all the new secret\n"
"messages you could find hidden\n"
"in the registered version!",

"Someone right now is probably\n"
"enjoying the really exciting\n"
"ending of the registered version.",

"ROTT was filmed before\n"
"a live audience.",

"No animals were harmed during the\n"
"creation of this video game, although\n"
"one dog did get its butt spanked\n"
"when it peed on the carpet.\n",


};
char NextGameString1[] = "The Developers of Incredible Power";
char NextGameString2[] = "shall return";

#else

static char    burnCastle1Msg[] =
"The monastery burns.\n"
"\n"
"El Oscuro is dead.\n"
"\n"
"The world is safe.\n";

// If all Snake Eggs not destroyed on final level:


static char    notDoneMsg[] =
"Unfortunately not all\n"
"of El Oscuro's larvae\n"
"were destroyed.\n"
"\n"
"Thirty years later,\n"
"a descendant of\n"
"El Oscuro wiped out\n"
"the entire world,\n"
"but nice job anyway.\n";

static char    tryAgainMsg[] =
"Try Again.\n"
"\n"
"The world will not be\n"
"safe until all of El\n"
"Oscuro's larvae are\n"
"destroyed. Find them.\n";

// If all snake eggs destroyed:
static char    doneMsg[] =
"You have destroyed\n"
"El Oscuro and all his\n"
"descendants.  Well done!\n";

// On Triad background, in bigger font.
static char    youWin1Msg[] =
"So, HUNT Members, how\n"
"do you think the\n"
"mission went?\n";

// Place menu pix of characters here (maybe modem frame too?)
static char    youWin2Msg[] =
"Barrett: Well, I think\n"
"I got shin splints from\n"
"all those jump pads.\n"
"But hey, action-wise,\n"
"I've been in tougher\n"
"bar fights, for crying\n"
"out loud.\n";

static char    youWin3Msg[] =
"Cassatt: Apart from\n"
"the other HUNT members\n"
"saying I look like\n"
"Richard Mulligan, it\n"
"was quite a success.\n"
"And some of the\n"
"monastery's ironwork\n"
"was very nice.\n";

static char    youWin4Msg[] =
"Ni: it was quite easy,\n"
"actually.  I just\n"
"pictured the enemy\n"
"having the face of\n"
"my ex-husband, and\n"
"man, I was a force\n"
"of Nature.\n";

static char    youWin5Msg[] =
"Wendt: I was kind of\n"
"disappointed. I think\n"
"I used the missile\n"
"weapons way too much.\n"
"Next time, bullets\n"
"only.  Nothing sweeter\n"
"than a head shot from\n"
"a hundred feet.\n";

static char    youWin6Msg[] =
"Freeley: I'm still\n"
"trying to adjust in\n"
"the aftermath.  It's\n"
"kinda tough.  I mean,\n"
"I save the damn world,\n"
"and all people ask\n"
"about is my name.\n"
"Sheesh.\n";

// On caching screen

static char     youWin7Msg[] =
"The HUNT is victorious!\n"
"\n"
"         THE END\n";


static char     youWin8Msg[] =
"Now go and celebrate!\n"
"\n"
"      THE REAL END";

#endif

void  DrawPlayerWeapon(void);
boolean TransformPlane (int x1, int y1, int x2, int y2, visobj_t * plane);
int   CalcRotate (objtype *ob);
void  DrawScaleds (void);
void SetSpriteLightLevel (int x, int y, visobj_t * sprite, int dir, int fullbright);

#endif