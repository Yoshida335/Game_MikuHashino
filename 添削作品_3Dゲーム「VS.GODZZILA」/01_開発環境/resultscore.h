//----------------------------------------
//　リザルトスコア
//　Author：橋野幹生
//----------------------------------------
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_

#include "main.h"

#define MAX_RESULTSCORE	(16)	//スコアの最大設定数

//プロトタイプ宣言
void InitResultScore(void);		//リザルトスコアの初期化
void UninitResultScore(void);	//リザルトスコアの終了
void UpdateResultScore(void);	//リザルトスコアの更新
void DrawResultScore(void);		//リザルトスコアの描画
void SetResultScore(int nResultScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);	//リザルトスコアの設定

#endif