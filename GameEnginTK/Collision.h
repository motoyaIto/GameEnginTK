//==============================================================
//�Փ˔���
//==============================================================
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

//��
class Sphere
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

public:
	Vector3 Center;//���S���W
	float Radius;//���a

	Sphere()
	{
		Radius = 1.0f;//���a1m
	}
};

class Segment
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

public:
	Vector3 Start;	//�n�_���W
	Vector3 End;	//�I�����W
};

bool ChecksSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
