//----------------------------------------
//　ポリゴン
//　Author：橋野幹生
//----------------------------------------
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//マクロ定義
#define POLIGON_X	(50.0f)	// x方向への値	横幅
#define POLIGON_Y	(0.0f)	// y方向への値	高さ
#define POLIGON_Z	(50.0f)	// z方向への値	縦幅

//プロトタイプ宣言
void InitPolygon(void);		//ポリゴンの初期化
void UninitPolygon(void);	//ポリゴンの終了
void UpdatePolygon(void);	//ポリゴンの更新
void DrawPolygon(void);		//ポリゴンの描画

#endif
