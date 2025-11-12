#include "BoxCollider.h"
#include "ColliderType.h"
#include <variant>

// コンストラクタ
BoxCollider::BoxCollider(Transform transform, ColliderManager* manager)
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
		}(), manager, transform)
{
	SetAABB(); // 回転を考慮したAABB
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
			other.gameObject.GetTrans() // Transformをコピー
			)
{
	SetAABB(); // AABBを再計算

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

}

// Transform基準のコライダーサイズ設定
void BoxCollider::SetTrans()
{

}

// AABBの設定
void BoxCollider::SetAABB()
{
	const BoxType& b = std::get<BoxType>(m_data);

	VECTOR center = VScale(VAdd(b.min, b.max), 0.5f);
	VECTOR halfSize = VScale(VSub(b.max, b.min), 0.5f);

	VECTOR local[8] = {
		VGet(-halfSize.x, -halfSize.y, -halfSize.z),
		VGet(halfSize.x, -halfSize.y, -halfSize.z),
		VGet(halfSize.x,  halfSize.y, -halfSize.z),
		VGet(-halfSize.x,  halfSize.y, -halfSize.z),
		VGet(-halfSize.x, -halfSize.y,  halfSize.z),
		VGet(halfSize.x, -halfSize.y,  halfSize.z),
		VGet(halfSize.x,  halfSize.y,  halfSize.z),
		VGet(-halfSize.x,  halfSize.y,  halfSize.z)
	};

	VECTOR worldMin = VGet(FLT_MAX, FLT_MAX, FLT_MAX);
	VECTOR worldMax = VGet(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int i = 0; i < 8; ++i)
	{
		VECTOR w = VAdd(VTransform(local[i], b.rot), center);
		worldMin.x = fminf(worldMin.x, w.x);
		worldMin.y = fminf(worldMin.y, w.y);
		worldMin.z = fminf(worldMin.z, w.z);
		worldMax.x = fmaxf(worldMax.x, w.x);
		worldMax.y = fmaxf(worldMax.y, w.y);
		worldMax.z = fmaxf(worldMax.z, w.z);
	}

	aabb.min = worldMin;
	aabb.max = worldMax;
}

