#pragma once
#include "MyDirect3D.h"
#include "AABB.h"
#include "XManager.h"

#define STAGE_NUM 512

enum STAGE_TYPE {
	STAGE_ROAD,
	STAGE_TREE,
	STAGE_HOUSE1,
	STAGE_HOUSE3,
	STAGE_CHURCH,
	STAGE_TEMPLE,
	STAGE_MAX
};

enum DIRECTION {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	NON
};

struct StageInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	STAGE_TYPE	type;
	DIRECTION	dir;
	bool		enable;
	StageInfo(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scl, STAGE_TYPE newType, DIRECTION dir, bool enable)
	{
		this->pos = position;
		this->rot = rotation;
		this->scale = scl;
		this->type = newType;
		this->dir = dir;
		this->enable = enable;
	}
	StageInfo()
	{
		this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		this->type = STAGE_ROAD;
		this->dir = UP;
		this->enable = false;
	}
};

class StageManager
{
private:
	//Stage*	m_stage;
	StageInfo* m_stageInfo;
	XManager* m_x;
	int			m_index;
	D3DXVECTOR3 m_playerPos;
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void CreateStage(StageInfo info);
	void CreateStage(D3DXVECTOR3 pos, STAGE_TYPE type, DIRECTION dir);
	void CreateStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, STAGE_TYPE type, DIRECTION dir);
	void CreateStage(D3DXVECTOR3 pos, float scale, STAGE_TYPE type, DIRECTION dir);
	void CreateStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float scale, STAGE_TYPE type, DIRECTION dir);
	int	 GetStageNum();
	StageInfo*	GetStageInfo(int idx);
	//OBB& GetOBB(int idx)const;
	AABB& GetAABB(int idx)const;
	void SetPlayerPos(D3DXVECTOR3 pos);
};

