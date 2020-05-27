#define _CRT_SECURE_NO_WARNINGS
#include "Input.h"
#include "Utility.h"

HRESULT					Input::m_ret = NULL;
LPDIRECTINPUTDEVICE8	Input::m_lpKeyboard = NULL;
LPDIRECTINPUT8			Input::m_lpDI = NULL;
BYTE					Input::m_key[KEY_MAX];
BYTE					Input::m_keyTrigger[KEY_MAX];
BYTE					Input::m_keyRelease[KEY_MAX];
LPDIRECTINPUTDEVICE8	Input::m_pGamePad[GAMEPADMAX] = { NULL, NULL, NULL, NULL };
DWORD					Input::m_padState[GAMEPADMAX];
DWORD					Input::m_padTrigger[GAMEPADMAX];
int						Input::m_padCount = 0;			// 検出したパッドの数

HRESULT Input::Initialize() {
	m_ret = DirectInput8Create(GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_lpDI, NULL);
	if (FAILED(m_ret)) {
		return E_FAIL;
	}
	m_ret = m_lpDI->CreateDevice(GUID_SysKeyboard, &m_lpKeyboard, NULL);
	if (FAILED(m_ret)) {
		return E_FAIL;
	}
	m_ret = m_lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(m_ret)) {
		SAFE_RELEASE(m_lpKeyboard);
		SAFE_RELEASE(m_lpDI);
		return E_FAIL;
	}
	m_ret = m_lpKeyboard->SetCooperativeLevel(GetHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(m_ret)) {
		SAFE_RELEASE(m_lpKeyboard);
		SAFE_RELEASE(m_lpDI);

		return E_FAIL;
	}
	memset(&m_key, 0, sizeof(m_key));
	memset(&m_keyTrigger, 0, sizeof(m_keyTrigger));
	memset(&m_keyRelease, 0, sizeof(m_keyRelease));
	m_lpKeyboard->Acquire();

	return S_OK;
}

void Input::Finalize() {
	m_lpKeyboard->Unacquire();
	SAFE_RELEASE(m_lpKeyboard);
	SAFE_RELEASE(m_lpDI);
}

bool Input::GetKey(UINT keyCode) {
	//チェックフラグ
	bool flag = false;

	//キー情報を取得
	ZeroMemory(m_key, sizeof(m_key));
	m_ret = m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	if (FAILED(m_ret)) {
		// 失敗なら再開させてもう一度取得
		m_lpKeyboard->Acquire();
		m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	}
	if (m_key[keyCode] & 0x80)
	{
		flag = true;
	}
	m_keyTrigger[keyCode] = m_key[keyCode];

	return flag;
}

bool Input::TriggerKey(UINT keyCode){
	//チェックフラグ
	bool flag = false;

	//キー情報を取得
	ZeroMemory(m_key, sizeof(m_key));
	m_ret = m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	if (FAILED(m_ret)) {
		// 失敗なら再開させてもう一度取得
		m_lpKeyboard->Acquire();
		m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	}
	if ((m_key[keyCode] & 0x80) && !(m_keyTrigger[keyCode] & 0x80))
	{
		flag = true;
	}
	m_keyTrigger[keyCode] = m_key[keyCode];

	return flag;
}

bool Input::ReleaseKey(UINT keyCode) {
	//チェックフラグ
	bool flag = false;

	//キー情報を取得
	ZeroMemory(m_key, sizeof(m_key));
	m_ret = m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	if (FAILED(m_ret)) {
		// 失敗なら再開させてもう一度取得
		m_lpKeyboard->Acquire();
		m_lpKeyboard->GetDeviceState(sizeof(m_key), m_key);
	}
	if (!(m_key[keyCode] & 0x80) && (m_keyRelease[keyCode] & 0x80))
	{
		flag = true;
	}
	m_keyRelease[keyCode] = m_key[keyCode];

	return flag;
}