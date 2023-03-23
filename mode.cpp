//**************************************************
// 
// mode.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "mode.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "tutorial.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CMode* CMode::Create(EMode mode)
{
	CMode* pMode = nullptr;

	switch (mode)
	{
	case CMode::MODE_TITLE:
		pMode = new CTitle;
		break;

	case CMode::MODE_TUTORIAL:
		pMode = new CTutorial;
		break;

	case CMode::MODE_GAME:
		pMode = new CGame;
		break;

	case CMode::MODE_RESULT:
		pMode = new CResult;
		break;

	case CMode::MODE_RANKING:
		pMode = new CRanking;
		break;
		
	case CMode::MODE_MAX:
	case CMode::MODE_NONE:
	default:
		assert(false);
		break;
	}

	if (pMode == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pMode->Init();

	return pMode;
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CMode::CMode() : CObject(CObject::PRIORITY_SYSTEM)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMode::~CMode()
{
}
