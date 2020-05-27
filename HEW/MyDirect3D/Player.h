#pragma once
#include "XManager.h"
#include "Fbx.h"
#include "MyDirect3D.h"
#include "Joycon.h"
#include "ItemManager.h"
#include "StageManager.h"
#include "shadow.h"

#define ROTATE 0.04f
#define MAX_SPEED 30.0f
#define MIN_SPEED 15.0f
#define CURVE_ANGLE_MAX 0.52f
#define COOL_TIME 120

struct CoolTime {
	int coolTime;
	bool bCoolTime;
};

struct PlayerInfo {
	D3DXVECTOR3 position;
	D3DXVECTOR3 oldPosition;
	D3DXVECTOR3 flowPosition;
	D3DXVECTOR3 bloomPosition;
	float		playerVerocity;
	float		angle;
	float		flowAngleX;
	float		flowAngleY;
	float		curveAngle;
};

class Player
{
private:
	PlayerInfo	m_info;
	bool		m_itemGet;
	bool		m_hit;
	//!Œ¸‘¬ƒtƒ‰ƒO
	bool		m_deceleration;

	int         d;
	float		m_maxSpeed;
	float		m_minSpeed;
	int			m_effectTime;
	CoolTime	m_coolTime;

	void		MoveForward();
	void		MoveSide(int i);
	void		FlowAnimation();
	void		CheckCoolTime();
	void		UpdateEffect();
	void		CalcDirection();
	
public:
	void Initialize();
	void Update(int i);
	D3DXVECTOR3 GetPlayerPosition();
	void Hit(DIRECTION dir);
	void HitWall();
	CoolTime& GetCoolTime();
	void StartCoolTime();
	void SetItemEffect(ITEM_TYPE type);
	D3DXVECTOR3 GetPlayerFlow();
	float		GetPlayerAngle();
	PlayerInfo GetPlayerInfo();
};