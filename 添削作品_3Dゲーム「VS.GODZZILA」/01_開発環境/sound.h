//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,		// start
	SOUND_LABEL_BGM_GAME,			// game
	SOUND_LABEL_BGM_RESULT,			// result
	SOUND_LABEL_SE_HIT,				// �q�b�g
	SOUND_LABEL_SE_K,				// �q�b�g
	SOUND_LABEL_SE_EXPLOSION,		// �q�b�g
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
