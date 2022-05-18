//----------------------------------------
//�@�}�b�v�̏���
//�@Author�F���슲��
//----------------------------------------
#include "map.h"
#include <stdio.h>
#include <string.h>
#include "bill.h"
#include "meshfield.h"

//�}�N����`
#define MAX_X		(10)	// x���ɒu����u���b�N�̍ő吔
#define MAX_Y		(10)	// y���ɒu����u���b�N�̍ő吔
#define FILE_PAS	("data\\map2.txt")	//�}�b�v�̏�񂪓����Ă���f�[�^
FILE * pFile;
int nData[MAX_Y][MAX_X];
SetPos g_SetEnemyPos;

//----------------------------------------
//�@�}�b�v�̐ݒ�
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
			case 0:	//�G�A
				break;

			case 1:	//�r��
				SetModel(D3DXVECTOR3(-(FIELD_SIZE / 2) + (BlockX * nCntX + (BlockX / 2)), 0.0f, -(FIELD_SIZE / 2) + (BlockY * nCntY + (BlockY / 2))),	//�ʒu
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),	//�p�x
					TYPE_BILL_01,	//���
					4);			//�̗�

				break;

			case 2:	//�G�o���|�C���g
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