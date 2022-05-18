//----------------------------------------
//　当たり判定
//　Author：橋野幹生
//----------------------------------------
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

//マクロ定義
#define MAX_COLLISION	(256)	//当たり判定の最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//現在の位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	bool bUse;					//使用しているかどうか
	int nLife;					//寿命
	D3DXVECTOR3 size;			//
}COLLISION;

//プロトタイプ宣言
void InitCollision(void);		//当たり判定の初期化処理
void UninitCollision(void);		//当たり判定の終了処理
void UpdateCollision(void);		//当たり判定の更新処理
void DrawCollision(void);		//当たり判定の描画処理
void SetCollision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 rot);	//当たり判定の描画処理

#endif
