#pragma once
#include "MyDirect3D.h"
#include "XManager.h"
#include "Enum.h"
#include "COBBTree.h"

class Wakka
{
private:
	XManager*		m_model;
	ELEM			m_elem;
	D3DXVECTOR3		m_pos;

	void SetElemModel();
	void SetPosition(int i);
public:
	Wakka();
	~Wakka();
	void Initialize(ELEM elem);
	void Update(D3DXVECTOR3 playerPosition);
	void Draw();
	void Finalize();
	static int GetCenter(int i);
	void Shoot();
	void Hit();
	D3DXVECTOR3 GetPosition();
	bool CollisionObstacle(ELEM elem);
	bool IsShoot();
	ELEM GetElem();
	//OBB*  GetOBB();
	COBBTree& GetOBB() const;
	D3DXMATRIX* GetMatrix();
	void MoveForward(int frame);
	void SetPosition(D3DXVECTOR3 pos);
};

