//============================================================================
//�����蔻��m�[�h
//============================================================================
#pragma once
#include "Collision.h"
#include "Obj3d.h"

//----------------------------------------------------------------------------
//�����蔻����N���X
//----------------------------------------------------------------------------
class CollisionNode
{
protected:
	using Vector3 = DirectX::SimpleMath::Vector3;
public:
	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Draw() = 0;

	//�e�q�֌W
	void SetParent(Obj3d* parent);
	void SetTrans(Vector3& trans) { m_trans = trans; }
protected:
	//�f�o�b�N�\���p�I�u�W�F�N�g
	Obj3d m_obj;

	//�e����̃I�t�Z�b�g
	Vector3 m_trans;
};

//----------------------------------------------------------------------------
//���̂����蔻��
//----------------------------------------------------------------------------
class SoherNode : public CollisionNode, public Sphere
{
public:
	SoherNode();

	void Initialize();//������
	void Update();//�X�V
	void Draw();//�`��

	void setLocalRadius(float Radius) { m_LocalRadius = Radius; }
private:
	//���[�J�����a
	float m_LocalRadius;
};