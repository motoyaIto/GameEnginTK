//==============================================================
//衝突判定
//==============================================================
#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
//----------------------------------------------------------------------
//球と球のあたり判定
//return :当たっている(true)いない(false)
bool ChecksSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//AとBの中心座標の差を計算する
	Vector3 sub = sphereB.Center - sphereA.Center;

	//距離の二乗
	float distanceSquare;

	//三平方の定理で距離を算出
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//半径の二乗
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	//距離が半径の和より大きければ当たっていない
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}