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

//-----------------------------
// 定義
//-----------------------------
namespace
{
	float fSpeed = 3.0f;	//速度
}

//-----------------------------
// 静的メンバ変数
//-----------------------------
bool CPlayer::m_kill = false;

//===============================
// コンストラクタ
//===============================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//大きさ
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
	//オブジェクトの初期化
	CObject3D::Init();

	//初期値の設定
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);	//大きさ

	//プレイヤー情報の設定
	CObject3D::SetSize(m_size);	//大きさ
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

	//移動
	D3DXVECTOR3 move = Move(DIK_W, DIK_S, DIK_A, DIK_D);

	//----------------------
	// 移動量を更新(減衰)
	//----------------------
	m_move.x += (0.0f - move.x) * 0.4f;
	m_move.y += (0.0f - move.y) * 0.4f;

	//位置に移動量を加算
	m_pos += m_move;

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
void CPlayer::SetKill(bool kill)
{
	m_kill = kill;
}

//===============================
// 取得
//===============================
bool CPlayer::GetKill()
{
	return m_kill;
}

//===============================
// 移動
// 引数：上下左右キー
//===============================
D3DXVECTOR3 CPlayer::Move(int nUp, int nDown, int nLeft, int nRight)
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Press(nLeft))
	{//左キーが押された
		//-------------------------
		// 左上移動
		//-------------------------
		if (pInput->Press(nUp))
		{//上キーが押された
			m_move.x += sinf(-D3DX_PI * 0.75f) * fSpeed;
			m_move.y += cosf(-D3DX_PI * 0.25f) * fSpeed;
		}
		//-------------------------
		// 左下移動
		//-------------------------
		else if (pInput->Press(nDown))
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
	else if (pInput->Press(nRight))
	{//右キーが押された
		//-------------------------
		// 右上移動
		//-------------------------
		if (pInput->Press(nUp))
		{//上キーが押された
			m_move.x += sinf(D3DX_PI * 0.25f) * fSpeed;
			m_move.y += cosf(D3DX_PI * 0.25f) * fSpeed;
		}
		//-------------------------
		// 右下移動
		//-------------------------
		else if (pInput->Press(nDown))
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
	else if (pInput->Press(nUp))
	{//上キーが押された
		m_move.y += cosf(D3DX_PI * 0.0f) * fSpeed;
	}
	//-------------------------
	// 下移動
	//-------------------------
	else if (pInput->Press(nDown))
	{//下キーが押された
		m_move.y += cosf(-D3DX_PI * 1.0f) * fSpeed;
	}

	return m_move;
}