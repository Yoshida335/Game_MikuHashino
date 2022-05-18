//----------------------------------------
//　敵の処理
//　Author：橋野幹生
//----------------------------------------
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "player.h"
#include "explosion.h"
#include "bullet.h"
#include <math.h>
#include <time.h>

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;	//テクスチャへのポインタ
LPD3DXMESH g_pMeshEnemy[TYPE_ENEMY_MAX] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatEnemy[TYPE_ENEMY_MAX] = {};//マテリアル情報へのポインタ
DWORD g_nNumMatEnemy = 0;					//マテリアル情報の数
Enemy g_aEnemy[MAX_ENEMY];

//---------------------------------------------------
//	敵の初期化処理
//---------------------------------------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各値の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//現在の位置
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
		g_aEnemy[nCntEnemy].diff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//差分計算用
		g_aEnemy[nCntEnemy].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の角度
		g_aEnemy[nCntEnemy].bUse = false;								//使ってるかどうか
		g_aEnemy[nCntEnemy].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//頂点の最小値取得用
		g_aEnemy[nCntEnemy].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//頂点の最大値取得用
		g_aEnemy[nCntEnemy].nType = TYPE_ENEMY_01;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].posdis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].bAttack = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\uroko_red.jpg",
		&g_pTextureEnemy);

	//Ⅹファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\airplane000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[0],
		NULL,
		&g_nNumMatEnemy,
		&g_pMeshEnemy[0]);

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

	for (int i = 0; i < TYPE_ENEMY_MAX; i++)
	{
		//頂点数の取得
		nNumVtx = g_pMeshEnemy[i]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshEnemy[i]->GetFVF());

		//頂点バッファのロック
		g_pMeshEnemy[i]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				// 最小値を求める
				if (vtx.x < g_aEnemy[nCntEnemy].vtxMin.x)
				{// 比較した値が入ってる当たりよりも小さかったら、置き換え
					g_aEnemy[nCntEnemy].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_aEnemy[nCntEnemy].vtxMin.y)
				{// 比較した値が入ってる当たりよりも小さかったら、置き換え
					g_aEnemy[nCntEnemy].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_aEnemy[nCntEnemy].vtxMin.z)
				{// 比較した値が入ってる当たりよりも小さかったら、置き換え
					g_aEnemy[nCntEnemy].vtxMin.z = vtx.z;
				}

				// 最大値を求める
				if (vtx.x > g_aEnemy[nCntEnemy].vtxMax.x)
				{// 比較した値が入ってる当たりよりも大きかったら、置き換え
					g_aEnemy[nCntEnemy].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_aEnemy[nCntEnemy].vtxMax.y)
				{// 比較した値が入ってる当たりよりも大きかったら、置き換え
					g_aEnemy[nCntEnemy].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_aEnemy[nCntEnemy].vtxMax.z)
				{// 比較した値が入ってる当たりよりも大きかったら、置き換え
					g_aEnemy[nCntEnemy].vtxMax.z = vtx.z;
				}

				//サイズを計算
				g_aEnemy[nCntEnemy].size.x = g_aEnemy[nCntEnemy].vtxMax.x - g_aEnemy[nCntEnemy].vtxMin.x;
				g_aEnemy[nCntEnemy].size.y = g_aEnemy[nCntEnemy].vtxMax.y - g_aEnemy[nCntEnemy].vtxMin.y;
				g_aEnemy[nCntEnemy].size.z = g_aEnemy[nCntEnemy].vtxMax.z - g_aEnemy[nCntEnemy].vtxMin.z;
			}

			//頂点フォーマットのポインタ分進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファをアンロック
		g_pMeshEnemy[i]->UnlockVertexBuffer();
	}

	//SetEnemy(D3DXVECTOR3(0.0f, 110.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), TYPE_ENEMY_01, 1);


}

//---------------------------------------------------
//	敵の終了処理
//---------------------------------------------------
void UninitEnemy(void)
{
	for (int i = 0; i < TYPE_ENEMY_MAX; i++)
	{
		//メッシュ破棄
		if (g_pMeshEnemy[i] != NULL)
		{
			g_pMeshEnemy[i]->Release();
			g_pMeshEnemy[i] = NULL;
		}

		//マテリアル破棄
		if (g_pBuffMatEnemy[i] != NULL)
		{
			g_pBuffMatEnemy[i]->Release();
			g_pBuffMatEnemy[i] = NULL;
		}
	}

	//テクスチャ破棄
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}
}
int g_nCntBullet = 0;
float Angle;

float fRotMove, fRotDest, fRotDiff;
int nLand;
//---------------------------------------------------
//	敵の更新処理
//---------------------------------------------------
void UpdateEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

			if (g_aEnemy[nCntEnemy].nLife <= 0)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}

			//プレイヤーの情報
			Player * pPlayer = GetPlayer();

			//プレイヤーとの差を求める
			g_aEnemy[nCntEnemy].posdis.x = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
			g_aEnemy[nCntEnemy].posdis.z = pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z;
			
			float fLength = D3DXVec3Length(&g_aEnemy[nCntEnemy].posdis);
			
			//正規化する
			D3DXVec3Normalize(&g_aEnemy[nCntEnemy].posdis, &g_aEnemy[nCntEnemy].posdis);
			
			if (fLength < 500.0f)
			{//100離れたら来ないよ。
				g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].posdis * 1.0f;
			}

			if (g_aEnemy[nCntEnemy].bAttack == false)
			{
				g_nCntBullet++;

				if ((g_nCntBullet % 500) == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].rot);
				}
			}

			//プレイヤーの方向に向かせる
			g_aEnemy[nCntEnemy].rot.y = atan2f(-pPlayer->pos.x + g_aEnemy[nCntEnemy].pos.x, -pPlayer->pos.z + g_aEnemy[nCntEnemy].pos.z);

			//差分の正規化
			if (g_aEnemy[nCntEnemy].rotDest.y - g_aEnemy[nCntEnemy].rot.y > D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rotDest.y -= D3DX_PI * 2.0f;
			}
			else if (g_aEnemy[nCntEnemy].rotDest.y - g_aEnemy[nCntEnemy].rot.y < -D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rotDest.y += D3DX_PI * 2.0f;
			}

			//敵の移動慣性
			g_aEnemy[nCntEnemy].rot.y += (g_aEnemy[nCntEnemy].rotDest.y - g_aEnemy[nCntEnemy].rot.y) * 0.05f;

			//角度の正規化
			if (g_aEnemy[nCntEnemy].rot.y < -D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rot.y += D3DX_PI * 2.0f;
			}
			else if (g_aEnemy[nCntEnemy].rot.y > D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rot.y -= D3DX_PI * 2.0f;
			}

			//プレイヤーとの当たり判定
			CollisionPlayer(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, D3DXVECTOR3(g_aEnemy[nCntEnemy].size.x + 10.0f, g_aEnemy[nCntEnemy].size.y, g_aEnemy[nCntEnemy].size.z + 10.0f));
		}
	}

}

//---------------------------------------------------
//	敵の描画処理
//---------------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL * pMat;			//マテリアルデータへのポインタ

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld,
				&g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//現在のマテリアル保持
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[g_aEnemy[nCntEnemy].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//敵パーツの描画
				g_pMeshEnemy[g_aEnemy[nCntEnemy].nType]->DrawSubset(nCntMat);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);
			}

			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------
//	敵の設定
//---------------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int life)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{// bUseがfalseだったら、
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].rot = rot;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nType = type;
			g_aEnemy[nCntEnemy].nLife = life;

			break;
		}
	}
}

//---------------------------------------------------
//	敵の当たり判定
//---------------------------------------------------
void CollisionEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
{
	for (int nCntModel = 0; nCntModel < MAX_ENEMY; nCntModel++)
	{//最大モデル数分確認
		if (g_aEnemy[nCntModel].bUse == true)
		{// bUseがtrueだったら（モデルが使用されている状態の時
			{// bHitがfalseだったら（攻撃が当たっていない、クールタイム中の時
				if (pos->y < g_aEnemy[nCntModel].pos.y + g_aEnemy[nCntModel].vtxMax.y &&
					pos->y + (size.y) > g_aEnemy[nCntModel].pos.y + g_aEnemy[nCntModel].vtxMin.y)
				{
					if (pos->z - (size.z / 2) < g_aEnemy[nCntModel].pos.z + g_aEnemy[nCntModel].vtxMax.z &&
						pos->z + (size.z / 2) > g_aEnemy[nCntModel].pos.z + g_aEnemy[nCntModel].vtxMin.z)
					{// *posのz座標がモデルに重なっている時
						if (pos->x - (size.x / 2) <= g_aEnemy[nCntModel].pos.x + g_aEnemy[nCntModel].vtxMax.x &&
							pos->x + (size.x / 2) >= g_aEnemy[nCntModel].pos.x + g_aEnemy[nCntModel].vtxMin.x)
						{//左側からモデルにめり込んだ時
						 //*pos.xにモデルのpos.x(左側)を設定
							HitEnemyl(nCntModel, 1);
						}
					}
					else if (pos->x - (size.x / 2) < g_aEnemy[nCntModel].pos.x + g_aEnemy[nCntModel].vtxMax.x &&
						pos->x + (size.x / 2) > g_aEnemy[nCntModel].pos.x + g_aEnemy[nCntModel].vtxMin.x)
					{// *posのx座標がモデルに重なっている時
						if (pos->z - (size.z / 2) < g_aEnemy[nCntModel].pos.z + g_aEnemy[nCntModel].vtxMax.z &&
							pos->z + (size.z / 2) > g_aEnemy[nCntModel].pos.z + g_aEnemy[nCntModel].vtxMin.z)
						{//モデルの手前側からめり込んだ時
						 //*pos.zにモデルのpos.z(手前側)を設定
							HitEnemyl(nCntModel, 1);
						}
					}
				}
			}
		}
	}
}

//---------------------------------------------------
//	ヒット処理
//---------------------------------------------------
void HitEnemyl(int nCntModel, int nDamage)
{
	//体力を減らす
	g_aEnemy[nCntModel].nLife -= nDamage;

	if (g_aEnemy[nCntModel].nLife <= 0)
	{//体力が０以下になったら
		SetExplosion(g_aEnemy[nCntModel].pos);
		g_aEnemy[nCntModel].bUse = false;	//消す
	}
}
