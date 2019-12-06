#pragma once
#include "MyDirect3D.h"

extern LPDIRECT3DDEVICE9		g_d3dDevice;
extern HINSTANCE				g_hInstance;
extern HWND						g_hWnd;


#define FPS 30.0f

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT			 Initialize(HWND hWnd);
//Å•Å•Å•èIóπèàóùä÷êîÅ•Å•Å•//
void             Finalize(void);
LPDIRECT3DDEVICE9 GetDevice();
HWND GetHWND();
HINSTANCE GetHInstance();