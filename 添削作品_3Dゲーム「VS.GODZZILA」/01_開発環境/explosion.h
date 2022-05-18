//----------------------------------------
//�@����
//�@Author�F���슲��
//----------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//�}�N����`
#define MAX_EXPLOSION	(256)	//�����̍ő吔

//�����̍\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXCOLOR col;				//�J���[
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nCntAnim;				//�A�j���[�V�����J�E���^�[
	int nPatternAnim;			//�A�j���[�V�����p�^�[��No.
}Explosion;

//�v���g�^�C�v�錾
void InitExplosion(void);				//�����̏���������
void UninitExplosion(void);				//�����̏I������
void UpdateExplosion(void);				//�����̍X�V����
void DrawExplosion(void);				//�����̕`�揈��
void SetExplosion(D3DXVECTOR3 pos);		//�����̐ݒ�

#endif
