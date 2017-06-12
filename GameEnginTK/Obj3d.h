//==============================================================
//3Dオブジェクトのクラス
//==============================================================
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>

#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

class Obj3d
{
protected:
	using ID3D11Device = Microsoft::WRL::ComPtr<ID3D11Device>;
	using ID3D11DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;

	//静的メンバ変数
public:
	//静的メンバ変数の初期化
	static void InitializeStatic(static ID3D11Device d3dDevice
								,static ID3D11DeviceContext d3dContext
								,static Camera* camera);
private:
	//デバイス
	static ID3D11Device				m_d3dDevice;
	//デバイスコンテキスト
	static ID3D11DeviceContext		m_d3dContext;
	//カメラ
	static Camera* m_Camera;
	//汎用描画ステート
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//エフェクトファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;


private:
	//3Dモデル
	std::unique_ptr<DirectX::Model> m_model;
	//スケーリング(XYZ)
	Vector3 m_scale;

	//回転角(XYZ)
	Vector3 m_rotation;

	//回転角(クオータニオン)
	DirectX::SimpleMath::Quaternion m_rotationQ;

	//平行移動(XYZ)
	Vector3 m_translation;

	//ワールド行列
	Matrix m_world;
	
	//親のワールド行列のポインタ
	Obj3d* m_parent;

	//クォータニオン使用フラグ
	bool m_UseQuaternion;
public:
	Obj3d();

	void Update();
	void Draw();

	//モデルの読み込み
	void LoadModel(const wchar_t* fileName);

	
	//setter
	//スケーリング(XYZ)
	void SetScale(const Vector3& scale) { m_scale = scale; }

	//回転角(XYZ)
	void SetRotation(const Vector3& rotation) { m_rotation = rotation; m_UseQuaternion = false; }
	//回転角(クォータニオン)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotationQ) { m_rotationQ = rotationQ; m_UseQuaternion = true; }

	//平行移動(XYZ)
	void SetTranslation(const Vector3& translation) { m_translation = translation; }

	//親の3Dオブジェクトのポインタ
	void SetParent(Obj3d* parent) { m_parent = parent; }


	//getter
	//スケーリング(XYZ)
	Vector3 GetScale() { return m_scale; }
	//回転角(XYZ)
	Vector3 GetRotation() { return m_rotation; }

	//平行移動(XYZ)
	Vector3 GetTranslation() { return m_translation; }

	//ワールド行列
	Matrix GetWorld() { return m_world; }

	//親の3Dオブジェクトポインタ
	Obj3d* GetParent() { return m_parent; }

};