//----------------------------------------
//　マウス
//　Author：橋野幹生
//----------------------------------------
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "main.h"

//プロトタイプ宣言
void InitMouse(HWND hWnd);	//マウスの初期化
void UninitMouse(void);		//マウスの終了
void UpdateMouse(void);		//マウスの更新
void DrawMouse(void);		//マウスの描画

#endif