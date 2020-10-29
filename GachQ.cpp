#include"GachQ.h"
QBrick::QBrick()
{
	SetState(QBRICK_STATE_1);
}
void QBrick::GetBBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + QBRICK_BBOX_W;
	bottom = y + QBRICK_BBOX_H;
}

void QBrick::Render()
{
	int ani = QBRICK_ANI_1;
	if (state == QBRICK_STATE_2) {
		ani = QBRICK_ANI_2;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBBox();
}
void QBrick::SetState(int state)
{
	GameObj::SetState(state);
	switch (state)
	{
	case QBRICK_STATE_1:
		//vx = 0;
		//vy = 0;
		break;
	case QBRICK_STATE_2:
		//vy = -QBRICK_MOVE;
		break;
	}
}
/*void QBrick::Update(DWORD dt, vector<LPGAMEOBJ>* coObjects)
{
	GameObj::Update(dt, coObjects);

	
}*/