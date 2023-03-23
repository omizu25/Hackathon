//**************************************************
//
// sound.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SOUND_H_	//このマクロ定義がされてなかったら
#define _SOUND_H_	//２重インクルード防止のマクロ定義

//==================================================
// クラス
//==================================================
class CSound
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,
		LABEL_BGM_Title = 0,	// タイトル
		LABEL_BGM_Game,			// ゲーム
		LABEL_BGM_Result,		// リザルト
		LABEL_BGM_Ranking,		// ランキング
		LABEL_BGM_Tutorial,		// チュートリアル
		LABEL_SE_Enter,			// 決定
		LABEL_SE_Select,		// 選択
		LABEL_SE_Hit,			// 当たったときの判定
		LABEL_SE_Waring,		// 時間制限
		LABEL_SE_Danger,		// 危険信号
		LABEL_MAX,
	};

	/* ↓メンバ関数↓ */
public:
	CSound();	// デフォルトコンストラクタ
	~CSound();	// デストラクタ

public:
	HRESULT Init(HWND hWnd);	// 初期化
	void Uninit();				// 終了
	HRESULT Play(ELabel sound);	// 再生
	void Stop(ELabel label);	// 指定した停止
	void Stop();				// 全ての停止

public:
	void SetVolume(ELabel label, float fVolume);		// 音量の設定
	void SetRate(ELabel label, float rate);				// ピッチ操作

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// チャンクのチェック
	HRESULT LoadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// チャンクデータの読み込み

	/* ↓メンバ変数↓ */
private: 
	IXAudio2* m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;		// マスターボイス
	IXAudio2SourceVoice* m_pSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE* m_pDataAudio[LABEL_MAX];					// オーディオデータ
	DWORD m_sizeAudio[LABEL_MAX];					// オーディオデータサイズ
	float m_fVol;									// サウンドの音量を変化させる変数
	float m_fPitch;									// サウンドの音程を変化させる変数
};

#endif // !_SOUND_H_
