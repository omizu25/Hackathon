//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "ranking.h"
#include "menu.h"
#include "application.h"
#include "instancing.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"
#include "sound.h"
#include "input.h"
#include "number_manager.h"
#include "ranking_ui.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CRanking::CRanking() :
	m_pMenu(nullptr),
	m_pScore(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRanking::~CRanking()
{
	assert(m_pMenu == nullptr);
	assert(m_pScore == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CRanking::Init()
{
	{// 背景
		CObject3D* pObj = CObject3D::Create();

		// 位置の設定
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// サイズの設定
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// 色の設定
		pObj->SetCol(D3DXCOLOR(0.5f, 0.0f, 0.5f, 1.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_NONE);
	}

	{// スコア
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, size.y * 0.5f, 0.0f);

		// 生成
		m_pScore = CNumberManager::Create(pos, size, 0);
	}

	{// ランキング
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, 200.0f, 0.0f);

		// スコアの設定
		CRankingUI::SetScore(1);

		// 生成
		CRankingUI::Create(pos, 20.0f);
	}

	// 曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRanking::Uninit()
{
	//曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu = nullptr;
	}

	if (m_pScore != nullptr)
	{// nullチェック
		m_pScore = nullptr;
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CRanking::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_F1))
	{// キーが押された
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_TITLE);
	}

	if (m_pScore != nullptr)
	{// nullチェック
		m_pScore->Add(1);
	}

	// 入力
	Input();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CRanking::Draw()
{
}

//--------------------------------------------------
// 入力
//--------------------------------------------------
void CRanking::Input()
{
	if (m_pMenu == nullptr)
	{// nullチェック
		return;
	}

	int select = m_pMenu->Select();

	if (select == -1)
	{// 入力されていない
		return;
	}

	if (select == 0)
	{
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
	}
	else
	{
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_TITLE);
	}
}
