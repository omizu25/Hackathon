//**************************************************
// 
// ranking_ui.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "ranking_ui.h"
#include "number_manager.h"
#include "number.h"
#include "object2D.h"
#include "utility.h"

//==================================================
// 定義
//==================================================
namespace
{
static const float NUM_WIDTH = 60.0f;	// 数の幅
static const float NUM_HEIGHT = 80.0f;	// 数の高さ
static const float RANK_SIZE = 60.0f;	// 位のサイズ
static const float RANK_INTERVAL = (NUM_WIDTH * CNumberManager::MAX_DIGIT) + (RANK_SIZE * 0.5f);	// 位の間隔
const string FILE_PATH = "data/TEXT/Ranking.txt";	// テキストのパス
}

//==================================================
// 静的メンバ変数
//==================================================
int CRankingUI::m_score = 0;
int CRankingUI::m_ranking[MAX_RANKING] = {};

//--------------------------------------------------
// 生成
//--------------------------------------------------
CRankingUI* CRankingUI::Create(const D3DXVECTOR3& pos, float length)
{
	CRankingUI* pRanking = nullptr;

	pRanking = new CRankingUI;

	if (pRanking != nullptr)
	{// nullチェック
		// 初期化
		pRanking->Init();

		// 設定
		pRanking->Set(pos, length);
	}

	return pRanking;
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CRankingUI::SetScore(int score)
{
	m_score = score;

	// 読み込み
	Load();

	// 変更
	Change();

	// 保存
	Save();
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CRankingUI::Get(int rank)
{
	if (rank == -1)
	{// 指定の値
		return m_score;
	}

	assert(rank >= 0 && rank < MAX_RANKING);

	// 読み込み
	Load();

	return m_ranking[rank];
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CRankingUI::Load()
{
	FILE *pFile = nullptr;

	// ファイルを開く
	pFile = fopen(FILE_PATH.c_str(), "r");

	if (pFile != nullptr)
	{// ファイルが開いた場合

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fscanf(pFile, "%d", &m_ranking[i]);
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
	}
}

//--------------------------------------------------
// 保存
//--------------------------------------------------
void CRankingUI::Save()
{
	FILE *pFile = nullptr;

	// ファイルを開く
	pFile = fopen(FILE_PATH.c_str(), "w");

	if (pFile != nullptr)
	{// ファイルが開いた場合

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fprintf(pFile, "%d\n\n", m_ranking[i]);
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
	}
}

//--------------------------------------------------
// 変更
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
			{// 相手が大きかったら交代
				save = ranking[j];
			}
		}

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save == ranking[j])
			{// 最大値を探して交代
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
// デフォルトコンストラクタ
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
// デストラクタ
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
// 初期化
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
// 終了
//--------------------------------------------------
void CRankingUI::Uninit()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_pRanking[i] != nullptr)
		{// nullチェック
			m_pRanking[i] = nullptr;
		}

		if (m_pRank[i] != nullptr)
		{// nullチェック
			// 終了
			m_pRank[i]->Uninit();
			m_pRank[i] = nullptr;
		}

		if (m_pNumber[i] != nullptr)
		{// nullチェック
			// 終了
			m_pNumber[i]->Uninit();
			m_pNumber[i] = nullptr;
		}
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CRankingUI::Update()
{
	if (m_newRank == -1)
	{// 指定の値
		return;
	}

	m_time++;

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, 0.01f) * 0.9f);

	// 色の設定
	m_pRanking[m_newRank]->SetCol(col);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CRankingUI::Draw()
{
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CRankingUI::Set(const D3DXVECTOR3& pos, float length)
{
	D3DXVECTOR3 size = D3DXVECTOR3(NUM_WIDTH, NUM_HEIGHT, 0.0f);

	float height = NUM_HEIGHT;

	if (length <= 0.0f)
	{// 値がマイナス
		height *= -1.0f;
	}

	float posY = 0.0f;
	float rankPosX = 0.0f;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		posY = pos.y + (i * (length + height));

		// スコアの生成
		m_pRanking[i] = CNumberManager::Create(D3DXVECTOR3(pos.x, posY, 0.0f), size, m_ranking[i]);

		// スコアの設定
		m_pRanking[i]->Set(m_ranking[i]);

		rankPosX = pos.x - (RANK_SIZE * 0.5f) - RANK_INTERVAL;

		// 位の生成
		m_pRank[i] = CObject2D::Create();
		m_pRank[i]->SetPos(D3DXVECTOR3(rankPosX, posY, 0.0f));
		m_pRank[i]->SetSize(D3DXVECTOR3(RANK_SIZE, RANK_SIZE, 0.0f));
		m_pRank[i]->SetTexture(CTexture::LABEL_Cursor);

		// 順位の生成
		m_pNumber[i] = CNumber::Create(D3DXVECTOR3(rankPosX - RANK_SIZE, posY, 0.0f), size * 1.2f);
		m_pNumber[i]->Change(i + 1);
	}

	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_ranking[i] != m_score)
		{// 指定の値ではない
			continue;
		}

		m_newRank = i;

		break;
	}
}
