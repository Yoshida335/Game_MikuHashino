//----------------------------------------
//　タイム
//　Author：橋野幹生
//----------------------------------------
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//フェードの状態
typedef enum
{
	TIME_ON = 0,	//タイム中
	TIME_OFF,		//タイム終了
	TIME_MAX
}TIME;

//プロトタイプ宣言
void InitTime(void);		//タイムの初期化
void UninitTime(void);		//タイムの終了
void UpdateTime(void);		//タイムの更新
void DrawTime(void);		//タイムの描画
int * GetTime(void);		//タイムの情報
void AddTime(int nTime);	//タイムの加算

#endif

