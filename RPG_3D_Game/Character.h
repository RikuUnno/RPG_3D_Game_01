#pragma once
#include "GameObject.h"


class Character
	: public GameObject
{
public:
	Character();
	virtual ~Character();

protected:
	virtual void Initialize(); // 初期化処理
	virtual void Finalize();   // 終了処理

public:
	virtual void Update();		// 基本進行の関数
	virtual void Draw();		// 基本描画の関数



};