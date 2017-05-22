//==============================================================
//���@�ɒǏ]����J����
//==============================================================
#pragma once

#include <windows.h>
#include <Keyboard.h>
#include "Camera.h"

class Follow : public Camera
{
protected:
	Vector3 m_target_pos;//�Ǐ]�Ώۂ̍��W
	float m_target_angle;//�Ǐ]�Ώۂ̉�]�p

	DirectX::Keyboard* m_keyboard;								//�L�[�{�[�h
	DirectX::Keyboard::KeyboardStateTracker m_keyboadTraker;	//�L�[�{�[�h�g���b�J�[
	bool cameraMode;

public:
	static const float CAMERA_DISTANCE;//�Ǐ]�ΏۂƂ̋���

	Follow(int outputWidth, int outputHeight);
	~Follow();

	void Update() override;


	void SetTargetPos(const Vector3& target_pos);	//�Ǐ]�Ώۂ̍��W���擾
	void SettargetAngle(float target_angle);		//�Ǐ]�Ώۂ̉�]�p���擾
	void setKeyboard(DirectX::Keyboard* keyboard);	//�L�[�{�[�h���擾

};