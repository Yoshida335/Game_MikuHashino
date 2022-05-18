//----------------------------------------
//�@���C�g�̏���
//�@Author�F���슲��
//----------------------------------------
#include "light.h"
#include "input.h"

//�O���[�o���ϐ��錾
D3DLIGHT9 g_alight[MAX_LIGHT];

//---------------------------------------------------
//	���C�g�̏�����
//---------------------------------------------------
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 verDir;		//���C�g�̕����x�N�g��

	//���C�g���N���A����
	ZeroMemory(&g_alight[0], sizeof(g_alight));

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̎�ނ�ݒ�
		g_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;					//���s����

		//���C�g�̊g�U����ݒ�
		g_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//���C�g�̐F
	}

	//���C�g�@�̕�����ݒ�--------------------------
	verDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	//���K������
	D3DXVec3Normalize(&verDir, &verDir);
	g_alight[0].Direction = verDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_alight[0]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	//���C�g�A�̕�����ݒ�--------------------------
	verDir = D3DXVECTOR3(-1.0f, 1.2f, 0.4f);

	//���K������
	D3DXVec3Normalize(&verDir, &verDir);
	g_alight[1].Direction = verDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(1, &g_alight[1]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);

	//���C�g�B�̕�����ݒ�--------------------------
	verDir = D3DXVECTOR3(0.8f, -0.8f, 1.0f);

	//���K������
	D3DXVec3Normalize(&verDir, &verDir);
	g_alight[2].Direction = verDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(2, &g_alight[2]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(2, TRUE);
}

//---------------------------------------------------
//	���C�g�̏I������
//---------------------------------------------------
void UninitLight(void)
{
	
}

//---------------------------------------------------
//	���C�g�̍X�V����
//---------------------------------------------------
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���C�g�@�̐F���ς��
	if (GetKeyboardPress(DIK_L) == true)
	{//���L�[�������ꂽ
		if (g_alight[0].Diffuse.r <= 1.0f)
		{
			g_alight[0].Diffuse.r += 0.01f;
		}
		else
		{
			g_alight[0].Diffuse.r = 0.0f;
		}
	}
	else if (GetKeyboardPress(DIK_P) == true)
	{//���L�[�������ꂽ
		if (g_alight[0].Diffuse.r >= 0.0f)
		{
			g_alight[0].Diffuse.r -= 0.01f;
		}
		else
		{
			g_alight[0].Diffuse.r = 1.0f;
		}
	}
	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_alight[0]);
}

