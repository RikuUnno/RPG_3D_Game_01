#pragma once
#include "DXlib.h"
#include "CapsuleCollider.h"
#include "GameObject.h"

class Player 
	: public GameObject
{
private: 

private: 

public:
	Player();
	virtual ~Player();

public: // �i�s�p
	void Update();		// ��{�i�s�̊֐�
	void Activate();	// �A�N�e�B�u��
	void Deactivate();	// ��A�N�e�B�u��

};