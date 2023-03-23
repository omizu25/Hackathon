//**************************************************
// 
// snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "snake_head.h"
#include "snake_body.h"
#include "application.h"
#include "utility.h"
#include "game.h"
#include "player.h"
#include "circle.h"

//==================================================
// ��`
//==================================================
namespace
{
const int MAX_BODY = 25;			// �̂̍ő吔
const int IDX_PARENT = 0;			// �e�̔ԍ�
const int STD_TIME = 90;			// ��������
const float STD_SIZE = 30.0f;		// �T�C�Y�̕W���l
const float OBJ_SIZE = 300.0f;		// �T�C�Y�̕W���l
const float STD_MOVE = 1.5f;		// �ړ��ʂ̕W���l
const float AMPLITUDE_WIDTH = 3.0f;	// �U���̕�
const float AMPLITUDE_SPEED = 2.0f;	// �U���̑��x
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CSnakeHead* CSnakeHead::Create(const D3DXVECTOR3& pos)
{
	CSnakeBody** pBody = new CSnakeBody*[MAX_BODY];

	for (int i = 0; i < MAX_BODY; i++)
	{
		pBody[i] = nullptr;
	}

	for (int i = 0; i < MAX_BODY; i++)
	{
		// ����
		pBody[i] = CSnakeBody::Create();
		pBody[i]->SetPos(pos);
		pBody[i]->SetPosDest(pos);
	}

	CSnakeHead* pSnake = new CSnakeHead;

	if (pSnake == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pSnake->Init();

	// �ݒ�
	pSnake->Set(pos, pBody);

	return pSnake;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CSnakeHead::CSnakeHead() :
	m_time(0),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_target(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pBody(nullptr),
	m_pObj(nullptr),
	m_chase(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CSnakeHead::~CSnakeHead()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CSnakeHead::Init()
{
	m_time = 0;
	m_chase = false;

	// ������
	CObject3D::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CSnakeHead::Uninit()
{
	for (int i = 0; i < MAX_BODY; i++)
	{
		if (m_pBody[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		// ���
		m_pBody[i] = nullptr;
	}

	if (m_pBody != nullptr)
	{// null�`�F�b�N
		delete[] m_pBody;
		m_pBody = nullptr;
	}

	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CSnakeHead::Update()
{
	if (CPlayer::GetKill())
	{
		return;
	}

	m_time++;

	if (m_time == STD_TIME)
	{
		// �F�̎擾
		D3DXCOLOR col = CObject3D::GetCol();

		col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		// �F�̐ݒ�
		CObject3D::SetCol(col);
	}

	if (m_time <= STD_TIME)
	{// �������Ԓ�

		// �F�̎擾
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = SinCurve(m_time, 0.1f);

		// �F�̐ݒ�
		CObject3D::SetCol(col);

		for (int i = 0; i < MAX_BODY; i++)
		{
			if (m_pBody[i] == nullptr)
			{// null�`�F�b�N
				continue;
			}

			// �F�̎擾
			D3DXCOLOR colBody = m_pBody[i]->GetCol();

			colBody.a = 0.0f;

			// �F�̐ݒ�
			m_pBody[i]->SetCol(colBody);
		}

		return;
	}
	else
	{

		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f;

		// �F�̐ݒ�
		CObject3D::SetCol(col);

		for (int i = 0; i < MAX_BODY; i++)
		{
			if (m_pBody[i] == nullptr)
			{// null�`�F�b�N
				continue;
			}

			// �F�̎擾
			D3DXCOLOR colBody = m_pBody[i]->GetCol();

			colBody.a = 1.0f;

			// �F�̐ݒ�
			m_pBody[i]->SetCol(colBody);
		}

		Target();

		// �ړ��ʂ̐ݒ�
		SetMove();

		D3DXVECTOR3 pos = CObject3D::GetPos();

		// �O��̈ʒu�̕ۑ�
		m_posOld = pos;

		pos.x += m_move.x;
		pos.y += m_move.y;

		D3DXVECTOR3 range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		range.x = ((float)CApplication::SCREEN_WIDTH * 0.5f) - (STD_SIZE * 0.5f);
		range.y = ((float)CApplication::SCREEN_HEIGHT * 0.5f) - (STD_SIZE * 0.5f);

		// �͈͓�
		InRange(&pos, range);

		// �ʒu�̐ݒ�
		CObject3D::SetPos(pos);
		m_pObj->SetPos(pos);

		if (m_pBody[IDX_PARENT] != nullptr)
		{// null�`�F�b�N
			// �ړI�̈ʒu�̐ݒ�
			m_pBody[IDX_PARENT]->SetPosDest(m_posOld);
		}

		for (int i = 0; i < MAX_BODY; i++)
		{
			if (m_pBody[i] == nullptr || i == IDX_PARENT)
			{// null�`�F�b�N
				continue;
			}

			int parent = i - 1;
			D3DXVECTOR3 posOld = m_pBody[parent]->GetPosOld();

			// �ړI�̈ʒu�̐ݒ�
			m_pBody[i]->SetPosDest(posOld);
		}

		// �����蔻��
		PlayerCollision();
		CircleCollision();
	}

	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CSnakeHead::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �O��̈ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CSnakeHead::GetPosOld() const
{
	return m_posOld;
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CSnakeHead::Set(const D3DXVECTOR3& pos, CSnakeBody** pBody)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	m_posOld = pos;

	m_pBody = pBody;

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Shape_Circle);

	// �ړ��ʂ̐ݒ�
	SetMove();

	{// �~
		m_pObj = CObject3D::Create();

		m_pObj->SetPos(pos);
		m_pObj->SetSize(D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE, 0.0f));
		m_pObj->SetTexture(CTexture::LABEL_Enemy_ver3_outside);
	}
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CSnakeHead::SetMove()
{
	float fRotMove, fRotDest, fRotDiff;

	// ���݂̈ړ�����(�p�x)
	fRotMove = atan2f(m_move.x, m_move.y);

	// �ړI�̈ړ�����(�p�x)
	fRotDest = atan2f(m_target.x - GetPos().x, m_target.y - GetPos().y);

	fRotDiff = fRotDest - fRotMove;	// �ړI�̈ړ������܂ł̍���

	// �p�x�̐��K��
	NormalizeAngle(&fRotDiff);

	fRotMove += fRotDiff;	// �ړ�����(�p�x)�̕␳

	// �p�x�̐��K��
	NormalizeAngle(&fRotMove);

	float sinCurve = sinf(D3DXToRadian(m_time * AMPLITUDE_SPEED)) * AMPLITUDE_WIDTH;

	m_move.x = (sinf(fRotMove) * (STD_MOVE + FloatRandom(STD_MOVE, 0.0f))) + (sinCurve * sinf(fRotMove + D3DX_PI * 0.5f));
	m_move.y = (cosf(fRotMove) * (STD_MOVE + FloatRandom(STD_MOVE, 0.0f))) + (sinCurve * cosf(fRotMove + D3DX_PI * 0.5f));

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move.x = (sinf(fRotMove) * STD_MOVE) + (sinCurve * sinf(fRotMove + D3DX_PI * 0.5f));
	move.y = (cosf(fRotMove) * STD_MOVE) + (sinCurve * cosf(fRotMove + D3DX_PI * 0.5f));

	float rot = atan2f(move.x, move.y);

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	// �����̐ݒ�
	CObject3D::SetRot(D3DXVECTOR3(0.0f, 0.0f, rot));
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CSnakeHead::Target()
{
	CGame* pGame = (CGame*)CApplication::GetInstance()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = OBJ_SIZE * 0.5f;
	D3DXVECTOR3 targetPos = pPlayer->GetPos();
	float targetSize = pPlayer->GetSize().x * 0.5f;

	D3DXCOLOR col = GetCol();

	if (CollisionCircle(pos, size, targetPos, targetSize))
	{// �����蔻��
		m_target = targetPos;
		m_chase = true;

		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (CollisionCircle(pos, size, m_target, targetSize))
	{
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.5f;

		m_target.x = FloatRandom(width, -width);
		m_target.y = FloatRandom(height, -height);

		m_chase = false;

		col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}

	SetCol(col);
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CSnakeHead::PlayerCollision()
{
	CGame* pGame = (CGame*)CApplication::GetInstance()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = STD_SIZE * 0.25f;
	D3DXVECTOR3 targetPos = pPlayer->GetPos();
	float targetSize = pPlayer->GetSize().x * 0.25f;

	if (CollisionCircle(pos, size, targetPos, targetSize))
	{// �����蔻��
		pPlayer->SetRelease();
		CPlayer::SetKill(true);
	}
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CSnakeHead::CircleCollision()
{
	if (!m_chase)
	{
		return;
	}

	CGame* pGame = (CGame*)CApplication::GetInstance()->GetMode();
	CCircle* pCircle = pGame->GetCircle();

	if (pCircle == nullptr)
	{// null�`�F�b�N
		return;
	}

	if (!pCircle->GetCollision())
	{
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = STD_SIZE * 0.35f;
	D3DXVECTOR3 targetPos = pCircle->GetPos();
	float targetSize = pCircle->GetSize().x * 0.35f;

	if (CollisionCircle(pos, size, targetPos, targetSize))
	{// �����蔻��
		SetRelease();

		for (int i = 0; i < MAX_BODY; i++)
		{
			if (m_pBody[i] == nullptr)
			{// null�`�F�b�N
				continue;
			}

			// ���
			m_pBody[i]->SetRelease();
		}

		m_pObj->SetRelease();

		pGame->AddScore(1);
	}
}
