#include "GameObject.h"
#include "DxLib.h"

// �R���X�g���N�^
GameObject::GameObject()
{
	m_isActive = true; // �A�N�e�B�u�ŏ�����
}

// �f�X�g���N�^
GameObject::~GameObject()
{

}

Transform GameObject::GetTrans() const
{
	return m_transform;
}

void GameObject::SetTransform(Transform trans)
{
	m_transform = trans;
}