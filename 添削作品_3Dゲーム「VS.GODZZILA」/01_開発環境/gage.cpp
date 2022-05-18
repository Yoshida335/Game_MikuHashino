//----------------------------------------
//　ライフゲージ処理
//　Author：橋野幹生
//----------------------------------------
#include "gage.h"
#include "shadow.h"
#include "input.h"

//マクロ定義
#define GAGE_X		(20.0f)	// x方向への値	横幅
#define GAGE_Y		(5.0f)	// y方向への値	高さ
#define GAGE_Z		(0.0f)	// z方向への値	縦幅

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGage[2] = {};		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureGage[2] = {};			//テクスチャ
Gage g_aGage[MAX_GAGE];

//---------------------------------------------------
//	ライフゲージ初期化
//---------------------------------------------------
void InitGage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\gage.png",
		&g_pTextureGage[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\gage_waku.png",
		&g_pTextureGage[1]);

	//ライフゲージ各値初期化
	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		g_aGage[nCntGage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGage[nCntGage].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGage[nCntGage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGage[nCntGage].bUse = false;
		g_aGage[nCntGage].nLife = 0;
		g_aGage[nCntGage].nMaxLife = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_GAGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGage[0],
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_GAGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGage[1],
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffGage[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-GAGE_X, GAGE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(GAGE_X, GAGE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-GAGE_X, -GAGE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(GAGE_X, -GAGE_Y, 0.0f);

		//各頂点の法線の設定(ベクトルの大きさは１にする)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffGage[0]->Unlock();


	//頂点バッファをロック
	g_pVtxBuffGage[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-GAGE_X, GAGE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(GAGE_X, GAGE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-GAGE_X, -GAGE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(GAGE_X, -GAGE_Y, 0.0f);

		//各頂点の法線の設定(ベクトルの大きさは１にする)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffGage[1]->Unlock();
}

//---------------------------------------------------
//	ライフゲージ終了処理
//---------------------------------------------------
void UninitGage(void)
{
	for (int i = 0; i < 2; i++)
	{
		if (g_pVtxBuffGage[i] != NULL)
		{
			g_pVtxBuffGage[i]->Release();
			g_pVtxBuffGage[i] = NULL;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (g_pTextureGage[i] != NULL)
		{
			g_pTextureGage[i]->Release();
			g_pTextureGage[i] = NULL;
		}
	}
}

//---------------------------------------------------
//	ライフゲージ更新処理
//---------------------------------------------------
void UpdateGage(void)
{
	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffGage[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		if (g_aGage[nCntGage].bUse)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + ((0.5f / g_aGage[nCntGage].nMaxLife) * (g_aGage[nCntGage].nMaxLife - g_aGage[nCntGage].nLife)), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + ((0.5f / g_aGage[nCntGage].nMaxLife) * (g_aGage[nCntGage].nMaxLife - g_aGage[nCntGage].nLife)), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + ((0.5f / g_aGage[nCntGage].nMaxLife) * (g_aGage[nCntGage].nMaxLife - g_aGage[nCntGage].nLife)), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + ((0.5f / g_aGage[nCntGage].nMaxLife) * (g_aGage[nCntGage].nMaxLife - g_aGage[nCntGage].nLife)), 1.0f);

			if (g_aGage[nCntGage].nLife <= 0)
			{//体力が０以下になったら
				g_aGage[nCntGage].bUse = false;	//消す
			}

			//確認用
			if (GetKeyboardTrigger(DIK_O))
			{
				g_aGage[nCntGage].nLife--;
			}
		}

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffGage[0]->Unlock();

}

//---------------------------------------------------
//	ライフゲージ描画処理
//---------------------------------------------------
void DrawGage(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	// Zバッファに関して
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (int i = 0; i < 2; i++)
	{
		for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
		{
			if (g_aGage[nCntGage].bUse == true)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aGage[nCntGage].mtxWorld);

				D3DXMATRIX mtxView;
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);	//ビューマトリックス取得

																//カメラの逆行性を設定
				g_aGage[nCntGage].mtxWorld._11 = mtxView._11;
				g_aGage[nCntGage].mtxWorld._12 = mtxView._21;
				g_aGage[nCntGage].mtxWorld._13 = mtxView._31;
				g_aGage[nCntGage].mtxWorld._21 = mtxView._12;
				g_aGage[nCntGage].mtxWorld._22 = mtxView._22;
				g_aGage[nCntGage].mtxWorld._23 = mtxView._32;
				g_aGage[nCntGage].mtxWorld._31 = mtxView._13;
				g_aGage[nCntGage].mtxWorld._32 = mtxView._23;
				g_aGage[nCntGage].mtxWorld._33 = mtxView._33;

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aGage[nCntGage].pos.x, g_aGage[nCntGage].pos.y, g_aGage[nCntGage].pos.z);
				D3DXMatrixMultiply(&g_aGage[nCntGage].mtxWorld, &g_aGage[nCntGage].mtxWorld, &mtxTrans);

				//ライトを無効にする
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aGage[nCntGage].mtxWorld);

				//頂点バッファをデバイスのデータストリームに設定
				pDevice->SetStreamSource(0, g_pVtxBuffGage[i], 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureGage[i]);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntGage * 4,
					2);

				pDevice->SetTexture(0, NULL);

				//ライトを有効にする
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}

	// Zバッファを元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//規定値：値が現在のピクセルの値以下の場合は、新しいピクセルを受け入れる。
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//---------------------------------------------------
//	ライフゲージ設定
//---------------------------------------------------
void SetGage(D3DXVECTOR3 pos, int nLife)
{
	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		if (g_aGage[nCntGage].bUse == false)
		{
			g_aGage[nCntGage].pos = pos;
			g_aGage[nCntGage].bUse = true;
			g_aGage[nCntGage].nLife = nLife;
			g_aGage[nCntGage].nMaxLife = nLife;

			break;
		}
	}
}

//---------------------------------------------------
//	ライフゲージのダメージ処理
//---------------------------------------------------
void HitGage(int nCntGage, int nDamage)
{
	//体力を減らす
	g_aGage[nCntGage].nLife -= nDamage;

	if (g_aGage[nCntGage].nLife <= 0)
	{//体力が０以下になったら
		g_aGage[nCntGage].bUse = false;	//消す
	}
}