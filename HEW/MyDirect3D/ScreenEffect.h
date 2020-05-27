#pragma once
#include "MyDirect3D.h"

enum SCREEN_EFFECT_TYPE{
	SCREEN_EFFECT_SPEED,
	SCREEN_EFEFCT_MAX
};

struct TextureInfo
{
	int	verticalSplit;
	int	holizontalSplit;
	int maxFrame;
};

class ScreenEffect
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPDIRECT3DTEXTURE9*	m_tex;
	SCREEN_EFFECT_TYPE	m_type;
	bool				m_enable;
	int					m_frame;
	static int			m_playerNumber;
	TextureInfo*		m_info;

	void TextureInitialize();
	void UpdateFrame();
	float CalcTextureX();
	float CalcTextureY();
	void ScreenEffectDraw();
	void PlayerNumUpdate();
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	void Enable();
	void Disable();
	void SetScreenEffect(SCREEN_EFFECT_TYPE type);
};

