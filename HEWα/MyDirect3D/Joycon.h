/**
* @file joycon.h
* @brief joycon�w�b�_�[
* @author �h���C��
* @date 2019/11/9
*/

#include "main.h"
// �}�N��
//-----------------------------------------------------------------------------
/* Joypad��� */
#define BUTTON_UP		0x00000001l	// �����L�[��(dijs.IY<0)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(dijs.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(dijs.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(dijs.IX>0)
#define BUTTON_A		0x00000010l	// �`�{�^��(dijs.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// �a�{�^��(dijs.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// �b�{�^��(dijs.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// �w�{�^��(dijs.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// �x�{�^��(dijs.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// �y�{�^��(dijs.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// �k�{�^��(dijs.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// �q�{�^��(dijs.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(dijs.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// �l�{�^��(dijs.rgbButtons[9]&0x80)

#define JOYPADMAX		8			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g


//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------

/* �W���C�p�b�h�p */
extern DWORD				g_diJoyState;
extern DWORD				g_diJoyState2[JOYPADMAX];
extern int					g_diJoyCount;


//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾 function-prototypes
//-----------------------------------------------------------------------------
/* DirectInput���� */
bool InitDInput(HINSTANCE);
void ReleaseDInput(void);

/* �W���C�p�b�h�p */
bool InitJoypad2(void);
void GetJoypadState2(void);

