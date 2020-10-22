#include "Rua.h"

Rua::Rua()
{
	SetState(RUA_STATE_WALKING);
}

void Rua::GetBBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + RUA_BBOX_W;

	if (state == RUA_STATE_DIE)
		bottom = y + RUA_BBOX_H_DIE;
	else
		bottom = y + RUA_BBOX_H;
}

void Rua::Update(DWORD dt, vector<LPGAMEOBJ>* coObjects)
{
	GameObj::Update(dt, coObjects);

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void Rua::Render()
{
	int ani = RUA_ANI_WALKING_LEFT;
	if (state == RUA_STATE_DIE) {
		ani = RUA_ANI_DIE;
	}
	else if (vx > 0) ani = RUA_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = RUA_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	//RenderBBox();
}

void Rua::SetState(int state)
{
	GameObj::SetState(state);
	switch (state)
	{
	case RUA_STATE_DIE:
		y += RUA_BBOX_H - RUA_BBOX_H_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case RUA_STATE_WALKING:
		vx = RUA_WALKING_SPEED;
	}

}