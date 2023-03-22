//**************************************************
// 
// number.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "number.h"
#include "application.h"

//==================================================
// 定義
//==================================================
namespace
{
const int TEX_DIVISION = 10;	// テクスチャの分割数
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CNumber* CNumber::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CNumber* pNumber = nullptr;

	pNumber = new CNumber;

	if (pNumber != nullptr)
	{// nullチェック
		pNumber->Init();
		pNumber->SetPos(pos);
		pNumber->SetSize(size);
	}

	return pNumber;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CNumber::CNumber()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CNumber::~CNumber()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CNumber::Init()
{
	// 初期化
	CObject2D::Init();

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::LABEL_Number);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CNumber::Uninit()
{
	// 終了
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CNumber::Update()
{
	// 更新
	CObject2D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CNumber::Draw()
{
	// 描画
	CObject2D::Draw();
}

//--------------------------------------------------
// 変更
//--------------------------------------------------
void CNumber::Change(int number)
{
	float div = 1.0f / TEX_DIVISION;
	float tex = div * number;

	D3DXVECTOR2 u = D3DXVECTOR2(tex, tex + div);
	D3DXVECTOR2 v = D3DXVECTOR2(0.0f, 1.0f);

	// テクスチャ座標の設定
	CObject2D::SetVtxTex(u, v);
}
