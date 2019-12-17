#pragma once
#include "XManager.h"
#include "MyDirect3D.h"
#include "Joycon.h"
#include "COBBTree.h"
#include "ItemManager.h"

#define ROTATE 0.04f
#define MAX_SPEED 10.0f
#define MIN_SPEED 5.0f
#define CURVE_ANGLE_MAX 0.52f

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
	D3DXVECTOR3 m_prePlayerPos;
	D3DXVECTOR3 m_flowPos;
	D3DXVECTOR3 m_bloomPos;
	float		m_playerVerocity;
	float		m_flowAngleX;
	float		m_flowAngleY;
	float		m_curveAngle;
	bool		m_itemGet;
	bool		m_hit;
	//!減速フラグ
	bool		m_deceleration;
	/*ボタンをプレイヤー1とプレイヤー2で判別するための変数*/
	int			m_num;
	int         d;
	float		m_angle;
	float		m_maxSpeed;
	float		m_minSpeed;
	int			m_effectTime;
	CoolTime	m_coolTime;

	void		MoveForward();
	void		MoveSide();
	void		FlowAnimation();
	void		CheckCoolTime();
	void		UpdateEffect();
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
	void Rotation();
	CoolTime& GetCoolTime();
	void StartCoolTime();
	void CalcDirection();
	float GetPlayerAngle();
	void GetItemEffect(ITEM_TYPE type);
	D3DXVECTOR3 GetPlayerFlow();
};

