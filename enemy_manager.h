//**************************************************
// 
// enemy_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_MANAGER_H_	// このマクロ定義がされてなかったら
#define _ENEMY_MANAGER_H_	// 二重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"

//==================================================
// クラス
//==================================================
class CEnemyManager : public CObject
{
	/* ↓定義↓ */
private:
	
	/* ↓静的メンバ関数↓ */
public:
	static CEnemyManager* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CEnemyManager();			// デフォルトコンストラクタ
	~CEnemyManager() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	static void SubPop() { m_pop--; }	//出現数の減少

private:
	void Game();	// ゲーム

	/* ↓メンバ変数↓ */
private:
	int m_time;			// 時間
	int m_interval;		// 間隔
	static int m_pop;	// 出現数
};

#endif // !_ENEMY_MANAGER_H_
