#pragma once
#include "GameObj.h"
#define NAM_WALKING_SPEED	0.05f;
#define NAM_BBOX_W			16
#define NAM_BBOX_H			15
#define NAM_BBOX_H_DIE		9
#define NAM_STATE_WALKING	100
#define NAM_STATE_DIE		200
#define NAM_ANI_WALKING		0
#define NAM_ANI_DIE			1
class Nam :public GameObj
{
	virtual void GetBBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJ>* coObj);
	virtual void Render();
public:
	Nam();
	virtual void SetState(int state);
};