#pragma once
#include "DXlib.h"
#include "CapsuleCollider.h"

class ColliderManager;

class Player
{
private: // Collider

private: // オブジェクトの状態
	bool m_isActive; // オブジェクト（コライダー）の状態

public:
	Player();
	virtual ~Player();

public: // 進行用
	void Update();		// 基本進行の関数
	void Activate();	// アクティブ時
	void Deactivate();	// 非アクティブ時

};