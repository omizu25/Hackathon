//**************************************************
// 
// Tutorial.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TUTORIAL_H_	//このマクロ定義がされてなかったら
#define _TUTORIAL_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CMenu;

//==================================================
// クラス
//==================================================
class CTutorial : public CMode
{
	/* 定義 */
public:

	/* ↓メンバ関数↓ */
public:
	CTutorial();			// デフォルトコンストラクタ
	~CTutorial() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Input();	// 入力

					/* メンバ変数 */
private:
	CMenu* m_pMenu;	// メニューの情報
};

#endif // !_TUTORIAL_H_
