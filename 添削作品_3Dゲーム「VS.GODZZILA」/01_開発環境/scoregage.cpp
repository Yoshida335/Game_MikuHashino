//----------------------------------------
//　ライフゲージ処理
//　Author：橋野幹生
//----------------------------------------
#include "scoregage.h"
#include "shadow.h"
#include "input.h"

//マクロ定義
#define SGAGE_X		(600.0f)	// x方向への値	横幅
#define SGAGE_Y		(100.0f)	// y方向への値	高さ
#define SGAGE_Z		(0.0f)	// z方向への値	縦幅

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreGage[2] = {};		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureScoreGage[2] = {};			//テクスチャ
ScoreGage g_aScoreGage[MAX_SCOREGAGE];

//----------------------------------------
//  タイトルの初期化設定処理
//----------------------------------------
void InitScoreGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\gage.png",
		&g_pTextureScoreGage[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\gage_waku.png",
		&g_pTextureScoreGage[1]);

	//頂点バッファの生成
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffScoreGage[nCnt],
			NULL);
	}

	for (int nCnt = 0; nCnt < MAX_SCOREGAGE; nCnt++)
	{
		g_aScoreGage[nCnt].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		g_aScoreGage[nCnt].bUse = false;
		g_aScoreGage[nCnt].nLife = 0;
		g_aScoreGage[nCnt].nMaxLife = 0;
		g_aScoreGage[nCnt].rot = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
	}

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	for (int nCnt = 0; nCnt < MAX_SCOREGAGE; nCnt++)
	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffScoreGage[0]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y - (SGAGE_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y - (SGAGE_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y + (SGAGE_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y + (SGAGE_Y / 2), 0.0f);

		//rhwの設定
		pVtx[0].rhm = 1.0f;
		pVtx[1].rhm = 1.0f;
		pVtx[2].rhm = 1.0f;
		pVtx[3].rhm = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffScoreGage[0]->Unlock();
	}

	for (int nCnt = 0; nCnt < MAX_SCOREGAGE; nCnt++)
	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffScoreGage[1]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y - (SGAGE_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y - (SGAGE_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y + (SGAGE_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y + (SGAGE_Y / 2), 0.0f);

		//rhwの設定
		pVtx[0].rhm = 1.0f;
		pVtx[1].rhm = 1.0f;
		pVtx[2].rhm = 1.0f;
		pVtx[3].rhm = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffScoreGage[1]->Unlock();
	}
}

//----------------------------------------
//  タイトルの終了処理
//----------------------------------------
void UninitScoreGage(void)
{
	int nCnt;

	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureScoreGage[nCnt] != NULL)
		{
			g_pTextureScoreGage[nCnt]->Release();
			g_pTextureScoreGage[nCnt] = NULL;
		}

		//頂点バッファの破棄
		if (g_pTextureScoreGage[nCnt] != NULL)
		{
			g_pTextureScoreGage[nCnt]->Release();
			g_pTextureScoreGage[nCnt] = NULL;
		}
	}
}

//----------------------------------------
//  タイトルの更新設定処理
//----------------------------------------
void UpdateScoreGage(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffScoreGage[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGage = 0; nCntGage < MAX_SCOREGAGE; nCntGage++)
	{
		if (g_aScoreGage[nCntGage].bUse == true)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + ((0.5f / g_aScoreGage[nCntGage].nMaxLife) * (g_aScoreGage[nCntGage].nMaxLife - g_aScoreGage[nCntGage].nLife)), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + ((0.5f / g_aScoreGage[nCntGage].nMaxLife) * (g_aScoreGage[nCntGage].nMaxLife - g_aScoreGage[nCntGage].nLife)), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + ((0.5f / g_aScoreGage[nCntGage].nMaxLife) * (g_aScoreGage[nCntGage].nMaxLife - g_aScoreGage[nCntGage].nLife)), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + ((0.5f / g_aScoreGage[nCntGage].nMaxLife) * (g_aScoreGage[nCntGage].nMaxLife - g_aScoreGage[nCntGage].nLife)), 1.0f);

			if (g_aScoreGage[nCntGage].nLife <= 0)
			{//体力が０以下になったら
				g_aScoreGage[nCntGage].bUse = false;	//消す
			}

			//確認用
			if (GetKeyboardTrigger(DIK_O) == true)
			{
				g_aScoreGage[nCntGage].nLife--;
			}
		}

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffScoreGage[0]->Unlock();
}

//----------------------------------------
//  タイトルの描画処理
//----------------------------------------
void DrawScoreGage(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffScoreGage[nCnt], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScoreGage[nCnt]);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//---------------------------------------------------
//	ライフゲージ設定
//---------------------------------------------------
void SetScoreGage(D3DXVECTOR3 pos, int nLife)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	for (int nCntScoreGage = 0; nCntScoreGage < MAX_SCOREGAGE; nCntScoreGage++)
	{
		if (g_aScoreGage[nCntScoreGage].bUse == false)
		{
			g_aScoreGage[nCntScoreGage].pos = pos;
			g_aScoreGage[nCntScoreGage].bUse = true;
			g_aScoreGage[nCntScoreGage].nLife = nLife;
			g_aScoreGage[nCntScoreGage].nMaxLife = nLife;

			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				//頂点バッファをロック
				g_pVtxBuffScoreGage[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

				//頂点座標設定
				pVtx[0].pos = D3DXVECTOR3(g_aScoreGage[nCntScoreGage].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCntScoreGage].pos.y - (SGAGE_Y / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aScoreGage[nCntScoreGage].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCntScoreGage].pos.y - (SGAGE_Y / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aScoreGage[nCntScoreGage].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCntScoreGage].pos.y + (SGAGE_Y / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aScoreGage[nCntScoreGage].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCntScoreGage].pos.y + (SGAGE_Y / 2), 0.0f);

				//頂点バッファのアンロック
				g_pVtxBuffScoreGage[nCnt]->Unlock();
			}

			break;
		}
	}
}

//---------------------------------------------------
//	ライフゲージのダメージ処理
//---------------------------------------------------
void HitScoreGage(int nCntScoreGage, int nDamage)
{
	//体力を減らす
	g_aScoreGage[nCntScoreGage].nLife -= nDamage;

	if (g_aScoreGage[nCntScoreGage].nLife <= 0)
	{//体力が０以下になったら
		g_aScoreGage[nCntScoreGage].bUse = false;	//消す
	}
}