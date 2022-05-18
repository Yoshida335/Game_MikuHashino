//----------------------------------------
//�@�v���C���[
//�@Author�F���슲��
//----------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�}�N����`
#define MAX_PLAYER			(1)		//�v���C���[�̍ő吔
#define PLAYER_SPEED		(2.0f)	//�v���C���[�̈ړ����x
#define MAX_PARTS			(12)	//�ő�p�[�c��

//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;			//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//�p�x
	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
	LPDIRECT3DTEXTURE9 pTexturePlayer[10];	//�e�N�X�`���ւ̃|�C���^
}ModelParts;

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 move;		//�ړ���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	float diff;				//�����p
	float rotDest;			//�ړI�̊p�x
	int IdxShadow;			//�e�p
	D3DXVECTOR3 vtxMin;		//���_�̍ŏ��l���擾�p
	D3DXVECTOR3 vtxMax;		//���_�̍ő�l���擾�p
	D3DXVECTOR3 size;		//�T�C�Y�ۑ��p
	ModelParts aModel[MAX_PARTS];	//���f���̏��[�ő�p�[�c����]
	bool bIsJumping;		//�W�����v���Ă��邩�ǂ���
	int nLife;				//�̗�
}Player;

typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
}SetPlayer;

//�v���g�^�C�v�錾
void InitPlayer(void);		//�v���C���[�̏�����
void UninitPlayer(void);	//�v���C���[�̏I��
void UpdatePlayer(void);	//�v���C���[�̍X�V
void DrawPlayer(void);		//�v���C���[�̕`��
void MovePlayer(void);		//�v���C���[�̈ړ�
Player * GetPlayer(void);	//�v���C���[�̏��
void MotionPlayer(int nMotion);		//�v���C���[�̃��[�V�����ݒ�
void SetMotion(int nSet);	//���[�V������ݒ肷��
void HitModel(int nDamage);	//�v���C���[�̍U���q�b�g�������̏���
bool CollisionPlayer(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);	//�v���C���[�ƓG�Ƃ̓����蔻��
void ControlPlayer(void);	//�v���C���[�̑���Ɋւ��鏈��

#endif