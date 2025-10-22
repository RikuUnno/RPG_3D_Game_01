#pragma once
#include "DxLib.h"

class Transform
{
private:
	VECTOR m_trans;		// ���W
	VECTOR m_rot;		// ��]
	VECTOR m_scale;		// �X�P�[��

	MATRIX m_matTrans;	// ���W�s��
	MATRIX m_matRot;	// ��]�s��
	MATRIX m_matScale;	// �X�P�[���s��
	MATRIX m_worldMat;	// ���[�J�������[���h�s��i�������ʁj

public: // �R���X�g���N�^��
	Transform();
	Transform(VECTOR trans, VECTOR rot, VECTOR scale);
	virtual ~Transform();

public: // �Q�b�^�[/�Z�b�^�[ 
	VECTOR GetTrans() const { return m_trans; }
	VECTOR GetRot() const { return m_rot; }
	VECTOR GetScale() const { return m_scale; }
	void SetTrans(VECTOR trans) { m_trans = trans; }
	void SetRot(VECTOR rot) { m_rot = rot; }
	void SetScale(VECTOR scale) { m_scale = scale; }

private: // �ϊ�
	void UpdateMatrix(); // ���[�J���s����X�V�i�X�P�[������]�����s�ړ��j

public: // �ϊ�
	void LocalToWorld(); // ���[�J�����W���烏�[���h�s����쐬

	VECTOR TransformPoint(const VECTOR& localPos); // ���[���h���W��Ԃ�
}; 