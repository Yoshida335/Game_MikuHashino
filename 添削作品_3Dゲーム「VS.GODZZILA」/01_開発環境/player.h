//----------------------------------------
//　プレイヤー
//　Author：橋野幹生
//----------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//マクロ定義
#define MAX_PLAYER			(1)		//プレイヤーの最大数
#define PLAYER_SPEED		(2.0f)	//プレイヤーの移動速度
#define MAX_PARTS			(12)	//最大パーツ数

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;		//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアル情報へのポインタ
	DWORD nNumMat;			//マテリアル情報の数
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//角度
	int nIdxModelParent;	//親モデルのインデックス
	LPDIRECT3DTEXTURE9 pTexturePlayer[10];	//テクスチャへのポインタ
}ModelParts;

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 move;		//移動量
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	float diff;				//差分用
	float rotDest;			//目的の角度
	int IdxShadow;			//影用
	D3DXVECTOR3 vtxMin;		//頂点の最小値を取得用
	D3DXVECTOR3 vtxMax;		//頂点の最大値を取得用
	D3DXVECTOR3 size;		//サイズ保存用
	ModelParts aModel[MAX_PARTS];	//モデルの情報[最大パーツ数分]
	bool bIsJumping;		//ジャンプしているかどうか
	int nLife;				//体力
}Player;

typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
}SetPlayer;

//プロトタイプ宣言
void InitPlayer(void);		//プレイヤーの初期化
void UninitPlayer(void);	//プレイヤーの終了
void UpdatePlayer(void);	//プレイヤーの更新
void DrawPlayer(void);		//プレイヤーの描画
void MovePlayer(void);		//プレイヤーの移動
Player * GetPlayer(void);	//プレイヤーの情報
void MotionPlayer(int nMotion);		//プレイヤーのモーション設定
void SetMotion(int nSet);	//モーションを設定する
void HitModel(int nDamage);	//プレイヤーの攻撃ヒットした時の処理
bool CollisionPlayer(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);	//プレイヤーと敵との当たり判定
void ControlPlayer(void);	//プレイヤーの操作に関する処理

#endif