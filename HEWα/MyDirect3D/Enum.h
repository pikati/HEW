#pragma once
#include "MyDirect3D.h"
#include <fbxsdk.h>
#include <vector>

enum SCENE_STATE {
	SCENE_TITLE
};

//頂点の情報
struct VERTEX_3D {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR	col;
	D3DXVECTOR2 tex;
};

//メッシュの情報
struct MeshInfo {
	//ポリゴンの数
	int							polygonCount;
	//頂点の数
	int							vertexCount;
	//頂点インデックスの数
	int							indexCount;
	//頂点
	VERTEX_3D*					vertex;
	//頂点インデックスの順番
	int*						indexBuffer;
	//UVSetの数
	int							uvSetCount;
	//UVSetの名前
	std::string*				uvSetName;
	//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9		pVB;
	//インデックスバッファ
	LPDIRECT3DINDEXBUFFER9		pIB;
	//テクスチャ
	LPDIRECT3DTEXTURE9*			texture;
	//テクスチャパス
	std::vector<std::string>	texturePath;
};

//FBXの情報
struct FbxInfo {
	//メッシュ
	std::vector<FbxMesh*>			 meshes;
	//メッシュの数
	int								 meshCount;
	//マテリアル
	std::vector<FbxSurfaceMaterial*> material;
	//マテリアルの数
	int								 materialCount;
	//UVSetの数
	int								 uvSetCount;
	//UVSetの名前
	std::string*					 uvSetName;
};
