#include "BoxCollider.h"
#include "ColliderType.h"
#include <variant>

// コンストラクタ
BoxCollider::BoxCollider(Transform transform, float boxSize, ColliderManager* manager)
	: Collider([transform]() {
	BoxType b;

	// min/maxから中心と半サイズを計算
	VECTOR halfSize = VScale(transform.GetScale(), 0.5f);
	VECTOR pos = transform.GetPos();
	b.min = VSub(pos, halfSize);
	b.max = VAdd(pos, halfSize);

	// 回転行列
	VECTOR rot = transform.GetRot();
	MATRIX rotX = MGetRotX(rot.x);
	MATRIX rotY = MGetRotY(rot.y);
	MATRIX rotZ = MGetRotZ(rot.z);
	b.rot = MMult(MMult(rotZ, rotX), rotY);

	return b;
		}(),
	manager,
	transform),
	m_originalSize(boxSize)
{
	SetOBB(); // 回転を考慮したAABB
}

// デストラクタ
BoxCollider::~BoxCollider()
{}

// コピコン
BoxCollider::BoxCollider(const BoxCollider& other)
	: Collider(
		[&other]() {
			BoxType b;
			b.min = other.GetBox()->min;
			b.max = other.GetBox()->max;
			return b;
		}(),
			other.m_manager,
			other.m_transform), // Transformをコピー
			m_originalSize(other.m_originalSize)
{
	SetOBB(); // AABBを再計算

#ifdef _DEBUG
	MessageBoxW(
		nullptr,
		L"BoxCollider コピーコンストラクタが呼ばれました。",
		L"通知",
		MB_OK | MB_ICONINFORMATION
	);
#endif
}

// Update
void BoxCollider::Update()
{
	SetTrans();
	SetOBB();   // OBB 計算
}

// Transform基準のコライダーサイズ設定
void BoxCollider::SetTrans()
{
	// ワールド行列まで更新
	m_transform.LocalToWorld();

	BoxType& box = std::get<BoxType>(m_data);

	// Transform の座標・回転・スケールを取得
	VECTOR pos = m_transform.GetPos();
	VECTOR rot = m_transform.GetRot();    // ラジアン
	VECTOR scale = m_transform.GetScale();

	// 回転行列を作成（X→Y→Z の順）
	MATRIX rotX = MGetRotX(rot.x);
	MATRIX rotY = MGetRotY(rot.y);
	MATRIX rotZ = MGetRotZ(rot.z);
	MATRIX rotMat = MMult(MMult(rotX, rotY), rotZ);

	// ラムダで VECTOR 同士の要素ごとのスケーリング
	auto VScaleV = [](const VECTOR& v1, const VECTOR& v2) -> VECTOR {
		return VGet(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
		};

	// originalSize を VECTOR に変換
	VECTOR originalVec = VGet(m_originalSize, m_originalSize, m_originalSize);

	// 半サイズをラムダで計算（スケール反映 + 半分）
	VECTOR halfSize = [&]() -> VECTOR {
		VECTOR scaled = VScaleV(originalVec, scale); // スケールを反映
		return VScale(scaled, 0.5f);                // 半分にする
		}();

	// Box の min/max を Transform 中心を基準に計算
	box.min = VSub(pos, halfSize);
	box.max = VAdd(pos, halfSize);

	// 回転行列を BoxType に保持（OBB 計算用）
	box.rot = rotMat;
}

// AABBの設定
void BoxCollider::SetOBB()
{
	const BoxType& b = std::get<BoxType>(m_data);

	// 中心と半サイズ
	VECTOR center = VScale(VAdd(b.min, b.max), 0.5f);
	VECTOR halfSize = VScale(VSub(b.max, b.min), 0.5f);

	// 回転行列から 3軸を取得
	// b.rot は 3x3 行列相当と仮定
	obb.center = center;
	obb.axes[0] = VNorm(VTransform(VGet(1, 0, 0), b.rot)); // X軸
	obb.axes[1] = VNorm(VTransform(VGet(0, 1, 0), b.rot)); // Y軸
	obb.axes[2] = VNorm(VTransform(VGet(0, 0, 1), b.rot)); // Z軸

	obb.halfLen[0] = halfSize.x;
	obb.halfLen[1] = halfSize.y;
	obb.halfLen[2] = halfSize.z;
}

// コライダーの可視化
void BoxCollider::DrawCollider() const
{
	const BoxType& b = std::get<BoxType>(m_data);

	// Box の中心
	VECTOR center = VScale(VAdd(b.min, b.max), 0.5f);

	// 8つの頂点（中心を原点にしたローカル座標）
	VECTOR local[8] = {
		VSub(VGet(b.min.x, b.min.y, b.min.z), center),
		VSub(VGet(b.max.x, b.min.y, b.min.z), center),
		VSub(VGet(b.max.x, b.max.y, b.min.z), center),
		VSub(VGet(b.min.x, b.max.y, b.min.z), center),
		VSub(VGet(b.min.x, b.min.y, b.max.z), center),
		VSub(VGet(b.max.x, b.min.y, b.max.z), center),
		VSub(VGet(b.max.x, b.max.y, b.max.z), center),
		VSub(VGet(b.min.x, b.max.y, b.max.z), center)
	};

	// 回転を適用
	VECTOR v[8];
	for (int i = 0; i < 8; ++i)
	{
		v[i] = VAdd(VTransform(local[i], b.rot), center);
	}

	int col = GetColor(0, 255, 0);

	// 前面（Z-）
	DrawTriangle3D(v[0], v[1], v[2], col, TRUE);
	DrawTriangle3D(v[0], v[2], v[3], col, TRUE);

	// 背面（Z+）
	DrawTriangle3D(v[4], v[6], v[5], col, TRUE);
	DrawTriangle3D(v[4], v[7], v[6], col, TRUE);

	// 左面（X-）
	DrawTriangle3D(v[0], v[3], v[7], col, TRUE);
	DrawTriangle3D(v[0], v[7], v[4], col, TRUE);

	// 右面（X+）
	DrawTriangle3D(v[1], v[5], v[6], col, TRUE);
	DrawTriangle3D(v[1], v[6], v[2], col, TRUE);

	// 上面（Y+）
	DrawTriangle3D(v[3], v[2], v[6], col, TRUE);
	DrawTriangle3D(v[3], v[6], v[7], col, TRUE);

	// 下面（Y-）
	DrawTriangle3D(v[0], v[4], v[5], col, TRUE);
	DrawTriangle3D(v[0], v[5], v[1], col, TRUE);
}
