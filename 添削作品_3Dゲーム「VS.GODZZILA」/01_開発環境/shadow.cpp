//----------------------------------------
//�@�e�̏���
//�@Author�F���슲��
//----------------------------------------
#include "shadow.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;
Shadow g_aShadow[MAX_SHADOW];

//---------------------------------------------------
//	�e�̏�����
//---------------------------------------------------
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
		g_aShadow[nCntShadow].size = 0.0f;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//�ő吔����
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].size / 2), 0.0f, (g_aShadow[nCntShadow].size / 2));
		pVtx[1].pos = D3DXVECTOR3((g_aShadow[nCntShadow].size / 2), 0.0f, (g_aShadow[nCntShadow].size / 2));
		pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].size / 2), 0.0f, -(g_aShadow[nCntShadow].size / 2));
		pVtx[3].pos = D3DXVECTOR3((g_aShadow[nCntShadow].size / 2), 0.0f, -(g_aShadow[nCntShadow].size / 2));

		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���)
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

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

		pVtx += 4;	//���_����+4
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//---------------------------------------------------
//	�e�̏I������
//---------------------------------------------------
void UninitShadow(void)
{
	if (g_pVtxBuffShadow != NULL)
	{//���_�o�b�t�@�̔j��
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	if (g_pTextureShadow != NULL)
	{//�e�N�X�`���̔j��
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//---------------------------------------------------
//	�e�̍X�V����
//---------------------------------------------------
void UpdateShadow(void)
{
	//�����Ȃ�
}

//---------------------------------------------------
//	�|���S���̕`�揈��
//---------------------------------------------------
void DrawShadow(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//�ő吔����
		if (g_aShadow[nCntShadow].bUse)
		{//�g�p���Ă��鎞�A�`�悷��
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld,
				&g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntShadow * 4,
				2);

			//���u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			pDevice->SetTexture(0, NULL);
		}
	}
}

//---------------------------------------------------
//	�e�̐ݒ�
//---------------------------------------------------
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float size)
{
	int nCntShadow;
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (!g_aShadow[nCntShadow].bUse)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;
			g_aShadow[nCntShadow].size = size;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].size / 2), 0.0f, (g_aShadow[nCntShadow].size / 2));
			pVtx[1].pos = D3DXVECTOR3((g_aShadow[nCntShadow].size / 2), 0.0f, (g_aShadow[nCntShadow].size / 2));
			pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].size / 2), 0.0f, -(g_aShadow[nCntShadow].size / 2));
			pVtx[3].pos = D3DXVECTOR3((g_aShadow[nCntShadow].size / 2), 0.0f, -(g_aShadow[nCntShadow].size / 2));

			pVtx += 4;	//���_����+4
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;		//�e�̔ԍ�(index)��Ԃ�
}

//---------------------------------------------------
//	�e�̈ʒu�̍X�V����
//---------------------------------------------------
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}

