//----------------------------------------
//　リザルト画面の処理
//　Author：橋野幹生
//----------------------------------------
#include "result.h"
#include "input.h"
#include "fade.h"
#include "bill.h"
#include "score.h"
#include "resultscore.h"
#include "time.h"
#include "sound.h"
#include <stdio.h>
#include <string.h>

#define MAX_RESULT	(3)
#define MAX_SIGN	(126)

LPDIRECT3DTEXTURE9 g_pTextureResult = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResultScore = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultScore = NULL;	//頂点バッファへのポインタ

LPDIRECT3DTEXTURE9 g_pTextureSign = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSign = NULL;	//頂点バッファへのポインタ

typedef struct
{
	int fParcent;	//破壊したモデルの㌫
	int fModel;		//生き残っているモデル数
	int fMaxModel;	//配置していたモデル数
}Result;
Result g_Result;

typedef struct
{
	D3DXVECTOR3 pos[5];
	D3DXVECTOR3 size[5];
	bool bUse;
}ResultScore;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	bool bUse;
	SignType nType;
}Sign;

ResultScore g_ResultS[MAX_RESULT];
Sign g_Sign[MAX_SIGN];
int g_aPosTexU[MAX_RESULT][5];	//各桁の数字を格納
int g_FinishResultScore = 0;
bool g_bResult;		//リザルト1回だけ起動用

//----------------------------------------
//　リザルト情報をロード
//----------------------------------------
void LoadP(void)
{
	FILE * pFile;

	//確認用
	//ファイルを開く
	pFile = fopen("data\\result.txt", "r");		//(テキスト名を指定, モードを指定)

	if (pFile != NULL)
	{//ファイルが開けた場合

		fscanf(pFile, "%d\n", &g_Result.fParcent);
		fscanf(pFile, "%d\n", &g_Result.fModel);
		fscanf(pFile, "%d\n", &g_Result.fMaxModel);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("\n***　ファイルが開けませんでした　***\n");
	}

	SaveParcent();
}

//----------------------------------------
//　リザルトの初期化処理
//----------------------------------------
void InitResult(void)
{
	LoadP();

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result.png",
		&g_pTextureResult);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureResultScore);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\符号.png",
		&g_pTextureSign);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 5 * MAX_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultScore,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SIGN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSign,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhm = 1.0f;
		pVtx[1].rhm = 1.0f;
		pVtx[2].rhm = 1.0f;
		pVtx[3].rhm = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffResult->Unlock();
	}

	{
		for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
		{
			for (int nCntScore = 0; nCntScore < 5; nCntScore++)
			{
				g_ResultS[nCnt].pos[nCntScore] = D3DXVECTOR3(35.0f * nCntScore + 990.0f, 25.0f, 0.0f);	//位置設定
			}
			g_ResultS[nCnt].bUse = false;
		}

		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffResultScore->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
		{
			for (int nCntScore = 0; nCntScore < 5; nCntScore++)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_ResultS[nCnt].pos[nCntScore].x - 20.0f, g_ResultS[nCnt].pos[nCntScore].y - 25.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_ResultS[nCnt].pos[nCntScore].x + 20.0f, g_ResultS[nCnt].pos[nCntScore].y - 25.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_ResultS[nCnt].pos[nCntScore].x - 20.0f, g_ResultS[nCnt].pos[nCntScore].y + 25.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_ResultS[nCnt].pos[nCntScore].x + 20.0f, g_ResultS[nCnt].pos[nCntScore].y + 25.0f, 0.0f);

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
		g_pVtxBuffResultScore->Unlock();
	}

	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffSign->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_SIGN; nCnt++)
		{
			g_Sign[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Sign[nCnt].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Sign[nCnt].nType = SignType_01;
			g_Sign[nCnt].bUse = false;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Sign[nCnt].pos.x - 20.0f, g_Sign[nCnt].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Sign[nCnt].pos.x + 20.0f, g_Sign[nCnt].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Sign[nCnt].pos.x - 20.0f, g_Sign[nCnt].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Sign[nCnt].pos.x + 20.0f, g_Sign[nCnt].pos.y + 25.0f, 0.0f);

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

		//頂点バッファをアンロックする
		g_pVtxBuffSign->Unlock();
	}

	//％
	{
		SetResult(g_Result.fParcent, D3DXVECTOR3(220.0f, 150.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
		SetSign(D3DXVECTOR3(347.0f, 150, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f), SignType_06);

		SetSign(D3DXVECTOR3(550.0f, 150, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f), SignType_01);

		SetResultScore((100), D3DXVECTOR3(620.0f, 150.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
		SetSign(D3DXVECTOR3(795.0f, 150.0f, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f), SignType_02);
		SetScore((g_Result.fParcent * 100), D3DXVECTOR3(895.0f, 150.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
	}

	//モデル数
	{
		SetResultScore((g_Result.fModel), D3DXVECTOR3(320.0f, 300.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
		//SetResultScore((g_Result.fMaxModel), D3DXVECTOR3(250.0f, 300.0f, 0.0f), D3DXVECTOR3(40.0f, 50.0f, 0.0f));

		SetSign(D3DXVECTOR3(550.0f, 300, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f), SignType_01);

		SetResultScore((500), D3DXVECTOR3(620.0f, 300.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
		SetSign(D3DXVECTOR3(795.0f, 300.0f, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f), SignType_02);
		SetScore((g_Result.fModel * 500), D3DXVECTOR3(895.0f, 300.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
	}

	int * pTime = GetTime();

	//タイム
	{
		SetResultScore((*pTime), D3DXVECTOR3(320.0f, 450.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));

		SetSign(D3DXVECTOR3(550.0f, 450.0f, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f), SignType_01);

		SetResultScore((100), D3DXVECTOR3(620.0f, 450.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
		SetSign(D3DXVECTOR3(795.0f, 450.0f, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f), SignType_02);
		SetScore((*pTime * 100), D3DXVECTOR3(895.0f, 450.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
	}

	//総評
	SetScore(((g_Result.fParcent * 100) + (g_Result.fModel * 500) + (*pTime * 100)), D3DXVECTOR3(790.0f, 620.0f, 0.0f), D3DXVECTOR3(80.0f, 100.0f, 0.0f));
	//最終スコアを保存
	g_FinishResultScore = ((g_Result.fParcent * 100) + (g_Result.fModel * 500) + (*pTime * 100));

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_RESULT);

	g_bResult = false;
}

//----------------------------------------
//　リザルトの終了処理
//----------------------------------------
void UninitResult(void)
{
	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureResultScore != NULL)
	{
		g_pTextureResultScore->Release();
		g_pTextureResultScore = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureSign != NULL)
	{
		g_pTextureSign->Release();
		g_pTextureSign = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResultScore != NULL)
	{
		g_pVtxBuffResultScore->Release();
		g_pVtxBuffResultScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSign != NULL)
	{
		g_pVtxBuffSign->Release();
		g_pVtxBuffSign = NULL;
	}
}

//----------------------------------------
//　リザルトの更新処理
//----------------------------------------
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true && g_bResult == false)
	{
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_RANKING);

		g_bResult = true;
	}

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_RESULT; i++)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_ResultS[i].pos[nCnt].x - (g_ResultS[i].size[nCnt].x / 2.0f), g_ResultS[i].pos[nCnt].y - (g_ResultS[i].size[nCnt].y / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ResultS[i].pos[nCnt].x + (g_ResultS[i].size[nCnt].x / 2.0f), g_ResultS[i].pos[nCnt].y - (g_ResultS[i].size[nCnt].y / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ResultS[i].pos[nCnt].x - (g_ResultS[i].size[nCnt].x / 2.0f), g_ResultS[i].pos[nCnt].y + (g_ResultS[i].size[nCnt].y / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ResultS[i].pos[nCnt].x + (g_ResultS[i].size[nCnt].x / 2.0f), g_ResultS[i].pos[nCnt].y + (g_ResultS[i].size[nCnt].y / 2.0f), 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * g_aPosTexU[i][nCnt], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * g_aPosTexU[i][nCnt] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * g_aPosTexU[i][nCnt], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * g_aPosTexU[i][nCnt] + 0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResultScore->Unlock();

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffSign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_SIGN; i++)
	{
		if (g_Sign[i].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Sign[i].pos.x - (g_Sign[i].size.x / 2.0f), g_Sign[i].pos.y - (g_Sign[i].size.y / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Sign[i].pos.x + (g_Sign[i].size.x / 2.0f), g_Sign[i].pos.y - (g_Sign[i].size.y / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Sign[i].pos.x - (g_Sign[i].size.x / 2.0f), g_Sign[i].pos.y + (g_Sign[i].size.y / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Sign[i].pos.x + (g_Sign[i].size.x / 2.0f), g_Sign[i].pos.y + (g_Sign[i].size.y / 2.0f), 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((1.0f / SignType_MAX) * g_Sign[i].nType, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((1.0f / SignType_MAX) * g_Sign[i].nType + (1.0f / SignType_MAX), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((1.0f / SignType_MAX) * g_Sign[i].nType, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / SignType_MAX) * g_Sign[i].nType + (1.0f / SignType_MAX), 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSign->Unlock();
}

//----------------------------------------
//　リザルトの描画処理
//----------------------------------------
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	int nCnt = 0;

	for (int i = 0; i < MAX_RESULT; i++)
	{
		if (g_ResultS[i].bUse == true)
		{
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffResultScore, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			for (int nCntResultScore = 0; nCntResultScore < 5; nCntResultScore++, nCnt++)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureResultScore);

				//ポリゴンの設定
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
			}
		}
	}

	for (int i = 0; i < MAX_SIGN; i++)
	{
		if (g_Sign[i].bUse == true)
		{
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffSign, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSign);

			//ポリゴンの設定
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
		}
	}

}

//----------------------------------------
//　
//----------------------------------------
void SetResult(int nParcent, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_RESULT; i++)
	{
		if (g_ResultS[i].bUse == false)
		{
			g_aPosTexU[i][0] = nParcent % 100000 / 10000;
			g_aPosTexU[i][1] = nParcent % 10000 / 1000;
			g_aPosTexU[i][2] = nParcent % 1000 / 100;
			g_aPosTexU[i][3] = nParcent % 100 / 10;
			g_aPosTexU[i][4] = nParcent % 10;

			for (int nCntResultScore = 0; nCntResultScore < 5; nCntResultScore++)
			{
				g_ResultS[i].pos[nCntResultScore] = D3DXVECTOR3((((size.x / 5) * 4) * nCntResultScore) + pos.x, pos.y, pos.z);
				g_ResultS[i].size[nCntResultScore] = size;
			}

			g_ResultS[i].pos[3] = D3DXVECTOR3((((size.x / 5) * 4) * 3) + 10.0f + pos.x, pos.y, pos.z);
			g_ResultS[i].pos[4] = D3DXVECTOR3((((size.x / 5) * 4) * 4) + 10.0f + pos.x, pos.y, pos.z);

			g_ResultS[i].bUse = true;

			break;
		}
	}
}

//----------------------------------------
//　
//----------------------------------------
void SetSign(D3DXVECTOR3 pos, D3DXVECTOR3 size, SignType type)
{
	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffSign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_SIGN; i++)
	{
		if (g_Sign[i].bUse == false)
		{
			g_Sign[i].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);
			g_Sign[i].size = size;
			g_Sign[i].bUse = true;
			g_Sign[i].nType = type;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Sign[i].pos.x - (g_Sign[i].size.x / 2.0f), g_Sign[i].pos.y - (g_Sign[i].size.y / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Sign[i].pos.x + (g_Sign[i].size.x / 2.0f), g_Sign[i].pos.y - (g_Sign[i].size.y / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Sign[i].pos.x - (g_Sign[i].size.x / 2.0f), g_Sign[i].pos.y + (g_Sign[i].size.y / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Sign[i].pos.x + (g_Sign[i].size.x / 2.0f), g_Sign[i].pos.y + (g_Sign[i].size.y / 2.0f), 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((1.0f / SignType_MAX) * g_Sign[i].nType, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((1.0f / SignType_MAX) * g_Sign[i].nType + (1.0f / SignType_MAX), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((1.0f / SignType_MAX) * g_Sign[i].nType, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / SignType_MAX) * g_Sign[i].nType + (1.0f / SignType_MAX), 1.0f);

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSign->Unlock();
}

int GetResultScore(void)
{
	return g_FinishResultScore;
}