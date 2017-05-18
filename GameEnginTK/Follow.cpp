//==============================================================
//自機に追従するカメラ
//==============================================================
#include "Follow.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//静的メンバクラスの初期化
const float Follow::CAMERA_DISTANCE = 5.0f;

//---------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------
Follow::Follow(int outputWidth, int outputHeight)
	: Camera(outputWidth, outputHeight)

	, m_target_pos(Vector3::Zero), m_target_angle(0.0f)
{

}

//---------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------
Follow::~Follow()
{
}

//---------------------------------------------------------------
//アップデート
//---------------------------------------------------------------
void Follow::Update()
{
	Vector3 eyepos, refpos;//視点, 参照点

	refpos = m_target_pos + Vector3(0, 2.0f, 0);//自機の2m上を参照する
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);//参照点と視点の差分ベクトル

	Matrix rotmat = Matrix::CreateRotationY(m_target_angle);//自機の後ろに回り込むための回転行列
	cameraV = Vector3::TransformNormal(cameraV, rotmat);//差分テクトルを回転させる

	eyepos = refpos + cameraV;//視点を計算

	Camera::SetEyePos(eyepos);
	Camera::SetRefPos(refpos);

	Camera::Update();//基底クラスの更新
}

//---------------------------------------------------------------
//追従対象の座標を取得
//---------------------------------------------------------------
void Follow::SetTargetPos(const Vector3 & target_pos)
{
	m_target_pos = target_pos;
}

//---------------------------------------------------------------
//追従対象の回転角を取得
//---------------------------------------------------------------
void Follow::SettargetAngle(float target_angle)
{
	m_target_angle = target_angle;
}
