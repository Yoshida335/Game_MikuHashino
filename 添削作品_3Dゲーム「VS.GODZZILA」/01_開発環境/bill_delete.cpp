//----------------------------------------
//�@�r��(�j���)�̏���
//�@Author�F���슲��
//----------------------------------------
#include "bill_delete.h"
#include "input.h"
#include "shadow.h"
#include "fade.h"
#include "sound.h"
#include "gage.h"
#include <stdio.h>
#include <string.h>

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshDeleteModel = NULL;			//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatDeleteModel = NULL;		//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatDeleteModel = 0;					//�}�e���A�����̐�
BillDelete g_aDeleteModel[MAX_BILLDELETE];	//�r��(�j���)�̍\����
D3DXMATERIAL * g_pMatDeleteModel;			//�}�e���A���f�[�^�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureDelete[10];	//�e�N�X�`���ւ̃|�C���^

//---------------------------------------------------
//	�r��(�j���)�̏���������
//---------------------------------------------------
void InitBillDelete(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�]�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\bill_off.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatDeleteModel,
		NULL,
		&g_nNumMatDeleteModel,
		&g_pMeshDeleteModel);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	g_pMatDeleteModel = (D3DXMATERIAL*)g_pBuffMatDeleteModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatDeleteModel; nCntMat++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			g_pMatDeleteModel[nCntMat].pTextureFilename,
			&g_pTextureDelete[nCntMat]);
	}

	//�e�l�̏�����
	for (int nCntModel = 0; nCntModel < MAX_BILLDELETE; nCntModel++)
	{
		g_aDeleteModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
		g_aDeleteModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
		g_aDeleteModel[nCntModel].bUse = false;							//�g���Ă邩�ǂ���
	}
}

//---------------------------------------------------
//	�r��(�j���)�̏I������
//---------------------------------------------------
void UninitBillDelete(void)
{
	//���b�V���j��
	if (g_pMeshDeleteModel != NULL)
	{
		g_pMeshDeleteModel->Release();
		g_pMeshDeleteModel = NULL;
	}

	//�}�e���A���j��
	if (g_pBuffMatDeleteModel != NULL)
	{
		g_pBuffMatDeleteModel->Release();
		g_pBuffMatDeleteModel = NULL;
	}

	//�e�N�X�`���j��
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatDeleteModel; nCntMat++)
	{
		if (g_pTextureDelete[nCntMat] != NULL)
		{
			g_pTextureDelete[nCntMat]->Release();
			g_pTextureDelete[nCntMat] = NULL;
		}
	}
}

//---------------------------------------------------
//	�r��(�j���)�̍X�V����
//---------------------------------------------------
void UpdateBillDelete(void)
{
	//�����Ȃ�
}

//---------------------------------------------------
//	�r��(�j���)�̕`�揈��
//---------------------------------------------------
void DrawBillDelete(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < MAX_BILLDELETE; nCntModel++)
	{
		if (g_aDeleteModel[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aDeleteModel[nCntModel].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aDeleteModel[nCntModel].rot.y, g_aDeleteModel[nCntModel].rot.x, g_aDeleteModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aDeleteModel[nCntModel].mtxWorld,
				&g_aDeleteModel[nCntModel].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aDeleteModel[nCntModel].pos.x, g_aDeleteModel[nCntModel].pos.y, g_aDeleteModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aDeleteModel[nCntModel].mtxWorld, &g_aDeleteModel[nCntModel].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aDeleteModel[nCntModel].mtxWorld);

			//���݂̃}�e���A���ێ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatDeleteModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatDeleteModel; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureDelete[nCntMat]);

				//���f���p�[�c�̕`��
				g_pMeshDeleteModel->DrawSubset(nCntMat);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureDelete[nCntMat]);
			}

			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------
//	�r��(�j���)�̐ݒ�
//---------------------------------------------------
void SetBillDelete(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntModel = 0; nCntModel < MAX_BILLDELETE; nCntModel++)
	{
		if (!g_aDeleteModel[nCntModel].bUse)
		{// bUse��false��������A
			g_aDeleteModel[nCntModel].pos = pos;	//�ʒu
			g_aDeleteModel[nCntModel].rot = rot;	//�p�x
			g_aDeleteModel[nCntModel].bUse = true;	//�g���Ă����Ԃɂ���
			break;
		}
	}
}