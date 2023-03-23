//**************************************************
// 
// snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "snake_body.h"
#include "utility.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "circle.h"

//==================================================
// ��`
//==================================================
const float CSnakeBody::STD_SIZE = 10.0f;
const int CSnakeBody::MOVE_INTERVAL = 2;

//--------------------------------------------------
// ����
//--------------------------------------------------
CSnakeBody* CSnakeBody::Create()
{
	CSnakeBody* pBody = nullptr;

	pBody = new CSnakeBody;

	if (pBody != nullptr)
	{// null�`�F�b�N
		pBody->Init();
	}

	return pBody;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CSnakeBody::CSnakeBody() :
	m_time(0),
	m_posDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CSnakeBody::~CSnakeBody()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CSnakeBody::Init()
{
	m_time = 0;

	// ������
	CObject3D::Init();

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_NONE);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CSnakeBody::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CSnakeBody::Update()
{
	m_time++;

	if ((m_time % MOVE_INTERVAL) != 0)
	{// ���Ԋu�̃^�C�~���O�ł͂Ȃ�
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �O��̈ʒu�̕ۑ�
	m_posOld = pos;

	// �z�[�~���O
	Homing(&pos, pos, m_posDest, 10.0f);

	D3DXVECTOR3 range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	range.x = ((float)CApplication::SCREEN_WIDTH * 0.5f) - (STD_SIZE * 0.5f);
	range.y = ((float)CApplication::SCREEN_HEIGHT * 0.5f) - (STD_SIZE * 0.5f);

	// �͈͓�
	InRange(&pos, range);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �����蔻��
	Collision();

	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CSnakeBody::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �ړI�̈ʒu�̐ݒ�
//--------------------------------------------------
void CSnakeBody::SetPosDest(const D3DXVECTOR3& posDest)
{
	m_posDest = posDest;
}

//--------------------------------------------------
// �O��̈ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CSnakeBody::GetPosOld() const
{
	return m_posOld;
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CSnakeBody::Collision()
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
		CPlayer::SetKill(true);
	}
}
