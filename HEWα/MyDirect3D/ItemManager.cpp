#include "ItemManager.h"



ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

void ItemManager::Initialize() {
	m_item[0] = new Taiyaki;
	m_item[1] = new Meronpan;
	for (int i = 0; i < ITEM_KIND; i++) 
	{
		m_item[i]->Initialize();
	}
}

void ItemManager::Update() {
}

void ItemManager::Draw() {
	for (int i = 0; i < (int)m_itemInfo.size(); i++)
	{
		m_item[m_itemInfo[i].type]->SetPosition(m_itemInfo[i].pos);
		m_item[m_itemInfo[i].type]->SetRotation(m_itemInfo[i].rot);
		m_item[m_itemInfo[i].type]->SetScale(m_itemInfo[i].scale);
		m_item[m_itemInfo[i].type]->Update();
		m_item[m_itemInfo[i].type]->Draw();
	}
}

void ItemManager::Finalize() {
	m_itemInfo.erase(m_itemInfo.begin(), m_itemInfo.end());
	for (int i = ITEM_KIND - 1; i >= 0; i--) 
	{
		m_item[i]->Finalize();
	}
}

void ItemManager::CreateItem(ItemInfo info) {
	m_itemInfo.push_back(info);
}

void ItemManager::CreateItem(D3DXVECTOR3 pos, ITEM_TYPE type) {
	m_itemInfo.push_back(ItemInfo(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f), type));
}

int ItemManager::GetItemNum() {
	return (int)m_itemInfo.size();
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

COBBTree& ItemManager::GetOBB(ITEM_TYPE type) const {
	return m_item[type]->GetOBB();
}

void ItemManager::Hit(int idx) {
	m_itemInfo.erase(m_itemInfo.begin() + idx);
}