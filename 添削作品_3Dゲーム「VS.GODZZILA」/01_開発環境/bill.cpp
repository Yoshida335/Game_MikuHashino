//----------------------------------------
//�@�r���̏���
//�@Author�F���슲��
//----------------------------------------
#include "bill.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "fade.h"
#include "sound.h"
#include "gage.h"
#include "bill_delete.h"
#include "time.h"
#include "explosion.h"
#include <stdio.h>
#include <string.h>

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshModel[TYPE_MAX] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel[TYPE_MAX] = {};//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatModel = 0;					//�}�e���A�����̐�
Model g_aModel[MAX_MODEL];
int g_nSetModel = 0;
int g_nMaxSetModel = 0;
Parcent g_Parcent;
D3DXMATERIAL * g_pMatModel;			//�}�e���A���f�[�^�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexture[TYPE_MAX][10];	//�e�N�X�`���ւ̃|�C���^

//---------------------------------------------------
//	�r���̃X�R�A���
//---------------------------------------------------
void SaveParcent(void)
{
	FILE * pFile;

	//�m�F�p
	//�t�@�C�����J��
	pFile = fopen("data\\result.txt", "w");		//(�e�L�X�g�����w��, ���[�h���w��)

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		fprintf(pFile, "%.0f\n", g_Parcent.nModelP);
		fprintf(pFile, "%d\n", g_nSetModel);
		fprintf(pFile, "%d\n", g_nMaxSetModel);
		fprintf(pFile, "\n\n");	//���s

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("\n***�@�t�@�C�����J���܂���ł����@***\n");
	}
}

//---------------------------------------------------
//	�r���̏���������
//---------------------------------------------------
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�l�̏�����
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
		g_aModel[nCntModel].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
		g_aModel[nCntModel].diff = 0.0f;								//�����v�Z�p
		g_aModel[nCntModel].rotDestModel = 0.0f;						//�ړI�̊p�x
		g_aModel[nCntModel].bUse = false;								//�g���Ă邩�ǂ���
		g_aModel[nCntModel].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//���_�̍ŏ��l�擾�p
		g_aModel[nCntModel].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);		//���_�̍ő�l�擾�p
		g_aModel[nCntModel].nType = TYPE_BILL_01;	//���
		g_aModel[nCntModel].nLife = 0;				//����
		g_aModel[nCntModel].bHit = false;			//�U���������������ǂ���
		g_aModel[nCntModel].nCntTime = 0;			//�N�[���^�C���̃J�E���g�p
	}

	g_Parcent.nMax = 0.0f;
	g_Parcent.nMaxLife = 0.0f;
	g_Parcent.nModelP = 0.0f;

	g_nSetModel = 0;
	g_nMaxSetModel = 0;

	//�]�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\bill_01.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[0],
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel[0]);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	g_pMatModel = (D3DXMATERIAL*)g_pBuffMatModel[0]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			g_pMatModel[nCntMat].pTextureFilename,
			&g_pTexture[0][nCntMat]);
	}

	D3DXLoadMeshFromX("data\\MODEL\\bill_02.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[1],
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel[1]);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	g_pMatModel = (D3DXMATERIAL*)g_pBuffMatModel[1]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			g_pMatModel[nCntMat].pTextureFilename,
			&g_pTexture[1][nCntMat]);
	}

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	for (int i = 0; i < TYPE_MAX; i++)
	{
		//���_���̎擾
		nNumVtx = g_pMeshModel[i]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel[i]->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_pMeshModel[i]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				// �ŏ��l�����߂�
				if (vtx.x < g_aModel[nCntModel].vtxMin.x)
				{// ��r�����l�������Ă铖�������������������A�u������
					g_aModel[nCntModel].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_aModel[nCntModel].vtxMin.y)
				{// ��r�����l�������Ă铖�������������������A�u������
					g_aModel[nCntModel].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_aModel[nCntModel].vtxMin.z)
				{// ��r�����l�������Ă铖�������������������A�u������
					g_aModel[nCntModel].vtxMin.z = vtx.z;
				}

				// �ő�l�����߂�
				if (vtx.x > g_aModel[nCntModel].vtxMax.x)
				{// ��r�����l�������Ă铖��������傫��������A�u������
					g_aModel[nCntModel].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_aModel[nCntModel].vtxMax.y)
				{// ��r�����l�������Ă铖��������傫��������A�u������
					g_aModel[nCntModel].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_aModel[nCntModel].vtxMax.z)
				{// ��r�����l�������Ă铖��������傫��������A�u������
					g_aModel[nCntModel].vtxMax.z = vtx.z;
				}
			}

			//���_�t�H�[�}�b�g�̃|�C���^���i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@���A�����b�N
		g_pMeshModel[i]->UnlockVertexBuffer();
	}
}

//---------------------------------------------------
//	�r���̏I������
//---------------------------------------------------
void UninitModel(void)
{
	//�r���̃X�R�A�����Z�[�u
	SaveParcent();

	for (int i = 0; i < TYPE_MAX; i++)
	{
		//���b�V���j��
		if (g_pMeshModel[i] != NULL)
		{
			g_pMeshModel[i]->Release();
			g_pMeshModel[i] = NULL;
		}

		//�}�e���A���j��
		if (g_pBuffMatModel[i] != NULL)
		{
			g_pBuffMatModel[i]->Release();
			g_pBuffMatModel[i] = NULL;
		}

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
		{
			if (g_pTexture[i][nCntMat] != NULL)
			{//�e�N�X�`���j��
				g_pTexture[i][nCntMat]->Release();
				g_pTexture[i][nCntMat] = NULL;
			}
		}
	}
}

//---------------------------------------------------
//	�r���̍X�V����
//---------------------------------------------------
void UpdateModel(void)
{
	g_Parcent.nModelP = (10000 - (g_Parcent.nMaxLife / g_Parcent.nMax) * 10000);

	//�r�����S����ꂽ��N���A����
	if (g_nSetModel >= g_nMaxSetModel)
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_RESULT);
		g_nSetModel--;
	}

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse)
		{//�r�����g�p����Ă��鎞
			if (g_aModel[nCntModel].bHit)
			{
				g_aModel[nCntModel].nCntTime++;

				if (g_aModel[nCntModel].nCntTime >= 60)
				{
					g_aModel[nCntModel].bHit = false;
					g_aModel[nCntModel].nCntTime = 0;
				}
			}
		}
	}
}

//---------------------------------------------------
//	�r���̕`�揈��
//---------------------------------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld,
				&g_aModel[nCntModel].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);

			//���݂̃}�e���A���ێ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			g_pMatModel = (D3DXMATERIAL*)g_pBuffMatModel[g_aModel[nCntModel].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&g_pMatModel[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture[g_aModel[nCntModel].nType][nCntMat]);

				//���f���p�[�c�̕`��
				g_pMeshModel[g_aModel[nCntModel].nType]->DrawSubset(nCntMat);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture[g_aModel[nCntModel].nType][nCntMat]);
			}

			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------
//	�r���̐ݒ�
//---------------------------------------------------
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE type, int life)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{// bUse��false��������A
			g_aModel[nCntModel].pos = pos;		//�ʒu
			g_aModel[nCntModel].rot = rot;		//�p�x
			g_aModel[nCntModel].bUse = true;	//�g���Ă��邩�ǂ���(�g���Ă����Ԃɂ���)
			g_aModel[nCntModel].nType = type;	//���
			g_aModel[nCntModel].nLife = life;	//����
			//������\������Q�[�W�̐ݒ�
			SetGage(D3DXVECTOR3(g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y + 100.0f, g_aModel[nCntModel].pos.z),	//�ʒu
				g_aModel[nCntModel].nLife);					//����

			g_Parcent.nMaxLife += g_aModel[nCntModel].nLife;	//�S�̂̍ő�����̒l��ۑ�
			g_Parcent.nMax += g_aModel[nCntModel].nLife;		//�S�̂�

			g_nMaxSetModel++;

			break;
		}
	}
}

//---------------------------------------------------
//	�r���̓����蔻�菈��
//---------------------------------------------------
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move)
{
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{//�ő�r�������m�F
		if (g_aModel[nCntModel].bUse)
		{// bUse��true��������i�r�����g�p����Ă����Ԃ̎�

			/**/
			if (pos->x - (size.x/ 2) < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
				pos->x + (size.x/ 2) > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x &&
				pos->z - (size.z/ 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
				pos->z + (size.z/ 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
			{
				if (posOld->y + size.y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y &&
					pos->y + size.y > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y)
				{//�r���̉�����߂荞�񂾎��̓����蔻��
					pos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y - size.y;
					move->y = 0.0f;
				}
				if (posOld->y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y &&
					pos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y)
				{//�r���̏ォ��߂荞�񂾎��̓����蔻��
					pos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y;
					move->y = 0.0f;
					bIsLanding = true;
				}
			}
			if (pos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y &&
				pos->y + (size.y) > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y)
			{
				if (pos->z - (size.z/ 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
					pos->z + (size.z/ 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
				{// *pos��z���W���r���ɏd�Ȃ��Ă��鎞
					if (posOld->x + (size.x/ 2) <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x &&
						pos->x + (size.x/ 2) >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x)
					{//��������r���ɂ߂荞�񂾎�
					 //*pos.x�Ƀr����pos.x(����)��ݒ�
						pos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x - (size.x/ 2);
					}
					else if (posOld->x - (size.x/ 2) >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
						pos->x - (size.x/ 2) <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x)
					{//�E������r���ɂ߂荞�񂾎�
					 //*pos.x�Ƀr����pos.x(�E��)��ݒ�
						pos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x + (size.x/ 2);
					}
				}
				if (pos->x - (size.x/ 2) < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
					pos->x + (size.x/ 2) > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x)
				{// *pos��x���W���r���ɏd�Ȃ��Ă��鎞
					if (posOld->z - (size.z/ 2) <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z &&
						pos->z + (size.z/ 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
					{//�r���̎�O������߂荞�񂾎�
					 //*pos.z�Ƀr����pos.z(��O��)��ݒ�
						pos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z - (size.z/ 2);
					}
					else if (posOld->z + (size.z/ 2) >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
						pos->z - (size.z/ 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z)
					{//�r���̉�������߂荞�񂾎�
					 //*pos.z�Ƀr����pos.z(����)��ݒ�
						pos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z + (size.z/ 2);
					}
				}
			}
		}
	}

	return bIsLanding;
}

//---------------------------------------------------
//	�����蔻�菈��
//---------------------------------------------------
void CollisionAttack(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{//�ő�r�������m�F
		if (!g_aModel[nCntModel].bUse)
		{// bUse��true��������A�I���
			continue;
		}
		if (g_aModel[nCntModel].bHit)
		{// bHit��true��������A�I���
			continue;
		}
		if (pos->y < g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMax.y &&
			pos->y + (size.y) > g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMin.y)
		{
			if (pos->z - (size.z / 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
				pos->z + (size.z / 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
			{// *pos��z���W���r���ɏd�Ȃ��Ă��鎞
				if (pos->x - (size.x / 2) <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
					pos->x + (size.x / 2) >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x)
				{//��������r���ɂ߂荞�񂾎�
				 //*pos.x�Ƀr����pos.x(����)��ݒ�
					HitModel(nCntModel, 1);
				}
			}
			else if (pos->x - (size.x / 2) < g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMax.x &&
				pos->x + (size.x / 2) > g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMin.x)
			{// *pos��x���W���r���ɏd�Ȃ��Ă��鎞
				if (pos->z - (size.z / 2) < g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMax.z &&
					pos->z + (size.z / 2) > g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMin.z)
				{//�r���̎�O������߂荞�񂾎�
				 //*pos.z�Ƀr����pos.z(��O��)��ݒ�
					HitModel(nCntModel, 1);
				}
			}
		}
	}
}

//---------------------------------------------------
//	�����蔻�菈��
//---------------------------------------------------
void HitModel(int nCntModel, int nDamage)
{
	//�̗͂����炷
	g_aModel[nCntModel].nLife -= nDamage;
	g_aModel[nCntModel].bHit = true;

	HitGage(nCntModel, nDamage);

	g_Parcent.nMaxLife -= nDamage;

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_SE_HIT);

	if (g_aModel[nCntModel].nLife <= 0)
	{//�̗͂��O�ȉ��ɂȂ�����
		SetExplosion(D3DXVECTOR3(g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y + 40.0f, g_aModel[nCntModel].pos.z));
		SetBillDelete(g_aModel[nCntModel].pos, g_aModel[nCntModel].rot);
		g_aModel[nCntModel].bUse = false;	//����
 		g_nSetModel++;	//�z�u�r�����̐������炷
		AddTime(5);		//���Ԃ𑝂₷
	}
}

//---------------------------------------------------
//	�S�̂̓��j�󂳂ꂽ�r���̃p�[�Z���g���
//---------------------------------------------------
Parcent * GetModeParcent(void)
{
	return &g_Parcent;
}