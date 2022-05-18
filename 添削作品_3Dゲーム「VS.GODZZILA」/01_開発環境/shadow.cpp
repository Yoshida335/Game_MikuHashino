//----------------------------------------
//　影の処理
//　Author：橋野幹生
//----------------------------------------
#include "shadow.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;
Shadow g_aShadow[MAX_SHADOW];

//---------------------------------------------------
//	影の初期化
//---------------------------------------------------
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
		g_aShadow[nCntShadow].size = 0.0f;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//最大数分回す
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].size / 2), 0.0f, (g_aShadow[nCntShadow].size / 2));
		pVtx[1].pos = D3DXVECTOR3((g_aShadow[nCntShadow].size / 2), 0.0f, (g_aShadow[nCntShadow].size / 2));
		pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].size / 2), 0.0f, -(g_aShadow[nCntShadow].size / 2));
		pVtx[3].pos = D3DXVECTOR3((g_aShadow[nCntShadow].size / 2), 0.0f, -(g_aShadow[nCntShadow].size / 2));

		//各頂点の法線の設定(ベクトルの大きさは１にする)
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点数分+4
	}

	//頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();
}

//---------------------------------------------------
//	影の終了処理
//---------------------------------------------------
void UninitShadow(void)
{
	if (g_pVtxBuffShadow != NULL)
	{//頂点バッファの破棄
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	if (g_pTextureShadow != NULL)
	{//テクスチャの破棄
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//---------------------------------------------------
//	影の更新処理
//---------------------------------------------------
void UpdateShadow(void)
{
	//処理なし
}

//---------------------------------------------------
//	ポリゴンの描画処理
//---------------------------------------------------
void DrawShadow(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//最大数分回す
		if (g_aShadow[nCntShadow].bUse)
		{//使用している時、描画する
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld,
				&g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//αブレンディングを減算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntShadow * 4,
				2);

			//αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			pDevice->SetTexture(0, NULL);
		}
	}
}

//---------------------------------------------------
//	影の設定
//---------------------------------------------------
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float size)
{
	int nCntShadow;
	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (!g_aShadow[nCntShadow].bUse)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;
			g_aShadow[nCntShadow].size = size;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].size / 2), 0.0f, (g_aShadow[nCntShadow].size / 2));
			pVtx[1].pos = D3DXVECTOR3((g_aShadow[nCntShadow].size / 2), 0.0f, (g_aShadow[nCntShadow].size / 2));
			pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].size / 2), 0.0f, -(g_aShadow[nCntShadow].size / 2));
			pVtx[3].pos = D3DXVECTOR3((g_aShadow[nCntShadow].size / 2), 0.0f, -(g_aShadow[nCntShadow].size / 2));

			pVtx += 4;	//頂点数分+4
			break;
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;		//影の番号(index)を返す
}

//---------------------------------------------------
//	影の位置の更新処理
//---------------------------------------------------
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}

