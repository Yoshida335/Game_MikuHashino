//----------------------------------------
//�@�}�E�X�̏���
//�@Author�F���슲��
//----------------------------------------
#include "mouse.h"

//�O���[�o���ϐ��錾
POINT g_mouse = {};
POINT g_mouseCenter = {};
HWND g_hWnd;

//---------------------------------------------------
//	�}�E�X�̏�����
//---------------------------------------------------
void InitMouse(HWND hWnd)
{
	ShowCursor(false);	// true�ŃJ�[�\���\���Afalse�Ŕ�\��

	g_hWnd = hWnd;

	RECT rect;

	GetWindowRect(g_hWnd, &rect);

	SetCursorPos(rect.left + SCREEN_WIDTH / 2, rect.top + SCREEN_HEIGHT / 2);
}

//---------------------------------------------------
//	�}�E�X�̏I������
//---------------------------------------------------
void UninitMouse(void)
{

}

//---------------------------------------------------
//	�}�E�X�̍X�V����
//---------------------------------------------------
void UpdateMouse(void)
{
	RECT rect;

	GetWindowRect(g_hWnd, &rect);

	SetCursorPos(rect.left + SCREEN_WIDTH / 2, rect.top + SCREEN_HEIGHT / 2);
}

//---------------------------------------------------
//	�}�E�X�̕`�揈��
//---------------------------------------------------
void DrawMouse(void)
{

}
