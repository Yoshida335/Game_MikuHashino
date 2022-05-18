//----------------------------------------
//�@�|���S���̏���
//�@Author�F���슲��
//----------------------------------------
#include "polygon.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;
D3DXVECTOR3 g_posPolygon;		//�ʒu
D3DXVECTOR3 g_rotPolygon;		//����
D3DXMATRIX g_mtxWorldPolygon;	//���[���h�}�g���b�N�X

//---------------------------------------------------
//	�|���S���̏�����
//---------------------------------------------------
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTexturePolygon);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-POLIGON_X, 0.0f,  POLIGON_Z);
	pVtx[1].pos = D3DXVECTOR3( POLIGON_X, 0.0f,  POLIGON_Z);
	pVtx[2].pos = D3DXVECTOR3(-POLIGON_X, 0.0f, -POLIGON_Z);
	pVtx[3].pos = D3DXVECTOR3( POLIGON_X, 0.0f, -POLIGON_Z);

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

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPolygon->Unlock();
}

//---------------------------------------------------
//	�|���S���̏I������
//---------------------------------------------------
void UninitPolygon(void)
{
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
}

//---------------------------------------------------
//	�|���S���̍X�V����
//---------------------------------------------------
void UpdatePolygon(void)
{

}

//---------------------------------------------------
//	�|���S���̕`�揈��
//---------------------------------------------------
void DrawPolygon(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon,
		&g_mtxWorldPolygon, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, NULL);
}
