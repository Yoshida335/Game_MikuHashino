//----------------------------------------
//　マップ
//　Author：橋野幹生
//----------------------------------------
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

//マクロ定義
#define FIELD_SIZE	(600.0f)

typedef struct
{
	D3DXVECTOR3 Setpos[10];
}SetPos;

void SetMap(void);	//マップの設定
SetPos * GetSetPos(void);	//敵の設定位置の情報

#endif

