#pragma once
#include "Obst.h"
#include "XManager.h"
#include "AABB.h"
#include <vector>

//障害物の数
#define OBSTACLE_NUM 100

class ObstacleManager
{
private:
	std::vector<ObstacleInfo> m_obstacleInfo;
	XManager*		m_x;
	int				m_index;
	D3DXVECTOR3		m_playerPos;
public:
	ObstacleManager();
	~ObstacleManager();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void CreateObstacle(ObstacleInfo info);
	void CreateObstacle(D3DXVECTOR3 pos, OBST_TYPE type);
	int	 GetObstacleNum();
	ObstacleInfo*	GetObstacleInfo(int idx);
	D3DXVECTOR3 GetObstaclePosition(int idx);
	D3DXVECTOR3 GetObstacleRotation(int idx);
	//OBB& GetOBB(int idx)const;
	AABB& GetAABB(int idx)const;
	void Hit(int idx);
	//プレイヤーのアップデート後、アイテムマネージャのアップデート前に実行する
	void SetPlayerPosition(D3DXVECTOR3 pos);
	void SetParticleIndex(int idx);
	int GetParticleIndex(int idx);
};