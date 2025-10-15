// 基本的なゲーム内におけるオブジェクトの親クラス

#pragma once
#include "Transform.h"

class GameObject
{
protected:
	bool m_isActive; // オブジェクトの状態

protected:
	Transform transform; // このオブジェクトのpos/pot/scaを保持する

public:
	GameObject() { m_isActive = true; /*アクティブで初期化*/ } // コンストラクタ
	virtual ~GameObject() {} // デストラクト

protected:
	bool IsActive(bool active) { m_isActive = active; } // 引数がtrueならアクティブfalseなら非アクティブにする関数

};