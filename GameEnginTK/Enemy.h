//==============================================================
//Player�̃N���X
//==============================================================
#pragma once

#include<d3d11_1.h>
#include <Keyboard.h>
#include <SimpleMath.h>
#include <vector>
#include "Obj3d.h"

class Camera;


class Enemy
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;	

	DirectX::Keyboard* m_keyboard;//�L�[�{�[�h
	std::vector<Obj3d> m_objEnemy;

	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// �T�C���p�̈����ƂȂ�p�x
	float m_sinAngle;

	// �^�C�}�[
	int m_Timer;
	// �ڕW�̊p�x
	float m_DistAngle;
public:	
	enum ENEMY_PARTS
	{
		ENEMY_PARTS_TANK,
		ENEMY_PARTS_BODE,
		ENEMY_PARTS_RIGHTARM,
		ENEMY_PARTS_LEFTARM,
		ENEMY_PARTS_HED,

		PLAYER_PARTS_NUM
	};

	Enemy(DirectX::Keyboard* keyboard);
	~Enemy();
	void Initialize();
	void Update();
	void Calc();
	void Draw();

	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetTrans();
	// ��]���擾
	const DirectX::SimpleMath::Vector3& GetRot();
	// ���W��ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// ��]��ݒ�
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ���[���h�s����擾
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
};