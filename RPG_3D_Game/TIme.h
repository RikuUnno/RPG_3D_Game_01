#pragma once

class Time
{
private:
	double m_currentFrame; // ���݂̃t���[��
	double m_previousFrame; // �ߋ��̃t���[��
	double m_deltaTime; // �t���[���Ԃ̍���

public:
	Time(); // �R���X�g���N�^
	virtual ~Time(); // �f�X�g���N�^

public:
	void Update(); // �X�V

public:

	double DeltaTime(); // �f���^�^�C���̎擾
};