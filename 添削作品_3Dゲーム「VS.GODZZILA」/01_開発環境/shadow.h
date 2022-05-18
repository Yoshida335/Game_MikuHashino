//----------------------------------------
//�@�e
//�@Author�F���슲��
//----------------------------------------
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//�}�N����`
#define MAX_SHADOW		(256)	//�e�̍ő吔

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//�p�x
	float size;				//�T�C�Y
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	bool bUse;				//�g���Ă��邩�ǂ���
}Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);		//�e�̏�����
void UninitShadow(void);	//�e�̏I��
void UpdateShadow(void);	//�e�̍X�V
void DrawShadow(void);		//�e�̕`��
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float size);	//�e�̐ݒ�
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);						//�e�̈ʒu�ݒ�

#endif
