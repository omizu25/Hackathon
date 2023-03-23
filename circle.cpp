//**************************************************
// 
// circle.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "circle.h"
#include "utility.h"
#include "application.h"
#include "player.h"

//==================================================
// ��`
//==================================================
namespace
{
const int STD_TIME = 100;
const float STD_SIZE = 300.0f;	// �T�C�Y
}

const int CCircle::COUNTDOWN_TIME = 120;
const int CCircle::MAX_LIFE = 1200;
const D3DXCOLOR CCircle::STD_COLOR = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR CCircle::START_COLOR = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CCircle::END_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR CCircle::DIFF_COLOR = END_COLOR - START_COLOR;

//--------------------------------------------------
// ����
//--------------------------------------------------
CCircle* CCircle::Create()
{
	CCircle* pEnemy = new CCircle;

	if (pEnemy == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pEnemy->Init();

	return pEnemy;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CCircle::CCircle() :
	m_time(0),
	m_changeCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_appear(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCircle::~CCircle()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CCircle::Init()
{
	m_time = 0;
	m_changeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_appear = false;

	// ������
	CObject3D::Init();

	// �ʒu�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �F�̐ݒ�
	CObject3D::SetCol(m_changeCol);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Shape_Circle);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCircle::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CCircle::Update()
{
	if (CPlayer::GetKill())
	{
		return;
	}

	m_time++;

	if (m_time >= STD_TIME)
	{
		m_time = 0;
		m_appear = !m_appear;
		D3DXCOLOR col = GetCol();

		if (m_appear)
		{
			col.a = 1.0f;

			float width = (float)CApplication::SCREEN_WIDTH * 0.35f;
			float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pos.x = FloatRandom(width, -width);
			pos.y = FloatRandom(height, -height);

			float size = FloatRandom(STD_SIZE, STD_SIZE * 0.25f);

			SetSize(D3DXVECTOR3(size, size, 0.0f));

			SetPos(pos);
		}
		else
		{
			col.a = 0.0f;
		}

		CObject3D::SetCol(col);

	}

	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CCircle::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �����蔻�肷�邩�ǂ���
//--------------------------------------------------
bool CCircle::GetCollision()
{
	return m_appear;
}

//--------------------------------------------------
// �o��������
//--------------------------------------------------
void CCircle::Appear()
{
}
