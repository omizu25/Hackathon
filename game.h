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
class CNumberManager;
class CObject2D;

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
	void AddScore(int score);	// プレイヤーの取得
	int GetScore();	// プレイヤーの取得

	/* ↓静的メンバ変数↓ */
private:
	static CPlayer* m_pPlayer;	//プレイヤー
	static CCircle* m_pCircle;	//プレイヤー
	static int m_score;

	/* ↓メンバ関数↓ */
public:
	CGame();			// デフォルトコンストラクタ
	~CGame() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	void DeathPlayer();

	/* ↓メンバ変数↓ */
private:
	int m_time;
	bool m_bUse_SE;				//SEを再生するかどうか変化させる変数
	CNumberManager* m_pTime;	// タイムの情報
	CNumberManager* m_pScore;	// スコアの情報

	CObject2D* pObjPlayer[3];	
};

#endif // !_GAME_H_
