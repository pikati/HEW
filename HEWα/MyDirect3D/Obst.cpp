#include "Obst.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*ここ抽象クラス化*/
/*障害物ごとにクラスを作る 初期化のタイミングで何を作成するかを決める*/

Obst::Obst()
{
	m_max = D3DXVECTOR3(0, 0, 0);
	m_min = D3DXVECTOR3(0, 0, 0);
}


Obst::~Obst()
{
}

void Obst::Initialize()
{

	m_xmanager = new XManager;
	const char *filename[4] = {
	{ "Models/obstacleFire.x"},
	{ "Models/obstacleSand.x"},
	{ "Models/obstacleFallHole.x"},
	{ "Models/obstacleTree.x"}
	};
}

void Obst::Update()
{

}

void Obst::Draw()
{

}

void Obst::Finalize()
{

}