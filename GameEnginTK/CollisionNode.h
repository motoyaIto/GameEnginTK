//============================================================================
//当たり判定ノード
//============================================================================
#pragma once
#include "Collision.h"
#include "Obj3d.h"

//----------------------------------------------------------------------------
//あたり判定基底クラス
//----------------------------------------------------------------------------
class CollisionNode
{
protected:
	using Vector3 = DirectX::SimpleMath::Vector3;
public:
	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Draw() = 0;

	//親子関係
	void SetParent(Obj3d* parent);
	void SetTrans(Vector3& trans) { m_trans = trans; }
protected:
	//デバック表示用オブジェクト
	Obj3d m_obj;

	//親からのオフセット
	Vector3 m_trans;
};

//----------------------------------------------------------------------------
//球のあたり判定
//----------------------------------------------------------------------------
class SoherNode : public CollisionNode, public Sphere
{
public:
	SoherNode();

	void Initialize();//初期化
	void Update();//更新
	void Draw();//描画

	void setLocalRadius(float Radius) { m_LocalRadius = Radius; }
private:
	//ローカル半径
	float m_LocalRadius;
};