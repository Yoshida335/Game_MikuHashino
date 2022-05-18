//----------------------------------------
//�@�^�C���̏���
//�@Author�F���슲��
//----------------------------------------
#include "time.h"
#include "fade.h"
#include "input.h"
#include "map.h"
#include "enemy.h"
#include <time.h>

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;
D3DXVECTOR3 g_posTime[3];	//�^�C���̐�
int g_nTime;				//���݂̃^�C��
int g_nCntTime;				//�J�E���g�^�C��
TIME g_TimeState;			//�^�C���̏��
bool g_bFinishTime = false;	//�^�C���I�����̉�ʑJ�ڂ����N������p

//----------------------------------------
//  �^�C���̏������ݒ菈��
//----------------------------------------
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number.png",
		&g_pTextureTime);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		g_posTime[nCntT] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏���
	}
	g_nTime = 30;				//�^�C���̏�����
	g_nCntTime = 60;			//�^�C���̍X�V���ԏ�����
	g_TimeState = TIME_ON;		//�^�C���̏�ԏ�����(�N����)
	g_bFinishTime = false;		//false�ɂ���

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{//�^�C���̈ʒu�ݒ�
		g_posTime[nCntT] = D3DXVECTOR3(35.0f * nCntT + (SCREEN_WIDTH / 2) - 35.0f, 40.0f, 0.0f);
	}

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCntT].x - 20.0f, g_posTime[nCntT].y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCntT].x + 20.0f, g_posTime[nCntT].y - 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCntT].x - 20.0f, g_posTime[nCntT].y + 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCntT].x + 20.0f, g_posTime[nCntT].y + 25.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhm = 1.0f;
		pVtx[1].rhm = 1.0f;
		pVtx[2].rhm = 1.0f;
		pVtx[3].rhm = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//----------------------------------------
//�@�^�C���̏I������
//----------------------------------------
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//----------------------------------------
//  �^�C���̍X�V����
//----------------------------------------
void UpdateTime(void)
{
	int nTimePos[3];

	switch (g_TimeState)
	{
	case TIME_ON:	//�^�C���N����(�Q�[���J�n)
		if (g_nTime != 0)
		{//���݂̎��Ԃ��O����Ȃ�������
		 //�J�E���g����1���炷
			g_nCntTime--;
		}

		if (g_nCntTime <= 0)
		{//�J�E���g�����O��������
			g_nTime--;

			if (g_nTime % 10 == 0)
			{//���Ԍo�߂ŃG�l�~�[�o��
				//�G�l�~�[�̏o���ʒu�������Ă���(map.cpp)
				SetPos * pSetEnemyPos = GetSetPos();
			
				for (int i = 0; i < 4; i++)
				{//�G�l�~�[�o��
					SetEnemy(pSetEnemyPos->Setpos[i], D3DXVECTOR3(0.0f, 0.0f, 0.0f), TYPE_ENEMY_01, 1);
				}
			}

			//�J�E���g�������Z�b�g
			g_nCntTime = 60;
		}

		//���ݎ�������^�C���̃e�N�X�`�����W���v�Z
		nTimePos[0] = g_nTime % 1000 / 100;
		nTimePos[1] = g_nTime % 100 / 10;
		nTimePos[2] = g_nTime % 10;

		VERTEX_2D * pVtx;	//���_���ւ̃|�C���^

		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntT = 0; nCntT < 3; nCntT++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntT] + 0.1f, 1.0f);

			pVtx += 4;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();

		if (g_nTime <= 0)
		{//�^�C�����O�ȉ��ɂȂ�����
			g_TimeState = TIME_OFF;	//�^�C���I�t�ɂ���
		}

		break;

	case TIME_OFF:	//�^�C���I�t(�Q�[���I��)
		if(g_bFinishTime == false)
		{//��񂾂��N������
			//���[�h�ݒ�(���U���g��ʂɈڍs)
			SetFade(MODE_RESULT);

			g_bFinishTime = true;
		}

		break;
	}
}

//----------------------------------------
//  �^�C���̕`�揈��
//----------------------------------------
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// Z�o�b�t�@�Ɋւ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntT = 0; nCntT < 3; nCntT++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntT * 4, 2);
	}

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//�K��l�F�l�����݂̃s�N�Z���̒l�ȉ��̏ꍇ�́A�V�����s�N�Z�����󂯓����B
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//----------------------------------------
//  �^�C���̏��
//----------------------------------------
int * GetTime(void)
{
	return &g_nTime;
}

//----------------------------------------
//  �^�C���̉��Z
//----------------------------------------
void AddTime(int nTime)
{
	g_nTime += nTime;
}