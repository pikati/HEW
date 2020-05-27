#pragma once
#include <d3dx9.h>
#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/*directXデバイス解放マクロ*/
#define SAFE_RELEASE(p) do { if(p){ (p)->Release(); (p) = NULL;} } while(0)

#define MY_FVF  (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define RADIAN (D3DX_PI / 180.0f)

struct LINE_VERTEX {
	D3DXVECTOR3 pos;
	D3DXCOLOR color;
};

//頂点の情報
struct VERTEX_3D {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR	col;

	D3DXVECTOR2 tex;
};
