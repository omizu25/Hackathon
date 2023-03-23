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
#include "ranking_ui.h"

//==================================================
// �ÓI�����o�ϐ��錾
//==================================================
CPlayer* CGame::m_pPlayer = nullptr;	//�v���C���[
CCircle* CGame::m_pCircle = nullptr;	//�v���C���[
int CGame::m_score = 0;

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
// �v���C���[�̎擾
//--------------------------------------------------
void CGame::AddScore(int score)
{
	m_score += score;
}

//--------------------------------------------------
// �v���C���[�̎擾
//--------------------------------------------------
int CGame::GetScore()
{
	return m_score;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	//�e�����o�ϐ��̏�����
	m_time = 0;
	m_score = 0;
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
		m_pTime = CNumberManager::Create(pos, size, 60);

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

	{// �c�@
		int nLife = CPlayer::GetLife();

		for (int i = 0; i < nLife; i++)
		{
			pObjPlayer[i] = CObject2D::Create();

			// �ʒu�̐ݒ�
			float fPosX = CApplication::SCREEN_WIDTH / 2 - 70.0f;
			pObjPlayer[i]->SetPos(D3DXVECTOR3(fPosX + (70.0f * i), 70.0f, 0.0f));

			// �T�C�Y�̐ݒ�
			pObjPlayer[i]->SetSize(D3DXVECTOR3(70.0f, 70.0f, 0.0f));

			// �F�̐ݒ�
			pObjPlayer[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// �e�N�X�`���̐ݒ�
			pObjPlayer[i]->SetTexture(CTexture::LABEL_Player);
		}
	}

	// ����
	CEnemyManager::Create();

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

	// �X�R�A�̐ݒ�
	CRankingUI::SetScore(m_score);

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
			m_pTime->Set(0);

			// ���[�h�̕ύX
			CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RESULT);
		}
	}

	m_pScore->Set(m_score);

	DeathPlayer();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CGame::Draw()
{
}

//--------------------------------------------------
// �c�@�����炷����
//--------------------------------------------------
void CGame::DeathPlayer()
{
	int nLife = CPlayer::GetLife();

	for (int i = 2; i > nLife - 1; i--)
	{
		pObjPlayer[i]->SetRelease();
	}
}