#pragma once
#include "DxLib.h"

class Camera
{
private:
	VECTOR m_camPos;

public:
	Camera();

	virtual ~Camera();

	Camera(const Camera&) = delete;
	void operator=(const Camera&) = delete;


};