#pragma once

//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#pragma once


#include <windows.h>
#include "xaudio2.h"						


//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_BGM_TITLE,			//１ タイトル
	//SOUND_BGM_TUTORIAL,		//２ チュートリアル
	SOUND_BGM_GAME,			    //３ ゲーム
	SOUND_BGM_RESULT,			//４ リザルト
	//SOUND_BGM_FEVER,			//５ フィーバー(ゲーム)
	SOUND_SE_SCHANGE,			//６ シーン遷移
	//SOUND_SE_DEC,				//７ 進める(チュートリアル/リザルト)
	//SOUND_SE_LETTER,			//８ 文字が出る(チュートリアル)
	//SOUND_SE_CNT,				//９ レース前カウント(ゲーム)
	SOUND_SE_START,				//１０ レーススタート(ゲーム)
	SOUND_SE_SHOOT,				//１１ 弾発射(チュートリアル/ゲーム)
	SOUND_SE_WCHANGE,			//１２ 弾変え(チュートリアル/ゲーム)
	SOUND_SE_PMOVE,				//１３ 進行(チュートリアル/ゲーム)
	SOUND_SE_WATER,				//１４ 火と砂の障害物がわっかと当たった(チュートリアル/ゲーム)
	SOUND_SE_HOLE,				//１５ 落とし穴とわっかが当たった・落とし穴を相手プレイヤーに生成(チュートリアル/ゲーム)
	SOUND_SE_FIRE,				//１６ 木と火のわっかが当たった(チュートリアル/ゲーム)
	SOUND_SE_HITFIRE,			//１７ 火の障害物とプレイヤーが当たった(チュートリアル/ゲーム)
	SOUND_SE_SAND,				//１８ 砂の障害物とプレイヤーが当たった・砂の障害物を相手プレイヤーに生成(チュートリアル/ゲーム)
	SOUND_SE_HITHOLE,			//１９ 落とし穴とプレイヤーが当たった(チュートリアル/ゲーム)
	SOUND_SE_HITTREE,			//２０ 木とプレイヤーが当たった(チュートリアル/ゲーム)
	SOUND_SE_CTREE,				//２１ 木を相手プレイヤーに生成(チュートリアル/ゲーム)
	SOUND_SE_PWALL,				//２２ 壁とプレイヤーが当たった(チュートリアル/ゲーム)
	SOUND_SE_WWALL,				//２３ 壁とわっかが当たった(チュートリアル/ゲーム)
	SOUND_SE_COMBO1,			//２４ ド・コンボ１(ゲーム)
	SOUND_SE_COMBO2,			//２５ レ・コンボ２(ゲーム)
	SOUND_SE_COMBO3,			//２６ ミ・コンボ３（ゲーム）
	SOUND_SE_COMBO4,			//２７ ファ・コンボ４(ゲーム)
	SOUND_SE_COMBO5,			//２８ ソ・コンボ５(ゲーム)
	SOUND_SE_COMBO6,			//２９ ラ・コンボ６(ゲーム)
	SOUND_SE_COMBO7,			//３０ シ・コンボ７(ゲーム)
	SOUND_SE_COMBO8,			//３１ ド・コンボ８(ゲーム)
	SOUND_SE_CITEM,				//３２ アイテム出現(チュートリアル/ゲーム)
	SOUND_SE_GTAIYAKI,			//３３ たい焼き取得(チュートリアル/ゲーム)
	SOUND_SE_GKAMERONPAN,		//３４ メロンパン取得(チュートリアル/ゲーム)
	SOUND_SE_GOAL,				//３５ ゴール(ゲーム)
	SOUND_SE_DIS,				//３６ 勝ち負け・スコア・ランキング表示(リザルト)

	SOUND_LABEL_MAX,
} SOUND_LABEL;

bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
