//----------------------------------------
//　ビルボード
//　Author：橋野幹生
//----------------------------------------
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//マクロ定義
#define MAX_BILLBOARD	(256)	//ビルボードの最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXCOLOR col;				//カラー
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	int nIdxShadow;				//影用
	bool bUse;					//使用しているかどうか
}Billboard;

//プロトタイプ宣言
void InitBillboard(void);				//ビルボードの初期化処理
void UninitBillboard(void);				//ビルボードの終了処理
void UpdateBillboard(void);				//ビルボードの更新処理
void DrawBillboard(void);				//ビルボードの描画処理
void SetBillboard(D3DXVECTOR3 pos);		//ビルボードの設定

#endif