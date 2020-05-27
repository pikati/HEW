#pragma once
#include "BaseScene.h"
#include "MyDirect3D.h"
#include "Fbx.h"
#include "Score.h"

class SceneResult : public BaseScene
{
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_texWin;
	LPDIRECT3DTEXTURE9 m_texLose;
	Fbx*		m_fbx;
	Score*		m_score;
	bool		m_win;//true:�v���C���[�P���� false:�v���C���[�Q����
	int			m_score1;
	int			m_score2;

	bool m_changeScene;
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void GetInfomation(bool win, int score1, int score2);
};

