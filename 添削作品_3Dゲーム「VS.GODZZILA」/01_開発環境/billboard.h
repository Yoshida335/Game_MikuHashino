//----------------------------------------
//�@�r���{�[�h
//�@Author�F���슲��
//----------------------------------------
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//�}�N����`
#define MAX_BILLBOARD	(256)	//�r���{�[�h�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXCOLOR col;				//�J���[
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int nIdxShadow;				//�e�p
	bool bUse;					//�g�p���Ă��邩�ǂ���
}Billboard;

//�v���g�^�C�v�錾
void InitBillboard(void);				//�r���{�[�h�̏���������
void UninitBillboard(void);				//�r���{�[�h�̏I������
void UpdateBillboard(void);				//�r���{�[�h�̍X�V����
void DrawBillboard(void);				//�r���{�[�h�̕`�揈��
void SetBillboard(D3DXVECTOR3 pos);		//�r���{�[�h�̐ݒ�

#endif