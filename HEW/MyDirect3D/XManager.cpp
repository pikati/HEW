#include "XManager.h"
#include "main.h"
#include "MyDirect3D.h"
#include "CameraMediator.h"

#define PI 3.141592653589793

static LPD3DXEFFECT g_pEffect = NULL;


void XManager::Initialize(bool isCol, bool isAABB = false) {
	m_isCol = isCol;
	m_isaabb = isAABB;
	m_d3dDevice = GetDevice();
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXMatrixIdentity(&m_mat);
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//if (FAILED(D3DXCreateEffectFromFile(
	//	m_d3dDevice,
	//	"Effect00.fx",
	//	NULL,
	//	NULL,
	//	D3DXSHADER_DEBUG,
	//	NULL,
	//	&g_pEffect,//ToCreator()はやばいやつ()
	//	NULL
	//)))
	//{
	//	MessageBox(NULL, "えっふぇくとの読み込みに失敗しました", NULL, MB_OK);
	//	return ;
	//}
}

bool XManager::LoadXFile(const char* filePath) {
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	//m_obb = new OBB;
	HRESULT hr = D3DXLoadMeshFromX(
		filePath,
		D3DXMESH_MANAGED,
		m_d3dDevice,
		NULL,//隣接性データ（アジャンシー）
		&pD3DXMtrlBuffer,
		NULL,//シェーダー？
		&m_numMaterials,
		&m_pMesh
	);

	if (FAILED(hr)) {
		MessageBox(NULL, "モデルの読み込みに失敗しました", NULL, MB_OK);
		return false;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterials = new D3DMATERIAL9[m_numMaterials];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_numMaterials];

	for (DWORD i = 0; i < m_numMaterials; i++)
	{
		m_pMaterials[i] = d3dxMaterials[i].MatD3D;
		m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;
		m_pTextures[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(m_d3dDevice,
				d3dxMaterials[i].pTextureFilename,
				&m_pTextures[i])))
			{
				//MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}

	if (m_isCol)
	{
		if (m_isaabb)
		{
			m_aabb = new AABB;
			m_aabb->Initialize(m_min, m_max, m_position);
		}
		/*else {
			m_obb = new OBB;
			m_obb->CreateOBB(m_min, m_max);
		}*/
	}
	//m_obb->SetPosition(m_position, m_rotation, m_pMesh, &m_max, &m_min);
	//SAFE_RELEASE(pD3DXMtrlBuffer);
	return true;
}

void XManager::Update() {
	D3DXMATRIX t, r, s;
	D3DXMatrixIdentity(&m_mat);
	D3DXMatrixIdentity(&t);
	D3DXMatrixIdentity(&r);
	D3DXMatrixIdentity(&s);
	D3DXMatrixTranslation(&t, m_position.x, m_position.y, m_position.z);
	D3DXMatrixRotationYawPitchRoll(&r, m_rotation.x, m_rotation.y, m_rotation.z);
	D3DXMatrixScaling(&s, m_scale.x, m_scale.y, m_scale.z);
	m_mat = s * r * t;
	if (m_isCol)
	{
		if (m_isaabb)
		{
			m_aabb->Update(m_position);
		}
	}
}

void XManager::Draw() {	
	m_d3dDevice->SetTransform(D3DTS_WORLD, &m_mat);
	m_d3dDevice->SetVertexShader(NULL);
	m_d3dDevice->SetFVF(m_pMesh->GetFVF());
	for (DWORD i = 0; i < m_numMaterials; i++)
	{
		m_d3dDevice->SetMaterial(&m_pMaterials[i]);
		m_d3dDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
	/*if (m_isCol)
	{
		if (m_isaabb)
		{
			m_aabb->Draw();
		}
	}*/
}

void XManager::Finalize() {
	if (m_isCol)
	{
		if (m_isaabb)
		{
			delete m_aabb;
		}
		/*else {
			delete m_obb;
		}*/
	}
	for (int i = m_numMaterials - 1; i >= 0; i--) {
		SAFE_RELEASE(m_pTextures[i]);
	}
	delete[](m_pTextures);
	delete[](m_pMaterials);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_d3dDevice);
}

void XManager::SetTranslation(float x, float y, float z) {
	m_position = D3DXVECTOR3(x, y, z);
}

void XManager::SetTranslation(D3DXVECTOR3 pos) {
	m_position = pos;
}

void XManager::SetRotationX(float angle) {
	m_rotation.x = angle;
}

void XManager::SetRotationY(float angle) {
	m_rotation.y = angle;
}

void XManager::SetRotationZ(float angle) {
	m_rotation.z = angle;
}

void XManager::SetRotation(float x, float y, float z){
	m_rotation = D3DXVECTOR3(x, y, z);
}

void XManager::SetRotation(D3DXVECTOR3 rot) {
	m_rotation = rot;
}

void XManager::SetScaling(float scale) {
	m_scale = D3DXVECTOR3(scale, scale, scale);
}

void XManager::SetScaling(D3DXVECTOR3 scale) {
	m_scale = scale;
}

void XManager::SetScaling(float scaleX, float scaleY, float scaleZ) {
	m_scale = D3DXVECTOR3(scaleX, scaleY, scaleZ);
}

//OBB& XManager::GetOBB()const {
//	if (m_isaabb)
//	{
//		MessageBox(NULL, "OBB is disable", NULL, MB_OK);
//
//	}
//	/*return *m_obb;*/
//}

AABB& XManager::GetAABB()const {
	if (!m_isaabb)
	{
		MessageBox(NULL, "AABB is disable", NULL, MB_OK);

	}
	return *m_aabb;
}

void XManager::SetMinMax(D3DXVECTOR3 min, D3DXVECTOR3 max) {
	m_min = min;
	m_max = max;
}