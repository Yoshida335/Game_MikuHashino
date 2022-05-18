//----------------------------------------
//　カメラ
//　Author：橋野幹生
//----------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//マクロ定義
#define CAMERA_SPEED		(1.0f)	//カメラの移動速度

//カメラの構造体
typedef struct
{
	D3DXVECTOR3 posV;			//現在の視点
	D3DXVECTOR3 posVOld;		//前回の視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 rotold;			//向き
	D3DXVECTOR3 rotDest;		//目的の向き
	float fDistance;			//視点から注視点の距離
	D3DVIEWPORT9 viewport;		//ビューポート

	POINT NowPointer;
	POINT CenterPointer;
	POINT MovePointer;
}CAMERA;

//プロトタイプ宣言
void InitCamera(void);			//カメラの初期化処理
void UninitCamera(void);		//カメラの終了処理
void UpdateCamera(void);		//カメラの更新処理
void MoveCamera(void);			//カメラの移動処理
void SetCamera(int nCnt);		//カメラの設定
CAMERA * GetCamera(void);		//カメラの情報

#endif
