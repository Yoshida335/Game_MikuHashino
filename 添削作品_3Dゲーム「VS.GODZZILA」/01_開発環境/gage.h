//----------------------------------------
//�@���C�t�Q�[�W
//�@Author�F���슲��
//----------------------------------------
#ifndef _GAGE_H_
#define _GAGE_H_

#include "main.h"

//�}�N����`
#define MAX_GAGE	(256)	//���C�t�Q�[�W�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXCOLOR col;				//�J���[
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nLife;					//����
	int nMaxLife;				//�ő����
}Gage;

//�v���g�^�C�v�錾
void InitGage(void);				//���C�t�Q�[�W�̏���������
void UninitGage(void);				//���C�t�Q�[�W�̏I������
void UpdateGage(void);				//���C�t�Q�[�W�̍X�V����
void DrawGage(void);				//���C�t�Q�[�W�̕`�揈��
void SetGage(D3DXVECTOR3 pos, int nLife);	//���C�t�Q�[�W�̐ݒ�
void HitGage(int nCntGage, int nDamage);	//���C�t�Q�[�W�̃q�b�g����

#endif


