//----------------------------------------
//　爆発
//　Author：橋野幹生
//----------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//マクロ定義
#define MAX_EXPLOSION	(256)	//爆発の最大数

//爆発の構造体
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXCOLOR col;				//カラー
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	bool bUse;					//使用しているかどうか
	int nCntAnim;				//アニメーションカウンター
	int nPatternAnim;			//アニメーションパターンNo.
}Explosion;

//プロトタイプ宣言
void InitExplosion(void);				//爆発の初期化処理
void UninitExplosion(void);				//爆発の終了処理
void UpdateExplosion(void);				//爆発の更新処理
void DrawExplosion(void);				//爆発の描画処理
void SetExplosion(D3DXVECTOR3 pos);		//爆発の設定

#endif
