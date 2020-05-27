#include "Fbx.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>

void Fbx::Initialize(bool col, bool aabb) {
	m_pDevice = GetDevice();
	m_manager = NULL;
	m_scene = NULL;
	m_isCollison = col;
	m_isaabb = aabb;
	if (m_isCollison) 
	{
		if (m_isaabb)
		{
			m_aabb = new AABB;
		}
		else 
		{
			m_obb = new OBB;
			m_obb->Initialize();
		}
	}
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_max = D3DXVECTOR3(-10000, -10000, -10000);
	m_min = D3DXVECTOR3(10000, 10000, 10000);
	m_manager = FbxManager::Create();
}

void Fbx::Update() {
	if (m_isCollison)
	{
		if (m_isaabb)
		{
			m_aabb->Update(m_position);
		}
		else
		{
			D3DXMATRIX mat, t, r, s;
			D3DXMatrixIdentity(&mat);
			D3DXMatrixIdentity(&t);
			D3DXMatrixIdentity(&r);
			D3DXMatrixIdentity(&s);
			D3DXMatrixTranslation(&t, m_position.x, m_position.y, m_position.z);
			D3DXMatrixRotationYawPitchRoll(&r, m_rotation.x, m_rotation.y, m_rotation.z);
			D3DXMatrixScaling(&s, m_scale.x, m_scale.y, m_scale.z);
			mat = s * r * t;
			m_obb->Update(mat);
		}
	}
	
}

void Fbx::Draw() {
	if (m_isAnim)
	{
		DrawAnimation();
	}
	else
	{
		DrawModel();
	}
	if (m_isCollison)
	{
		if (m_isaabb)
		{
			m_aabb->Draw();
		}
		else
		{
			m_obb->Draw();
		}
	}
}

void Fbx::Finalize() {
	for (int meshIndex = m_fbxInfo.meshCount - 1; meshIndex >= 0; meshIndex--)
	{
		for (int i = m_meshInfo[meshIndex].uvSetCount - 1; i >= 0; i--)
		{
			SAFE_RELEASE(m_meshInfo[meshIndex].texture[i]);
		}
		//delete m_meshInfo[meshIndex].texture;
		/*for (int i = 0; i < m_meshInfo[meshIndex].uvSetName->size(); i++)
		{
			m_meshInfo[meshIndex].uvSetName[i].clear();
			m_meshInfo[meshIndex].uvSetName[i].shrink_to_fit();
		}*/
		//delete m_meshInfo[meshIndex].uvSetName;
	}
	for (int meshIndex = m_fbxInfo.meshCount - 1; meshIndex >= 0; meshIndex--)
	{
		//delete m_meshInfo[meshIndex].vertex;
	}
//	delete m_fbxInfo.uvSetName;
//	delete m_meshInfo;
//	m_manager->Destroy();
	if (m_isCollison)
	{
		if (m_isaabb)
		{
			delete m_aabb;
		}
		else
		{
			//delete m_obb;
		}
	}
	
}

void Fbx::Load(const char* filePath, bool animation) {
	LoadFBX(filePath);
	InitializeFBX();
	InitializeAnimation(animation);
	if (m_isCollison)
	{
		if (m_isaabb)
		{
			m_aabb->Initialize(m_min, m_max, m_position);
		}
		else {
			m_obb->CreateOBB(m_meshInfo, m_fbxInfo.meshCount);
		}
	}
}

void Fbx::LoadFBX(const char* filePath) {
	if (NULL != m_manager) {
		//�C���|�[�^�[�쐬
		FbxImporter* importer = FbxImporter::Create(m_manager, "");

		if (NULL != importer) {
			//�V�[���쐬
			m_scene = FbxScene::Create(m_manager, "");

			if (NULL != m_scene) {
				//filePath�Ɏw�肵���t�@�C����ǂݍ���
				bool result = importer->Initialize(filePath);

				if (result) {
					//�V�[���ɃC���|�[�g�����t�@�C����n��
					importer->Import(m_scene);
				}
				else
				{
					MessageBox(NULL, "�t�@�C���p�X�Ԉ���Ă邩����", NULL, MB_OK);
				}
			}
		}
		//�C���|�[�^�[�̖�ڂ͏I���Ȃ̂ŉ������
		importer->Destroy();
	}
}

void Fbx::InitializeFBX() {
	MeshTrianglate();
	InitializeUnit();
	m_fbxInfo.meshes = GetMesh();
	SetInfomation();
}

void Fbx::InitializeAnimation(bool isAnimation) {
	if (isAnimation)
	{
		m_isAnim = true;
		/*�A�j���[�V�����̑I������ѐݒ�*/
		FbxArray<FbxString*> AnimStackNameArray;
		//�A�j���[�V�����̖��O�ꗗ���擾
		m_scene->FillAnimStackNameArray(AnimStackNameArray);
		m_animationStackNumber = m_scene->GetSrcObjectCount<FbxAnimStack>();
		//m_animationStackNumber�Ԗڂ̃A�j���[�V���������擾
		if (m_animationStackNumber == 0)
		{
			m_isAnim = false;
			return;
		}
		FbxAnimStack *AnimationStack = m_scene->FindMember<FbxAnimStack>(AnimStackNameArray[m_animationStackNumber - 1]->Buffer());
		//�A�j���[�V������ݒ�
		m_scene->SetCurrentAnimationStack(AnimationStack);

		/*�A�j���[�V�������s����ŕK�v�Ȏ��Ԋ֌W�̒l���擾*/
		//�A�j���[�V�������̎擾
		FbxTakeInfo *takeInfo = m_scene->GetTakeInfo(*(AnimStackNameArray[m_animationStackNumber - 1]));
		//�J�n����
		m_start = takeInfo->mLocalTimeSpan.GetStart();
		//�I������
		m_stop = takeInfo->mLocalTimeSpan.GetStop();
		//�A�j���[�V�����P�R�}�����s����Ă������ԏ���ێ����� ���Ԃ̃J�E���g���@��ݒ�
		m_frameTime.SetTime(0, 0, 0, 1, 0, m_scene->GetGlobalSettings().GetTimeMode());
		m_timeCount = m_start;
	}
}

void Fbx::MeshTrianglate() {
	FbxGeometryConverter geometryConverter(m_manager);
	geometryConverter.Triangulate(m_scene, true);
}

void Fbx::InitializeUnit() {
	FbxSystemUnit SceneSystemUnit = m_scene->GetGlobalSettings().GetSystemUnit();
	if (SceneSystemUnit.GetScaleFactor() != 1.0f)
	{
		// �Z���`���[�^�[�P�ʂɃR���o�[�g����B
		FbxSystemUnit::cm.ConvertScene(m_scene);
	}
}

std::vector<FbxMesh*> Fbx::GetMesh() {
	//���b�V���̐����擾
	m_fbxInfo.meshCount = m_scene->GetSrcObjectCount<FbxMesh>();
	std::vector<FbxMesh*> meshes;
	for (int i = 0; i < m_fbxInfo.meshCount; ++i)
	{
		//i�Ԗڂ̃��b�V�����擾
		FbxMesh* mesh = m_scene->GetSrcObject<FbxMesh>(i);
		meshes.emplace_back(mesh);
	}
	return meshes;
}

void Fbx::SetInfomation() {
	//�������m��
	m_fbxInfo.uvSetName = new std::string[GetUVSetNum()];
	m_meshInfo = new MeshInfo[m_fbxInfo.meshCount];
	GetMaterial();
	//���ꂼ��̒l�擾
	for (int meshIndex = 0; meshIndex < m_fbxInfo.meshCount; meshIndex++)
	{
		m_meshInfo[meshIndex].polygonCount = GetPolygonCount(meshIndex);
		m_meshInfo[meshIndex].vertexCount = GetVertexCount(meshIndex);
		m_meshInfo[meshIndex].indexCount = GetIndexCount(meshIndex);

		m_meshInfo[meshIndex].vertex = new VERTEX_3D[m_meshInfo[meshIndex].vertexCount];
		GetVertex(meshIndex, m_meshInfo[meshIndex].vertex);
		m_meshInfo[meshIndex].indexBuffer = m_fbxInfo.meshes[meshIndex]->GetPolygonVertices();
		GetNormal(meshIndex, m_meshInfo[meshIndex].vertex);
		GetUVSetName(meshIndex);
		GetUV(meshIndex);
		
		GetTextureInfo(meshIndex);
		LoadTexture(meshIndex);
		CreateVertexBuffer(meshIndex);
		CreateIndexBuffer(meshIndex);
		SetVertexBuffer(meshIndex);
		SetIndexBuffer(meshIndex);
	}
	
}

int Fbx::GetPolygonCount(int meshIndex) {
	return m_fbxInfo.meshes[meshIndex]->GetPolygonCount();
}

int Fbx::GetVertexCount(int meshIndex) {
	return m_fbxInfo.meshes[meshIndex]->GetControlPointsCount();
}

int Fbx::GetIndexCount(int meshIndex) {
	return m_fbxInfo.meshes[meshIndex]->GetPolygonVertexCount();
}

void Fbx::GetVertex(int meshIndex, VERTEX_3D* vertex) {
	//���b�V���Ɋ܂܂�钸�_���W���擾
	FbxVector4* vtx = m_fbxInfo.meshes[meshIndex]->GetControlPoints();
	for (int vIdx = 0; vIdx < m_meshInfo[meshIndex].vertexCount; vIdx++)
	{
		vertex[vIdx].pos.x = (float)vtx[vIdx][0];
		vertex[vIdx].pos.y = (float)vtx[vIdx][1];
		vertex[vIdx].pos.z = (float)vtx[vIdx][2];
		if ((float)vtx[vIdx][0] < m_min.x)m_min.x = (float)vtx[vIdx][0];
		if ((float)vtx[vIdx][0] > m_max.x)m_max.x = (float)vtx[vIdx][0];
		if ((float)vtx[vIdx][1] < m_min.y)m_min.y = (float)vtx[vIdx][1];
		if ((float)vtx[vIdx][1] > m_max.y)m_max.y = (float)vtx[vIdx][1];
		if ((float)vtx[vIdx][2] < m_min.z)m_min.z = (float)vtx[vIdx][2];
		if ((float)vtx[vIdx][2] > m_max.z)m_max.z = (float)vtx[vIdx][2];
	}
}

void Fbx::GetNormal(int meshIndex, VERTEX_3D* vertex) {
	FbxArray<FbxVector4> normals;
	//�@�����擾
	m_fbxInfo.meshes[meshIndex]->GetPolygonVertexNormals(normals);
	//�@���̐����擾
	int normalCount = normals.Size();
	for (int i = 0; i < normalCount; i++)
	{
		//���_�C���f�b�N�X�ɑΉ��������_�ɒl����
		vertex[m_meshInfo[meshIndex].indexBuffer[i]].nor.x = normals[i][0];
		vertex[m_meshInfo[meshIndex].indexBuffer[i]].nor.y = normals[i][1];
		vertex[m_meshInfo[meshIndex].indexBuffer[i]].nor.z = normals[i][2];
	}
}

void Fbx::GetUVSetName(int meshIndex) {
	FbxStringList uvsetName;
	//���b�V���Ɋ܂܂��UVSet�������ׂĎ擾
	m_fbxInfo.meshes[meshIndex]->GetUVSetNames(uvsetName);
	//UVSet�̐����擾
	m_meshInfo[meshIndex].uvSetCount = m_fbxInfo.meshes[meshIndex]->GetUVLayerCount();
	/*�e�N�X�`���֌W�̃������m��*/
	TextureMemoryAllocate(meshIndex);
	for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
	{
		//UVSet�����擾
		m_meshInfo[meshIndex].uvSetName[i] = uvsetName[i];
	}
}

void Fbx::GetUV(int meshIndex) {
	FbxArray<FbxVector2> uvsets;
	FbxStringList uvsetName;
	m_fbxInfo.meshes[meshIndex]->GetUVSetNames(uvsetName);
	//UV���擾
	m_fbxInfo.meshes[meshIndex]->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);
	//UV�̐����擾
	int uvsetCount = uvsets.Size();
	for (int i = 0; i < uvsetCount; i++)
	{
		//���_�C���f�b�N�X�ɑΉ��������_�ɒl����
		m_meshInfo[meshIndex].vertex[m_meshInfo[meshIndex].indexBuffer[i]].tex.x = uvsets[i][0];
		m_meshInfo[meshIndex].vertex[m_meshInfo[meshIndex].indexBuffer[i]].tex.y = uvsets[i][1];
	}
}

void Fbx::GetMaterial() {
	//�}�e���A���̐����擾
	m_fbxInfo.materialCount = m_scene->GetMaterialCount();
	m_fbxInfo.material.reserve(m_fbxInfo.materialCount);
	for (int i = 0; i < m_fbxInfo.materialCount; i++)
	{
		//�}�e���A�����擾
		m_fbxInfo.material.emplace_back(m_scene->GetMaterial(i));
	}
}

void Fbx::GetTextureInfo(int meshIndex) {
	int uvIndex = 0;
	int currentIndex = m_fbxInfo.uvSetCount;
	for (int matIndex = 0; matIndex < m_fbxInfo.materialCount; matIndex++)
	{
		//diffuse�̏����擾
		FbxProperty prop = m_fbxInfo.material[matIndex]->FindProperty(FbxSurfaceMaterial::sDiffuse);
		//���C���e�N�X�`���̐����擾����
		int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

		//���C���e�N�X�`���𗘗p���Ă���ꍇ
		if (0 < layeredTextureCount) 
		{
			for (int j = 0; layeredTextureCount > j; j++) {

				//���C���e�N�X�`�����擾����
				FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
				//�e�N�X�`���̐����擾����
				int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

				for (int k = 0; textureCount > k; k++) 
				{
					//�e�N�X�`�����擾����
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

					if (texture) 
					{
						//�e�N�X�`�������擾����
						std::string textureName = texture->GetRelativeFileName();

						//UVSet�����擾����
						std::string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ�����
						for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
						{
							if (m_meshInfo[meshIndex].uvSetName[i] == UVSetName) {
								//�����Ɛݒ肵�Ă��Ȃ��̂Ńt�@�C���܂ł̃p�X��ǉ����Ă��܂�
								std::string a = "Models/test/";
								m_meshInfo[meshIndex].texturePath.emplace_back(a + textureName);
								//�e�N�X�`����UVSet�����擾����
								m_fbxInfo.uvSetName[uvIndex + currentIndex] = UVSetName;
								uvIndex++;
							}
						}
						
					}
				}
			}
		}
		//���C���e�N�X�`���𗘗p���Ă��Ȃ��ꍇ
		else {
			//�e�N�X�`�������擾����
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

			if (0 < fileTextureCount) 
			{
				for (int j = 0; fileTextureCount > j; j++) 
				{
					//�e�N�X�`�����擾����
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
					if (texture) 
					{
						//�e�N�X�`�������擾����
						std::string textureName = texture->GetFileName();
						textureName = textureName.substr(textureName.find_last_of('/') + 1);
						textureName = "Asset/Texture/" + textureName;
						//std::string textureName = texture->GetRelativeFileName();

						//UVSet�����擾����
						std::string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ�����
						for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
						{
							//int count = 0;
							if (m_meshInfo[meshIndex].uvSetName[i] == UVSetName) 
							{
								/*count++;
								int j;
								for (j = 0; j < currentIndex + count; j++)
								{
									if (m_fbxInfo.uvSetName[j] == UVSetName)
									{
										break;
									}
								}
								if (j == currentIndex + count)
								{*/
									m_meshInfo[meshIndex].texturePath.emplace_back(textureName);
									m_fbxInfo.uvSetName[uvIndex + currentIndex] = UVSetName;
									uvIndex++;
								//}
							}
						}
					}
				}
			}
		}
	}
	//UVSet�̐����擾����
	m_fbxInfo.uvSetCount += uvIndex;
}

bool Fbx::CreateVertexBuffer(int meshIndex) {
	HRESULT hr;
	if (FAILED(hr = m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_meshInfo[meshIndex].vertexCount,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_meshInfo[meshIndex].pVB,
		NULL)))									// NULL�ɐݒ�
	{
		return false;
	}
	return true;
}

bool Fbx::CreateIndexBuffer(int meshIndex) {
	HRESULT hr;
	if (FAILED(hr = m_pDevice->CreateIndexBuffer(sizeof(WORD)*m_meshInfo[meshIndex].indexCount,	//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y�i�f�[�^�P�ʁj
		D3DUSAGE_WRITEONLY,												//���_�o�b�t�@�̎g�p�@
		D3DFMT_INDEX16,													//�g�p����C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED,												//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_meshInfo[meshIndex].pIB,												//�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))															//NULL�ɐݒ�
	{
		return false;
	}
	return true;
}

void Fbx::SetVertexBuffer(int meshIndex) {
	VERTEX_3D* pVtx;
	m_meshInfo[meshIndex].pVB->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < m_meshInfo[meshIndex].vertexCount; i++)
	{
		pVtx[i].pos = m_meshInfo[meshIndex].vertex[i].pos;
		pVtx[i].nor = m_meshInfo[meshIndex].vertex[i].nor;
		pVtx[i].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[i].tex = m_meshInfo[meshIndex].vertex[i].tex;
	}
	m_meshInfo[meshIndex].pVB->Unlock();
}

void Fbx::SetIndexBuffer(int meshIndex) {
	WORD* pIdx;
	m_meshInfo[meshIndex].pIB->Lock(0, 0, (void**)&pIdx, 0);
	for (int i = 0; i < m_meshInfo[meshIndex].indexCount; i++)
	{
		pIdx[i] = m_meshInfo[meshIndex].indexBuffer[i];
	}
}

	void Fbx::TextureMemoryAllocate(int meshIndex) {
	m_meshInfo[meshIndex].uvSetName = new std::string[m_meshInfo[meshIndex].uvSetCount];
	m_meshInfo[meshIndex].texturePath.reserve(m_meshInfo[meshIndex].uvSetCount);
	m_meshInfo[meshIndex].texture = new LPDIRECT3DTEXTURE9[m_meshInfo[meshIndex].uvSetCount];
}

void Fbx::LoadTexture(int meshIndex) {
	for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
	{
		if (m_meshInfo[meshIndex].texturePath.size() > 0)
		{
			D3DXCreateTextureFromFile(m_pDevice, m_meshInfo[meshIndex].texturePath[i].c_str(), &m_meshInfo[meshIndex].texture[i]);
		}
	}
}

void Fbx::SetTexture(int meshIndex) {
	for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
	{
		for (int j = 0; j < m_fbxInfo.uvSetCount; j++)
		{
			//���b�V���ƃe�N�X�`����UVSet������v���Ă�����Ή������e�N�X�`����ݒ肷��
			if (m_meshInfo[meshIndex].uvSetName[i] == m_fbxInfo.uvSetName[j])
			{
				m_pDevice->SetTexture(0, m_meshInfo[meshIndex].texture[i]);
				return;
			}
		}
	}
	m_pDevice->SetTexture(0, 0);
}

int Fbx::GetUVSetNum() {
	int n = 0;
	for (int i = 0; i < m_fbxInfo.meshCount; i++)
	{
		n += m_fbxInfo.meshes[i]->GetUVLayerCount();

	}
	return n;
}

void Fbx::DrawModel() {
	D3DXMATRIX t, r, s, mat;
	D3DXMatrixIdentity(&t);
	D3DXMatrixIdentity(&r);
	D3DXMatrixIdentity(&s);
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&t, m_position.x, m_position.y, m_position.z);
	D3DXMatrixRotationYawPitchRoll(&r, m_rotation.y, m_rotation.x + 90.0f * (D3DX_PI / 180.0f), m_rotation.z);
	D3DXMatrixScaling(&s, m_scale.x * 0.1f, m_scale.y * 0.1f, m_scale.z * 0.1f);
	mat = s * r * t;
	m_pDevice->SetTransform(D3DTS_WORLD, &mat);
	for (int i = 0; i < m_fbxInfo.meshCount; i++)
	{
		m_pDevice->SetStreamSource(0, m_meshInfo[i].pVB, 0, sizeof(VERTEX_3D));
		m_pDevice->SetIndices(m_meshInfo[i].pIB);
		SetTexture(i);
		m_pDevice->SetFVF(FVF_VERTEX_3D);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshInfo[i].indexCount, 0, m_meshInfo[i].polygonCount);
		PrintFile();
	}
}

void Fbx::DrawAnimation()
{
	UpdateTime();

	FbxNode* pNode = m_scene->GetRootNode();
	// <�ړ��A��]�A�g��̂��߂̍s����쐬>
	FbxMatrix globalPosition = pNode->EvaluateGlobalTransform(m_timeCount);
	FbxVector4 t0 = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 r0 = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 s0 = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	FbxAMatrix geometryOffset = FbxAMatrix(t0, r0, s0);

	for (int i = 0; i < m_fbxInfo.meshCount; i++)
	{

		// <�e���_�Ɋ|���邽�߂̍ŏI�I�ȍs��̔z��>
		FbxMatrix *clusterDeformation = new FbxMatrix[m_fbxInfo.meshes[i]->GetControlPointsCount()];
		memset(clusterDeformation, 0, sizeof(FbxMatrix) * m_fbxInfo.meshes[i]->GetControlPointsCount());
		//�S�ẴN���X�^��񂪓���
		FbxSkin *skinDeformer = (FbxSkin *)m_fbxInfo.meshes[i]->GetDeformer(0, FbxDeformer::eSkin);
		if (skinDeformer)
		{
			int clusterCount = skinDeformer->GetClusterCount();

			// <�e�N���X�^����e���_�ɉe����^���邽�߂̍s��쐬>
			for (int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++) {
				// <�N���X�^(�{�[��)�̎��o��>
				FbxCluster *cluster = skinDeformer->GetCluster(clusterIndex);
				FbxMatrix vertexTransformMatrix;
				FbxAMatrix referenceGlobalInitPosition;
				FbxAMatrix clusterGlobalInitPosition;
				FbxMatrix clusterGlobalCurrentPosition;
				FbxMatrix clusterRelativeInitPosition;
				FbxMatrix clusterRelativeCurrentPositionInverse;
				cluster->GetTransformMatrix(referenceGlobalInitPosition);
				referenceGlobalInitPosition *= geometryOffset;
				cluster->GetTransformLinkMatrix(clusterGlobalInitPosition);
				clusterGlobalCurrentPosition = cluster->GetLink()->EvaluateGlobalTransform(m_timeCount);
				clusterRelativeInitPosition = clusterGlobalInitPosition.Inverse() * referenceGlobalInitPosition;
				clusterRelativeCurrentPositionInverse = globalPosition.Inverse() * clusterGlobalCurrentPosition;
				vertexTransformMatrix = clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;
				// <��ō�����s��Ɋe���_���̉e���x(�d��)���|���Ă��ꂼ��ɉ��Z>
				for (int cnt = 0; cnt < cluster->GetControlPointIndicesCount(); cnt++) {
					int index = cluster->GetControlPointIndices()[cnt];
					double weight = cluster->GetControlPointWeights()[cnt];
					FbxMatrix influence = vertexTransformMatrix * weight;
					clusterDeformation[index] += influence;
				}
			}


			// <�ŏI�I�Ȓ��_���W���v�Z��VERTEX�ɕϊ�>
			for (int cnt = 0; cnt < m_meshInfo[i].vertexCount; cnt++) {
				FbxVector4 outVertex = clusterDeformation[cnt].MultNormalize(m_fbxInfo.meshes[i]->GetControlPointAt(cnt));
				float x = (FLOAT)outVertex[0];
				float y = (FLOAT)outVertex[1];
				float z = (FLOAT)outVertex[2];

				m_meshInfo[i].vertex[cnt].pos.x = x;
				m_meshInfo[i].vertex[cnt].pos.y = y;
				m_meshInfo[i].vertex[cnt].pos.z = z;
			}
			delete[] clusterDeformation;
		}
		SetVertexBuffer(i);
		D3DXMATRIX t, r, s, mat;
		D3DXMatrixIdentity(&t);
		D3DXMatrixIdentity(&r);
		D3DXMatrixIdentity(&s);
		D3DXMatrixIdentity(&mat);
		D3DXMatrixTranslation(&t, m_position.x, m_position.y, m_position.z);
		D3DXMatrixRotationYawPitchRoll(&r, m_rotation.y, m_rotation.x, m_rotation.z);
		D3DXMatrixScaling(&s, m_scale.x, m_scale.y, m_scale.z);
		mat = s * r * t;
		m_pDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pDevice->SetStreamSource(0, m_meshInfo[i].pVB, 0, sizeof(VERTEX_3D));
		m_pDevice->SetIndices(m_meshInfo[i].pIB);
		SetTexture(i);
		m_pDevice->SetFVF(FVF_VERTEX_3D);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshInfo[i].indexCount, 0, m_meshInfo[i].polygonCount);
		//PrintFile();
	}
}

void Fbx::SetTranslation(float x, float y, float z) {
	m_position = D3DXVECTOR3(x, y, z);
}

void Fbx::SetTranslation(D3DXVECTOR3 pos) {
	m_position = pos;
}

void Fbx::SetRotationX(float angle) {
	m_rotation.x = angle;
}

void Fbx::SetRotationY(float angle) {
	m_rotation.y = angle;
}

void Fbx::SetRotationZ(float angle) {
	m_rotation.z = angle;
}

void Fbx::SetRotation(float x, float y, float z) {
	m_rotation = D3DXVECTOR3(x, y, z);
}

void Fbx::SetRotation(D3DXVECTOR3 rot) {
	m_rotation = rot;
}

void Fbx::SetScaling(float scale) {
	m_scale = D3DXVECTOR3(scale, scale, scale);
}

void Fbx::SetScaling(float scaleX, float scaleY, float scaleZ) {
	m_scale = D3DXVECTOR3(scaleX, scaleY, scaleZ);
}

OBB& Fbx::GetOBB()const {
	if (m_isaabb) 
	{
		MessageBox(NULL, "OBB is disable", NULL, MB_OK);

	}
	return *m_obb;
}

AABB& Fbx::GetAABB()const {
	if (!m_isaabb)
	{
		MessageBox(NULL, "AABB is disable", NULL, MB_OK);

	}
	return *m_aabb;
}

void Fbx::UpdateTime() {
	if (m_isMove)
	{
		//�A�j���[�V�����̎��ԍX�V
		m_timeCount += m_frameTime;
		if (m_timeCount > m_stop)
		{
			//���s�����������ɂȂ���^�C�~���O
			m_timeCount = m_stop * 3 / 28;
		}
	}
	else
	{
		m_timeCount = m_start;
	}
}

void Fbx::Move(bool b) {
	m_isMove = b;
}



void Fbx::PrintFile() {
	//std::string filename = "testUV.txt";
	std::string filename = "testPos.txt";
	std::ofstream writing_file;
	writing_file.open(filename, std::ios::out);
	int count = 0;

	for (int i = 0; i < m_meshInfo[0].vertexCount; i++)
	{
		writing_file << "x:" << m_meshInfo[0].vertex[i].pos.x << " y:" << m_meshInfo[0].vertex[i].pos.y << " z:" << m_meshInfo[0].vertex[i].pos.z << std::endl;
	}
}