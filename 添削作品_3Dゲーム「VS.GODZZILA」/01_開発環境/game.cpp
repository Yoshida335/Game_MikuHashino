//================================================================
//�@�Q�[����ʂ̏���
//�@Author�F���슲��
//================================================================
//---------------------------------------------------
//	�C���N���[�h�t�@�C��
//---------------------------------------------------
#include "game.h"
#include "input.h"
#include "fade.h"
#include "time.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "input.h"
#include "bill.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "bullet.h"
#include "meshfield.h"
#include "effect.h"
#include "particle.h"
#include "player.h"
#include "enemy.h"
#include "collision.h"
#include "map.h"
#include "gage.h"
#include "scoregage.h"
#include "bill_delete.h"
#include "explosion.h"
#include "mouse.h"
#include "pause.h"

//�O���[�o���ϐ��錾
bool g_bPause = false;		//�|�[�Y�����ǂ���

//---------------------------------------------------
//	�Q�[����ʂ̏���������
//---------------------------------------------------
void InitGame(void)
{
	//�|�[�Y��ʂ̏���������
	InitPause();

	//�J�����̏����ݒ�
	InitCamera();

	//���C�g�̏����ݒ�
	InitLight();

	//�^�C�}�[�̏����ݒ�
	InitTime();

	//�G�t�F�N�g�̏����ݒ�
	InitEffect();

	//�p�[�e�B�N���̏����ݒ�
	InitParticle();

	//���b�V���t�B�[���h(����)�̏����ݒ�
	InitMeshfield();

	//�e�̏����ݒ�
	InitShadow();

	//���C�t�Q�[�W�̏����ݒ�
	InitGage();

	//�X�R�A�Q�[�W�̏����ݒ�
	InitScoreGage();

	//�����̏����ݒ�
	InitExplosion();

	//�j��ヂ�f���̏����ݒ�
	InitBillDelete();

	//���f���̏����ݒ�
	InitModel();

	//�G�̏����ݒ�
	InitEnemy();

	//�v���C���[�̏����ݒ�
	InitPlayer();

	//�����蔻��̏����ݒ�
	InitCollision();

	//�e�̏����ݒ�
	InitBullet();

	//�ǂ̏����ݒ�
	InitWall();

	//�}�b�v�̐ݒ�
	SetMap();

	g_bPause = false;		//�|�[�Y����(������)

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM_GAME);
}

//---------------------------------------------------
//	�Q�[����ʂ̏I������
//---------------------------------------------------
void UninitGame(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�����̏I������
	UninitExplosion();

	//���C�t�Q�[�W�̏I������
	UninitGage();

	//�X�R�A�Q�[�W�̏I������
	UninitScoreGage();

	//�e�̏I������
	UninitBullet();

	//�ǂ̏I������
	UninitWall();

	//�e�̏I������
	UninitShadow();

	//���f���̏I������
	UninitModel();

	//�j��ヂ�f���̏I������
	UninitBillDelete();

	//�G�̏I������
	UninitEnemy();

	//�����蔻��̏I������
	UninitCollision();

	//�v���C���[�̏I������
	UninitPlayer();

	//���b�V���t�B�[���h�̏I������
	UninitMeshfield();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�^�C�}�[�̏I������
	UninitTime();

	//���C�g�̏I������
	UninitLight();

	//�J�����̏I������
	UninitCamera();

	//�}�E�X�̏I������
	UninitMouse();

	//�|�[�Y��ʂ̏I������
	UninitPause();
}

//---------------------------------------------------
//	�Q�[����ʂ̍X�V����
//---------------------------------------------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�X�L�[(P�L�[)�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{
		//�|�[�Y��ʂ̍X�V����
		UpdatePause();
	}

	if (g_bPause == false)
	{//�|�[�Y���łȂ����
		//�J�����̍X�V����
		UpdateCamera();

		//���C�g�̍X�V����
		UpdateLight();

		//�^�C�}�[�̍X�V����
		UpdateTime();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();

		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshfield();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�����̍X�V����
		UpdateExplosion();

		//�����蔻��̍X�V����
		UpdateCollision();

		//���f���̍X�V����
		UpdateModel();

		//�j��ヂ�f���̍X�V����
		UpdateBillDelete();

		//�e�̍X�V����
		UpdateShadow();

		//���C�t�Q�[�W�̍X�V����
		UpdateGage();

		//�X�R�A�Q�[�W�̍X�V����
		UpdateScoreGage();

		//�e�̍X�V����
		UpdateBullet();

		//�ǂ̍X�V����
		UpdateWall();
	}

	//�}�E�X�̍X�V����
	UpdateMouse();
}

//---------------------------------------------------
//	�Q�[����ʂ̕`�揈��
//---------------------------------------------------
void DrawGame(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewport;		//�r���[�|�[�g

	pDevice->GetViewport(&viewport);

	//�J�����̏��擾
	CAMERA * pCamera = GetCamera();

	for (int i = 0; i < 2; i++)
	{
		//�r���[�|�[�g�̐ݒ�
		pDevice->SetViewport(&pCamera[i].viewport);

		//��ʃN���A
		pDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0),
			1.0f, 0);

		//�J�����̕`�揈��
		SetCamera(i);

		//�}�E�X�̕`�揈��
		DrawMouse();

		//���b�V���t�B�[���h�̕`�揈��
		DrawMeshfield();

		//�j��ヂ�f���̕`�揈��
		DrawBillDelete();

		//���f���̕`�揈��
		DrawModel();

		//�v���C���[�̕`�揈��
		DrawPlayer();

		//�G�̕`�揈��
		DrawEnemy();

		//�����蔻��̕`�揈��
		DrawCollision();

		//�e�̕`�揈��
		DrawShadow();

		//�ǂ̕`�揈��
		DrawWall();

		//���C�t�Q�[�W�̕`�揈��
		DrawGage();

		//�X�R�A�Q�[�W�̕`�揈��
		DrawScoreGage();

		//�����̕`�揈��
		DrawExplosion();

		//�e�̕`�揈��
		DrawBullet();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		//�p�[�e�B�N���̕`�揈��
		DrawParticle();

		//�^�C�}�[�̕`�揈��
		DrawTime();

		if (g_bPause)
		{
			//�|�[�Y��ʂ̕`�揈��
			DrawPause();
		}
	}

	pDevice->SetViewport(&viewport);
}

//---------------------------------------------------
//	�|�[�Y�����ǂ����̏��
//---------------------------------------------------
bool * GetPause(void)
{
	return &g_bPause;
}
