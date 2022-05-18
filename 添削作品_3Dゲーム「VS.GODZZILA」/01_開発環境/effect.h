//----------------------------------------
//　エフェクト
//　Author：橋野幹生
//----------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//マクロ定義
#define MAX_EFFECT	(1000)	//エフェクトの最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//角度
	D3DXCOLOR col;			//カラー
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	D3DXVECTOR3 size;		//サイズ
	bool bUse;				//使っているかどうか
	int nLife;				//寿命
}Effect;

//プロトタイプ宣言
void InitEffect(void);			//エフェクトの初期化
void UninitEffect(void);		//エフェクトの終了
void UpdateEffect(void);		//エフェクトの更新
void DrawEffect(void);			//エフェクトの描画
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size);	//エフェクトの設定

#endif
