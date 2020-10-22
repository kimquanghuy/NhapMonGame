#include"Nam.h"
Nam::Nam()
{
	SetState(NAM_STATE_WALKING);
}
void Nam::GetBBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + NAM_BBOX_W;
	if (state == NAM_STATE_DIE)
		bottom = y + NAM_BBOX_H_DIE;
	else
		bottom = y + NAM_BBOX_H;
}
void Nam::Update(DWORD dt, vector<LPGAMEOBJ>* coObjects)
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

void Nam::Render()
{
	int ani = NAM_ANI_WALKING;
	if (state == NAM_STATE_DIE) {
		ani = NAM_ANI_DIE;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBBox();
}

void Nam::SetState(int state)
{
	GameObj::SetState(state);
	switch (state)
	{
	case NAM_STATE_DIE:
		y += NAM_BBOX_H - NAM_BBOX_H_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case NAM_STATE_WALKING:
		vx = -NAM_WALKING_SPEED;
	}
}