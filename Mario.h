#pragma once
#include"GameObj.h"
#define MARIO_WALKING_SPEED	0.15f
#define MARIO_JUMP_SPEED_Y	0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY	0.002f
#define MARIO_DIE_DEFLECT_SPEED 0.5f

#define MARIO_STATE_IDLE 0
#define MARIO_STATE_WALKING_RIGHT 100
#define MARIO_STATE_WALKING_LEFT 200
#define MARIO_STATE_JUMP 300
#define MARIO_STATE_DIE 400

#define MARIO_ANI_DIE 0

#define MARIO_ANI_SMALL_IDLE_RIGHT 1
#define MARIO_ANI_SMALL_IDLE_LEFT 2
#define MARIO_ANI_SMALL_WALKING_RIGHT 3
#define MARIO_ANI_SMALL_WALKING_LEFT 4

#define MARIO_ANI_BIG_IDLE_RIGHT 5
#define MARIO_ANI_BIG_IDLE_LEFT 6
#define MARIO_ANI_BIG_WALKING_RIGHT 7
#define MARIO_ANI_BIG_WALKING_LEFT 8

#define MARIO_ANI_FIRE_IDLE_RIGHT 9
#define MARIO_ANI_FIRE_IDLE_LEFT 10
#define MARIO_ANI_FIRE_WALKING_RIGHT 11
#define MARIO_ANI_FIRE_WALKING_LEFT 12

#define MARIO_ANI_RACCOON_IDLE_RIGHT 13
#define MARIO_ANI_RACCOON_IDLE_LEFT 14
#define MARIO_ANI_RACCOON_WALKING_RIGHT 15
#define MARIO_ANI_RACCOON_WALKING_LEFT 16

#define MARIO_LEVEL_SMALL 1
#define MARIO_LEVEL_BIG 2
#define MARIO_LEVEL_FIREM 3
#define MARIO_LEVEL_RACCOON 4

#define MARIO_SMALL_BBOX_W 13
#define MARIO_SMALL_BBOX_H 15
#define MARIO_BIG_BBOX_W 15
#define MARIO_BIG_BBOX_H 27
#define MARIO_FIRE_BBOX_W 15
#define MARIO_FIRE_BBOX_H 27
#define MARIO_RACCOON_BBOX_W 23
#define MARIO_RACCOON_BBOX_H 27


#define MARIO_UNTOUCHABLE_TIME 2000

class Mario : public GameObj
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	float start_x;
	float start_y;
public:
	Mario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJ>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	void FireMario();
	void RacMario();

	virtual void GetBBox(float& left, float& bottom, float& right, float& top);
};
