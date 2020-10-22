#pragma once
#include<Windows.h>
#include<d3dx9.h>
#include<vector>
#include"Sprite.h"
#include"Animation.h"

using namespace std;
#define ID_TEX_BBOX -100
class GameObj;
typedef GameObj* LPGAMEOBJ;
struct CollisionEvent;
typedef CollisionEvent* LPCOLLISIONEVENT;

struct CollisionEvent
{
	LPGAMEOBJ obj;
	float t, nx, ny, dx, dy;
	CollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJ obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}
	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};


class GameObj
{
public:
	float x, y;
	float dx, dy;
	float vx, vy;
	int nx, state;
	DWORD dt;
	LPANIMATION_SET animation_set;
	void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void SetSpeed(float vx, float vy)
	{
		this->vx = vx;
		this->vy = vy;
	}
	void GetPosition(float& x, float& y)
	{
		x = this->x;
		y = this->y;
	}
	void GetSpeed(float& vx, float& vy)
	{
		vx = this->vx;
		vy = this->vy;
	}
	int GetState()
	{
		return this->state;
	}
	void RenderBBox();
	void SetAnimationSet(LPANIMATION_SET ani_set)
	{
		animation_set = ani_set;
	}
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJ coO);
	void CalcPotentialCo(vector<LPGAMEOBJ>* coObj, vector<LPCOLLISIONEVENT>& coEvent);
	void FilterCo(	vector<LPCOLLISIONEVENT>& coEnvent, 
					vector<LPCOLLISIONEVENT>& coEventResult, 
					float& min_tx, float& min_ty, float& nx,
					float& ny, float& rdx, float& rdy);
	GameObj();
	virtual void GetBBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJ>* coObj = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state)
	{
		this->state = state;
	}
	~GameObj();
};

