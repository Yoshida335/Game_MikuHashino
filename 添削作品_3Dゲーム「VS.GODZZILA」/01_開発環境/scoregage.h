//----------------------------------------
//　スコアゲージ
//　Author：橋野幹生
//----------------------------------------
#ifndef _SCOREGAGE_H_
#define _SCOREGAGE_H_

#include "main.h"

//マクロ定義
#define MAX_SCOREGAGE	(256)	//スコアゲージの最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//カラー
	bool bUse;			//使用しているかどうか
	int nLife;			//寿命
	int nMaxLife;		//最大寿命
}ScoreGage;

//プロトタイプ宣言
void InitScoreGage(void);		//スコアゲージの初期化処理
void UninitScoreGage(void);		//スコアゲージの終了処理
void UpdateScoreGage(void);		//スコアゲージの更新処理
void DrawScoreGage(void);		//スコアゲージの描画処理
void SetScoreGage(D3DXVECTOR3 pos, int nLife);		//スコアゲージの設定
void HitScoreGage(int nCntScoreGage, int nDamage);	//スコアのゲージが減る処理

#endif

