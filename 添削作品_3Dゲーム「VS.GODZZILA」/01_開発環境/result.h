//----------------------------------------
//　リザルト画面
//　Author：橋野幹生
//----------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

typedef enum
{
	SignType_01 = 0,	//*
	SignType_02,		//=
	SignType_03,		//+
	SignType_04,		//-
	SignType_05,		//%
	SignType_06,		//.
	SignType_MAX
}SignType;

//プロトタイプ宣言
void InitResult(void);		//リザルト画面の初期化
void UninitResult(void);	//リザルト画面の終了
void UpdateResult(void);	//リザルト画面の更新
void DrawResult(void);		//リザルト画面の描画
void SetResult(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);		//リザルトの設定
void SetSign(D3DXVECTOR3 pos, D3DXVECTOR3 size, SignType type);		//記号の設定
int GetResultScore(void);	//リザルト画面のスコア情報

#endif
