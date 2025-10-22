#pragma once
#include "DxLib.h"

class Camera
{
private:
	VECTOR m_camPos;		// カメラのPos
	VECTOR m_camTraget;		// 注視点


public: // コンストラクタ
	Camera();
	virtual ~Camera();

	Camera(const Camera&) = delete;
	void operator=(const Camera&) = delete;

public: // 更新
	void Update();



};