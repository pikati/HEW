#pragma once
#include "BaseScene.h"

#pragma comment(lib,"winmm.lib")

enum SCENE_STATE {
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT
};

class SceneManager
{
private:
	static BaseScene			*m_scene[3];
	static SCENE_STATE			m_sceneState;
	static LPDIRECT3DDEVICE9	m_d3dDevice;
	static const float MIN_FREAM_TIME;
	static float frameTime;
	static LARGE_INTEGER timeStart;
	static LARGE_INTEGER timeEnd;
	static LARGE_INTEGER timeFreq;
	// fps���擾����Ȃ�0�ŏ��������Ȃ��ƃS�~���������ă}�C�i�X����n�܂����肷��(�����m��Ȃ�)
	static float fps;
	static bool frame;

	static void ResetGame();
public:
	static void					Initialize();
	static void					Update();
	static void					Draw();
	static void					Finalize();
	static void					ChangeSceneState();
	static bool					PastOneFrame();
	static BaseScene*			SetSceneGame();
};

