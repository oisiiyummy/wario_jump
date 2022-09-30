#include"DxLib.h"
#include"SceneMain.h"
#include "Game.h"

namespace
{
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

SceneMain::SceneMain()
{
	m_hPlayer = -1;
	m_hCar = -1;
}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{
	int m_hPlayer = LoadGraph("data/player.png");
	int m_hCar = LoadGraph("data/car.png");

	m_player.setGraphic(m_hPlayer);
	m_player.setup(kFieldY);

	m_car.setGraphic(m_hCar);
	m_car.setup(kFieldY);
}

void SceneMain::end()
{

}

// �Q�[������
bool SceneMain::update()
{
	m_player.update();
	m_car.update();

	m_player.getPos();

	// �����蔻��
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);
	}
	return false;
}

// �`��
void SceneMain::draw()
{
	// �n�ʂ̕`��
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_car.draw();
}
