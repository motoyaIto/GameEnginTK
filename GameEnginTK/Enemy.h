//==============================================================
//Playerのクラス
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

	DirectX::Keyboard* m_keyboard;//キーボード
	std::vector<Obj3d> m_objEnemy;

	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// サイン用の引数となる角度
	float m_sinAngle;

	// タイマー
	int m_Timer;
	// 目標の角度
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

	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetTrans();
	// 回転を取得
	const DirectX::SimpleMath::Vector3& GetRot();
	// 座標を設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// 回転を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ワールド行列を取得
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
};