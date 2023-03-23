//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "effect.h"
#include "application.h"
#include "utility.h"

//==================================================
// 定義
//==================================================
namespace
{
const int MAX_EXPLOSION = 1000;	// 爆発の最大数
const int MAX_LIFE = 100;		// 寿命の最大値
const float STD_MOVE = 5.0f;	// 移動量の最大値
const float STD_SIZE = 12.0f;	// サイズの標準値
}

//==================================================
// 静的メンバ変数
//==================================================
CEffect* CEffect::m_pEffect[MAX_EFFECT] = {};
int CEffect::m_numAll = 0;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col)
{
	if (m_numAll >= MAX_EFFECT
		)
	{// 最大数を越した
		return nullptr;
	}

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;
	
	if (pEffect != nullptr)
	{// nullチェック
		pEffect->Init();
		pEffect->m_pos = pos;
		pEffect->m_move = move;
		pEffect->m_col = col;
	}

	return pEffect;
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CEffect::ReleaseAll()
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (m_pEffect[i] != nullptr)
		{// NULLチェック
			m_pEffect[i]->Uninit();
			m_pEffect[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 全ての更新
//--------------------------------------------------
void CEffect::UpdateAll()
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (m_pEffect[i] != nullptr)
		{// NULLチェック
			m_pEffect[i]->Update();
		}
	}
}

//--------------------------------------------------
// 総数の取得
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// エフェクトの情報の取得
//--------------------------------------------------
CEffect** CEffect::GetEffect()
{
	assert(m_numAll >= 0 && m_numAll <= MAX_EFFECT);

	return m_pEffect;
}

//--------------------------------------------------
// 爆発
//--------------------------------------------------
void CEffect::Explosion(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	col.r = FloatRandom(1.0f, 0.0f);
	col.g = FloatRandom(1.0f, 0.0f);
	col.b = FloatRandom(1.0f, 0.0f);

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR randomCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_EXPLOSION * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, -50.0f);

		random = FloatRandom(STD_MOVE, STD_MOVE * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandom(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandom(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandom(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos + randomPos, move, randomCol);
	}
}

//--------------------------------------------------
// プレイヤー
//--------------------------------------------------
void CEffect::Player(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < 500; i++)
	{
		rot = (D3DX_PI * 2.0f) / 500 * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(100.0f, 50.0f);

		random = FloatRandom(50.0f, 50.0f * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = 1.0f + FloatRandom(0.0f, -0.25f);
		col.g = 1.0f + FloatRandom(0.0f, -0.25f);
		col.b = 1.0f + FloatRandom(0.0f, -0.25f);

		// 生成
		CEffect::Create(pos + randomPos, move, col);
	}
}

//--------------------------------------------------
// 爆発
//--------------------------------------------------
void CEffect::Enemy(const D3DXVECTOR3& pos)
{
	float red = FloatRandom(1.0f, 0.0f);
	float green = FloatRandom(1.0f, 0.0f);
	float blue = FloatRandom(1.0f, 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 randomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	float random = 0.0f;

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_EXPLOSION * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(75.0f, 50.0f);

		random = FloatRandom(10.0f, 10.0f * 0.5f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = red + FloatRandom(0.25f, -0.25f);
		col.g = green + FloatRandom(0.25f, -0.25f);
		col.b = blue + FloatRandom(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos + randomPos, move, col);
	}

	for (int i = 0; i < (MAX_EXPLOSION / 2); i++)
	{
		rot = (D3DX_PI * 2.0f) / (MAX_EXPLOSION / 2) * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		randomPos = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(75.0f, 50.0f);

		random = FloatRandom(10.0f, 10.0f * 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = red + FloatRandom(0.25f, -0.25f);
		col.g = green + FloatRandom(0.25f, -0.25f);
		col.b = blue + FloatRandom(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos + randomPos, move, col);
	}
}

//--------------------------------------------------
// ボム
//--------------------------------------------------
void CEffect::Bom(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;
	CEffect* pEffect = nullptr;

	for (int i = 0; i < 500; i++)
	{
		rot = (D3DX_PI * 2.0f) / 500 * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		{// 外側
			move.x = sinf(rot) * 70.0f;
			move.y = cosf(rot) * 70.0f;

			// 生成
			pEffect = CEffect::Create(pos, move, col);
		}

		{// 内側
			move.x = sinf(rot) * (70.0f * 0.75f);
			move.y = cosf(rot) * (70.0f * 0.75f);

			// 生成
			pEffect = CEffect::Create(pos, move, col);
		}
	}
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffect::CEffect() :
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_life(0)
{
	assert(m_numAll >= 0 && m_numAll <= MAX_EFFECT);

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (m_pEffect[i] == nullptr)
		{// NULLチェック
			m_pEffect[i] = this;
			m_index = i;
			m_numAll++;
			break;
		}
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEffect::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(STD_SIZE, STD_SIZE);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_life = MAX_LIFE;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEffect::Uninit()
{
	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEffect::Update()
{
	m_life--;

	if (m_life <= 0)
	{
		// 終了
		Uninit();
		return;
	}

	m_pos += m_move;

	//慣性・移動量を更新 (減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.05f;
	m_move.y += (0.0f - m_move.y) * 0.05f;

	{// 色の減算
		float ratio = ((float)(MAX_LIFE - m_life) / MAX_LIFE);
		m_col.a = 1.0f - (ratio * ratio);
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CEffect::Release()
{
	if (m_pEffect[m_index] != nullptr)
	{// NULLチェック
		int index = m_index;
		delete m_pEffect[index];
		m_pEffect[index] = nullptr;
	}
}

//--------------------------------------------------
// 位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
const D3DXCOLOR& CEffect::GetCol() const
{
	return m_col;
}

//--------------------------------------------------
// 移動量の取得
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetMove() const
{
	return m_move;
}

//--------------------------------------------------
// サイズの取得
//--------------------------------------------------
const D3DXVECTOR2& CEffect::GetSize() const
{
	return m_size;
}
