#pragma once
#include "MyDirect3D.h"
#include "Item.h"
#include "Taiyaki.h"
#include "Meronpan.h"
#include <vector>

//同時に出現できるアイテムの数
#define ITEM_NUM 5
//アイテムの種類
#define ITEM_KIND 2


enum ITEM_TYPE {
	TAIYAKI,
	MERONPAN
};

struct ItemInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	ITEM_TYPE	type;
	ItemInfo(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scl , ITEM_TYPE newType)
		: pos(position),
		rot(rotation),
		scale(scl),
		type(newType){}
};

class ItemManager
{
private:
	Item*		m_item[ITEM_KIND];
	std::vector<ItemInfo> m_itemInfo;
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
	COBBTree& GetOBB(ITEM_TYPE type) const;
	void Hit(int idx);
};

