#include "TIme.h"
#include "DxLib.h"

// �R���X�g���N�^
Time::Time()
{
	m_currentFrame = 0;
	m_previousFrame = 0;
	m_deltaTime = 0;
}

// �f�X�g���N�^
Time::~Time()
{}

// �X�V
void Time::Update()
{
	// deltaTime�̏���
	m_previousFrame = m_currentFrame; // �O�t���[���̎��Ԃ̕ۑ�
	m_currentFrame = GetNowCount();	// ���݂̃t���[���̌o�ߎ���
	m_deltaTime = (m_currentFrame - m_previousFrame) / 1000.0; // �~���b���b

}

// �f���^�^�C���̎擾
double Time::DeltaTime()
{
	return m_deltaTime;
}