#pragma once
#include "DxLib.h"

enum class ColliderType		// Colliderの分別
{
	Box,					// ボックス
	Sphere,					// 球
	Capsule					// カプセル
							// etc...
};

struct BoxType {            // AABB兼Box
	VECTOR min;				// 最小座標
	VECTOR max;				// 最大座標
}typedef AABB;

struct SphereType           // 球    
{
	VECTOR spherePos;		// 球の中心点
	double radius;		// 円の半径
};

struct CapsuleType			// カプセル
{
	VECTOR posTop;		// カプセルの上端
	VECTOR posBottom;		// カプセルの下端
	double height;		// カプセルの高さ
	double radius;		// カプセルの半径
};