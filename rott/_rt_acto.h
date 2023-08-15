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
#ifndef _rt_actor_private
#define _rt_actor_private

#define MAXGIBS            600
#define HAAPT              24
#define VAAPT              24
#define GODHAPT            1024
#define GODVAPT            1024
#define MAXDELTAYZSHOOT    (((5*FINEANGLES)/360))
#define MAXDELTAYZSEE      (((15*FINEANGLES)/360))
#define MAXSHOOTOFFSET     (((15*FINEANGLES)/360))
#define MAXSHOOTSHIFT      (1)
#define MAXDAMAGE          (64)
#define MAXYZANGLE         (((30*FINEANGLES)/360))
#define SMOKEWALLOFFSET    (0x800)
#define MZADJUST           0x30000;
#define MAXSTEPHEIGHT      24
#define SIGN(x)            ((x)>=0)?(1):(-1)
#define MAXRAIN            128
#define SG_PSTAT      0x4000
#define SG_PSTATE     0x2000
#define EXPLOSION_DAMAGE   50
#define LOWFALLCLIPZ       (maxheight - 96)
#define HIGHFALLCLIPZ      -5
#define LOWRISECLIPZ       (nominalheight)
#define HIGHRISECLIPZ      64
#define NORMALGIBSPEED     0x2f00

#define FL_PLEADING        0x400
#define FL_EYEBALL         0x400
#define FL_UNDEAD          0x8000

#define NME_DRUNKTYPE       0x01
#define NME_HEATSEEKINGTYPE 0x02

#define NUMSTATES 11

enum {
  STAND,
  PATH,
  COLLIDE1,
  COLLIDE2,
  CHASE,
  USE,
  AIM,
  DIE,
  FIRE,
  WAIT,
  CRUSH
  };

#define SHOTMOM                0x200l
#define NEXT                   1
#define PREV                   0
#define ANGLEMOVE              0x2b000l
#define PAINTIME               5l
#define LOOKAHEAD              (20 << 16)
#define DRAINTIME              70l
#define EXPLOSION_IMPULSE      0x2600l
#define ZEROMOM                ob->momentumx = ob->momentumy = 0
#define NOMOM                  ((!ob->momentumx) && (!ob->momentumy))
#define WHICHACTOR             (ob->obclass-lowguardobj)
#define SPDPATROL              0x600l
#define ENEMYRUNSPEED          (0xc00)
#define ENEMYFASTRUNSPEED      (5*SPDPATROL)
#define ENEMYINSANESPEED       (7*SPDPATROL)
#define MAXMOVE                0x2000l
#define PROJECTILESIZE         0x6000l
#define DEADFRICTION           0x6000l
#define ROLLMOMENTUM           0x920l
#define PROJSIZE               0x4000l
#define PILLARMOM              0x800l
#define HALFGLOBAL1            (TILEGLOBAL/2)
#define TOUCHDIST              0xb000l
#define STANDDIST              0x5000l
#define SNAKERAD               0x4000l
#define MINSIGHT               0x18000l
#define HBM                    -2
#define SNEAKY                 -3
#define GIBVALUE               -3
#define DISKMOMZ               4
#define PWALLTOL               0xc000
#define MINSTATZDIFF           58
#define MINACTORZDIFF          58
#define WILEYBLITZCHANCE    20
#define GIBSOUND            SD_GIBSPLASHSND
#define ACTORTHUDSND        SD_BODYLANDSND
#define ACTORLANDSND        SD_PLAYERLANDSND
#define CORNERVALUE         0x500

//=========================== macros =============================

#define M_ISWALL(x)           ((x->which == WALL) || (x->which == PWALL) || (x->which == MWALL))
#define M_DISTOK(p1,p2,d)     (abs((p1)-(p2)) <= d)
#define M_NONS(x)             ((x->obclass == wallfireobj) || (x->obclass == pillarobj))
#define M_CHOOSETIME(x)       ((int)(TILEGLOBAL/((x->speed))))
#define M_DIST(x1,x2,y1,y2)   (((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)))
#define M_S(x)                (UPDATE_STATES[x][ob->obclass-lowguardobj])
#define Fix(a)                (a &= (FINEANGLES - 1))
#define GAS_DOOR(x,y) (MISCVARS->GASON && (MAPSPOT(x,y,1) == GASVALUE))

#define DOOR_LOCKED(door)                                      \
           (((door->flags & DF_ELEVLOCKED) || (door->lock)) && \
             (ob->obclass != b_darianobj)                       \
           )

#define STOPACTOR(ob)                   \
   {                                    \
   ob->momentumx = ob->momentumy = 0;   \
   ob->dirchoosetime = 0;               \
   }


#define M_CHECKDIR(ob,tdir)             \
   {                                    \
   ob->dir = tdir;                      \
   ParseMomentum(ob,dirangle8[tdir]);   \
   ActorMovement(ob);                   \
   if (ob->momentumx || ob->momentumy)  \
      return;                           \
   }                                    \

#define CheckSpecialGibMovement(blocker)            \
   {                                                \
   int centerx = ((trytilex<<16) + 0x8000);         \
   int centery = ((trytiley<<16) + 0x8000);         \
                                                    \
   if (blocker->vertical==false)                    \
      {                                             \
      int dyt = centery - ob->y;                    \
      int dytp1 = centery - tryy;                   \
                                                    \
      if ((abs(dytp1) > abs(dyt)) &&                \
         (SGN(dyt) == SGN(dytp1))                   \
         )                                          \
         return OK_TO_CONTINUE;                     \
                                                    \
      }                                             \
   else                                             \
      {                                             \
      int dxt = centerx - ob->x;                    \
      int dxtp1 = centerx - tryx;                   \
                                                    \
      if ((abs(dxtp1) > abs(dxt)) &&                \
         (SGN(dxt) == SGN(dxtp1))                   \
         )                                          \
         return OK_TO_CONTINUE;                     \
                                                    \
      }                                             \
   }

#define ClipHeight(ob,clipz)                                \
{  ob->momentumz = 0;                                       \
                                                            \
   if (ISPLAYER && (ob->z != clipz) && (ob->temp2 == 0))    \
      {playertype *pstate;                                  \
       int dz = ob->z - clipz;                              \
                                                            \
       M_LINKSTATE(ob,pstate);                              \
                                                            \
       pstate->heightoffset = pstate->oldheightoffset + dz; \
       ob->temp2 = (dz >= 0)?(STEPUP):(STEPDOWN);           \
      }                                                     \
                                                            \
   ob->z = clipz;                                           \
}

#define M_CHECKTURN(x,ndir)                             \
   {                                                    \
   if (ndir == olddir)                                  \
      ZEROMOM;                                          \
   ParseMomentum(x,dirangle8[ndir]);                    \
   ActorMovement(x);                                    \
   if (!NOMOM)                                          \
      {                                                 \
      if (ndir != olddir)                               \
         {                                              \
         next = dirorder[olddir][NEXT];                 \
         prev = dirorder[olddir][PREV];                 \
         x->temp1 = ndir;                               \
         if (dirdiff[ndir][next] < dirdiff[ndir][prev]) \
            NewState(x,&s_kristleft);                   \
         else                                           \
            NewState(x,&s_kristright);                  \
         }                                              \
      return;                                           \
      }                                                 \
   }                                                    \

#define M_CheckDoor(ob)                          \
   {                                             \
   door = ob->door_to_open;                      \
   if (door != -1)                               \
      {                                          \
      if ((ob->obclass > shurikenobj) &&         \
          (ob->obclass != collectorobj)          \
         )                                       \
         Error("you got it !!!");                \
      LinkedOpenDoor(door);                      \
      if (doorobjlist[door]->action != dr_open)  \
         return;                                 \
      ob->door_to_open = -1;                     \
      }                                          \
   }                                             \

#define M_CheckBossSounds(ob)                                 \
   {                                                          \
   if ((ob->obclass >= b_darianobj) &&                        \
       (ob->obclass <= b_darksnakeobj) &&                     \
       (ob->flags & FL_ATTACKMODE)  &&                        \
       (ob->obclass != b_robobossobj) &&                      \
       (!(ob->flags & FL_DYING))                              \
      )                                                       \
      {                                                       \
      if (MISCVARS->SOUNDTIME)                                \
         MISCVARS->SOUNDTIME --;                              \
      else                                                    \
         {                                                    \
         MISCVARS->SOUNDTIME = 5*VBLCOUNTER;                  \
         if (GameRandomNumber("boss sound check",0)<160)      \
            {                                                 \
            int rand,sound;                                   \
                                                              \
            rand = GameRandomNumber("boss sounds",0);         \
            sound = BAS[ob->obclass].operate;                 \
            if (rand < 160)                                   \
               sound ++;                                      \
            if (rand < 80)                                    \
               sound ++;                                      \
                                                              \
            SD_PlaySoundRTP(sound,ob->x,ob->y);               \
            }                                                 \
         }                                                    \
      if (MISCVARS->REDTIME)                                  \
         {                                                    \
         MISCVARS->REDTIME --;                                \
         MISCVARS->redindex = ((MISCVARS->REDTIME >> 1) & 15);\
         }                                                    \
      }                                                       \
   }

#define SET_DEATH_SHAPEOFFSET(ob)                     \
   {                                                  \
   ob->flags |= FL_ALTERNATE;                         \
   ob->shapeoffset += deathshapeoffset[ob->obclass];  \
   }


#define RESET_DEATH_SHAPEOFFSET(ob)                   \
   {                                                  \
   ob->flags &= ~FL_ALTERNATE;                        \
   ob->shapeoffset -= deathshapeoffset[ob->obclass];  \
   }

#define LOW_VIOLENCE_DEATH_SHOULD_BE_SET(ob)          \
     ((gamestate.violence < vl_high) &&               \
      (ob->obclass >= lowguardobj) &&                 \
      (ob->obclass <= triadenforcerobj) &&            \
      (!(ob->flags & FL_ALTERNATE))                   \
     )                                                \

#define LOW_VIOLENCE_DEATH_IS_SET(ob)   (ob->flags & FL_ALTERNATE)
#define LOW_VIOLENCE_PAIN_SHOULD_BE_SET  LOW_VIOLENCE_DEATH_SHOULD_BE_SET
#define LOW_VIOLENCE_PAIN_IS_SET  LOW_VIOLENCE_DEATH_IS_SET
#define SET_PAIN_SHAPEOFFSET  SET_DEATH_SHAPEOFFSET
#define RESET_PAIN_SHAPEOFFSET  RESET_DEATH_SHAPEOFFSET

#define SLIDER(ob)  ((ob->flags & FL_NOFRICTION) && (ob->state->think != T_Collide))
#define AIRBORNE(ob) ((ob->obclass != playerobj) && (ob->z != nominalheight) &&\
                      (!IsPlatform(ob->tilex,ob->tiley)) && \
                      (DiskAt(ob->tilex,ob->tiley) == NULL) \
                     )

#define InitSprayPart(newflags)                                          \
   {                                                                     \
   new->hitpoints = starthitpoints[gamestate.difficulty][b_robobossobj]; \
   new->dir = dir*4;                                                     \
   new->speed = 7*SPDPATROL;                                             \
   new->door_to_open = -1;                                               \
   new->flags |= (newflags);                                             \
   }

#define TryAbruptProximalDirections(trydir)             \
   {                                                    \
   next = dirorder[trydir][NEXT];                       \
   prev = dirorder[trydir][PREV];                       \
   if (GameRandomNumber("actor choose dir",0) < 128)    \
      {                                                 \
      dirtype temp = next;                              \
                                                        \
      next = prev;                                      \
      prev = temp;                                      \
      }                                                 \
                                                        \
   if (!dirtried[next])                                 \
      {                                                 \
      M_CHECKDIR(ob,next);                              \
      dirtried[next]=1;                                 \
      }                                                 \
                                                        \
   if (!dirtried[prev])                                 \
      {                                                 \
      M_CHECKDIR(ob,prev);                              \
      dirtried[prev]=1;                                 \
      }                                                 \
                                                        \
   }

#define TrySmoothProximalDirections(trydir)                        \
   {                                                               \
                                                                   \
   if (((trydir == olddir) || (dirdiff[trydir][olddir] < 2)) &&    \
      (!dirtried[trydir]))                                         \
      {                                                            \
      M_CHECKDIR(ob,trydir);                                       \
      dirtried[trydir] = 1;                                        \
      }                                                            \
   next = dirorder[olddir][NEXT];                                  \
   prev = dirorder[olddir][PREV];                                  \
                                                                   \
   if (dirdiff[trydir][next] <= dirdiff[trydir][prev])             \
      {                                                            \
      start = next;                                                \
      whichway = NEXT;                                             \
      }                                                            \
   else                                                            \
      {                                                            \
      start = prev;                                                \
      whichway = PREV;                                             \
      }                                                            \
                                                                   \
   for (tdir= start; tdir != dirorder[trydir][whichway];           \
        tdir = dirorder[tdir][whichway]                            \
       )                                                           \
      {                                                            \
      if (dirtried[tdir])                                          \
         continue;                                                 \
      M_CHECKDIR(ob,tdir);                                         \
      dirtried[tdir]=1;                                            \
      }                                                            \
                                                                   \
   }

#define ChasePlayer(ob)                          \
   {                                             \
   dx= player->x-ob->x;                          \
   dy= ob->y-player->y;                          \
   if ((abs(dx) < 0xb000) && (abs(dy) < 0xb000)) \
      return;                                    \
   dummy.x = player->x;                          \
   dummy.y = player->y;                          \
   }

#define RollStart(ob,state,angle)     \
   {                                  \
   int oldspeed = ob->speed;          \
                                      \
   ob->speed = ROLLMOMENTUM+0x200;    \
   NewState(ob,state);                \
   ParseMomentum(ob,angle);           \
   ob->speed = oldspeed;              \
   }                                  \

#define CheckMinDist(destx,desty,dir)                    \
   {                                                     \
   curr = FindDistance(destx-ob->tilex,desty-ob->tiley); \
   if (curr < min)                                       \
      {                                                  \
      min = curr;                                        \
      ob->targettilex = destx;                           \
      ob->targettiley = desty;                           \
      ob->temp1 = dir;                                   \
      }                                                  \
   }

// default = actor

//==================== Some ActorTryMove macros ==============================

#define CheckProximitySpecials(ob,temp)                             \
{                                                                   \
   if (ocl == b_heinrichobj)                                       \
      {                                                            \
      if (tcl == playerobj)                                        \
         {                                                         \
         playertype *pstate;                                      \
                                                                     \
         M_LINKSTATE(temp,pstate);                                \
         DamageThing(temp,5);                                     \
         temp->whatever = ob;                                     \
         temp->temp2 = COLUMNCRUSH;                               \
         pstate->heightoffset += 4;                               \
         if (pstate->heightoffset >= 30)                          \
            pstate->heightoffset = 30;                           \
         pstate->oldheightoffset = pstate->heightoffset;          \
         }                                                         \
      else                                                         \
         {                                                         \
         temp->momentumx = temp->momentumy = temp->momentumz = 0; \
         temp->hitpoints = 0;                                     \
         }                                                         \
      if (temp->hitpoints <= 0)                                    \
         temp->flags |= FL_HBM;                                     \
      Collision(temp,ob,0,0);                                      \
      continue;                                                    \
      }                                                             \
                                                                    \
   else if ((ocl == b_darksnakeobj) && (tcl == playerobj)) \
      {                                                     \
      DamageThing(temp,1);                                      \
      Collision(temp,ob,0,0);     \
      M_CheckPlayerKilled(temp);                                   \
      } \
        \
   if ((ocl == boulderobj) && (tcl >= lowguardobj) && (tcl < roboguardobj))\
      {temp->momentumx = temp->momentumy = temp->momentumz = 0;     \
       temp->hitpoints = 0;                                         \
       temp->flags |= FL_HBM;                                       \
       Collision(temp,ob,0,0);                                      \
       SD_PlaySoundRTP(SD_ACTORSQUISHSND,temp->x,temp->y);          \
       continue;                                                    \
      }                                                             \
                                                                    \
   if (pusher && (ocl != tcl) && (!(temp->flags & FL_DYING))  &&    \
       (tcl < roboguardobj)                                         \
      )                                                             \
      {if ((!ob->ticcount) && (ocl != collectorobj) && (ocl != diskobj))\
          DamageThing(temp,5);                                      \
                                                                    \
       if (tcl == playerobj)                                        \
         temp->flags |= FL_PUSHED;                                  \
       Collision(temp,ob,ob->momentumx-temp->momentumx,ob->momentumy-temp->momentumy);\
       M_CheckPlayerKilled(temp);                                   \
       continue;                                                    \
      }                                                             \
                                                                    \
   if (bouncer)                                                    \
      {ob->momentumx = -ob->momentumx;                              \
       continue;                                                    \
      }                                                             \
   }



#define CheckStepping(ob,step,minzdiff)                         \
{                                                               \
 int cz = (ob->z - step->z + minzdiff);                         \
                                                                \
 if ((cz >= -MAXSTEPHEIGHT) && (cz <= MAXSTEPHEIGHT))           \
      {if ((ob->obclass == playerobj) && (ob->temp2 == 0) &&    \
           (ob->z != (step->z - minzdiff))                      \
          )                                                     \
         {                                                      \
         playertype *pstate;                                    \
                                                                \
         M_LINKSTATE(ob,pstate);                                \
                                                                \
         pstate->heightoffset = pstate->oldheightoffset + cz;   \
         ob->temp2 = (cz >= 0)?(STEPUP):(STEPDOWN);             \
         }                                                      \
      ob->z = step->z - minzdiff;                               \
      tryz = ob->z + (ob->momentumz >> 16);                     \
      dzt = minzdiff;                                           \
      }                                                         \
}

#define SetCollectorTarget(xoffset,yoffset,newdir)                         \
   {                                                                       \
   ob->targettilex = ((dptr->tilex + (xoffset)) << TILESHIFT) + HALFGLOBAL1; \
   ob->targettiley = ((dptr->tiley + (yoffset)) << TILESHIFT) + HALFGLOBAL1; \
   ob->temp2 = newdir;                                                     \
   if (GameRandomNumber("collector door search",0) < 100)                  \
      return;                                                              \
   }

#define CheckAdjacentArea(x,y)        \
   {                                  \
   if (InMapBounds(x,y))              \
      {                               \
      temparea = AREANUMBER(x,y);     \
      if (ValidAreanumber(temparea))  \
         newarea = temparea;          \
      }                               \
   }

#define DetonateMissile(x,y) \
{MissileHit(x,y);             \
 return false;                 \
}                                \

#define QuietDetonate(ob)            \
   {                                 \
   if (ob->soundhandle != -1)        \
      SD_StopSound(ob->soundhandle); \
   if (ob == missobj)                \
      missobj = NULL;                \
   NewState(ob,&s_megaremove);       \
   return false;                     \
   }

#define SGN(x)  (((x) > 0)?(1):(-1))
#define SHP(difficulty,ob)  (starthitpoints[difficulty][ob->obclass])
#define CAP_OSCUROS_HITPOINTS(ob)                         \
   {                                                      \
   if (ob->hitpoints > (SHP(gamestate.difficulty,ob)<<1)) \
      ob->hitpoints = (SHP(gamestate.difficulty,ob)<<1);  \
   }

typedef struct  sat {
    int          x, y, z;
    unsigned     flags;
    int          hitpoints;
    int          targetx, targety;
    int          angle;
    int          yzangle;
    int          speed;
    int          momentumx, momentumy, momentumz;
    int          temp1, temp2, temp3;
    int          whateverindex, targetindex;

    short        ticcount;
    short        shapeoffset;
    short        stateindex;
    short        dirchoosetime;

    byte         areanumber;
    byte         obclass;
    signed char  door_to_open;
    signed char  dir;

} saved_actor_type;

typedef enum {
    down_in_a_hole = -1,
    no_holes_available = 0,
    holes_unreachable = 1,
    hole_targetted = 2
}   hiding_status;

typedef enum {
    NO_MOVEMENT,
    Z_MOVEMENT_ONLY,
    OK_TO_CONTINUE
} movement_status;

enum {
    ESAU_USING_HOLES = 1,
    ESAU_LEAVING_CONTROL_ROOM,
    ESAU_USING_TOUCH_PEDASTALS,
    ESAU_CHASING_PLAYER
};

typedef struct {
    thingtype which;
    byte tilex, tiley;
    fixed x, y, z;
} tpoint;


//========================== Function Prototypes ==============================

void     MissileMovement(objtype*);
boolean  MissileTryMove(objtype*,int,int,int);
void     T_DarkSnakeChase(objtype*);
void     HeatSeek(objtype*);
boolean  CheckDoor(objtype *ob,doorobj_t*,int,int);
boolean  NextToDoor(objtype*ob);
void     MissileHit (objtype *ob,void*);
boolean  Near(objtype*,void*,int);
void     FirstSighting(objtype*);
void     SelectOrobotChaseDir(objtype*);
void     SelectPathDir(objtype*);
void     SelectChaseDir(objtype*);
void     SelectRoboChaseDir(objtype*);
void     SelectDodgeDir(objtype*);
void     SelectRollDir (objtype*);
void     SelectTouchDir(objtype*);
void     SelectMineDir(objtype*);
boolean  WallCheck(int,int);
boolean  NMEspincheck(objtype*);
void     TurnActorIntoSprite(objtype*ob);
void     ActivateEnemy(objtype*);
#endif
