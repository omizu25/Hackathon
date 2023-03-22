//**************************************************
// 
// object3D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT3D_H_	//このマクロ定義がされてなかったら
#define _OBJECT3D_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "texture.h"

//==================================================
// クラス
//==================================================
class CObject3D : public CObject
{
	/* ↓定義↓ */
public:
	struct VERTEX
	{// 頂点データ
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

	// 頂点フォーマット
	static const DWORD FVF_VERTEX = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	/* ↓静的メンバ関数↓ */
public:
	static CObject3D* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
//	CObject3D() = delete;	// デフォルトコンストラクタ
	explicit CObject3D(CObject::EPriority prio = CObject::PRIORITY_3D);	// コンストラクタ
	~CObject3D() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	void SetPos(const D3DXVECTOR3& pos);		// 位置の設定
	const D3DXVECTOR3& GetPos() const;			// 位置の取得
	void SetSize(const D3DXVECTOR3& size);		// サイズの設定
	const D3DXVECTOR3& GetSize() const;			// サイズの取得
	void SetRot(const D3DXVECTOR3& rot);		// 向きの設定
	const D3DXVECTOR3& GetRot() const;			// 向きの取得
	void SetCol(const D3DXCOLOR& col);			// 色の設定
	const D3DXCOLOR& GetCol() const;			// 色の取得
	void SetTexture(CTexture::ELabel texture);	// テクスチャの設定
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2& v);	// テクスチャ座標の設定

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	CTexture::ELabel m_texture;	// テクスチャの列挙型
	D3DXVECTOR3 m_size;	// サイズ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXCOLOR m_col;	// 色
};

#endif // !_OBJECT3D_H_
