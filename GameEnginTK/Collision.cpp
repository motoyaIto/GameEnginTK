//==============================================================
//�Փ˔���
//==============================================================
#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
//----------------------------------------------------------------------
//���Ƌ��̂����蔻��
//return :�������Ă���(true)���Ȃ�(false)
bool ChecksSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//A��B�̒��S���W�̍����v�Z����
	Vector3 sub = sphereB.Center - sphereA.Center;

	//�����̓��
	float distanceSquare;

	//�O�����̒藝�ŋ������Z�o
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//���a�̓��
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	//���������a�̘a���傫����Γ������Ă��Ȃ�
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}