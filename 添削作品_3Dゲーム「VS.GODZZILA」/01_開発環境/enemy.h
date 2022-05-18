//----------------------------------------
//�@�G
//�@Author�F���슲��
//----------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//�}�N����`
#define MAX_ENEMY			(126)	//�G�̍ő吔
#define ENEMY_SPEED			(1.0f)	//�G�̈ړ����x

//�G�̎��
typedef enum
{
	TYPE_ENEMY_01 = 0,
	TYPE_ENEMY_MAX
}ENEMYTYPE;

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 diff;		//�����p
	D3DXVECTOR3 rotDest;	//�ړI�̊p�x
	int IdxShadow;			//�e�p
	bool bUse;				//�g���Ă��邩�ǂ���
	D3DXVECTOR3 vtxMin;		//���_�̍ŏ��l���擾�p
	D3DXVECTOR3 vtxMax;		//���_�̍ő�l���擾�p
	ENEMYTYPE nType;		//�G�̎��
	int nLife;				//�̗�
	D3DXVECTOR3 posdis;		//�v���C���[�Ƃ̍������߂�
	D3DXVECTOR3 size;		//�T�C�Y�ۑ�
	bool bAttack;
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);		//�G�̏�����
void UninitEnemy(void);		//�G�̏I��
void UpdateEnemy(void);		//�G�̍X�V
void DrawEnemy(void);		//�G�̕`��
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int life);		//�G�̐ݒ�
void CollisionEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);	//�G�̓����蔻��
void HitEnemyl(int nCntModel, int nDamage);	//�G�ɍU����������������

#endif

