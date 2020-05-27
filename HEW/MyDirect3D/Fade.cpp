#include "Fade.h"
#include "Polygons.h"
#include "main.h"

#define FADE_SPEED 12

int Fade::m_alfa = 0;
int Fade::m_fadeSpeed = 0;
bool  Fade::m_isFadeIn = false;
bool  Fade::m_isFadeOut = false;
LPDIRECT3DTEXTURE9 Fade::m_tex = NULL;

void Fade::Initialize() {
	D3DXCreateTextureFromFile(GetDevice(), "Asset/Texture/Other/Fade.png", &m_tex);
}

void Fade::Finalize() {
	SAFE_RELEASE(m_tex);
}

void Fade::FadeIn() {
	if (!m_isFadeIn)
	{
		m_isFadeIn = true;
		m_isFadeOut = false;
		m_alfa = 0;
		m_fadeSpeed = FADE_SPEED;
	}
}

void Fade::FadeOut() {
	if (!m_isFadeOut)
	{
		m_isFadeIn = false;
		m_isFadeOut = true;
		m_alfa = 255;
		m_fadeSpeed = -FADE_SPEED;
	}
}

void Fade::Fading() {
	if (m_isFadeIn || m_isFadeOut)
	{
		m_alfa += m_fadeSpeed;
		if (m_alfa > 255)
		{
			m_alfa = 255;
			m_isFadeIn = false;
		}
		if (m_alfa < 0)
		{
			m_alfa = 0;
			m_isFadeOut = false;
		}
		Polygons::FadeDraw(0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1.0f, 1.0f, m_alfa, m_tex);
	}
}

bool Fade::IsFadeIn() {
	return m_isFadeIn;
}

bool Fade::IsFadeOut() {
	return m_isFadeOut;
}