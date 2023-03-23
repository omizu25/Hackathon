//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "texture.h"
#include "application.h"

//==================================================
// 定義
//==================================================
namespace
{
const string FILE_PATH[] =
{// テクスチャのパス
	"data/TEXTURE/effect.png",				// エフェクト
	"data/TEXTURE/Cursor.png",				// カーソル
	"data/TEXTURE/Number.png",				// 数字
	"data/TEXTURE/Enemy.png",				// 敵
	"data/TEXTURE/Enemy_ver2.png",			// 敵ver.2
	"data/TEXTURE/Enemy_ver3_inside.png",	// 敵ver.3_内側
	"data/TEXTURE/Enemy_ver3_outside.png",	// 敵ver.3_外側
	"data/TEXTURE/Player.png",				// プレイヤー
	"data/TEXTURE/UI_Snake.png",			// 蛇の数(UI)
	"data/TEXTURE/Shape_Circle.png",		// 図形(円)
	"data/TEXTURE/Shape_Square.png",		// 図形(四角)
	"data/TEXTURE/Shape_Triangle.png",		// 図形(三角)
	"data/TEXTURE/Time.png",				// タイム
	"data/TEXTURE/Life.png",				// ライフ
	"data/TEXTURE/Frame_Space.png",			// 宇宙フレーム
	"data/TEXTURE/circle.png",				// サークル

	/* ↓タイトル↓ */
	"data/TEXTURE/Title/BG.png",			// 背景
	"data/TEXTURE/Title/Snake.png",			// 蛇
	"data/TEXTURE/Title/PressEnter.png",	// PressEnter
	"data/TEXTURE/Title/Logo.png",			// ロゴ

	/* ↓ランキング↓ */
	"data/TEXTURE/Ranking/RankingLogo.png",			// ロゴ
	"data/TEXTURE/Ranking/RankingReturnLogo.png",	// ロゴ
	"data/TEXTURE/Ranking/RankingGoLogo.png",	// ロゴ

	/* ↓リザルト↓ */
	"data/TEXTURE/Result/Snake_Anim.png",	//アニメーション蛇
};
}

static_assert(sizeof(FILE_PATH) / sizeof(FILE_PATH[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture()
{
	memset(m_pTexture, 0, sizeof(m_pTexture));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// 読み込み
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_PATH[label].c_str(),
		&m_pTexture[label]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// 破棄
		Release((ELabel)i);
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// テクスチャの解放
		m_pTexture[label]->Release();
		m_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(label > LABEL_NONE && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return m_pTexture[label];
}
