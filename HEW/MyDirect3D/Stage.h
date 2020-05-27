#pragma once
#include "MyDirect3D.h"
#include "StageManager.h"

class Stage
{
private:
	StageInfo m_info;
public:
	void Initialize(STAGE_TYPE type);
	void Update();
	void Draw();
	void Finalize();
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rotation);
	void SetScale(D3DXVECTOR3 scale);
	//OBB& GetOBB()const;
};