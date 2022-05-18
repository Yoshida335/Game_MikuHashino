//----------------------------------------
//�@�G�t�F�N�g�̏���
//�@Author�F���슲��
//----------------------------------------
#include "effect.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
Effect g_aEffect[MAX_EFFECT];

//---------------------------------------------------
//	�G�t�F�N�g�̏�����
//---------------------------------------------------
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Particle02.png",
		&g_pTextureEffect);

	//�G�t�F�N�g�̊e�l������
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].bUse = false;
		g_aEffect[nCntEffect].nLife = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].size.x,  g_aEffect[nCntEffect].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( g_aEffect[nCntEffect].size.x,  g_aEffect[nCntEffect].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].size.x, -g_aEffect[nCntEffect].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( g_aEffect[nCntEffect].size.x, -g_aEffect[nCntEffect].size.y, 0.0f);

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
	g_pVtxBuffEffect->Unlock();
}

//---------------------------------------------------
//	�G�t�F�N�g�̏I������
//---------------------------------------------------
void UninitEffect(void)
{
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
}

//---------------------------------------------------
//	�G�t�F�N�g�̍X�V����
//---------------------------------------------------
void UpdateEffect(void)
{
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//�G�t�F�N�g�̎��������炷
			g_aEffect[nCntEffect].nLife--;

			//���X�Ƀ��l��������
			g_aEffect[nCntEffect].col.a -= 0.03f;

			if (g_aEffect[nCntEffect].nLife <= 0)
			{//���C�t��0�ɂȂ�����Afalse��(�g�p���ĂȂ����)
				g_aEffect[nCntEffect].bUse = false;
			}

			//���_�J���[�X�V
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

		}
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//---------------------------------------------------
//	�G�t�F�N�g�̕`�揈��
//---------------------------------------------------
void DrawEffect(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z�o�b�t�@�Ɋւ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);	//�r���[�}�g���b�N�X�擾

			//�J�����̋t�s����ݒ�
			g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEffect * 4,
				2);

			//�e�N�X�`����NULL
			pDevice->SetTexture(0, NULL);

			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//�K��l�F�l�����݂̃s�N�Z���̒l�ȉ��̏ꍇ�́A�V�����s�N�Z�����󂯓����B
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//---------------------------------------------------
//	�G�t�F�N�g�̐ݒ�
//---------------------------------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size)
{
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].rot = rot;
			g_aEffect[nCntEffect].size = size;
			g_aEffect[nCntEffect].bUse = true;
			g_aEffect[nCntEffect].nLife = nLife;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-size.x,  size.y, size.z);
			pVtx[1].pos = D3DXVECTOR3( size.x,  size.y, size.z);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, size.z);
			pVtx[3].pos = D3DXVECTOR3( size.x, -size.y, size.z);

			//���_�J���[
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}

