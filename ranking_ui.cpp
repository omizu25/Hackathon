//**************************************************
// 
// ranking_ui.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "ranking_ui.h"
#include "number_manager.h"
#include "number.h"
#include "object2D.h"
#include "utility.h"

//==================================================
// ��`
//==================================================
namespace
{
static const float NUM_WIDTH = 60.0f;	// ���̕�
static const float NUM_HEIGHT = 80.0f;	// ���̍���
static const float RANK_SIZE = 60.0f;	// �ʂ̃T�C�Y
static const float RANK_INTERVAL = (NUM_WIDTH * CNumberManager::MAX_DIGIT) + (RANK_SIZE * 0.5f);	// �ʂ̊Ԋu
const string FILE_PATH = "data/TEXT/Ranking.txt";	// �e�L�X�g�̃p�X
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CRankingUI::m_score = 0;
int CRankingUI::m_ranking[MAX_RANKING] = {};

//--------------------------------------------------
// ����
//--------------------------------------------------
CRankingUI* CRankingUI::Create(const D3DXVECTOR3& pos, float length)
{
	CRankingUI* pRanking = nullptr;

	pRanking = new CRankingUI;

	if (pRanking != nullptr)
	{// null�`�F�b�N
		// ������
		pRanking->Init();

		// �ݒ�
		pRanking->Set(pos, length);
	}

	return pRanking;
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CRankingUI::SetScore(int score)
{
	m_score = score;

	// �ǂݍ���
	Load();

	// �ύX
	Change();

	// �ۑ�
	Save();
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int CRankingUI::Get(int rank)
{
	if (rank == -1)
	{// �w��̒l
		return m_score;
	}

	assert(rank >= 0 && rank < MAX_RANKING);

	// �ǂݍ���
	Load();

	return m_ranking[rank];
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CRankingUI::Load()
{
	FILE *pFile = nullptr;

	// �t�@�C�����J��
	pFile = fopen(FILE_PATH.c_str(), "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fscanf(pFile, "%d", &m_ranking[i]);
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		assert(false);
	}
}

//--------------------------------------------------
// �ۑ�
//--------------------------------------------------
void CRankingUI::Save()
{
	FILE *pFile = nullptr;

	// �t�@�C�����J��
	pFile = fopen(FILE_PATH.c_str(), "w");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fprintf(pFile, "%d\n\n", m_ranking[i]);
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		assert(false);
	}
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void CRankingUI::Change()
{
	int ranking[MAX_RANKING + 1] = {};

	for (int i = 0; i < MAX_RANKING; i++)
	{
		ranking[i] = m_ranking[i];
	}

	ranking[MAX_RANKING] = m_score;

	int save = 0;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		save = ranking[i];

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save < ranking[j])
			{// ���肪�傫����������
				save = ranking[j];
			}
		}

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save == ranking[j])
			{// �ő�l��T���Č��
				ranking[j] = ranking[i];
				ranking[i] = save;
				break;
			}
		}
	}

	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_ranking[i] = ranking[i];
	}
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CRankingUI::CRankingUI(): CObject(CObject::PRIORITY_SYSTEM),
	m_newRank(0),
	m_time(0)
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_pRanking[i] = nullptr;
		m_pRank[i] = nullptr;
		m_pNumber[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CRankingUI::~CRankingUI()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		assert(m_pRanking[i] == nullptr);
		assert(m_pNumber[i] == nullptr);
		assert(m_pRank[i] == nullptr);
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CRankingUI::Init()
{
	m_time = 0;
	m_newRank = 0;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_pRanking[i] = nullptr;
		m_pRank[i] = nullptr;
		m_pNumber[i] = nullptr;
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CRankingUI::Uninit()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_pRanking[i] != nullptr)
		{// null�`�F�b�N
			m_pRanking[i] = nullptr;
		}

		if (m_pRank[i] != nullptr)
		{// null�`�F�b�N
			// �I��
			m_pRank[i]->Uninit();
			m_pRank[i] = nullptr;
		}

		if (m_pNumber[i] != nullptr)
		{// null�`�F�b�N
			// �I��
			m_pNumber[i]->Uninit();
			m_pNumber[i] = nullptr;
		}
	}

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CRankingUI::Update()
{
	if (m_newRank == -1)
	{// �w��̒l
		return;
	}

	m_time++;

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, 0.01f) * 0.9f);

	// �F�̐ݒ�
	m_pRanking[m_newRank]->SetCol(col);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CRankingUI::Draw()
{
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CRankingUI::Set(const D3DXVECTOR3& pos, float length)
{
	D3DXVECTOR3 size = D3DXVECTOR3(NUM_WIDTH, NUM_HEIGHT, 0.0f);

	float height = NUM_HEIGHT;

	if (length <= 0.0f)
	{// �l���}�C�i�X
		height *= -1.0f;
	}

	float posY = 0.0f;
	float rankPosX = 0.0f;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		posY = pos.y + (i * (length + height));

		// �X�R�A�̐���
		m_pRanking[i] = CNumberManager::Create(D3DXVECTOR3(pos.x, posY, 0.0f), size, m_ranking[i]);

		// �X�R�A�̐ݒ�
		m_pRanking[i]->Set(m_ranking[i]);

		rankPosX = pos.x - (RANK_SIZE * 0.5f) - RANK_INTERVAL;

		// �ʂ̐���
		m_pRank[i] = CObject2D::Create();
		m_pRank[i]->SetPos(D3DXVECTOR3(rankPosX, posY, 0.0f));
		m_pRank[i]->SetSize(D3DXVECTOR3(RANK_SIZE, RANK_SIZE, 0.0f));
		m_pRank[i]->SetTexture(CTexture::LABEL_Cursor);

		// ���ʂ̐���
		m_pNumber[i] = CNumber::Create(D3DXVECTOR3(rankPosX - RANK_SIZE, posY, 0.0f), size * 1.2f);
		m_pNumber[i]->Change(i + 1);
	}

	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_ranking[i] != m_score)
		{// �w��̒l�ł͂Ȃ�
			continue;
		}

		m_newRank = i;

		break;
	}
}
