//----------------------------------------
//�@���U���g�Ɏg���X�R�A�̏���
//�@Author�F���슲��
//----------------------------------------
#include "resultscore.h"
#include "main.h"
#include "bill.h"

#define MAX_BOX	(3)

typedef struct
{
	D3DXVECTOR3 pos[MAX_BOX];
	D3DXVECTOR3 size[MAX_BOX];
	bool bUse;
}ResultScore;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResultScore2 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultScore2 = NULL;

ResultScore g_ResultScore[MAX_RESULTSCORE];
int aResultPosTexU[MAX_RESULTSCORE][MAX_BOX];	//�e���̐������i�[

//----------------------------------------
//  �X�R�A�̏������ݒ菈��
//----------------------------------------
void InitResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureResultScore2);

	for (int i = 0; i < MAX_RESULTSCORE; i++)
	{
		for (int nCntResultScore = 0; nCntResultScore < MAX_BOX; nCntResultScore++)
		{
			g_ResultScore[i].pos[nCntResultScore] = D3DXVECTOR3(0.0f + (30.0f * nCntResultScore), 0.0f + (50.0f * i), 0.0f);		//�ʒu�̏���
		}
		g_ResultScore[i].bUse = false;
	}

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BOX * MAX_RESULTSCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultScore2,
		NULL);

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

						//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultScore2->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_RESULTSCORE; i++)
	{
		for (int nCntResultScore = 0; nCntResultScore < MAX_BOX; nCntResultScore++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_ResultScore[i].pos[nCntResultScore].x - 20.0f, g_ResultScore[i].pos[nCntResultScore].y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ResultScore[i].pos[nCntResultScore].x + 20.0f, g_ResultScore[i].pos[nCntResultScore].y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ResultScore[i].pos[nCntResultScore].x - 20.0f, g_ResultScore[i].pos[nCntResultScore].y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ResultScore[i].pos[nCntResultScore].x + 20.0f, g_ResultScore[i].pos[nCntResultScore].y + 25.0f, 0.0f);

			//rhw�̐ݒ�
			pVtx[0].rhm = 1.0f;
			pVtx[1].rhm = 1.0f;
			pVtx[2].rhm = 1.0f;
			pVtx[3].rhm = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultScore2->Unlock();
}

//----------------------------------------
//�@�X�R�A�̏I������
//----------------------------------------
void UninitResultScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureResultScore2 != NULL)
	{
		g_pTextureResultScore2->Release();
		g_pTextureResultScore2 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResultScore2 != NULL)
	{
		g_pVtxBuffResultScore2->Release();
		g_pVtxBuffResultScore2 = NULL;
	}
}

//----------------------------------------
//  �v���C���[�̍X�V����
//----------------------------------------
void UpdateResultScore(void)
{
	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultScore2->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_RESULTSCORE; i++)
	{
		for (int nCntResultScore = 0; nCntResultScore < MAX_BOX; nCntResultScore++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_ResultScore[i].pos[nCntResultScore].x - (g_ResultScore[i].size[nCntResultScore].x / 2.0f), g_ResultScore[i].pos[nCntResultScore].y - (g_ResultScore[i].size[nCntResultScore].y / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ResultScore[i].pos[nCntResultScore].x + (g_ResultScore[i].size[nCntResultScore].x / 2.0f), g_ResultScore[i].pos[nCntResultScore].y - (g_ResultScore[i].size[nCntResultScore].y / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ResultScore[i].pos[nCntResultScore].x - (g_ResultScore[i].size[nCntResultScore].x / 2.0f), g_ResultScore[i].pos[nCntResultScore].y + (g_ResultScore[i].size[nCntResultScore].y / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ResultScore[i].pos[nCntResultScore].x + (g_ResultScore[i].size[nCntResultScore].x / 2.0f), g_ResultScore[i].pos[nCntResultScore].y + (g_ResultScore[i].size[nCntResultScore].y / 2.0f), 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f * aResultPosTexU[i][nCntResultScore], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * aResultPosTexU[i][nCntResultScore] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aResultPosTexU[i][nCntResultScore], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * aResultPosTexU[i][nCntResultScore] + 0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultScore2->Unlock();
}

//----------------------------------------
//  �X�R�A�̕`�揈��
//----------------------------------------
void DrawResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCnt = 0;

	for (int i = 0; i < MAX_RESULTSCORE; i++)
	{
		if (g_ResultScore[i].bUse == true)
		{
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffResultScore2, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			for (int nCntResultScore = 0; nCntResultScore < MAX_BOX; nCntResultScore++, nCnt++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureResultScore2);

				//�|���S���̐ݒ�
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
			}
		}
	}
}

//----------------------------------------
//  �X�R�A�̐ݒ菈��
//----------------------------------------
void SetResultScore(int nResultScore, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int i = 0; i < MAX_RESULTSCORE; i++)
	{
		if (g_ResultScore[i].bUse == false)
		{
			aResultPosTexU[i][0] = nResultScore % 1000 / 100;
			aResultPosTexU[i][1] = nResultScore % 100 / 10;
			aResultPosTexU[i][2] = nResultScore % 10;

			for (int nCntResultScore = 0; nCntResultScore < MAX_BOX; nCntResultScore++)
			{
				g_ResultScore[i].pos[nCntResultScore] = D3DXVECTOR3((((size.x / 4) * 3) * nCntResultScore) + pos.x, pos.y, pos.z);
				g_ResultScore[i].size[nCntResultScore] = size;
			}
			g_ResultScore[i].bUse = true;

			break;
		}
	}
}
