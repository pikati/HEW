#pragma once
#include "XManager.h"
#include "MyDirect3D.h"


class TextBack
{
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scl;

public:
	XManager    *m_textback;

	TextBack();
	~TextBack();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	D3DXVECTOR3 GetTextBackPos();
};