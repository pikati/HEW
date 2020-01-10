#pragma once
#include <iostream>
#include <fbxsdk.h>
#include <vector>
#include "MyDirect3D.h"
#include "OBB.h"
#include "Enum.h"

#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Fbx
{
private:
	//!fbx�̃}�l�[�W��
	FbxManager* m_manager;
	//!fbx�̃V�[��
	FbxScene*	m_scene;
	//!fbx�̏��
	FbxInfo		m_fbxInfo;
	//!���b�V���̏��
	MeshInfo*	m_meshInfo;

	//!�A�j���[�V�������邩
	bool		m_isAnim;
	//!�A�j���[�V�����̐�
	int				m_animationStackNumber;
	//!���낢��
	FbxTime			m_frameTime, m_timeCount, m_start, m_stop;

	/*DirectX�̋@�\�̂��߂̕ϐ�����*/
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scale;
	OBB*		m_obb;

	void LoadFBX(const char* filePath);
	void InitializeFBX();
	void InitializeUnit();
	void InitializeAnimation(bool isAnimation);
	std::vector<FbxMesh*> GetMesh();
	void MeshTrianglate();
	void SetInfomation();
	int  GetPolygonCount(int meshIndex);
	int  GetVertexCount(int meshIndex);
	int	 GetIndexCount(int meshIndex);
	void GetVertex(int meshIndex, VERTEX_3D* vertex);
	void GetNormal(int meshIndex, VERTEX_3D* vertex);
	void GetUVSetName(int meshIndex);
	void GetUV(int meshIndex);
	void GetMaterial();
	void GetTextureInfo(int meshindex);
	bool CreateVertexBuffer(int meshIndex);
	bool CreateIndexBuffer(int meshIndex);
	void SetVertexBuffer(int meshIndex);
	void SetIndexBuffer(int meshIndex);

	void TextureMemoryAllocate(int meshIndex);
	void LoadTexture(int meshIndex);
	void SetTexture(int meshIndex);

	int GetUVSetNum();

	void DrawModel();
	void DrawAnimation();
	/*�f�o�b�O�p�̕`��*/
	void DrawPoint();
	void DrawWire();
	/*�f�o�b�O�p�̃t�@�C���o��*/
	void PrintFile();


public:
	Fbx();
	~Fbx();

	void Initialize();
	void Load(const char* filePath, bool animation = false);
	void Update();
	void Draw();
	void Finalize();

	/*�ړ� 1:�ړ����������s�� 2:x�����̈ړ��� 3:y�����̈ړ��� 4:z�����̈ړ���*/
	void SetTranslation(float x, float y, float z);
	void SetTranslation(D3DXVECTOR3 pos);
	/*��] 1:��]���������s�� 2:��]���������p�x�i���W�A���p����Ȃ��āZ���̌`�ő��v��Łj�����ɕ����̎�����]�ł��Ȃ�*/
	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);
	void SetRotation(float x, float y, float z);
	/*�g�k 1:�g�k���������s�� 2:�e�k���i1���Ɠ����j */
	void SetScaling(float scale);
	void SetScaling(float scaleX, float scaleY, float scaleZ);

	OBB& GetOBB()const;
};

