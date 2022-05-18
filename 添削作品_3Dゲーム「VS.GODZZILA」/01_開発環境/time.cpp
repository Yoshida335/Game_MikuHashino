//----------------------------------------
//　タイムの処理
//　Author：橋野幹生
//----------------------------------------
#include "time.h"
#include "fade.h"
#include "input.h"
#include "map.h"
#include "enemy.h"
#include <time.h>

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
D3DXVECTOR3 g_posTime[3];	//タイムの数
int g_nTime;				//現在のタイム
int g_nCntTime;				//カウントタイム
TIME g_TimeState;			//タイムの状態
bool g_bFinishTime = false;	//タイム終了時の画面遷移を一回起動する用

//----------------------------------------
//  タイムの初期化設定処理
//----------------------------------------
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureTime);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期
	}
	g_nTime = 30;				//タイムの初期化
	g_nCntTime = 60;			//タイムの更新時間初期化
	g_TimeState = TIME_ON;		//タイムの状態初期化(起動中)
	g_bFinishTime = false;		//falseにする

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D * pVtx;	//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{//タイムの位置設定
		g_posTime[nCntT] = D3DXVECTOR3(35.0f * nCntT + (SCREEN_WIDTH / 2) - 35.0f, 40.0f, 0.0f);
	}

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntT].x - 20.0f, g_posTime[nCntT].y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntT].x + 20.0f, g_posTime[nCntT].y - 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntT].x - 20.0f, g_posTime[nCntT].y + 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntT].x + 20.0f, g_posTime[nCntT].y + 25.0f, 0.0f);

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
	g_pVtxBuffTime->Unlock();
}

//----------------------------------------
//　タイムの終了処理
//----------------------------------------
void UninitTime(void)
{
	//テクスチャの破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//----------------------------------------
//  タイムの更新処理
//----------------------------------------
void UpdateTime(void)
{
	int nTimePos[3];

	switch (g_TimeState)
	{
	case TIME_ON:	//タイム起動中(ゲーム開始)
		if (g_nTime != 0)
		{//現在の時間が０じゃなかったら
		 //カウント数を1減らす
			g_nCntTime--;
		}

		if (g_nCntTime <= 0)
		{//カウント数が０だったら
			g_nTime--;

			if (g_nTime % 10 == 0)
			{//時間経過でエネミー出現
				//エネミーの出現位置を持ってくる(map.cpp)
				SetPos * pSetEnemyPos = GetSetPos();
			
				for (int i = 0; i < 4; i++)
				{//エネミー出現
					SetEnemy(pSetEnemyPos->Setpos[i], D3DXVECTOR3(0.0f, 0.0f, 0.0f), TYPE_ENEMY_01, 1);
				}
			}

			//カウント数をリセット
			g_nCntTime = 60;
		}

		//現在時刻からタイムのテクスチャ座標を計算
		nTimePos[0] = g_nTime % 1000 / 100;
		nTimePos[1] = g_nTime % 100 / 10;
		nTimePos[2] = g_nTime % 10;

		VERTEX_2D * pVtx;	//頂点情報へのポインタ

		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntT = 0; nCntT < 3; nCntT++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT] + 0.1f, 1.0f);

			pVtx += 4;
		}

		//頂点バッファをアンロックする
		g_pVtxBuffTime->Unlock();

		if (g_nTime <= 0)
		{//タイムが０以下になったら
			g_TimeState = TIME_OFF;	//タイムオフにする
		}

		break;

	case TIME_OFF:	//タイムオフ(ゲーム終了)
		if(g_bFinishTime == false)
		{//一回だけ起動する
			//モード設定(リザルト画面に移行)
			SetFade(MODE_RESULT);

			g_bFinishTime = true;
		}

		break;
	}
}

//----------------------------------------
//  タイムの描画処理
//----------------------------------------
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	// Zバッファに関して
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntT * 4, 2);
	}

	// Zバッファを元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//規定値：値が現在のピクセルの値以下の場合は、新しいピクセルを受け入れる。
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//----------------------------------------
//  タイムの情報
//----------------------------------------
int * GetTime(void)
{
	return &g_nTime;
}

//----------------------------------------
//  タイムの加算
//----------------------------------------
void AddTime(int nTime)
{
	g_nTime += nTime;
}