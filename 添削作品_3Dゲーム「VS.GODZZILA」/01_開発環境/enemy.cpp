//----------------------------------------
//�@�G�̏���
//�@Author�F���슲��
//----------------------------------------
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "player.h"
#include "explosion.h"
#include "bullet.h"
#include <math.h>
#include <time.h>

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;	//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshEnemy[TYPE_ENEMY_MAX] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatEnemy[TYPE_ENEMY_MAX] = {};//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatEnemy = 0;					//�}�e���A�����̐�
Enemy g_aEnemy[MAX_ENEMY];

//---------------------------------------------------
//	�G�̏���������
//---------------------------------------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�l�̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���݂̈ʒu
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
		g_aEnemy[nCntEnemy].diff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����v�Z�p
		g_aEnemy[nCntEnemy].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̊p�x
		g_aEnemy[nCntEnemy].bUse = false;								//�g���Ă邩�ǂ���
		g_aEnemy[nCntEnemy].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//���_�̍ŏ��l�擾�p
		g_aEnemy[nCntEnemy].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//���_�̍ő�l�擾�p
		g_aEnemy[nCntEnemy].nType = TYPE_ENEMY_01;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].posdis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].bAttack = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\uroko_red.jpg",
		&g_pTextureEnemy);

	//�]�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\airplane000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatEnemy[0],
		NULL,
		&g_nNumMatEnemy,
		&g_pMeshEnemy[0]);

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	for (int i = 0; i < TYPE_ENEMY_MAX; i++)
	{
		//���_���̎擾
		nNumVtx = g_pMeshEnemy[i]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshEnemy[i]->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_pMeshEnemy[i]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				// �ŏ��l�����߂�
				if (vtx.x < g_aEnemy[nCntEnemy].vtxMin.x)
				{// ��r�����l�������Ă铖�������������������A�u������
					g_aEnemy[nCntEnemy].vtxMin.x = vtx.x;
				}
				if (vtx.y < g_aEnemy[nCntEnemy].vtxMin.y)
				{// ��r�����l�������Ă铖�������������������A�u������
					g_aEnemy[nCntEnemy].vtxMin.y = vtx.y;
				}
				if (vtx.z < g_aEnemy[nCntEnemy].vtxMin.z)
				{// ��r�����l�������Ă铖�������������������A�u������
					g_aEnemy[nCntEnemy].vtxMin.z = vtx.z;
				}

				// �ő�l�����߂�
				if (vtx.x > g_aEnemy[nCntEnemy].vtxMax.x)
				{// ��r�����l�������Ă铖��������傫��������A�u������
					g_aEnemy[nCntEnemy].vtxMax.x = vtx.x;
				}
				if (vtx.y > g_aEnemy[nCntEnemy].vtxMax.y)
				{// ��r�����l�������Ă铖��������傫��������A�u������
					g_aEnemy[nCntEnemy].vtxMax.y = vtx.y;
				}
				if (vtx.z > g_aEnemy[nCntEnemy].vtxMax.z)
				{// ��r�����l�������Ă铖��������傫��������A�u������
					g_aEnemy[nCntEnemy].vtxMax.z = vtx.z;
				}

				//�T�C�Y���v�Z
				g_aEnemy[nCntEnemy].size.x = g_aEnemy[nCntEnemy].vtxMax.x - g_aEnemy[nCntEnemy].vtxMin.x;
				g_aEnemy[nCntEnemy].size.y = g_aEnemy[nCntEnemy].vtxMax.y - g_aEnemy[nCntEnemy].vtxMin.y;
				g_aEnemy[nCntEnemy].size.z = g_aEnemy[nCntEnemy].vtxMax.z - g_aEnemy[nCntEnemy].vtxMin.z;
			}

			//���_�t�H�[�}�b�g�̃|�C���^���i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@���A�����b�N
		g_pMeshEnemy[i]->UnlockVertexBuffer();
	}

	//SetEnemy(D3DXVECTOR3(0.0f, 110.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), TYPE_ENEMY_01, 1);


}

//---------------------------------------------------
//	�G�̏I������
//---------------------------------------------------
void UninitEnemy(void)
{
	for (int i = 0; i < TYPE_ENEMY_MAX; i++)
	{
		//���b�V���j��
		if (g_pMeshEnemy[i] != NULL)
		{
			g_pMeshEnemy[i]->Release();
			g_pMeshEnemy[i] = NULL;
		}

		//�}�e���A���j��
		if (g_pBuffMatEnemy[i] != NULL)
		{
			g_pBuffMatEnemy[i]->Release();
			g_pBuffMatEnemy[i] = NULL;
		}
	}

	//�e�N�X�`���j��
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}
}
int g_nCntBullet = 0;
float Angle;

float fRotMove, fRotDest, fRotDiff;
int nLand;
//---------------------------------------------------
//	�G�̍X�V����
//---------------------------------------------------
void UpdateEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

			if (g_aEnemy[nCntEnemy].nLife <= 0)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}

			//�v���C���[�̏��
			Player * pPlayer = GetPlayer();

			//�v���C���[�Ƃ̍������߂�
			g_aEnemy[nCntEnemy].posdis.x = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
			g_aEnemy[nCntEnemy].posdis.z = pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z;
			
			float fLength = D3DXVec3Length(&g_aEnemy[nCntEnemy].posdis);
			
			//���K������
			D3DXVec3Normalize(&g_aEnemy[nCntEnemy].posdis, &g_aEnemy[nCntEnemy].posdis);
			
			if (fLength < 500.0f)
			{//100���ꂽ�痈�Ȃ���B
				g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].posdis * 1.0f;
			}

			if (g_aEnemy[nCntEnemy].bAttack == false)
			{
				g_nCntBullet++;

				if ((g_nCntBullet % 500) == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].rot);
				}
			}

			//�v���C���[�̕����Ɍ�������
			g_aEnemy[nCntEnemy].rot.y = atan2f(-pPlayer->pos.x + g_aEnemy[nCntEnemy].pos.x, -pPlayer->pos.z + g_aEnemy[nCntEnemy].pos.z);

			//�����̐��K��
			if (g_aEnemy[nCntEnemy].rotDest.y - g_aEnemy[nCntEnemy].rot.y > D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rotDest.y -= D3DX_PI * 2.0f;
			}
			else if (g_aEnemy[nCntEnemy].rotDest.y - g_aEnemy[nCntEnemy].rot.y < -D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rotDest.y += D3DX_PI * 2.0f;
			}

			//�G�̈ړ�����
			g_aEnemy[nCntEnemy].rot.y += (g_aEnemy[nCntEnemy].rotDest.y - g_aEnemy[nCntEnemy].rot.y) * 0.05f;

			//�p�x�̐��K��
			if (g_aEnemy[nCntEnemy].rot.y < -D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rot.y += D3DX_PI * 2.0f;
			}
			else if (g_aEnemy[nCntEnemy].rot.y > D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rot.y -= D3DX_PI * 2.0f;
			}

			//�v���C���[�Ƃ̓����蔻��
			CollisionPlayer(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, D3DXVECTOR3(g_aEnemy[nCntEnemy].size.x + 10.0f, g_aEnemy[nCntEnemy].size.y, g_aEnemy[nCntEnemy].size.z + 10.0f));
		}
	}

}

//---------------------------------------------------
//	�G�̕`�揈��
//---------------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld,
				&g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//���݂̃}�e���A���ێ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[g_aEnemy[nCntEnemy].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�G�p�[�c�̕`��
				g_pMeshEnemy[g_aEnemy[nCntEnemy].nType]->DrawSubset(nCntMat);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
			}

			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------------------------------
//	�G�̐ݒ�
//---------------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int life)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{// bUse��false��������A
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].rot = rot;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nType = type;
			g_aEnemy[nCntEnemy].nLife = life;

			break;
		}
	}
}

//---------------------------------------------------
//	�G�̓����蔻��
//---------------------------------------------------
void CollisionEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
{
	for (int nCntModel = 0; nCntModel < MAX_ENEMY; nCntModel++)
	{//�ő僂�f�������m�F
		if (g_aEnemy[nCntModel].bUse == true)
		{// bUse��true��������i���f�����g�p����Ă����Ԃ̎�
			{// bHit��false��������i�U�����������Ă��Ȃ��A�N�[���^�C�����̎�
				if (pos->y < g_aEnemy[nCntModel].pos.y + g_aEnemy[nCntModel].vtxMax.y &&
					pos->y + (size.y) > g_aEnemy[nCntModel].pos.y + g_aEnemy[nCntModel].vtxMin.y)
				{
					if (pos->z - (size.z / 2) < g_aEnemy[nCntModel].pos.z + g_aEnemy[nCntModel].vtxMax.z &&
						pos->z + (size.z / 2) > g_aEnemy[nCntModel].pos.z + g_aEnemy[nCntModel].vtxMin.z)
					{// *pos��z���W�����f���ɏd�Ȃ��Ă��鎞
						if (pos->x - (size.x / 2) <= g_aEnemy[nCntModel].pos.x + g_aEnemy[nCntModel].vtxMax.x &&
							pos->x + (size.x / 2) >= g_aEnemy[nCntModel].pos.x + g_aEnemy[nCntModel].vtxMin.x)
						{//�������烂�f���ɂ߂荞�񂾎�
						 //*pos.x�Ƀ��f����pos.x(����)��ݒ�
							HitEnemyl(nCntModel, 1);
						}
					}
					else if (pos->x - (size.x / 2) < g_aEnemy[nCntModel].pos.x + g_aEnemy[nCntModel].vtxMax.x &&
						pos->x + (size.x / 2) > g_aEnemy[nCntModel].pos.x + g_aEnemy[nCntModel].vtxMin.x)
					{// *pos��x���W�����f���ɏd�Ȃ��Ă��鎞
						if (pos->z - (size.z / 2) < g_aEnemy[nCntModel].pos.z + g_aEnemy[nCntModel].vtxMax.z &&
							pos->z + (size.z / 2) > g_aEnemy[nCntModel].pos.z + g_aEnemy[nCntModel].vtxMin.z)
						{//���f���̎�O������߂荞�񂾎�
						 //*pos.z�Ƀ��f����pos.z(��O��)��ݒ�
							HitEnemyl(nCntModel, 1);
						}
					}
				}
			}
		}
	}
}

//---------------------------------------------------
//	�q�b�g����
//---------------------------------------------------
void HitEnemyl(int nCntModel, int nDamage)
{
	//�̗͂����炷
	g_aEnemy[nCntModel].nLife -= nDamage;

	if (g_aEnemy[nCntModel].nLife <= 0)
	{//�̗͂��O�ȉ��ɂȂ�����
		SetExplosion(g_aEnemy[nCntModel].pos);
		g_aEnemy[nCntModel].bUse = false;	//����
	}
}
