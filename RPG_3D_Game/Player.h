#pragma once
#include "DXlib.h"
#include "GameObject.h"

class Player 
	: public GameObject
{
private: 

public:
	Player();
	virtual ~Player();

public: // 進行用
	void Update();		// 基本進行の関数

};