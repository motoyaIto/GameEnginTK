//==============================================================
//3Dオブジェクトのクラス
//==============================================================
#include "Obj3d.h"

using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//静的メンバ変数の実体
//デバイス
ComPtr<ID3D11Device>            Obj3d::m_d3dDevice;
//デバイスコンテキスト
ComPtr<ID3D11DeviceContext>    Obj3d::m_d3dContext;
//カメラ
Camera* Obj3d::m_Camera;
//汎用描画ステート
unique_ptr<CommonStates> Obj3d::m_states;
//エフェクトファクトリ
unique_ptr<EffectFactory> Obj3d::m_factory;



void Obj3d::InitializeStatic(ID3D11Device d3dDevice, ID3D11DeviceContext d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	//汎用描画ステート
	m_states = make_unique<CommonStates>(m_d3dDevice.Get());
	//エフェクトファクトリを作成
	m_factory = make_unique<EffectFactory>(m_d3dDevice.Get());
	//テクスチャの読み込みパス設定
	m_factory->SetDirectory(L"Resources");
}

//---------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------
Obj3d::Obj3d()
	: m_scale(1, 1, 1)
	, m_rotation(Vector3::Zero)
	, m_translation(Vector3::Zero)
	, m_parent(nullptr)
	,m_UseQuaternion(false)
{

}

//---------------------------------------------------------------
//アップデート
//---------------------------------------------------------------
void Obj3d::Update()
{
	//行列の計算=======================================================
	//サイズ
	Matrix scalemat = Matrix::CreateScale(m_scale);

	Matrix rotmat;
	//回転
	if (m_UseQuaternion)
	{//クォータニオン
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{//オイラー角
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	//平行行列
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//ワールド行列を計算する
	m_world = scalemat * rotmat * transmat;

	if (m_parent)
	{
		//親の行列掛ける
		m_world *= m_parent->m_world;
	}
}

//---------------------------------------------------------------
//描画
//---------------------------------------------------------------
void Obj3d::Draw()
{
	assert(m_Camera);

	if (m_model)
	{
		//3Dモデルの描画
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjMatrix());
	}
}
//---------------------------------------------------------------
//モデルの読み込み
//---------------------------------------------------------------
void Obj3d::LoadModel(const wchar_t * fileName)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

