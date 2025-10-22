#pragma once
#include "DxLib.h"

class Transform
{
private:
	VECTOR m_trans;		// 座標
	VECTOR m_rot;		// 回転
	VECTOR m_scale;		// スケール

	MATRIX m_matTrans;	// 座標行列
	MATRIX m_matRot;	// 回転行列
	MATRIX m_matScale;	// スケール行列
	MATRIX m_worldMat;	// ローカル→ワールド行列（合成結果）

public: // コンストラクタ等
	Transform();
	Transform(VECTOR trans, VECTOR rot, VECTOR scale);
	virtual ~Transform();

public: // ゲッター/セッター 
	VECTOR GetTrans() const { return m_trans; }
	VECTOR GetRot() const { return m_rot; }
	VECTOR GetScale() const { return m_scale; }
	void SetTrans(VECTOR trans) { m_trans = trans; }
	void SetRot(VECTOR rot) { m_rot = rot; }
	void SetScale(VECTOR scale) { m_scale = scale; }

private: // 変換
	void UpdateMatrix(); // ローカル行列を更新（スケール→回転→平行移動）

public: // 変換
	void LocalToWorld(); // ローカル座標からワールド行列を作成

	VECTOR TransformPoint(const VECTOR& localPos); // ワールド座標を返す
}; 