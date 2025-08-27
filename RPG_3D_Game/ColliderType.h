#pragma once
#include "DxLib.h"

enum class ColliderType		// Collider�̕���
{
	Box,					// �{�b�N�X
	Sphere,					// ��
	Capsule					// �J�v�Z��
							// etc...
};

struct BoxType {            // AABB��Box
	VECTOR min;				// �ŏ����W
	VECTOR max;				// �ő���W
}typedef AABB;

struct SphereType           // ��    
{
	VECTOR spherePos;		// ���̒��S�_
	double radius;		// �~�̔��a
};

struct CapsuleType			// �J�v�Z��
{
	VECTOR posTop;		// �J�v�Z���̏�[
	VECTOR posBottom;		// �J�v�Z���̉��[
	double height;		// �J�v�Z���̍���
	double radius;		// �J�v�Z���̔��a
};