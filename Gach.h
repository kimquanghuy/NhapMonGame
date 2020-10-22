#pragma once
#include"GameObj.h"
#define GACH_BBOX_W 16
#define GACH_BBOX_H 16

class Gach :public GameObj
{
public:
	virtual void Render();
	virtual void GetBBox(float& l, float& t, float& r, float& b);
};
