//----------------------------------------
//�@�L�[�{�[�h�̓���
//�@Author�F���슲��
//----------------------------------------
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX		(256)	//�L�[�̍ő吔
#define MOUSE_KEY_MAX	(8)		//�L�[�̍ő吔�i�}�E�X�j

//----------------------------------------
//	�O���[�o���ϐ��錾
//----------------------------------------
//�L�[�{�[�h
LPDIRECTINPUT8 g_pInput = NULL;					//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
//�}�E�X
LPDIRECTINPUT8 g_pMouseInput = NULL;			//Directinut�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;		//���͂Ńp�X�ւ̃|�C���^
DIMOUSESTATE2 g_aKeyStateMouse;					//�}�E�X�̃v���X����
DIMOUSESTATE2 g_aKeyStatetriggerMouse;			//�}�E�X�̃g���K�[����
POINT g_MousePos;								//�}�E�X�̃J�[�\���p
HWND g_hMouseWnd;								//�E�B���h�E�n���h��

//----------------------------------------
//�@�L�[�{�[�h�̏���������
//----------------------------------------
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,
		&g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//----------------------------------------
//�@�L�[�{�[�h�̏I������
//----------------------------------------
void UninitKeyboard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//----------------------------------------
//�@�L�[�{�[�h�̍X�V����
//----------------------------------------
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//�L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyStateTrigger[nCntKey] = (aKeyState[nCntKey] ^ g_aKeyState[nCntKey]) & aKeyState[nCntKey];
		
			//�L�[�{�[�h�̃v���X����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//----------------------------------------
//�@�L�[�{�[�h�̃v���X�����擾
//----------------------------------------
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//----------------------------------------
//�@�L�[�{�[�h�̃g���K�[�����擾
//----------------------------------------
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//----------------------------------------
//	�}�E�X�̏�����
//----------------------------------------
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pMouseInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�i�}�E�X�j�̐���
	if (FAILED(g_pMouseInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�E�B���h�E�n���h���̕ۊ�
	g_hMouseWnd = hWnd;

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevMouse->Acquire();

	return S_OK;
}

//----------------------------------------
//	�}�E�X�̏I������
//----------------------------------------
void UninitInputMouse(void)
{
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse = NULL;
	}
}

//----------------------------------------
//	�}�E�X�̍X�V����
//----------------------------------------
void UpdateInputMouse(void)
{
	DIMOUSESTATE2 aKeyState;	//�}�E�X�̓��͏��

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{

		for (int nCntKey = 0; nCntKey < MOUSE_KEY_MAX; nCntKey++)
		{
			g_aKeyStatetriggerMouse.rgbButtons[nCntKey]
				= (g_aKeyStateMouse.rgbButtons[nCntKey]
					^ aKeyState.rgbButtons[nCntKey])
				& aKeyState.rgbButtons[nCntKey]; //�L�[�{�[�h�̃g���K�[����ۑ�
		}

		g_aKeyStateMouse = aKeyState;		//�}�E�X�̃v���X����ۑ�

	}
	else
	{
		g_pDevMouse->Acquire();			//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//----------------------------------------
//	�}�E�X�̃v���X����
//----------------------------------------
bool GetMousePress(MOUSE mouse)
{
	return (g_aKeyStateMouse.rgbButtons[mouse] & 0x80) ? true : false;
}

//----------------------------------------
//	�}�E�X�̃g���K�[����
//----------------------------------------
bool GetMouseTrigger(MOUSE mouse)
{
	return (g_aKeyStatetriggerMouse.rgbButtons[mouse] & 0x80) ? true : false;
}
