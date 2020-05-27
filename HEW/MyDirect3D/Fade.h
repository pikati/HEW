#pragma once
#include "MyDirect3D.h"
 class Fade
{
private:
	static LPDIRECT3DTEXTURE9 m_tex;
	static int m_alfa;
	static int m_fadeSpeed;
	static bool  m_isFadeIn;
	static bool  m_isFadeOut;
public:
	static void Initialize();
	static void Fading();
	static void FadeIn();
	static void FadeOut();
	static bool IsFadeIn();
	static bool IsFadeOut();
	static void Finalize();
};

