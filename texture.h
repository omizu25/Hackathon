//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// クラス
//==================================================
class CTexture
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,		// 使用しない
		LABEL_Effect = 0,		// エフェクト
		LABEL_Cursor,			// カーソル
		LABEL_Number,			// 数字
		LABEL_Enemy,			// 敵
		LABEL_Enemy_ver2,		// 敵ver2
		LABEL_Player,			// プレイヤー
		LABEL_UI_Stake,			// 蛇の数(UI)
		LABEL_Shape_Circle,		// 図形(円)
		LABEL_Shape_Square,		// 図形(四角)
		LABEL_Shape_Triangle,	// 図形(三角)

		/* ↓タイトル↓ */
		LABEL_TITLE_BG,			// 背景
		LABEL_TITLE_Snake,		// 蛇
		LABEL_TITLE_PressEnter,	// PressEnter
		LABEL_TITLE_LOGO,		// ロゴ
		LABEL_MAX
	};

	/* ↓メンバ関数↓ */
public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public:
	void LoadAll();				// 全ての読み込み
	void Load(ELabel label);	// 指定の読み込み
	void ReleaseAll();			// 全ての破棄
	void Release(ELabel label);	// 指定の破棄
	LPDIRECT3DTEXTURE9 Get(ELabel label);	// 情報の取得

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DTEXTURE9 m_pTexture[LABEL_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
