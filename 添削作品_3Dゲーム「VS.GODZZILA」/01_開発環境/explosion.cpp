//----------------------------------------
//　爆発の処理
//　Author：橋野幹生
//----------------------------------------
#include "explosion.h"
#include "shadow.h"
#include "input.h"
#include "sound.h"

//マクロ定義
#define EXPLOSION_X		(20.0f)	// x方向への値	横幅
#define EXPLOSION_Y		(20.0f)	// y方向への値	高さ
#define EXPLOSION_Z		(0.0f)	// z方向への値	縦幅

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
Explosion g_aExplosion[MAX_EXPLOSION];

//---------------------------------------------------
//	爆発の初期化
//---------------------------------------------------
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\explosion.png",
		&g_pTextureExplosion);

	//爆発の各値初期化
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].nCntAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_X,  EXPLOSION_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( EXPLOSION_X,  EXPLOSION_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_X, -EXPLOSION_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( EXPLOSION_X, -EXPLOSION_Y, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();

}

//---------------------------------------------------
//	爆発の終了処理
//---------------------------------------------------
void UninitExplosion(void)
{

	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//---------------------------------------------------
//	爆発の更新処理
//---------------------------------------------------
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_3D * pVtx;

	//頂点情報をロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている
			g_aExplosion[nCntExplosion].nCntAnim++;

			if ((g_aExplosion[nCntExplosion].nCntAnim % 6) == 0)
			{
				//パターンNo.を更新する
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;

				if (g_aExplosion[nCntExplosion].nPatternAnim == 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 1.0f);

			}
		}

		pVtx += 4;			//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//---------------------------------------------------
//	爆発の描画処理
//---------------------------------------------------
void DrawExplosion(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	// Zバッファに関して
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (int i = 0; i < 2; i++)
	{
		for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

				D3DXMATRIX mtxView;
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);	//ビューマトリックス取得

																//カメラの逆行性を設定
				g_aExplosion[nCntExplosion].mtxWorld._11 = mtxView._11;
				g_aExplosion[nCntExplosion].mtxWorld._12 = mtxView._21;
				g_aExplosion[nCntExplosion].mtxWorld._13 = mtxView._31;
				g_aExplosion[nCntExplosion].mtxWorld._21 = mtxView._12;
				g_aExplosion[nCntExplosion].mtxWorld._22 = mtxView._22;
				g_aExplosion[nCntExplosion].mtxWorld._23 = mtxView._32;
				g_aExplosion[nCntExplosion].mtxWorld._31 = mtxView._13;
				g_aExplosion[nCntExplosion].mtxWorld._32 = mtxView._23;
				g_aExplosion[nCntExplosion].mtxWorld._33 = mtxView._33;

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
				D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);

				//ライトを無効にする
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

				//頂点バッファをデバイスのデータストリームに設定
				pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureExplosion);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntExplosion * 4,
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
//	爆発の設定
//---------------------------------------------------
void SetExplosion(D3DXVECTOR3 pos)
{
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].bUse = true;
			g_aExplosion[nCntExplosion].nCntAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_EXPLOSION);

			break;
		}
	}
}