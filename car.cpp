#include "DxLib.h"
#include "game.h"
#include "car.h"
#include "player.h"

namespace
{

	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;

	constexpr float kSpeed = 10.0f;

	// ジャンプ力
	constexpr float kJumpacc = -15.0f;
	// 重力
	constexpr float kGravity = 0.5f;
}

Car::Car()
{
	//rand() % 100;	// 0~99
	//GetRand(100);	//  0~100
	m_handle = -1;
	m_fieldY = 0.0f;

	m_moveType = kMoveTypeNormal;

	m_waitFrame = 0;
	m_StopOneTimeStop = 0;
	m_getPos = 0.0f;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = -kSpeed;
	m_vec.y = 0.0f;

	// 動きのバリエーションを選択
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	// デバッグ用
	m_moveType = kMoveTypeNormal;

	// 動き始めるまでの時間を設定　1秒から３秒待つ　60フレームから180フレーム
	m_waitFrame = GetRand(kWaitFrameMax - kWaitFrameMin) + kWaitFrameMin;
	
	// 車が止まっている時間1秒待つ
	m_StopOneTimeStop = kWaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}

////////////////////////////
// private
////////////////////////////
// まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;
}
// 一時停止フェイント
// ジャンプする
void Car::updateJump()
{
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		if(m_pos.x < 400)
		isField = true;
	}
	m_pos += m_vec;

	if (isField)
	{
		m_vec.y = kJumpacc;	// ジャンプ開始
	}
	if (m_pos.x < 400)
	{
		m_vec.y += kGravity;
	}
}
void Car::updateStop()
{
	m_pos += m_vec;
	if (m_pos.x < 400 && m_StopOneTimeStop > 0)
	{
		m_StopOneTimeStop--;
		m_vec.x = 0;
		return;
	}
	m_vec.x = -kSpeed;
}

//　途中で引き返す（必ず成功）
void Car::updateReturn()
{
	m_pos += m_vec;
	if (m_pos.x < 400)
	{
		m_vec.x *= -1;
	}
}