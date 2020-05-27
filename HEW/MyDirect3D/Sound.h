#pragma once

//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#pragma once


#include <windows.h>
#include "xaudio2.h"						


//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_BGM_TITLE,			//�P �^�C�g��
	//SOUND_BGM_TUTORIAL,		//�Q �`���[�g���A��
	SOUND_BGM_GAME,			    //�R �Q�[��
	SOUND_BGM_RESULT,			//�S ���U���g
	//SOUND_BGM_FEVER,			//�T �t�B�[�o�[(�Q�[��)
	SOUND_SE_SCHANGE,			//�U �V�[���J��
	//SOUND_SE_DEC,				//�V �i�߂�(�`���[�g���A��/���U���g)
	//SOUND_SE_LETTER,			//�W �������o��(�`���[�g���A��)
	//SOUND_SE_CNT,				//�X ���[�X�O�J�E���g(�Q�[��)
	SOUND_SE_START,				//�P�O ���[�X�X�^�[�g(�Q�[��)
	SOUND_SE_SHOOT,				//�P�P �e����(�`���[�g���A��/�Q�[��)
	SOUND_SE_WCHANGE,			//�P�Q �e�ς�(�`���[�g���A��/�Q�[��)
	SOUND_SE_PMOVE,				//�P�R �i�s(�`���[�g���A��/�Q�[��)
	SOUND_SE_WATER,				//�P�S �΂ƍ��̏�Q����������Ɠ�������(�`���[�g���A��/�Q�[��)
	SOUND_SE_HOLE,				//�P�T ���Ƃ����Ƃ���������������E���Ƃ����𑊎�v���C���[�ɐ���(�`���[�g���A��/�Q�[��)
	SOUND_SE_FIRE,				//�P�U �؂Ɖ΂̂��������������(�`���[�g���A��/�Q�[��)
	SOUND_SE_HITFIRE,			//�P�V �΂̏�Q���ƃv���C���[����������(�`���[�g���A��/�Q�[��)
	SOUND_SE_SAND,				//�P�W ���̏�Q���ƃv���C���[�����������E���̏�Q���𑊎�v���C���[�ɐ���(�`���[�g���A��/�Q�[��)
	SOUND_SE_HITHOLE,			//�P�X ���Ƃ����ƃv���C���[����������(�`���[�g���A��/�Q�[��)
	SOUND_SE_HITTREE,			//�Q�O �؂ƃv���C���[����������(�`���[�g���A��/�Q�[��)
	SOUND_SE_CTREE,				//�Q�P �؂𑊎�v���C���[�ɐ���(�`���[�g���A��/�Q�[��)
	SOUND_SE_PWALL,				//�Q�Q �ǂƃv���C���[����������(�`���[�g���A��/�Q�[��)
	SOUND_SE_WWALL,				//�Q�R �ǂƂ��������������(�`���[�g���A��/�Q�[��)
	SOUND_SE_COMBO1,			//�Q�S �h�E�R���{�P(�Q�[��)
	SOUND_SE_COMBO2,			//�Q�T ���E�R���{�Q(�Q�[��)
	SOUND_SE_COMBO3,			//�Q�U �~�E�R���{�R�i�Q�[���j
	SOUND_SE_COMBO4,			//�Q�V �t�@�E�R���{�S(�Q�[��)
	SOUND_SE_COMBO5,			//�Q�W �\�E�R���{�T(�Q�[��)
	SOUND_SE_COMBO6,			//�Q�X ���E�R���{�U(�Q�[��)
	SOUND_SE_COMBO7,			//�R�O �V�E�R���{�V(�Q�[��)
	SOUND_SE_COMBO8,			//�R�P �h�E�R���{�W(�Q�[��)
	SOUND_SE_CITEM,				//�R�Q �A�C�e���o��(�`���[�g���A��/�Q�[��)
	SOUND_SE_GTAIYAKI,			//�R�R �����Ă��擾(�`���[�g���A��/�Q�[��)
	SOUND_SE_GKAMERONPAN,		//�R�S �������p���擾(�`���[�g���A��/�Q�[��)
	SOUND_SE_GOAL,				//�R�T �S�[��(�Q�[��)
	SOUND_SE_DIS,				//�R�U ���������E�X�R�A�E�����L���O�\��(���U���g)

	SOUND_LABEL_MAX,
} SOUND_LABEL;

bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
