//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "tutorial.h"
#include "input.h"
#include "sound.h"
#include "application.h"
#include "instancing.h"
#include "menu.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTutorial::CTutorial() :
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTutorial::~CTutorial()
{
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTutorial::Init()
{
	{// �w�i
		CObject3D* pObj = CObject3D::Create();

		// �ʒu�̐ݒ�
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// �F�̐ݒ�
		pObj->SetCol(D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LABEL_TITLE_BG);
	}

	{// ���j���[
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.8f, (float)CApplication::SCREEN_HEIGHT * 0.9f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(350.0f, 100.0f, 0.0f);

		// ����
		m_pMenu = CMenu::Create(pos, size, 1, 50.0f);

		// �g�̐ݒ�
		m_pMenu->SetFrame(pos, D3DXVECTOR3(600.f, 100.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		// �e�N�X�`���̐ݒ�
		m_pMenu->SetTexture(0, CTexture::LABEL_TITLE_PressEnter);
	}

	//�Ȃ̍Đ�
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Title);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTutorial::Uninit()
{
	//�Ȃ̒�~
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pMenu != nullptr)
	{// null�`�F�b�N
		m_pMenu = nullptr;
	}

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTutorial::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_F1))
	{// �L�[�������ꂽ
	 // ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
	}

	// ����
	Input();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTutorial::Draw()
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CTutorial::Input()
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

	// ���[�h�̕ύX
	CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
}