#include "DisplaySandStorm.h"
#include "main.h"
#include "Polygons.h"

#define SANDSTORM_HEGIHT	720.0f
#define SANDSTORM_WIDTH		640.0f

void DisplaySandStorm::Initialize() {
	m_pDevice = GetDevice();
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/Other/SandStorm1.png", &m_texture);
}

void DisplaySandStorm::Draw() {
	float x;
	if (p1)
	{
		x = 0;
	}
	else
	{
		x = SANDSTORM_WIDTH;
	}
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	Polygons::Draw(x, 0.0f, SANDSTORM_WIDTH, SANDSTORM_HEGIHT, 0, 0, 1, 1, m_texture);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
}

void DisplaySandStorm::Finalize() {
	SAFE_RELEASE(m_texture);
}

void DisplaySandStorm::SetPlayer(bool b) {
	p1 = b;
}