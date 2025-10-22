#pragma once
#include "Collider.h"
#include "DxLib.h"

class ColliderManager;

class BoxCollider
	: public Collider
{
private:

public: // �R���C�_�[�֌W
	BoxCollider(VECTOR min, VECTOR max, ColliderManager* manager, bool isActive);
	virtual ~BoxCollider();
	BoxCollider(const BoxCollider& other);

public:
	void Update() override; // �i�s

private: // Transform��̃R���C�_�[�T�C�Y�ݒ�
	void SetTrans() override;

public: // �Q�b�^�[�Z�b�^�[
	const BoxType* GetBox() const override { return std::get_if<BoxType>(&m_data); } // BoxType�̃Q�b�^�[

public: // �����蔻��֌W
	void SetAABB() override;
};