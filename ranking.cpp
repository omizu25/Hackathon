//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "ranking.h"
#include "menu.h"
#include "application.h"
#include "instancing.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"
#include "sound.h"
#include "input.h"
#include "number_manager.h"
#include "ranking_ui.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CRanking::CRanking() :
	m_pMenu(nullptr),
	m_pScore(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CRanking::~CRanking()
{
	assert(m_pMenu == nullptr);
	assert(m_pScore == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CRanking::Init()
{
	{// �w�i
		CObject3D* pObj = CObject3D::Create();

		// �ʒu�̐ݒ�
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// �F�̐ݒ�
		pObj->SetCol(D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LABEL_TITLE_BG);
	}

	{// �����L���O�̃��S
		CObject2D* pObj = CObject2D::Create();

		pObj->SetPos(D3DXVECTOR3(320.0f, 70.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pObj->SetSize(D3DXVECTOR3(600.f, 400.f, 0.0f));

		// �F�̐ݒ�
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LABEL_RANKING_LOGO);
	}

	{// �����L���O
		D3DXVECTOR3 pos = D3DXVECTOR3(520.f, 200.0f, 0.0f);

		// �X�R�A�̐ݒ�
		CRankingUI::SetScore(1);

		// ����
		CRankingUI::Create(pos, 20.0f);
	}

	{// ���j���[
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.75f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(500.0f, 400.0f, 0.0f);

		// ����
		m_pMenu = CMenu::Create(pos, size, 2, 0.0f);

		// �g�̐ݒ�
		m_pMenu->SetFrame(pos, D3DXVECTOR3(500.f, 600.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		// �J�[�\���̐ݒ�
		m_pMenu->SetCursor(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 20.0f);

		// �e�N�X�`���̐ݒ�
		m_pMenu->SetTexture(0, CTexture::LABEL_RANKING_RETURN_LOGO);

		// �e�N�X�`���̐ݒ�
		m_pMenu->SetTexture(1, CTexture::LABEL_RANKING_GO_LOGO);
	}

	// �Ȃ̍Đ�
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CRanking::Uninit()
{
	//�Ȃ̒�~
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pMenu != nullptr)
	{// null�`�F�b�N
		m_pMenu = nullptr;
	}

	if (m_pScore != nullptr)
	{// null�`�F�b�N
		m_pScore = nullptr;
	}

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CRanking::Update()
{
	// ����
	Input();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CRanking::Draw()
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CRanking::Input()
{
	if (m_pMenu == nullptr)
	{// null�`�F�b�N
		return;
	}

	int select = m_pMenu->Select();

	if (select == -1)
	{// ���͂���Ă��Ȃ�
		return;
	}

	if (select == 0)
	{
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
	}
	else
	{
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_TITLE);
	}
}
