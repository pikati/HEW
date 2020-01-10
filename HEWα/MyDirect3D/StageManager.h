#pragma once
#include "MyDirect3D.h"
#include "Stage.h"
#include "OBB.h"
enum STAGE_TYPE {
	STAGE_NORMAL,
	STAGE_WALL,
	STAGE_CURVE
};

//è·äQï®ÇÃêî
#define STAGE_KIND 3

struct StageInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	STAGE_TYPE	type;
	StageInfo(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scl, STAGE_TYPE newType)
		: pos(position),
		rot(rotation),
		scale(scl),
		type(newType) {}
};

class StageManager
{
private:
	Stage*	m_stage;
	std::vector<StageInfo> m_stageInfo;
public:
	StageManager();
	~StageManager();
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void CreateStage(StageInfo info);
	void CreateStage(D3DXVECTOR3 pos, STAGE_TYPE type);
	int	 GetStageNum();
	StageInfo*	GetStageInfo(int idx);
	//COBBTree& GetOBB(STAGE_TYPE type) const;
	OBB& GetOBB(STAGE_TYPE type)const;
};

