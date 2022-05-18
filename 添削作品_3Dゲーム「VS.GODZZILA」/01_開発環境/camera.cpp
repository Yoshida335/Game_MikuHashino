//----------------------------------------
//　カメラの処理
//　Author：橋野幹生
//----------------------------------------
#include "camera.h"
#include "input.h"
#include "player.h"
#include "mouse.h"

//マクロ定義
#define MAX_CAMERA		(2)	//カメラの最大数

//グローバル変数宣言
CAMERA g_camera[MAX_CAMERA];
int g_nCnt = 0;

//---------------------------------------------------
//	カメラの初期化処理
//---------------------------------------------------
void InitCamera(void)
{
	//ビューポート構成の保存
	g_camera[0].viewport.X = 0;			//ビューポートの開始位置(x座標)
	g_camera[0].viewport.Y = 0;			//ビューポートの開始位置(y座標)
	g_camera[0].viewport.Width = SCREEN_WIDTH;		//ビューポートの幅
	g_camera[0].viewport.Height = SCREEN_HEIGHT;	//ビューポートの高さ
	g_camera[0].viewport.MinZ = 0.0f;
	g_camera[0].viewport.MaxZ = 1.0f;

	g_camera[1].viewport.X = 10;			//ビューポートの開始位置(x座標)
	g_camera[1].viewport.Y = (SCREEN_HEIGHT - 300 - 10);			//ビューポートの開始位置(y座標)	(SCREEN_HEIGHT - 250)
	g_camera[1].viewport.Width = 300;	//ビューポートの幅
	g_camera[1].viewport.Height = 300;	//ビューポートの高さ
	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;

	//視点・注視点・上方向を設定する
	g_camera[0].posV = D3DXVECTOR3(0.0f, 140.0f, -100.0f);	//現在の視点
	g_camera[0].posR = D3DXVECTOR3(0.0f, 100.0f, 00.0f);		//注視点
	g_camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//上方向(固定)

	g_camera[0].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の視点
	g_camera[0].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の注視点

	//初期化
	g_camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	g_camera[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の向き

	//視点から注視点の距離
	g_camera[0].fDistance = sqrtf((g_camera[0].posV.x - g_camera[0].posR.x) * (g_camera[0].posV.x - g_camera[0].posR.x)
		+ (g_camera[0].posV.z - g_camera[0].posR.z) * (g_camera[0].posV.z - g_camera[0].posR.z));


	//視点・注視点・上方向を設定する
	g_camera[1].posV = D3DXVECTOR3(0.0f, 800.0f, -D3DX_PI / 2.0f);	//現在の視点
	g_camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//注視点
	g_camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//上方向(固定)

	g_camera[1].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の視点
	g_camera[1].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の注視点

	//初期化
	g_camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	g_camera[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の向き

	//視点から注視点の距離
	g_camera[1].fDistance = sqrtf((g_camera[1].posV.x - g_camera[1].posR.x) * (g_camera[1].posV.x - g_camera[1].posR.x)
		+ (g_camera[1].posV.z - g_camera[1].posR.z) * (g_camera[1].posV.z - g_camera[1].posR.z));


	GetCursorPos(&g_camera[0].CenterPointer);

	g_camera[0].NowPointer = g_camera[0].CenterPointer;
}

//---------------------------------------------------
//	カメラの終了処理
//---------------------------------------------------
void UninitCamera(void)
{

}

//---------------------------------------------------
//	カメラの更新処理
//---------------------------------------------------
void UpdateCamera(void)
{
	g_camera[0].posVOld = g_camera[0].posV;


	ShowCursor(false);	// trueでカーソル表示、falseで非表示

	//カーソルの位置を NowPointer に入れる
	GetCursorPos(&g_camera[0].NowPointer);

	//中心の位置から現在の位置を引いて、移動量計算
	g_camera[0].MovePointer.x = g_camera[0].CenterPointer.x - g_camera[0].NowPointer.x;
	g_camera[0].MovePointer.y = g_camera[0].CenterPointer.y - g_camera[0].NowPointer.y;

	//注視点の旋回
	if (g_camera[0].MovePointer.x != 0.0f)
	{//左右マウス移動
		g_camera[0].rot.y -= g_camera[0].MovePointer.x * 0.0005f;
	}

	//移動量分を位置に加算
	g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
	g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * g_camera[0].fDistance;

	//注視点の旋回(左右)
	if (GetKeyboardPress(DIK_Q) == true)
	{//Qキーが押された(左方向)
		g_camera[0].rot.y -= 0.01f;
		g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{//Eキーが押された(右方向)
		g_camera[0].rot.y += 0.01f;
		g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}

	//注視点の旋回(上下)
	if (GetKeyboardPress(DIK_R) == true)
	{//Rキーが押された(左方向)
		g_camera[0].posR.y += 2.0f;
	}
	else if (GetKeyboardPress(DIK_F) == true)
	{//Fキーが押された(右方向)
		g_camera[0].posR.y -= 2.0f;
	}

	//視点の旋回(上下)
	if (GetKeyboardPress(DIK_T) == true)
	{//Rキーが押された(左方向)
		g_camera[0].posV.y += 2.0f;
	}
	else if (GetKeyboardPress(DIK_G) == true)
	{//Fキーが押された(右方向)
		g_camera[0].posV.y -= 2.0f;
	}

	//視点の旋回(左右)
	if (GetKeyboardPress(DIK_Z) == true)
	{//Zキーが押された(左方向)
		g_camera[0].rot.y -= 0.01f;
		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{//Cキーが押された(右方向)
		g_camera[0].rot.y += 0.01f;
		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}

	//プレイヤー追従処理
	Player * pPlayer = GetPlayer();		//プレイヤーの情報を取得

	//目的の注視点の位置を計算
	g_camera[0].posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 10.0f;
	g_camera[0].posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 10.0f;
	//目的の視点の位置を計算
	g_camera[0].posVDest.x = pPlayer->pos.x - sinf(g_camera[0].rot.y) * 100.0f;
	g_camera[0].posVDest.z = pPlayer->pos.z - cosf(g_camera[0].rot.y) * 100.0f;

	//目的の注視点位置まで移動
	g_camera[0].posR.x += (g_camera[0].posRDest.x - g_camera[0].posR.x) * 0.05f;
	g_camera[0].posR.z += (g_camera[0].posRDest.z - g_camera[0].posR.z) * 0.05f;
	//目的の視点位置まで移動
	g_camera[0].posV.x += (g_camera[0].posVDest.x - g_camera[0].posV.x) * 0.05f;
	g_camera[0].posV.z += (g_camera[0].posVDest.z - g_camera[0].posV.z) * 0.05f;

	//角度の正規化
	if (g_camera[0].rot.y > D3DX_PI)
	{
		g_camera[0].rot.y -= D3DX_PI * 2;
	}
	else if (g_camera[0].rot.y < -D3DX_PI)
	{
		g_camera[0].rot.y += D3DX_PI * 2;
	}

	if (g_camera[0].rot.z > D3DX_PI)
	{
		g_camera[0].rot.z -= D3DX_PI * 2;
	}
	else if (g_camera[0].rot.z < -D3DX_PI)
	{
		g_camera[0].rot.z += D3DX_PI * 2;
	}

	if (g_camera[0].rot.x > D3DX_PI)
	{
		g_camera[0].rot.x -= D3DX_PI * 2;
	}
	else if (g_camera[0].rot.x < -D3DX_PI)
	{
		g_camera[0].rot.x += D3DX_PI * 2;
	}

	/*
*/

	//カメラの移動
	//MoveCamera();
}

//---------------------------------------------------
//	カメラの移動処理
//---------------------------------------------------
void MoveCamera(void)
{
	for (int i = 0; i < 1; i++)
	{
		if (GetKeyboardPress(DIK_W) == true)
		{//Wキーが押された
			if (GetKeyboardPress(DIK_D) == true)
			{//Dキーと押されたとき
				g_camera[i].posV.x += sinf(g_camera[i].rot.y + (D3DX_PI / 4)) * CAMERA_SPEED;			//視点の位置移動
				g_camera[i].posV.z += cosf(g_camera[i].rot.y + (D3DX_PI / 4)) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//注視点の位置移動
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//Aキーと押されたとき
				g_camera[i].posV.x += sinf(g_camera[i].rot.y - (D3DX_PI / 4)) * CAMERA_SPEED;			//視点の位置移動
				g_camera[i].posV.z += cosf(g_camera[i].rot.y - (D3DX_PI / 4)) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//注視点の位置移動
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
			else
			{//Wキーのみ(正面に進む)
				g_camera[i].posV.x += sinf(g_camera[i].rot.y) * CAMERA_SPEED;							//視点の位置移動
				g_camera[i].posV.z += cosf(g_camera[i].rot.y) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//注視点の位置移動
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
		}
		else  if (GetKeyboardPress(DIK_S) == true)
		{//Sキーが押された
			if (GetKeyboardPress(DIK_D) == true)
			{//Dキーと押されたとき
				g_camera[i].posV.x += sinf(g_camera[i].rot.y + (D3DX_PI / 4 * 3.0f)) * CAMERA_SPEED;	//視点の位置移動
				g_camera[i].posV.z += cosf(g_camera[i].rot.y + (D3DX_PI / 4 * 3.0f)) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//注視点の位置移動
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//Aキーと押されたとき
				g_camera[i].posV.x += sinf(g_camera[i].rot.y - (D3DX_PI / 4 * 3.0f)) * CAMERA_SPEED;	//視点の位置移動
				g_camera[i].posV.z += cosf(g_camera[i].rot.y - (D3DX_PI / 4 * 3.0f)) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//注視点の位置移動
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
			else
			{//Sキーのみ(後ろに進む)
				g_camera[i].posV.x += sinf(g_camera[i].rot.y - D3DX_PI) * CAMERA_SPEED;				//視点の位置移動
				g_camera[i].posV.z += cosf(g_camera[i].rot.y - D3DX_PI) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//注視点の位置移動
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dキーが押された(右に進む)
			g_camera[i].posV.x += sinf(g_camera[i].rot.y + (D3DX_PI / 2)) * CAMERA_SPEED;			//視点の位置移動
			g_camera[i].posV.z += cosf(g_camera[i].rot.y + (D3DX_PI / 2)) * CAMERA_SPEED;

			g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//注視点の位置移動
			g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{//Aキーが押された(左に進む)
			g_camera[i].posV.x += sinf(g_camera[i].rot.y - (D3DX_PI / 2)) * CAMERA_SPEED;			//視点の位置移動
			g_camera[i].posV.z += cosf(g_camera[i].rot.y - (D3DX_PI / 2)) * CAMERA_SPEED;

			g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//注視点の位置移動
			g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
		}
	}
}

//---------------------------------------------------
//	カメラの設定
//---------------------------------------------------
void SetCamera(int nCnt)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nCnt].mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera[nCnt].mtxView,
		&g_camera[nCnt].posV,
		&g_camera[nCnt].posR,
		&g_camera[nCnt].vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCnt].mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nCnt].mtxProjection);

	switch (nCnt)
	{//カメラによってアスペクト比を変える
	case 0:
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&g_camera[nCnt].mtxProjection,
			D3DXToRadian(45.0f),							//視野角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//アスペクト比
			10.0f,			//どこから(ニア)
			1000.0f);		//どこまで(ファー)
		break;

	case 1:
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&g_camera[nCnt].mtxProjection,
			D3DXToRadian(45.0f),							//視野角
			(float)250 / (float)250,		//アスペクト比
			10.0f,			//どこから(ニア)
			1000.0f);		//どこまで(ファー)
		break;
	}

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCnt].mtxProjection);
}

//---------------------------------------------------
//	カメラの情報
//---------------------------------------------------
CAMERA * GetCamera(void)
{
	return g_camera;
}
