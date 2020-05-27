#pragma once
#include "BaseScene.h"
#include "MyDirect3D.h"

class SceneTitle : public BaseScene
{
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_texture;
	bool m_changeScene;
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};

