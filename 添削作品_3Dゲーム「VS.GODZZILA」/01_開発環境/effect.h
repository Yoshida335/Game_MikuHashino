//----------------------------------------
//�@�G�t�F�N�g
//�@Author�F���슲��
//----------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�}�N����`
#define MAX_EFFECT	(1000)	//�G�t�F�N�g�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//�p�x
	D3DXCOLOR col;			//�J���[
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	D3DXVECTOR3 size;		//�T�C�Y
	bool bUse;				//�g���Ă��邩�ǂ���
	int nLife;				//����
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);			//�G�t�F�N�g�̏�����
void UninitEffect(void);		//�G�t�F�N�g�̏I��
void UpdateEffect(void);		//�G�t�F�N�g�̍X�V
void DrawEffect(void);			//�G�t�F�N�g�̕`��
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size);	//�G�t�F�N�g�̐ݒ�

#endif
