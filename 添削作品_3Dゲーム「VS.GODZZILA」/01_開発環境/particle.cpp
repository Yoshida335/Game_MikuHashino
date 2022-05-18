//----------------------------------------
//　パーティクルの処理
//　Author：橋野幹生
//----------------------------------------
#include "particle.h"
#include "effect.h"
#include "input.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;		//頂点バッファへのポインタ
Particle g_aParticle[MAX_PARTICLE];

//---------------------------------------------------
//	パーティクルの初期化処理
//---------------------------------------------------
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス取得

	//エフェクトの各値初期化
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].bUse = false;
		g_aParticle[nCntParticle].nLife = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffParticle->Unlock();
}

//---------------------------------------------------
//	パーティクルの終了処理
//---------------------------------------------------
void UninitParticle(void)
{
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//---------------------------------------------------
//	パーティクルの更新処理
//---------------------------------------------------
void UpdateParticle(void)
{
	//角度をランダムで設定
	float fpRot = (float)(rand() % (314 - 0 + 1)) - 157 / 100.0f + 10.0f;
	//位置をランダムで設定
	//float fpPos = (float)((rand() % (100 - 0 + 1)) - 50) + 10.0f;

	//パーティクルを設定
	//SetParticle(D3DXVECTOR3(0.0f, 20.0f, -80.0f), D3DXVECTOR3(fpRot, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f), 20, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	//SetParticle(D3DXVECTOR3(0.0f, 20.0f, -80.0f), D3DXVECTOR3(fpRot, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 10, D3DXVECTOR3(1.0f, 1.0f, 0.0f));

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{// 使用されている場合
			//エフェクトを設定
			SetEffect(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].rot, g_aParticle[nCntParticle].col, g_aParticle[nCntParticle].nLife, g_aParticle[nCntParticle].size);

			//移動量を設定(向いている方向へ)
			g_aParticle[nCntParticle].move.x = sinf(g_aParticle[nCntParticle].rot.x);
			g_aParticle[nCntParticle].move.z = cosf(g_aParticle[nCntParticle].rot.z);

			//重力
			g_aParticle[nCntParticle].move.y -= 0.1f;

			//移動量加算
			g_aParticle[nCntParticle].pos.x += g_aParticle[nCntParticle].move.x;
			g_aParticle[nCntParticle].pos.y += g_aParticle[nCntParticle].move.y;
			g_aParticle[nCntParticle].pos.z += g_aParticle[nCntParticle].move.z;

			//ライフを減らしていく
			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife < 0)
			{// パーティクルのライフが0になったら、falseにする
				g_aParticle[nCntParticle].bUse = false;
				g_aParticle[nCntParticle].move.y = 0.0f;
			}
		}
	}
}

//---------------------------------------------------
//	パーティクルの描画処理
//---------------------------------------------------
void DrawParticle(void)
{

}

//---------------------------------------------------
//	パーティクルの設定
//---------------------------------------------------
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].rot = rot;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].size = size;
			g_aParticle[nCntParticle].bUse = true;

			break;
		}
	}
}

