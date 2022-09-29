#include "DxLib.h"
#include "game.h"
#include "car.h"
#include "player.h"

namespace
{

	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;

	constexpr float kSpeed = 10.0f;

	// �W�����v��
	constexpr float kJumpacc = -15.0f;
	// �d��
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

	// �����̃o���G�[�V������I��
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
	// �f�o�b�O�p
	m_moveType = kMoveTypeNormal;

	// �����n�߂�܂ł̎��Ԃ�ݒ�@1�b����R�b�҂@60�t���[������180�t���[��
	m_waitFrame = GetRand(kWaitFrameMax - kWaitFrameMin) + kWaitFrameMin;
	
	// �Ԃ��~�܂��Ă��鎞��1�b�҂�
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
// �܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;
}
// �ꎞ��~�t�F�C���g
// �W�����v����
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
		m_vec.y = kJumpacc;	// �W�����v�J�n
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

//�@�r���ň����Ԃ��i�K�������j
void Car::updateReturn()
{
	m_pos += m_vec;
	if (m_pos.x < 400)
	{
		m_vec.x *= -1;
	}
}