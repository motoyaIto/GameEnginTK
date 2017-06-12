//==============================================================
//3D�I�u�W�F�N�g�̃N���X
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

	//�ÓI�����o�ϐ�
public:
	//�ÓI�����o�ϐ��̏�����
	static void InitializeStatic(static ID3D11Device d3dDevice
								,static ID3D11DeviceContext d3dContext
								,static Camera* camera);
private:
	//�f�o�C�X
	static ID3D11Device				m_d3dDevice;
	//�f�o�C�X�R���e�L�X�g
	static ID3D11DeviceContext		m_d3dContext;
	//�J����
	static Camera* m_Camera;
	//�ėp�`��X�e�[�g
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//�G�t�F�N�g�t�@�N�g��
	static std::unique_ptr<DirectX::EffectFactory> m_factory;


private:
	//3D���f��
	std::unique_ptr<DirectX::Model> m_model;
	//�X�P�[�����O(XYZ)
	Vector3 m_scale;

	//��]�p(XYZ)
	Vector3 m_rotation;

	//��]�p(�N�I�[�^�j�I��)
	DirectX::SimpleMath::Quaternion m_rotationQ;

	//���s�ړ�(XYZ)
	Vector3 m_translation;

	//���[���h�s��
	Matrix m_world;
	
	//�e�̃��[���h�s��̃|�C���^
	Obj3d* m_parent;

	//�N�H�[�^�j�I���g�p�t���O
	bool m_UseQuaternion;
public:
	Obj3d();

	void Update();
	void Draw();

	//���f���̓ǂݍ���
	void LoadModel(const wchar_t* fileName);

	
	//setter
	//�X�P�[�����O(XYZ)
	void SetScale(const Vector3& scale) { m_scale = scale; }

	//��]�p(XYZ)
	void SetRotation(const Vector3& rotation) { m_rotation = rotation; m_UseQuaternion = false; }
	//��]�p(�N�H�[�^�j�I��)
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotationQ) { m_rotationQ = rotationQ; m_UseQuaternion = true; }

	//���s�ړ�(XYZ)
	void SetTranslation(const Vector3& translation) { m_translation = translation; }

	//�e��3D�I�u�W�F�N�g�̃|�C���^
	void SetParent(Obj3d* parent) { m_parent = parent; }


	//getter
	//�X�P�[�����O(XYZ)
	Vector3 GetScale() { return m_scale; }
	//��]�p(XYZ)
	Vector3 GetRotation() { return m_rotation; }

	//���s�ړ�(XYZ)
	Vector3 GetTranslation() { return m_translation; }

	//���[���h�s��
	Matrix GetWorld() { return m_world; }

	//�e��3D�I�u�W�F�N�g�|�C���^
	Obj3d* GetParent() { return m_parent; }

};