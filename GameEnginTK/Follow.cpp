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

	, m_keyboard(nullptr), m_isFPS(false)
	, m_player(nullptr)
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
	//キーボードの状態を取得
	Keyboard::State keyboardstate = m_keyboard->GetState();
	m_keyboadTraker.Update(keyboardstate);

	//cキーを押すことにFPS/TPSを切り替え
	if (m_keyboadTraker.IsKeyPressed(Keyboard::Keys::F1))
	{
		m_isFPS = !m_isFPS;

		if (m_isFPS)
		{

		}
	}

	if (m_player)
	{
		//自機の追従
		this->SetTargetPos(m_player->GetTranslation());
		this->SettargetAngle(m_player->GetRotation().y);
	}

	Vector3 eyepos, refpos;//視点, 参照点

	if (m_isFPS)
	{
		//FPS-------------------------------------------------------------------------------
		Vector3 position;//視点, 参照点

		position = m_target_pos + Vector3(0, 1.0f, 0);
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);//参照点と視点の差分ベクトル

		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);//自機の後ろに回り込むための回転行列
		cameraV = Vector3::TransformNormal(cameraV, rotmat);//差分テクトルを回転させる

		eyepos = position + cameraV * 0.1f;//視点を計算

		refpos = position + cameraV;
	
	}
	else
	{
		//TPS----------------------------------------------------------------------------------
		refpos = m_target_pos + Vector3(0, 2.0f, 0);//自機の2m上を参照する
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);//参照点と視点の差分ベクトル

		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);//自機の後ろに回り込むための回転行列
		cameraV = Vector3::TransformNormal(cameraV, rotmat);//差分テクトルを回転させる

		eyepos = refpos + cameraV;//視点を計算

		//視点を現在位置から補間する
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
		//参照点を現在位置から補間する
		refpos = m_refpos + (refpos - m_refpos) * 0.2f;
	}

	SetEyePos(eyepos);
	SetRefPos(refpos);

	Camera::Update();
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

//---------------------------------------------------------------
//キーボードを取得
//---------------------------------------------------------------
void Follow::setKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
