#pragma once
#include "MyDirect3D.h"
#include "AABB.h"

class XManager {
private:
	LPDIRECT3DDEVICE9	m_d3dDevice;
	D3DMATERIAL9		*m_pMaterials;
	DWORD				m_numMaterials;
	LPD3DXMESH			m_pMesh;
	LPDIRECT3DTEXTURE9* m_pTextures;
	D3DXVECTOR3			m_position;
	D3DXVECTOR3			m_rotation;
	D3DXVECTOR3			m_scale;
	D3DXVECTOR3			m_max;
	D3DXVECTOR3			m_min;
	D3DXMATRIX			m_mat;

	AABB*				m_aabb;
	//OBB*				m_obb;

	bool				m_isCol;
	bool				m_isaabb;
public:
	/*�C���X�^���X������炷���ɌĂ�ł�*/
	void Initialize(bool col, bool isAABB);
	/*�����ɂ����t�@�C����ǂݍ��ނ� isCol��true�Ȃ瓖���蔻�肷��� false�Ȃ瓖���蔻�肵�Ȃ���*/
	bool LoadXFile(const char* filePath);
	/*�X�V*/
	void Update();
	/*�`�悷���*/
	void Draw();
	/*�ǂݍ��񂾐F�X���J�������*/
	void Finalize();
	/*�ړ� 1:�ړ����������s�� 2:x�����̈ړ��� 3:y�����̈ړ��� 4:z�����̈ړ���*/
	void SetTranslation(float x, float y, float z);
	void SetTranslation(D3DXVECTOR3 pos);
	/*��] 1:��]���������s�� 2:��]���������p�x�i���W�A���p����Ȃ��āZ���̌`�ő��v��Łj�����ɕ����̎�����]�ł��Ȃ�*/
	void SetRotationX(float angle);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);
	void SetRotation(float x, float y, float z);
	void SetRotation(D3DXVECTOR3 rot);
	/*�g�k 1:�g�k���������s�� 2:�e�k���i1���Ɠ����j */
	void SetScaling(D3DXVECTOR3 scale);
	void SetScaling(float scale);
	void SetScaling(float scaleX, float scaleY, float scaleZ);

	/*OBB& GetOBB()const;*/
	AABB& GetAABB()const;

	void SetMinMax(D3DXVECTOR3 min, D3DXVECTOR3 max);
};
