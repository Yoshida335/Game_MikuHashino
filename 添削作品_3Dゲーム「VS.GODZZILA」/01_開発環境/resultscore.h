//----------------------------------------
//�@���U���g�X�R�A
//�@Author�F���슲��
//----------------------------------------
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_

#include "main.h"

#define MAX_RESULTSCORE	(16)	//�X�R�A�̍ő�ݒ萔

//�v���g�^�C�v�錾
void InitResultScore(void);		//���U���g�X�R�A�̏�����
void UninitResultScore(void);	//���U���g�X�R�A�̏I��
void UpdateResultScore(void);	//���U���g�X�R�A�̍X�V
void DrawResultScore(void);		//���U���g�X�R�A�̕`��
void SetResultScore(int nResultScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);	//���U���g�X�R�A�̐ݒ�

#endif