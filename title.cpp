//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "title.h"
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
CTitle::CTitle() :
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTitle::~CTitle()
{
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTitle::Init()
{
	{// 背景
		CObject3D* pObj = CObject3D::Create();

		// 位置の設定
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// サイズの設定
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// 色の設定
		pObj->SetCol(D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_TITLE_BG);
	}

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(450.0f, 100.0f, 0.0f);

		// 生成
		m_pMenu = CMenu::Create(pos, size, 1, 50.0f);

		// 枠の設定
		m_pMenu->SetFrame(pos, D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, 200.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		// カーソルの設定
		m_pMenu->SetCursor(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 20.0f);

		// テクスチャの設定
		m_pMenu->SetTexture(0, CTexture::LABEL_TITLE_PressEnter);
	}

	//曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Title);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTitle::Uninit()
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
void CTitle::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_F1))
	{// キーが押された
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
	}

	// 入力
	Input();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CTitle::Draw()
{
}

//--------------------------------------------------
// 入力
//--------------------------------------------------
void CTitle::Input()
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
