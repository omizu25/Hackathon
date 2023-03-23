//**************************************************
// 
// return.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "return.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "fade.h"
#include "mode.h"
#include "game.h"
#include "ranking_ui.h"
#include "effect.h"
#include "utility.h"
#include "sound.h"

//==================================================
// 定義
//==================================================
namespace
{
const int STD_TIME = 20;
const float STD_SIZE = 270.0f;
}

//==================================================
// 静的メンバ変数
//==================================================
float CReturn::m_move = 0.0f;
int CReturn::m_count = 0;

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CReturn::AddMove()
{
	m_move += 0.1f;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
float CReturn::GetMove()
{
	return m_move;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CReturn::CreateAll()
{
	m_move = 0.0f;
	D3DXVECTOR3 pos = D3DXVECTOR3(-STD_SIZE, -120.0f, 0.0f);

	m_count = CRankingUI::Get(-1);
	//m_count = 7;

	for (int i = 0; i < CRankingUI::Get(-1); i++)
		//for (int i = 0; i < 7; i++)
	{
		// 生成
		CReturn::Create(pos);

		pos.x -= STD_SIZE;
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CReturn* CReturn::Create(const D3DXVECTOR3& pos)
{
	CReturn* pDomino = new CReturn;

	if (pDomino == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pDomino->Init();

	// 位置の設定
	pDomino->SetPos(pos);

	return pDomino;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CReturn::CReturn()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CReturn::~CReturn()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CReturn::Init()
{
	m_time = 0;
	u = D3DXVECTOR2(0.0f, 0.5f);
	m_effect = false;

	// 初期化
	CObject3D::Init();

	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// 使用するモデルの設定
	CObject3D::SetTexture(CTexture::LABEL_RESULT_SnakeAnim);

	CObject3D::SetVtxTex(u, D3DXVECTOR2(0.0f, 1.0f));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CReturn::Uninit()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 終了
	CObject3D::Uninit();

	m_count--;

	if (m_count <= 0)
	{
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RANKING);
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CReturn::Update()
{
	m_time++;

	if (m_time >= STD_TIME)
	{
		u.x += 0.5f;
		u.y += 0.5f;
		CObject3D::SetVtxTex(u, D3DXVECTOR2(0.0f, 1.0f));
	}

	// 位置の取得
	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos.x += m_move;

	// 位置の設定
	CObject3D::SetPos(pos);

	if (!m_effect)
	{
		if (pos.x >= (float)CApplication::SCREEN_WIDTH * 0.25f)
		{
			CEffect::Enemy(pos);
			CEffect::Bom(pos);
			CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_Explosion);
			m_effect = true;
		}
	}
		

	if (pos.x >= (float)CApplication::SCREEN_WIDTH)
	{// 範囲外に出た
		CObject::SetRelease();
	}

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CReturn::Draw()
{
	// 描画
	CObject3D::Draw();
}
