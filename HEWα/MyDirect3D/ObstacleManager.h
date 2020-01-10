#pragma once
#include "Obst.h"
#include "DriftWood.h"
#include "Fire.h"
#include "PitFall.h"
#include "SandStorm.h"
#include "Tree.h"

//è·äQï®ÇÃêî
#define OBSTACLE_KIND 5

struct ObstacleInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	OBST_TYPE	type;
	ObstacleInfo(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scl, OBST_TYPE newType)
		: pos(position),
		rot(rotation),
		scale(scl),
		type(newType) {}
};

class ObstacleManager
{
private:
	Obst*	m_obstacle[OBSTACLE_KIND];
	std::vector<ObstacleInfo> m_obstacleInfo;
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
	//COBBTree& GetOBB(OBST_TYPE type) const;
	OBB& GetOBB(OBST_TYPE type)const;
	void Hit(int idx);
	void SetPlayerPosition(D3DXVECTOR3 pos);
};

