#pragma once
#include "Wakka.h"
#include "Enum.h"


class WakkaManager
{
private:
	Wakka*		m_wakka;
	D3DXVECTOR3 m_playerPos;
	int			m_center;
	int			m_frame;
	bool		m_shoot;

	void ShotUpdate();
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
	void Hit();
	bool IsShoot();
	ELEM GetElem(int i);
	void SetPlayerPosition(D3DXVECTOR3 playerPos);
	void SetPlayerAngle(float angle);
};

