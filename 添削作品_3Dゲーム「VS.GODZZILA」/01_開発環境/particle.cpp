//----------------------------------------
//�@�p�[�e�B�N���̏���
//�@Author�F���슲��
//----------------------------------------
#include "particle.h"
#include "effect.h"
#include "input.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Particle g_aParticle[MAX_PARTICLE];

//---------------------------------------------------
//	�p�[�e�B�N���̏���������
//---------------------------------------------------
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�擾

	//�G�t�F�N�g�̊e�l������
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].bUse = false;
		g_aParticle[nCntParticle].nLife = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//---------------------------------------------------
//	�p�[�e�B�N���̏I������
//---------------------------------------------------
void UninitParticle(void)
{
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//---------------------------------------------------
//	�p�[�e�B�N���̍X�V����
//---------------------------------------------------
void UpdateParticle(void)
{
	//�p�x�������_���Őݒ�
	float fpRot = (float)(rand() % (314 - 0 + 1)) - 157 / 100.0f + 10.0f;
	//�ʒu�������_���Őݒ�
	//float fpPos = (float)((rand() % (100 - 0 + 1)) - 50) + 10.0f;

	//�p�[�e�B�N����ݒ�
	//SetParticle(D3DXVECTOR3(0.0f, 20.0f, -80.0f), D3DXVECTOR3(fpRot, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f), 20, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	//SetParticle(D3DXVECTOR3(0.0f, 20.0f, -80.0f), D3DXVECTOR3(fpRot, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 10, D3DXVECTOR3(1.0f, 1.0f, 0.0f));

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{// �g�p����Ă���ꍇ
			//�G�t�F�N�g��ݒ�
			SetEffect(g_aParticle[nCntParticle].pos, g_aParticle[nCntParticle].rot, g_aParticle[nCntParticle].col, g_aParticle[nCntParticle].nLife, g_aParticle[nCntParticle].size);

			//�ړ��ʂ�ݒ�(�����Ă��������)
			g_aParticle[nCntParticle].move.x = sinf(g_aParticle[nCntParticle].rot.x);
			g_aParticle[nCntParticle].move.z = cosf(g_aParticle[nCntParticle].rot.z);

			//�d��
			g_aParticle[nCntParticle].move.y -= 0.1f;

			//�ړ��ʉ��Z
			g_aParticle[nCntParticle].pos.x += g_aParticle[nCntParticle].move.x;
			g_aParticle[nCntParticle].pos.y += g_aParticle[nCntParticle].move.y;
			g_aParticle[nCntParticle].pos.z += g_aParticle[nCntParticle].move.z;

			//���C�t�����炵�Ă���
			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife < 0)
			{// �p�[�e�B�N���̃��C�t��0�ɂȂ�����Afalse�ɂ���
				g_aParticle[nCntParticle].bUse = false;
				g_aParticle[nCntParticle].move.y = 0.0f;
			}
		}
	}
}

//---------------------------------------------------
//	�p�[�e�B�N���̕`�揈��
//---------------------------------------------------
void DrawParticle(void)
{

}

//---------------------------------------------------
//	�p�[�e�B�N���̐ݒ�
//---------------------------------------------------
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].rot = rot;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].size = size;
			g_aParticle[nCntParticle].bUse = true;

			break;
		}
	}
}

