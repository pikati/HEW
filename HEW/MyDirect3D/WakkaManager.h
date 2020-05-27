#pragma once
#include "Wakka.h"
#include "Combo.h"

class WakkaManager
{
private:
	Wakka*		m_wakka;
	Combo*		m_combo;
	D3DXVECTOR3 m_playerPos;
	D3DXVECTOR3 m_playerFlowPos;
	float		m_playerAngle;
	int			m_center;
	bool		m_shoot[5];
	int			m_feverTime;
	bool		m_fever;

	//!è·äQï®ÇâÛÇµÇΩêî
	int			m_destroyObstacleNum;

	void ShotUpdate(int i);
	void LerpUpdate(int i);
	D3DXVECTOR3* Lerp(D3DXVECTOR3* out, D3DXVECTOR3* start, D3DXVECTOR3* end, float t);
	D3DXVECTOR3 GetEndPos(int i);
	void CheckFever();
	void FeverUpdate();
public:
	WakkaManager();
	~WakkaManager();
	void Initialize(int idx);
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
	/*COBBTree& GetOBB(int idx) const;
	D3DXMATRIX* GetMatrix(int idx);*/
	//OBB& GetOBB(int idx)const;
	AABB& GetAABB(int idx)const;
	D3DXVECTOR3 GetPosition(int idx);
	int GetDestroyObstacleNum();
	void DestroyObstacleCountUp();
	void SetPlayerFlow(D3DXVECTOR3 pos);
	void SetComboCount(int combo);
	int  GetComboCount();
	bool GetIsFever();
};

