//----------------------------------------
//　メッシュフィールドの処理
//　Author：橋野幹生
//----------------------------------------
#include "meshfield.h"

#define MESHFIELD_X_BLOCK		(3)		// X軸のブロック数
#define MESHFIELD_Z_BLOCK		(2)		// Z軸のブロック数

#define MESHFIELD_VERTEX		((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))									//メッシュの頂点
#define MESHFIELD_INDEX			((MESHFIELD_X_BLOCK  + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) * 2)	//インデックス数
#define MESHFIELD_PRIMITIVE		((MESHFIELD_X_BLOCK * MESHFIELD_Z_BLOCK * 2) + (MESHFIELD_Z_BLOCK - 1) * 4)			//ポリゴン数

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;			//メッシュフィールドのテクスチャ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;		//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshfield;		//位置
D3DXVECTOR3 g_rotMeshfield;		//向き
D3DXMATRIX g_mtxWorldMeshfield;	//ワールドマトリックス

//---------------------------------------------------
//	ポリゴンの初期化
//---------------------------------------------------
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\field006.jpg",
		&g_pTextureMeshfield);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;

	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	

	//頂点情報を設定(平面)
	/**/
	for (int nCnt_Z = 0; nCnt_Z < MESHFIELD_Z_BLOCK + 1; nCnt_Z++)
	{
		for (int nCnt_X = 0; nCnt_X < MESHFIELD_X_BLOCK + 1; nCnt_X++, nCnt++)
		{
			//頂点座標の設定
			pVtx[nCnt].pos = D3DXVECTOR3((-MESHFIELD_SIZE / 2.0f) + (MESHFIELD_SIZE / MESHFIELD_X_BLOCK) * nCnt_X, 0.0f, (MESHFIELD_SIZE / 2.0f) - (MESHFIELD_SIZE / MESHFIELD_Z_BLOCK) * nCnt_Z);

			//各頂点の法線の設定(ベクトルの大きさは１にする)
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラー
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (1.0f / MESHFIELD_X_BLOCK) * nCnt_X, 0.0f + (1.0f / MESHFIELD_Z_BLOCK) * nCnt_Z);
		}
	}

	
	
	//頂点座標の設定
	/*pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f,  50.0f);
	pVtx[1].pos = D3DXVECTOR3(	0.0f, 0.0f,  50.0f);
	pVtx[2].pos = D3DXVECTOR3( 50.0f, 0.0f,  50.0f);

	pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f,   0.0f);
	pVtx[4].pos = D3DXVECTOR3(	0.0f, 0.0f,   0.0f);
	pVtx[5].pos = D3DXVECTOR3( 50.0f, 0.0f,   0.0f);

	pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[7].pos = D3DXVECTOR3(	0.0f, 0.0f, -50.0f);
	pVtx[8].pos = D3DXVECTOR3( 50.0f, 0.0f, -50.0f);*/

	//各頂点の法線の設定(ベクトルの大きさは１にする)
	/*pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);*/

	//頂点カラー
	/*pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);*/

	//テクスチャ座標の設定
	/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);*/

	//頂点バッファのアンロック
	g_pVtxBuffMeshfield->Unlock();

	//インデックスバッファをロック
	WORD * pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	nCnt = 0;
	int nCntPlas = 0;

	//インデックスの設定
	for (int nCnt_Z = 0; nCnt_Z < MESHFIELD_Z_BLOCK; nCnt_Z++)
	{
		for (int nCnt_X = 0; nCnt_X < MESHFIELD_X_BLOCK + 1; nCnt_X++, nCnt++)
		{
			pIdx[nCnt] = (MESHFIELD_X_BLOCK + 1) + nCntPlas;
			pIdx[nCnt + 1] = nCntPlas;

			nCnt++;
			nCntPlas++;
		}

		if (nCnt_Z != (MESHFIELD_Z_BLOCK - 1))
		{
			pIdx[nCnt] = nCntPlas - 1;
			pIdx[nCnt + 1] = nCntPlas + (MESHFIELD_X_BLOCK + 1);

			nCnt += 2;
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffMeshField->Unlock();

}

//---------------------------------------------------
//	ポリゴンの終了処理
//---------------------------------------------------
void UninitMeshfield(void)
{
	//頂点バッファ破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//---------------------------------------------------
//	ポリゴンの更新処理
//---------------------------------------------------
void UpdateMeshfield(void)
{

}

//---------------------------------------------------
//	ポリゴンの描画処理
//---------------------------------------------------
void DrawMeshfield(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield,
		&g_mtxWorldMeshfield, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX, 0, MESHFIELD_PRIMITIVE);

	pDevice->SetTexture(0, NULL);
}

