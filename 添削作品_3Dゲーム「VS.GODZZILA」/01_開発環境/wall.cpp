//----------------------------------------
//�@�ǂ̏���
//�@Author�F���슲��
//----------------------------------------
#include "wall.h"
#include "meshfield.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall[2] = {};			//�e�N�X�`���փ|�C���^
Wall g_aWall[MAX_WALL];		//�ǂ̍\����

//---------------------------------------------------
//	�ǂ̏�����
//---------------------------------------------------
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\WARNING.png",
		&g_pTextureWall[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\wall002.png",
		&g_pTextureWall[1]);

	//�ǂ̊e�l������
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{//�ǂ̍ő吔����
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�p�x
		g_aWall[nCntWall].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�J���[
		g_aWall[nCntWall].bUse = false;				//�g���Ă��邩�ǂ���
		g_aWall[nCntWall].type = TYPE_WARKING;		//�ǂ̃e�N�X�`���̎��
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{//�ǂ̍ő吔����
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-WALL_X, WALL_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(WALL_X, WALL_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(- WALL_X, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(WALL_X, 0.0f, 0.0f);

		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f * 2, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f * 2, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f * 2, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f * 2, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();

	//�ǂ̐ݒ�
	SetWall(D3DXVECTOR3(-(MESHFIELD_SIZE / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, (-D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) , D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(-(MESHFIELD_SIZE / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) , D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, (MESHFIELD_SIZE / 2.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, (MESHFIELD_SIZE / 2.0f)), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 0.0f, 0.0f), D3DXVECTOR3(0.0f, (-D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -(MESHFIELD_SIZE / 2.0f)), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -(MESHFIELD_SIZE / 2.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3((MESHFIELD_SIZE / 2.0f), 600, 0.0f), TYPE_BILL);
	SetWall(D3DXVECTOR3(-WALL_X, 0.0f, 0.0f), D3DXVECTOR3(0.0f, (-D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(-WALL_X, 0.0f, 0.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, WALL_X), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, WALL_X), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(WALL_X, 0.0f, 0.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(WALL_X, 0.0f, 0.0f), D3DXVECTOR3(0.0f, (-D3DX_PI / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -WALL_X), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -WALL_X), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), D3DXVECTOR3(WALL_X, WALL_Y, 0.0f), TYPE_WARKING);
}

//---------------------------------------------------
//	�ǂ̏I������
//---------------------------------------------------
void UninitWall(void)
{
	if (g_pVtxBuffWall != NULL)
	{//���_�o�b�t�@�j��
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_TYPE; nCnt++)
	{
		if (g_pTextureWall[nCnt] != NULL)
		{//�e�N�X�`���j��
			g_pTextureWall[nCnt]->Release();
			g_pTextureWall[nCnt] = NULL;
		}
	}
}

//---------------------------------------------------
//	�ǂ̍X�V����
//---------------------------------------------------
void UpdateWall(void)
{
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{//�ǂ̍ő吔����
		if (g_aWall[nCntWall].bUse)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].size.x, g_aWall[nCntWall].size.y, 0.0f);	//
			pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].size.x, g_aWall[nCntWall].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].size.x, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].size.x, 0.0f, 0.0f);

			if (g_aWall[nCntWall].type == TYPE_WARKING)
			{//�ǂ̃^�C�v����v������
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex.x += 0.001f;
				pVtx[1].tex.x += 0.001f;
				pVtx[2].tex.x += 0.001f;
				pVtx[3].tex.x += 0.001f;
			}
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------
//	�ǂ̕`�揈��
//---------------------------------------------------
void DrawWall(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	// Z�o�b�t�@�Ɋւ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	// ���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld,
				&g_aWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall[g_aWall[nCntWall].type]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntWall * 4,
				2);

			pDevice->SetTexture(0, NULL);
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			//�K��l�F�l�����݂̃s�N�Z���̒l�ȉ��̏ꍇ�́A�V�����s�N�Z�����󂯓����B
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

//---------------------------------------------------
//	�ǂ̐ݒ�
//---------------------------------------------------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 size, WALLTYPE type)
{
	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;	//�ʒu
			g_aWall[nCntWall].rot = rot;	//�p�x
			g_aWall[nCntWall].col = col;	//�J���[
			g_aWall[nCntWall].size = size;	//�T�C�Y
			g_aWall[nCntWall].bUse = true;	//�g���Ă����Ԃɂ���
			g_aWall[nCntWall].type = type;	//���

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].size.x, g_aWall[nCntWall].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( g_aWall[nCntWall].size.x, g_aWall[nCntWall].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].size.x, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( g_aWall[nCntWall].size.x, 0.0f, 0.0f);

			//���_�J���[
			pVtx[0].col = g_aWall[nCntWall].col;
			pVtx[1].col = g_aWall[nCntWall].col;
			pVtx[2].col = g_aWall[nCntWall].col;
			pVtx[3].col = g_aWall[nCntWall].col;

			if (g_aWall[nCntWall].type == TYPE_WARKING)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f * 2, 0.0f * 2);
				pVtx[1].tex = D3DXVECTOR2(1.0f * 2, 0.0f * 2);
				pVtx[2].tex = D3DXVECTOR2(0.0f * 2, 1.0f * 2);
				pVtx[3].tex = D3DXVECTOR2(1.0f * 2, 1.0f * 2);
			}
			break;
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}

//---------------------------------------------------
//	�ǂ̏��
//---------------------------------------------------
Wall * GetWall(void)
{
	return g_aWall;
}
