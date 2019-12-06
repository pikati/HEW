#pragma once
#include "main.h"
#define KEY_MAX 256
// game pad�p�ݒ�l
#define DEADZONE		2500			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX		1000			// �L���͈͂̍ő�l
#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l

#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)
#define BUTTON_A		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

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
	static int						m_padCount;			// ���o�����p�b�h�̐�
public:
	static HRESULT	Initialize();
	static void		Finalize();
	static bool		GetKey(UINT keyCode);
	static bool		TriggerKey(UINT keyCode);
	static bool		ReleaseKey(UINT keyCode);
};

