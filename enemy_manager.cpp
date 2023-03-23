//**************************************************
// 
// enemy_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_manager.h"
#include "enemy.h"
#include "application.h"
#include "utility.h"
#include "snake_head.h"
#include "player.h"

//==================================================
// ��`
//==================================================
namespace
{
const int MIN_INTERVAL = 30;	// �Ԋu�̍ŏ��l
const int MAX_INTERVAL = 120;	// �Ԋu�̍ő�l
const int MAX_POP = 5;			// �G�̏o�����̍ő�l
}

//==================================================
// �ÓI�����o�ϐ��錾
//==================================================
int CEnemyManager::m_pop = 0;	//�o����

//--------------------------------------------------
// ����
//--------------------------------------------------
CEnemyManager* CEnemyManager::Create()
{
	CEnemyManager* pManager = nullptr;

	pManager = new CEnemyManager;

	if (pManager != nullptr)
	{// null�`�F�b�N
		// ������
		pManager->Init();
	}

	return pManager;
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CEnemyManager::CEnemyManager() : CObject(CObject::PRIORITY_SYSTEM),
	m_time(0),
	m_interval(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyManager::~CEnemyManager()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemyManager::Init()
{
	m_time = 0;
	m_interval = MAX_INTERVAL;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyManager::Uninit()
{
	// �j��
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyManager::Update()
{
	if (CPlayer::GetKill())
	{
		return;
	}

	m_time++;

	// �Q�[��
	Game();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemyManager::Draw()
{
}

//--------------------------------------------------
// �Q�[��
//--------------------------------------------------
void CEnemyManager::Game()
{
	if (m_time % m_interval != 0)
	{// ���Ԋu
		return;
	}

	float width = (float)CApplication::SCREEN_WIDTH * 0.35f;
	float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pos.x = FloatRandom(width, -width);
	pos.y = FloatRandom(height, -height);

	if (m_pop < MAX_POP)
	{//�ő吔�ȓ��Ȃ�
		// ����
		CSnakeHead::Create(pos);

		m_pop++;

	}

	m_interval--;

	if (m_interval <= MIN_INTERVAL)
	{// �ŏ��l�ȉ�
		m_interval = MIN_INTERVAL;
	}
}
