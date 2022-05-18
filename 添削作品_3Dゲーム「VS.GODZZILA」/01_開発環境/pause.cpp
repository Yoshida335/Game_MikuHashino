//----------------------------------------
//　ポーズ処理
//　Author：橋野幹生
//----------------------------------------
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause[3] = {};	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePause[3] = {};			//テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBG = NULL;	//頂点バッファへのポインタ
PAUSE g_Pause[3];
int g_nSelectPause;

//----------------------------------------
// ポーズの初期化設定処理
//----------------------------------------
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\pause001.png",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\pause002.png",
		&g_pTexturePause[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\pause003.png",
		&g_pTexturePause[2]);

	//頂点バッファの生成
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffPause[nCnt],
			NULL);
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		g_Pause[nCnt].pos = D3DXVECTOR3(((float)SCREEN_WIDTH / 2.0f), 200 + (150.0f * nCnt), 0.0f);
		g_Pause[nCnt].state = SELECT_OFF;
	}
	g_Pause[1].state = SELECT_ON;
	g_nSelectPause = 0;

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffPause[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_Pause[nCnt].pos.x - (400.0f / 2.0f), g_Pause[nCnt].pos.y - (120.0f / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Pause[nCnt].pos.x + (400.0f / 2.0f), g_Pause[nCnt].pos.y - (120.0f / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Pause[nCnt].pos.x - (400.0f / 2.0f), g_Pause[nCnt].pos.y + (120.0f / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Pause[nCnt].pos.x + (400.0f / 2.0f), g_Pause[nCnt].pos.y + (120.0f / 2), 0.0f);

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
		g_pVtxBuffPause[nCnt]->Unlock();
	}

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseBG->Unlock();
}

//----------------------------------------
// ポーズの終了処理
//----------------------------------------
void UninitPause(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}

		//頂点バッファの破棄
		if (g_pVtxBuffPause[nCnt] != NULL)
		{
			g_pVtxBuffPause[nCnt]->Release();
			g_pVtxBuffPause[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}
}

//----------------------------------------
// ポーズの更新設定処理
//----------------------------------------
void UpdatePause(void)
{
	bool * pPause = GetPause();

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffPause[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		switch (g_Pause[nCnt].state)
		{
		case SELECT_OFF:
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case SELECT_ON:
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//頂点バッファをアンロックする
		g_pVtxBuffPause[nCnt]->Unlock();
	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{//Wキーが押された
		g_nSelectPause--;

		if (g_nSelectPause < 0)
		{
			g_nSelectPause = 2;
		}
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{//Sキーが押された
		g_nSelectPause++;

		if (g_nSelectPause > 2)
		{
			g_nSelectPause = 0;
		}
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (g_nSelectPause == nCnt)
		{
			g_Pause[nCnt].state = SELECT_ON;
		}
		else if (g_nSelectPause != nCnt)
		{
			g_Pause[nCnt].state = SELECT_OFF;
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		switch (g_nSelectPause)
		{
		case 0:
			*pPause = false;
			break;

		case 1:
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_GAME);
			break;

		case 2:
			//モード設定(ランキング画面に移行)
			SetFade(MODE_RANKING);
			break;
		}
	}
}

//----------------------------------------
// ポーズの描画処理
//----------------------------------------
void DrawPause(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPause[nCnt], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCnt]);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
