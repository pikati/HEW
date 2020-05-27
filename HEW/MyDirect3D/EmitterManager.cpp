/**
 *	@file		EmitterManager.cpp
 *	@brief		エミッター管理クラスの実装
 *	@authotr	AT-12C-342 門脇 喬哉
*/

#include "EmitterManager.h"
#include "NormalParticle.h"
#include "main.h"
#include "input.h"
#include "FlameParticle.h"
#include "WaterParticle.h"
#include "FeverParticle.h"
#include "PowerUpParticle.h"
#include "PowerDownParticle.h"
#include "SandStormParticle.h"
#include "HitParticle.h"
#include "HitEffect.h"
#include "PlayerHitEffect.h"
#include "SpeedEffect.h"

/** @def
 * NormalParticleのテクスチャの相対パス
 */
#define NORMAL_TEXTURE	"Asset/Texture/Effect/Star.png"

 /** @def
  * FeverParticleのテクスチャの相対パス
  */
#define FEVER_TEXTURE	"Asset/Texture/Effect/Fever.jpg"

  /** @def
   * FeverParticleのテクスチャの相対パス
   */
#define HIT_TEXTURE	"Asset/Texture/Effect/HitEffect.png"

   /** @def
	* SpeedEffectのテクスチャの相対パス
	*/
#define SPEED_TEXTURE	"Asset/Texture/Effect/Speed.jpg"

//TはTextureのT
enum {
	T_STAR,
	T_FEVER,
	T_HIT,
	T_SPEED
};

void EmitterManager::Initialize() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 tex;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		NORMAL_TEXTURE,
		&tex);
	m_texture.push_back(tex);
	D3DXCreateTextureFromFile(pDevice,
		FEVER_TEXTURE,
		&tex);
	m_texture.push_back(tex);
	D3DXCreateTextureFromFile(pDevice,
		HIT_TEXTURE,
		&tex);
	m_texture.push_back(tex);
	D3DXCreateTextureFromFile(pDevice,
		SPEED_TEXTURE,
		&tex);
	m_texture.push_back(tex);
}

void EmitterManager::Update(D3DXVECTOR3 pos) {
	for (int i = 0; i < (int)m_emitter.size(); i++)
	{
		ParticleType type = m_emitter[i]->GetParticleType();
		m_emitter[i]->SetPlayerPosition(pos);
		if (type == PARTICLE_SPEED)
		{
			m_emitter[i]->SetplayerAngle(m_playerAngle);
		}
		m_emitter[i]->Update();
		if (type == PARTICLE_FEVER || type == PARTICLE_POWERUP || type == PARTICLE_POWERDOWN || type == PARTICLE_HIT_PLAYER || type == PARTICLE_SPEED)
		{
			m_emitter[i]->SetPosition(pos);
		}
		
		if (m_emitter[i]->GetLifeTime() <= 0)
		{
			DestroyEmitter(i);
		}
	}
}

void EmitterManager::Draw(){
	for (int i = 0; i < (int)m_emitter.size(); i++)
	{
		m_emitter[i]->Draw();
	}
}

void EmitterManager::Finalize() {
	for (int i = m_emitter.size() - 1; i >= 0; i--)
	{
		m_emitter[i]->Finalize();
		delete m_emitter[i];
	}
	m_emitter.erase(m_emitter.begin(), m_emitter.end());
}

int EmitterManager::CreateEmitter(ParticleType type, D3DXVECTOR3 pos) {
	switch (type)
	{
	case PARTICLE_NORMAL:
	{
		Emitter* emitter = new HitParticle;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		m_emitter[idx]->SetPosition(pos);
		m_emitter[idx]->Initialize(m_texture[T_STAR], D3DXVECTOR2(0.25f, 0.25f));
		m_emitter[idx]->SetPosition(pos);
		Emitter* emitter2 = new HitEffect;
		m_emitter.push_back(emitter2);
		idx = m_emitter.size() - 1;
		m_emitter[idx]->SetPosition(pos);
		m_emitter[idx]->Initialize(m_texture[T_HIT], D3DXVECTOR2(0.25f, 0.25f));
		m_emitter[idx]->SetPosition(pos);
		break;
	}
	case PARTICLE_FLAME:
	{
		Emitter* emitter = new FlameParticle;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		m_emitter[idx]->Initialize(m_texture[T_STAR], D3DXVECTOR2(1.0f, 1.0f));
		m_emitter[idx]->SetPosition(pos);
		break;
	}
	case PARTICLE_WATER:
	{
		Emitter* emitter = new WaterParticle;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		m_emitter[idx]->Initialize(m_texture[T_STAR], D3DXVECTOR2(1.0f, 1.0f));
		m_emitter[idx]->SetPosition(pos);
		break;
	}
	case PARTICLE_FEVER:
	{
		Emitter* emitter = new FeverParticle;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		m_emitter[idx]->Initialize(m_texture[T_FEVER], D3DXVECTOR2(0.1f, 0.1f));
		m_emitter[idx]->SetPosition(pos);
		break;
	}
	case PARTICLE_POWERUP:
	{
		Emitter* emitter = new PowerUpParticle;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		m_emitter[idx]->Initialize(m_texture[T_FEVER], D3DXVECTOR2(0.1f, 0.1f));
		m_emitter[idx]->SetPosition(pos);
		break;
	}
	case PARTICLE_POWERDOWN:
	{
		Emitter* emitter = new PowerDownParticle;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		m_emitter[idx]->Initialize(m_texture[T_FEVER], D3DXVECTOR2(0.1f, 0.1f));
		m_emitter[idx]->SetPosition(pos);
		break;
	}
	case PARTICLE_SAND_STORM:
	{
		Emitter* emitter = new SandStormParticle;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		m_emitter[idx]->Initialize(m_texture[T_FEVER], D3DXVECTOR2(0.1f, 0.1f));
		m_emitter[idx]->SetPosition(pos);
		break;
	}
	case PARTICLE_HIT_PLAYER:
	{
		Emitter* emitter = new PlayerHitEffect;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		D3DXVECTOR3 position = pos;
		position.y += 1.0f;
		m_emitter[idx]->SetPosition(position);
		m_emitter[idx]->Initialize(m_texture[T_STAR], D3DXVECTOR2(0.02f, 0.02f));
		m_emitter[idx]->SetPosition(position);
		break;
	}
	case PARTICLE_SPEED:
	{
		Emitter* emitter = new SpeedEffect;
		m_emitter.push_back(emitter);
		int idx = m_emitter.size() - 1;
		D3DXVECTOR3 position = pos;
		m_emitter[idx]->SetPosition(position);
		m_emitter[idx]->Initialize(m_texture[T_SPEED], D3DXVECTOR2(0.2f, 0.2f));
		m_emitter[idx]->SetPosition(position);
		break;
	}
	default:
		break;
	}
	return m_emitter.size() - 1;
}

void EmitterManager::DestroyEmitter(int idx) {
	delete m_emitter[idx];
	m_emitter.erase(m_emitter.begin() + idx);
}

void EmitterManager::SetPlayerAngle(float angle) {
	m_playerAngle = angle;
}