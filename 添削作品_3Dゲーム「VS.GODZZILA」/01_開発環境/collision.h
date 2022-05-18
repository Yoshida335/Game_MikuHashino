//----------------------------------------
//�@�����蔻��
//�@Author�F���슲��
//----------------------------------------
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

//�}�N����`
#define MAX_COLLISION	(256)	//�����蔻��̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nLife;					//����
	D3DXVECTOR3 size;			//
}COLLISION;

//�v���g�^�C�v�錾
void InitCollision(void);		//�����蔻��̏���������
void UninitCollision(void);		//�����蔻��̏I������
void UpdateCollision(void);		//�����蔻��̍X�V����
void DrawCollision(void);		//�����蔻��̕`�揈��
void SetCollision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 rot);	//�����蔻��̕`�揈��

#endif
