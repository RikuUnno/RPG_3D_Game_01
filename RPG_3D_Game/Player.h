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

public: // 進行用
	void Update();		// 基本進行の関数
	void Activate();	// アクティブ時
	void Deactivate();	// 非アクティブ時

};