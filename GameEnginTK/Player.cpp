//==============================================================
//Player�̃N���X
//==============================================================


#include "Player.h"
#include "Camera.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------
Player::Player()
	: m_risetFlag(false)
{
	m_objPlayer.resize(PLAYER_PARTS_NUM);
	m_objPlayer[PLAYER_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_objPlayer[PLAYER_PARTS_BODE].LoadModel(L"Resources/bode.cmo");
	m_objPlayer[PLAYER_PARTS_RIGHTARM].LoadModel(L"Resources/rightArm.cmo");
	m_objPlayer[PLAYER_PARTS_LEFTARM].LoadModel(L"Resources/leftArm.cmo");
	m_objPlayer[PLAYER_PARTS_HED].LoadModel(L"Resources/hed.cmo");

	m_objPlayer[PLAYER_PARTS_HED].SetParent(&m_objPlayer[PLAYER_PARTS_BODE]);
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetParent(&m_objPlayer[PLAYER_PARTS_BODE]);
	m_objPlayer[PLAYER_PARTS_LEFTARM].SetParent(&m_objPlayer[PLAYER_PARTS_BODE]);

	m_objPlayer[PLAYER_PARTS_BODE].SetParent(&m_objPlayer[PLAYER_PARTS_TANK]);

	//�e����̍��W
	m_objPlayer[PLAYER_PARTS_BODE].SetTranslation(Vector3(0, 0.3, 0));
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetTranslation(Vector3(0.5, 0.85, 0));
	m_objPlayer[PLAYER_PARTS_LEFTARM].SetTranslation(Vector3(-0.5, 0.85, 0));
	m_objPlayer[PLAYER_PARTS_HED].SetTranslation(Vector3(0, 1, 0));
	
}

void Player::Initialize(Keyboard* keyboard)
{
	m_keyboard = keyboard;

	{//�e�ۗp�̂����蔻��̐ݒ�
		m_collisiorNodeBullet.Initialize();

		m_collisiorNodeBullet.SetParent(&m_objPlayer[PLAYER_PARTS_RIGHTARM]);
		m_collisiorNodeBullet.SetTrans(Vector3(0.f, 0.f, -0.7f));
		m_collisiorNodeBullet.setLocalRadius(0.3f);
	}


}
//---------------------------------------------------------------
//�A�b�v�f�[�g
//---------------------------------------------------------------
void Player::Update()
{
	Keyboard::State g_key = m_keyboard->GetState();

	m_keyboadTraker.Update(g_key);
		//�@�̊p�x------------------------------------------------------
		//���[(���ʊp)
		if (g_key.A)
		{
			m_objPlayer[0].SetRotation(Vector3(0, m_objPlayer[0].GetRotation().y + 0.03f, 0));
		}

		if (g_key.D)
		{
			m_objPlayer[0].SetRotation(Vector3(0, m_objPlayer[0].GetRotation().y - 0.03f, 0));
		}


		//�O�i��i------------------------------------------------------
		if (g_key.W)
		{
			//�ړ��ʂ����
			Vector3 moveV(0, 0, -0.1f);

			float angle = m_objPlayer[0].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationY(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//���@�̈ړ�
			Vector3 pos = m_objPlayer[0].GetTranslation();
			m_objPlayer[0].SetTranslation(pos + moveV);
		}

		if (g_key.S)
		{
			//�ړ��ʂ����
			Vector3 moveV(0, 0, 0.1f);

			float angle = m_objPlayer[0].GetRotation().y;
			Matrix rotmat = Matrix::CreateRotationY(angle);
			moveV = Vector3::TransformNormal(moveV, rotmat);

			//���@�̈ړ�
			Vector3 pos = m_objPlayer[0].GetTranslation();
			m_objPlayer[0].SetTranslation(pos + moveV);
		}
	

		//���r-----------------------------------------------------------
		if (g_key.Q)
		{
			float angle = m_objPlayer[3].GetRotation().x;

			if (angle <= XMConvertToRadians(45))
			{
				m_objPlayer[3].SetRotation(Vector3(angle + 0.03f, 0, 0));
			}
		}

		if (g_key.Z)
		{
			float angle = m_objPlayer[3].GetRotation().x;

			if (angle >= XMConvertToRadians(-45))
			{
				m_objPlayer[3].SetRotation(Vector3(angle - 0.03f, 0, 0));
			}
		}
	

	
		//�E�r-----------------------------------------------------------
		if (!m_risetFlag)
		{
			if (g_key.E)
			{
				float angle = m_objPlayer[2].GetRotation().x;

				if (angle <= XMConvertToRadians(45))
				{
					m_objPlayer[2].SetRotation(Vector3(angle + 0.03f, 0, 0));
				}
			}

			if (g_key.C)
			{
				float angle = m_objPlayer[2].GetRotation().x;

				if (angle >= XMConvertToRadians(-45))
				{
					m_objPlayer[2].SetRotation(Vector3(angle - 0.03f, 0, 0));
				}
			}
		}
	

	
		/*for (int i = 0; i < PLAYER_PARTS_NUM; i++)
		{
			m_objPlayer[i].Update();
		}*/


		{
			Vector3 pos = m_objPlayer[PLAYER_PARTS_RIGHTARM].GetTranslation();
			m_objPlayer[PLAYER_PARTS_RIGHTARM].SetTranslation(pos + m_BulletVel);
		}

		Calc();
		if (m_keyboadTraker.IsKeyPressed(Keyboard::Keys::Space))
		{
			FireBull();
		}

		
}


//---------------------------------------------------------------
//�`��
//---------------------------------------------------------------
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_objPlayer.begin(); it != m_objPlayer.end(); it++)
	{
		it->Draw();
	}

	m_collisiorNodeBullet.Draw();
}

Vector3 Player::GetTranslation()
{
	return m_objPlayer[0].GetTranslation();
}

Vector3 Player::GetRotation()
{
	return m_objPlayer[0].GetRotation();
}

void Player::FireBull()
{
	if (m_risetFlag)
	{
		RsetFireBull();
		return;
	}

	//���˂��郏�[���h�s��̎擾
	Matrix worldm = m_objPlayer[PLAYER_PARTS_RIGHTARM].GetWorld();

	//���[���h�s�񂩂�e�v�f���擾
	Vector3 scale;//���[���h�X�P�[�����O
	Quaternion rotation;//���[���h��]
	Vector3 translation;//���[���h���W

	worldm.Decompose(scale, rotation, translation);

	//���˃p�[�c��e���番�����ēƗ�
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetParent(nullptr);
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetScale(scale);
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetRotationQ(rotation);
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetTranslation(translation);

	//�e�ۂ̑��x��ݒ�
	m_BulletVel = Vector3(0, 0, -0.1f);
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	m_risetFlag = true;
}

void Player::RsetFireBull()
{
	if (!m_risetFlag) return;
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetParent(&m_objPlayer[PLAYER_PARTS_BODE]);

	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetScale(Vector3(1, 1, 1));
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetRotation(Vector3(0, 0, 0));
	m_objPlayer[PLAYER_PARTS_RIGHTARM].SetTranslation(Vector3(0.5, 0.85, 0));

	m_BulletVel = Vector3(0, 0, 0);

	m_risetFlag = false;
}

void Player::Calc()
{
	for (int i = 0; i < PLAYER_PARTS_NUM; i++)
	{
		m_objPlayer[i].Update();
	}

	//�X�V
	m_collisiorNodeBullet.Update();
}
