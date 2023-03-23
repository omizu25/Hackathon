//**************************************************
// 
// return.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "return.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "fade.h"
#include "mode.h"
#include "game.h"
#include "ranking_ui.h"
#include "effect.h"
#include "utility.h"
#include "sound.h"

//==================================================
// ��`
//==================================================
namespace
{
const int STD_TIME = 20;
const float STD_SIZE = 270.0f;
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
float CReturn::m_move = 0.0f;
int CReturn::m_count = 0;

//--------------------------------------------------
// ����
//--------------------------------------------------
void CReturn::AddMove()
{
	m_move += 0.1f;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
float CReturn::GetMove()
{
	return m_move;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CReturn::CreateAll()
{
	m_move = 0.0f;
	D3DXVECTOR3 pos = D3DXVECTOR3(-STD_SIZE, -120.0f, 0.0f);

	m_count = CRankingUI::Get(-1);
	//m_count = 7;

	for (int i = 0; i < CRankingUI::Get(-1); i++)
		//for (int i = 0; i < 7; i++)
	{
		// ����
		CReturn::Create(pos);

		pos.x -= STD_SIZE;
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CReturn* CReturn::Create(const D3DXVECTOR3& pos)
{
	CReturn* pDomino = new CReturn;

	if (pDomino == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pDomino->Init();

	// �ʒu�̐ݒ�
	pDomino->SetPos(pos);

	return pDomino;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CReturn::CReturn()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CReturn::~CReturn()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CReturn::Init()
{
	m_time = 0;
	u = D3DXVECTOR2(0.0f, 0.5f);
	m_effect = false;

	// ������
	CObject3D::Init();

	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �g�p���郂�f���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_RESULT_SnakeAnim);

	CObject3D::SetVtxTex(u, D3DXVECTOR2(0.0f, 1.0f));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CReturn::Uninit()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �I��
	CObject3D::Uninit();

	m_count--;

	if (m_count <= 0)
	{
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RANKING);
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CReturn::Update()
{
	m_time++;

	if (m_time >= STD_TIME)
	{
		u.x += 0.5f;
		u.y += 0.5f;
		CObject3D::SetVtxTex(u, D3DXVECTOR2(0.0f, 1.0f));
	}

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos.x += m_move;

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	if (!m_effect)
	{
		if (pos.x >= (float)CApplication::SCREEN_WIDTH * 0.25f)
		{
			CEffect::Enemy(pos);
			CEffect::Bom(pos);
			CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_Explosion);
			m_effect = true;
		}
	}
		

	if (pos.x >= (float)CApplication::SCREEN_WIDTH)
	{// �͈͊O�ɏo��
		CObject::SetRelease();
	}

	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CReturn::Draw()
{
	// �`��
	CObject3D::Draw();
}
