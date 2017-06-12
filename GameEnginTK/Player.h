//==============================================================
//Playerのクラス
//==============================================================
#pragma once

#include<d3d11_1.h>
#include <Keyboard.h>


#include <SimpleMath.h>
#include "Obj3d.h"

class Camera;


class Player
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

	DirectX::Keyboard* m_keyboard;//キーボード
	DirectX::Keyboard::KeyboardStateTracker m_keyboadTraker;	//キーボードトラッカー
	std::vector<Obj3d> m_objPlayer;
	//サイン用
	float m_sinAngle;
	DirectX::SimpleMath::Vector3 m_BulletVel;

	bool m_risetFlag;
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
	void Draw();

	Vector3 GetTranslation();
	Vector3 GetRotation();

	//弾丸発射
	void FireBull();
	//弾丸を再装填(リセット)
	void RsetFireBull();

	void Calc();
};