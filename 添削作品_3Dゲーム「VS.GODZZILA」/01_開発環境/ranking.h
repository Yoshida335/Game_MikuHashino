//----------------------------------------
//�@�����L���O���
//�@Author�F���슲��
//----------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//�}�N����`
#define MAX_RANK		(5)	//�����L���O��

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nScore;			//�X�R�A
}RankScore;

//�v���g�^�C�v�錾
void InitRanking(void);		//�����L���O�̏�����
void UninitRanking(void);	//�����L���O�̏I��
void UpdateRanking(void);	//�����L���O�̍X�V
void DrawRanking(void);		//�����L���O�̕`��
void ResetRanking(void);	//�����L���O�̃��Z�b�g
void SetRanking(void);		//�����L���O�̐ݒ�
void SaveRanking(void);		//�����L���O�̃Z�[�u

#endif
