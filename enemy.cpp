//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy.h"
#include "application.h"
#include "utility.h"
#include "player.h"
#include "game.h"

//==================================================
// 定義
//==================================================
namespace
{
const int STD_TIME = 90;		// 発生時間
const float STD_MOVE = 5.0f;	// 移動速度
const float STD_SIZE = 40.0f;	// サイズ
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, float rot)
{
	CEnemy* pEnemy = new CEnemy;

	if (pEnemy == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pEnemy->Init();

	// 設定
	pEnemy->Set(pos, rot);

	return pEnemy;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemy::CEnemy() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemy::~CEnemy()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemy::Init()
{
	m_time = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 初期化
	CObject3D::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemy::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemy::Update()
{
	m_time++;

	if (m_time <= STD_TIME)
	{// 生成時間中

		// 色の取得
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = SinCurve(m_time, 0.1f);

		// 色の設定
		CObject3D::SetCol(col);

		// 更新
		CObject3D::Update();
		return;
	}
	else
	{
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f;

		// 色の設定
		CObject3D::SetCol(col);

		// 移動
		Move();

		// 当たり判定
		Collision();

		// 更新
		CObject3D::Update();
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemy::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemy::Set(const D3DXVECTOR3& pos, float rot)
{
	// 移動量の設定
	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;

	// 位置の設定
	CObject3D::SetPos(pos);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Enemy);
}

//--------------------------------------------------
// 移動
//--------------------------------------------------
void CEnemy::Move()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	D3DXVECTOR3 range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	range.x = ((float)CApplication::SCREEN_WIDTH * 0.5f) - (STD_SIZE * 0.5f);
	range.y = ((float)CApplication::SCREEN_HEIGHT * 0.5f) - (STD_SIZE * 0.5f);

	// 範囲内で反射
	InRangeReflect(&pos, &m_move, range);

	// 位置の設定
	CObject3D::SetPos(pos);
}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CEnemy::Collision()
{
	CGame* pGame = (CGame*)CApplication::GetInstance()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// nullチェック
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = STD_SIZE * 0.5f;
	D3DXVECTOR3 targetPos = pPlayer->GetPos();
	float targetSize = pPlayer->GetSize().x * 0.5f;

	if (CollisionCircle(pos, size, targetPos, targetSize))
	{// 当たり判定
		pPlayer->SetRelease();
	}
}
