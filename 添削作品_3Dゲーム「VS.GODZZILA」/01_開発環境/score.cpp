//----------------------------------------
//　スコアの処理
//　Author：橋野幹生
//----------------------------------------
#include "score.h"
#include "main.h"
#include "bill.h"

typedef struct
{
	D3DXVECTOR3 pos[8];
	D3DXVECTOR3 size[8];
	bool bUse;
}Score;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;

Score g_Score[MAX_SCORE];
int aPosTexU[MAX_SCORE][8];	//各桁の数字を格納

//----------------------------------------
//  スコアの初期化設定処理
//----------------------------------------
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureScore);

	for (int i = 0; i < MAX_SCORE; i++)
	{
		for (int nCntScore = 0; nCntScore < 8; nCntScore++)
		{
			g_Score[i].pos[nCntScore] = D3DXVECTOR3(0.0f + (30.0f * nCntScore), 0.0f + (50.0f * i), 0.0f);		//位置の初期
		}
		g_Score[i].bUse = false;
	}

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_SCORE; i++)
	{
		for (int nCntScore = 0; nCntScore < 8; nCntScore++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Score[i].pos[nCntScore].x - 20.0f, g_Score[i].pos[nCntScore].y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Score[i].pos[nCntScore].x + 20.0f, g_Score[i].pos[nCntScore].y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Score[i].pos[nCntScore].x - 20.0f, g_Score[i].pos[nCntScore].y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Score[i].pos[nCntScore].x + 20.0f, g_Score[i].pos[nCntScore].y + 25.0f, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//----------------------------------------
//　スコアの終了処理
//----------------------------------------
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//----------------------------------------
//  プレイヤーの更新処理
//----------------------------------------
void UpdateScore(void)
{
	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_SCORE; i++)
	{
		for (int nCntScore = 0; nCntScore < 8; nCntScore++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Score[i].pos[nCntScore].x - (g_Score[i].size[nCntScore].x / 2.0f), g_Score[i].pos[nCntScore].y - (g_Score[i].size[nCntScore].y / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Score[i].pos[nCntScore].x + (g_Score[i].size[nCntScore].x / 2.0f), g_Score[i].pos[nCntScore].y - (g_Score[i].size[nCntScore].y / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Score[i].pos[nCntScore].x - (g_Score[i].size[nCntScore].x / 2.0f), g_Score[i].pos[nCntScore].y + (g_Score[i].size[nCntScore].y / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Score[i].pos[nCntScore].x + (g_Score[i].size[nCntScore].x / 2.0f), g_Score[i].pos[nCntScore].y + (g_Score[i].size[nCntScore].y / 2.0f), 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[i][nCntScore], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[i][nCntScore] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[i][nCntScore], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[i][nCntScore] + 0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//----------------------------------------
//  スコアの描画処理
//----------------------------------------
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	int nCnt = 0;

	for (int i = 0; i < MAX_SCORE; i++)
	{
		if (g_Score[i].bUse == true)
		{
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			for (int nCntScore = 0; nCntScore < 8; nCntScore++, nCnt++)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureScore);

				//ポリゴンの設定
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
			}
		}
	}
}

//----------------------------------------
//  スコアの設定処理
//----------------------------------------
void SetScore(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_SCORE; i++)
	{
		if (g_Score[i].bUse == false)
		{
			aPosTexU[i][0] = nScore % 100000000 / 10000000;
			aPosTexU[i][1] = nScore % 10000000 / 1000000;
			aPosTexU[i][2] = nScore % 1000000 / 100000;
			aPosTexU[i][3] = nScore % 100000 / 10000;
			aPosTexU[i][4] = nScore % 10000 / 1000;
			aPosTexU[i][5] = nScore % 1000 / 100;
			aPosTexU[i][6] = nScore % 100 / 10;
			aPosTexU[i][7] = nScore % 10;


			for (int nCntScore = 0; nCntScore < 8; nCntScore++)
			{
				g_Score[i].pos[nCntScore] = D3DXVECTOR3((((size.x / 4) * 3) * nCntScore) + pos.x, pos.y, pos.z);
				g_Score[i].size[nCntScore] = size;
			}
			g_Score[i].bUse = true;

			break;
		}
	}
}
