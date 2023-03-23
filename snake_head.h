//**************************************************
// 
// snake_head.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _SNAKE_HEAD_H_	//このマクロ定義がされてなかったら
#define _SNAKE_HEAD_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object3D.h"

//==================================================
// 前方宣言
//==================================================
class CSnakeBody;

//==================================================
// 定義
//==================================================
class CSnakeHead : public CObject3D
{
	/* 定義 */
public:

	/* ↓静的メンバ関数↓ */
public:
	static CSnakeHead* Create(const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CSnakeHead();			// デフォルトコンストラクタ
	~CSnakeHead() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	const D3DXVECTOR3& GetPosOld() const;	// 前回の位置の取得

private:
	void Set(const D3DXVECTOR3& pos, CSnakeBody** pBody);	// 設定
	void SetMove();		// 移動量の設定
	void PlayerCollision();	// 当たり判定
	void CircleCollision();	// 当たり判定

	/* メンバ変数 */
private:
	int m_time;				// タイム
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_posOld;	// 前回の位置
	CSnakeBody** m_pBody;	// 体の情報
};

#endif // !_ENEMY_SNAKE_HEAD_H_
