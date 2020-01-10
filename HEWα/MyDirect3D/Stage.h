#pragma once
#include "XManager.h"
#include "MyDirect3D.h"
#include "OBB.h"
#include "Fbx.h"
class Stage
{
private:
	Fbx	*m_stage;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_sca;
public:
	void Initialize(int n);
	void Update();
	void Draw();
	void Finalize();
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rotation);
	void SetScale(D3DXVECTOR3 scale);
	/*COBBTree& GetOBB() const;
	D3DXMATRIX* GetMatrix();*/
	OBB& GetOBB()const;
};

