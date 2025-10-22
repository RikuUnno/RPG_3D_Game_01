// 基本的なゲーム内におけるオブジェクトの親クラス

#pragma once
#include "Transform.h"

class GameObject
{
protected:
	bool m_isActive; // オブジェクトの状態

protected:
	Transform m_transform; // このオブジェクトのpos/pot/scaを保持する

public:
	GameObject(); // コンストラクタ
	virtual ~GameObject(); // デストラクト

protected:
	bool IsActive(bool active) { m_isActive = active; } // 引数がtrueならアクティブfalseなら非アクティブにする関数

};