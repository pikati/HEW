#define _CRT_SECURE_NO_WARNINGS
#include "Utility.h"
#include "Player.h"
#include "Input.h"
#include "camera.h"
#include "Joycon.h"


//半径0.125
void Player::Initialize() {
	m_itemGet = false;
	m_hit = false;
	m_deceleration = false;
	m_coolTime.bCoolTime = false;
	m_coolTime.coolTime = COOL_TIME;
	m_maxSpeed = MAX_SPEED;
	m_minSpeed = MIN_SPEED;
	m_effectTime = 0;
	Camera_Initialize();
	m_info.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.curveAngle = 0.0f;
	m_info.bloomPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.flowAngleX = 0.0f;
	m_info.flowAngleY = 0.0f;
	m_info.flowPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.oldPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_info.playerVerocity = 0.0f;
	m_info.angle = 90.0f * (D3DX_PI / 180.0f);
}

void Player::Update(int i) {
	m_hit = false;
	UpdateEffect();
	MoveSide(i);
	MoveForward();
	FlowAnimation();

	CheckCoolTime();

	if (i == 0)
	{
		MyOutputDebugString("pos:%f %f %f\n", m_info.position.x, m_info.position.y, m_info.position.z)
	}
	
	//CalcDirection();
	//MyOutputDebugString("x:%f y:%f z:%f\n", m_position.x, m_position.y, m_position.z);
	//MyOutputDebugString("angle:%f\n", m_angle);

}

void Player::MoveForward() {
	//当たってなければ加速
	if (m_deceleration == false)
	{
		m_info.playerVerocity += 0.75f;
	}
	else
	{
		//当たったら減速　一定値以下になったらfalseにしてまた加速
		m_info.playerVerocity -= 1.0f;
		if (m_info.playerVerocity <= m_minSpeed)
		{
			m_info.playerVerocity = m_minSpeed;
			m_deceleration = false;
		}
	}

	//プレイヤーの速さ
	if (m_info.playerVerocity >= m_maxSpeed)
	{
		m_info.playerVerocity = m_maxSpeed;
	}
	//0.01より遅くはならない
	if (m_info.playerVerocity < m_minSpeed)
	{
		m_info.playerVerocity = m_minSpeed;
	}
	//自動前進
	m_info.position.z += sinf(m_info.angle) * 0.015f * m_info.playerVerocity;
	m_info.position.x -= cosf(m_info.angle) * 0.015f * m_info.playerVerocity;
	m_info.bloomPosition.z += sinf(m_info.angle) * 0.015f * m_info.playerVerocity;
	m_info.bloomPosition.x -= cosf(m_info.angle) * 0.015f * m_info.playerVerocity;

}

void Player::MoveSide(int i) {
	if (i == 0) {
		if (Input::GetKey(DIK_D) || g_diJoyState2[0] & BUTTON_RIGHT)
		{
			m_info.angle += ROTATE;
			m_info.curveAngle += -ROTATE / 2.0f;
			if (m_info.curveAngle < -CURVE_ANGLE_MAX)
			{
				m_info.curveAngle = -CURVE_ANGLE_MAX;
			}
			return;
		}
		else if (Input::GetKey(DIK_A) || g_diJoyState2[0] & BUTTON_LEFT)
		{
			m_info.angle += -ROTATE;
			m_info.curveAngle += ROTATE / 2.0f;
			if (m_info.curveAngle > CURVE_ANGLE_MAX)
			{
				m_info.curveAngle = CURVE_ANGLE_MAX;
			}
			return;
		}
		/*else 
		{
			m_dir = NON;
		}*/
	}
	else {
		if (Input::GetKey(DIK_L) || g_diJoyState2[2] & BUTTON_RIGHT)
		{
			m_info.angle += ROTATE;
			m_info.curveAngle += -ROTATE / 2.0f;
			if (m_info.curveAngle < -CURVE_ANGLE_MAX)
			{
				m_info.curveAngle = -CURVE_ANGLE_MAX;
			}
			return;
		}
		else if (Input::GetKey(DIK_J) || g_diJoyState2[2] & BUTTON_LEFT)
		{
			m_info.angle += -ROTATE;
			m_info.curveAngle += ROTATE / 2.0f;
			if (m_info.curveAngle > CURVE_ANGLE_MAX)
			{
				m_info.curveAngle = CURVE_ANGLE_MAX;
			}
			return;
		}
	}
	if (m_info.curveAngle > 0)
	{
		m_info.curveAngle += -ROTATE;
		if (m_info.curveAngle < 0)
		{
			m_info.curveAngle = 0;
		}
	}
	else if (m_info.curveAngle < 0)
	{
		m_info.curveAngle += ROTATE;
		if (m_info.curveAngle > 0)
		{
			m_info.curveAngle = 0;
		}
	}
}

void Player::FlowAnimation() {
	m_info.flowPosition.x = cosf(m_info.flowAngleX) * 0.01f;
	m_info.flowPosition.y = sinf(m_info.flowAngleY) * 0.01f;
	m_info.flowPosition.z = 0;
	m_info.flowAngleX += rand() % 10 * 0.02f;
	m_info.flowAngleY += rand() % 10 * 0.02f;
	if (m_info.flowAngleX > 2 * D3DX_PI)
	{
		m_info.flowAngleX = 0;
	}
	if (m_info.flowAngleY > 2 * D3DX_PI)
	{
		m_info.flowAngleY = 0;
	}
}

D3DXVECTOR3 Player::GetPlayerPosition() {
	D3DXVECTOR3 tmp;
	tmp = m_info.position;
	tmp.y -= 0.25f;
	return tmp;
}

void Player::Hit(DIRECTION dir) {
	m_hit = true;
	m_deceleration = true;
	switch (dir)
	{
	case UP:
		m_info.position.z += 2.0f;
		break;
	case DOWN:
		m_info.position.z += -2.0f;
		break;
	case RIGHT:
		m_info.position.x += 2.0f;
		break;
	case LEFT:
		m_info.position.x += -2.0f;
		break;
	default:
		break;
	}
}

void Player::HitWall() {
	/*if (m_dir == RIGHT)
	{
		m_position.x -= 0.05f;
		m_bloomPosition.x -= 0.05f;
	}
	else
	{
		m_position.x += 0.05f;
		m_bloomPosition.x += 0.05f;
	}*/
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

void Player::SetItemEffect(ITEM_TYPE type) {
	if (type == TAIYAKI)
	{
		m_maxSpeed = MAX_SPEED * 1.5f;
		m_minSpeed = MIN_SPEED;
		m_effectTime = 100;
	}
	else if (type == MERONPAN)
	{
		m_maxSpeed = MAX_SPEED * 0.75f;
		m_minSpeed = MIN_SPEED;
		m_effectTime = 50;
	}
}

void Player::UpdateEffect() {
	if (m_effectTime > 0)
	{
		m_effectTime--;
	}
	else
	{
		m_effectTime = 0;
		m_maxSpeed = MAX_SPEED;
		m_minSpeed = MIN_SPEED;
	}
}

D3DXVECTOR3 Player::GetPlayerFlow() {
	return m_info.flowPosition;
}

PlayerInfo Player::GetPlayerInfo() {
	return m_info;
}

void Player::CalcDirection() {
	float x = m_info.position.x - m_info.oldPosition.x;
	float z = m_info.position.z - m_info.oldPosition.z;
	D3DXVECTOR3 vec = D3DXVECTOR3(x, 0.0f, z);
	float normalize = sqrtf(x * x + z * z);
	vec = vec / normalize;
	m_info.angle = atan2f(vec.z, vec.x) * (180.0f / D3DX_PI);
	if (m_info.angle > 180)
	{
		m_info.angle += -360;
	}
	else if (m_info.angle < -180)
	{
		m_info.angle += 360;
	}

	m_info.angle = m_info.angle * RADIAN;

	m_info.oldPosition = m_info.position;
}

float Player::GetPlayerAngle() {
	return m_info.angle;
}