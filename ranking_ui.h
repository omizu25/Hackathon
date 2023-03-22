//**************************************************
// 
// ranking_ui.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RANKING_UI_H_	//このマクロ定義がされてなかったら
#define _RANKING_UI_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"

//==================================================
// 前方宣言
//==================================================
class CNumberManager;
class CNumber;
class CObject2D;

//==================================================
// 定義
//==================================================
class CRankingUI : public CObject
{
	/* ↓静的メンバ関数↓ */
public:
	static const int MAX_RANKING = 5;	// ランキングの最大数

	/* ↓静的メンバ関数↓ */
public:
	static CRankingUI* Create(const D3DXVECTOR3& pos, float length);	// 生成
	static void SetScore(int score);	// 設定
	static int Get(int rank);	// 取得

private:
	static void Load();		// 読み込み
	static void Save();		// 保存
	static void Change();	// 変更

	/* ↓静的メンバ変数↓ */
private:
	static int m_score;	// 今回のスコア
	static int m_ranking[MAX_RANKING];	// ランキング

	/* ↓メンバ関数↓ */
public:
	CRankingUI();			// デフォルトコンストラクタ
	~CRankingUI() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Set(const D3DXVECTOR3& pos, float length);	// 設定

	/* ↓メンバ変数↓ */
private:
	CNumberManager* m_pRanking[MAX_RANKING];	// ランキング
	CNumber* m_pNumber[MAX_RANKING];	// 順位
	CObject2D* m_pRank[MAX_RANKING];	// 位
	int m_newRank;	// 新しいスコア
	int m_time;		// タイム
};

#endif // !_RANKING_UI_H_
