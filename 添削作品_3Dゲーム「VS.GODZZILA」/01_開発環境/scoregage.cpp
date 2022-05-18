//----------------------------------------
//�@���C�t�Q�[�W����
//�@Author�F���슲��
//----------------------------------------
#include "scoregage.h"
#include "shadow.h"
#include "input.h"

//�}�N����`
#define SGAGE_X		(600.0f)	// x�����ւ̒l	����
#define SGAGE_Y		(100.0f)	// y�����ւ̒l	����
#define SGAGE_Z		(0.0f)	// z�����ւ̒l	�c��

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreGage[2] = {};		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureScoreGage[2] = {};			//�e�N�X�`��
ScoreGage g_aScoreGage[MAX_SCOREGAGE];

//----------------------------------------
//  �^�C�g���̏������ݒ菈��
//----------------------------------------
void InitScoreGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\gage.png",
		&g_pTextureScoreGage[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\gage_waku.png",
		&g_pTextureScoreGage[1]);

	//���_�o�b�t�@�̐���
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffScoreGage[nCnt],
			NULL);
	}

	for (int nCnt = 0; nCnt < MAX_SCOREGAGE; nCnt++)
	{
		g_aScoreGage[nCnt].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		g_aScoreGage[nCnt].bUse = false;
		g_aScoreGage[nCnt].nLife = 0;
		g_aScoreGage[nCnt].nMaxLife = 0;
		g_aScoreGage[nCnt].rot = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
	}

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_SCOREGAGE; nCnt++)
	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffScoreGage[0]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y - (SGAGE_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y - (SGAGE_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y + (SGAGE_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y + (SGAGE_Y / 2), 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffScoreGage[0]->Unlock();
	}

	for (int nCnt = 0; nCnt < MAX_SCOREGAGE; nCnt++)
	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffScoreGage[1]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y - (SGAGE_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y - (SGAGE_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y + (SGAGE_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aScoreGage[nCnt].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCnt].pos.y + (SGAGE_Y / 2), 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffScoreGage[1]->Unlock();
	}
}

//----------------------------------------
//  �^�C�g���̏I������
//----------------------------------------
void UninitScoreGage(void)
{
	int nCnt;

	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureScoreGage[nCnt] != NULL)
		{
			g_pTextureScoreGage[nCnt]->Release();
			g_pTextureScoreGage[nCnt] = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_pTextureScoreGage[nCnt] != NULL)
		{
			g_pTextureScoreGage[nCnt]->Release();
			g_pTextureScoreGage[nCnt] = NULL;
		}
	}
}

//----------------------------------------
//  �^�C�g���̍X�V�ݒ菈��
//----------------------------------------
void UpdateScoreGage(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffScoreGage[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGage = 0; nCntGage < MAX_SCOREGAGE; nCntGage++)
	{
		if (g_aScoreGage[nCntGage].bUse == true)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + ((0.5f / g_aScoreGage[nCntGage].nMaxLife) * (g_aScoreGage[nCntGage].nMaxLife - g_aScoreGage[nCntGage].nLife)), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + ((0.5f / g_aScoreGage[nCntGage].nMaxLife) * (g_aScoreGage[nCntGage].nMaxLife - g_aScoreGage[nCntGage].nLife)), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + ((0.5f / g_aScoreGage[nCntGage].nMaxLife) * (g_aScoreGage[nCntGage].nMaxLife - g_aScoreGage[nCntGage].nLife)), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + ((0.5f / g_aScoreGage[nCntGage].nMaxLife) * (g_aScoreGage[nCntGage].nMaxLife - g_aScoreGage[nCntGage].nLife)), 1.0f);

			if (g_aScoreGage[nCntGage].nLife <= 0)
			{//�̗͂��O�ȉ��ɂȂ�����
				g_aScoreGage[nCntGage].bUse = false;	//����
			}

			//�m�F�p
			if (GetKeyboardTrigger(DIK_O) == true)
			{
				g_aScoreGage[nCntGage].nLife--;
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffScoreGage[0]->Unlock();
}

//----------------------------------------
//  �^�C�g���̕`�揈��
//----------------------------------------
void DrawScoreGage(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffScoreGage[nCnt], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScoreGage[nCnt]);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//---------------------------------------------------
//	���C�t�Q�[�W�ݒ�
//---------------------------------------------------
void SetScoreGage(D3DXVECTOR3 pos, int nLife)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	for (int nCntScoreGage = 0; nCntScoreGage < MAX_SCOREGAGE; nCntScoreGage++)
	{
		if (g_aScoreGage[nCntScoreGage].bUse == false)
		{
			g_aScoreGage[nCntScoreGage].pos = pos;
			g_aScoreGage[nCntScoreGage].bUse = true;
			g_aScoreGage[nCntScoreGage].nLife = nLife;
			g_aScoreGage[nCntScoreGage].nMaxLife = nLife;

			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				//���_�o�b�t�@�����b�N
				g_pVtxBuffScoreGage[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

				//���_���W�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aScoreGage[nCntScoreGage].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCntScoreGage].pos.y - (SGAGE_Y / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aScoreGage[nCntScoreGage].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCntScoreGage].pos.y - (SGAGE_Y / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aScoreGage[nCntScoreGage].pos.x - (SGAGE_X / 2.0f), g_aScoreGage[nCntScoreGage].pos.y + (SGAGE_Y / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aScoreGage[nCntScoreGage].pos.x + (SGAGE_X / 2.0f), g_aScoreGage[nCntScoreGage].pos.y + (SGAGE_Y / 2), 0.0f);

				//���_�o�b�t�@�̃A�����b�N
				g_pVtxBuffScoreGage[nCnt]->Unlock();
			}

			break;
		}
	}
}

//---------------------------------------------------
//	���C�t�Q�[�W�̃_���[�W����
//---------------------------------------------------
void HitScoreGage(int nCntScoreGage, int nDamage)
{
	//�̗͂����炷
	g_aScoreGage[nCntScoreGage].nLife -= nDamage;

	if (g_aScoreGage[nCntScoreGage].nLife <= 0)
	{//�̗͂��O�ȉ��ɂȂ�����
		g_aScoreGage[nCntScoreGage].bUse = false;	//����
	}
}