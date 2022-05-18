//----------------------------------------
//�@�r��
//�@Author�F���슲��
//----------------------------------------
#ifndef _BILL_H_
#define _BILL_H_

#include "main.h"

//�}�N����`
#define MAX_MODEL			(126)	//�r���̍ő吔
#define MODEL_SPEED			(1.0f)	//�r���̈ړ����x

//�r���̎��
typedef enum
{
	TYPE_BILL_01 = 0,
	TYPE_BILL_02,
	TYPE_MAX
}MODELTYPE;

//�r���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXCOLOR col;			//�F
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	float diff;				//�����p
	float rotDestModel;		//�ړI�̊p�x
	int IdxShadow;			//�e�p
	bool bUse;				//�g���Ă��邩�ǂ���
	D3DXVECTOR3 vtxMin;		//���_�̍ŏ��l���擾�p
	D3DXVECTOR3 vtxMax;		//���_�̍ő�l���擾�p
	MODELTYPE nType;		//�r���̎��
	int nLife;				//�̗�
	bool bHit;				//�U�����������Ă��邩�ǂ���
	int nCntTime;
}Model;

typedef struct
{
	float nModelP;		//�r���̔j��󋵂��p�[�Z���g�Ŕc������悤
	float nMaxLife;		//bUse��true�ɂȂ��Ă���r���́A���v�̗͐�
	float nMax;			//bUse��true�ɂȂ��Ă���r���́A���v��
}Parcent;

//�v���g�^�C�v�錾
void InitModel(void);		//�r���̏�����
void UninitModel(void);		//�r���̏I��
void UpdateModel(void);		//�r���̍X�V
void DrawModel(void);		//�r���̕`��
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE type, int life);		//�r���̐ݒ�
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size, D3DXVECTOR3 *move);	//�r���̓����蔻��
void CollisionAttack(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);	//�r���̓����蔻��
void HitModel(int nCntModel, int nDamage);	//�r���ɍU���������������̏���
Parcent * GetModeParcent(void);	//�j��󋵂̏��
void SaveParcent(void);			//�p�[�Z���g�ۑ�
void LoadP(void);				//�p�[�Z���g�ǂݍ���

#endif
