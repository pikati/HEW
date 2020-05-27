#include "ItemManager.h"
//障害物情報のようにこっちも情報で管理する（タイ焼きメロンパンクラスいらないあと障害物も若干書き換え）


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

void ItemManager::Initialize() {
	/*m_item[0] = new Taiyaki;
	m_item[1] = new Meronpan;*/
	m_x = new XManager[ITEM_KIND];
	/*for (int i = 0; i < ITEM_KIND; i++) 
	{
		m_item[i]->Initialize();
	}*/
	for (int i = 0; i < ITEM_KIND; i++)
	{
		m_x[i].Initialize(true, true);
		m_x[i].SetMinMax(D3DXVECTOR3(-1.0f, -10.0f, -1.0f), D3DXVECTOR3(1.0f, 10.0f, 1.0f));
	}
	m_x[MERONPAN].LoadXFile("Asset/Models/Item/Meronpan.x");
	m_x[TAIYAKI].LoadXFile("Asset/Models/Item/Taiyaki.x");
	m_itemInfo = new ItemInfo[5];
	m_index = 0;
	for (int i = 0; i < 5; i++)
	{
		m_itemInfo[i].pos = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	}
}

void ItemManager::Update() {
	for (int i = 0; i < ITEM_NUM; i++)
	{
		if (fabsf(m_playerPos.x - m_itemInfo[i].pos.x) > 30.0f || fabsf(m_playerPos.y - m_itemInfo[i].pos.y) > 30.0f || fabsf(m_playerPos.z - m_itemInfo[i].pos.z) > 30.0f)
		{
			m_itemInfo[i].enable = false;
		}
		else
		{
			if (!m_itemInfo[i].hit)
			{
				m_itemInfo[i].enable = true;
			}
		}
	}
}

void ItemManager::Draw() {
	for (int i = 0; i < ITEM_NUM; i++)
	{
		if (m_itemInfo[i].enable)
		{
			m_x[m_itemInfo[i].type].SetTranslation(m_itemInfo[i].pos);
			m_x[m_itemInfo[i].type].SetRotation(m_itemInfo[i].rot);
			m_x[m_itemInfo[i].type].SetScaling(m_itemInfo[i].scale.x);
			m_x[m_itemInfo[i].type].Update();
			m_x[m_itemInfo[i].type].Draw();
		}
	}
}

void ItemManager::Finalize() {
	delete[] m_itemInfo;
	for (int i = ITEM_KIND - 1; i >= 0; i--)
	{
		m_x[i].Finalize();
	}
	delete[] m_x;
}

void ItemManager::CreateItem(ItemInfo info) {
	m_itemInfo[m_index++] = info;
	if (m_index >= ITEM_NUM)
	{
		m_index = 0;
	}
}

void ItemManager::CreateItem(D3DXVECTOR3 pos, ITEM_TYPE type) {
	m_itemInfo[m_index++] = ItemInfo(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f), type, true, false);
	if (m_index >= ITEM_NUM)
	{
		m_index = 0;
	}
}

int ItemManager::GetItemNum() {
	int num = 0;
	for (int i = 0; i < ITEM_NUM; i++)
	{
		if (m_itemInfo[i].enable)
		{
			num++;
		}
	}
	return num;
}

ItemInfo* ItemManager::GetItemInfo(int idx) {
	return &m_itemInfo[idx];
}

D3DXVECTOR3 ItemManager::GetItemPosition(int idx) {
	return m_itemInfo[idx].pos;
}

D3DXVECTOR3 ItemManager::GetItemRotation(int idx) {
	return m_itemInfo[idx].rot;
}
//OBB& ItemManager::GetOBB(int idx) const {
//	ItemInfo info = m_itemInfo[idx];
//	m_x[info.type].SetTranslation(info.pos);
//	m_x[info.type].SetRotation(info.rot);
//	m_x[info.type].SetScaling(info.scale.x);
//	m_x[info.type].Update();
//	return m_x[info.type].GetOBB();
//}

AABB& ItemManager::GetAABB(int idx)const {
	ItemInfo info = m_itemInfo[idx];
	m_x[info.type].SetTranslation(info.pos);
	m_x[info.type].Update();
	return m_x[info.type].GetAABB();
}

void ItemManager::Hit(int idx) {
	m_itemInfo[idx].enable = false;
	m_itemInfo[idx].hit = true;
}

void ItemManager::SetPlayerPosition(D3DXVECTOR3 pos) {
	m_playerPos = pos;
}