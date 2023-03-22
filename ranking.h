//**************************************************
// 
// ranking.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RANKING_H_	//このマクロ定義がされてなかったら
#define _RANKING_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CMenu;
class CNumberManager;

//==================================================
// クラス
//==================================================
class CRanking : public CMode
{
	/* 定義 */
public:

	/* ↓メンバ関数↓ */
public:
	CRanking();				// デフォルトコンストラクタ
	~CRanking() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	/* ↓メンバ変数↓ */
private:
	void Input();	// 入力

	/* メンバ変数 */
private:
	CMenu* m_pMenu;	// メニューの情報
	CNumberManager* m_pScore;	// スコアの情報
};

#endif // !_RANKING_H_
