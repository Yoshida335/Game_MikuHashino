//----------------------------------------
//�@�J�����̏���
//�@Author�F���슲��
//----------------------------------------
#include "camera.h"
#include "input.h"
#include "player.h"
#include "mouse.h"

//�}�N����`
#define MAX_CAMERA		(2)	//�J�����̍ő吔

//�O���[�o���ϐ��錾
CAMERA g_camera[MAX_CAMERA];
int g_nCnt = 0;

//---------------------------------------------------
//	�J�����̏���������
//---------------------------------------------------
void InitCamera(void)
{
	//�r���[�|�[�g�\���̕ۑ�
	g_camera[0].viewport.X = 0;			//�r���[�|�[�g�̊J�n�ʒu(x���W)
	g_camera[0].viewport.Y = 0;			//�r���[�|�[�g�̊J�n�ʒu(y���W)
	g_camera[0].viewport.Width = SCREEN_WIDTH;		//�r���[�|�[�g�̕�
	g_camera[0].viewport.Height = SCREEN_HEIGHT;	//�r���[�|�[�g�̍���
	g_camera[0].viewport.MinZ = 0.0f;
	g_camera[0].viewport.MaxZ = 1.0f;

	g_camera[1].viewport.X = 10;			//�r���[�|�[�g�̊J�n�ʒu(x���W)
	g_camera[1].viewport.Y = (SCREEN_HEIGHT - 300 - 10);			//�r���[�|�[�g�̊J�n�ʒu(y���W)	(SCREEN_HEIGHT - 250)
	g_camera[1].viewport.Width = 300;	//�r���[�|�[�g�̕�
	g_camera[1].viewport.Height = 300;	//�r���[�|�[�g�̍���
	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;

	//���_�E�����_�E�������ݒ肷��
	g_camera[0].posV = D3DXVECTOR3(0.0f, 140.0f, -100.0f);	//���݂̎��_
	g_camera[0].posR = D3DXVECTOR3(0.0f, 100.0f, 00.0f);		//�����_
	g_camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�����(�Œ�)

	g_camera[0].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̎��_
	g_camera[0].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̒����_

	//������
	g_camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	g_camera[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̌���

	//���_���璍���_�̋���
	g_camera[0].fDistance = sqrtf((g_camera[0].posV.x - g_camera[0].posR.x) * (g_camera[0].posV.x - g_camera[0].posR.x)
		+ (g_camera[0].posV.z - g_camera[0].posR.z) * (g_camera[0].posV.z - g_camera[0].posR.z));


	//���_�E�����_�E�������ݒ肷��
	g_camera[1].posV = D3DXVECTOR3(0.0f, 800.0f, -D3DX_PI / 2.0f);	//���݂̎��_
	g_camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����_
	g_camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�����(�Œ�)

	g_camera[1].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̎��_
	g_camera[1].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̒����_

	//������
	g_camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	g_camera[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̌���

	//���_���璍���_�̋���
	g_camera[1].fDistance = sqrtf((g_camera[1].posV.x - g_camera[1].posR.x) * (g_camera[1].posV.x - g_camera[1].posR.x)
		+ (g_camera[1].posV.z - g_camera[1].posR.z) * (g_camera[1].posV.z - g_camera[1].posR.z));


	GetCursorPos(&g_camera[0].CenterPointer);

	g_camera[0].NowPointer = g_camera[0].CenterPointer;
}

//---------------------------------------------------
//	�J�����̏I������
//---------------------------------------------------
void UninitCamera(void)
{

}

//---------------------------------------------------
//	�J�����̍X�V����
//---------------------------------------------------
void UpdateCamera(void)
{
	g_camera[0].posVOld = g_camera[0].posV;


	ShowCursor(false);	// true�ŃJ�[�\���\���Afalse�Ŕ�\��

	//�J�[�\���̈ʒu�� NowPointer �ɓ����
	GetCursorPos(&g_camera[0].NowPointer);

	//���S�̈ʒu���猻�݂̈ʒu�������āA�ړ��ʌv�Z
	g_camera[0].MovePointer.x = g_camera[0].CenterPointer.x - g_camera[0].NowPointer.x;
	g_camera[0].MovePointer.y = g_camera[0].CenterPointer.y - g_camera[0].NowPointer.y;

	//�����_�̐���
	if (g_camera[0].MovePointer.x != 0.0f)
	{//���E�}�E�X�ړ�
		g_camera[0].rot.y -= g_camera[0].MovePointer.x * 0.0005f;
	}

	//�ړ��ʕ����ʒu�ɉ��Z
	g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
	g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * g_camera[0].fDistance;

	//�����_�̐���(���E)
	if (GetKeyboardPress(DIK_Q) == true)
	{//Q�L�[�������ꂽ(������)
		g_camera[0].rot.y -= 0.01f;
		g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{//E�L�[�������ꂽ(�E����)
		g_camera[0].rot.y += 0.01f;
		g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}

	//�����_�̐���(�㉺)
	if (GetKeyboardPress(DIK_R) == true)
	{//R�L�[�������ꂽ(������)
		g_camera[0].posR.y += 2.0f;
	}
	else if (GetKeyboardPress(DIK_F) == true)
	{//F�L�[�������ꂽ(�E����)
		g_camera[0].posR.y -= 2.0f;
	}

	//���_�̐���(�㉺)
	if (GetKeyboardPress(DIK_T) == true)
	{//R�L�[�������ꂽ(������)
		g_camera[0].posV.y += 2.0f;
	}
	else if (GetKeyboardPress(DIK_G) == true)
	{//F�L�[�������ꂽ(�E����)
		g_camera[0].posV.y -= 2.0f;
	}

	//���_�̐���(���E)
	if (GetKeyboardPress(DIK_Z) == true)
	{//Z�L�[�������ꂽ(������)
		g_camera[0].rot.y -= 0.01f;
		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{//C�L�[�������ꂽ(�E����)
		g_camera[0].rot.y += 0.01f;
		g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}

	//�v���C���[�Ǐ]����
	Player * pPlayer = GetPlayer();		//�v���C���[�̏����擾

	//�ړI�̒����_�̈ʒu���v�Z
	g_camera[0].posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 10.0f;
	g_camera[0].posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 10.0f;
	//�ړI�̎��_�̈ʒu���v�Z
	g_camera[0].posVDest.x = pPlayer->pos.x - sinf(g_camera[0].rot.y) * 100.0f;
	g_camera[0].posVDest.z = pPlayer->pos.z - cosf(g_camera[0].rot.y) * 100.0f;

	//�ړI�̒����_�ʒu�܂ňړ�
	g_camera[0].posR.x += (g_camera[0].posRDest.x - g_camera[0].posR.x) * 0.05f;
	g_camera[0].posR.z += (g_camera[0].posRDest.z - g_camera[0].posR.z) * 0.05f;
	//�ړI�̎��_�ʒu�܂ňړ�
	g_camera[0].posV.x += (g_camera[0].posVDest.x - g_camera[0].posV.x) * 0.05f;
	g_camera[0].posV.z += (g_camera[0].posVDest.z - g_camera[0].posV.z) * 0.05f;

	//�p�x�̐��K��
	if (g_camera[0].rot.y > D3DX_PI)
	{
		g_camera[0].rot.y -= D3DX_PI * 2;
	}
	else if (g_camera[0].rot.y < -D3DX_PI)
	{
		g_camera[0].rot.y += D3DX_PI * 2;
	}

	if (g_camera[0].rot.z > D3DX_PI)
	{
		g_camera[0].rot.z -= D3DX_PI * 2;
	}
	else if (g_camera[0].rot.z < -D3DX_PI)
	{
		g_camera[0].rot.z += D3DX_PI * 2;
	}

	if (g_camera[0].rot.x > D3DX_PI)
	{
		g_camera[0].rot.x -= D3DX_PI * 2;
	}
	else if (g_camera[0].rot.x < -D3DX_PI)
	{
		g_camera[0].rot.x += D3DX_PI * 2;
	}

	/*
*/

	//�J�����̈ړ�
	//MoveCamera();
}

//---------------------------------------------------
//	�J�����̈ړ�����
//---------------------------------------------------
void MoveCamera(void)
{
	for (int i = 0; i < 1; i++)
	{
		if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[�������ꂽ
			if (GetKeyboardPress(DIK_D) == true)
			{//D�L�[�Ɖ����ꂽ�Ƃ�
				g_camera[i].posV.x += sinf(g_camera[i].rot.y + (D3DX_PI / 4)) * CAMERA_SPEED;			//���_�̈ʒu�ړ�
				g_camera[i].posV.z += cosf(g_camera[i].rot.y + (D3DX_PI / 4)) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//�����_�̈ʒu�ړ�
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//A�L�[�Ɖ����ꂽ�Ƃ�
				g_camera[i].posV.x += sinf(g_camera[i].rot.y - (D3DX_PI / 4)) * CAMERA_SPEED;			//���_�̈ʒu�ړ�
				g_camera[i].posV.z += cosf(g_camera[i].rot.y - (D3DX_PI / 4)) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//�����_�̈ʒu�ړ�
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
			else
			{//W�L�[�̂�(���ʂɐi��)
				g_camera[i].posV.x += sinf(g_camera[i].rot.y) * CAMERA_SPEED;							//���_�̈ʒu�ړ�
				g_camera[i].posV.z += cosf(g_camera[i].rot.y) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//�����_�̈ʒu�ړ�
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
		}
		else  if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[�������ꂽ
			if (GetKeyboardPress(DIK_D) == true)
			{//D�L�[�Ɖ����ꂽ�Ƃ�
				g_camera[i].posV.x += sinf(g_camera[i].rot.y + (D3DX_PI / 4 * 3.0f)) * CAMERA_SPEED;	//���_�̈ʒu�ړ�
				g_camera[i].posV.z += cosf(g_camera[i].rot.y + (D3DX_PI / 4 * 3.0f)) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//�����_�̈ʒu�ړ�
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//A�L�[�Ɖ����ꂽ�Ƃ�
				g_camera[i].posV.x += sinf(g_camera[i].rot.y - (D3DX_PI / 4 * 3.0f)) * CAMERA_SPEED;	//���_�̈ʒu�ړ�
				g_camera[i].posV.z += cosf(g_camera[i].rot.y - (D3DX_PI / 4 * 3.0f)) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//�����_�̈ʒu�ړ�
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
			else
			{//S�L�[�̂�(���ɐi��)
				g_camera[i].posV.x += sinf(g_camera[i].rot.y - D3DX_PI) * CAMERA_SPEED;				//���_�̈ʒu�ړ�
				g_camera[i].posV.z += cosf(g_camera[i].rot.y - D3DX_PI) * CAMERA_SPEED;

				g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//�����_�̈ʒu�ړ�
				g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[�������ꂽ(�E�ɐi��)
			g_camera[i].posV.x += sinf(g_camera[i].rot.y + (D3DX_PI / 2)) * CAMERA_SPEED;			//���_�̈ʒu�ړ�
			g_camera[i].posV.z += cosf(g_camera[i].rot.y + (D3DX_PI / 2)) * CAMERA_SPEED;

			g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//�����_�̈ʒu�ړ�
			g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[�������ꂽ(���ɐi��)
			g_camera[i].posV.x += sinf(g_camera[i].rot.y - (D3DX_PI / 2)) * CAMERA_SPEED;			//���_�̈ʒu�ړ�
			g_camera[i].posV.z += cosf(g_camera[i].rot.y - (D3DX_PI / 2)) * CAMERA_SPEED;

			g_camera[i].posR.x = g_camera[i].posV.x + sinf(g_camera[i].rot.y) * g_camera[i].fDistance;	//�����_�̈ʒu�ړ�
			g_camera[i].posR.z = g_camera[i].posV.z + cosf(g_camera[i].rot.y) * g_camera[i].fDistance;
		}
	}
}

//---------------------------------------------------
//	�J�����̐ݒ�
//---------------------------------------------------
void SetCamera(int nCnt)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCnt].mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera[nCnt].mtxView,
		&g_camera[nCnt].posV,
		&g_camera[nCnt].posR,
		&g_camera[nCnt].vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCnt].mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCnt].mtxProjection);

	switch (nCnt)
	{//�J�����ɂ���ăA�X�y�N�g���ς���
	case 0:
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&g_camera[nCnt].mtxProjection,
			D3DXToRadian(45.0f),							//����p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//�A�X�y�N�g��
			10.0f,			//�ǂ�����(�j�A)
			1000.0f);		//�ǂ��܂�(�t�@�[)
		break;

	case 1:
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&g_camera[nCnt].mtxProjection,
			D3DXToRadian(45.0f),							//����p
			(float)250 / (float)250,		//�A�X�y�N�g��
			10.0f,			//�ǂ�����(�j�A)
			1000.0f);		//�ǂ��܂�(�t�@�[)
		break;
	}

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCnt].mtxProjection);
}

//---------------------------------------------------
//	�J�����̏��
//---------------------------------------------------
CAMERA * GetCamera(void)
{
	return g_camera;
}
