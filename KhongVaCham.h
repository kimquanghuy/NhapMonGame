
#pragma once
#include"GameObj.h"
#define KVC_BBOX_W 0
#define KVC_BBOX_H 0

class kvc :public GameObj
{
public:
	virtual void Render();
	virtual void GetBBox(float& l, float& t, float& r, float& b);
};