#pragma once
#include "Wakka.h"
#include "Enum.h"
#include "COBBTree.h"

class WakkaManager
{
private:
	Wakka*		m_wakka;
	D3DXVECTOR3 m_playerPos;
	float		m_playerAngle;
	int			m_center;
	bool		m_shoot[5];

	//!è·äQï®ÇâÛÇµÇΩêî
	int			m_destroyObstacleNum;

	void ShotUpdate(int i);
	void LerpUpdate(int i);
	D3DXVECTOR3* Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t);
	D3DXVECTOR3 GetEndPos(int i);
public:
	WakkaManager();
	~WakkaManager();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void CreateWakka(ELEM elem);
	void Change(int dir);
	void Shoot();
	int  GetCenter();
	void Hit(int idx);
	bool IsShoot(int i);
	ELEM GetElem(int i);
	void SetPlayerPosition(D3DXVECTOR3 playerPos);
	void SetPlayerAngle(float angle);
	COBBTree& GetOBB(int idx) const;
	D3DXMATRIX* GetMatrix(int idx);
	D3DXVECTOR3 GetPosition(int idx);
	int GetDestroyObstacleNum();
	void DestroyObstacleCountUp();
};

