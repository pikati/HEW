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
	static D3DXVECTOR3	m_max;
	static D3DXVECTOR3	m_min;
	static int	m_center1;
	static int	m_center2;
	int			m_frame;
	bool		m_shoot;

	void SetElem();
	void SetPosition(int i);
public:
	Wakka();
	~Wakka();
	void Initialize(ELEM elem, int i);
	void Update(int i);
	void Draw();
	void Finalize();
	static void Chenge(int a, int i);
	static int GetCenter(int i);
	void Shoot();
	void Hit();
	void SetPlayerPosition(D3DXVECTOR3);
	D3DXVECTOR3 GetPosition(int i);
	bool CollisionObstacle(ELEM elem);
	bool IsShoot();
	ELEM GetElem();
	//OBB*  GetOBB();
	COBBTree& GetOBB() const;
	D3DXMATRIX* GetMatrix();
};

