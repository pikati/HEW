#pragma once
#include "XManager.h"
#include "MyDirect3D.h"
#include "Joycon.h"
#include "COBBTree.h"

enum DIR {
	RIGHT,
	LEFT,
	NON
};

struct CoolTime {
	int coolTime;
	bool bCoolTime;
};

static const int COOL_TIME = 120;

class Player
{
private:
	XManager	*m_xfile_Player;
	XManager	*m_bloom;
	D3DXVECTOR3 m_playerPos;
	D3DXVECTOR3 m_bloomPos;
	float		m_playerVerocity;
	bool		m_itemGet;
	bool		m_hit;
	bool		m_deceleration;
	int			m_num;
	int         d;
	float		player1_Rotation;
	float		player2_Rotation;
	DIR			m_dir;
	CoolTime	m_coolTime;

	void		MoveForward();
	void		MoveSide();
	void		CheckCoolTime();
public:
	Player();
	~Player();
	void Initialize(int i);
	void Update();
	void Draw();
	void Finalize();
	D3DXVECTOR3 GetPlayerPosition();
	void Hit();
	void HitWall();
	//OBB*  GetOBB();
	COBBTree& GetOBB() const;
	D3DXMATRIX* GetMatrix();
	void Rotation1(float r);
	CoolTime& GetCoolTime();
	void StartCoolTime();
};

