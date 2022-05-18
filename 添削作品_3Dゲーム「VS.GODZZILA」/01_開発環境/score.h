//----------------------------------------
//　スコア
//　Author：橋野幹生
//----------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

#define MAX_SCORE	(16)	//スコアの最大設定数

//プロトタイプ宣言
void InitScore(void);		//スコアの初期化
void UninitScore(void);		//スコアの終了
void UpdateScore(void);		//スコアの更新
void DrawScore(void);		//スコアの描画
void SetScore(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);	//スコアの設定

#endif
