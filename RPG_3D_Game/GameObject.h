// ��{�I�ȃQ�[�����ɂ�����I�u�W�F�N�g�̐e�N���X

#pragma once
#include "Transform.h"

class GameObject
{
protected:
	bool m_isActive; // �I�u�W�F�N�g�̏��

protected:
	Transform m_transform; // ���̃I�u�W�F�N�g��pos/pot/sca��ێ�����

public:
	GameObject(); // �R���X�g���N�^
	virtual ~GameObject(); // �f�X�g���N�g

protected:
	bool IsActive(bool active) { m_isActive = active; } // ������true�Ȃ�A�N�e�B�ufalse�Ȃ��A�N�e�B�u�ɂ���֐�

};