//----------------------------------------
//�@�^�C��
//�@Author�F���슲��
//----------------------------------------
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	TIME_ON = 0,	//�^�C����
	TIME_OFF,		//�^�C���I��
	TIME_MAX
}TIME;

//�v���g�^�C�v�錾
void InitTime(void);		//�^�C���̏�����
void UninitTime(void);		//�^�C���̏I��
void UpdateTime(void);		//�^�C���̍X�V
void DrawTime(void);		//�^�C���̕`��
int * GetTime(void);		//�^�C���̏��
void AddTime(int nTime);	//�^�C���̉��Z

#endif

