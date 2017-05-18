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
	Vector3 eyepos, refpos;//���_, �Q�Ɠ_

	refpos = m_target_pos + Vector3(0, 2.0f, 0);//���@��2m����Q�Ƃ���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);//�Q�Ɠ_�Ǝ��_�̍����x�N�g��

	Matrix rotmat = Matrix::CreateRotationY(m_target_angle);//���@�̌��ɉ�荞�ނ��߂̉�]�s��
	cameraV = Vector3::TransformNormal(cameraV, rotmat);//�����e�N�g������]������

	eyepos = refpos + cameraV;//���_���v�Z

	Camera::SetEyePos(eyepos);
	Camera::SetRefPos(refpos);

	Camera::Update();//���N���X�̍X�V
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
