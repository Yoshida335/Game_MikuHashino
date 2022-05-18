//----------------------------------------
//�@���U���g���
//�@Author�F���슲��
//----------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

typedef enum
{
	SignType_01 = 0,	//*
	SignType_02,		//=
	SignType_03,		//+
	SignType_04,		//-
	SignType_05,		//%
	SignType_06,		//.
	SignType_MAX
}SignType;

//�v���g�^�C�v�錾
void InitResult(void);		//���U���g��ʂ̏�����
void UninitResult(void);	//���U���g��ʂ̏I��
void UpdateResult(void);	//���U���g��ʂ̍X�V
void DrawResult(void);		//���U���g��ʂ̕`��
void SetResult(int nScore, D3DXVECTOR3 pos, D3DXVECTOR3 size);		//���U���g�̐ݒ�
void SetSign(D3DXVECTOR3 pos, D3DXVECTOR3 size, SignType type);		//�L���̐ݒ�
int GetResultScore(void);	//���U���g��ʂ̃X�R�A���

#endif
