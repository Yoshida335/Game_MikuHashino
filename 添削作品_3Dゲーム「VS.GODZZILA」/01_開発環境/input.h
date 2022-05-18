//----------------------------------------
//�@���͏��
//�@Author�F���슲��
//----------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//�L�[���(�}�E�X)
typedef enum
{
	MOUSE_INPUT_LEFT,			//�}�E�X���{�^��
	MOUSE_INPUT_RIGHT,			//�}�E�X�E�{�^��
	MOUSE_INPUT_MIDDLE,			//�}�E�X�����{�^��
	MOUSE_INPUT_4,				//�}�E�X�{�^��4
	MOUSE_INPUT_5,				//�}�E�X�{�^��5
	MOUSE_INPUT_6,				//�}�E�X�{�^��6
	MOUSE_INPUT_7,				//�}�E�X�{�^��7
	MOUSE_INPUT_8,				//�}�E�X�{�^��8
}MOUSE;

#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//�L�[�{�[�h�̏�����
void UninitKeyboard(void);				//�L�[�{�[�h�̏I��
void UpdateKeyboard(void);				//�L�[�{�[�h�̍X�V
bool GetKeyboardPress(int nKey);		//�L�[�{�[�h�̃v���X���
bool GetKeyboardTrigger(int nKey);		//�L�[�{�[�h�̃g���K�[���

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);		//�}�E�X�̏�����
void UninitInputMouse(void);		//�}�E�X�̏I������
void UpdateInputMouse(void);		//�}�E�X�̍X�V����
bool GetMousePress(MOUSE mouse);	//�}�E�X�̃v���X���
bool GetMouseTrigger(MOUSE mouse);	//�}�E�X�̃g���K�[���

#endif