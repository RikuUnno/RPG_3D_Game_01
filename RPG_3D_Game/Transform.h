#pragma once
#include "DxLib.h"

class Transform
{
private:
	VECTOR m_pos;		// 座標
	VECTOR m_rot;		// 回転(ラジアン)
	VECTOR m_scale;		// スケール

	MATRIX m_matPos;	// 座標行列
	MATRIX m_matRot;	// 回転行列
	MATRIX m_matScale;	// スケール行列
	MATRIX m_worldMat;	// ローカル→ワールド行列（合成結果）

public: // コンストラクタ等
	Transform();
	Transform(VECTOR trans, VECTOR rot, VECTOR scale);
	virtual ~Transform();

public: // ゲッター/セッター 
	VECTOR GetPos() const { return m_pos; }
	VECTOR GetRot() const { return m_rot; }
	VECTOR GetScale() const { return m_scale; }
	void SetPos(VECTOR trans) { m_pos = trans; }
	void SetRot(VECTOR rotDeg) { m_rot = DegToRadV(rotDeg); } // 度数からラジアン
	void SetScale(VECTOR scale) { m_scale = scale; }

private: // 変換
	void UpdateMatrix(); // ローカル行列を更新（スケール→回転→平行移動）
public: // 更新とローカル→ワールドの関数
	void LocalToWorld(); // ローカル座標からワールド行列を作成
private:
	float DegToRad(float deg);
	VECTOR DegToRadV(const VECTOR& degV);
public: // ワールド座標を返す
	VECTOR TransformPoint(const VECTOR& localPos); // ワールド座標を返す
}; 