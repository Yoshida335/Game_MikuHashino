//----------------------------------------
//　ライフゲージ
//　Author：橋野幹生
//----------------------------------------
#ifndef _GAGE_H_
#define _GAGE_H_

#include "main.h"

//マクロ定義
#define MAX_GAGE	(256)	//ライフゲージの最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXCOLOR col;				//カラー
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	bool bUse;					//使用しているかどうか
	int nLife;					//寿命
	int nMaxLife;				//最大寿命
}Gage;

//プロトタイプ宣言
void InitGage(void);				//ライフゲージの初期化処理
void UninitGage(void);				//ライフゲージの終了処理
void UpdateGage(void);				//ライフゲージの更新処理
void DrawGage(void);				//ライフゲージの描画処理
void SetGage(D3DXVECTOR3 pos, int nLife);	//ライフゲージの設定
void HitGage(int nCntGage, int nDamage);	//ライフゲージのヒット処理

#endif


