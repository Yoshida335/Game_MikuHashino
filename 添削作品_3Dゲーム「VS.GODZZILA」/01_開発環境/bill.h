//----------------------------------------
//　ビル
//　Author：橋野幹生
//----------------------------------------
#ifndef _BILL_H_
#define _BILL_H_

#include "main.h"

//マクロ定義
#define MAX_MODEL			(126)	//ビルの最大数
#define MODEL_SPEED			(1.0f)	//ビルの移動速度

//ビルの種類
typedef enum
{
	TYPE_BILL_01 = 0,
	TYPE_BILL_02,
	TYPE_MAX
}MODELTYPE;

//ビルの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXCOLOR col;			//色
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	float diff;				//差分用
	float rotDestModel;		//目的の角度
	int IdxShadow;			//影用
	bool bUse;				//使っているかどうか
	D3DXVECTOR3 vtxMin;		//頂点の最小値を取得用
	D3DXVECTOR3 vtxMax;		//頂点の最大値を取得用
	MODELTYPE nType;		//ビルの種類
	int nLife;				//体力
	bool bHit;				//攻撃が当たっているかどうか
	int nCntTime;
}Model;

typedef struct
{
	float nModelP;		//ビルの破壊状況をパーセントで把握するよう
	float nMaxLife;		//bUseがtrueになっているビルの、合計体力数
	float nMax;			//bUseがtrueになっているビルの、合計数
}Parcent;

//プロトタイプ宣言
void InitModel(void);		//ビルの初期化
void UninitModel(void);		//ビルの終了
void UpdateModel(void);		//ビルの更新
void DrawModel(void);		//ビルの描画
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE type, int life);		//ビルの設定
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move);	//ビルの当たり判定
void CollisionAttack(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);	//ビルの当たり判定
void HitModel(int nCntModel, int nDamage);	//ビルに攻撃が当たった時の処理
Parcent * GetModeParcent(void);	//破壊状況の情報
void SaveParcent(void);			//パーセント保存
void LoadP(void);				//パーセント読み込み

#endif
