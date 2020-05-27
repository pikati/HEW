#pragma once
#include "XManager.h"
#include "MyDirect3D.h"
#include "Joycon.h"

static const int INTERVAL = 120;

class Text
{
private:
	XManager *m_text;
	XManager *m_next;
	D3DXVECTOR3 m_textPos;
	D3DXVECTOR3 m_nextPos;
	bool m_bEnable;
	//���Ԗڂ̐�������
	int m_num;
	int interVal;
	bool bInterval;

public:
	Text();
	~Text();
	void Initialize(int i);
	void Update();
	void Draw();
	void Finalize();
	//�i�ރ{�^���\���֘A�̏���
	void NextInitialize();
	void NextUpdate();
	void NextDraw();
	void NextFinalize();
	D3DXVECTOR3 GetTextPos();
	bool IsEnable();
	void TrueChange();
	void FalseChange();
	void CheckInterval();
	void StartInterval();
	/*int GetInterval();*/
	bool GetbInterval();
};