//**************************************************
// 
// snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "snake_body.h"
#include "utility.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "circle.h"

//==================================================
// 定義
//==================================================
const float CSnakeBody::STD_SIZE = 10.0f;
const int CSnakeBody::MOVE_INTERVAL = 2;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CSnakeBody* CSnakeBody::Create()
{
	CSnakeBody* pBody = nullptr;

	pBody = new CSnakeBody;

	if (pBody != nullptr)
	{// nullチェック
		pBody->Init();
	}

	return pBody;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CSnakeBody::CSnakeBody() :
	m_time(0),
	m_posDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CSnakeBody::~CSnakeBody()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CSnakeBody::Init()
{
	m_time = 0;

	// 初期化
	CObject3D::Init();

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_NONE);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CSnakeBody::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CSnakeBody::Update()
{
	m_time++;

	if ((m_time % MOVE_INTERVAL) != 0)
	{// 一定間隔のタイミングではない
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 前回の位置の保存
	m_posOld = pos;

	// ホーミング
	Homing(&pos, pos, m_posDest, 10.0f);

	D3DXVECTOR3 range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	range.x = ((float)CApplication::SCREEN_WIDTH * 0.5f) - (STD_SIZE * 0.5f);
	range.y = ((float)CApplication::SCREEN_HEIGHT * 0.5f) - (STD_SIZE * 0.5f);

	// 範囲内
	InRange(&pos, range);

	// 位置の設定
	CObject3D::SetPos(pos);

	// 当たり判定
	Collision();

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CSnakeBody::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 目的の位置の設定
//--------------------------------------------------
void CSnakeBody::SetPosDest(const D3DXVECTOR3& posDest)
{
	m_posDest = posDest;
}

//--------------------------------------------------
// 前回の位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CSnakeBody::GetPosOld() const
{
	return m_posOld;
}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CSnakeBody::Collision()
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
		CPlayer::SetKill(true);
	}
}
