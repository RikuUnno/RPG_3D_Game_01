#pragma once
#include <vector>
#include <variant>
#include "Layer.h"
#include "Tag.h"
#include "ColliderType.h"

class ColliderManager; 

class Collider
{
protected: // �I�u�W�F�N�g�̏��
	bool m_isActive; // �I�u�W�F�N�g�i�R���C�_�[�j�̏��

protected: // �R���C�_�[�̎�ނɉ�����Pos�p
	ColliderType m_type;									// �R���C�_�[�̎��
	std::variant<BoxType, SphereType, CapsuleType> m_data;	// ��L�̕ϐ��ɉ������R���C�_�[��Pos

protected: // �ȈՓI�ȓ����蔻��p
	AABB aabb;	// �����蔻��p

protected: // �����蔻���̃C�x���g�`�F�b�N�p�ϐ�
	std::vector<Collider*>previousHitColliders; //�O�i�������̃t���[���j�̓�������Collider
	std::vector<Collider*>currentHitColliders;  //����(�������̃t���[��)�̓�������Collider

protected: // �R���C�_�[�̓o�^�p
	ColliderManager* m_manager; // �R���C�_�[�̓o�^��̃}�l�[�W���[

protected: // ���C���[/�}�X�N�����p
	Layer m_layer;			// ���g�̃��C���[
	Layer m_collisionMask;	// �Փ˔���
	Tag m_tag;				// Tag

public: // �R���X�g���N�^�]�X
	Collider(const std::variant<BoxType, SphereType, CapsuleType>& data, ColliderManager* manager, bool isActive);
	virtual ~Collider();

	Collider(const Collider&);			// �݌v���ɕς��邩��
	void operator=(const Collider&) = delete;	// �݌v���ɕς��邩��

public: // �i�s�p
	void Update();		// ��{�i�s�̊֐�
	void Activate();	// �A�N�e�B�u��
	void Deactivate();	// ��A�N�e�B�u��

public: // ���C���[/�}�X�N�����p�ϐ��̐ݒ�/�Đݒ�p
	virtual void SetLayer(Layer layer)	 { m_layer = layer; }								// ���C���[�̐ݒ�/�Đݒ�
	virtual void SetMask(uint32_t mask) { m_collisionMask = static_cast<Layer>(mask); }	// �}�X�N�̐ݒ�/�Đݒ�
	virtual void SetTag(Tag tag)		 { m_tag = tag; }									// �^�O�̐ݒ�/�Đݒ�

public: // Type�Q�b�^�[
	ColliderType GetType() const { return m_type; }

public: // Layer�Q�b�^�[
	Layer GetLayer() const { return m_layer; }
	Layer GetCollisionMask() const { return m_collisionMask; }

public: // Pos�Q�b�^�[
	virtual const BoxType* GetBox() const { return nullptr; }
	virtual const SphereType* GetSphere() const { return nullptr; }
	virtual const CapsuleType* GetCapsule() const { return nullptr; }

	const AABB* GetAABB() const { return &aabb; }

public: // ��Ԑݒ�
	void SetActiveCollider(bool active) { m_isActive = active; } // ��Ԃ̐ݒ�

public: // �����蔻��̉���
	virtual void SetAABB() = 0; // AABB�̐ݒ�i�����j

	// �C�x���g�`�F�b�N
	void EventCheck(std::vector<Collider*> &colliders);

	virtual void OnCollisionEnter(Collider* other) {};	// �ڐG��
	virtual void OnCollisionStay(Collider* other) {};	// �ڐG��
	virtual void OnCollisionExit(Collider* other) {};	// �ڐG��
};
