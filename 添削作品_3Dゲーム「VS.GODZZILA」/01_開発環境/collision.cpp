//----------------------------------------
//�@�����蔻��̏���
//�@Author�F���슲��
//----------------------------------------
#include "collision.h"
#include "bill.h"
#include "enemy.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCollision = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCollision = NULL;			//���b�V���t�B�[���h�̃e�N�X�`��
COLLISION g_Collision[MAX_COLLISION];

//---------------------------------------------------
//	������
//---------------------------------------------------
void InitCollision(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Shock_wave_ring001.png",
		&g_pTextureCollision);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_COLLISION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCollision,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffCollision->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
	{
		//�ʒu�ݒ�
		g_Collision[nCntCollision].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Collision[nCntCollision].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Collision[nCntCollision].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Collision[nCntCollision].bUse = false;
		g_Collision[nCntCollision].nLife = 0;
		g_Collision[nCntCollision].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffCollision->Unlock();
}

//---------------------------------------------------
//	�����蔻��̏I������
//---------------------------------------------------
void UninitCollision(void)
{
	//���_�o�b�t�@�j��
	if (g_pVtxBuffCollision != NULL)
	{
		g_pVtxBuffCollision->Release();
		g_pVtxBuffCollision = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureCollision != NULL)
	{
		g_pTextureCollision->Release();
		g_pTextureCollision = NULL;
	}
}
//---------------------------------------------------
//	�����蔻��̍X�V����
//---------------------------------------------------
void UpdateCollision(void)
{
	for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
	{
		if (g_Collision[nCntCollision].bUse == true)
		{
			CollisionAttack(&g_Collision[nCntCollision].pos, &g_Collision[nCntCollision].posOld, D3DXVECTOR3(10.0f, 30.0f, 10.0f));
			CollisionEnemy(&g_Collision[nCntCollision].pos, &g_Collision[nCntCollision].posOld, D3DXVECTOR3(30.0f, 40.0f, 30.0f));

			g_Collision[nCntCollision].nLife--;

			if (g_Collision[nCntCollision].nLife <= 0)
			{
				g_Collision[nCntCollision].bUse = false;
			}
		}
	}
}

//---------------------------------------------------
//	�����蔻��̕`�揈��
//---------------------------------------------------
void DrawCollision(void)
{

}

//---------------------------------------------------
//	�����蔻��̐ݒ�
//---------------------------------------------------
void SetCollision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 rot)
{
	for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
	{
		if (g_Collision[nCntCollision].bUse == false)
		{
			g_Collision[nCntCollision].pos = pos;
			g_Collision[nCntCollision].posOld = posOld;
			g_Collision[nCntCollision].rot = rot;
			g_Collision[nCntCollision].bUse = true;
			g_Collision[nCntCollision].nLife = 60;

			break;
		}
	}
}