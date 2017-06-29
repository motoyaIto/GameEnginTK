//==============================================================
//Player�̃N���X
//==============================================================


#include "Enemy.h"
#include "Camera.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------
Enemy::Enemy(DirectX::Keyboard* keyboard)
{
	m_keyboard = keyboard;

	m_sinAngle = 0.0f;

	Initialize();
	
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	m_objEnemy.resize(PLAYER_PARTS_NUM);
	m_objEnemy[ENEMY_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_objEnemy[ENEMY_PARTS_BODE].LoadModel(L"Resources/bode.cmo");
	m_objEnemy[ENEMY_PARTS_RIGHTARM].LoadModel(L"Resources/rightArm.cmo");
	m_objEnemy[ENEMY_PARTS_LEFTARM].LoadModel(L"Resources/leftArm.cmo");
	m_objEnemy[ENEMY_PARTS_HED].LoadModel(L"Resources/hed.cmo");

	m_objEnemy[ENEMY_PARTS_HED].SetParent(&m_objEnemy[ENEMY_PARTS_BODE]);
	m_objEnemy[ENEMY_PARTS_RIGHTARM].SetParent(&m_objEnemy[ENEMY_PARTS_BODE]);
	m_objEnemy[ENEMY_PARTS_LEFTARM].SetParent(&m_objEnemy[ENEMY_PARTS_BODE]);

	m_objEnemy[ENEMY_PARTS_BODE].SetParent(&m_objEnemy[ENEMY_PARTS_TANK]);

	//�e����̍��W
	m_objEnemy[ENEMY_PARTS_BODE].SetTranslation(Vector3(0, 0.3, 0));
	m_objEnemy[ENEMY_PARTS_RIGHTARM].SetTranslation(Vector3(0.5, 0.85, 0));
	m_objEnemy[ENEMY_PARTS_LEFTARM].SetTranslation(Vector3(-0.5, 0.85, 0));
	m_objEnemy[ENEMY_PARTS_HED].SetTranslation(Vector3(0, 1, 0));

	//�����ʒu
	Vector3 pos;
	pos.x = rand() % 10 + 10;
	//pos.y = rand() % 10;

	this->SetTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;
	//m_objEnemy[ENEMY_PARTS_TANK].SetTranslation(pos);

	{//�e�ۗp�̂����蔻��̐ݒ�
		m_collisionNodeBody.Initialize();

		m_collisionNodeBody.SetParent(&m_objEnemy[ENEMY_PARTS_BODE]);
		m_collisionNodeBody.SetTrans(Vector3(0.f, 0.5f, 0.0f));
		m_collisionNodeBody.setLocalRadius(1.0f);
	}
}

//---------------------------------------------------------------
//�A�b�v�f�[�g
//---------------------------------------------------------------
void Enemy::Update()
{
	/*m_timer--;

	if (m_timer < 0)
	{
		m_timer = 60;

		float rnd = (float)rand() / RAND_MAX - 0.05f;

		rnd *= 180.f;

		m_distAngle += rnd;
	}

	Vector3 rotv = m_objEnemy[ENEMY_PARTS_TANK].GetRotation();
	float angle = GetShortAngleRad(rotv.y, XMConvertToRadians(m_distAngle));
	rotv.y += angle * 0.01f;
	m_objEnemy[ENEMY_PARTS_TANK].SetTranslation(rotv);



	Vector3 trans = m_objEnemy[ENEMY_PARTS_TANK].GetRotation();

	Vector3 move(0, 0, -0.02f);
	Vector3 rotv = m_objEnemy[ENEMY_PARTS_TANK].GetRotation();
	Matrix rotm = Matrix::CreateRotationY(rotv.y);
	move = Vector3::TransformNormal(move, rotm);

	trans += move;
	m_objEnemy[ENEMY_PARTS_TANK].SetTranslation(trans);

	Calc();
*/

	m_Timer--;
	if (m_Timer < 0)
	{
		m_Timer = 60;
		// -0.5�`+0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	if (hypot(m_objEnemy[0].GetTranslation().z, m_objEnemy[0].GetTranslation().x) >= 100)
	{
		m_DistAngle = atan2f(-m_objEnemy[0].GetTranslation().x, -m_objEnemy[0].GetTranslation().z) + 180;
	}
	//��]�p�����߂�
	this->moveRotation();

	// �@�̂������Ă�������ɐi��
	this->moveransform();
	
	

	Calc();

	//�X�V
	m_collisionNodeBody.Update();
}

void Enemy::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_objEnemy.begin();
		it != m_objEnemy.end();
		it++)
	{
		it->Update();
	}
}


//---------------------------------------------------------------
//�`��
//---------------------------------------------------------------
void Enemy::Draw(bool debug)
{
	for (std::vector<Obj3d>::iterator it = m_objEnemy.begin();
		it != m_objEnemy.end();
		it++)
	{
		it->Draw();
	}

	if (debug == true)
	{
		m_collisionNodeBody.Draw();
	}
}

const DirectX::SimpleMath::Vector3 & Enemy::GetTrans()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return m_objEnemy[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3 & Enemy::GetRot()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return m_objEnemy[0].GetRotation();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3 & trans)
{
	m_objEnemy[0].SetTranslation(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3 & rot)
{
	m_objEnemy[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix & Enemy::GetLocalWorld()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return m_objEnemy[0].GetWorld();
}

void Enemy::moveRotation()
{
	// ���@�̊p�x����]������
	Vector3 rotv = m_objEnemy[0].GetRotation();

	float angle = m_DistAngle - rotv.y;

	// 180�x�𒴂��Ă����ꍇ�A�t���̕����߂�
	if (angle > XM_PI)
	{
		angle -= XM_2PI;
	}

	if (angle < -XM_PI)
	{
		angle += XM_2PI;
	}

	// ���
	rotv.y += angle * 0.05f;

	SetRot(rotv);
}

void Enemy::moveransform()
{
	// �ړ��ʂ̃x�N�g��
	Vector3 moveV(0, 0, -0.1f);
	// �ړ��ʃx�N�g�������@�̊p�x����]������
	//moveV = Vector3::TransformNormal(moveV, tank_world);
	float angle = m_objEnemy[0].GetRotation().y;
	Matrix rotmat = Matrix::CreateRotationY(angle);
	moveV = Vector3::TransformNormal(moveV, rotmat);
	// ���@�̍��W���ړ�������
	Vector3 pos = m_objEnemy[0].GetTranslation();

	m_objEnemy[0].SetTranslation(pos + moveV);
}
