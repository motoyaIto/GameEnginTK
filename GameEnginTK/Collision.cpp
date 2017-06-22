//==============================================================
//Õ“Ë”»’è
//==============================================================
#include "Collision.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
//----------------------------------------------------------------------
//‹…‚Æ‹…‚Ì‚ ‚½‚è”»’è
//return :“–‚½‚Á‚Ä‚¢‚é(true)‚¢‚È‚¢(false)
bool ChecksSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//A‚ÆB‚Ì’†SÀ•W‚Ì·‚ğŒvZ‚·‚é
	Vector3 sub = sphereB.Center - sphereA.Center;

	//‹——£‚Ì“ñæ
	float distanceSquare;

	//O•½•û‚Ì’è—‚Å‹——£‚ğZo
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//”¼Œa‚Ì“ñæ
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	//‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚Î“–‚½‚Á‚Ä‚¢‚È‚¢
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}