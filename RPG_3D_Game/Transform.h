#pragma once
#include "DxLib.h"
#include "Quaternion.h"

class Transform
{
	VECTOR m_localPos;	// 座標（ローカル）
	VECTOR m_roteision;	// 回転
	VECTOR m_scale;		// スケール
};