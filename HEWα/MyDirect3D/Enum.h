#pragma once
#include "MyDirect3D.h"
#include <fbxsdk.h>
#include <vector>

enum SCENE_STATE {
	SCENE_TITLE
};

//���_�̏��
struct VERTEX_3D {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR	col;
	D3DXVECTOR2 tex;
};

//���b�V���̏��
struct MeshInfo {
	//�|���S���̐�
	int							polygonCount;
	//���_�̐�
	int							vertexCount;
	//���_�C���f�b�N�X�̐�
	int							indexCount;
	//���_
	VERTEX_3D*					vertex;
	//���_�C���f�b�N�X�̏���
	int*						indexBuffer;
	//UVSet�̐�
	int							uvSetCount;
	//UVSet�̖��O
	std::string*				uvSetName;
	//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9		pVB;
	//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9		pIB;
	//�e�N�X�`��
	LPDIRECT3DTEXTURE9*			texture;
	//�e�N�X�`���p�X
	std::vector<std::string>	texturePath;
};

//FBX�̏��
struct FbxInfo {
	//���b�V��
	std::vector<FbxMesh*>			 meshes;
	//���b�V���̐�
	int								 meshCount;
	//�}�e���A��
	std::vector<FbxSurfaceMaterial*> material;
	//�}�e���A���̐�
	int								 materialCount;
	//UVSet�̐�
	int								 uvSetCount;
	//UVSet�̖��O
	std::string*					 uvSetName;
};
