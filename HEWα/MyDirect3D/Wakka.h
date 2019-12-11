#pragma once
#include "MyDirect3D.h"
#include "XManager.h"
#include "Enum.h"
#include "COBBTree.h"

enum ELEM {
	FIRE,
	WATER,
	SAND,
	SOIL,
	WOOD
};

class Wakka
{
private:
	XManager*		m_model;
	ELEM			m_elem;
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_playerPos;
	D3DXVECTOR3		m_shotPos;
	float			m_playerAngle;
	float			m_shotAngle;
	int				m_frame;
	void SetElem();
	
public:
	Wakka();
	~Wakka();
	void Initialize(ELEM elem);
	void Update();
	void Draw();
	void Finalize();
	D3DXVECTOR3 GetPosition();
	bool CollisionObstacle(ELEM elem);
	ELEM GetElem();
	//OBB*  GetOBB();
	COBBTree& GetOBB() const;
	D3DXMATRIX* GetMatrix();
	bool MoveForward();
	void SetPlayerPosition(D3DXVECTOR3 pos);
	void SetPosition(D3DXVECTOR3 pos);
	void DecidePosition(int center);
	void SetPlayerAngle(float angle);
	void SetShotPosition(D3DXVECTOR3 pos);
	void SetShotAngle(float angle);
	void ResetFrame();
};

