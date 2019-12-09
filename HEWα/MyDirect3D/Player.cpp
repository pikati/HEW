#define _CRT_SECURE_NO_WARNINGS
#include "Utility.h"
#include "Player.h"
#include "Input.h"
#include "camera.h"
#include "Joycon.h"

/*プレイヤーとカメラとxmanager.cpp変更*/
Player::Player() {
}

Player::~Player() {
}

//半径0.125
void Player::Initialize(int i) {
	m_xfile_Player = new XManager;
	m_xfile_Player->Initialize();
	m_bloom = new XManager;
	m_bloom->Initialize();
	m_num = i;
	/*四角いモデルのポジション初期化*/
	m_playerPos = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	m_xfile_Player->SetTranslation(m_playerPos);
	/*読み込みたいファイルを引数に指定します*/
	if (i == 0) {
		m_xfile_Player->LoadXFile("Models/Player/player.x", true);
		m_xfile_Player->SetScaling(0.5f);
		m_xfile_Player->SetRotationY(180.0f);
	}
	else {
		m_xfile_Player->LoadXFile("Models/Player/Player.x", true);
		m_xfile_Player->SetScaling(0.5f);
		m_xfile_Player->SetRotationY(180.0f);
	}
	m_bloom->LoadXFile("Models/Player/Bloom.x", false);
	m_bloomPos = D3DXVECTOR3(0.05f, 0.0f, -0.1f);
	m_bloom->SetScaling(0.5f);
	m_bloom->SetTranslation(m_bloomPos);
	m_bloom->SetRotation(90.0f, 0.0f, 0.0f);
	m_itemGet = false;

	m_hit = false;
	m_deceleration = false;

	m_playerVerocity = 0;

	m_coolTime.bCoolTime = false;
	m_coolTime.coolTime = COOL_TIME;

	Camera_Initialize();

	m_angle = 90.0f * (D3DX_PI / 180.0f);
	m_prePlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Player::Update() {
	m_hit = false;
	MoveSide();
	MoveForward();

	m_xfile_Player->Update();
	m_bloom->Update();
	m_xfile_Player->SetTranslation(m_playerPos);
	m_xfile_Player->SetRotationY(m_angle + 90.0f * (D3DX_PI / 180.0f));
	m_bloom->SetTranslation(m_bloomPos);
	m_bloom->SetRotationY(m_angle - 90.0f * (D3DX_PI / 180.0f));
	CheckCoolTime();
	//CalcDirection();
	//MyOutputDebugString("x:%f y:%f z:%f\n", m_playerPos.x, m_playerPos.y, m_playerPos.z);
	//MyOutputDebugString("angle:%f\n", m_angle);
}

void Player::Draw() {
	m_xfile_Player->Draw();
	m_bloom->Draw();
}

void Player::Finalize() {
	m_bloom->Finalize();
	delete m_bloom;
	m_xfile_Player->Finalize();
	delete m_xfile_Player;
}

void Player::MoveForward() {
	//当たってなければ加速
	if (m_deceleration == false)
	{
		m_playerVerocity += 1.0f;
	}
	else
	{
		//当たったら減速　一定値以下になったらfalseにしてまた加速
		m_playerVerocity -= 0.2f;
		if (m_playerVerocity <= 5.0f)
		{
			m_playerVerocity = 5.0f;
			m_deceleration = false;
		}
	}

	//プレイヤーの速さ　2.0より速くはならない
	if (m_playerVerocity >= 10.0f)
	{
		m_playerVerocity = 10.0f;
	}
	//0.01より遅くはならない
	if (m_playerVerocity < 0.01f)
	{
		m_playerVerocity = 0.01f;
	}
	//自動前進
	m_playerPos.z += sinf(m_angle) * 0.015f * m_playerVerocity;
	m_playerPos.x -= cosf(m_angle) * 0.015f * m_playerVerocity;
	m_bloomPos.z += sinf(m_angle) * 0.015f * m_playerVerocity;
	m_bloomPos.x -= cosf(m_angle) * 0.015f * m_playerVerocity;

}

void Player::MoveSide() {
	if (m_num == 0) {
		if (Input::GetKey(DIK_D) || g_diJoyState2[0] & BUTTON_RIGHT)
		{
			/*m_playerPos.x += 0.05f;
			m_bloomPos.x += 0.05f;
			m_dir = RIGHT;
			if (m_playerPos.x >= 0.9f)
			{
				HitWall();
				Hit();
			}*/
			m_angle += ROTATE;
		}
		else if (Input::GetKey(DIK_A) || g_diJoyState2[0] & BUTTON_LEFT)
		{
			/*m_playerPos.x -= 0.05f;
			m_bloomPos.x -= 0.05f;
			m_dir = LEFT;
			if (m_playerPos.x <= -0.9f)
			{
				HitWall();
				Hit();
			}*/
			m_angle += -ROTATE;
		}
		/*else
		{
			m_dir = NON;
		}*/
	}
	else {
		if (Input::GetKey(DIK_L) || g_diJoyState2[2] & BUTTON_RIGHT)
		{
			/*m_playerPos.x += 0.05f;
			m_bloomPos.x += 0.05f;
			m_dir = RIGHT;
			if (m_playerPos.x >= 0.9f)
			{
				HitWall();
				Hit();
			}*/
			m_angle += ROTATE;
		}
		else if (Input::GetKey(DIK_J) || g_diJoyState2[2] & BUTTON_LEFT)
		{
			/*m_playerPos.x -= 0.05f;
			m_bloomPos.x -= 0.05f;
			m_dir = LEFT;
			if (m_playerPos.x <= -0.9f)
			{
				HitWall();
				Hit();
			}*/
			m_angle += -ROTATE;
		}
		/*else
		{
			m_dir = NON;
		}*/
	}
}

D3DXVECTOR3 Player::GetPlayerPosition() {
	D3DXVECTOR3 tmp;
	tmp = m_playerPos;
	tmp.y -= 0.25f;
	return tmp;
}

void Player::Hit() {
	m_hit = true;
	m_deceleration = true;
}

void Player::HitWall() {
	/*if (m_dir == RIGHT)
	{
		m_playerPos.x -= 0.05f;
		m_bloomPos.x -= 0.05f;
	}
	else
	{
		m_playerPos.x += 0.05f;
		m_bloomPos.x += 0.05f;
	}*/
}

//OBB* Player::GetOBB() {
//	return m_xfile_Player->GetOBB();
//}

COBBTree& Player::GetOBB() const {
	return m_xfile_Player->GetOBB();
}

D3DXMATRIX* Player::GetMatrix() {
	return m_xfile_Player->GetMatrix();
}

void Player::Rotation()
{
	m_xfile_Player->SetRotationZ(m_angle);
}

CoolTime& Player::GetCoolTime() {
	return m_coolTime;
}

void Player::CheckCoolTime() {
	if (m_coolTime.bCoolTime)
	{
		m_coolTime.coolTime--;
		if (m_coolTime.coolTime <= 0)
		{
			m_coolTime.bCoolTime = false;
			m_coolTime.coolTime = COOL_TIME;
		}
	}
}

void Player::StartCoolTime() {
	m_coolTime.bCoolTime = true;
}

void Player::CalcDirection() {
	float x = m_playerPos.x - m_prePlayerPos.x;
	float z = m_playerPos.z - m_prePlayerPos.z;
	D3DXVECTOR3 vec = D3DXVECTOR3(x, 0.0f, z);
	float normalize = sqrtf(x * x + z * z);
	vec = vec / normalize;
	m_angle = atan2f(vec.z, vec.x) * (180.0f / D3DX_PI);
	if (m_angle > 180)
	{
		m_angle += -360;
	}
	else if (m_angle < -180)
	{
		m_angle += 360;
	}

	//MyOutputDebugString("角度：%f\n", m_angle);

	m_angle = m_angle * (D3DX_PI / 180.0f);

	m_prePlayerPos = m_playerPos;
}

float Player::GetPlayerAngle() {
	return m_angle;
}