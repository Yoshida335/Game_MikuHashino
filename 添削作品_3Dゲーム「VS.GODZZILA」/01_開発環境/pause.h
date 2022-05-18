//----------------------------------------
//　ポーズ画面
//　Author：橋野幹生
//----------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//ポーズの状態
typedef enum
{
	SELECT_OFF = 0,
	SELECT_ON,
	SELECT_MAX
}PauseState;

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	PauseState state;		//状態
}PAUSE;

//プロトタイプ宣言
void InitPause(void);		//ポーズの初期化処理
void UninitPause(void);		//ポーズの終了処理
void UpdatePause(void);		//ポーズの更新処理
void DrawPause(void);		//ポーズの描画処理

#endif


