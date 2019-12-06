/**
* @file joycon.cpp
* @brief ジョイコンの処理
* @author ドメイン
* @date 2019/11/9
*/

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "Joycon.h"
#include "main.h"
#include "dinput.h"
//-----------------------------------------------------------------------------
// マクロ
//-----------------------------------------------------------------------------
// Joypad用設定値
#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX		1000			// 有効範囲の最大値
#define RANGE_MIN		-1000			// 有効範囲の最小値

/* ジョイパッド用 */
DWORD					g_diJoyState = 0x00000000L;	// ジョイパッド情報
DWORD					g_diJoyState2[JOYPADMAX];	// ジョイパッド情報（複数対応）
int						g_diJoyCount = 0;			// 検出したジョイパッドの数

/* DirectInput共通 */
LPDIRECTINPUT8		m_lpDI = NULL;			// DirectInputオブジェクト
HRESULT					    m_ret = NULL;

/* ジョイパッド用 */
static LPDIRECTINPUTDEVICE8	g_lpDIJoypad = NULL;		// ジョイパッドデバイス
static LPDIRECTINPUTDEVICE8	g_lpDIJoypad2[JOYPADMAX] = { NULL,NULL,NULL,NULL };// ジョイパッドデバイス



// Direct Input 初期化
bool InitDInput(HINSTANCE hInstApp)
{
	HRESULT		hr;

	hr = DirectInput8Create(hInstApp, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_lpDI, NULL);
	if (FAILED(hr))
		return false;	// DirectInput8の作成に失敗

	return true;

}


void ReleaseDInput(void)
{
	// DirectInputのデバイスを開放
	if (g_lpDIJoypad) g_lpDIJoypad->Unacquire();
	SAFE_RELEASE(g_lpDIJoypad);
	for (int i = 0; i < JOYPADMAX; i++) {
		if (g_lpDIJoypad2[i]) g_lpDIJoypad2[i]->Unacquire();
		SAFE_RELEASE(g_lpDIJoypad2[i]);
	}
	SAFE_RELEASE(m_lpDI);

}



//	複数のジョイスティック・デバイスを列挙（コールバック関数）
BOOL CALLBACK GetJoystickCallback2(LPDIDEVICEINSTANCE lpddi, LPVOID /*pvRef*/)
{
	HRESULT hr;

	hr = m_lpDI->CreateDevice(lpddi->guidInstance, &g_lpDIJoypad2[g_diJoyCount++], NULL);
	return DIENUM_CONTINUE;	// 次のデバイスを列挙

}


//  複数のJoypad用オブジェクトを作成
bool InitJoypad2(void)
{
	HRESULT		hr;
	int			i;

	// ジョイパッドを探す
	m_lpDI->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)GetJoystickCallback2, NULL, DIEDFL_ATTACHEDONLY);

	for (i = 0; i < g_diJoyCount; i++) {
		// ジョイスティック用のデータ・フォーマットを設定
		hr = g_lpDIJoypad2[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr))
			return false; // データフォーマットの設定に失敗

		// モードを設定（フォアグラウンド＆非排他モード）
//		hr = g_lpDIJoypad2[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//		if ( FAILED(hr) )
//			return false; // モードの設定に失敗

		// 軸の値の範囲を設定
		// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
		// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
		// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドは、関係なし)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;
		// X軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_X;
		g_lpDIJoypad2[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Y;
		g_lpDIJoypad2[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 各軸ごとに、無効のゾーン値を設定する。
		// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
		// 指定する値は、10000に対する相対値(2000なら20パーセント)。
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_X;
		g_lpDIJoypad2[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Y;
		g_lpDIJoypad2[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//ジョイスティック入力制御開始
		g_lpDIJoypad2[i]->Acquire();
	}

	return true;

}


// 機能概要：　複数のジョイパッドの状態を取得
void GetJoypadState2(void)
{
	
	DIJOYSTATE2		dijs;
	int				i;

	for (i = 0; i < g_diJoyCount; i++) {
		g_diJoyState2[i] = 0x00000000l;	// 初期化

		g_lpDIJoypad2[i]->Poll();	// ジョイスティックにポールをかける
	/*	if (FAILED(hr)) {
			hr = g_lpDIJoypad2[i]->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = g_lpDIJoypad2[i]->Acquire();
		}
*/
		HRESULT	hr = g_lpDIJoypad2[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
			hr = g_lpDIJoypad2[i]->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = g_lpDIJoypad2[i]->Acquire();
		}

		// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
		//* y-axis (forward)
		if (dijs.lY < 0)					g_diJoyState2[i] |= BUTTON_UP;
		//* y-axis (backward)
		if (dijs.lY > 0)					g_diJoyState2[i] |= BUTTON_DOWN;
		//* x-axis (left)
		if (dijs.lX < 0)					g_diJoyState2[i] |= BUTTON_LEFT;
		//* x-axis (right)
		if (dijs.lX > 0)					g_diJoyState2[i] |= BUTTON_RIGHT;

		if(dijs.rglSlider[1] <100 && dijs.rglSlider[0] > 100)           g_diJoyState2[i] |= BUTTON_M;
		if (dijs.rglSlider[1] > 65000 && dijs.rglSlider[0] > 100)           g_diJoyState2[i] |= BUTTON_R;
		if (dijs.rglSlider[0] < 100 && dijs.rglSlider[1] > 100)           g_diJoyState2[i] |= BUTTON_START;
		//* Ａボタン
		if (dijs.rgbButtons[0] & 0x80)	g_diJoyState2[i] |= BUTTON_A;
		//* Ｂボタン
		if (dijs.rgbButtons[1] & 0x80)	g_diJoyState2[i] |= BUTTON_B;
		//* Ｃボタン
		if (dijs.rgbButtons[2] & 0x80)	g_diJoyState2[i] |= BUTTON_C;
		//* Ｘボタン
		if (dijs.rgbButtons[3] & 0x80)	g_diJoyState2[i] |= BUTTON_X;
		//* Ｙボタン
		if (dijs.rgbButtons[4] & 0x80)	g_diJoyState2[i] |= BUTTON_Y;
		//* Ｚボタン
		if (dijs.rgbButtons[5] & 0x80)	g_diJoyState2[i] |= BUTTON_Z;
		//* Ｌボタン
		if (dijs.rgbButtons[6] & 0x80)	g_diJoyState2[i] |= BUTTON_L;
		////* Ｒボタン
		//if (dijs.rgbButtons[7] & 0x80)	g_diJoyState2[i] |= BUTTON_R;
		////* ＳＴＡＲＴボタン
		//if (dijs.rgbButtons[8] & 0x80)	g_diJoyState2[i] |= BUTTON_START;
		////* Ｍボタン
		//if (dijs.rgbButtons[9] & 0x80)	g_diJoyState2[i] |= BUTTON_M;
		

	/*	if (dijs.rgdwPOV[0] == 22500 || dijs.rgdwPOV[0] == 18000 || dijs.rgdwPOV[0] == 13500) g_diJoyState2[i] |= BUTTON_LEFT;

		if (dijs.rgdwPOV[0] == 31500 || dijs.rgdwPOV[0] == 0 || dijs.rgdwPOV[0] == 4500)  g_diJoyState2[i] |= BUTTON_RIGHT;*/
	}

}


