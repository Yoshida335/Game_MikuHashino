//----------------------------------------
//�@�}�b�v
//�@Author�F���슲��
//----------------------------------------
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

//�}�N����`
#define FIELD_SIZE	(600.0f)

typedef struct
{
	D3DXVECTOR3 Setpos[10];
}SetPos;

void SetMap(void);	//�}�b�v�̐ݒ�
SetPos * GetSetPos(void);	//�G�̐ݒ�ʒu�̏��

#endif

