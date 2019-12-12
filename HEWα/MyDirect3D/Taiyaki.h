#pragma once
#include "Item.h"
class Taiyaki : public Item
{
public:
	Taiyaki();
	~Taiyaki();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetScale(D3DXVECTOR3 scale);
	virtual COBBTree& GetOBB() const;
	virtual D3DXMATRIX* GetMatrix();
};

