//----------------------------------------
//　フェード処理
//　Author：橋野幹生
//----------------------------------------
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//フェードの状態
typedef enum
{
	FADE_NOME = 0,			//何もしてない
	FADE_IN,				//フェードイン
	FADE_OUT,				//フェードアウト
	FADE_MAX
}FADE;

//プロトタイプ宣言
void InitFade(MODE modeNext);	//フェードの初期化処理
void UninitFade(void);			//フェードの終了処理
void UpdateFade(void);			//フェードの更新処理
void DrawFade(void);			//フェードの描画処理
void SetFade(MODE modeNext);	//フェードの設定
FADE GetFade(void);				//フェードの情報

#endif

