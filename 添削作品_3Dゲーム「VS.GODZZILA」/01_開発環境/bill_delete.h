//----------------------------------------
//　ビル(破壊後)
//　Author：橋野幹生
//----------------------------------------
#ifndef _BILL_DELETE_H_
#define _BILL_DELETE_H_

#include "main.h"

//マクロ定義
#define MAX_BILLDELETE			(126)	//ビル(破壊後)の最大数

//ビル(破壊後)の種類
typedef enum
{
	TYPE_DELETEBILL_01 = 0,
	TYPE_DELETEBILL_02,
	TYPE_DLETEMAX
}BILLDELETETYPE;

//ビル(破壊後)の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXCOLOR col;			//色
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	bool bUse;				//使っているかどうか
	BILLDELETETYPE type;	//種類
}BillDelete;

//プロトタイプ宣言
void InitBillDelete(void);		//ビル(破壊後)の初期化
void UninitBillDelete(void);	//ビル(破壊後)の終了
void UpdateBillDelete(void);	//ビル(破壊後)の更新
void DrawBillDelete(void);		//ビル(破壊後)の描画
void SetBillDelete(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//ビル(破壊後)の設定

#endif

