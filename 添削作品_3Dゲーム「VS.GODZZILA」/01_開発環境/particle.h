//----------------------------------------
//　パーティクル
//　Author：橋野幹生
//----------------------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//マクロ定義
#define MAX_PARTICLE	(256)	//パーティクル最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//角度
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//カラー
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	D3DXVECTOR3 size;		//サイズ
	bool bUse;				//使っているかどうか
	int nLife;				//寿命
}Particle;

//プロトタイプ宣言
void InitParticle(void);	//パーティクル初期化
void UninitParticle(void);	//パーティクル終了
void UpdateParticle(void);	//パーティクル更新
void DrawParticle(void);	//パーティクル描画
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size);		//パーティクルの設定

#endif


