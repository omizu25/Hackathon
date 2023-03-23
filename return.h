//**************************************************
// 
// return.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RETURN_H_	//このマクロ定義がされてなかったら
#define _RETURN_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object3D.h"

//==================================================
// クラス
//==================================================
class CReturn : public CObject3D
{
	/* ↓定義↓ */
public:

	/* ↓静的メンバ関数↓ */
private:
	static float m_move;	// 移動量
	static int m_count;		// カウント

	/* ↓静的メンバ関数↓ */
public:
	static float GetMove();
	static void AddMove();		// 速度の加算
	static void CreateAll();	// 全ての生成
	static CReturn* Create(const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CReturn();				// デフォルトコンストラクタ
	~CReturn() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	/* ↓メンバ変数↓ */
private:
	int m_time;
	D3DXVECTOR2 u;
	bool m_effect;
};

#endif // !_RETURN_H_
