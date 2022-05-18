//----------------------------------------
//�@�r��(�j���)
//�@Author�F���슲��
//----------------------------------------
#ifndef _BILL_DELETE_H_
#define _BILL_DELETE_H_

#include "main.h"

//�}�N����`
#define MAX_BILLDELETE			(126)	//�r��(�j���)�̍ő吔

//�r��(�j���)�̎��
typedef enum
{
	TYPE_DELETEBILL_01 = 0,
	TYPE_DELETEBILL_02,
	TYPE_DLETEMAX
}BILLDELETETYPE;

//�r��(�j���)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXCOLOR col;			//�F
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;				//�g���Ă��邩�ǂ���
	BILLDELETETYPE type;	//���
}BillDelete;

//�v���g�^�C�v�錾
void InitBillDelete(void);		//�r��(�j���)�̏�����
void UninitBillDelete(void);	//�r��(�j���)�̏I��
void UpdateBillDelete(void);	//�r��(�j���)�̍X�V
void DrawBillDelete(void);		//�r��(�j���)�̕`��
void SetBillDelete(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�r��(�j���)�̐ݒ�

#endif

