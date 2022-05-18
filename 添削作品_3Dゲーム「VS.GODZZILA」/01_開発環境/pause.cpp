//----------------------------------------
//�@�|�[�Y����
//�@Author�F���슲��
//----------------------------------------
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause[3] = {};	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePause[3] = {};			//�e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
PAUSE g_Pause[3];
int g_nSelectPause;

//----------------------------------------
// �|�[�Y�̏������ݒ菈��
//----------------------------------------
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\pause001.png",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\pause002.png",
		&g_pTexturePause[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\pause003.png",
		&g_pTexturePause[2]);

	//���_�o�b�t�@�̐���
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffPause[nCnt],
			NULL);
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		g_Pause[nCnt].pos = D3DXVECTOR3(((float)SCREEN_WIDTH / 2.0f), 200 + (150.0f * nCnt), 0.0f);
		g_Pause[nCnt].state = SELECT_OFF;
	}
	g_Pause[1].state = SELECT_ON;
	g_nSelectPause = 0;

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPause[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Pause[nCnt].pos.x - (400.0f / 2.0f), g_Pause[nCnt].pos.y - (120.0f / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Pause[nCnt].pos.x + (400.0f / 2.0f), g_Pause[nCnt].pos.y - (120.0f / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Pause[nCnt].pos.x - (400.0f / 2.0f), g_Pause[nCnt].pos.y + (120.0f / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Pause[nCnt].pos.x + (400.0f / 2.0f), g_Pause[nCnt].pos.y + (120.0f / 2), 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPause[nCnt]->Unlock();
	}

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseBG->Unlock();
}

//----------------------------------------
// �|�[�Y�̏I������
//----------------------------------------
void UninitPause(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffPause[nCnt] != NULL)
		{
			g_pVtxBuffPause[nCnt]->Release();
			g_pVtxBuffPause[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}
}

//----------------------------------------
// �|�[�Y�̍X�V�ݒ菈��
//----------------------------------------
void UpdatePause(void)
{
	bool * pPause = GetPause();

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPause[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		switch (g_Pause[nCnt].state)
		{
		case SELECT_OFF:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case SELECT_ON:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPause[nCnt]->Unlock();
	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{//W�L�[�������ꂽ
		g_nSelectPause--;

		if (g_nSelectPause < 0)
		{
			g_nSelectPause = 2;
		}
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{//S�L�[�������ꂽ
		g_nSelectPause++;

		if (g_nSelectPause > 2)
		{
			g_nSelectPause = 0;
		}
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (g_nSelectPause == nCnt)
		{
			g_Pause[nCnt].state = SELECT_ON;
		}
		else if (g_nSelectPause != nCnt)
		{
			g_Pause[nCnt].state = SELECT_OFF;
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		switch (g_nSelectPause)
		{
		case 0:
			*pPause = false;
			break;

		case 1:
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_GAME);
			break;

		case 2:
			//���[�h�ݒ�(�����L���O��ʂɈڍs)
			SetFade(MODE_RANKING);
			break;
		}
	}
}

//----------------------------------------
// �|�[�Y�̕`�揈��
//----------------------------------------
void DrawPause(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPause[nCnt], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCnt]);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
