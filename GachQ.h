#pragma once
#include "GameObj.h"
#define QBRICK_MOVE 0.5f
#define QBRICK_BBOX_W			16
#define QBRICK_BBOX_H			16

#define QBRICK_STATE_1	100
#define QBRICK_STATE_2	200

#define QBRICK_ANI_1 0
#define QBRICK_ANI_2 1
class QBrick :public GameObj
{
	virtual void GetBBox(float& left, float& top, float& right, float& bottom);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJ>* coObj);
	virtual void Render();
public:
	QBrick();
	virtual void SetState(int state);
};