#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

// ��{�i�s
void Player::Update()
{
	if (m_isActive)
	{
		Activate();
	}
	else if (!m_isActive)
	{
		Deactivate();
	}
}

// �A�N�e�B�u��
void Player::Activate()
{
	// collider.SetActiveCollider(m_isActive);	// �����蔻��̃A�N�e�B�u��
}

// ��A�N�e�B�u��
void Player::Deactivate()
{
	// collider.SetActiveCollider(!m_isActive); // �����蔻��̔�A�N�e�B�u��
}