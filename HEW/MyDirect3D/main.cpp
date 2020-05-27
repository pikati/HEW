/*画面の幅と高さマクロ*/
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
static LPD3DXFONT			g_pFont = NULL;//フォント
//
//DWORD dwNumMaterials = 0;
//
////テキスト描画
//void TextDraw(LPD3DXFONT pFont, char* text, int X, int Y)
//{
//	RECT rect = { X,Y,0,0 };//描画位置
//	//スプライトポインタ(無くても良し),描画文字,文字数(-1で全部),描画範囲,フォーマット,色
//	pFont->DrawText(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
//}
//
//
////Direct3D初期化
HRESULT InitD3D(HWND hWnd)
{
	//Direct3Dを生成する
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) { return E_FAIL; }

	//デバイス生成用のパラメーター
	D3DPRESENT_PARAMETERS d3dpp;//パラメーター構造体
	ZeroMemory(&d3dpp, sizeof(d3dpp));//ゼロで初期化
	d3dpp.Windowed = TRUE;//ウインドウモードで起動
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//バックバッファのスワップエフェクト Direct3Dにスワップエフェクトをまかせる
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//バックバッファのフォーマット今表示されているモニタの設定と同じ
	d3dpp.BackBufferCount = 1;//バックバッファの数
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;//マルチサンプリングは行わない
	d3dpp.MultiSampleQuality = 0;//マルチサンプリングは行わないので0
	d3dpp.EnableAutoDepthStencil = TRUE;//Direct3Dに深度バッファの管理をまかせる
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//深度バッファのフォーマット（通常はこの値で問題ない）
	d3dpp.hDeviceWindow = hWnd;//カバーウィンドウ＝アプリケーションのウィンドウ
	d3dpp.Flags = 0;//フラグは使わない
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//今のリフレッシュレートをそのまま使う
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//モニタの垂直回帰を待つ

	//Direct3Dデバイスの生成 HAL(ハードウェアアクセラレーション)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_d3dDevice))) {
		//HALが駄目ならHEL(ソフトウェアエミュレーション)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_d3dDevice))) {
			//駄目なら終了
			return(E_FAIL);
		}
	}

	//フォントの生成 MSゴシック
   //デバイス,文字高さ,文字幅,フォントスタイル,ミップマップのレベル,斜体にするかどうか,文字セット,出力精度,出力品質,フォントピッチとファミリ,フォント名,フォントポインタ
	HRESULT hr = D3DXCreateFont(g_d3dDevice, 20, 0, FW_HEAVY, 1, false, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "ＭＳ ゴシック", &g_pFont);
	if FAILED(hr) { return(E_FAIL); }


	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = D3DXVECTOR3(-1, 0, -1);


	// Zバッファー処理を有効にする
	g_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// ライトを有効にする
	g_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// アンビエントライト（環境光）を設定する
	g_d3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00111111);
	// スペキュラ（鏡面反射）を有効にする
	//g_d3dDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	g_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
	return S_OK;
}

//終了時解放処理
VOID Cleanup()
{
	SAFE_RELEASE(g_pFont);
	SAFE_RELEASE(g_d3dDevice);
	SAFE_RELEASE(g_pD3D);
}

//メッセージプロシージャ
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

//メイン関数
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	g_hInstance = hInst;
	MSG msg;
	//ウインドウクラスの登録
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
					  GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
					  "Window1", NULL };
	RegisterClassEx(&wc);

	//タイトルバーとウインドウ枠の分を含めてウインドウサイズを設定
	RECT rect;
	SetRect(&rect, 0, 0, 1280, 720);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	rect.right = rect.right - rect.left;
	rect.bottom = rect.bottom - rect.top;
	rect.top = 0;
	rect.left = 0;

	//ウインドウの生成
	HWND hWnd = CreateWindow("Window1", "Manaringo",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right, rect.bottom,
		NULL, NULL, wc.hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	g_hWnd = hWnd;
	
	//MyApplication* myApp = NULL;
	//Direct3D初期化





	/*ーーーーーーーーーーーーーーーーここからーーーーーーーーーーーーーーーー*/


	/*クラスのインスタンスを作ります*/
	XManager *xfile = new XManager;
	XManager *xfile2 = new XManager;



	if (SUCCEEDED(InitD3D(hWnd)))
	{
		SceneManager::Initialize();
		///*クラスの初期化をします*/
		//xfile->Initialize();
		//xfile2->Initialize();
		//
		///*読み込みたいファイルを引数に指定します*/
		//xfile->LoadXFile("sample.x");
		//xfile2->LoadXFile("test.x");

		//メッセージループ
		while (1)
		{
			//メッセージあったら実行されるやつ
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (GetMessage(&msg, NULL, 0, 0) == 0)
				{
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);//システムに返す
			}
			else {
				SceneManager::Update();
				SceneManager::Draw();

				//xfile->Translation(0.0f, 1.0f, 0.0f);
				//xfile2->Translation(0.5f, 0.0f, 0.0f);
				///*なんかします*/
				//xfile->Rendering();
				//
				///*描画前のお約束（そのうち便利にします）*/
				//g_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 0, 255), 1.0f, 0);
				//g_d3dDevice->BeginScene();

				///*実際に描画します*/
				//xfile->Draw();
				//xfile2->Draw();

				///*描画後のお約束*/
				//g_d3dDevice->EndScene();
				//g_d3dDevice->Present(NULL, NULL, NULL, NULL);
			}
		}
	}
	SceneManager::Finalize();
	/*いらなくなったタイミングで終了します*/
	/*xfile->Finalize();
	xfile2->Finalize();*/







	/*ーーーーーーーーーーーーーーーーここまでーーーーーーーーーーーーーーーー*/








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