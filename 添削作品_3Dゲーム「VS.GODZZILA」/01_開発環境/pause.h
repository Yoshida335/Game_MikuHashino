//----------------------------------------
//�@�|�[�Y���
//�@Author�F���슲��
//----------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//�|�[�Y�̏��
typedef enum
{
	SELECT_OFF = 0,
	SELECT_ON,
	SELECT_MAX
}PauseState;

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	PauseState state;		//���
}PAUSE;

//�v���g�^�C�v�錾
void InitPause(void);		//�|�[�Y�̏���������
void UninitPause(void);		//�|�[�Y�̏I������
void UpdatePause(void);		//�|�[�Y�̍X�V����
void DrawPause(void);		//�|�[�Y�̕`�揈��

#endif


