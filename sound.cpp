//**************************************************
// 
// sound.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "sound.h"

//==================================================
// 定義
//==================================================
namespace
{
struct SParam
{
	const string str;	// ファイルパス
	int loop;			// ループ
};

const SParam PARAM[] =
{// パラメータの情報
	{ "data/BGM/Title.wav", -1 },				// タイトル
	{ "data/BGM/Devil_Disaster.wav", -1 },		// ゲーム
	{ "data/BGM/Result.wav", -1 },				// リザルト
	{ "data/BGM/a_beautiful_sunset.wav", -1 },	// 命危険
	{ "data/BGM/tutorial.wav", -1 },			// チュートリアル
	{ "data/SE/Enter.wav", 0 },					// 決定
	{ "data/SE/Select.wav", 0 },				// 選択
	{ "data/SE/Hit.wav", 0 },					// 当たったとき
	{ "data/SE/Warning.wav", 0 },				// 危険
	{ "data/SE/life_danger.wav", -1 },			// 命危険
};
}

static_assert(sizeof(PARAM) / sizeof(PARAM[0]) == CSound::LABEL_MAX, "aho");

//==================================================
// 定数定義
//==================================================
const float DEFAULT_PARAM = 1.0f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CSound::CSound() :
	m_pMasteringVoice(nullptr),
	m_pXAudio2(nullptr)
{
	memset(m_pDataAudio, 0, sizeof(m_pDataAudio));
	memset(m_pSourceVoice, 0, sizeof(m_pSourceVoice));
	memset(m_sizeAudio, 0, sizeof(m_sizeAudio));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CSound::~CSound()
{
	assert(m_pMasteringVoice == nullptr);
	assert(m_pXAudio2 == nullptr);

	for (int i = 0; i < LABEL_MAX; i++)
	{
		assert(m_pDataAudio[i] == nullptr);
		assert(m_pSourceVoice[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CSound::Init(HWND hWnd)
{
	//各変数の初期化
	m_fVol = DEFAULT_PARAM;
	m_fPitch = DEFAULT_PARAM;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (FAILED(XAudio2Create(&m_pXAudio2, 0)))
	{// XAudio2オブジェクトの作成
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了
		CoUninitialize();

		return E_FAIL;
	}

	if (FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice)))
	{// マスターボイスの生成
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if (m_pXAudio2 != nullptr)
		{// nullチェック
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = nullptr;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	HANDLE hFile = INVALID_HANDLE_VALUE;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype = 0;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// サウンドデータの初期化
	for (int i = 0; i < LABEL_MAX; i++)
	{
		hFile = INVALID_HANDLE_VALUE;
		dwChunkSize = 0;
		dwChunkPosition = 0;
		dwFiletype = 0;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		/* ↓サウンドデータファイルの生成↓ */

		hFile = CreateFile(PARAM[i].str.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		/* ↓WAVEファイルのチェック↓ */

		if (FAILED(CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		if (FAILED(LoadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition)))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		/* ↓フォーマットチェック↓ */

		if (FAILED(CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		if (FAILED(LoadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition)))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		/* ↓オーディオデータ読み込み↓ */

		if (FAILED(CheckChunk(hFile, 'atad', &m_sizeAudio[i], &dwChunkPosition)))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		m_pDataAudio[i] = new BYTE[m_sizeAudio[i]];

		if (FAILED(LoadChunkData(hFile, m_pDataAudio[i], m_sizeAudio[i], dwChunkPosition)))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		/* ↓ソースボイスの生成↓ */

		if (FAILED(m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &(wfx.Format))))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		buffer.AudioBytes = m_sizeAudio[i];
		buffer.pAudioData = m_pDataAudio[i];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = PARAM[i].loop;

		// オーディオバッファの登録
		m_pSourceVoice[i]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CSound::Uninit()
{
	// 一時停止
	for (int i = 0; i < LABEL_MAX; i++)
	{
		if (m_pSourceVoice[i] == nullptr)
		{// nullチェック
			continue;
		}

		// 一時停止
		m_pSourceVoice[i]->Stop(0);

		// ソースボイスの破棄
		m_pSourceVoice[i]->DestroyVoice();
		m_pSourceVoice[i] = nullptr;

		// オーディオデータの開放
		delete m_pDataAudio[i];
		m_pDataAudio[i] = nullptr;
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = nullptr;

	if (m_pXAudio2 != nullptr)
	{// nullチェック
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = nullptr;
	}

	// COMライブラリの終了
	CoUninitialize();
}

//--------------------------------------------------
// 再生
//--------------------------------------------------
HRESULT CSound::Play(CSound::ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio[label];
	buffer.pAudioData = m_pDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = PARAM[label].loop;

	// セグメント停止(ラベル指定)
	Stop(label);

	// オーディオバッファの登録
	m_pSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_pSourceVoice[label]->Start(0);

	return S_OK;
}

//--------------------------------------------------
// 指定した停止
//--------------------------------------------------
void CSound::Stop(CSound::ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_pSourceVoice[label]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_pSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_pSourceVoice[label]->FlushSourceBuffers();
	}
}

//--------------------------------------------------
// 停止
//--------------------------------------------------
void CSound::Stop()
{
	// 一時停止
	for (int i = 0; i < LABEL_MAX; i++)
	{
		if (m_pSourceVoice[i] == nullptr)
		{
			continue;
		}

		// 一時停止
		m_pSourceVoice[i]->Stop(0);
	}
}

//--------------------------------------
//音量設定
//--------------------------------------
void CSound::SetVolume(ELabel lavel, float fVolume)
{//1.使用するサウンドタイプを指定 2.設定したい値を代入
	m_pSourceVoice[lavel]->SetVolume(fVolume);
}

//--------------------------------------
//ピッチ操作
//--------------------------------------
void CSound::SetRate(ELabel lavel, float rate)
{//1.使用するサウンドタイプを指定 2.設定したい値を代入
	m_pSourceVoice[lavel]->SetFrequencyRatio(rate);
}

//--------------------------------------------------
// チャンクのチェック
//--------------------------------------------------
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead = 0;
	DWORD dwChunkType = 0;
	DWORD dwChunkDataSize = 0;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType = 0;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (!ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (!ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;

			if (!ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}

			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
			break;
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//--------------------------------------------------
// チャンクデータの読み込み
//--------------------------------------------------
HRESULT CSound::LoadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (!ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL))
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
