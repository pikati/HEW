#include "Circle.h"

void Circle::SetPosition(D3DXVECTOR3 newPos) {
	m_pos = newPos;
}

void Circle::SetRudius(float newRudius) {
	m_radius = newRudius;
}

D3DXVECTOR3 Circle::GetPosition() {
	return m_pos;
}

float Circle::GetRudius() {
	return m_radius;
}