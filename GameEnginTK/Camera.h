//==============================================================
//�J�����p�N���X
//==============================================================
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
private:
	using Matrix = DirectX::SimpleMath::Matrix;
	using Vector3 = DirectX::SimpleMath::Vector3;

protected:
	//�r���[�s��-------------------------------------
	Matrix m_view;

	Vector3 m_eyepos;	//�ǂ����猩�邩(���_)
	Vector3 m_refpos;	//�ǂ�������̂�(���ړ_/�Q�Ɠ_)
	Vector3 m_upvec;	//�ǂ��炪��ʏ������(������x�N�g��)
	

	//�v���W�F�N�V�����s��----------------------------
	Matrix m_proj;

	float m_fovY;		//������������p
	float m_aspect;		//�A�X�y�N�g��(���E�c�̔䗦)
	float m_nearclip;	//��O�̕\�����E����
	float m_farclip;	//���̕\�����E����

public:
	Camera(int outputWidth, int outputHeight);
	virtual ~Camera();

	virtual void Update();

	const Matrix& GetViewMatrix();//�r���[�s��̎擾
	const Matrix& GetProjMatrix();//�v���W�F�N�V�����s��̎擾

	void SetEyePos(const Vector3& eyepos);		//���_���擾
	void SetRefPos(const Vector3& refpos);		//���ړ_���擾
	void SetUpvec(const Vector3& upvec);		//������x�N�g�����擾
	void SetFovY(float fovY);			//������������p���擾
	void SetAspect(float aspect);		//�A�X�y�N�g����擾
	void SetNearclip(float nearclip);	//��O�̕\�����E�������擾
	void SetFarclip(float farclip);		//���̕\�����E�������擾
};
