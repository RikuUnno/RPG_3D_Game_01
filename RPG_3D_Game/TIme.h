#pragma once

class Time
{
private:
	double m_currentFrame; // ���݂̃t���[��
	double m_previousFrame; // �ߋ��̃t���[��
	double m_deltaTime; // �t���[���Ԃ̍���

public:
	Time();
	virtual ~Time();

public:
	void Update();

public:

	double DeltaTime();
};