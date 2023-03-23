//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "game.h"
#include "sound.h"
#include "input.h"
#include "application.h"
#include "fade.h"
#include "object3D.h"
#include "effect.h"
#include "player.h"
#include "enemy_manager.h"
#include "circle.h"
#include "number_manager.h"
#include "ranking_ui.h"

//==================================================
// 静的メンバ変数宣言
//==================================================
CPlayer* CGame::m_pPlayer = nullptr;	//プレイヤー
CCircle* CGame::m_pCircle = nullptr;	//プレイヤー
int CGame::m_score = 0;

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CGame::CGame()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// プレイヤーの取得
//--------------------------------------------------
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//--------------------------------------------------
// プレイヤーの取得
//--------------------------------------------------
CCircle* CGame::GetCircle()
{
	return m_pCircle;
}

//--------------------------------------------------
// プレイヤーの取得
//--------------------------------------------------
void CGame::AddScore(int score)
{
	m_score += score;
}

//--------------------------------------------------
// プレイヤーの取得
//--------------------------------------------------
int CGame::GetScore()
{
	return m_score;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	//各メンバ変数の初期化
	m_time = 0;
	m_score = 0;
	m_bUse_SE = false;

	{// 背景
		CObject3D* pObj = CObject3D::Create();

		// 位置の設定
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// サイズの設定
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// 色の設定
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_Frame_Space);
	}

	{// スコア
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.27f, size.y * 0.65f, 0.0f);

		// 生成
		m_pTime = CNumberManager::Create(pos, size, 60);

		//スコア用UIの生成
		CObject2D* pScore = CObject2D::Create();

		// 位置の設定
		pScore->SetPos(D3DXVECTOR3(1045.0f, 65.0f, 0.0f));

		// サイズの設定
		pScore->SetSize(D3DXVECTOR3(170.0f, 170.0f, 0.0f));

		// 色の設定
		pScore->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャの設定
		pScore->SetTexture(CTexture::LABEL_UI_Stake);
	}

	{// タイム
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH - 30.0f, size.y * 0.65f, 0.0f);

		// 生成
		m_pScore = CNumberManager::Create(pos, size, 0);

		//タイム用UIの生成
		CObject2D* pTime = CObject2D::Create();

		// 位置の設定
		pTime->SetPos(D3DXVECTOR3(120.0f, 68.0f, 0.0f));

		// サイズの設定
		pTime->SetSize(D3DXVECTOR3(200.0f, 150.0f, 0.0f));

		// 色の設定
		pTime->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャの設定
		pTime->SetTexture(CTexture::LABEL_Time);
	}

	// サークル
	m_pCircle = CCircle::Create();

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	{// 残機
		int nLife = CPlayer::GetLife();

		for (int i = 0; i < nLife; i++)
		{
			pObjPlayer[i] = CObject2D::Create();

			// 位置の設定
			float fPosX = CApplication::SCREEN_WIDTH / 2 - 70.0f;
			pObjPlayer[i]->SetPos(D3DXVECTOR3(fPosX + (70.0f * i), 70.0f, 0.0f));

			// サイズの設定
			pObjPlayer[i]->SetSize(D3DXVECTOR3(70.0f, 70.0f, 0.0f));

			// 色の設定
			pObjPlayer[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// テクスチャの設定
			pObjPlayer[i]->SetTexture(CTexture::LABEL_Player);
		}
	}

	// 生成
	CEnemyManager::Create();

	// 曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Game);
	CApplication::GetInstance()->GetSound()->SetVolume(CSound::LABEL_BGM_Game, 0.5f);
	CApplication::GetInstance()->GetSound()->SetRate(CSound::LABEL_BGM_Game, 1.0f);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	// 曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	// スコアの設定
	CRankingUI::SetScore(m_score);

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	m_time++;

	if (m_time % 60 == 0)
	{
		m_pTime->Add(-1);

		if (!m_bUse_SE &&
			m_pTime->Get() <= 10)
		{
			CApplication::GetInstance()->GetSound()->SetVolume(CSound::LABEL_SE_Waring, 2.0f);
			CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_Waring);
			m_bUse_SE = true;
			CApplication::GetInstance()->GetSound()->SetRate(CSound::LABEL_BGM_Game, 1.2f);
		}

		if (m_pTime->Get() <= 0)
		{
			m_pTime->Set(0);

			// モードの変更
			CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RESULT);
		}
	}

	m_pScore->Set(m_score);

	DeathPlayer();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
}

//--------------------------------------------------
// 残機を減らす処理
//--------------------------------------------------
void CGame::DeathPlayer()
{
	int nLife = CPlayer::GetLife();

	for (int i = 2; i > nLife - 1; i--)
	{
		pObjPlayer[i]->SetRelease();
	}
}