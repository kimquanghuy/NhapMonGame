#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include"GachQ.h"
#include"KeyEventHandler.h"

#include "Nam.h"
#include "Portal.h"

Mario::Mario(float x, float y) : GameObj()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void Mario::Update(DWORD dt, vector<LPGAMEOBJ>* coObjects)
{
	// Calculate dx, dy 
	GameObj::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCo(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCo(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
			//x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Nam*>(e->obj)) // if e->obj is Goomba 
			{
				Nam* namm = dynamic_cast<Nam*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (namm->GetState() != NAM_STATE_DIE)
					{
						namm->SetState(NAM_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (namm->GetState() != NAM_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_FIREM;
								//StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
			//rua
			//Qbrick

			if (dynamic_cast<QBrick*>(e->obj)) // if e->obj is Goomba 
			{
				QBrick* qb = dynamic_cast<QBrick*>(e->obj);				
				if (e->dy < 0)
				{
					if (qb->GetState() != QBRICK_STATE_2)
					{
						qb->SetState(QBRICK_STATE_2);						
					}
				}			
			}
			// if Goomba
			else if (dynamic_cast<Portal*>(e->obj))
			{
				Portal* p = dynamic_cast<Portal*>(e->obj);
				Game::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
				else ani = MARIO_ANI_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = MARIO_ANI_BIG_WALKING_RIGHT;
			else ani = MARIO_ANI_BIG_WALKING_LEFT;
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				else ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = MARIO_ANI_SMALL_WALKING_RIGHT;
			else ani = MARIO_ANI_SMALL_WALKING_LEFT;
		}
	//fire
		else if (level == MARIO_LEVEL_FIREM)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_FIRE_IDLE_RIGHT;
				else ani = MARIO_ANI_FIRE_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = MARIO_ANI_FIRE_WALKING_RIGHT;
			else ani = MARIO_ANI_FIRE_WALKING_LEFT;
		}
	//raccoon
		else if (level == MARIO_LEVEL_RACCOON)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_RACCOON_IDLE_RIGHT;
				else ani = MARIO_ANI_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = MARIO_ANI_RACCOON_WALKING_RIGHT;
			else ani = MARIO_ANI_RACCOON_WALKING_LEFT;
		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBBox();
}

void Mario::SetState(int state)
{
	GameObj::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		{
			// TODO: need to check if Mario is *current* on a platform before allowing to jump again
			vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void Mario::GetBBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_W;
		bottom = y + MARIO_BIG_BBOX_H;
	}
	else if (level == MARIO_LEVEL_FIREM)
	{
		right = x + MARIO_FIRE_BBOX_W;
		bottom = y + MARIO_FIRE_BBOX_H;
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		right = x + MARIO_RACCOON_BBOX_W;
		bottom = y + MARIO_RACCOON_BBOX_H;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		right = x + MARIO_SMALL_BBOX_W;
		bottom = y + MARIO_SMALL_BBOX_H;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void Mario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	//SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
//Fire Mario
void Mario::FireMario()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_FIREM);
	SetSpeed(0, 0);
}
//Raccoon Mario
void Mario::RacMario()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_RACCOON);
	SetSpeed(0, 0);
}

