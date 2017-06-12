//==============================================================
//3D�I�u�W�F�N�g�̃N���X
//==============================================================
#include "Obj3d.h"

using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//�ÓI�����o�ϐ��̎���
//�f�o�C�X
ComPtr<ID3D11Device>            Obj3d::m_d3dDevice;
//�f�o�C�X�R���e�L�X�g
ComPtr<ID3D11DeviceContext>    Obj3d::m_d3dContext;
//�J����
Camera* Obj3d::m_Camera;
//�ėp�`��X�e�[�g
unique_ptr<CommonStates> Obj3d::m_states;
//�G�t�F�N�g�t�@�N�g��
unique_ptr<EffectFactory> Obj3d::m_factory;



void Obj3d::InitializeStatic(ID3D11Device d3dDevice, ID3D11DeviceContext d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	//�ėp�`��X�e�[�g
	m_states = make_unique<CommonStates>(m_d3dDevice.Get());
	//�G�t�F�N�g�t�@�N�g�����쐬
	m_factory = make_unique<EffectFactory>(m_d3dDevice.Get());
	//�e�N�X�`���̓ǂݍ��݃p�X�ݒ�
	m_factory->SetDirectory(L"Resources");
}

//---------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------
Obj3d::Obj3d()
	: m_scale(1, 1, 1)
	, m_rotation(Vector3::Zero)
	, m_translation(Vector3::Zero)
	, m_parent(nullptr)
	,m_UseQuaternion(false)
{

}

//---------------------------------------------------------------
//�A�b�v�f�[�g
//---------------------------------------------------------------
void Obj3d::Update()
{
	//�s��̌v�Z=======================================================
	//�T�C�Y
	Matrix scalemat = Matrix::CreateScale(m_scale);

	Matrix rotmat;
	//��]
	if (m_UseQuaternion)
	{//�N�H�[�^�j�I��
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{//�I�C���[�p
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	//���s�s��
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//���[���h�s����v�Z����
	m_world = scalemat * rotmat * transmat;

	if (m_parent)
	{
		//�e�̍s��|����
		m_world *= m_parent->m_world;
	}
}

//---------------------------------------------------------------
//�`��
//---------------------------------------------------------------
void Obj3d::Draw()
{
	assert(m_Camera);

	if (m_model)
	{
		//3D���f���̕`��
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjMatrix());
	}
}
//---------------------------------------------------------------
//���f���̓ǂݍ���
//---------------------------------------------------------------
void Obj3d::LoadModel(const wchar_t * fileName)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);
}

