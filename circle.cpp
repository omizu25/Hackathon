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
const int POP_TIME = 30;
const int APPEARANCE_TIME = 300;
const int INTERVAL_TIME = 90;
const float STD_SIZE = 400.0f;	// �T�C�Y
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
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_changeCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_appear(false),
	m_nowAppear(false)
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
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_appear = false;
	m_nowAppear = false;

	// ������
	CObject3D::Init();

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObject3D::SetCol(D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_circle);
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
		m_time = 0;
		m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_appear = false;
		m_nowAppear = false;

		// �T�C�Y�̐ݒ�
		CObject3D::SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		return;
	}

	m_time++;

	if (!m_nowAppear)
	{
		// �F�̐ݒ�
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (m_appear)
		{
			if (m_time >= APPEARANCE_TIME)
			{
				m_time = 0;
				m_nowAppear = true;
				m_appear = false;
			}
		}
		else
		{
			if (m_time >= INTERVAL_TIME)
			{
				m_time = 0;
				m_nowAppear = true;
				m_appear = true;

				float size = FloatRandom(STD_SIZE, STD_SIZE * 0.5f);
				m_size = D3DXVECTOR3(size, size, 0.0f);

				float width = (float)CApplication::SCREEN_WIDTH * 0.35f;
				float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

				D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				pos.x = FloatRandom(width, -width);
				pos.y = FloatRandom(height, -height);

				SetPos(pos);
			}
		}
	}
	else
	{
		Appear();
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
	if (m_appear)
	{
		D3DXVECTOR3 size = GetSize();

		size.x += (m_size.x / POP_TIME);
		size.y += (m_size.y / POP_TIME);

		if (m_time >= POP_TIME)
		{
			m_time = 0;
			m_nowAppear = false;

			size = m_size;
		}
		
		SetSize(size);
	}
	else
	{
		D3DXVECTOR3 size = GetSize();

		size.x -= (m_size.x / POP_TIME);
		size.y -= (m_size.y / POP_TIME);

		if (m_time >= POP_TIME)
		{
			m_time = 0;
			m_nowAppear = false;

			size.x = 0.0f;
			size.y = 0.0f;
		}

		SetSize(size);
	}

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.7f);

	// �F�̐ݒ�
	SetCol(col);
}
