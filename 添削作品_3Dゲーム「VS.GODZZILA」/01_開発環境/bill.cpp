//----------------------------------------
//　ビルの処理
//　Author：橋野幹生
//----------------------------------------
#include "bill.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "fade.h"
#include "sound.h"
#include "gage.h"
#include "bill_delete.h"
#include "time.h"
#include "explosion.h"
#include <stdio.h>
#include <string.h>

//グローバル変数宣言
LPD3DXMESH g_pMeshModel[TYPE_MAX] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatModel[TYPE_MAX] = {};//マテリアル情報へのポインタ
DWORD g_nNumMatModel = 0;					//マテリアル情報の数
Model g_aModel[MAX_MODEL];
int g_nSetModel = 0;
int g_nMaxSetModel = 0;
Parcent g_Parcent;
D3DXMATERIAL * g_pMatModel;			//マテリアルデータへのポインタ
LPDIRECT3DTEXTURE9 g_pTexture[TYPE_MAX][10];	//テクスチャへのポインタ

//---------------------------------------------------
//	ビルのスコア情報
//---------------------------------------------------
void SaveParcent(void)
{
	FILE * pFile;

	//確認用
	//ファイルを開く
	pFile = fopen("data\\result.txt", "w");		//(テキスト名を指定, モードを指定)

	if (pFile != NULL)
	{//ファイルが開けた場合

		fprintf(pFile, "%.0f\n", g_Parcent.nModelP);
		fprintf(pFile, "%d\n", g_nSetModel);
		fprintf(pFile, "%d\n", g_nMaxSetModel);
		fprintf(pFile, "\n\n");	//改行

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("\n***　ファイルが開けませんでした　***\n");
	}
}

//---------------------------------------------------
//	ビルの初期化処理
//---------------------------------------------------
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各値の初期化
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
		g_aModel[nCntModel].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
		g_aModel[nCntModel].diff = 0.0f;								//差分計算用
		g_aModel[nCntModel].rotDestModel = 0.0f;						//目的の角度
		g_aModel[nCntModel].bUse = false;								//使ってるかどうか
		g_aModel[nCntModel].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//頂点の最小値取得用
		g_aModel[nCntModel].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);		//頂点の最大値取得用
		g_aModel[nCntModel].nType = TYPE_BILL_01;	//種類
		g_aModel[nCntModel].nLife = 0;				//寿命
		g_aModel[nCntModel].bHit = false;			//攻撃が当たったかどうか
		g_aModel[nCntModel].nCntTime = 0;			//クールタイムのカウント用
	}

	g_Parcent.nMax = 0.0f;
	g_Parcent.nMaxLife = 0.0f;
	g_Parcent.nModelP = 0.0f;

	g_nSetModel = 0;
	g_nMaxSetModel = 0;

	//Ⅹファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\bill_01.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[0],
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel[0]);

	//マテリアルデータへのポインタを取得
	g_pMatModel = (D3DXMATERIAL*)g_pBuffMatModel[0]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			g_pMatModel[nCntMat].pTextureFilename,
			&g_pTexture[0][nCntMat]);
	}

	D3DXLoadMeshFromX("data\\MODEL\\bill_02.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[1],
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel[1]);

	//マテリアルデータへのポインタを取得
	g_pMatModel = (D3DXMATERIAL*)g_pBuffMatModel[1]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			g_pMatModel[nCntMat].pTextureFilename,
			&g_pTexture[1][nCntMat]);
	}

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

	for (int i = 0; i < TYPE_MAX; i++)
	{
		//頂点数の取得
		nNumVtx = g_pMeshModel[i]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel[i]->GetFVF());

		//頂点バッファのロック
		g_pMeshModel[i]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				// 最小値を求める
				if (vtx.x < g_aModel[nCntModel].vtxMin.x)
				{// 比較した値が入ってる当たりよりも小さかったら、置き換え
					g_aModel[nCntModel].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_aModel[nCntModel].vtxMin.y)
				{// 比較した値が入ってる当たりよりも小さかったら、置き換え
					g_aModel[nCntModel].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_aModel[nCntModel].vtxMin.z)
				{// 比較した値が入ってる当たりよりも小さかったら、置き換え
					g_aModel[nCntModel].vtxMin.z = vtx.z;
				}

				// 最大値を求める
				if (vtx.x > g_aModel[nCntModel].vtxMax.x)
				{// 比較した値が入ってる当たりよりも大きかったら、置き換え
					g_aModel[nCntModel].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_aModel[nCntModel].vtxMax.y)
				{// 比較した値が入ってる当たりよりも大きかったら、置き換え
					g_aModel[nCntModel].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_aModel[nCntModel].vtxMax.z)
				{// 比較した値が入ってる当たりよりも大きかったら、置き換え
					g_aModel[nCntModel].vtxMax.z = vtx.z;
				}
			}

			//頂点フォーマットのポインタ分進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファをアンロック
		g_pMeshModel[i]->UnlockVertexBuffer();
	}
}

//---------------------------------------------------
//	ビルの終了処理
//---------------------------------------------------
void UninitModel(void)
{
	//ビルのスコア情報をセーブ
	SaveParcent();

	for (int i = 0; i < TYPE_MAX; i++)
	{
		//メッシュ破棄
		if (g_pMeshModel[i] != NULL)
		{
			g_pMeshModel[i]->Release();
			g_pMeshModel[i] = NULL;
		}

		//マテリアル破棄
		if (g_pBuffMatModel[i] != NULL)
		{
			g_pBuffMatModel[i]->Release();
			g_pBuffMatModel[i] = NULL;
		}

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
		{
			if (g_pTexture[i][nCntMat] != NULL)
			{//テクスチャ破棄
				g_pTexture[i][nCntMat]->Release();
				g_pTexture[i][nCntMat] = NULL;
			}
		}
	}
}

//---------------------------------------------------
//	ビルの更新処理
//---------------------------------------------------
void UpdateModel(void)
{
	g_Parcent.nModelP = (10000 - (g_Parcent.nMaxLife / g_Parcent.nMax) * 10000);

	//ビルが全部壊れたらクリア判定
	if (g_nSetModel >= g_nMaxSetModel)
	{
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_RESULT);
		g_nSetModel--;
	}

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse)
		{//ビルが使用されている時
			if (g_aModel[nCntModel].bHit)
			{
				g_aModel[nCntModel].nCntTime++;

				if (g_aModel[nCntModel].nCntTime >= 60)
				{
					g_aModel[nCntModel].bHit = false;
					g_aModel[nCntModel].nCntTime = 0;
				}
			}
		}
	}
}

//---------------------------------------------------
//	ビルの描画処理
//---------------------------------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld,
				&g_aModel[nCntModel].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);

			//現在のマテリアル保持
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			g_pMatModel = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&g_pMatModel[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture[g_aModel[nCntModel].nType][nCntMat]);

				//モデルパーツの描画
				g_pMeshModel[g_aModel[nCntModel].nType]->DrawSubset(nCntMat);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture[g_aModel[nCntModel].nType][nCntMat]);
			}

			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------
//	ビルの設定
//---------------------------------------------------
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE type, int life)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{// bUseがfalseだったら、
			g_aModel[nCntModel].pos = pos;		//位置
			g_aModel[nCntModel].rot = rot;		//角度
			g_aModel[nCntModel].bUse = true;	//使っているかどうか(使っている状態にする)
			g_aModel[nCntModel].nType = type;	//種類
			g_aModel[nCntModel].nLife = life;	//寿命
			//寿命を表示するゲージの設定
			SetGage(D3DXVECTOR3(g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y + 100.0f, g_aModel[nCntModel].pos.z),	//位置
				g_aModel[nCntModel].nLife);					//寿命

			g_Parcent.nMaxLife += g_aModel[nCntModel].nLife;	//全体の最大寿命の値を保存
			g_Parcent.nMax += g_aModel[nCntModel].nLife;		//全体の

			g_nMaxSetModel++;

			break;
		}
	}
}

//---------------------------------------------------
//	ビルの当たり判定処理
//---------------------------------------------------
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move)
{
	bool bIsLanding = false;		//着地しているかどうか

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{//最大ビル数分確認
		if (g_aModel[nCntModel].bUse)
		{// bUseがtrueだったら（ビルが使用されている状態の時

			/**/
			if (pos->x - (size.x/ 2) < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
				pos->x + (size.x/ 2) > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x &&
				pos->z - (size.z/ 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
				pos->z + (size.z/ 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
			{
				if (posOld->y + size.y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y &&
					pos->y + size.y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y)
				{//ビルの下からめり込んだ時の当たり判定
					pos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y - size.y;
					move->y = 0.0f;
				}
				if (posOld->y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y &&
					pos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y)
				{//ビルの上からめり込んだ時の当たり判定
					pos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y;
					move->y = 0.0f;
					bIsLanding = true;
				}
			}
			if (pos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y &&
				pos->y + (size.y) > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y)
			{
				if (pos->z - (size.z/ 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
					pos->z + (size.z/ 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
				{// *posのz座標がビルに重なっている時
					if (posOld->x + (size.x/ 2) <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x &&
						pos->x + (size.x/ 2) >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x)
					{//左側からビルにめり込んだ時
					 //*pos.xにビルのpos.x(左側)を設定
						pos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x - (size.x/ 2);
					}
					else if (posOld->x - (size.x/ 2) >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
						pos->x - (size.x/ 2) <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x)
					{//右側からビルにめり込んだ時
					 //*pos.xにビルのpos.x(右側)を設定
						pos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x + (size.x/ 2);
					}
				}
				if (pos->x - (size.x/ 2) < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
					pos->x + (size.x/ 2) > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x)
				{// *posのx座標がビルに重なっている時
					if (posOld->z - (size.z/ 2) <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z &&
						pos->z + (size.z/ 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
					{//ビルの手前側からめり込んだ時
					 //*pos.zにビルのpos.z(手前側)を設定
						pos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z - (size.z/ 2);
					}
					else if (posOld->z + (size.z/ 2) >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
						pos->z - (size.z/ 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z)
					{//ビルの奥側からめり込んだ時
					 //*pos.zにビルのpos.z(奥側)を設定
						pos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z + (size.z/ 2);
					}
				}
			}
		}
	}

	return bIsLanding;
}

//---------------------------------------------------
//	当たり判定処理
//---------------------------------------------------
void CollisionAttack(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{//最大ビル数分確認
		if (!g_aModel[nCntModel].bUse)
		{// bUseがtrueだったら、終わる
			continue;
		}
		if (g_aModel[nCntModel].bHit)
		{// bHitがtrueだったら、終わる
			continue;
		}
		if (pos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y &&
			pos->y + (size.y) > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y)
		{
			if (pos->z - (size.z / 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
				pos->z + (size.z / 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
			{// *posのz座標がビルに重なっている時
				if (pos->x - (size.x / 2) <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
					pos->x + (size.x / 2) >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x)
				{//左側からビルにめり込んだ時
				 //*pos.xにビルのpos.x(左側)を設定
					HitModel(nCntModel, 1);
				}
			}
			else if (pos->x - (size.x / 2) < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
				pos->x + (size.x / 2) > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x)
			{// *posのx座標がビルに重なっている時
				if (pos->z - (size.z / 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
					pos->z + (size.z / 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
				{//ビルの手前側からめり込んだ時
				 //*pos.zにビルのpos.z(手前側)を設定
					HitModel(nCntModel, 1);
				}
			}
		}
	}
}

//---------------------------------------------------
//	当たり判定処理
//---------------------------------------------------
void HitModel(int nCntModel, int nDamage)
{
	//体力を減らす
	g_aModel[nCntModel].nLife -= nDamage;
	g_aModel[nCntModel].bHit = true;

	HitGage(nCntModel, nDamage);

	g_Parcent.nMaxLife -= nDamage;

	//サウンドの再生
	PlaySound(SOUND_LABEL_SE_HIT);

	if (g_aModel[nCntModel].nLife <= 0)
	{//体力が０以下になったら
		SetExplosion(D3DXVECTOR3(g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y + 40.0f, g_aModel[nCntModel].pos.z));
		SetBillDelete(g_aModel[nCntModel].pos, g_aModel[nCntModel].rot);
		g_aModel[nCntModel].bUse = false;	//消す
 		g_nSetModel++;	//配置ビル数の数を減らす
		AddTime(5);		//時間を増やす
	}
}

//---------------------------------------------------
//	全体の内破壊されたビルのパーセント情報
//---------------------------------------------------
Parcent * GetModeParcent(void)
{
	return &g_Parcent;
}