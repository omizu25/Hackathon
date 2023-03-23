//==========================================
//
// プレイヤーの処理
// Author:Teruto Sato
//
//==========================================

//-----------------------------
// インクルード
//-----------------------------
#include "player.h"
#include "input.h"
#include "application.h"
#include "utility.h"
#include "fade.h"
#include "mode.h"
#include "sound.h"
#include "effect.h"

//-----------------------------
// 定義
//-----------------------------
namespace
{
	const float fSpeed = 3.0f;		//速度
	const float STD_SIZE = 30.0f;	// サイズ
}

//-----------------------------
// 静的メンバ変数
//-----------------------------
bool CPlayer::m_kill = false;
int CPlayer::m_life = 0;

//===============================
// コンストラクタ
//===============================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//大きさ
	m_time = 0;
	m_interval = false;
}

//===============================
// デストラクタ
//===============================
CPlayer::~CPlayer()
{
}

//===============================
// 初期化
//===============================
void CPlayer::Init()
{
	m_kill = true;

	//オブジェクトの初期化
	CObject3D::Init();

	//初期値の設定
	m_size = D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f);	//大きさ

	//プレイヤー情報の設定
	CObject3D::SetSize(m_size);	//大きさ

	//残機の設定
	SetLife();

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Player);
}

//===============================
// 終了
//===============================
void CPlayer::Uninit()
{
	//オブジェクトの終了
	CObject3D::Uninit();
}

//===============================
// 更新
//===============================
void CPlayer::Update()
{
	//オブジェクトの更新
	CObject3D::Update();

	if (m_interval)
	{
		m_time++;

		if (m_time >= 10)
		{
			
			CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_Hit);
			m_kill = true;
			m_interval = false;
			m_time = 0;
		}

		return;
	}

	if (m_kill)
	{
		m_time++;

		// 色の取得
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = SinCurve(m_time, 0.1f);

		// 色の設定
		CObject3D::SetCol(col);

		if (m_time >= 30)
		{
			CEffect::Bom(m_pos);
			m_kill = false;
			m_interval = false;
			m_time = 0;
		}

		return;
	}

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//移動
	D3DXVECTOR3 move = Move(DIK_W, DIK_S, DIK_A, DIK_D);

	//----------------------
	// 移動量を更新(減衰)
	//----------------------
	m_move.x += (0.0f - move.x) * 0.4f;
	m_move.y += (0.0f - move.y) * 0.4f;

	//位置に移動量を加算
	m_pos += m_move;

	D3DXVECTOR3 range = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	range.x = ((float)CApplication::SCREEN_WIDTH * 0.5f) - (STD_SIZE * 0.5f);
	range.y = ((float)CApplication::SCREEN_HEIGHT * 0.5f) - (STD_SIZE * 0.5f);

	// 範囲内で反射
	InRangeReflect(&m_pos, &m_move, range);

	//位置を設定
	CObject3D::SetPos(m_pos);
}

//===============================
// 描画
//===============================
void CPlayer::Draw()
{
	//オブジェクトの描画
	CObject3D::Draw();
}

//===============================
// 生成
//===============================
CPlayer* CPlayer::Create()
{
	CPlayer *pPlayer = nullptr;

	//-------------------------------
	// 生成と初期化
	//-------------------------------
	pPlayer = new CPlayer;	//生成

	if (pPlayer != nullptr)
	{//NULLチェック
		//初期化
		pPlayer->Init();
	}

	return pPlayer;
}

//===============================
// 設定
//===============================
void CPlayer::SetKill()
{
	if (m_interval)
	{
		return;
	}

	if (m_kill)
	{
		return;
	}

	CEffect::Player(m_pos);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//位置を設定
	CObject3D::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	m_kill = true;
	m_interval = true;
	m_life--;
	m_time = 0;

	if (m_life <= 0)
	{
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RESULT);
	}
}

//===============================
// 取得
//===============================
bool CPlayer::GetKill()
{
	return m_kill;
}

//===============================
// 設定
//===============================
void CPlayer::SetLife()
{
	m_life = 3;
}

//===============================
// 取得
//===============================
int CPlayer::GetLife()
{
	return m_life;
}

//===============================
// 移動
// 引数：上下左右キー
//===============================
D3DXVECTOR3 CPlayer::Move(int nUp, int nDown, int nLeft, int nRight)
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Press(nLeft) || pInput->Press(KEY_LEFT))
	{//左キーが押された
		//-------------------------
		// 左上移動
		//-------------------------
		if (pInput->Press(nUp) || pInput->Press(KEY_UP))
		{//上キーが押された
			m_move.x += sinf(-D3DX_PI * 0.75f) * fSpeed;
			m_move.y += cosf(-D3DX_PI * 0.25f) * fSpeed;
		}
		//-------------------------
		// 左下移動
		//-------------------------
		else if (pInput->Press(nDown) || pInput->Press(KEY_DOWN))
		{//下キーが押された
			m_move.x += sinf(-D3DX_PI * 0.25f) * fSpeed;
			m_move.y += cosf(D3DX_PI * 0.75f) * fSpeed;
		}
		//-------------------------
		// 左移動
		//-------------------------
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * fSpeed;
		}
	}
	else if (pInput->Press(nRight) || pInput->Press(KEY_RIGHT))
	{//右キーが押された
		//-------------------------
		// 右上移動
		//-------------------------
		if (pInput->Press(nUp) || pInput->Press(KEY_UP))
		{//上キーが押された
			m_move.x += sinf(D3DX_PI * 0.25f) * fSpeed;
			m_move.y += cosf(D3DX_PI * 0.25f) * fSpeed;
		}
		//-------------------------
		// 右下移動
		//-------------------------
		else if (pInput->Press(nDown) || pInput->Press(KEY_DOWN))
		{//下キーが押された
			m_move.x += sinf(D3DX_PI * 0.75f) * fSpeed;
			m_move.y += cosf(-D3DX_PI * 0.75f) * fSpeed;
		}
		//-------------------------
		// 右移動
		//-------------------------
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * fSpeed;
		}
	}
	//-------------------------
	// 上移動
	//-------------------------
	else if (pInput->Press(nUp) || pInput->Press(KEY_UP))
	{//上キーが押された
		m_move.y += cosf(D3DX_PI * 0.0f) * fSpeed;
	}
	//-------------------------
	// 下移動
	//-------------------------
	else if (pInput->Press(nDown) || pInput->Press(KEY_DOWN))
	{//下キーが押された
		m_move.y += cosf(-D3DX_PI * 1.0f) * fSpeed;
	}

	return m_move;
}