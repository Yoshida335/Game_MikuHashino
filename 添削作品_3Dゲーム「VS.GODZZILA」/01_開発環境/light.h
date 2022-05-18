//----------------------------------------
//　ライト
//　Author：橋野幹生
//----------------------------------------
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//マクロ定義
#define MAX_LIGHT		(3)		//ライトの最大数

//プロトタイプ宣言
void InitLight(void);		//ライトの初期化
void UninitLight(void);		//ライトの終了
void UpdateLight(void);		//ライトの更新

#endif
