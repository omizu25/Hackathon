//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "result.h"
#include "input.h"
#include "sound.h"
#include "application.h"
#include "object3D.h"
#include "fade.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CResult::CResult()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CResult::Init()
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

	{// ���A(��)
		CObject3D* pLeft = CObject3D::Create();

		// �ʒu�̐ݒ�
		pLeft->SetPos(D3DXVECTOR3(300.0f, -10.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pLeft->SetSize(D3DXVECTOR3(430.0f, 430.0f, 0.0f));

		// �F�̐ݒ�
		pLeft->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pLeft->SetTexture(CTexture::LABEL_RESULT_CaveLeft);
	}

	{// ���A(�E)
		CObject2D* pLeft = CObject2D::Create();

		// �ʒu�̐ݒ�
		pLeft->SetPos(D3DXVECTOR3(939.0f, 365.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pLeft->SetSize(D3DXVECTOR3(410.0f, 410.0f, 0.0f));

		// �F�̐ݒ�
		pLeft->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pLeft->SetTexture(CTexture::LABEL_RESULT_CaveRight);
	}

	{// ��
		CObject2D* pSnake = CObject2D::Create();

		// �ʒu�̐ݒ�
		pSnake->SetPos(D3DXVECTOR3(300.0f, 365.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pSnake->SetSize(D3DXVECTOR3(500.0f, 200.0f, 0.0f));

		// �F�̐ݒ�
		pSnake->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �e�N�X�`���̐ݒ�
		pSnake->SetTexture(CTexture::LABEL_RESULT_SnakeAnim);
	}

	//�Ȃ̍Đ�
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CResult::Uninit()
{
	//�Ȃ̒�~
	CApplication::GetInstance()->GetSound()->Stop();

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CResult::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_F1))
	{// �L�[�������ꂽ
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RANKING);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CResult::Draw()
{
}
