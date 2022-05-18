//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,		// start
	SOUND_LABEL_BGM_GAME,			// game
	SOUND_LABEL_BGM_RESULT,			// result
	SOUND_LABEL_SE_HIT,				// ヒット
	SOUND_LABEL_SE_K,				// ヒット
	SOUND_LABEL_SE_EXPLOSION,		// ヒット
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
