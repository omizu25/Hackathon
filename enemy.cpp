//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy.h"
#include "application.h"
#include "utility.h"
#include "player.h"
#include "game.h"

//==================================================
// ��`
//==================================================
namespace
{
const int STD_TIME = 90;		// ��������
const float STD_MOVE = 5.0f;	// �ړ����x
const float STD_SIZE = 40.0f;	// �T�C�Y
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, float rot)
{
	CEnemy* pEnemy = new CEnemy;

	if (pEnemy == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pEnemy->Init();

	// �ݒ�
	pEnemy->Set(pos, rot);

	return pEnemy;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemy::CEnemy() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemy::~CEnemy()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemy::Init()
{
	m_time = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ������
	CObject3D::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemy::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemy::Update()
{
	m_time++;

	if (m_time <= STD_TIME)
	{// �������Ԓ�

		// �F�̎擾
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = SinCurve(m_time, 0.1f);

		// �F�̐ݒ�
		CObject3D::SetCol(col);

		// �X�V
		CObject3D::Update();
		return;
	}
	else
	{
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f;

		// �F�̐ݒ�
		CObject3D::SetCol(col);

		// �ړ�
		Move();

		// �����蔻��
		Collision();

		// �X�V
		CObject3D::Update();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemy::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemy::Set(const D3DXVECTOR3& pos, float rot)
{
	// �ړ��ʂ̐ݒ�
	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Enemy);
}

//--------------------------------------------------
// �ړ�
//--------------------------------------------------
void CEnemy::Move()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	D3DXVECTOR3 range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	range.x = ((float)CApplication::SCREEN_WIDTH * 0.5f) - (STD_SIZE * 0.5f);
	range.y = ((float)CApplication::SCREEN_HEIGHT * 0.5f) - (STD_SIZE * 0.5f);

	// �͈͓��Ŕ���
	InRangeReflect(&pos, &m_move, range);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CEnemy::Collision()
{
	CGame* pGame = (CGame*)CApplication::GetInstance()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = STD_SIZE * 0.5f;
	D3DXVECTOR3 targetPos = pPlayer->GetPos();
	float targetSize = pPlayer->GetSize().x * 0.5f;

	if (CollisionCircle(pos, size, targetPos, targetSize))
	{// �����蔻��
		pPlayer->SetRelease();
	}
}
