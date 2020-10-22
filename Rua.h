#pragma once
#include "GameObj.h"

#define RUA_WALKING_SPEED	0.03f;
#define RUA_BBOX_W			16
#define RUA_BBOX_H			26
#define RUA_BBOX_H_DIE		16
#define RUA_STATE_WALKING	100
#define RUA_STATE_DIE		200
#define RUA_ANI_WALKING_LEFT 0
#define RUA_ANI_WALKING_RIGHT 1
#define RUA_ANI_DIE			2

class Rua : public GameObj
{
	virtual void GetBBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJ>* coObjects);
	virtual void Render();

public:
	Rua();
	virtual void SetState(int state);
};