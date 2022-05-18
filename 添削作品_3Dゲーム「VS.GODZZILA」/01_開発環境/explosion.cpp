//----------------------------------------
//�@�����̏���
//�@Author�F���슲��
//----------------------------------------
#include "explosion.h"
#include "shadow.h"
#include "input.h"
#include "sound.h"

//�}�N����`
#define EXPLOSION_X		(20.0f)	// x�����ւ̒l	����
#define EXPLOSION_Y		(20.0f)	// y�����ւ̒l	����
#define EXPLOSION_Z		(0.0f)	// z�����ւ̒l	�c��

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
Explosion g_aExplosion[MAX_EXPLOSION];

//---------------------------------------------------
//	�����̏�����
//---------------------------------------------------
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\explosion.png",
		&g_pTextureExplosion);

	//�����̊e�l������
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].nCntAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_X,  EXPLOSION_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( EXPLOSION_X,  EXPLOSION_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_X, -EXPLOSION_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( EXPLOSION_X, -EXPLOSION_Y, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffExplosion->Unlock();

}

//---------------------------------------------------
//	�����̏I������
//---------------------------------------------------
void UninitExplosion(void)
{

	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//---------------------------------------------------
//	�����̍X�V����
//---------------------------------------------------
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_3D * pVtx;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�������g�p����Ă���
			g_aExplosion[nCntExplosion].nCntAnim++;

			if ((g_aExplosion[nCntExplosion].nCntAnim % 6) == 0)
			{
				//�p�^�[��No.���X�V����
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;

				if (g_aExplosion[nCntExplosion].nPatternAnim == 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim + 0.125f, 1.0f);

			}
		}

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//---------------------------------------------------
//	�����̕`�揈��
//---------------------------------------------------
void DrawExplosion(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// Z�o�b�t�@�Ɋւ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (int i = 0; i < 2; i++)
	{
		for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

				D3DXMATRIX mtxView;
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);	//�r���[�}�g���b�N�X�擾

																//�J�����̋t�s����ݒ�
				g_aExplosion[nCntExplosion].mtxWorld._11 = mtxView._11;
				g_aExplosion[nCntExplosion].mtxWorld._12 = mtxView._21;
				g_aExplosion[nCntExplosion].mtxWorld._13 = mtxView._31;
				g_aExplosion[nCntExplosion].mtxWorld._21 = mtxView._12;
				g_aExplosion[nCntExplosion].mtxWorld._22 = mtxView._22;
				g_aExplosion[nCntExplosion].mtxWorld._23 = mtxView._32;
				g_aExplosion[nCntExplosion].mtxWorld._31 = mtxView._13;
				g_aExplosion[nCntExplosion].mtxWorld._32 = mtxView._23;
				g_aExplosion[nCntExplosion].mtxWorld._33 = mtxView._33;

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
				D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);

				//���C�g�𖳌��ɂ���
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

				//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureExplosion);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntExplosion * 4,
					2);

				pDevice->SetTexture(0, NULL);

				//���C�g��L���ɂ���
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//�K��l�F�l�����݂̃s�N�Z���̒l�ȉ��̏ꍇ�́A�V�����s�N�Z�����󂯓����B
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//---------------------------------------------------
//	�����̐ݒ�
//---------------------------------------------------
void SetExplosion(D3DXVECTOR3 pos)
{
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].bUse = true;
			g_aExplosion[nCntExplosion].nCntAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_EXPLOSION);

			break;
		}
	}
}