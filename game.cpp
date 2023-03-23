//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "game.h"
#include "sound.h"
#include "input.h"
#include "application.h"
#include "fade.h"
#include "object3D.h"
#include "effect.h"
#include "player.h"
#include "enemy_manager.h"
#include "circle.h"

//==================================================
// �ÓI�����o�ϐ��錾
//==================================================
CPlayer* CGame::m_pPlayer = nullptr;	//�v���C���[
CCircle* CGame::m_pCircle = nullptr;	//�v���C���[

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// �v���C���[�̎擾
//--------------------------------------------------
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//--------------------------------------------------
// �v���C���[�̎擾
//--------------------------------------------------
CCircle* CGame::GetCircle()
{
	return m_pCircle;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	{// �w�i
		CObject3D* pObj = CObject3D::Create();

		// �ʒu�̐ݒ�
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// �F�̐ݒ�
		pObj->SetCol(D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LABEL_NONE);
	}

	// �T�[�N��
	m_pCircle = CCircle::Create();

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	// ����
	CEnemyManager::Create();

	CPlayer::SetKill(false);

	// �Ȃ̍Đ�
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Game);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	// �Ȃ̒�~
	CApplication::GetInstance()->GetSound()->Stop();

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
#ifdef _DEBUG
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_F1))
	{// �L�[�������ꂽ
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RESULT);
	}
	else if (pInput->Trigger(DIK_F2))
	{// �L�[�������ꂽ
		CEffect::Explosion(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else if (pInput->Trigger(DIK_F3))
	{// �L�[�������ꂽ
		CApplication::GetInstance()->GetSound()->SetRate(CSound::LABEL_BGM_Game, 1.2f);
	}
	else if (pInput->Trigger(DIK_F4))
	{// �L�[�������ꂽ
		CApplication::GetInstance()->GetSound()->SetRate(CSound::LABEL_BGM_Game, 0.8f);
	}
	else if (pInput->Trigger(DIK_F5))
	{// �L�[�������ꂽ
		CApplication::GetInstance()->GetSound()->SetVolume(CSound::LABEL_BGM_Game, 1.5f);
	}
	else if (pInput->Trigger(DIK_F6))
	{// �L�[�������ꂽ
		CApplication::GetInstance()->GetSound()->SetVolume(CSound::LABEL_BGM_Game, 0.5f);
	}
#endif // _DEBUG
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CGame::Draw()
{
}
