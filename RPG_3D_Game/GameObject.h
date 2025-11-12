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

public:
	void SetActive(bool active) { m_isActive = active; } // アクティブ状態を設定
	bool IsActive() const { return m_isActive; }         // アクティブ状態を取得

public:
	Transform GetTrans() const; // Transformを返す
	void SetTransform(Transform trans); // Transformをセットする

};