//**************************************************
// 
// enemy.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_H_	//このマクロ定義がされてなかったら
#define _ENEMY_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CEnemy : public CObject3D
{
	/* 定義 */
public:

	/* ↓静的メンバ関数↓ */
public:
	static CEnemy* Create(const D3DXVECTOR3& pos, float rot);	// 生成

	/* ↓メンバ関数↓ */
public:
	CEnemy();			// デフォルトコンストラクタ
	~CEnemy() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Set(const D3DXVECTOR3& pos, float rot);	// 設定
	void Move();	// 移動

	/* メンバ変数 */
private:
	D3DXVECTOR3 m_move;	// 移動量
};

#endif // !_ENEMY_H_
