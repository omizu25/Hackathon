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

//==================================================
// 静的メンバ変数宣言
//==================================================
CPlayer* CGame::m_pPlayer = nullptr;	//プレイヤー

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
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	{// 背景
		CObject3D* pObj = CObject3D::Create();

		// 位置の設定
		pObj->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// サイズの設定
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// 色の設定
		pObj->SetCol(D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_NONE);

		//プレイヤーの生成
		m_pPlayer = CPlayer::Create();
	}

	// 曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Game);}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	// 曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_F1))
	{// キーが押された
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RESULT);
	}
	else if (pInput->Trigger(DIK_F2))
	{// キーが押された
		CEffect::Explosion(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
}
