//==============================================================
//���@�ɒǏ]����J����
//==============================================================
#pragma once

#include "Camera.h"

class Follow : public Camera
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;

	Vector3 m_target_pos;//�Ǐ]�Ώۂ̍��W
	float m_target_angle;//�Ǐ]�Ώۂ̉�]�p



public:
	static const float CAMERA_DISTANCE;//�Ǐ]�ΏۂƂ̋���

	Follow(int outputWidth, int outputHeight);
	~Follow();

	void Update() override;


	void SetTargetPos(const Vector3& target_pos);	//�Ǐ]�Ώۂ̍��W���擾
	void SettargetAngle(float target_angle);		//�Ǐ]�Ώۂ̉�]�p���擾

};