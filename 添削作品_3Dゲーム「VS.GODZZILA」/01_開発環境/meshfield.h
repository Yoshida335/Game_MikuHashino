//----------------------------------------
//　メッシュフィールド(平面)
//　Author：橋野幹生
//----------------------------------------
#ifndef _MESHFIELR_H_
#define _MESHFIELR_H_

#include "main.h"

#define MESHFIELD_SIZE			(1200.0f)	//広さ

//プロトタイプ宣言
void InitMeshfield(void);		//平面の初期化処理
void UninitMeshfield(void);		//平面の終了処理
void UpdateMeshfield(void);		//平面の更新処理
void DrawMeshfield(void);		//平面の描画処理

#endif