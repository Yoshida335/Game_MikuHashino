//----------------------------------------
//　当たり判定の処理
//　Author：橋野幹生
//----------------------------------------
#include "collision.h"
#include "bill.h"
#include "enemy.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCollision = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCollision = NULL;			//メッシュフィールドのテクスチャ
COLLISION g_Collision[MAX_COLLISION];

//---------------------------------------------------
//	初期化
//---------------------------------------------------
void InitCollision(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Shock_wave_ring001.png",
		&g_pTextureCollision);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_COLLISION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCollision,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffCollision->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
	{
		//位置設定
		g_Collision[nCntCollision].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Collision[nCntCollision].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Collision[nCntCollision].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Collision[nCntCollision].bUse = false;
		g_Collision[nCntCollision].nLife = 0;
		g_Collision[nCntCollision].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//頂点バッファのアンロック
	g_pVtxBuffCollision->Unlock();
}

//---------------------------------------------------
//	当たり判定の終了処理
//---------------------------------------------------
void UninitCollision(void)
{
	//頂点バッファ破棄
	if (g_pVtxBuffCollision != NULL)
	{
		g_pVtxBuffCollision->Release();
		g_pVtxBuffCollision = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureCollision != NULL)
	{
		g_pTextureCollision->Release();
		g_pTextureCollision = NULL;
	}
}
//---------------------------------------------------
//	当たり判定の更新処理
//---------------------------------------------------
void UpdateCollision(void)
{
	for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
	{
		if (g_Collision[nCntCollision].bUse == true)
		{
			CollisionAttack(&g_Collision[nCntCollision].pos, &g_Collision[nCntCollision].posOld, D3DXVECTOR3(10.0f, 30.0f, 10.0f));
			CollisionEnemy(&g_Collision[nCntCollision].pos, &g_Collision[nCntCollision].posOld, D3DXVECTOR3(30.0f, 40.0f, 30.0f));

			g_Collision[nCntCollision].nLife--;

			if (g_Collision[nCntCollision].nLife <= 0)
			{
				g_Collision[nCntCollision].bUse = false;
			}
		}
	}
}

//---------------------------------------------------
//	当たり判定の描画処理
//---------------------------------------------------
void DrawCollision(void)
{

}

//---------------------------------------------------
//	当たり判定の設定
//---------------------------------------------------
void SetCollision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 rot)
{
	for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
	{
		if (g_Collision[nCntCollision].bUse == false)
		{
			g_Collision[nCntCollision].pos = pos;
			g_Collision[nCntCollision].posOld = posOld;
			g_Collision[nCntCollision].rot = rot;
			g_Collision[nCntCollision].bUse = true;
			g_Collision[nCntCollision].nLife = 60;

			break;
		}
	}
}