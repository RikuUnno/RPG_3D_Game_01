#pragma once

class Time
{
private:
	double m_currentFrame; // 現在のフレーム
	double m_previousFrame; // 過去のフレーム
	double m_deltaTime; // フレーム間の差分

public:
	Time();
	virtual ~Time();

public:
	void Update();

public:

	double DeltaTime();
};