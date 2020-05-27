#pragma once
#include <iostream>
#include <fbxsdk.h>
#include <vector>
#include "MyDirect3D.h"
#include "AABB.h"

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
	//�}�e���A���̐F
	D3DXCOLOR*						 color;
};

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

	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	FbxMatrix clusterDeformation[2404];//1.9053

	std::vector<std::vector<std::vector<D3DXVECTOR3>>> m_animVertex;


	bool		m_isMove;

	//OBB*		m_obb;
	bool		m_isCollison;
	bool		m_isaabb;
	int testCount;
	AABB*		m_aabb;

	int m_frame;
	int m_count;

	std::vector<FbxSkin*>	m_skinDeformer;
	std::vector<FbxNode*>	m_link;

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

	void UpdateTime();

	/*�f�o�b�O�p�̃t�@�C���o��*/
	void PrintFile();

	void LoadTexture();

	void SetAnimationVertex();
	void SetSkinDeformer();
public:

	void Initialize(bool col, bool aabb);
	void Load(const char* filePath, bool animation = false);
	void Update();
	void Draw();
	void Finalize();

	/*�ړ� 1:�ړ����������s�� 2:x�����̈ړ��� 3:y�����̈ړ��� 4:z�����̈ړ���*/
	void SetTranslation(float x, float y, float z);
	void SetTranslation(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);
	void SetRotation(float x, float y, float z);
	/*�g�k 1:�g�k���������s�� 2:�e�k���i1���Ɠ����j */
	void SetScaling(float scale);
	void SetScaling(float scaleX, float scaleY, float scaleZ);

	//OBB& GetOBB()const;
	AABB& GetAABB()const;
	void Move(bool b);
};

