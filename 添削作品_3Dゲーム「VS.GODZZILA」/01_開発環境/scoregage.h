//----------------------------------------
//�@�X�R�A�Q�[�W
//�@Author�F���슲��
//----------------------------------------
#ifndef _SCOREGAGE_H_
#define _SCOREGAGE_H_

#include "main.h"

//�}�N����`
#define MAX_SCOREGAGE	(256)	//�X�R�A�Q�[�W�̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�J���[
	bool bUse;			//�g�p���Ă��邩�ǂ���
	int nLife;			//����
	int nMaxLife;		//�ő����
}ScoreGage;

//�v���g�^�C�v�錾
void InitScoreGage(void);		//�X�R�A�Q�[�W�̏���������
void UninitScoreGage(void);		//�X�R�A�Q�[�W�̏I������
void UpdateScoreGage(void);		//�X�R�A�Q�[�W�̍X�V����
void DrawScoreGage(void);		//�X�R�A�Q�[�W�̕`�揈��
void SetScoreGage(D3DXVECTOR3 pos, int nLife);		//�X�R�A�Q�[�W�̐ݒ�
void HitScoreGage(int nCntScoreGage, int nDamage);	//�X�R�A�̃Q�[�W�����鏈��

#endif

