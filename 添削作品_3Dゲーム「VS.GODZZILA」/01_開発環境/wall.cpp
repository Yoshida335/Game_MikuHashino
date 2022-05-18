//----------------------------------------
//　壁の処理
//　Author：橋野幹生
//----------------------------------------
#include "wall.h"
#include "meshfield.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall[2] = {};			//テクスチャへポインタ
Wall g_aWall[MAX_WALL];		//壁の構造体

//---------------------------------------------------
//	壁の初期化
//---------------------------------------------------
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\WARNING.png",
		&g_pTextureWall[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\wall002.png",
		&g_pTextureWall[1]);

	//壁の各値初期化
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{//壁の最大数分回す
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//角度
		g_aWall[nCntWall].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//カラー
		g_aWall[nCntWall].bUse = false;				//使っているかどうか
		g_aWall[nCntWall].type = TYPE_WARKING;		//壁のテクスチャの種類
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{//壁の最大数分回す
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-WALL_X, WALL_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(WALL_X, WALL_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(- WALL_X, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(WALL_X, 0.0f, 0.0f);

		//各頂点の法線の設定(ベクトルの大きさは１にする)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f * 2, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f * 2, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f * 2, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f * 2, 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();

	//壁の設定
	SetWall(D3DXVECTOR3(-(MESHFIELD_SIZE / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, (-D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) , D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(-(MESHFIELD_SIZE / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) , D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, (MESHFIELD_SIZE / 2.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, (MESHFIELD_SIZE / 2.0f)), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, (-D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -(MESHFIELD_SIZE / 2.0f)), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -(MESHFIELD_SIZE / 2.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(-WALL_X, 0.0f, 0.0f), D3DXVECTOR3(0.0f, (-D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(-WALL_X, 0.0f, 0.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, WALL_X), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, WALL_X), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(WALL_X, 0.0f, 0.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(WALL_X, 0.0f, 0.0f), D3DXVECTOR3(0.0f, (-D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -WALL_X), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -WALL_X), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
}

//---------------------------------------------------
//	壁の終了処理
//---------------------------------------------------
void UninitWall(void)
{
	if (g_pVtxBuffWall != NULL)
	{//頂点バッファ破棄
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_TYPE; nCnt++)
	{
		if (g_pTextureWall[nCnt] != NULL)
		{//テクスチャ破棄
			g_pTextureWall[nCnt]->Release();
			g_pTextureWall[nCnt] = NULL;
		}
	}
}

//---------------------------------------------------
//	壁の更新処理
//---------------------------------------------------
void UpdateWall(void)
{
	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{//壁の最大数分回す
		if (g_aWall[nCntWall].bUse)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].size.x, g_aWall[nCntWall].size.y, 0.0f);	//
			pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].size.x, g_aWall[nCntWall].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].size.x, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].size.x, 0.0f, 0.0f);

			if (g_aWall[nCntWall].type == TYPE_WARKING)
			{//壁のタイプが一致したら
				//テクスチャ座標の設定
				pVtx[0].tex.x += 0.001f;
				pVtx[1].tex.x += 0.001f;
				pVtx[2].tex.x += 0.001f;
				pVtx[3].tex.x += 0.001f;
			}
		}

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------
//	壁の描画処理
//---------------------------------------------------
void DrawWall(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	// Zバッファに関して
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	// αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld,
				&g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall[g_aWall[nCntWall].type]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntWall * 4,
				2);

			pDevice->SetTexture(0, NULL);
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);

	// Zバッファを元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//規定値：値が現在のピクセルの値以下の場合は、新しいピクセルを受け入れる。
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//---------------------------------------------------
//	壁の設定
//---------------------------------------------------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 size, WALLTYPE type)
{
	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;	//位置
			g_aWall[nCntWall].rot = rot;	//角度
			g_aWall[nCntWall].col = col;	//カラー
			g_aWall[nCntWall].size = size;	//サイズ
			g_aWall[nCntWall].bUse = true;	//使っている状態にする
			g_aWall[nCntWall].type = type;	//種類

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].size.x, g_aWall[nCntWall].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( g_aWall[nCntWall].size.x, g_aWall[nCntWall].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].size.x, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( g_aWall[nCntWall].size.x, 0.0f, 0.0f);

			//頂点カラー
			pVtx[0].col = g_aWall[nCntWall].col;
			pVtx[1].col = g_aWall[nCntWall].col;
			pVtx[2].col = g_aWall[nCntWall].col;
			pVtx[3].col = g_aWall[nCntWall].col;

			if (g_aWall[nCntWall].type == TYPE_WARKING)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f * 2, 0.0f * 2);
				pVtx[1].tex = D3DXVECTOR2(1.0f * 2, 0.0f * 2);
				pVtx[2].tex = D3DXVECTOR2(0.0f * 2, 1.0f * 2);
				pVtx[3].tex = D3DXVECTOR2(1.0f * 2, 1.0f * 2);
			}
			break;
		}

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------
//	壁の情報
//---------------------------------------------------
Wall * GetWall(void)
{
	return g_aWall;
}
