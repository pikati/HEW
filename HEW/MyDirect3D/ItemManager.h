#pragma once
#include "MyDirect3D.h"
#include "Taiyaki.h"
#include "Meronpan.h"
#include "XManager.h"
#include "AABB.h"

//�����ɏo���ł���A�C�e���̐�
#define ITEM_NUM 5
//�A�C�e���̎��
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
	//�v���C���[�̃A�b�v�f�[�g��A�A�C�e���}�l�[�W���̃A�b�v�f�[�g�O�Ɏ��s����
	void SetPlayerPosition(D3DXVECTOR3 pos);
};

