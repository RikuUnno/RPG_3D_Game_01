#include "SphereCollider.h"
#include "ColliderType.h"
#include <variant>

// コンストラクタ
SphereCollider::SphereCollider(Transform transform, float radius, ColliderManager* manager)
	: Collider([transform, radius]() {
			SphereType s;
			s.spherePos = transform.GetPos(); // Transformの座標
			s.radius = radius;
			return s;
		}(),
	manager,
	transform),
	m_originalRadius(radius)
{
	SetOBB(); // AABBの設定
}

// デストラクタ
SphereCollider::~SphereCollider()
{}

// コピコン
SphereCollider::SphereCollider(const SphereCollider& other)
	: Collider(
		[&other]() {
			SphereType s;
			s.spherePos = other.GetSphere()->spherePos;
			s.radius = other.GetSphere()->radius;
			return s;
		}(),
			other.m_manager,
			other.m_transform), // Transformをそのままコピー
			m_originalRadius(other.m_originalRadius)
{

	SetOBB(); // AABBの再設定

#ifdef _DEBUG // コピコンがよばれたときの処理（把握用）
	MessageBoxW(
		nullptr,
		L"SphereCollider コピーコンストラクタが呼ばれました。",
		L"通知",
		MB_OK | MB_ICONINFORMATION
	);
#endif // _DEBUG
}

// Update
void SphereCollider::Update()
{
	SetTrans(); // Transform基準のコライダーサイズ設定
	SetOBB(); // ワールド座標の AABB を更新
}

void SphereCollider::SetTrans()
{
	m_transform.LocalToWorld();

	SphereType& sph = std::get<SphereType>(m_data);

	VECTOR center = m_transform.GetPos();
	VECTOR scale = m_transform.GetScale();

	// X/Y/Z の平均スケールで radius を調整
	float scaleAvg = (scale.x + scale.y + scale.z) / 3.0f;
	sph.spherePos = center;
	sph.radius = m_originalRadius * scaleAvg;

	// 回転を取得（ラジアン）
	VECTOR rot = m_transform.GetRot();

	// 回転行列作成
	MATRIX rotX = MGetRotX(rot.x);
	MATRIX rotY = MGetRotY(rot.y);
	MATRIX rotZ = MGetRotZ(rot.z);
	MATRIX rotMat = MMult(MMult(rotX, rotY), rotZ);

	// 描画やOBB用に軸を計算
	sph.axisX = VTransform(VGet(1, 0, 0), rotMat);
	sph.axisY = VTransform(VGet(0, 1, 0), rotMat);
	sph.axisZ = VTransform(VGet(0, 0, 1), rotMat);
}

void SphereCollider::SetOBB()
{
	const SphereType& s = std::get<SphereType>(m_data);

	obb.center = s.spherePos;
	obb.axes[0] = s.axisX; // Transform の回転に対応
	obb.axes[1] = s.axisY;
	obb.axes[2] = s.axisZ;

	obb.halfLen[0] = s.radius;
	obb.halfLen[1] = s.radius;
	obb.halfLen[2] = s.radius;
}

// コライダーの可視化
void SphereCollider::DrawCollider() const
{
	const SphereType& SphePos = std::get<SphereType>(m_data);

	DrawSphere3D(SphePos.spherePos, SphePos.radius, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
}