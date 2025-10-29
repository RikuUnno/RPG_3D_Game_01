#include "GameObject.h"
#include "DxLib.h"

// コンストラクタ
GameObject::GameObject()
{
	m_isActive = true; // アクティブで初期化
}

// デストラクタ
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