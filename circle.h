//**************************************************
// 
// circle.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_H_	//このマクロ定義がされてなかったら
#define _CIRCLE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CCircle : public CObject3D
{
	/* 定義 */
public:
	static const int COUNTDOWN_TIME;	// カウントダウンの時間

private:
	static const int MAX_LIFE;			// 寿命の最大値
	static const D3DXCOLOR STD_COLOR;	// 標準の色
	static const D3DXCOLOR START_COLOR;	// 始まりの色
	static const D3DXCOLOR END_COLOR;	// 終わりの色
	static const D3DXCOLOR DIFF_COLOR;	// 色の差分

	/* ↓静的メンバ関数↓ */
public:
	static CCircle* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CCircle();				// デフォルトコンストラクタ
	~CCircle() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	bool GetCollision();

private:
	void Appear();		// 出現
	void DisAppear();	// 消滅

	/* ↓メンバ変数↓ */
private:
	int m_time;	// タイム
	bool m_appear;	// 出現しているかどうか
	D3DXCOLOR m_changeCol;	// 色の変化量
};

#endif // !_CIRCLE_H_
