//----------------------------------------
//�@���C�t�Q�[�W����
//�@Author�F���슲��
//----------------------------------------
#include "gage.h"
#include "shadow.h"
#include "input.h"

//�}�N����`
#define GAGE_X		(20.0f)	// x�����ւ̒l	����
#define GAGE_Y		(5.0f)	// y�����ւ̒l	����
#define GAGE_Z		(0.0f)	// z�����ւ̒l	�c��

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGage[2] = {};		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureGage[2] = {};			//�e�N�X�`��
Gage g_aGage[MAX_GAGE];

//---------------------------------------------------
//	���C�t�Q�[�W������
//---------------------------------------------------
void InitGage(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\gage.png",
		&g_pTextureGage[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\gage_waku.png",
		&g_pTextureGage[1]);

	//���C�t�Q�[�W�e�l������
	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		g_aGage[nCntGage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGage[nCntGage].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGage[nCntGage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGage[nCntGage].bUse = false;
		g_aGage[nCntGage].nLife = 0;
		g_aGage[nCntGage].nMaxLife = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_GAGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGage[0],
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_GAGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGage[1],
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffGage[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-GAGE_X, GAGE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(GAGE_X, GAGE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-GAGE_X, -GAGE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(GAGE_X, -GAGE_Y, 0.0f);

		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffGage[0]->Unlock();


	//���_�o�b�t�@�����b�N
	g_pVtxBuffGage[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-GAGE_X, GAGE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(GAGE_X, GAGE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-GAGE_X, -GAGE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(GAGE_X, -GAGE_Y, 0.0f);

		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffGage[1]->Unlock();
}

//---------------------------------------------------
//	���C�t�Q�[�W�I������
//---------------------------------------------------
void UninitGage(void)
{
	for (int i = 0; i < 2; i++)
	{
		if (g_pVtxBuffGage[i] != NULL)
		{
			g_pVtxBuffGage[i]->Release();
			g_pVtxBuffGage[i] = NULL;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (g_pTextureGage[i] != NULL)
		{
			g_pTextureGage[i]->Release();
			g_pTextureGage[i] = NULL;
		}
	}
}

//---------------------------------------------------
//	���C�t�Q�[�W�X�V����
//---------------------------------------------------
void UpdateGage(void)
{
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffGage[0]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		if (g_aGage[nCntGage].bUse)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + ((0.5f / g_aGage[nCntGage].nMaxLife) * (g_aGage[nCntGage].nMaxLife - g_aGage[nCntGage].nLife)), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + ((0.5f / g_aGage[nCntGage].nMaxLife) * (g_aGage[nCntGage].nMaxLife - g_aGage[nCntGage].nLife)), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + ((0.5f / g_aGage[nCntGage].nMaxLife) * (g_aGage[nCntGage].nMaxLife - g_aGage[nCntGage].nLife)), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + ((0.5f / g_aGage[nCntGage].nMaxLife) * (g_aGage[nCntGage].nMaxLife - g_aGage[nCntGage].nLife)), 1.0f);

			if (g_aGage[nCntGage].nLife <= 0)
			{//�̗͂��O�ȉ��ɂȂ�����
				g_aGage[nCntGage].bUse = false;	//����
			}

			//�m�F�p
			if (GetKeyboardTrigger(DIK_O))
			{
				g_aGage[nCntGage].nLife--;
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffGage[0]->Unlock();

}

//---------------------------------------------------
//	���C�t�Q�[�W�`�揈��
//---------------------------------------------------
void DrawGage(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// Z�o�b�t�@�Ɋւ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (int i = 0; i < 2; i++)
	{
		for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
		{
			if (g_aGage[nCntGage].bUse == true)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aGage[nCntGage].mtxWorld);

				D3DXMATRIX mtxView;
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);	//�r���[�}�g���b�N�X�擾

																//�J�����̋t�s����ݒ�
				g_aGage[nCntGage].mtxWorld._11 = mtxView._11;
				g_aGage[nCntGage].mtxWorld._12 = mtxView._21;
				g_aGage[nCntGage].mtxWorld._13 = mtxView._31;
				g_aGage[nCntGage].mtxWorld._21 = mtxView._12;
				g_aGage[nCntGage].mtxWorld._22 = mtxView._22;
				g_aGage[nCntGage].mtxWorld._23 = mtxView._32;
				g_aGage[nCntGage].mtxWorld._31 = mtxView._13;
				g_aGage[nCntGage].mtxWorld._32 = mtxView._23;
				g_aGage[nCntGage].mtxWorld._33 = mtxView._33;

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aGage[nCntGage].pos.x, g_aGage[nCntGage].pos.y, g_aGage[nCntGage].pos.z);
				D3DXMatrixMultiply(&g_aGage[nCntGage].mtxWorld, &g_aGage[nCntGage].mtxWorld, &mtxTrans);

				//���C�g�𖳌��ɂ���
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aGage[nCntGage].mtxWorld);

				//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffGage[i], 0, sizeof(VERTEX_3D));

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureGage[i]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntGage * 4,
					2);

				pDevice->SetTexture(0, NULL);

				//���C�g��L���ɂ���
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//�K��l�F�l�����݂̃s�N�Z���̒l�ȉ��̏ꍇ�́A�V�����s�N�Z�����󂯓����B
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//---------------------------------------------------
//	���C�t�Q�[�W�ݒ�
//---------------------------------------------------
void SetGage(D3DXVECTOR3 pos, int nLife)
{
	for (int nCntGage = 0; nCntGage < MAX_GAGE; nCntGage++)
	{
		if (g_aGage[nCntGage].bUse == false)
		{
			g_aGage[nCntGage].pos = pos;
			g_aGage[nCntGage].bUse = true;
			g_aGage[nCntGage].nLife = nLife;
			g_aGage[nCntGage].nMaxLife = nLife;

			break;
		}
	}
}

//---------------------------------------------------
//	���C�t�Q�[�W�̃_���[�W����
//---------------------------------------------------
void HitGage(int nCntGage, int nDamage)
{
	//�̗͂����炷
	g_aGage[nCntGage].nLife -= nDamage;

	if (g_aGage[nCntGage].nLife <= 0)
	{//�̗͂��O�ȉ��ɂȂ�����
		g_aGage[nCntGage].bUse = false;	//����
	}
}