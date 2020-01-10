#pragma once
#include "XManager.h"
#include "Fbx.h"
#include "MyDirect3D.h"
#include "Joycon.h"
#include "COBBTree.h"
#include "OBB.h"

#define ROTATE 0.04f

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
	XManager	*m_bloom;
	Fbx*		m_player;
	D3DXVECTOR3 m_playerPos;
	D3DXVECTOR3 m_prePlayerPos;
	D3DXVECTOR3 m_bloomPos;
	float		m_playerVerocity;
	bool		m_itemGet;
	bool		m_hit;
	bool		m_deceleration;
	/*ボタンをプレイヤー1とプレイヤー2で判別するための変数*/
	int			m_num;
	int         d;
	float		m_angle;
	CoolTime	m_coolTime;
	D3DXMATRIX	m_ProjMat;
	D3DXMATRIX	m_ViewMat;

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
	OBB&  GetOBB()const;
	//COBBTree& GetOBB() const;
	//D3DXMATRIX* GetMatrix();
	void Rotation();
	CoolTime& GetCoolTime();
	void StartCoolTime();
	void CalcDirection();
	float GetPlayerAngle();
	void SetProjMat(D3DXMATRIX* mat);
	void SetViewMat(D3DXMATRIX* mat);
};

