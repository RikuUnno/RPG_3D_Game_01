#include "Transform.h"

Transform::Transform()
{ 
	// 初期値：原点・回転なし・等倍スケール
	m_trans = VGet(0.0f, 0.0f, 0.0f);
	m_rot   = VGet(0.0f, 0.0f, 0.0f);
	m_scale = VGet(1.0f, 1.0f, 1.0f);

	// 各行列を単位行列で初期化
	m_matTrans	= MGetIdent();
	m_matRot	= MGetIdent();
	m_matScale	= MGetIdent();
	m_worldMat	= MGetIdent();
}

Transform::Transform(VECTOR trans, VECTOR rot, VECTOR scale)
	: m_trans(trans), m_rot(rot), m_scale(scale)
{
	// 各行列を単位行列で初期化
	m_matTrans = MGetIdent();
	m_matRot = MGetIdent();
	m_matScale = MGetIdent();
	m_worldMat = MGetIdent();
}

Transform::~Transform()
{ }

// ローカル座標からワールド行列を作成
void Transform::LocalToWorld()
{
	UpdateMatrix();
}

// ローカル行列を更新（スケール→回転→平行移動）
void Transform::UpdateMatrix()
{
	m_matScale = MGetScale(m_scale); // スケール

	// DxLib基準 (X → Y → Z)
	MATRIX m_rotX = MGetRotX(m_rot.x);
	MATRIX m_rotY = MGetRotY(m_rot.y);
	MATRIX m_rotZ = MGetRotZ(m_rot.z);

	// 行列合成 (X→Y→Z の順で適用)
	m_matRot = MMult(MMult(m_rotX, m_rotY), m_rotZ);

	m_matTrans = MGetTranslate(m_trans);

	// スケール → 回転 → 移動 の順に適用
	m_worldMat = MMult(MMult(m_matScale, m_matRot), m_matTrans);
}

// ワールド座標を返す
VECTOR Transform::TransformPoint(const VECTOR& localPos)
{
	return VTransform(localPos, m_worldMat);
}