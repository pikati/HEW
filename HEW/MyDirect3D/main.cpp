/*��ʂ̕��ƍ����}�N��*/
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "MyDirect3D.h"
#include "XManager.h"
#include "SceneManager.h"
#include <string.h>
#pragma comment(lib,"winmm.lib")

static LPDIRECT3DDEVICE9	g_d3dDevice = NULL;
static HWND					g_hWnd = NULL;
static HINSTANCE			g_hInstance;
static LPDIRECT3D9			g_pD3D = NULL;
static LPD3DXFONT			g_pFont = NULL;//�t�H���g
//
//DWORD dwNumMaterials = 0;
//
////�e�L�X�g�`��
//void TextDraw(LPD3DXFONT pFont, char* text, int X, int Y)
//{
//	RECT rect = { X,Y,0,0 };//�`��ʒu
//	//�X�v���C�g�|�C���^(�����Ă��ǂ�),�`�敶��,������(-1�őS��),�`��͈�,�t�H�[�}�b�g,�F
//	pFont->DrawText(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
//}
//
//
////Direct3D������
HRESULT InitD3D(HWND hWnd)
{
	//Direct3D�𐶐�����
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) { return E_FAIL; }

	//�f�o�C�X�����p�̃p�����[�^�[
	D3DPRESENT_PARAMETERS d3dpp;//�p�����[�^�[�\����
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�[���ŏ�����
	d3dpp.Windowed = TRUE;//�E�C���h�E���[�h�ŋN��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�o�b�N�o�b�t�@�̃X���b�v�G�t�F�N�g Direct3D�ɃX���b�v�G�t�F�N�g���܂�����
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//�o�b�N�o�b�t�@�̃t�H�[�}�b�g���\������Ă��郂�j�^�̐ݒ�Ɠ���
	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@�̐�
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;//�}���`�T���v�����O�͍s��Ȃ�
	d3dpp.MultiSampleQuality = 0;//�}���`�T���v�����O�͍s��Ȃ��̂�0
	d3dpp.EnableAutoDepthStencil = TRUE;//Direct3D�ɐ[�x�o�b�t�@�̊Ǘ����܂�����
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�[�x�o�b�t�@�̃t�H�[�}�b�g�i�ʏ�͂��̒l�Ŗ��Ȃ��j
	d3dpp.hDeviceWindow = hWnd;//�J�o�[�E�B���h�E���A�v���P�[�V�����̃E�B���h�E
	d3dpp.Flags = 0;//�t���O�͎g��Ȃ�
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���̃��t���b�V�����[�g�����̂܂܎g��
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//���j�^�̐�����A��҂�

	//Direct3D�f�o�C�X�̐��� HAL(�n�[�h�E�F�A�A�N�Z�����[�V����)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_d3dDevice))) {
		//HAL���ʖڂȂ�HEL(�\�t�g�E�F�A�G�~�����[�V����)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_d3dDevice))) {
			//�ʖڂȂ�I��
			return(E_FAIL);
		}
	}

	//�t�H���g�̐��� MS�S�V�b�N
   //�f�o�C�X,��������,������,�t�H���g�X�^�C��,�~�b�v�}�b�v�̃��x��,�Α̂ɂ��邩�ǂ���,�����Z�b�g,�o�͐��x,�o�͕i��,�t�H���g�s�b�`�ƃt�@�~��,�t�H���g��,�t�H���g�|�C���^
	HRESULT hr = D3DXCreateFont(g_d3dDevice, 20, 0, FW_HEAVY, 1, false, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "�l�r �S�V�b�N", &g_pFont);
	if FAILED(hr) { return(E_FAIL); }


	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = D3DXVECTOR3(-1, 0, -1);


	// Z�o�b�t�@�[������L���ɂ���
	g_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// ���C�g��L���ɂ���
	g_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �A���r�G���g���C�g�i�����j��ݒ肷��
	g_d3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00111111);
	// �X�y�L�����i���ʔ��ˁj��L���ɂ���
	//g_d3dDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	g_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
	return S_OK;
}

//�I�����������
VOID Cleanup()
{
	SAFE_RELEASE(g_pFont);
	SAFE_RELEASE(g_d3dDevice);
	SAFE_RELEASE(g_pD3D);
}

//���b�Z�[�W�v���V�[�W��
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

//���C���֐�
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	g_hInstance = hInst;
	MSG msg;
	//�E�C���h�E�N���X�̓o�^
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
					  GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
					  "Window1", NULL };
	RegisterClassEx(&wc);

	//�^�C�g���o�[�ƃE�C���h�E�g�̕����܂߂ăE�C���h�E�T�C�Y��ݒ�
	RECT rect;
	SetRect(&rect, 0, 0, 1280, 720);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	rect.right = rect.right - rect.left;
	rect.bottom = rect.bottom - rect.top;
	rect.top = 0;
	rect.left = 0;

	//�E�C���h�E�̐���
	HWND hWnd = CreateWindow("Window1", "Manaringo",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right, rect.bottom,
		NULL, NULL, wc.hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	g_hWnd = hWnd;
	
	//MyApplication* myApp = NULL;
	//Direct3D������





	/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[��������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/


	/*�N���X�̃C���X�^���X�����܂�*/
	XManager *xfile = new XManager;
	XManager *xfile2 = new XManager;



	if (SUCCEEDED(InitD3D(hWnd)))
	{
		SceneManager::Initialize();
		///*�N���X�̏����������܂�*/
		//xfile->Initialize();
		//xfile2->Initialize();
		//
		///*�ǂݍ��݂����t�@�C���������Ɏw�肵�܂�*/
		//xfile->LoadXFile("sample.x");
		//xfile2->LoadXFile("test.x");

		//���b�Z�[�W���[�v
		while (1)
		{
			//���b�Z�[�W����������s�������
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (GetMessage(&msg, NULL, 0, 0) == 0)
				{
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);//�V�X�e���ɕԂ�
			}
			else {
				SceneManager::Update();
				SceneManager::Draw();

				//xfile->Translation(0.0f, 1.0f, 0.0f);
				//xfile2->Translation(0.5f, 0.0f, 0.0f);
				///*�Ȃ񂩂��܂�*/
				//xfile->Rendering();
				//
				///*�`��O�̂��񑩁i���̂����֗��ɂ��܂��j*/
				//g_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 0, 255), 1.0f, 0);
				//g_d3dDevice->BeginScene();

				///*���ۂɕ`�悵�܂�*/
				//xfile->Draw();
				//xfile2->Draw();

				///*�`���̂���*/
				//g_d3dDevice->EndScene();
				//g_d3dDevice->Present(NULL, NULL, NULL, NULL);
			}
		}
	}
	SceneManager::Finalize();
	/*����Ȃ��Ȃ����^�C�~���O�ŏI�����܂�*/
	/*xfile->Finalize();
	xfile2->Finalize();*/







	/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�����܂Ł[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/








	//delete myApp;
	Cleanup();
	UnregisterClass("Window1", wc.hInstance);
	return 0;
}

LPDIRECT3DDEVICE9 GetDevice() {
	return g_d3dDevice;
}

HINSTANCE GetHInstance() {
	return g_hInstance;
}

HWND GetHWND() {
	return g_hWnd;
}