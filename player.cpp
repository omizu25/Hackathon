//==========================================
//
// �v���C���[�̏���
// Author:Teruto Sato
//
//==========================================

//-----------------------------
// �C���N���[�h
//-----------------------------
#include "player.h"
#include "input.h"

//-----------------------------
// ��`
//-----------------------------
namespace
{
	float fSpeed = 3.0f;	//���x
}

//-----------------------------
// �ÓI�����o�ϐ�
//-----------------------------
bool CPlayer::m_kill = false;

//===============================
// �R���X�g���N�^
//===============================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�傫��
}

//===============================
// �f�X�g���N�^
//===============================
CPlayer::~CPlayer()
{
}

//===============================
// ������
//===============================
void CPlayer::Init()
{
	//�I�u�W�F�N�g�̏�����
	CObject3D::Init();

	//�����l�̐ݒ�
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);	//�傫��

	//�v���C���[���̐ݒ�
	CObject3D::SetSize(m_size);	//�傫��
}

//===============================
// �I��
//===============================
void CPlayer::Uninit()
{
	//�I�u�W�F�N�g�̏I��
	CObject3D::Uninit();
}

//===============================
// �X�V
//===============================
void CPlayer::Update()
{
	//�I�u�W�F�N�g�̍X�V
	CObject3D::Update();

	//�ړ�
	D3DXVECTOR3 move = Move(DIK_W, DIK_S, DIK_A, DIK_D);

	//----------------------
	// �ړ��ʂ��X�V(����)
	//----------------------
	m_move.x += (0.0f - move.x) * 0.4f;
	m_move.y += (0.0f - move.y) * 0.4f;

	//�ʒu�Ɉړ��ʂ����Z
	m_pos += m_move;

	//�ʒu��ݒ�
	CObject3D::SetPos(m_pos);
}

//===============================
// �`��
//===============================
void CPlayer::Draw()
{
	//�I�u�W�F�N�g�̕`��
	CObject3D::Draw();
}

//===============================
// ����
//===============================
CPlayer* CPlayer::Create()
{
	CPlayer *pPlayer = nullptr;

	//-------------------------------
	// �����Ə�����
	//-------------------------------
	pPlayer = new CPlayer;	//����

	if (pPlayer != nullptr)
	{//NULL�`�F�b�N
		//������
		pPlayer->Init();
	}

	return pPlayer;
}

//===============================
// �ݒ�
//===============================
void CPlayer::SetKill(bool kill)
{
	m_kill = kill;
}

//===============================
// �擾
//===============================
bool CPlayer::GetKill()
{
	return m_kill;
}

//===============================
// �ړ�
// �����F�㉺���E�L�[
//===============================
D3DXVECTOR3 CPlayer::Move(int nUp, int nDown, int nLeft, int nRight)
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Press(nLeft))
	{//���L�[�������ꂽ
		//-------------------------
		// ����ړ�
		//-------------------------
		if (pInput->Press(nUp))
		{//��L�[�������ꂽ
			m_move.x += sinf(-D3DX_PI * 0.75f) * fSpeed;
			m_move.y += cosf(-D3DX_PI * 0.25f) * fSpeed;
		}
		//-------------------------
		// �����ړ�
		//-------------------------
		else if (pInput->Press(nDown))
		{//���L�[�������ꂽ
			m_move.x += sinf(-D3DX_PI * 0.25f) * fSpeed;
			m_move.y += cosf(D3DX_PI * 0.75f) * fSpeed;
		}
		//-------------------------
		// ���ړ�
		//-------------------------
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * fSpeed;
		}
	}
	else if (pInput->Press(nRight))
	{//�E�L�[�������ꂽ
		//-------------------------
		// �E��ړ�
		//-------------------------
		if (pInput->Press(nUp))
		{//��L�[�������ꂽ
			m_move.x += sinf(D3DX_PI * 0.25f) * fSpeed;
			m_move.y += cosf(D3DX_PI * 0.25f) * fSpeed;
		}
		//-------------------------
		// �E���ړ�
		//-------------------------
		else if (pInput->Press(nDown))
		{//���L�[�������ꂽ
			m_move.x += sinf(D3DX_PI * 0.75f) * fSpeed;
			m_move.y += cosf(-D3DX_PI * 0.75f) * fSpeed;
		}
		//-------------------------
		// �E�ړ�
		//-------------------------
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * fSpeed;
		}
	}
	//-------------------------
	// ��ړ�
	//-------------------------
	else if (pInput->Press(nUp))
	{//��L�[�������ꂽ
		m_move.y += cosf(D3DX_PI * 0.0f) * fSpeed;
	}
	//-------------------------
	// ���ړ�
	//-------------------------
	else if (pInput->Press(nDown))
	{//���L�[�������ꂽ
		m_move.y += cosf(-D3DX_PI * 1.0f) * fSpeed;
	}

	return m_move;
}