//**************************************************
// 
// circle.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "circle.h"
#include "utility.h"
#include "application.h"
#include "player.h"

//==================================================
// 定義
//==================================================
namespace
{
const int STD_TIME = 100;
const float STD_SIZE = 300.0f;	// サイズ
}

const int CCircle::COUNTDOWN_TIME = 120;
const int CCircle::MAX_LIFE = 1200;
const D3DXCOLOR CCircle::STD_COLOR = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR CCircle::START_COLOR = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CCircle::END_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR CCircle::DIFF_COLOR = END_COLOR - START_COLOR;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CCircle* CCircle::Create()
{
	CCircle* pEnemy = new CCircle;

	if (pEnemy == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pEnemy->Init();

	return pEnemy;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CCircle::CCircle() :
	m_time(0),
	m_changeCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_appear(false)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCircle::~CCircle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CCircle::Init()
{
	m_time = 0;
	m_changeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_appear = false;

	// 初期化
	CObject3D::Init();

	// 位置の設定
	CObject3D::SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// 色の設定
	CObject3D::SetCol(m_changeCol);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Shape_Circle);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CCircle::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CCircle::Update()
{
	if (CPlayer::GetKill())
	{
		return;
	}

	m_time++;

	if (m_time >= STD_TIME)
	{
		m_time = 0;
		m_appear = !m_appear;
		D3DXCOLOR col = GetCol();

		if (m_appear)
		{
			col.a = 1.0f;

			float width = (float)CApplication::SCREEN_WIDTH * 0.35f;
			float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pos.x = FloatRandom(width, -width);
			pos.y = FloatRandom(height, -height);

			float size = FloatRandom(STD_SIZE, STD_SIZE * 0.25f);

			SetSize(D3DXVECTOR3(size, size, 0.0f));

			SetPos(pos);
		}
		else
		{
			col.a = 0.0f;
		}

		CObject3D::SetCol(col);

	}

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CCircle::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 当たり判定するかどうか
//--------------------------------------------------
bool CCircle::GetCollision()
{
	return m_appear;
}

//--------------------------------------------------
// 出現か消滅
//--------------------------------------------------
void CCircle::Appear()
{
}
