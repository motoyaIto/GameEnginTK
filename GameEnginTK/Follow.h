//==============================================================
//自機に追従するカメラ
//==============================================================
#pragma once

#include <windows.h>
#include <Keyboard.h>
#include "Camera.h"

class Follow : public Camera
{
protected:
	Vector3 m_target_pos;//追従対象の座標
	float m_target_angle;//追従対象の回転角

	DirectX::Keyboard* m_keyboard;								//キーボード
	DirectX::Keyboard::KeyboardStateTracker m_keyboadTraker;	//キーボードトラッカー
	bool cameraMode;

public:
	static const float CAMERA_DISTANCE;//追従対象との距離

	Follow(int outputWidth, int outputHeight);
	~Follow();

	void Update() override;


	void SetTargetPos(const Vector3& target_pos);	//追従対象の座標を取得
	void SettargetAngle(float target_angle);		//追従対象の回転角を取得
	void setKeyboard(DirectX::Keyboard* keyboard);	//キーボードを取得

};