#pragma once
#include "DxLib.h"

class Camera
{
private:
	VECTOR m_camPos;		// �J������Pos
	VECTOR m_camTraget;		// �����_


public: // �R���X�g���N�^
	Camera();
	virtual ~Camera();

	Camera(const Camera&) = delete;
	void operator=(const Camera&) = delete;

public: // �X�V
	void Update();



};