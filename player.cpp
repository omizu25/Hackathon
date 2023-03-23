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
#include "application.h"
#include "utility.h"
#include "fade.h"
#include "mode.h"
#include "sound.h"
#include "effect.h"

//-----------------------------
// ��`
//-----------------------------
namespace
{
	const float fSpeed = 3.0f;		//���x
	const float STD_SIZE = 30.0f;	// �T�C�Y
}

//-----------------------------
// �ÓI�����o�ϐ�
//-----------------------------
bool CPlayer::m_kill = false;
int CPlayer::m_life = 0;

//===============================
// �R���X�g���N�^
//===============================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�傫��
	m_time = 0;
	m_interval = false;
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
	m_kill = true;

	//�I�u�W�F�N�g�̏�����
	CObject3D::Init();

	//�����l�̐ݒ�
	m_size = D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f);	//�傫��

	//�v���C���[���̐ݒ�
	CObject3D::SetSize(m_size);	//�傫��

	//�c�@�̐ݒ�
	SetLife();

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Player);
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

	if (m_interval)
	{
		m_time++;

		if (m_time >= 10)
		{
			
			CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_Hit);
			m_kill = true;
			m_interval = false;
			m_time = 0;
		}

		return;
	}

	if (m_kill)
	{
		m_time++;

		// �F�̎擾
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = SinCurve(m_time, 0.1f);

		// �F�̐ݒ�
		CObject3D::SetCol(col);

		if (m_time >= 30)
		{
			CEffect::Bom(m_pos);
			m_kill = false;
			m_interval = false;
			m_time = 0;
		}

		return;
	}

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�ړ�
	D3DXVECTOR3 move = Move(DIK_W, DIK_S, DIK_A, DIK_D);

	//----------------------
	// �ړ��ʂ��X�V(����)
	//----------------------
	m_move.x += (0.0f - move.x) * 0.4f;
	m_move.y += (0.0f - move.y) * 0.4f;

	//�ʒu�Ɉړ��ʂ����Z
	m_pos += m_move;

	D3DXVECTOR3 range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	range.x = ((float)CApplication::SCREEN_WIDTH * 0.5f) - (STD_SIZE * 0.5f);
	range.y = ((float)CApplication::SCREEN_HEIGHT * 0.5f) - (STD_SIZE * 0.5f);

	// �͈͓��Ŕ���
	InRangeReflect(&m_pos, &m_move, range);

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
void CPlayer::SetKill()
{
	if (m_interval)
	{
		return;
	}

	if (m_kill)
	{
		return;
	}

	CEffect::Player(m_pos);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ʒu��ݒ�
	CObject3D::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	m_kill = true;
	m_interval = true;
	m_life--;
	m_time = 0;

	if (m_life <= 0)
	{
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RESULT);
	}
}

//===============================
// �擾
//===============================
bool CPlayer::GetKill()
{
	return m_kill;
}

//===============================
// �ݒ�
//===============================
void CPlayer::SetLife()
{
	m_life = 3;
}

//===============================
// �擾
//===============================
int CPlayer::GetLife()
{
	return m_life;
}

//===============================
// �ړ�
// �����F�㉺���E�L�[
//===============================
D3DXVECTOR3 CPlayer::Move(int nUp, int nDown, int nLeft, int nRight)
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Press(nLeft) || pInput->Press(KEY_LEFT))
	{//���L�[�������ꂽ
		//-------------------------
		// ����ړ�
		//-------------------------
		if (pInput->Press(nUp) || pInput->Press(KEY_UP))
		{//��L�[�������ꂽ
			m_move.x += sinf(-D3DX_PI * 0.75f) * fSpeed;
			m_move.y += cosf(-D3DX_PI * 0.25f) * fSpeed;
		}
		//-------------------------
		// �����ړ�
		//-------------------------
		else if (pInput->Press(nDown) || pInput->Press(KEY_DOWN))
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
	else if (pInput->Press(nRight) || pInput->Press(KEY_RIGHT))
	{//�E�L�[�������ꂽ
		//-------------------------
		// �E��ړ�
		//-------------------------
		if (pInput->Press(nUp) || pInput->Press(KEY_UP))
		{//��L�[�������ꂽ
			m_move.x += sinf(D3DX_PI * 0.25f) * fSpeed;
			m_move.y += cosf(D3DX_PI * 0.25f) * fSpeed;
		}
		//-------------------------
		// �E���ړ�
		//-------------------------
		else if (pInput->Press(nDown) || pInput->Press(KEY_DOWN))
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
	else if (pInput->Press(nUp) || pInput->Press(KEY_UP))
	{//��L�[�������ꂽ
		m_move.y += cosf(D3DX_PI * 0.0f) * fSpeed;
	}
	//-------------------------
	// ���ړ�
	//-------------------------
	else if (pInput->Press(nDown) || pInput->Press(KEY_DOWN))
	{//���L�[�������ꂽ
		m_move.y += cosf(-D3DX_PI * 1.0f) * fSpeed;
	}

	return m_move;
}