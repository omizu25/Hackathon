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
#include "number_manager.h"

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
	//�e�����o�ϐ��̏�����
	m_time = 0;
	m_bUse_SE = false;

	{// �w�i
		CObject3D* pObj = CObject3D::Create();

		// �ʒu�̐ݒ�
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// �F�̐ݒ�
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LABEL_Frame_Space);
	}

	{// �X�R�A
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.27f, size.y * 0.65f, 0.0f);

		// ����
		m_pTime = CNumberManager::Create(pos, size, 30);

		//�X�R�A�pUI�̐���
		CObject2D* pScore = CObject2D::Create();

		// �ʒu�̐ݒ�
		pScore->SetPos(D3DXVECTOR3(1045.0f, 65.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pScore->SetSize(D3DXVECTOR3(170.0f, 170.0f, 0.0f));

		// �F�̐ݒ�
		pScore->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pScore->SetTexture(CTexture::LABEL_UI_Stake);
	}

	{// �^�C��
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH - 30.0f, size.y * 0.65f, 0.0f);

		// ����
		m_pScore = CNumberManager::Create(pos, size, 0);

		//�^�C���pUI�̐���
		CObject2D* pTime = CObject2D::Create();

		// �ʒu�̐ݒ�
		pTime->SetPos(D3DXVECTOR3(120.0f, 68.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pTime->SetSize(D3DXVECTOR3(200.0f, 150.0f, 0.0f));

		// �F�̐ݒ�
		pTime->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pTime->SetTexture(CTexture::LABEL_Time);
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
	CApplication::GetInstance()->GetSound()->SetVolume(CSound::LABEL_BGM_Game, 0.5f);
	CApplication::GetInstance()->GetSound()->SetRate(CSound::LABEL_BGM_Game, 1.0f);
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
	m_time++;

	if (m_time % 60 == 0)
	{
		m_pTime->Add(-1);

		if (!m_bUse_SE &&
			m_pTime->Get() <= 10)
		{
			CApplication::GetInstance()->GetSound()->SetVolume(CSound::LABEL_SE_Waring, 2.0f);
			CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_Waring);
			m_bUse_SE = true;
			CApplication::GetInstance()->GetSound()->SetRate(CSound::LABEL_BGM_Game, 1.2f);
		}

		if (m_pTime->Get() <= 0)
		{
			// ���[�h�̕ύX
			CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RESULT);
		}
	}

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
