#pragma once
#include "KeyEventHandler.h"

class Scene
{
protected:
	KeyEventHandler* key_handler;
	int id;
	LPCWSTR sceneFilePath;
public:
	Scene(int id, LPCWSTR filePath);
	KeyEventHandler* GetKeyEventHandler()
	{
		return key_handler;
	}
	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef Scene* LPSCENE;
class SceneKeyHandler :public KeyEventHandler
{
protected:
	Scene* scene;
public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	SceneKeyHandler(Scene* s) :KeyEventHandler()
	{
		scene = s;
	}
};