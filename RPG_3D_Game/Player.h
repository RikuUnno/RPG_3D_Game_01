#pragma once
#include "DXlib.h"
#include "GameObject.h"
#include "Character.h"	

class Player 
	: public Character
{
private: 

public:
	Player();
	virtual ~Player();

private:
	void Initialize() override; // 初期化処理
	void Finalize() override;   // 終了処理

public: // 進行用
	void Update() override;		// 基本進行の関数
	void Draw() override;		// 基本描画の関数

// モデル
// アニメーション
// サウンド
// 当たり判定
};