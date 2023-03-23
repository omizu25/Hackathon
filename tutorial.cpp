//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "tutorial.h"
#include "input.h"
#include "sound.h"
#include "application.h"
#include "instancing.h"
#include "menu.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTutorial::CTutorial() :
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTutorial::~CTutorial()
{
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTutorial::Init()
{
	{// 背景
		CObject3D* pObj = CObject3D::Create();

		// 位置の設定
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// サイズの設定
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// 色の設定
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_TUTORIAL_BG);
	}

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.313f, (float)CApplication::SCREEN_HEIGHT * 0.92f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(350.0f, 50.0f, 0.0f);

		// 生成
		m_pMenu = CMenu::Create(pos, size, 1, 50.0f);

		// 枠の設定
		m_pMenu->SetFrame(pos, size + D3DXVECTOR3(300.0f, 10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		// テクスチャの設定
		m_pMenu->SetTexture(0, CTexture::LABEL_TITLE_PressEnter);
	}

	//曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Tutorial);
	CApplication::GetInstance()->GetSound()->SetVolume(CSound::LABEL_BGM_Tutorial,1.6f);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTutorial::Uninit()
{
	//曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu = nullptr;
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTutorial::Update()
{
	// 入力
	Input();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CTutorial::Draw()
{
}

//--------------------------------------------------
// 入力
//--------------------------------------------------
void CTutorial::Input()
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

	// モードの変更
	CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
}
