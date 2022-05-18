//----------------------------------------
//�@���C���̏���
//�@Author�F���슲��
//----------------------------------------
#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "score.h"
#include "ranking.h"
#include "resultscore.h"
#include "mouse.h"
#include "rule.h"

//�}�N����`
#define CLASS_NAME			"WindowsClass"		//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME			"VS.GODZZILA"		//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Updata(void);
void Draw(void);
void DrawFPS(void);

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;						//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;
int g_nCntFPS = 0;
bool g_Meshfield = false;
MODE g_mode = MODE_TITLE;

//----------------------------------------
//�@���C���֐�
//----------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),							//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,									//�E�B���h�E�̃X�^�C��
		WindowProc,									//�E�B���h�E�v���V�[�W��
		0,											//0�ɂ���i�ʏ�͎g�p���Ȃ��j
		0,
		hInstance,									//�C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),			//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),				//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),					//�N���C�A���g�̈�̔w�i�F
		NULL,										//���j���[�o�[
		CLASS_NAME,									//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)				//�t�@�C���̃A�C�R��
	};

	MSG msg;		//���b�Z�[�W���i�[����ϐ�
	HWND hWnd;		//�E�B���h�E�n���h��(���ʎq)
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	//��ʃT�C�Y�̍\����
	
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		//�g���E�B���h�E�X�^�C��
		CLASS_NAME,					//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�B���h�E�̍���w���W
		CW_USEDEFAULT,			//�E�B���h�E�̍���x���W
		(rect.right - rect.left),	//�E�B���h�E�̕�
		(rect.bottom - rect.top),	//�E�B���h�E�̍���
		NULL,						//�e�E�B���h�E�̃n���h��
		NULL,						//���j���[�n���h���܂��́A�q�E�B���h�EID
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�B���h�E�쐬�f�[�^

	DWORD dwCurrentTime;				//���ݎ���
	DWORD dwExecLastTime;				//�Ō�ɏ�����������
	DWORD dwFrameCount;					//�t���[���J�E���g
	DWORD dwFPSLastTime;				//�Ō�Ɍv����������

	//�������ݒ�
	if (FAILED(Init(hInstance, hWnd, true)))	// false�őS��ʕ\��
	{//�����������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;					//����������
	dwExecLastTime = timeGetTime();		//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);			//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);					//�N���C�A���g�̈���X�V

	//���b�Z�[�W�����[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Window�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�������b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);		//�E�B���h�E�v���V�[�W�����b�Z�[�W��n�o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();	//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
			 //FPS���v��
				g_nCntFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;			//FPS���v������������ۑ�
				dwFrameCount = 0;						//�t���[���J�E���g�N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Updata();

				//�`�揈��
				Draw();

				dwFrameCount++;				//�t���[���J�E���g���Z
			}
		}
	}

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//----------------------------------------
//�@�E�B���h�E�v���V�[�W��
//----------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;		//�Ԃ�l���i�[
	//HDC hDC;		//�f�o�C�X�R���e�L�X�g(GDI�I�u�W�F�N�g)�̃n���h��

	switch (uMsg)
	{
	case WM_DESTROY:	//�E�B���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);

		break;

	case WM_KEYDOWN:	//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		//�yESC�z�L�[�������ꂽ�Ƃ�
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY ���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	
	case WM_CLOSE:		//����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�B���h�E��j������(WM_DESTROY ���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	//�O��Ԃ��Ȃ��ƏI������
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//����̏������J��Ԃ�
}

//----------------------------------------
//  ����������
//----------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;				//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;		//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));			//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//�Q�[����ʂ̃T�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//�Q�[����ʂ̃T�C�Y(��)
	d3dpp.BackBufferFormat = d3ddm.Format;		//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;					//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;		//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;					//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈�����n�[�h�E�F�A�A���_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�J�����O���[�h�����߂Ă���	(�J�����O�ɂ��Ă̐ݒ�, �ǂ̃��[�h�ɂ��邩)���ƁH�F��
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//���l(�����x)�ɂ��Ă̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//������Z
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//���𔽓]�������̂���Z

	
	g_pD3DDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0);

	//�J�������猩�āA(Z�o�b�t�@�l��������)�������㏑���B(TRUE�̎�)
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	// Z�o�b�t�@�̒l�Ɋւ�炸�A�K���㏑������B

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitMouse(hInstance, hWnd);

	InitMouse(hWnd);

	//�����L���O�̏�����
	ResetRanking();

	//�T�E���h�̏�����
	InitSound(hWnd);

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	return S_OK;
}

//----------------------------------------
//  �I������
//----------------------------------------
void Uninit(void)
{
	//�^�C�g����ʂ̏I������
	UninitTitle();

	//�^�C�g����ʂ̏I������
	UninitMouse();

	//�Q�[����ʂ̏I������
	UninitGame();

	//���U���g��ʂ̏I������
	UninitResult();

	//�X�R�A�̏I������
	UninitScore();

	//�X�R�A�̏I������
	UninitResultScore();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�T�E���h�̏I���ݒ�
	UninitSound();

	//�t�F�[�h�̏I������
	UninitFade();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�}�E�X�̏I������
	UninitInputMouse();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//----------------------------------------
//  �X�V����
//----------------------------------------
void Updata(void)
{
	//���C���[�t���[���ɂ���
	if (GetKeyboardTrigger(DIK_F2) == true)
	{
		g_Meshfield = g_Meshfield ? false : true;
	}

	if (g_Meshfield == true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else if (g_Meshfield != true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	g_pD3DDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0);

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�}�E�X�̍X�V����
	UpdateInputMouse();

	//�}�E�X�̍X�V����
	if (g_mode != MODE_GAME)
	{
		UpdateMouse();
	}

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_RULE:
		UpdateRule();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_RANKING:
		UpdateRanking();
		break;

	case MODE_RESULT:
		UpdateScore();
		UpdateResultScore();
		UpdateResult();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//----------------------------------------
//  �`�揈��
//----------------------------------------
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		switch (g_mode)
		{
		case MODE_TITLE:	//�^�C�g�����
			DrawTitle();
			break;

		case MODE_RULE:		//���[�����
			DrawRule();
			break;

		case MODE_GAME:		//�Q�[�����
			DrawGame();
			break;

		case MODE_RESULT:	//���U���g���
			DrawResult();
			DrawScore();
			DrawResultScore();
			break;

		case MODE_RANKING:	//�����L���O���
			DrawRanking();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//----------------------------------------
//	�f�o�C�X�̎擾
//----------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//----------------------------------------
//	���[�h�I��
//----------------------------------------
void SetMode(MODE mode)
{
	//���݂̉��(���[�h)�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		UninitTitle();
		break;

	case MODE_RULE:		//���[�����
		UninitRule();
		break;

	case MODE_GAME:		//�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT:	//���U���g���
		UninitScore();
		UninitResultScore();
		UninitResult();
		break;

	case MODE_RANKING:	//�����L���O���
		UninitRanking();
		break;
	}

	//�V�������(���[�h)�̏���������
	switch (mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		InitTitle();
		break;

	case MODE_RULE:		//���[�����
		InitRule();
		break;

	case MODE_GAME:		//�Q�[�����
		InitGame();
		break;

	case MODE_RESULT:	//���U���g���
		InitScore();
		InitResultScore();
		InitResult();
		break;

	case MODE_RANKING:	//�����L���O���
		InitRanking();
		break;
	}

	g_mode = mode;
}

//----------------------------------------
//	���[�h�̏��
//----------------------------------------
MODE GetMode(void)
{
	return g_mode;
}

//----------------------------------------
//	FPS�̕\��
//----------------------------------------
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCntFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
