#pragma once
#include "main.h"
typedef struct {
	/*座標情報*/
	float x, y, z;		//D3DFVF_XYZRHWのXYZの部分
	/*おまじないでおｋ*/
	float rhw;          //射影変換完了フラグ D3DFVF_XYZRHWのRHWの部分 パイプラインの最後に行うスケール変換の値で構造体の中にあると頂点が座標変換済みであると判断される
	/*ポリゴンの色情報*/
	D3DCOLOR deffuse;	//D3DFVF_DIFFUSE
	/*テクスチャ座標*/
	float tu, tv;		//D3DFVF_TEX1
}VERTEX;

class Polygons
{
private:
	static VERTEX vertex[4];
public:
	static void Draw(float x, float y, float w, float h, float tx, float ty, float tw, float th, LPDIRECT3DTEXTURE9 texture);
	static void FadeDraw(float x, float y, float w, float h, float tx, float ty, float tw, float th, int alfa, LPDIRECT3DTEXTURE9 texture);
};

