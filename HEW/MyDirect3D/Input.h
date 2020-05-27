#pragma once
#include "main.h"
#define KEY_MAX 256
// game pad用設定値
#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX		1000			// 有効範囲の最大値
#define RANGE_MIN		-1000			// 有効範囲の最小値

#define BUTTON_UP		0x00000001l	// 方向キー上(.IY<0)
#define BUTTON_DOWN		0x00000002l	// 方向キー下(.IY>0)
#define BUTTON_LEFT		0x00000004l	// 方向キー左(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// 方向キー右(.IX>0)
#define BUTTON_A		0x00000010l	// Ａボタン(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// Ｂボタン(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// Ｃボタン(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// Ｘボタン(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// Ｙボタン(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// Ｚボタン(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// Ｍボタン(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット

class Input
{
private:
	static HRESULT					m_ret;
	static LPDIRECTINPUTDEVICE8		m_lpKeyboard;
	static LPDIRECTINPUT8			m_lpDI;
	static BYTE						m_key[KEY_MAX];
	static BYTE						m_keyTrigger[KEY_MAX];
	static BYTE						m_keyRelease[KEY_MAX];
	static LPDIRECTINPUTDEVICE8		m_pGamePad[GAMEPADMAX];
	static DWORD					m_padState[GAMEPADMAX];
	static DWORD					m_padTrigger[GAMEPADMAX];
	static int						m_padCount;			// 検出したパッドの数
public:
	static HRESULT	Initialize();
	static void		Finalize();
	static bool		GetKey(UINT keyCode);
	static bool		TriggerKey(UINT keyCode);
	static bool		ReleaseKey(UINT keyCode);
};

