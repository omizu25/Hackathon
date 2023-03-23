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
		pObj->SetCol(D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_TITLE_BG);
	}

	{// ランキングのロゴ
		CObject2D* pObj = CObject2D::Create();

		pObj->SetPos(D3DXVECTOR3(320.0f, 70.0f, 0.0f));

		// サイズの設定
		pObj->SetSize(D3DXVECTOR3(600.f, 400.f, 0.0f));

		// 色の設定
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_RANKING_LOGO);
	}

	{// ランキング
		D3DXVECTOR3 pos = D3DXVECTOR3(520.f, 200.0f, 0.0f);

		// スコアの設定
		CRankingUI::SetScore(1);

		// 生成
		CRankingUI::Create(pos, 20.0f);
	}

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.75f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(500.0f, 400.0f, 0.0f);

		// 生成
		m_pMenu = CMenu::Create(pos, size, 2, 0.0f);

		// 枠の設定
		m_pMenu->SetFrame(pos, D3DXVECTOR3(500.f, 600.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		// カーソルの設定
		m_pMenu->SetCursor(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 20.0f);

		// テクスチャの設定
		m_pMenu->SetTexture(0, CTexture::LABEL_RANKING_RETURN_LOGO);

		// テクスチャの設定
		m_pMenu->SetTexture(1, CTexture::LABEL_RANKING_GO_LOGO);
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
