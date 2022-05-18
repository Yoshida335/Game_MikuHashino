//----------------------------------------
//　マップの処理
//　Author：橋野幹生
//----------------------------------------
#include "map.h"
#include <stdio.h>
#include <string.h>
#include "bill.h"
#include "meshfield.h"

//マクロ定義
#define MAX_X		(10)	// x軸に置けるブロックの最大数
#define MAX_Y		(10)	// y軸に置けるブロックの最大数
#define FILE_PAS	("data\\map2.txt")	//マップの情報が入っているデータ
FILE * pFile;
int nData[MAX_Y][MAX_X];
SetPos g_SetEnemyPos;

//----------------------------------------
//　マップの設定
//----------------------------------------
void SetMap(void)
{
	float BlockX = FIELD_SIZE / MAX_X;
	float BlockY = FIELD_SIZE / MAX_Y;

	int nCntSetpos = 0;

	pFile = fopen(FILE_PAS, "r");

	if (pFile != NULL)
	{
		for (int nCntY = 0; nCntY < MAX_Y; nCntY++)
		{
			for (int nCntX = 0; nCntX < MAX_X; nCntX++)
			{
				fscanf(pFile, "%d", &nData[nCntY][nCntX]);
			}
		}
	}
	else
	{

	}

	for (int nCntY = 0; nCntY < MAX_Y; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_X; nCntX++)
		{
			switch (nData[nCntY][nCntX])
			{
			case 0:	//エア
				break;

			case 1:	//ビル
				SetModel(D3DXVECTOR3(-(FIELD_SIZE / 2) + (BlockX * nCntX + (BlockX / 2)), 0.0f, -(FIELD_SIZE / 2) + (BlockY * nCntY + (BlockY / 2))),	//位置
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),	//角度
					TYPE_BILL_01,	//種類
					4);			//体力

				break;

			case 2:	//敵出現ポイント
				g_SetEnemyPos.Setpos[nCntSetpos] = D3DXVECTOR3(-(FIELD_SIZE / 2) + (BlockX * nCntX + (BlockX / 2)), 110.0f, -(FIELD_SIZE / 2) + (BlockY * nCntY + (BlockY / 2)));
				nCntSetpos++;
				break;
			}
		}
	}

}

SetPos * GetSetPos(void)
{
	return &g_SetEnemyPos;
}