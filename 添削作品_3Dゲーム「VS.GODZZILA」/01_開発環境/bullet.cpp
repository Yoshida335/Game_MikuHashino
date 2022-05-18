//----------------------------------------
//�@�e�̏���
//�@Author�F���슲��
//----------------------------------------
#include "bullet.h"
#include "shadow.h"
#include "bill.h"
#include "effect.h"
#include "Player.h"

//�}�N����`
#define Bullet_X		(3.0f)	// x�����ւ̒l	����
#define Bullet_Y		(3.0f)	// y�����ւ̒l	����
#define Bullet_Z		(3.0f)	// z�����ւ̒l	�c��
#define BULLET_DAMAGE	(4)		// �e�ŗ^����_���[�W��

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`���̂ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];	//�e�̍\����

//---------------------------------------------------
//	�e�̏�����
//---------------------------------------------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\Bullet000.png",
		&g_pTextureBullet);

	//�e�̊e�l������
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�p�x
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�J���[
		g_aBullet[nCntBullet].bUse = false;		//�g���Ă��邩�ǂ���
		g_aBullet[nCntBullet].nLife = 0;		//����
		g_aBullet[nCntBullet].posdis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�v���C���[�Ƃ̍������߂�p
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-Bullet_X, Bullet_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Bullet_X, Bullet_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-Bullet_X, -Bullet_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Bullet_X, -Bullet_Y, 0.0f);

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

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//---------------------------------------------------
//	�e�̏I������
//---------------------------------------------------
void UninitBullet(void)
{
	if (g_pVtxBuffBullet != NULL)
	{//���_�o�b�t�@�j��
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	if (g_pTextureBullet != NULL)
	{//�e�N�X�`���j��
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//---------------------------------------------------
//	�e�̍X�V����
//---------------------------------------------------
void UpdateBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�o���b�g�̍ő吔����
		if (g_aBullet[nCntBullet].bUse)
		{//�e���g�p����Ă��鎞
			//�e�̈ʒu�ړ�
			g_aBullet[nCntBullet].pos.x -= sinf(g_aBullet[nCntBullet].rot.y) * 1.0f;
			g_aBullet[nCntBullet].pos.z -= cosf(g_aBullet[nCntBullet].rot.y) * 1.0f;

			//���������炵�Ă���
			g_aBullet[nCntBullet].nLife -= 1;

			if (g_aBullet[nCntBullet].nLife <= 0)
			{//�e�̎�����0�ɂȂ�����false�ɂ���
				g_aBullet[nCntBullet].bUse = false;
			}

			//�v���C���[�̏��
			Player * pPlayer = GetPlayer();

			//�v���C���[�Ƃ̍������߂�
			g_aBullet[nCntBullet].posdis.x = pPlayer->pos.x - g_aBullet[nCntBullet].pos.x;
			g_aBullet[nCntBullet].posdis.z = pPlayer->pos.z - g_aBullet[nCntBullet].pos.z;

			//���K������
			D3DXVec3Normalize(&g_aBullet[nCntBullet].posdis, &g_aBullet[nCntBullet].posdis);

			//�v���C���[�̕����ɒǔ�
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].posdis * 1.0f;

			//�G�t�F�N�g����
			SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].rot, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 40, D3DXVECTOR3(4.0f, 4.0f, 0.0f));
			SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].rot, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.8f), 40, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
		}
	}
}

//---------------------------------------------------
//	�e�̕`�揈��
//---------------------------------------------------
void DrawBullet(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);	//�r���[�}�g���b�N�X�擾

			//�J�����̋t�s����ݒ�
			g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,
				2);

			pDevice->SetTexture(0, NULL);

			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//---------------------------------------------------
//	�e�̐ݒ�
//---------------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�e�̍ő吔����
		if (!g_aBullet[nCntBullet].bUse)
		{//�e���g�p����Ă��Ȃ���Ԃ̎�
			g_aBullet[nCntBullet].pos = pos;	//�ʒu
			g_aBullet[nCntBullet].rot = rot;	//�p�x
			g_aBullet[nCntBullet].bUse = true;	//�g���Ă��邩�ǂ���(�g���Ă����Ԃɂ���)
			g_aBullet[nCntBullet].nLife = 100;	//����
			break;
		}
	}
}

//---------------------------------------------------
//	�e�̓����蔻�菈��
//---------------------------------------------------
void CollisionBullet(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�e�̍ő吔����
		if (!g_aBullet[nCntBullet].bUse)
		{// bUse��false��������i���f�����g�p����Ă��Ȃ���Ԃ̎��A�I���
			continue;
		}
		if (pos->x - (size.x / 2) < g_aBullet[nCntBullet].pos.x + (Bullet_X / 2.0f) &&
			pos->x + (size.x / 2) > g_aBullet[nCntBullet].pos.x - (Bullet_X / 2.0f) &&
			pos->z - (size.z / 2) < g_aBullet[nCntBullet].pos.z + (Bullet_Z / 2.0f) &&
			pos->z + (size.z / 2) > g_aBullet[nCntBullet].pos.z - (Bullet_Z / 2.0f))
		{
			if (posOld->y + size.y <= g_aBullet[nCntBullet].pos.y - (Bullet_Y / 2.0f) &&
				pos->y + size.y > g_aBullet[nCntBullet].pos.y - (Bullet_Y / 2.0f))
			{//���f���̉�����߂荞�񂾎��̓����蔻��
				g_aBullet[nCntBullet].bUse = false;	//�e������
				HitModel(BULLET_DAMAGE);	//�v���C���[�̃q�b�g����
				//�G�t�F�N�g��ݒ�
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z), g_aBullet[nCntBullet].rot, D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 100, D3DXVECTOR3(40.0f, 40.0f, 0.0f));
			}
			if (posOld->y >= g_aBullet[nCntBullet].pos.y + (Bullet_Y / 2.0f) &&
				pos->y < g_aBullet[nCntBullet].pos.y + (Bullet_Y / 2.0f))
			{//���f���̏ォ��߂荞�񂾎��̓����蔻��
				g_aBullet[nCntBullet].bUse = false;	//�e������
				HitModel(BULLET_DAMAGE);	//�v���C���[�̃q�b�g����
				//�G�t�F�N�g��ݒ�
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z), g_aBullet[nCntBullet].rot, D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 100, D3DXVECTOR3(40.0f, 40.0f, 0.0f));
			}
		}
		if (pos->y < g_aBullet[nCntBullet].pos.y + (Bullet_Y / 2.0f) &&
			pos->y + (size.y) > g_aBullet[nCntBullet].pos.y - (Bullet_Y / 2.0f))
		{
			if (pos->z - (size.z / 2) < g_aBullet[nCntBullet].pos.z + (Bullet_Z / 2.0f) &&
				pos->z + (size.z / 2) > g_aBullet[nCntBullet].pos.z - (Bullet_Z / 2.0f))
			{// *pos��z���W�����f���ɏd�Ȃ��Ă��鎞
				if (posOld->x + (size.x / 2) <= g_aBullet[nCntBullet].pos.x - (Bullet_X / 2.0f) &&
					pos->x + (size.x / 2) >= g_aBullet[nCntBullet].pos.x - (Bullet_X / 2.0f))
				{//�������烂�f���ɂ߂荞�񂾎�
				 //*pos.x�Ƀ��f����pos.x(����)��ݒ�
					g_aBullet[nCntBullet].bUse = false;	//�e������
					HitModel(BULLET_DAMAGE);	//�v���C���[�̃q�b�g����
					//�G�t�F�N�g��ݒ�
					SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z), g_aBullet[nCntBullet].rot, D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 100, D3DXVECTOR3(40.0f, 40.0f, 0.0f));
				}
				else if (posOld->x - (size.x / 2) >= g_aBullet[nCntBullet].pos.x + (Bullet_X / 2.0f) &&
					pos->x - (size.x / 2) <= g_aBullet[nCntBullet].pos.x + (Bullet_X / 2.0f))
				{//�E�����烂�f���ɂ߂荞�񂾎�
				 //*pos.x�Ƀ��f����pos.x(�E��)��ݒ�
					g_aBullet[nCntBullet].bUse = false;	//�e������
					HitModel(BULLET_DAMAGE);	//�v���C���[�̃q�b�g����
					//�G�t�F�N�g��ݒ�
					SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z), g_aBullet[nCntBullet].rot, D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 100, D3DXVECTOR3(40.0f, 40.0f, 0.0f));
				}
			}
			if (pos->x - (size.x / 2) < g_aBullet[nCntBullet].pos.x + (Bullet_X / 2.0f) &&
				pos->x + (size.x / 2) > g_aBullet[nCntBullet].pos.x - (Bullet_X / 2.0f))
			{// *pos��x���W�����f���ɏd�Ȃ��Ă��鎞
				if (posOld->z - (size.z / 2) <= g_aBullet[nCntBullet].pos.z - (Bullet_Z / 2.0f) &&
					pos->z + (size.z / 2) > g_aBullet[nCntBullet].pos.z - (Bullet_Z / 2.0f))
				{//���f���̎�O������߂荞�񂾎�
				 //*pos.z�Ƀ��f����pos.z(��O��)��ݒ�
					g_aBullet[nCntBullet].bUse = false;	//�e������
					HitModel(BULLET_DAMAGE);	//�v���C���[�̃q�b�g����
					//�G�t�F�N�g��ݒ�
					SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z), g_aBullet[nCntBullet].rot, D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 100, D3DXVECTOR3(40.0f, 40.0f, 0.0f));
				}
				else if (posOld->z + (size.z / 2) >= g_aBullet[nCntBullet].pos.z + (Bullet_Z / 2.0f) &&
					pos->z - (size.z / 2) < g_aBullet[nCntBullet].pos.z + (Bullet_Z / 2.0f))
				{//���f���̉�������߂荞�񂾎�
				 //*pos.z�Ƀ��f����pos.z(����)��ݒ�
					g_aBullet[nCntBullet].bUse = false;	//�e������
					HitModel(BULLET_DAMAGE);	//�v���C���[�̃q�b�g����
					//�G�t�F�N�g��ݒ�
					SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z), g_aBullet[nCntBullet].rot, D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 100, D3DXVECTOR3(40.0f, 40.0f, 0.0f));
				}
			}
		}
	}
}