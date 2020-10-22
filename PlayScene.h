#pragma once
#include "Game.h"
#include "Texture.h"
#include "Scene.h"
#include "GameObj.h"
#include "Gach.h"
#include "Mario.h"
#include "Nam.h"
#include "Rua.h"
#include"KhongVaCham.h"

class PlayScene :public Scene
{
protected:
	Mario* player;
	vector<LPGAMEOBJ> object;
	void _ParseSection_TEXTURE(string line);
	void _ParseSection_SPRITE(string line);
	void _ParseSection_ANIMATION(string line);
	void _ParseSection_ANIMATION_SET(string line);
	void _ParseSection_OBJECTS(string line);
public:
	PlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void UnLoad();
	Mario* GetPlayer()
	{
		return player;
	}
};
class PlaySceneKeyHandler :public SceneKeyHandler
{
public:
	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	PlaySceneKeyHandler(Scene* s) :SceneKeyHandler(s) {};
};