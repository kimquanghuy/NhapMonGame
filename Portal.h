#pragma once
#include"GameObj.h"
class Portal :public GameObj
{
	int scene_id;
	int width;
	int height;
public:
	Portal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBBox(float& l, float& t, float& r, float& b);
	int GetSceneId()
	{
		return scene_id;
	}
};