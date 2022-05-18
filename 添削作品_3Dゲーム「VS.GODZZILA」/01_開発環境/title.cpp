//----------------------------------------
//�@�^�C�g����ʂ̏���
//�@Author�F���슲��
//----------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 g_pTextureTitle[2] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle[2] = {};	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posText;

LPDIRECT3DTEXTURE9 g_pTextureK[2] = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffK[2] = {};		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posK;

LPDIRECT3DTEXTURE9 g_pTextureLogo = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLogo = NULL;		//���_�o�b�t�@�ւ̃|�C���^

bool g_bTitle;		//�^�C�g�����1�񂾂��N���p
float g_fCntColor = 0;
float g_fCntTitle = 0;

//----------------------------------------
//  �^�C�g���̏������ݒ菈��
//----------------------------------------
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\PRESSENTER.png",
		&g_pTextureTitle[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title_white.png",
		&g_pTextureK[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title_k.png",
		&g_pTextureK[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\titile_logo.png",
		&g_pTextureLogo);

	//�ʒu������(PRESS ENTER)
	g_posText = D3DXVECTOR3((SCREEN_WIDTH / 2) + 250.0f, 550.0f, 0.0f);
	g_posK = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 10.0f, 0.0f);
	g_bTitle = false;

	//���_�o�b�t�@�̐���
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTitle[nCnt],
			NULL);
	}

	//���_�o�b�t�@�̐���
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffK[nCnt],
			NULL);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLogo,
		NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//�w�i�̒��_
	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
		g_pVtxBuffTitle[0]->Unlock();
	}

	//�e�L�X�g�̒��_
	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posText.x - 200.0f, g_posText.y - 70.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posText.x + 200.0f, g_posText.y - 70.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posText.x - 200.0f, g_posText.y + 70.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posText.x + 200.0f, g_posText.y + 70.0f, 0.0f);

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
		g_pVtxBuffTitle[1]->Unlock();
	}

	//���b
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffK[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posK.x - (SCREEN_WIDTH / 2.0f), g_posK.y - (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posK.x + (SCREEN_WIDTH / 2.0f), g_posK.y - (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posK.x - (SCREEN_WIDTH / 2.0f), g_posK.y + (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posK.x + (SCREEN_WIDTH / 2.0f), g_posK.y + (SCREEN_HEIGHT / 2), 0.0f);

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
		g_pVtxBuffK[nCnt]->Unlock();
		}
	}

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLogo->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffLogo->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_TITLE);
}

//----------------------------------------
//  �^�C�g���̏I������
//----------------------------------------
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffTitle[nCnt] != NULL)
		{
			g_pVtxBuffTitle[nCnt]->Release();
			g_pVtxBuffTitle[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureK[nCnt] != NULL)
		{
			g_pTextureK[nCnt]->Release();
			g_pTextureK[nCnt] = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffK[nCnt] != NULL)
		{
			g_pVtxBuffK[nCnt]->Release();
			g_pVtxBuffK[nCnt] = NULL;
		}
	}

	//�e�N�X�`���̔j��
	if (g_pTextureLogo != NULL)
	{
		g_pTextureLogo->Release();
		g_pTextureLogo = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLogo != NULL)
	{
		g_pVtxBuffLogo->Release();
		g_pVtxBuffLogo = NULL;
	}
}

//----------------------------------------
//  �^�C�g���̍X�V�ݒ菈��
//----------------------------------------
void UpdateTitle(void)
{
	//�e�L�X�g�̒��_
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);

	g_fCntTitle += 0.0005f;	//���X�ɒl��ύX

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f - g_fCntTitle, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f - g_fCntTitle, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f - g_fCntTitle, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f - g_fCntTitle, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle[0]->Unlock();

	g_fCntColor += 0.8f;

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffK[1]->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f + (sinf((D3DX_PI / 270.0f) * g_fCntColor) * 1.0f), 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f + (sinf((D3DX_PI / 270.0f) * g_fCntColor) * 1.0f), 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f + (sinf((D3DX_PI / 270.0f) * g_fCntColor) * 1.0f), 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f + (sinf((D3DX_PI / 270.0f) * g_fCntColor) * 1.0f), 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffK[1]->Unlock();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//���_�������b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffK[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posK.x - (SCREEN_WIDTH / 2.0f), g_posK.y - (SCREEN_HEIGHT / 2.0f) + (sinf((D3DX_PI / 100.0f) * g_fCntColor) * 10.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posK.x + (SCREEN_WIDTH / 2.0f), g_posK.y - (SCREEN_HEIGHT / 2.0f) + (sinf((D3DX_PI / 100.0f) * g_fCntColor) * 10.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posK.x - (SCREEN_WIDTH / 2.0f), g_posK.y + (SCREEN_HEIGHT / 2.0f) + (sinf((D3DX_PI / 100.0f) * g_fCntColor) * 10.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posK.x + (SCREEN_WIDTH / 2.0f), g_posK.y + (SCREEN_HEIGHT / 2.0f) + (sinf((D3DX_PI / 100.0f) * g_fCntColor) * 10.0f), 0.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffK[nCnt]->Unlock();
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && !g_bTitle)
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_RULE);

		g_bTitle = true;
	}
}

//----------------------------------------
//  �^�C�g���̕`�揈��
//----------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�w�i
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[0], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[0]);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{//���b
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffK[nCnt], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureK[nCnt]);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//PRESSENTER
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[1], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[1]);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//�^�C�g�����S
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffLogo, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureLogo);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}