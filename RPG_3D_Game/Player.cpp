#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

// 基本進行
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

// アクティブ時
void Player::Activate()
{
	// collider.SetActiveCollider(m_isActive);	// 当たり判定のアクティブ化
}

// 非アクティブ時
void Player::Deactivate()
{
	// collider.SetActiveCollider(!m_isActive); // 当たり判定の非アクティブ化
}