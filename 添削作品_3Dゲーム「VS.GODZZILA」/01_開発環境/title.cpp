//----------------------------------------
//　タイトル画面の処理
//　Author：橋野幹生
//----------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 g_pTextureTitle[2] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle[2] = {};	//頂点バッファへのポインタ
D3DXVECTOR3 g_posText;

LPDIRECT3DTEXTURE9 g_pTextureK[2] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffK[2] = {};		//頂点バッファへのポインタ
D3DXVECTOR3 g_posK;

LPDIRECT3DTEXTURE9 g_pTextureLogo = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLogo = NULL;		//頂点バッファへのポインタ

bool g_bTitle;		//タイトル画面1回だけ起動用
float g_fCntColor = 0;
float g_fCntTitle = 0;

//----------------------------------------
//  タイトルの初期化設定処理
//----------------------------------------
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\PRESSENTER.png",
		&g_pTextureTitle[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title_white.png",
		&g_pTextureK[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title_k.png",
		&g_pTextureK[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\titile_logo.png",
		&g_pTextureLogo);

	//位置初期化(PRESS ENTER)
	g_posText = D3DXVECTOR3((SCREEN_WIDTH / 2) + 250.0f, 550.0f, 0.0f);
	g_posK = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 10.0f, 0.0f);
	g_bTitle = false;

	//頂点バッファの生成
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTitle[nCnt],
			NULL);
	}

	//頂点バッファの生成
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffK[nCnt],
			NULL);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLogo,
		NULL);

	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//背景の頂点
	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pVtxBuffTitle[0]->Unlock();
	}

	//テキストの頂点
	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_posText.x - 200.0f, g_posText.y - 70.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posText.x + 200.0f, g_posText.y - 70.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posText.x - 200.0f, g_posText.y + 70.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posText.x + 200.0f, g_posText.y + 70.0f, 0.0f);

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
		g_pVtxBuffTitle[1]->Unlock();
	}

	//怪獣
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffK[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_posK.x - (SCREEN_WIDTH / 2.0f), g_posK.y - (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posK.x + (SCREEN_WIDTH / 2.0f), g_posK.y - (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posK.x - (SCREEN_WIDTH / 2.0f), g_posK.y + (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posK.x + (SCREEN_WIDTH / 2.0f), g_posK.y + (SCREEN_HEIGHT / 2), 0.0f);

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
		g_pVtxBuffK[nCnt]->Unlock();
		}
	}

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffLogo->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffLogo->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//----------------------------------------
//  タイトルの終了処理
//----------------------------------------
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}

		//頂点バッファの破棄
		if (g_pVtxBuffTitle[nCnt] != NULL)
		{
			g_pVtxBuffTitle[nCnt]->Release();
			g_pVtxBuffTitle[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureK[nCnt] != NULL)
		{
			g_pTextureK[nCnt]->Release();
			g_pTextureK[nCnt] = NULL;
		}

		//頂点バッファの破棄
		if (g_pVtxBuffK[nCnt] != NULL)
		{
			g_pVtxBuffK[nCnt]->Release();
			g_pVtxBuffK[nCnt] = NULL;
		}
	}

	//テクスチャの破棄
	if (g_pTextureLogo != NULL)
	{
		g_pTextureLogo->Release();
		g_pTextureLogo = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLogo != NULL)
	{
		g_pVtxBuffLogo->Release();
		g_pVtxBuffLogo = NULL;
	}
}

//----------------------------------------
//  タイトルの更新設定処理
//----------------------------------------
void UpdateTitle(void)
{
	//テキストの頂点
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);

	g_fCntTitle += 0.0005f;	//徐々に値を変更

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f - g_fCntTitle, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f - g_fCntTitle, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f - g_fCntTitle, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f - g_fCntTitle, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle[0]->Unlock();

	g_fCntColor += 0.8f;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffK[1]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f + (sinf((D3DX_PI / 270.0f) * g_fCntColor) * 1.0f), 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f + (sinf((D3DX_PI / 270.0f) * g_fCntColor) * 1.0f), 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f + (sinf((D3DX_PI / 270.0f) * g_fCntColor) * 1.0f), 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f + (sinf((D3DX_PI / 270.0f) * g_fCntColor) * 1.0f), 0.0f, 0.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffK[1]->Unlock();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//頂点情報をロックし、頂点情報へのポインタを取得
		g_pVtxBuffK[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_posK.x - (SCREEN_WIDTH / 2.0f), g_posK.y - (SCREEN_HEIGHT / 2.0f) + (sinf((D3DX_PI / 100.0f) * g_fCntColor) * 10.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posK.x + (SCREEN_WIDTH / 2.0f), g_posK.y - (SCREEN_HEIGHT / 2.0f) + (sinf((D3DX_PI / 100.0f) * g_fCntColor) * 10.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posK.x - (SCREEN_WIDTH / 2.0f), g_posK.y + (SCREEN_HEIGHT / 2.0f) + (sinf((D3DX_PI / 100.0f) * g_fCntColor) * 10.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posK.x + (SCREEN_WIDTH / 2.0f), g_posK.y + (SCREEN_HEIGHT / 2.0f) + (sinf((D3DX_PI / 100.0f) * g_fCntColor) * 10.0f), 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffK[nCnt]->Unlock();
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && !g_bTitle)
	{
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_RULE);

		g_bTitle = true;
	}
}

//----------------------------------------
//  タイトルの描画処理
//----------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//背景
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[0], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[0]);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{//怪獣
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffK[nCnt], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureK[nCnt]);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//PRESSENTER
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[1], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[1]);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//タイトルロゴ
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffLogo, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureLogo);

		//ポリゴンの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}