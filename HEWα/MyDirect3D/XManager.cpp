#include "XManager.h"
#include "main.h"
#include "MyDirect3D.h"
#include "CameraMediator.h"

#define PI 3.141592653589793

static LPD3DXEFFECT g_pEffect = NULL;


void XManager::Initialize() {
	m_d3dDevice = GetDevice();
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXMatrixIdentity(&m_mat);
	if (FAILED(D3DXCreateEffectFromFile(
		m_d3dDevice,
		"Effect00.fx",
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&g_pEffect,//ToCreator()はやばいやつ()
		NULL
	)))
	{
		MessageBox(NULL, "えっふぇくとの読み込みに失敗しました", NULL, MB_OK);
		return ;
	}
}

bool XManager::LoadXFile(const char* filePath, bool isCol) {
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	m_bOBB = isCol;
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
	//m_obb->SetPosition(m_position, m_rotation, m_pMesh, &m_max, &m_min);
	//SAFE_RELEASE(pD3DXMtrlBuffer);
	m_COBBTree = new COBBTree;
	if (m_bOBB) 
	{
		m_COBBTree->Create(m_pMesh, 5);
	}
	return true;
}

void XManager::Update() {
	/*if (m_bOBB)
	{
		m_obb->SetPosition(m_position, m_rotation, m_pMesh, &m_max, &m_min);
	}*/
	D3DXMATRIXA16 matTranslation, matRotation, matScale;
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixTranslation(&matTranslation, m_position.x, m_position.y, m_position.z);
	D3DXMatrixRotationYawPitchRoll(&matRotation, m_rotation.y, m_rotation.x, m_rotation.z);
	D3DXMatrixScaling(&matScale, m_scale.x, m_scale.y, m_scale.z);
	m_mat = matScale * matRotation * matTranslation;
}

void XManager::Draw() {
	
	D3DXMATRIX *mat;
	mat = CameraMediator::GetCameraMatrix();
	*mat = m_mat * *mat;
	
	m_d3dDevice->SetTransform(D3DTS_WORLD, &m_mat);
	g_pEffect->SetTechnique("BasicTec");
	g_pEffect->SetMatrix("matWorldViewProj", mat);
	g_pEffect->Begin(NULL, 0);
	g_pEffect->BeginPass(0);
	for (DWORD i = 0; i < m_numMaterials; i++)
	{
		{
			g_pEffect->SetValue("Diffuse", (LPVOID)&m_pMaterials[i].Diffuse, 16);
		}
		g_pEffect->SetTexture("BasicTec", m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
	/*if (m_bOBB)
	{
		m_COBBTree->Draw(2);
	}*/
	g_pEffect->EndPass();
	g_pEffect->End();
}

void XManager::Finalize() {
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

COBBTree& XManager::GetOBB() const{
	return *m_COBBTree;
}

D3DXMATRIX* XManager::GetMatrix() {
	return &m_mat;
}