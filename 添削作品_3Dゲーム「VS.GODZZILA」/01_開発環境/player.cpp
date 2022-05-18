//----------------------------------------
//�@�v���C���[�̏���
//�@Author�F���슲��
//----------------------------------------
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "bullet.h"
#include "effect.h"
#include "bill.h"
#include "fade.h"
#include "collision.h"
#include "enemy.h"
#include "time.h"
#include "scoregage.h"
#include "sound.h"
#include "map.h"

//�}�N����`
#define MOTION_PAS			("data\\motion.txt")	//�v���C���[�̃��[�V�����e�L�X�g
#define PLAYER_JUMP			(5.0f)	//�v���C���[�̃W�����v��
#define PLAYER_INERTIA		(0.1f)	//�v���C���[�̊����̗�
#define PLAYER_LIFE			(100)	//�v���C���[�̗̑�
#define PLAYER_SHADOW		(50.0f)	//�v���C���[�̉e�̑傫��

//�p�[�c�Z�b�g�̍\����
typedef struct
{
	int nIndex;			//�����̔ԍ�
	int nParent;		//�e
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//�p�x
}PARTSSET;

//Key�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//�p�x
}Key;

//KeySet�̍\����
typedef struct
{
	int nFrame;		//�v���[����
	Key Key[20];	//�L�[��
}KeySet;

//���[�V�����Z�b�g�̍\����
typedef struct
{
	int nLoop;				//���[�v���邩�ǂ���
	int nNumKey;			//�ő�L�[��
	KeySet KeySet[20];		//�ݒ肵�Ă���L�[
}MOTIONSET;

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshPlayer = NULL;			//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;		//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatPlayer = 0;					//�}�e���A�����̐�
Player g_Player;							//�v���C���[�̕ϐ��錾
int nNowFrame = 0;		//���݂̃t���[����
int nCntFrame = 0;		//���Đ��t���[����
int nNowKeySet = 0;					//���ݍĐ�����KeySet�ԍ�
int nNextKeySet = nNowKeySet + 1;	//���ɍĐ�����KeySet�ԍ�
int g_nPlayMotion = 0;	//���ݍĐ����̃��[�V�����ԍ�
SetPlayer g_SetPlayer;
int g_nSelectMotion;	//���[�V�����I��p
D3DXMATERIAL * g_pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

//���f���A���[�V������ǂݍ��ނƂ��Ɏg���O���[�o���ϐ�
int g_nNumParts;			//�p�[�c��
PARTSSET PartsSet[20];		//�ǂݍ��񂾃p�[�c�̏�������ϐ�
MOTIONSET MotionSet[10];	//�ǂݍ��񂾃��[�V������������ϐ�
char cModelPas[20][256];	//���f���̃p�X��ǂݍ��ޗp
D3DXVECTOR3 MotionDiff[20];

//---------------------------------------------------
//	���f�����t�@�C������ǂݍ���
//---------------------------------------------------
void LoadModel(void)
{
	FILE * pFile;

	char cData[256];	//������ǂݍ��ޗp
	int nData;			//������ǂݍ��ޗp

	int nCntParts;		//�p�[�c���ۑ��p

	int nCntMotion = 0;		//���[�V���������J�E���g����
	int nCntKey = 0;		//�L�[�����J�E���g����
	int nCntKeyParts = 0;	//�L�[�p�[�c�����J�E���g����

	pFile = fopen(MOTION_PAS, "r");

	// strncmp : �w�肵����������r����
	// sscanf : �w�肵������ϐ��ɓ����
	// fgetc : ��s��ǂݍ���

	if (pFile != NULL)
	{//�t�@�C�����J������
		do
		{//"SCRIPT"�ƈ�v����܂ŉ�
			fscanf(pFile, "%s", &cData[0]);
		} while (strcmp(&cData[0], "SCRIPT") != 0);

		do
		{//"END_SCRIPT"�ƈ�v����܂ŉ�
			fscanf(pFile, "%s", &cData[0]);

			//���f���̃t�@�C���p�X��ǂݍ���
			if (strcmp(&cData[0], "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%s", &cData[0]);
				fscanf(pFile, "%d", &nCntParts);

				for (int i = 0, nCntModel = 0; i < nCntParts; i++, nCntModel++)
				{//���f���p�[�c������
					do
					{//"MODEL_FILENAME"�ƈ�v����܂ŉ�
						fscanf(pFile, "%s", &cData[0]);
					} while (strcmp(&cData[0], "MODEL_FILENAME") != 0);

					if (strcmp(&cData[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &cData[0]);		// "��"��΂��p
						fscanf(pFile, "%s", &cModelPas[nCntModel][0]);
					}
				}
			}

			//�L�����N�^�[����ǂݍ���
			if (strcmp(&cData[0], "CHARACTERSET") == 0)
			{
				do
				{//"END_CHARACTERSET"�ƈ�v����܂ŉ�
					fscanf(pFile, "%s", &cData[0]);

					if (strcmp(&cData[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &cData[0]);
						fscanf(pFile, "%d", &nData);
						g_nNumParts = nData;	//�p�[�c����ۑ�

						for (int i = 0, nCntParts = 0; i < g_nNumParts; i++, nCntParts++)
						{
							do
							{//"PARTSSET"�ƈ�v����܂ŉ�
								fscanf(pFile, "%s", &cData[0]);
							} while (strcmp(&cData[0], "PARTSSET") != 0);

							if (strcmp(&cData[0], "PARTSSET") == 0)
							{
								do
								{//"END_PARTSSET"�ƈ�v����܂ŉ�
									fscanf(pFile, "%s", &cData[0]);

									if (strcmp(&cData[0], "INDEX") == 0)
									{
										fscanf(pFile, "%s", &cData[0]);
										fscanf(pFile, "%d", &PartsSet[nCntParts].nIndex);
									}
									if (strcmp(&cData[0], "PARENT") == 0)
									{
										fscanf(pFile, "%s", &cData[0]);
										fscanf(pFile, "%d", &PartsSet[nCntParts].nParent);
									}
									if (strcmp(&cData[0], "POS") == 0)
									{
										fscanf(pFile, "%s", &cData[0]);
										fscanf(pFile, "%f", &PartsSet[nCntParts].pos.x);
										fscanf(pFile, "%f", &PartsSet[nCntParts].pos.y);
										fscanf(pFile, "%f", &PartsSet[nCntParts].pos.z);
									}
									if (strcmp(&cData[0], "ROT") == 0)
									{
										fscanf(pFile, "%s", &cData[0]);
										fscanf(pFile, "%f", &PartsSet[nCntParts].rot.x);
										fscanf(pFile, "%f", &PartsSet[nCntParts].rot.y);
										fscanf(pFile, "%f", &PartsSet[nCntParts].rot.z);
									}
								} while (strcmp(&cData[0], "END_PARTSSET") != 0);
							}
						}
					}
				} while (strcmp(&cData[0], "END_CHARACTERSET") != 0);
			}

			//���[�V�����̓ǂݍ���
			if (strcmp(&cData[0], "MOTIONSET") == 0)
			{
				do
				{//"END_MOTIONSET"�ƈ�v����܂ŉ�
					fscanf(pFile, "%s", &cData[0]);

					if (strcmp(&cData[0], "LOOP") == 0)
					{// "LOOP"�ƈ�v�����Ƃ�
						fscanf(pFile, "%s", &cData[0]);		// "="
						fscanf(pFile, "%d", &MotionSet[nCntMotion].nLoop);	//���[�v
					}
					if (strcmp(&cData[0], "NUM_KEY") == 0)
					{// "NUM_KEY"�ƈ�v�����Ƃ�
						fscanf(pFile, "%s", &cData[0]);		// "="
						fscanf(pFile, "%d", &MotionSet[nCntMotion].nNumKey);		//�L�[��
					}
					if (strcmp(&cData[0], "KEYSET") == 0)
					{// "KEYSET"�ƈ�v�����Ƃ�
						do
						{//"END_KEYSET"�ƈ�v����܂ŉ�
							fscanf(pFile, "%s", &cData[0]);

							if (strcmp(&cData[0], "FRAME") == 0)
							{// "FRAME"�ƈ�v�����Ƃ�
								fscanf(pFile, "%s", &cData[0]);		// "="
								fscanf(pFile, "%d", &MotionSet[nCntMotion].KeySet[nCntKey].nFrame);		//�t���[����
							}
							if (strcmp(&cData[0], "KEY") == 0)
							{// "KEY"�ƈ�v�����Ƃ�
								do
								{//"END_KEY"�ƈ�v����܂ŉ�
									fscanf(pFile, "%s", &cData[0]);

									if (strcmp(&cData[0], "POS") == 0)
									{// "POS"�ƈ�v�����Ƃ�
										fscanf(pFile, "%s", &cData[0]);		// "="
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].pos.x);	// x���W
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].pos.y);	// y���W
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].pos.z);	// z���W
									}
									if (strcmp(&cData[0], "ROT") == 0)
									{// "ROT"�ƈ�v�����Ƃ�
										fscanf(pFile, "%s", &cData[0]);		// "="
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].rot.x);	// x��
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].rot.y);	// y��
										fscanf(pFile, "%f", &MotionSet[nCntMotion].KeySet[nCntKey].Key[nCntKeyParts].rot.z);	// z��
									}
								} while (strcmp(&cData[0], "END_KEY") != 0);

								nCntKeyParts++;	//�L�[�p�[�c����+1����
							}
						} while (strcmp(&cData[0], "END_KEYSET") != 0);

						nCntKey++;	//�L�[����+1����
						nCntKeyParts = 0;	//�L�[�p�[�c���̃J�E���g��0�ɂ���
					}
				} while (strcmp(&cData[0], "END_MOTIONSET") != 0);

				nCntMotion++;	//���[�V��������+1����
				nCntKey = 0;	//�L�[���̃J�E���g��0�ɂ���
			}
		} while (strcmp(&cData[0], "END_SCRIPT") != 0);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("\n***�@�t�@�C�����J���܂���ł����@***\n");
	}
}

//---------------------------------------------------
//	�v���C���[�̏���������
//---------------------------------------------------
void InitPlayer(void)
{
	LoadModel();	//���f���̃f�[�^��ǂݍ���

	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�����擾

	//�p�[�c�̊e�l�̏�����
	for (int nCntParts = 0; nCntParts < g_nNumParts; nCntParts++)
	{//	�p�[�c������
		g_Player.aModel[nCntParts].pos = PartsSet[nCntParts].pos;	//�ʒu
		g_Player.aModel[nCntParts].rot = PartsSet[nCntParts].rot;	//�p�x
		g_Player.aModel[nCntParts].nIdxModelParent = PartsSet[nCntParts].nParent;	//�e�p�[�c�ݒ�
	}

	//�v���C���[�̊e�l�̏�����
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���݂̈ʒu
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	g_Player.diff = 0.0f;								//�����v�Z�p
	g_Player.rotDest = 0.0f;							//�ړI�̊p�x
	g_Player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_�̍ŏ��l���擾�p
	g_Player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_�̍ő�l���擾�p
	g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�T�C�Y�ۑ��p
	g_Player.bIsJumping = false;	//�W�����v���Ă��邩�ǂ���
	g_Player.nLife = PLAYER_LIFE;	//�̗�
	g_nSelectMotion = 1;			//���[�V�����ԍ��ݒ�

	g_SetPlayer.pos = D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 50.0f, g_Player.pos.z);
	g_SetPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_SetPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e��ݒ�
	g_Player.IdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.1f, g_Player.pos.z), g_Player.rot, PLAYER_SHADOW);

	//�]�t�@�C���̓ǂݍ���
	for (int nCntParts = 0; nCntParts < g_nNumParts; nCntParts++)
	{
		D3DXLoadMeshFromX(&cModelPas[nCntParts][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntParts].pBuffMat,
			NULL,
			&g_Player.aModel[nCntParts].nNumMat,
			&g_Player.aModel[nCntParts].pMesh);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		g_pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMat->GetBufferPointer();

		//�e�N�X�`���̓ǂݍ���
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			D3DXCreateTextureFromFile(
				pDevice,
				g_pMat[nCntMat].pTextureFilename,
				&g_Player.aModel[nCntParts].pTexturePlayer[nCntMat]);
		}
	}

	//�v���C���[�̒��_�̍ŏ��l�A�ő�l�ݒ�
	g_Player.vtxMin = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
	g_Player.vtxMax = D3DXVECTOR3(20.0f, 110.0f, 20.0f);

	//�v���C���[�̃T�C�Y�ݒ�
	g_Player.size.x = g_Player.vtxMax.x - g_Player.vtxMin.x;
	g_Player.size.y = g_Player.vtxMax.y - g_Player.vtxMin.y;
	g_Player.size.z = g_Player.vtxMax.z - g_Player.vtxMin.z;

	//�v���C���[�̗̑͂����ɃQ�[�W��ݒ�
	SetScoreGage(D3DXVECTOR3(650.0f, SCREEN_HEIGHT - (200.0f / 2.0f), 0.0f), g_Player.nLife);
}

//---------------------------------------------------
//	�v���C���[�̏I������
//---------------------------------------------------
void UninitPlayer(void)
{
	//�v���C���[�̃��b�V���j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		//���f���̃��b�V���j��
		if (g_Player.aModel[nCntParts].pMesh != NULL)
		{
			g_Player.aModel[nCntParts].pMesh->Release();
			g_Player.aModel[nCntParts].pMesh = NULL;
		}

		//�e�N�X�`���j��
		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			if (g_Player.aModel[nCntParts].pTexturePlayer[nCntMat] != NULL)
			{
				g_Player.aModel[nCntParts].pTexturePlayer[nCntMat]->Release();
				g_Player.aModel[nCntParts].pTexturePlayer[nCntMat] = NULL;
			}
		}
	}

	//�v���C���[�̃}�e���A���j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	//���f���̃}�e���A���j��
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].pBuffMat != NULL)
		{
			g_Player.aModel[nCntParts].pBuffMat->Release();
			g_Player.aModel[nCntParts].pBuffMat = NULL;
		}
	}
}

//---------------------------------------------------
//	�v���C���[�̍X�V����
//---------------------------------------------------
void UpdatePlayer(void)
{
	//�d��
	g_Player.move.y -= 0.3f;

	//�v���C���[�̌��݂̈ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	//�p�[�c�̌��݂̈ʒu��ۑ�
	g_SetPlayer.posOld = g_SetPlayer.pos;

	//�p�[�c�̌��݂̈ʒu��ۑ�
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		g_Player.aModel[nCntParts].posOld = g_Player.aModel[nCntParts].pos;
	}

	//�v���C���[�̑���
	ControlPlayer();

	//�p�[�c�̈ړ�
	g_SetPlayer.pos = D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 50.0f, g_Player.pos.z - g_Player.vtxMax.z - 20.0f);

	//�d�͂����Z
	g_Player.pos.y += g_Player.move.y;

	//�v���C���[�ƃ��f���̓����蔻��
	CollisionModel(&g_Player.pos, &g_Player.posOld, g_Player.size, &g_Player.move);

	//�G���U�����Ă����e�̓����蔻��
	CollisionBullet(&g_Player.pos, &g_Player.posOld, g_Player.size);

	//�W�����v�̉�
	g_Player.bIsJumping = !CollisionModel(&g_Player.pos, &g_Player.posOld, g_Player.size, &g_Player.move);

	if (g_Player.pos.y <= 0.0f)
	{//���ɂ���Ƃ�
		g_Player.pos.y = 0.0f;			//�ʒu
		g_Player.move.y = 0.0f;			//�ړ���
		g_Player.bIsJumping = false;	//�W�����v���Ă��邩�ǂ���
	}

	//�ړ��͈͂̐ݒ�
	if ((g_Player.pos.x + (g_Player.size.x / 2.0f)) >= (FIELD_SIZE / 2.0f))
	{//����
		g_Player.pos.x = (FIELD_SIZE / 2.0f) - (g_Player.size.x / 2.0f);
	}
	else if ((g_Player.pos.x - (g_Player.size.x / 2.0f)) <= -(FIELD_SIZE / 2.0f))
	{
		g_Player.pos.x = -(FIELD_SIZE / 2.0f) + (g_Player.size.x / 2.0f);
	}
	if ((g_Player.pos.z + (g_Player.size.z / 2.0f)) >= (FIELD_SIZE / 2.0f))
	{//����
		g_Player.pos.z = (FIELD_SIZE / 2.0f) - (g_Player.size.z / 2.0f);
	}
	else if ((g_Player.pos.z - (g_Player.size.z / 2.0f)) <= -(FIELD_SIZE / 2.0f))
	{
		g_Player.pos.z = -(FIELD_SIZE / 2.0f) + (g_Player.size.z / 2.0f);
	}

	if (g_Player.pos != g_Player.posOld)
	{//�v���C���[���ړ����Ă���ꍇ�A�G�t�F�N�g��t�^
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z),	//�ʒu
			g_Player.rot,						//�p�x
			D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f),	//�J���[
			40,									//����
			D3DXVECTOR3(3.0f, 3.0f, 0.0f));		//�T�C�Y
	}

	//�e�̈ʒu���X�V
	SetPositionShadow(0, D3DXVECTOR3(g_Player.pos.x, 0.1f, g_Player.pos.z));

	MotionPlayer(g_nSelectMotion);		//���[�V�����ݒ�

	g_SetPlayer.rot = g_Player.rot;
	g_SetPlayer.pos.x = sinf(g_SetPlayer.rot.y) * -50.0f;
	g_SetPlayer.pos.z = cosf(g_SetPlayer.rot.y) * -50.0f;

	//�����Ă鎞�̃��[�V�����̐ݒ�
	if (g_nSelectMotion != 0)
	{
		if ((g_Player.pos.x != g_Player.posOld.x || g_Player.pos.z != g_Player.posOld.z) && g_nSelectMotion != 2)
		{//�v���C���[�������Ă��鎞
			SetMotion(2);
		}
		else if (g_Player.pos == g_Player.posOld && g_nSelectMotion == 2)
		{
			SetMotion(1);
		}
	}
}

//---------------------------------------------------
//	�v���C���[�̑���Ɋւ��鏈��
//---------------------------------------------------
void ControlPlayer(void)
{
	//�v���C���[�̈ړ�����
	MovePlayer();

	//�}�E�X�̍��{�^���A�E�{�^�����������Ƃ��A
	if (GetMouseTrigger(MOUSE_INPUT_LEFT) || GetMouseTrigger(MOUSE_INPUT_RIGHT))
	{//�U�������Ƃ�
		SetCollision(D3DXVECTOR3(g_Player.pos.x + g_SetPlayer.pos.x, g_SetPlayer.pos.y, g_Player.pos.z + g_SetPlayer.pos.z), D3DXVECTOR3(g_Player.posOld.x + g_SetPlayer.posOld.x, g_SetPlayer.posOld.y, g_Player.posOld.z + g_SetPlayer.posOld.z), g_SetPlayer.rot);
		SetMotion(0);
	}
}

//---------------------------------------------------
//	�v���C���[�̃��[�V��������
//---------------------------------------------------
void MotionPlayer(int nPlayMotion)
{
	if (nNextKeySet >= MotionSet[nPlayMotion].nNumKey)
	{//�L�[�����I�������
		if (MotionSet[nPlayMotion].nLoop != 1)
		{//���[�v���Ȃ��ݒ�Ȃ�A�ҋ@���[�V������ݒ�
			SetMotion(1);
		}
		return;
	}

	for (int i = 0; i < g_nNumParts; i++)
	{// �p�[�c������
		//�O��̃L�[�Ƃ̊p�x�̍������߂�
		MotionDiff[i].x = (MotionSet[nPlayMotion].KeySet[nNextKeySet].Key[i].rot.x - MotionSet[nPlayMotion].KeySet[nNowKeySet].Key[i].rot.x) / MotionSet[nPlayMotion].KeySet[nNowKeySet].nFrame;
		MotionDiff[i].y = (MotionSet[nPlayMotion].KeySet[nNextKeySet].Key[i].rot.y - MotionSet[nPlayMotion].KeySet[nNowKeySet].Key[i].rot.y) / MotionSet[nPlayMotion].KeySet[nNowKeySet].nFrame;
		MotionDiff[i].z = (MotionSet[nPlayMotion].KeySet[nNextKeySet].Key[i].rot.z - MotionSet[nPlayMotion].KeySet[nNowKeySet].Key[i].rot.z) / MotionSet[nPlayMotion].KeySet[nNowKeySet].nFrame;
		//�Z�o���������v�Z
		g_Player.aModel[i].rot.x += MotionDiff[i].x;
		g_Player.aModel[i].rot.y += MotionDiff[i].y;
		g_Player.aModel[i].rot.z += MotionDiff[i].z;
	}

	if (nNowFrame >= MotionSet[nPlayMotion].KeySet[nNowKeySet].nFrame)
	{// Frame���������
		nNowFrame = 0;		//�t���[������0(�����l)�ɖ߂�
		nNowKeySet++;		//���̃L�[�ɐi��
		nNextKeySet++;		//�Đ����̃L�[�̎��̃L�[�ɐi��
	}

	if (MotionSet[nPlayMotion].nLoop == 1)
	{
		if (nNextKeySet >= MotionSet[nPlayMotion].nNumKey)
		{//���̃L�[�Z�b�g�����ő�L�[���𒴂��Ă�����A0�i�ŏ��̃L�[�j�ɂ���
			nNextKeySet = 0;
		}
		if (nNowKeySet >= MotionSet[nPlayMotion].nNumKey)
		{//���݂̃L�[���S���������
			nNowKeySet = 0;	//�ŏ��̃L�[�ɂ���
			nNextKeySet = nNowKeySet + 1;	//�ŏ��̃L�[�ɂ���
		}
	}

	//�t���[������1�i�߂�
	nNowFrame++;
	nCntFrame++;
}

//---------------------------------------------------
//	�v���C���[�̃��[�V�����I������
//---------------------------------------------------
void SetMotion(int nSet)
{
	//���[�V�����ԍ�����
	g_nSelectMotion = nSet;

	for (int i = 0; i < g_nNumParts; i++)
	{// �p�[�c������
		g_Player.aModel[i].rot.x = 0.0f;
		g_Player.aModel[i].rot.y = 0.0f;
		g_Player.aModel[i].rot.z = 0.0f;
	}

	nNowFrame = 0;		//�t���[������0(�����l)�ɖ߂�
	nNowKeySet = 0;		//���̃L�[�ɐi��
	nNextKeySet = nNowKeySet + 1;	//�Đ����̃L�[�̎��̃L�[�ɐi��
}

//---------------------------------------------------
//	�v���C���[�̈ړ�����
//---------------------------------------------------
void MovePlayer(void)
{
	CAMERA * pCamera = GetCamera();		//�J�����̏��擾

	if (GetKeyboardPress(DIK_W))
	{//���L�[�������ꂽ�Ƃ�
		if (GetKeyboardPress(DIK_D))
		{//���L�[�Ɖ����ꂽ�Ƃ�(���΂ߏ����)
			g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4)) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4)) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 4 * 3.0f);
		}
		else if (GetKeyboardPress(DIK_A))
		{//���L�[�Ɖ����ꂽ�Ƃ�(�E�΂ߏ����)
			g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4)) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4)) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 4 * 3.0f);
		}
		else
		{//���L�[�̂�(������ֈړ�)
			g_Player.pos.x += sinf(pCamera->rot.y) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_S))
	{//���L�[�������ꂽ�Ƃ�
		if (GetKeyboardPress(DIK_D))
		{//���L�[�Ɖ����ꂽ�Ƃ�(���΂߉�����)
			g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;		//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 4);
		}
		else if (GetKeyboardPress(DIK_A))
		{//���L�[�Ɖ����ꂽ�Ƃ�(�E�΂߉�����)
			g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;		//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 4);
		}
		else
		{//���L�[�̂�(�������ֈړ�)
			g_Player.pos.x += sinf(pCamera->rot.y + D3DX_PI) * PLAYER_SPEED;		//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y + D3DX_PI) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_D))
	{//���L�[�������ꂽ�Ƃ�(�E�����ֈړ�)
		g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 2)) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
		g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 2)) * PLAYER_SPEED;
		//�v���C���[�̖ړI�̌�����ݒ�
		g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_A))
	{//���L�[�������ꂽ�Ƃ�(�������ֈړ�)
		g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 2)) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
		g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 2)) * PLAYER_SPEED;
		//�v���C���[�̖ړI�̌�����ݒ�
		g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 2);
	}

	//�W�����v
	if (GetKeyboardTrigger(DIK_SPACE) && !g_Player.bIsJumping)
	{//�G���^�[�L�[�������ꂽ
		g_Player.move.y += PLAYER_JUMP;
	}

	//�p�x�̐��K��
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2;
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}

	//�����̌v�Z
	g_Player.diff = (g_Player.rotDest - g_Player.rot.y);

	//�����̐��K��
	if (g_Player.diff > D3DX_PI)
	{
		g_Player.diff -= D3DX_PI * 2;
	}
	else if (g_Player.diff < -D3DX_PI)
	{
		g_Player.diff += D3DX_PI * 2;
	}

	//�v���C���[�̈ړ�����
	g_Player.rot.y += g_Player.diff * PLAYER_INERTIA;
}

//---------------------------------------------------
//	�v���C���[�̕`�揈��
//---------------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		D3DXMATRIX mtxRotChild, mtxTransChild;	//�v�Z�p�}�g���b�N�X

		D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotChild,
			g_Player.aModel[nCntParts].rot.y, g_Player.aModel[nCntParts].rot.x, g_Player.aModel[nCntParts].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld,
			&g_Player.aModel[nCntParts].mtxWorld, &mtxRotChild);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransChild, g_Player.aModel[nCntParts].pos.x, g_Player.aModel[nCntParts].pos.y, g_Player.aModel[nCntParts].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxTransChild);

		D3DXMATRIX mtxParent;	//�e�̃}�g���N�X����p

		if (g_Player.aModel[nCntParts].nIdxModelParent == -1)
		{
			//�v���C���[�̃}�g���N�X���
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			//�����̐e���f���̃}�g���N�X���
			mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorld;
		}

		//�����̐e���f���}�g���N�X�Ƃ̊|�Z�i�����̃}�g���N�X * �e�̃}�g���N�X = �����̃��[���h�}�g���N�X�j
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld,
			&g_Player.aModel[nCntParts].mtxWorld,		//�����̃}�g���N�X
			&mtxParent);								//�e�̃}�g���N�X

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorld);

		//���݂̃}�e���A���ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		g_pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&g_pMat[nCntMat].MatD3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_Player.aModel[nCntParts].pTexturePlayer[nCntMat]);

			//X�t�@�C���̕`��
			g_Player.aModel[nCntParts].pMesh->DrawSubset(nCntMat);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Player.aModel[nCntParts].pTexturePlayer[nCntMat]);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------------------------------
//	�v���C���[�̏��
//---------------------------------------------------
Player * GetPlayer(void)
{//�v���C���[�̏��𑗂�
	return &g_Player;
}

//---------------------------------------------------
//	�_���[�W���菈��
//---------------------------------------------------
void HitModel(int nDamage)
{
	//�̗͂����炷
	g_Player.nLife -= nDamage;

	HitScoreGage(0, nDamage);

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_SE_K);

	//�^�C���̏������
	int * pTime = GetTime();

	if (g_Player.nLife <= 0)
	{//�̗͂��O�ȉ��ɂȂ�����
		*pTime = 0;
	}
}

//---------------------------------------------------
//	�v���C���[�̓����蔻��
//---------------------------------------------------
bool CollisionPlayer(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
{
	bool bAttack = false;

	for (int nCntModel = 0; nCntModel < MAX_ENEMY; nCntModel++)
	{//�ő僂�f�������m�F
		if (pos->z - (size.z / 2) < g_Player.pos.z + g_Player.vtxMax.z &&
			pos->z + (size.z / 2) > g_Player.pos.z + g_Player.vtxMin.z)
		{// *pos��z���W�����f���ɏd�Ȃ��Ă��鎞
			if (posOld->x + (size.x / 2) <= g_Player.pos.x + g_Player.vtxMin.x &&
				pos->x + (size.x / 2) >= g_Player.pos.x + g_Player.vtxMin.x)
			{//�������烂�f���ɂ߂荞�񂾎�
			 //*pos.x�Ƀ��f����pos.x(����)��ݒ�
				pos->x = g_Player.pos.x + g_Player.vtxMin.x - (size.x / 2);
				bAttack = true;
			}
			else if (posOld->x - (size.x / 2) >= g_Player.pos.x + g_Player.vtxMax.x &&
				pos->x - (size.x / 2) <= g_Player.pos.x + g_Player.vtxMax.x)
			{//�E�����烂�f���ɂ߂荞�񂾎�
			 //*pos.x�Ƀ��f����pos.x(�E��)��ݒ�
				pos->x = g_Player.pos.x + g_Player.vtxMax.x + (size.x / 2);
				bAttack = true;
			}
		}
		if (pos->x - (size.x / 2) < g_Player.pos.x + g_Player.vtxMax.x &&
			pos->x + (size.x / 2) > g_Player.pos.x + g_Player.vtxMin.x)
		{// *pos��x���W�����f���ɏd�Ȃ��Ă��鎞
			if (posOld->z - (size.z / 2) <= g_Player.pos.z + g_Player.vtxMin.z &&
				pos->z + (size.z / 2) > g_Player.pos.z + g_Player.vtxMin.z)
			{//���f���̎�O������߂荞�񂾎�
			 //*pos.z�Ƀ��f����pos.z(��O��)��ݒ�
				pos->z = g_Player.pos.z + g_Player.vtxMin.z - (size.z / 2);
				bAttack = true;
			}
			else if (posOld->z + (size.z / 2) >= g_Player.pos.z + g_Player.vtxMax.z &&
				pos->z - (size.z / 2) < g_Player.pos.z + g_Player.vtxMax.z)
			{//���f���̉�������߂荞�񂾎�
			 //*pos.z�Ƀ��f����pos.z(����)��ݒ�
				pos->z = g_Player.pos.z + g_Player.vtxMax.z + (size.z / 2);
				bAttack = true;
			}
		}
		else
		{
			bAttack = false;
		}
	}

	return bAttack;
}
