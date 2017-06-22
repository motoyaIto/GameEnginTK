#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//=========================================================
//�����蔻��
//=========================================================
//---------------------------------------------------------
//�e�q�֌W������
//---------------------------------------------------------
void CollisionNode::SetParent(Obj3d * parent)
{
	m_obj.SetParent(parent);
}






//=========================================================
//���̂����蔻��
//=========================================================
//---------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------
SoherNode::SoherNode()
	:m_LocalRadius(1.0f)
{
}

//---------------------------------------------------------
//������
//---------------------------------------------------------
void SoherNode::Initialize()
{
	//�f�o�b�N�\���p���f����ǂݍ���
	m_obj.LoadModel(L"Resources//soherNode.cmo");
}

//---------------------------------------------------------
//�X�V
//---------------------------------------------------------
void SoherNode::Update()
{
	m_obj.SetTranslation(m_trans);
	m_obj.SetScale(SimpleMath::Vector3(m_LocalRadius));

	m_obj.Update();

	{//���[���h���W�ł̂����蔻�苅���v�Z����
		//�v�Z�ς݂̃��[���h�s����擾
		Matrix worldm = m_obj.GetWorld();

		//���f�����W�n�ł̒��S�_
		SimpleMath::Vector3 center(0, 0, 0);
		//���f�����W�n�ł̉E�[
		SimpleMath::Vector3 right(1, 0, 0);

		//���[���h���W�ɕϊ�
		center = SimpleMath::Vector3();

		center = SimpleMath::Vector3::Transform(center, worldm);

		Center = center;
	}
}

//---------------------------------------------------------
//�`��
//---------------------------------------------------------
void SoherNode::Draw()
{
	m_obj.Draw();
}

