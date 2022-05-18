//----------------------------------------
//�@���b�V���t�B�[���h�̏���
//�@Author�F���슲��
//----------------------------------------
#include "meshfield.h"

#define MESHFIELD_X_BLOCK		(3)		// X���̃u���b�N��
#define MESHFIELD_Z_BLOCK		(2)		// Z���̃u���b�N��

#define MESHFIELD_VERTEX		((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))									//���b�V���̒��_
#define MESHFIELD_INDEX			((MESHFIELD_X_BLOCK  + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) * 2)	//�C���f�b�N�X��
#define MESHFIELD_PRIMITIVE		((MESHFIELD_X_BLOCK * MESHFIELD_Z_BLOCK * 2) + (MESHFIELD_Z_BLOCK - 1) * 4)			//�|���S����

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;			//���b�V���t�B�[���h�̃e�N�X�`��
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshfield;		//�ʒu
D3DXVECTOR3 g_rotMeshfield;		//����
D3DXMATRIX g_mtxWorldMeshfield;	//���[���h�}�g���b�N�X

//---------------------------------------------------
//	�|���S���̏�����
//---------------------------------------------------
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\field006.jpg",
		&g_pTextureMeshfield);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;

	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	

	//���_����ݒ�(����)
	/**/
	for (int nCnt_Z = 0; nCnt_Z < MESHFIELD_Z_BLOCK + 1; nCnt_Z++)
	{
		for (int nCnt_X = 0; nCnt_X < MESHFIELD_X_BLOCK + 1; nCnt_X++, nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[nCnt].pos = D3DXVECTOR3((-MESHFIELD_SIZE / 2.0f) + (MESHFIELD_SIZE / MESHFIELD_X_BLOCK) * nCnt_X, 0.0f, (MESHFIELD_SIZE / 2.0f) - (MESHFIELD_SIZE / MESHFIELD_Z_BLOCK) * nCnt_Z);

			//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���)
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (1.0f / MESHFIELD_X_BLOCK) * nCnt_X, 0.0f + (1.0f / MESHFIELD_Z_BLOCK) * nCnt_Z);
		}
	}

	
	
	//���_���W�̐ݒ�
	/*pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f,  50.0f);
	pVtx[1].pos = D3DXVECTOR3(	0.0f, 0.0f,  50.0f);
	pVtx[2].pos = D3DXVECTOR3( 50.0f, 0.0f,  50.0f);

	pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f,   0.0f);
	pVtx[4].pos = D3DXVECTOR3(	0.0f, 0.0f,   0.0f);
	pVtx[5].pos = D3DXVECTOR3( 50.0f, 0.0f,   0.0f);

	pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[7].pos = D3DXVECTOR3(	0.0f, 0.0f, -50.0f);
	pVtx[8].pos = D3DXVECTOR3( 50.0f, 0.0f, -50.0f);*/

	//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���)
	/*pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);*/

	//���_�J���[
	/*pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);*/

	//�e�N�X�`�����W�̐ݒ�
	/*pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);*/

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshfield->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	nCnt = 0;
	int nCntPlas = 0;

	//�C���f�b�N�X�̐ݒ�
	for (int nCnt_Z = 0; nCnt_Z < MESHFIELD_Z_BLOCK; nCnt_Z++)
	{
		for (int nCnt_X = 0; nCnt_X < MESHFIELD_X_BLOCK + 1; nCnt_X++, nCnt++)
		{
			pIdx[nCnt] = (MESHFIELD_X_BLOCK + 1) + nCntPlas;
			pIdx[nCnt + 1] = nCntPlas;

			nCnt++;
			nCntPlas++;
		}

		if (nCnt_Z != (MESHFIELD_Z_BLOCK - 1))
		{
			pIdx[nCnt] = nCntPlas - 1;
			pIdx[nCnt + 1] = nCntPlas + (MESHFIELD_X_BLOCK + 1);

			nCnt += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshField->Unlock();

}

//---------------------------------------------------
//	�|���S���̏I������
//---------------------------------------------------
void UninitMeshfield(void)
{
	//���_�o�b�t�@�j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//---------------------------------------------------
//	�|���S���̍X�V����
//---------------------------------------------------
void UpdateMeshfield(void)
{

}

//---------------------------------------------------
//	�|���S���̕`�揈��
//---------------------------------------------------
void DrawMeshfield(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield,
		&g_mtxWorldMeshfield, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX, 0, MESHFIELD_PRIMITIVE);

	pDevice->SetTexture(0, NULL);
}

