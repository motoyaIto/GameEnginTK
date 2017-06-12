//==============================================================
//���@�ɒǏ]����J����
//==============================================================
#include "Follow.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�ÓI�����o�N���X�̏�����
const float Follow::CAMERA_DISTANCE = 5.0f;

//---------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------
Follow::Follow(int outputWidth, int outputHeight)
	: Camera(outputWidth, outputHeight)

	, m_target_pos(Vector3::Zero), m_target_angle(0.0f)

	, m_keyboard(nullptr), m_isFPS(false)
	, m_player(nullptr)
{

}

//---------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------
Follow::~Follow()
{
}

//---------------------------------------------------------------
//�A�b�v�f�[�g
//---------------------------------------------------------------
void Follow::Update()
{
	//�L�[�{�[�h�̏�Ԃ��擾
	Keyboard::State keyboardstate = m_keyboard->GetState();
	m_keyboadTraker.Update(keyboardstate);

	//c�L�[���������Ƃ�FPS/TPS��؂�ւ�
	if (m_keyboadTraker.IsKeyPressed(Keyboard::Keys::F1))
	{
		m_isFPS = !m_isFPS;

		if (m_isFPS)
		{

		}
	}

	if (m_player)
	{
		//���@�̒Ǐ]
		this->SetTargetPos(m_player->GetTranslation());
		this->SettargetAngle(m_player->GetRotation().y);
	}

	Vector3 eyepos, refpos;//���_, �Q�Ɠ_

	if (m_isFPS)
	{
		//FPS-------------------------------------------------------------------------------
		Vector3 position;//���_, �Q�Ɠ_

		position = m_target_pos + Vector3(0, 1.0f, 0);
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);//�Q�Ɠ_�Ǝ��_�̍����x�N�g��

		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);//���@�̌��ɉ�荞�ނ��߂̉�]�s��
		cameraV = Vector3::TransformNormal(cameraV, rotmat);//�����e�N�g������]������

		eyepos = position + cameraV * 0.1f;//���_���v�Z

		refpos = position + cameraV;
	
	}
	else
	{
		//TPS----------------------------------------------------------------------------------
		refpos = m_target_pos + Vector3(0, 2.0f, 0);//���@��2m����Q�Ƃ���
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);//�Q�Ɠ_�Ǝ��_�̍����x�N�g��

		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);//���@�̌��ɉ�荞�ނ��߂̉�]�s��
		cameraV = Vector3::TransformNormal(cameraV, rotmat);//�����e�N�g������]������

		eyepos = refpos + cameraV;//���_���v�Z

		//���_�����݈ʒu�����Ԃ���
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
		//�Q�Ɠ_�����݈ʒu�����Ԃ���
		refpos = m_refpos + (refpos - m_refpos) * 0.2f;
	}

	SetEyePos(eyepos);
	SetRefPos(refpos);

	Camera::Update();
}

//---------------------------------------------------------------
//�Ǐ]�Ώۂ̍��W���擾
//---------------------------------------------------------------
void Follow::SetTargetPos(const Vector3 & target_pos)
{
	m_target_pos = target_pos;
}

//---------------------------------------------------------------
//�Ǐ]�Ώۂ̉�]�p���擾
//---------------------------------------------------------------
void Follow::SettargetAngle(float target_angle)
{
	m_target_angle = target_angle;
}

//---------------------------------------------------------------
//�L�[�{�[�h���擾
//---------------------------------------------------------------
void Follow::setKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
