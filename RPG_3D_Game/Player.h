#pragma once
#include "DXlib.h"
#include "CapsuleCollider.h"

class ColliderManager;

class Player
{
private: // Collider

private: // �I�u�W�F�N�g�̏��
	bool m_isActive; // �I�u�W�F�N�g�i�R���C�_�[�j�̏��

public:
	Player();
	virtual ~Player();

public: // �i�s�p
	void Update();		// ��{�i�s�̊֐�
	void Activate();	// �A�N�e�B�u��
	void Deactivate();	// ��A�N�e�B�u��

};