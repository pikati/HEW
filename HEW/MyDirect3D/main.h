#pragma once
#include "MyDirect3D.h"

extern LPDIRECT3DDEVICE9		g_d3dDevice;
extern HINSTANCE				g_hInstance;
extern HWND						g_hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT			 Initialize(HWND hWnd);
//�������I�������֐�������//
void             Finalize(void);
LPDIRECT3DDEVICE9 GetDevice();
HWND GetHWND();
HINSTANCE GetHInstance();