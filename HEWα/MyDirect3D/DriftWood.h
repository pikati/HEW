#pragma once
#include "Obst.h"
#include "COBBTree.h"
class DriftWood : public Obst
{
private:
public:
	DriftWood();
	~DriftWood();
	virtual void	Initialize();
	virtual void	Update();
	virtual void	Draw();
	virtual void	Finalize();
	virtual D3DXVECTOR3 GetPosition();
	virtual void	Hit();
	virtual bool	IsEnable();
	virtual void	CreateObstacle(D3DXVECTOR3 pos);
	virtual float*	CreateRondam(float* random);
	virtual void	SetPlayerPos(D3DXVECTOR3 pos);
	//virtual OBB*	GetOBB();
	virtual void	SetPosition(D3DXVECTOR3 pos);
	virtual COBBTree& GetOBB() const;
	virtual D3DXMATRIX* GetMatrix();
	virtual void	Reset();
	virtual OBST_ELEM GetElem();
};

