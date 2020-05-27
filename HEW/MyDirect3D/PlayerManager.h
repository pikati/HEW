#pragma once
#include "MyDirect3D.h"
#include "Fbx.h"
#include "Player.h"
#include "AABB.h"
#include "StageManager.h"
#include "shadow.h"
#include "Obst.h"
#include "DisplaySandStorm.h"

class PlayerManager
{
private:
	Fbx*		m_fbx;
	Player*		m_player;
	Shadow*		m_shadow;
	DisplaySandStorm* m_sand;
	int			m_goalTime[2];
	int			m_obstacleEffectTime[2];
public:
	void Initialize();
	void Update(bool b1, bool b2);
	void Draw(int i);
	void Finalize();
	AABB& GetAABB(int i)const;
	D3DXVECTOR3 GetPlayerPosition(int i);
	float GetPlayerAngle(int i);
	D3DXVECTOR3 GetPlayerFlow(int i);
	void Hit(int idx, DIRECTION dir);
	CoolTime& GetCoolTime(int idx);
	void SetItemEffect(int idx, ITEM_TYPE type);
	void StartCoolTime(int idx);
	void GetGoalTime(int time, int idx);
	void SetObstacleEffect(int idx, OBST_TYPE type);
};

