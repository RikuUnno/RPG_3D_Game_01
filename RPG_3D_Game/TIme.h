#pragma once

class Time
{
private:
	double m_currentFrame; // 現在のフレーム
	double m_previousFrame; // 過去のフレーム
	double m_deltaTime; // フレーム間の差分

public:
	Time(); // コンストラクタ
	virtual ~Time(); // デストラクタ

public:
	void Update(); // 更新

public:

	double DeltaTime(); // デルタタイムの取得
};