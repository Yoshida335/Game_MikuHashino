//----------------------------------------
//　壁
//　Author：橋野幹生
//----------------------------------------
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//マクロ定義
#define MAX_WALL	(256)		//壁の最大数
#define WALL_X		(300.0f)	// x方向への値	横幅
#define WALL_Y		(140.0f)	// y方向への値	高さ
#define WALL_Z		(0.0f)		// z方向への値	縦幅

//テクスチャの種類
typedef enum
{
	TYPE_WARKING = 0,	//危険テクスチャ
	TYPE_BILL,			//ビルテクスチャ
	MAX_TYPE
}WALLTYPE;

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//角度
	D3DXVECTOR3 size;		//サイズ
	D3DXCOLOR col;			//カラー
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	bool bUse;				//使っているかどうか
	WALLTYPE type;			//種類
}Wall;

//プロトタイプ宣言
void InitWall(void);	//壁の初期化
void UninitWall(void);	//壁の終了
void UpdateWall(void);	//壁の更新
void DrawWall(void);	//壁の描画
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 size, WALLTYPE type);	//壁の設定
Wall * GetWall(void);	//壁の情報

#endif

