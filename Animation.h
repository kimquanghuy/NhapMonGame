#pragma once
#include<Windows.h>
#include <d3dx9.h>
#include<unordered_map>

#include"Sprite.h"

class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;
public:
	AnimationFrame(LPSPRITE sprite, int time)
	{
		this->sprite = sprite;
		this->time = time;
	}
	DWORD GetTime()
	{
		return time;
	}
	LPSPRITE GetSprite()
	{
		return sprite;
	}
};
typedef AnimationFrame* LPANIMATION_FRAME;
class Animation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	vector< LPANIMATION_FRAME> frames;
public:
	Animation(int defaultTime = 100)
	{
		this->defaultTime = defaultTime;
		lastFrameTime = -1;
		currentFrame = -1;
	}
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);
};
typedef Animation* LPANIMATION;
class Animations
{
	static Animations* __instance;
	unordered_map<int, LPANIMATION> animations;
public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();
	static Animations* GetInstance();
};
typedef vector<LPANIMATION> AnimationSet;
typedef AnimationSet* LPANIMATION_SET;
class AnimationSets
{
	static AnimationSets* __instance;
	unordered_map<int, LPANIMATION_SET> animation_sets;
public:
	AnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);
	static AnimationSets* GetInstance();
};
