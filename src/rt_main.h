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
//***************************************************************************
//
//                  RT_MAIN.H
//
//***************************************************************************

#ifndef _rt_main_public
#define _rt_main_public

#include "develop.h"
#include "rt_def.h"
#include "rottnet.h"
#include "rt_battl.h"

#if (SHAREWARE==0)
#define  STANDARDGAMELEVELS   (DATADIR "DARKWAR.RTL")
#define  STANDARDBATTLELEVELS (DATADIR "DARKWAR.RTC")
#define  SUPERROTTBATTLELEVELS (DATADIR "ROTTCD.RTC")
#define  SITELICENSEBATTLELEVELS (DATADIR "ROTTSITE.RTC")
#else
#define  STANDARDGAMELEVELS   (DATADIR "HUNTBGIN.RTL")
#define  STANDARDBATTLELEVELS (DATADIR "HUNTBGIN.RTC")
#endif

enum {
    vl_low,
    vl_medium,
    vl_high,
    vl_excessive
};

// Enum for each version of the game
typedef enum {
    ROTT_SHAREWARE,
    ROTT_REGISTERED,
    ROTT_SUPERCD,
    ROTT_SITELICENSE
} version_type;

typedef struct {
    int32_t GodModeTime;
    int32_t DogModeTime;
    int32_t ShroomsModeTime;
    int32_t ElastoModeTime;
    int32_t AsbestosVestTime;
    int32_t BulletProofVestTime;
    int32_t GasMaskTime;
    int32_t MercuryModeTime;

    int32_t GodModeRespawnTime;
    int32_t DogModeRespawnTime;
    int32_t ShroomsModeRespawnTime;
    int32_t ElastoModeRespawnTime;
    int32_t AsbestosVestRespawnTime;
    int32_t BulletProofVestRespawnTime;
    int32_t GasMaskRespawnTime;
    int32_t MercuryModeRespawnTime;

} specials;


typedef struct {
    // Variables for which version of the game can be played
    version_type Product;
    uint32_t     Version;

    int32_t  TimeCount;
    int32_t  frame;
    int32_t  secrettotal,treasuretotal,killtotal;
    int32_t  secretcount,treasurecount,killcount;
    int32_t  supertotal,healthtotal,missiletotal;
    int32_t  supercount,healthcount,missilecount;
    int32_t  democratictotal,planttotal;
    int32_t  democraticcount,plantcount;
    int32_t  dipballs;
    int32_t  difficulty;
    int32_t  violence;
    int32_t  mapon;
    int32_t  score;
    int32_t  episode;
    int32_t  battlemode;
    int32_t  battleoption;
    int32_t  randomseed;
    boolean  teamplay;
    boolean  DODEMOCRATICBONUS1;
    boolean  DOGROUNDZEROBONUS;
    int32_t  autorun;

    // Battle Options
    battle_type BattleOptions;

    boolean  SpawnCollectItems;
    boolean  SpawnEluder;
    boolean  SpawnDeluder;
    boolean  ShowScores;
    boolean  PlayerHasGun[MAXPLAYERS];
    specials SpecialsTimes;
    
} gametype;


extern  int      doublestep;
extern  boolean  tedlevel;
extern  int      tedlevelnum;
extern  int      tedx;
extern  int      tedy;
extern  boolean  fizzlein;
extern  int      pheight;
extern  boolean  NoSound;
extern  int      timelimit;
extern  boolean  timelimitenabled;
extern  boolean  noecho;
extern  boolean  demoexit;
extern  boolean  quiet;

extern gametype  gamestate;
extern boolean DebugOk;
extern  boolean newlevel;

void QuitGame(void);
void PlayCinematic(void);
void InitCharacter(void);
void ShutDown(void);
void UpdateGameObjects(void);

void CheckCommandLineParameters(void);
void PlayTurboGame(void);
void Init_Tables(void);
void CheckRemoteRidicule (int scancode);
void SetRottScreenRes(int Width, int Height);

void crash_print (int sig);
int  setup_homedir(void);
void ComSetTime(void);
void VH_UpdateScreen(void);
void RecordDemoQuery(void);
int  CountDigits(const int number);

extern  int polltime;
extern  int oldpolltime;
extern  volatile int oldtime;
void PauseLoop ( void );
#if SAVE_SCREEN
extern boolean inhmenu;
void SaveScreen (boolean saveLBM);
#endif
void SetupWads( void );

extern boolean SCREENSHOTS;
extern boolean COMPUTELEVELSIZE;
extern boolean MONOPRESENT;
extern boolean MAPSTATS;
extern boolean TILESTATS;
extern boolean HUD;

extern char CWD[40];

#endif
