//==============================================================
//©‹@‚É’Ç]‚·‚éƒJƒƒ‰
//==============================================================
#pragma once

#include "Camera.h"

class Follow : public Camera
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;

	Vector3 m_target_pos;//’Ç]‘ÎÛ‚ÌÀ•W
	float m_target_angle;//’Ç]‘ÎÛ‚Ì‰ñ“]Šp



public:
	static const float CAMERA_DISTANCE;//’Ç]‘ÎÛ‚Æ‚Ì‹——£

	Follow(int outputWidth, int outputHeight);
	~Follow();

	void Update() override;


	void SetTargetPos(const Vector3& target_pos);	//’Ç]‘ÎÛ‚ÌÀ•W‚ğæ“¾
	void SettargetAngle(float target_angle);		//’Ç]‘ÎÛ‚Ì‰ñ“]Šp‚ğæ“¾

};