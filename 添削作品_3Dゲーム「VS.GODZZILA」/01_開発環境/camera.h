//----------------------------------------
//�@�J����
//�@Author�F���슲��
//----------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�}�N����`
#define CAMERA_SPEED		(1.0f)	//�J�����̈ړ����x

//�J�����̍\����
typedef struct
{
	D3DXVECTOR3 posV;			//���݂̎��_
	D3DXVECTOR3 posVOld;		//�O��̎��_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 rotold;			//����
	D3DXVECTOR3 rotDest;		//�ړI�̌���
	float fDistance;			//���_���璍���_�̋���
	D3DVIEWPORT9 viewport;		//�r���[�|�[�g

	POINT NowPointer;
	POINT CenterPointer;
	POINT MovePointer;
}CAMERA;

//�v���g�^�C�v�錾
void InitCamera(void);			//�J�����̏���������
void UninitCamera(void);		//�J�����̏I������
void UpdateCamera(void);		//�J�����̍X�V����
void MoveCamera(void);			//�J�����̈ړ�����
void SetCamera(int nCnt);		//�J�����̐ݒ�
CAMERA * GetCamera(void);		//�J�����̏��

#endif
