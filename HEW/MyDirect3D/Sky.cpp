#include "Sky.h"
#include "main.h"

void Sky::Initialize() {
	m_pDevice = GetDevice();
	m_x = new XManager;
	m_x->Initialize(false, false);
	m_x->LoadXFile("Asset/Models/Other/Sky.x");
}

void Sky::Update() {

}

void Sky::Draw() {
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_x->Draw();
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Sky::Finalize() {
	m_x->Finalize();
	delete m_x;
	SAFE_RELEASE(m_pDevice);
}