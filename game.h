//**************************************************
// 
// game.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _GAME_H_	//このマクロ定義がされてなかったら
#define _GAME_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CPlayer;	//プレイヤー
class CCircle;

//==================================================
// クラス
//==================================================
class CGame : public CMode
{
	/* 定義 */
public:

	/* ↓静的メンバ関数↓ */
public:
	CPlayer* GetPlayer();	// プレイヤーの取得
	CCircle* GetCircle();	// プレイヤーの取得

	/* ↓メンバ関数↓ */
public:
	CGame();			// デフォルトコンストラクタ
	~CGame() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	/* ↓メンバ変数↓ */
private:
	static CPlayer* m_pPlayer;	//プレイヤー
	static CCircle* m_pCircle;	//プレイヤー
};

#endif // !_GAME_H_
