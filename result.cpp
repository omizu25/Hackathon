//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "result.h"
#include "input.h"
#include "sound.h"
#include "application.h"
#include "object3D.h"
#include "fade.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CResult::CResult()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CResult::Init()
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

	{// 洞窟(左)
		CObject3D* pLeft = CObject3D::Create();

		// 位置の設定
		pLeft->SetPos(D3DXVECTOR3(300.0f, -10.0f, 0.0f));

		// サイズの設定
		pLeft->SetSize(D3DXVECTOR3(430.0f, 430.0f, 0.0f));

		// 色の設定
		pLeft->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャの設定
		pLeft->SetTexture(CTexture::LABEL_RESULT_CaveLeft);
	}

	{// 洞窟(右)
		CObject2D* pLeft = CObject2D::Create();

		// 位置の設定
		pLeft->SetPos(D3DXVECTOR3(939.0f, 365.0f, 0.0f));

		// サイズの設定
		pLeft->SetSize(D3DXVECTOR3(410.0f, 410.0f, 0.0f));

		// 色の設定
		pLeft->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャの設定
		pLeft->SetTexture(CTexture::LABEL_RESULT_CaveRight);
	}

	{// 蛇
		CObject2D* pSnake = CObject2D::Create();

		// 位置の設定
		pSnake->SetPos(D3DXVECTOR3(300.0f, 365.0f, 0.0f));

		// サイズの設定
		pSnake->SetSize(D3DXVECTOR3(500.0f, 200.0f, 0.0f));

		// 色の設定
		pSnake->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャの設定
		pSnake->SetTexture(CTexture::LABEL_RESULT_SnakeAnim);
	}

	//曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CResult::Uninit()
{
	//曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CResult::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(DIK_F1))
	{// キーが押された
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RANKING);
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CResult::Draw()
{
}
