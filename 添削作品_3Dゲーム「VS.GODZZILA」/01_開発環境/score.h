//----------------------------------------
//�@�X�R�A
//�@Author�F���슲��
//----------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

#define MAX_SCORE	(16)	//�X�R�A�̍ő�ݒ萔

//�v���g�^�C�v�錾
void InitScore(void);		//�X�R�A�̏�����
void UninitScore(void);		//�X�R�A�̏I��
void UpdateScore(void);		//�X�R�A�̍X�V
void DrawScore(void);		//�X�R�A�̕`��
void SetScore(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);	//�X�R�A�̐ݒ�

#endif
