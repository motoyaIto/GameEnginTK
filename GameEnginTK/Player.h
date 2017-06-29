//==============================================================
//Player�̃N���X
//==============================================================
#pragma once

#include<d3d11_1.h>
#include <Keyboard.h>


#include <SimpleMath.h>
#include "Obj3d.h"

#include "CollisionNode.h"

class Camera;


class Player
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

	DirectX::Keyboard* m_keyboard;//�L�[�{�[�h
	DirectX::Keyboard::KeyboardStateTracker m_keyboadTraker;	//�L�[�{�[�h�g���b�J�[
	std::vector<Obj3d> m_objPlayer;
	//�T�C���p
	float m_sinAngle;
	DirectX::SimpleMath::Vector3 m_BulletVel;

	bool m_risetFlag;

	//�e�ۗp�̂����蔻��
	SoherNode m_collisiorNodeBullet;
public:
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_TANK,
		PLAYER_PARTS_BODE,
		PLAYER_PARTS_RIGHTARM,
		PLAYER_PARTS_LEFTARM,
		PLAYER_PARTS_HED,

		PLAYER_PARTS_NUM
	};







	Player();

	void Initialize(DirectX::Keyboard* keyboard);
	void Update();
	void Draw(bool debug);

	Vector3 GetTranslation();
	Vector3 GetRotation();

	//�e�۔���
	void FireBull();
	//�e�ۂ��đ��U(���Z�b�g)
	void RsetFireBull();

	void Calc();

	const SoherNode& GetCollisionNodeBullet() { return m_collisiorNodeBullet; }
};