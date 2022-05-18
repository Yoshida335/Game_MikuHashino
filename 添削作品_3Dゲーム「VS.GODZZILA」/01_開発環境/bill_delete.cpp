//----------------------------------------
//　ビル(破壊後)の処理
//　Author：橋野幹生
//----------------------------------------
#include "bill_delete.h"
#include "input.h"
#include "shadow.h"
#include "fade.h"
#include "sound.h"
#include "gage.h"
#include <stdio.h>
#include <string.h>

//グローバル変数宣言
LPD3DXMESH g_pMeshDeleteModel = NULL;			//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatDeleteModel = NULL;		//マテリアル情報へのポインタ
DWORD g_nNumMatDeleteModel = 0;					//マテリアル情報の数
BillDelete g_aDeleteModel[MAX_BILLDELETE];	//ビル(破壊後)の構造体
D3DXMATERIAL * g_pMatDeleteModel;			//マテリアルデータへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureDelete[10];	//テクスチャへのポインタ

//---------------------------------------------------
//	ビル(破壊後)の初期化処理
//---------------------------------------------------
void InitBillDelete(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Ⅹファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\bill_off.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatDeleteModel,
		NULL,
		&g_nNumMatDeleteModel,
		&g_pMeshDeleteModel);

	//マテリアルデータへのポインタを取得
	g_pMatDeleteModel = (D3DXMATERIAL*)g_pBuffMatDeleteModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatDeleteModel; nCntMat++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			g_pMatDeleteModel[nCntMat].pTextureFilename,
			&g_pTextureDelete[nCntMat]);
	}

	//各値の初期化
	for (int nCntModel = 0; nCntModel < MAX_BILLDELETE; nCntModel++)
	{
		g_aDeleteModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_aDeleteModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
		g_aDeleteModel[nCntModel].bUse = false;							//使ってるかどうか
	}
}

//---------------------------------------------------
//	ビル(破壊後)の終了処理
//---------------------------------------------------
void UninitBillDelete(void)
{
	//メッシュ破棄
	if (g_pMeshDeleteModel != NULL)
	{
		g_pMeshDeleteModel->Release();
		g_pMeshDeleteModel = NULL;
	}

	//マテリアル破棄
	if (g_pBuffMatDeleteModel != NULL)
	{
		g_pBuffMatDeleteModel->Release();
		g_pBuffMatDeleteModel = NULL;
	}

	//テクスチャ破棄
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatDeleteModel; nCntMat++)
	{
		if (g_pTextureDelete[nCntMat] != NULL)
		{
			g_pTextureDelete[nCntMat]->Release();
			g_pTextureDelete[nCntMat] = NULL;
		}
	}
}

//---------------------------------------------------
//	ビル(破壊後)の更新処理
//---------------------------------------------------
void UpdateBillDelete(void)
{
	//処理なし
}

//---------------------------------------------------
//	ビル(破壊後)の描画処理
//---------------------------------------------------
void DrawBillDelete(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL * pMat;			//マテリアルデータへのポインタ

	for (int nCntModel = 0; nCntModel < MAX_BILLDELETE; nCntModel++)
	{
		if (g_aDeleteModel[nCntModel].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aDeleteModel[nCntModel].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aDeleteModel[nCntModel].rot.y, g_aDeleteModel[nCntModel].rot.x, g_aDeleteModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aDeleteModel[nCntModel].mtxWorld,
				&g_aDeleteModel[nCntModel].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aDeleteModel[nCntModel].pos.x, g_aDeleteModel[nCntModel].pos.y, g_aDeleteModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aDeleteModel[nCntModel].mtxWorld, &g_aDeleteModel[nCntModel].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aDeleteModel[nCntModel].mtxWorld);

			//現在のマテリアル保持
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatDeleteModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatDeleteModel; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureDelete[nCntMat]);

				//モデルパーツの描画
				g_pMeshDeleteModel->DrawSubset(nCntMat);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureDelete[nCntMat]);
			}

			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------
//	ビル(破壊後)の設定
//---------------------------------------------------
void SetBillDelete(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntModel = 0; nCntModel < MAX_BILLDELETE; nCntModel++)
	{
		if (!g_aDeleteModel[nCntModel].bUse)
		{// bUseがfalseだったら、
			g_aDeleteModel[nCntModel].pos = pos;	//位置
			g_aDeleteModel[nCntModel].rot = rot;	//角度
			g_aDeleteModel[nCntModel].bUse = true;	//使っている状態にする
			break;
		}
	}
}