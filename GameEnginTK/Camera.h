//==============================================================
//カメラ用クラス
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
	//ビュー行列-------------------------------------
	Matrix m_view;

	Vector3 m_eyepos;	//どこから見るか(視点)
	Vector3 m_refpos;	//どこを見るのか(注目点/参照点)
	Vector3 m_upvec;	//どちらが画面上方向か(上方向ベクトル)
	

	//プロジェクション行列----------------------------
	Matrix m_proj;

	float m_fovY;		//垂直方向視野角
	float m_aspect;		//アスペクト比(横・縦の比率)
	float m_nearclip;	//手前の表示限界距離
	float m_farclip;	//奥の表示限界距離

public:
	Camera(int outputWidth, int outputHeight);
	virtual ~Camera();

	virtual void Update();

	const Matrix& GetViewMatrix();//ビュー行列の取得
	const Matrix& GetProjMatrix();//プロジェクション行列の取得

	void SetEyePos(const Vector3& eyepos);		//視点を取得
	void SetRefPos(const Vector3& refpos);		//注目点を取得
	void SetUpvec(const Vector3& upvec);		//上方向ベクトルを取得
	void SetFovY(float fovY);			//垂直方向視野角を取得
	void SetAspect(float aspect);		//アスペクト比を取得
	void SetNearclip(float nearclip);	//手前の表示限界距離を取得
	void SetFarclip(float farclip);		//奥の表示限界距離を取得
};
