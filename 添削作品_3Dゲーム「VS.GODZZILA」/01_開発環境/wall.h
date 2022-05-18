//----------------------------------------
//�@��
//�@Author�F���슲��
//----------------------------------------
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//�}�N����`
#define MAX_WALL	(256)		//�ǂ̍ő吔
#define WALL_X		(300.0f)	// x�����ւ̒l	����
#define WALL_Y		(140.0f)	// y�����ւ̒l	����
#define WALL_Z		(0.0f)		// z�����ւ̒l	�c��

//�e�N�X�`���̎��
typedef enum
{
	TYPE_WARKING = 0,	//�댯�e�N�X�`��
	TYPE_BILL,			//�r���e�N�X�`��
	MAX_TYPE
}WALLTYPE;

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//�p�x
	D3DXVECTOR3 size;		//�T�C�Y
	D3DXCOLOR col;			//�J���[
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	bool bUse;				//�g���Ă��邩�ǂ���
	WALLTYPE type;			//���
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);	//�ǂ̏�����
void UninitWall(void);	//�ǂ̏I��
void UpdateWall(void);	//�ǂ̍X�V
void DrawWall(void);	//�ǂ̕`��
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 size, WALLTYPE type);	//�ǂ̐ݒ�
Wall * GetWall(void);	//�ǂ̏��

#endif

