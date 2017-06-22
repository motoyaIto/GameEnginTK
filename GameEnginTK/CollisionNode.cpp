#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//=========================================================
//あたり判定
//=========================================================
//---------------------------------------------------------
//親子関係を結ぶ
//---------------------------------------------------------
void CollisionNode::SetParent(Obj3d * parent)
{
	m_obj.SetParent(parent);
}






//=========================================================
//球のあたり判定
//=========================================================
//---------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------
SoherNode::SoherNode()
	:m_LocalRadius(1.0f)
{
}

//---------------------------------------------------------
//初期化
//---------------------------------------------------------
void SoherNode::Initialize()
{
	//デバック表示用モデルを読み込む
	m_obj.LoadModel(L"Resources//soherNode.cmo");
}

//---------------------------------------------------------
//更新
//---------------------------------------------------------
void SoherNode::Update()
{
	m_obj.SetTranslation(m_trans);
	m_obj.SetScale(SimpleMath::Vector3(m_LocalRadius));

	m_obj.Update();

	{//ワールド座標でのあたり判定球を計算する
		//計算済みのワールド行列を取得
		Matrix worldm = m_obj.GetWorld();

		//モデル座標系での中心点
		SimpleMath::Vector3 center(0, 0, 0);
		//モデル座標系での右端
		SimpleMath::Vector3 right(1, 0, 0);

		//ワールド座標に変換
		center = SimpleMath::Vector3();

		center = SimpleMath::Vector3::Transform(center, worldm);

		Center = center;
	}
}

//---------------------------------------------------------
//描画
//---------------------------------------------------------
void SoherNode::Draw()
{
	m_obj.Draw();
}

