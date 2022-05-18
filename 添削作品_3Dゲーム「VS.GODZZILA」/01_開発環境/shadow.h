//----------------------------------------
//　影
//　Author：橋野幹生
//----------------------------------------
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//マクロ定義
#define MAX_SHADOW		(256)	//影の最大数

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//角度
	float size;				//サイズ
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	bool bUse;				//使っているかどうか
}Shadow;

//プロトタイプ宣言
void InitShadow(void);		//影の初期化
void UninitShadow(void);	//影の終了
void UpdateShadow(void);	//影の更新
void DrawShadow(void);		//影の描画
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float size);	//影の設定
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);						//影の位置設定

#endif
