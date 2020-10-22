#pragma once
#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Scene.h"

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024
class Game
{
	static Game* __instance;
	HWND hWnd;
	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;
	LPDIRECTINPUT8       di;
	LPDIRECTINPUTDEVICE8 didv;		

	BYTE  keyStates[256];			
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		

	LPKEYEVENTHANDLER keyHandler;
	float cam_x = 0.0f;
	float cam_y = 0.0f;
	int screen_w;
	int screen_h;
	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	void _ParseSection_SETTING(string line);
	void _ParseSection_SCENE(string line);
public:
	void InitKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler)
	{
		keyHandler = handler;
	}
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void Load(LPCWSTR gameFile);
	LPSCENE GetCurrentScene()
	{
		return scenes[current_scene];
	}
	void SwitchScene(int scene_id);
	int GetScreenWidth()
	{
		return screen_w;
	}
	int GetScreenHeight()
	{
		return screen_h;
	}
	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }

	static Game* GetInstance();

	~Game();
};

