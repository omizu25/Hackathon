//**************************************************
// 
// enemy_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_manager.h"
#include "enemy.h"
#include "application.h"
#include "utility.h"
#include "snake_head.h"
#include "player.h"

//==================================================
// 定義
//==================================================
namespace
{
const int MIN_INTERVAL = 30;	// 間隔の最小値
const int MAX_INTERVAL = 120;	// 間隔の最大値
const int MAX_POP = 5;			// 敵の出現数の最大値
}

//==================================================
// 静的メンバ変数宣言
//==================================================
int CEnemyManager::m_pop = 0;	//出現数

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEnemyManager* CEnemyManager::Create()
{
	CEnemyManager* pManager = nullptr;

	pManager = new CEnemyManager;

	if (pManager != nullptr)
	{// nullチェック
		// 初期化
		pManager->Init();
	}

	return pManager;
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CEnemyManager::CEnemyManager() : CObject(CObject::PRIORITY_SYSTEM),
	m_time(0),
	m_interval(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyManager::~CEnemyManager()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyManager::Init()
{
	m_time = 0;
	m_interval = MAX_INTERVAL;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyManager::Uninit()
{
	// 破棄
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyManager::Update()
{
	if (CPlayer::GetKill())
	{
		return;
	}

	m_time++;

	// ゲーム
	Game();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemyManager::Draw()
{
}

//--------------------------------------------------
// ゲーム
//--------------------------------------------------
void CEnemyManager::Game()
{
	if (m_time % m_interval != 0)
	{// 一定間隔
		return;
	}

	float width = (float)CApplication::SCREEN_WIDTH * 0.35f;
	float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pos.x = FloatRandom(width, -width);
	pos.y = FloatRandom(height, -height);

	if (m_pop < MAX_POP)
	{//最大数以内なら
		// 生成
		CSnakeHead::Create(pos);

		m_pop++;

	}

	m_interval--;

	if (m_interval <= MIN_INTERVAL)
	{// 最小値以下
		m_interval = MIN_INTERVAL;
	}
}
