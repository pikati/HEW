#pragma once
#include "MyDirect3D.h"
#include "Taiyaki.h"
#include "Meronpan.h"
#include "XManager.h"
#include "AABB.h"

//同時に出現できるアイテムの数
#define ITEM_NUM 5
//アイテムの種類
#define ITEM_KIND 2

class ItemManager
{
private:
	ItemInfo*	m_itemInfo;
	XManager*	m_x;
	int			m_index;
	D3DXVECTOR3 m_playerPos;
public:
	ItemManager();
	~ItemManager();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void CreateItem(ItemInfo info);
	void CreateItem(D3DXVECTOR3 pos, ITEM_TYPE type);
	int	 GetItemNum();
	ItemInfo*	GetItemInfo(int idx);
	D3DXVECTOR3 GetItemPosition(int idx);
	D3DXVECTOR3 GetItemRotation(int idx);
	//OBB& GetOBB(int idx) const;
	AABB& GetAABB(int idx) const;
	void Hit(int idx);
	//プレイヤーのアップデート後、アイテムマネージャのアップデート前に実行する
	void SetPlayerPosition(D3DXVECTOR3 pos);
};

