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

//===============================
// コンストラクタ
//===============================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
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