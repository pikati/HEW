#pragma once
#include "XManager.h"
#include "MyDirect3D.h"
#include "Enum.h"
#include "COBBTree.h"

enum OBST_TYPE{
	FIREDRIFTWOOD,
	TREE,
	SANDSTORM,
	PITFALL,
	DRIFTWOOD
};

class Obst
{
protected:
	XManager*		m_pXmanager;
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_rot;
	D3DXVECTOR3		m_scale;
	D3DXVECTOR3		m_playerPos;
	OBST_TYPE		m_elem;
	bool			m_bEnable;
	bool			m_bHit;

public:
	~Obst() {};
	virtual void	Initialize() = 0;
	virtual void	Update() = 0;
	virtual void	Draw() = 0;
	virtual void	Finalize() = 0;
	virtual D3DXVECTOR3 GetPosition() = 0;
	virtual void	Hit() = 0;
	virtual bool	IsEnable() = 0;
	virtual void	CreateObstacle(D3DXVECTOR3 pos) = 0;
	virtual float*	CreateRondam(float* random) = 0;
	virtual void	SetPosition(D3DXVECTOR3 pos) = 0;
	virtual void	SetRotation(D3DXVECTOR3 rot) = 0;
	virtual void	SetScale(D3DXVECTOR3 scale) = 0;
	//virtual OBB*	GetOBB() = 0;
	virtual COBBTree& GetOBB() const = 0;
	virtual D3DXMATRIX* GetMatrix() = 0;
	virtual void	Reset() = 0;
	virtual OBST_TYPE	GetElem() = 0;
	virtual void	SetPlayerPos(D3DXVECTOR3 pos) = 0;
};