#include "Transform.h"

Transform::Transform()
{ 
	// �����l�F���_�E��]�Ȃ��E���{�X�P�[��
	m_trans = VGet(0.0f, 0.0f, 0.0f);
	m_rot   = VGet(0.0f, 0.0f, 0.0f);
	m_scale = VGet(1.0f, 1.0f, 1.0f);

	// �e�s���P�ʍs��ŏ�����
	m_matTrans	= MGetIdent();
	m_matRot	= MGetIdent();
	m_matScale	= MGetIdent();
	m_worldMat	= MGetIdent();
}

Transform::Transform(VECTOR trans, VECTOR rot, VECTOR scale)
	: m_trans(trans), m_rot(rot), m_scale(scale)
{
	// �e�s���P�ʍs��ŏ�����
	m_matTrans = MGetIdent();
	m_matRot = MGetIdent();
	m_matScale = MGetIdent();
	m_worldMat = MGetIdent();
}

Transform::~Transform()
{ }

// ���[�J�����W���烏�[���h�s����쐬
void Transform::LocalToWorld()
{
	UpdateMatrix();
}

// ���[�J���s����X�V�i�X�P�[������]�����s�ړ��j
void Transform::UpdateMatrix()
{
	m_matScale = MGetScale(m_scale); // �X�P�[��

	// DxLib� (X �� Y �� Z)
	MATRIX m_rotX = MGetRotX(m_rot.x);
	MATRIX m_rotY = MGetRotY(m_rot.y);
	MATRIX m_rotZ = MGetRotZ(m_rot.z);

	// �s�񍇐� (X��Y��Z �̏��œK�p)
	m_matRot = MMult(MMult(m_rotX, m_rotY), m_rotZ);

	m_matTrans = MGetTranslate(m_trans);

	// �X�P�[�� �� ��] �� �ړ� �̏��ɓK�p
	m_worldMat = MMult(MMult(m_matScale, m_matRot), m_matTrans);
}

// ���[���h���W��Ԃ�
VECTOR Transform::TransformPoint(const VECTOR& localPos)
{
	return VTransform(localPos, m_worldMat);
}