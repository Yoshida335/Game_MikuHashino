//----------------------------------------
//�@�p�[�e�B�N��
//�@Author�F���슲��
//----------------------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�}�N����`
#define MAX_PARTICLE	(256)	//�p�[�e�B�N���ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//�p�x
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�J���[
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	D3DXVECTOR3 size;		//�T�C�Y
	bool bUse;				//�g���Ă��邩�ǂ���
	int nLife;				//����
}Particle;

//�v���g�^�C�v�錾
void InitParticle(void);	//�p�[�e�B�N��������
void UninitParticle(void);	//�p�[�e�B�N���I��
void UpdateParticle(void);	//�p�[�e�B�N���X�V
void DrawParticle(void);	//�p�[�e�B�N���`��
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nLife, D3DXVECTOR3 size);		//�p�[�e�B�N���̐ݒ�

#endif


