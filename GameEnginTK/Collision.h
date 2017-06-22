//==============================================================
//衝突判定
//==============================================================
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

//球
class Sphere
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

public:
	Vector3 Center;//中心座標
	float Radius;//半径

	Sphere()
	{
		Radius = 1.0f;//半径1m
	}
};

class Segment
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

public:
	Vector3 Start;	//始点座標
	Vector3 End;	//終了座標
};

bool ChecksSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
