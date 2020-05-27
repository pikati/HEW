#define _CRT_SECURE_NO_WARNINGS
#include "Fbx.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Utility.h"

#define FRAME 0.0166666666666667

static LPDIRECT3DTEXTURE9 tex;


void Start(LARGE_INTEGER *start);
void End(LARGE_INTEGER *start, LARGE_INTEGER *end, LARGE_INTEGER *f);

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
		/*else
		{
			m_obb = new OBB;
			m_obb->Initialize();
		}*/
	}
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_max = D3DXVECTOR3(-10000, -10000, -10000);
	m_min = D3DXVECTOR3(10000, 10000, 10000);
	m_manager = FbxManager::Create();
	m_fbxInfo.uvSetCount = 0;
	testCount = 0; 
	m_frame = 0;
	m_count = 0;
	D3DXCreateTextureFromFile(m_pDevice, "Asset/Texture/player2.png", &tex);
}

void Fbx::Update() {
	if (m_isCollison)
	{
		if (m_isaabb)
		{
			m_aabb->Update(m_position);
		}
		/*else
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
		}*/
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
	//if (m_isCollison)
	//{
	//	if (m_isaabb)
	//	{
	//		m_aabb->Draw();
	//	}
	//	else
	//	{
	//		m_obb->Draw();
	//	}
	//}
}

void Fbx::Finalize() {
	for (int meshIndex = m_fbxInfo.meshCount - 1; meshIndex >= 0; meshIndex--)
	{
		for (int i = m_meshInfo[meshIndex].uvSetCount - 1; i >= 0; i--)
		{
			//SAFE_RELEASE(m_meshInfo[meshIndex].texture[i]);
			SAFE_RELEASE(tex);
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
		/*else {
			m_obb->CreateOBB(m_meshInfo, m_fbxInfo.meshCount);
		}*/
	}
	SetAnimationVertex();
	//SetSkinDeformer();
}

void Fbx::LoadFBX(const char* filePath) {
	if (NULL != m_manager) {
		//インポーター作成
		FbxImporter* importer = FbxImporter::Create(m_manager, "");

		if (NULL != importer) {
			//シーン作成
			m_scene = FbxScene::Create(m_manager, "");

			if (NULL != m_scene) {
				//filePathに指定したファイルを読み込む
				bool result = importer->Initialize(filePath);

				if (result) {
					//シーンにインポートしたファイルを渡す
					importer->Import(m_scene);
				}
				else
				{
					MessageBox(NULL, "ファイルパス間違ってるかもよ", NULL, MB_OK);
				}
			}
		}
		//インポーターの役目は終わりなので解放する
		importer->Destroy();
	}
}

void Fbx::InitializeFBX() {
	MeshTrianglate();
	//InitializeUnit();
	m_fbxInfo.meshes = GetMesh();
	SetInfomation();
}

void Fbx::InitializeAnimation(bool isAnimation) {
	if (isAnimation)
	{
		m_isAnim = true;
		/*アニメーションの選択および設定*/
		FbxArray<FbxString*> AnimStackNameArray;
		//アニメーションの名前一覧を取得
		m_scene->FillAnimStackNameArray(AnimStackNameArray);
		m_animationStackNumber = m_scene->GetSrcObjectCount<FbxAnimStack>();
		//m_animationStackNumber番目のアニメーション情報を取得
		if (m_animationStackNumber == 0)
		{
			m_isAnim = false;
			return;
		}
		FbxAnimStack *AnimationStack = m_scene->FindMember<FbxAnimStack>(AnimStackNameArray[m_animationStackNumber - 1]->Buffer());
		//アニメーションを設定
		m_scene->SetCurrentAnimationStack(AnimationStack);

		/*アニメーションを行う上で必要な時間関係の値を取得*/
		//アニメーション情報の取得
		FbxTakeInfo *takeInfo = m_scene->GetTakeInfo(*(AnimStackNameArray[m_animationStackNumber - 1]));
		//開始時間
		m_start = takeInfo->mLocalTimeSpan.GetStart();
		//終了時間
		m_stop = takeInfo->mLocalTimeSpan.GetStop();
		//アニメーション１コマが実行されていく時間情報を保持する 時間のカウント方法を設定
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
		// センチメーター単位にコンバートする。
		FbxSystemUnit::cm.ConvertScene(m_scene);
	}
}

std::vector<FbxMesh*> Fbx::GetMesh() {
	//メッシュの数を取得
	m_fbxInfo.meshCount = m_scene->GetSrcObjectCount<FbxMesh>();
	std::vector<FbxMesh*> meshes;
	for (int i = 0; i < m_fbxInfo.meshCount; ++i)
	{
		//i番目のメッシュを取得
		FbxMesh* mesh = m_scene->GetSrcObject<FbxMesh>(i);
		meshes.emplace_back(mesh);
	}
	return meshes;
}

void Fbx::SetInfomation() {
	//メモリ確保
	m_fbxInfo.uvSetName = new std::string[GetUVSetNum()];
	m_meshInfo = new MeshInfo[m_fbxInfo.meshCount];
	GetMaterial();
	//それぞれの値取得
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
		
		//GetTextureInfo(meshIndex);
		//LoadTexture(meshIndex);
		CreateVertexBuffer(meshIndex);
		CreateIndexBuffer(meshIndex);
		//SetVertexBuffer(meshIndex);
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
	//メッシュに含まれる頂点座標を取得
	FbxVector4* vtx = m_fbxInfo.meshes[meshIndex]->GetControlPoints();
	for (int vIdx = 0; vIdx < m_meshInfo[meshIndex].vertexCount; vIdx++)
	{
		vertex[vIdx].pos.x = (float)vtx[vIdx][0];
		vertex[vIdx].pos.y = (float)vtx[vIdx][1];
		vertex[vIdx].pos.z = (float)vtx[vIdx][2];
		if ((float)vtx[vIdx][0] * m_scale.x < m_min.x)m_min.x = (float)vtx[vIdx][0] * m_scale.x;
		if ((float)vtx[vIdx][0] * m_scale.x > m_max.x)m_max.x = (float)vtx[vIdx][0] * m_scale.x;
		if ((float)vtx[vIdx][1] * m_scale.y < m_min.y)m_min.y = (float)vtx[vIdx][1] * m_scale.y;
		if ((float)vtx[vIdx][1] * m_scale.y > m_max.y)m_max.y = (float)vtx[vIdx][1] * m_scale.y;
		if ((float)vtx[vIdx][2] * m_scale.z < m_min.z)m_min.z = (float)vtx[vIdx][2] * m_scale.z;
		if ((float)vtx[vIdx][2] * m_scale.z > m_max.z)m_max.z = (float)vtx[vIdx][2] * m_scale.z;
	}
}

void Fbx::GetNormal(int meshIndex, VERTEX_3D* vertex) {
	FbxArray<FbxVector4> normals;
	//法線を取得
	m_fbxInfo.meshes[meshIndex]->GetPolygonVertexNormals(normals);
	//法線の数を取得
	int normalCount = normals.Size();
	for (int i = 0; i < normalCount; i++)
	{
		//頂点インデックスに対応した頂点に値を代入
		vertex[m_meshInfo[meshIndex].indexBuffer[i]].nor.x = normals[i][0];
		vertex[m_meshInfo[meshIndex].indexBuffer[i]].nor.y = normals[i][1];
		vertex[m_meshInfo[meshIndex].indexBuffer[i]].nor.z = normals[i][2];
	}
}

void Fbx::GetUVSetName(int meshIndex) {
	FbxStringList uvsetName;
	//メッシュに含まれるUVSet名をすべて取得
	m_fbxInfo.meshes[meshIndex]->GetUVSetNames(uvsetName);
	//UVSetの数を取得
	m_meshInfo[meshIndex].uvSetCount = m_fbxInfo.meshes[meshIndex]->GetUVLayerCount();
	/*テクスチャ関係のメモリ確保*/
	TextureMemoryAllocate(meshIndex);
	for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
	{
		//UVSet名を取得
		m_meshInfo[meshIndex].uvSetName[i] = uvsetName[i];
	}
}

void Fbx::GetUV(int meshIndex) {
	FbxArray<FbxVector2> uvsets;
	FbxStringList uvsetName;
	m_fbxInfo.meshes[meshIndex]->GetUVSetNames(uvsetName);
	//UVを取得
	m_fbxInfo.meshes[meshIndex]->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);
	//UVの数を取得
	int uvsetCount = uvsets.Size();
	for (int i = 0; i < uvsetCount; i++)
	{
		//頂点インデックスに対応した頂点に値を代入
		m_meshInfo[meshIndex].vertex[m_meshInfo[meshIndex].indexBuffer[i]].tex.x = uvsets[i][0];
		m_meshInfo[meshIndex].vertex[m_meshInfo[meshIndex].indexBuffer[i]].tex.y = 1.0f - uvsets[i][1];
	}
}

void Fbx::GetMaterial() {
	//マテリアルの数を取得
	m_fbxInfo.materialCount = m_scene->GetMaterialCount();
	m_fbxInfo.material.reserve(m_fbxInfo.materialCount);
	for (int i = 0; i < m_fbxInfo.materialCount; i++)
	{
		//マテリアルを取得
		m_fbxInfo.material.emplace_back(m_scene->GetMaterial(i));
	}
}

void Fbx::GetTextureInfo(int meshIndex) {
	int uvIndex = 0;
	int currentIndex = m_fbxInfo.uvSetCount;
	for (int matIndex = 0; matIndex < m_fbxInfo.materialCount; matIndex++)
	{
		//diffuseの情報を取得
		FbxProperty prop = m_fbxInfo.material[matIndex]->FindProperty(FbxSurfaceMaterial::sDiffuse);
		//レイヤテクスチャの数を取得する
		int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

		//レイヤテクスチャを利用している場合
		if (0 < layeredTextureCount) 
		{
			for (int j = 0; layeredTextureCount > j; j++) {

				//レイヤテクスチャを取得する
				FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
				//テクスチャの数を取得する
				int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

				for (int k = 0; textureCount > k; k++) 
				{
					//テクスチャを取得する
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

					if (texture) 
					{
						//テクスチャ名を取得する
						std::string textureName = texture->GetRelativeFileName();

						//UVSet名を取得する
						std::string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet名を比較し対応しているテクスチャなら保持する
						for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
						{
							if (m_meshInfo[meshIndex].uvSetName[i] == UVSetName) {
								//ちゃんと設定していないのでファイルまでのパスを追加しています
								std::string a = "Models/test/";
								m_meshInfo[meshIndex].texturePath.emplace_back(a + textureName);
								//テクスチャのUVSet名を取得する
								m_fbxInfo.uvSetName[uvIndex + currentIndex] = UVSetName;
								uvIndex++;
							}
						}
						
					}
				}
			}
		}
		//レイヤテクスチャを利用していない場合
		else {
			//テクスチャ数を取得する
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

			/*HEWPlayer動かすとき トライアングレイト忘れずに*/
			if (0 < fileTextureCount) 
			{
				for (int j = 0; fileTextureCount > j; j++) 
				{
					//テクスチャを取得する
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
					if (texture) 
					{
						//テクスチャ名を取得する
						std::string textureName = texture->GetFileName();
						textureName = textureName.substr(textureName.find_last_of('/') + 1);
						textureName = "Asset/Texture/" + textureName;
						//std::string textureName = texture->GetRelativeFileName();

						//UVSet名を取得する
						std::string UVSetName = texture->UVSet.Get().Buffer();

						//UVSet名を比較し対応しているテクスチャなら保持する
						for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
						{
							/*int count = 0;
							if (m_meshInfo[meshIndex].uvSetName[i] == UVSetName) 
							{
								count++;
								int j;
								for (j = 0; j < currentIndex + count; j++)
								{
									if (m_fbxInfo.uvSetName[j] == UVSetName)
									{
										break;
									}
								}
								if (j == currentIndex + count)
								{
									m_meshInfo[meshIndex].texturePath.emplace_back(textureName);
									m_fbxInfo.uvSetName[uvIndex + currentIndex] = UVSetName;
									uvIndex++;
								}
							}*/
							m_meshInfo[meshIndex].texturePath.emplace_back(textureName);
							m_fbxInfo.uvSetName[uvIndex + currentIndex] = UVSetName;
							uvIndex++;
						}
					}
				}
			}

			/*girl読み込むとき*/
			//if (0 < fileTextureCount)
			//{
			//	for (int j = 0; fileTextureCount > j; j++)
			//	{
			//		//テクスチャを取得する
			//		FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
			//		if (texture)
			//		{
			//			//テクスチャ名を取得する
			//			std::string textureName = texture->GetFileName();
			//			textureName = textureName.substr(textureName.find_last_of('/') + 1);
			//			textureName = "Asset/Texture/" + textureName;
			//			//std::string textureName = texture->GetRelativeFileName();

			//			//UVSet名を取得する
			//			std::string UVSetName = texture->UVSet.Get().Buffer();

			//			//UVSet名を比較し対応しているテクスチャなら保持する
			//			for (int i = 0; i < m_meshInfo[meshIndex].uvSetCount; i++)
			//			{
			//				int count = 0;
			//				if (m_meshInfo[meshIndex].uvSetName[i] == UVSetName)
			//				{
			//					count++;
			//					int j;
			//					for (j = 0; j < currentIndex + count; j++)
			//					{
			//						if (m_fbxInfo.uvSetName[j] == UVSetName)
			//						{
			//							break;
			//						}
			//					}
			//					if (j == currentIndex + count)
			//					{
			//						m_meshInfo[meshIndex].texturePath.emplace_back(textureName);
			//						m_fbxInfo.uvSetName[uvIndex + currentIndex] = UVSetName;
			//						uvIndex++;
			//					}
			//				}
			//			}
			//		}
			//	}
			//}

		}
	}
	//UVSetの数を取得する
	m_fbxInfo.uvSetCount += uvIndex;
}

bool Fbx::CreateVertexBuffer(int meshIndex) {
	HRESULT hr;
	if (FAILED(hr = m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_meshInfo[meshIndex].vertexCount,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_meshInfo[meshIndex].pVB,
		NULL)))									// NULLに設定
	{
		return false;
	}
	return true;
}

bool Fbx::CreateIndexBuffer(int meshIndex) {
	HRESULT hr;
	if (FAILED(hr = m_pDevice->CreateIndexBuffer(sizeof(WORD)*m_meshInfo[meshIndex].indexCount,	//頂点データ用に確保するバッファサイズ（データ単位）
		D3DUSAGE_WRITEONLY,												//頂点バッファの使用法
		D3DFMT_INDEX16,													//使用するインデックスフォーマット
		D3DPOOL_MANAGED,												//リソースのバッファを保持するメモリクラスを指定
		&m_meshInfo[meshIndex].pIB,												//インデックスバッファインターフェースへのポインタ
		NULL)))															//NULLに設定
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
		//pVtx[i].pos = m_meshInfo[meshIndex].vertex[i].pos;
		pVtx[i].pos = m_animVertex[meshIndex][m_frame][i];
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
			//メッシュとテクスチャのUVSet名が一致していたら対応したテクスチャを設定する
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
		//PrintFile();
	}
}

void Fbx::DrawAnimation()
{

	UpdateTime();
	/*if (testCount == 2)
	{
		testCount++;
		return;
	}
	else if (testCount == 3)
	{
		testCount = 0;
		return;
	}*/
	//LARGE_INTEGER freq;
	//QueryPerformanceFrequency(&freq);

	//LARGE_INTEGER start;
	//LARGE_INTEGER end;

	//FbxNode* pNode = m_scene->GetRootNode();//0.0029

	//// <移動、回転、拡大のための行列を作成>
	//FbxMatrix globalPosition = pNode->EvaluateGlobalTransform(m_timeCount);//0.6313
	//FbxVector4 t0 = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);//0.0024
	//FbxVector4 r0 = pNode->GetGeometricRotation(FbxNode::eSourcePivot);//0.0020
	//FbxVector4 s0 = pNode->GetGeometricScaling(FbxNode::eSourcePivot);//0.0017
	//FbxAMatrix geometryOffset = FbxAMatrix(t0, r0, s0);//0.0081
	for (int i = 0; i < m_fbxInfo.meshCount; i++)
	{

		// <各頂点に掛けるための最終的な行列の配列>

		//FbxMatrix *clusterDeformation = new FbxMatrix[m_fbxInfo.meshes[i]->GetControlPointsCount()];//1.9053
		//memset(clusterDeformation, 0, sizeof(FbxMatrix) * m_fbxInfo.meshes[i]->GetControlPointsCount());//0.0167
		////全てのクラスタ情報が入る
		//FbxSkin *skinDeformer = (FbxSkin *)m_fbxInfo.meshes[i]->GetDeformer(0, FbxDeformer::eSkin);//0.0220
		//if (skinDeformer)
		//{
		//	int clusterCount = skinDeformer->GetClusterCount();//0.0492
		//	// <各クラスタから各頂点に影響を与えるための行列作成>
		//	for (int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++) {
		//		// <クラスタ(ボーン)の取り出し>
		//		FbxCluster *cluster = skinDeformer->GetCluster(clusterIndex);//0.0321
		//		FbxMatrix vertexTransformMatrix;//0.0063
		//		FbxAMatrix referenceGlobalInitPosition;//0.0042
		//		FbxAMatrix clusterGlobalInitPosition;//0.0042
		//		FbxMatrix clusterGlobalCurrentPosition;//0.0063
		//		FbxMatrix clusterRelativeInitPosition;//0.0039
		//		FbxMatrix clusterRelativeCurrentPositionInverse;//0.0095
		//		cluster->GetTransformMatrix(referenceGlobalInitPosition);//0.0595
		//		referenceGlobalInitPosition *= geometryOffset;//0.0035
		//		cluster->GetTransformLinkMatrix(clusterGlobalInitPosition);//0.0566
		//		clusterGlobalCurrentPosition = cluster->GetLink()->EvaluateGlobalTransform(m_timeCount);//2.0852
		//		clusterRelativeInitPosition = clusterGlobalInitPosition.Inverse() * referenceGlobalInitPosition;//0.0378
		//		clusterRelativeCurrentPositionInverse = globalPosition.Inverse() * clusterGlobalCurrentPosition;//0.0705
		//		vertexTransformMatrix = clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;//0.0203
		//		// <上で作った行列に各頂点毎の影響度(重み)を掛けてそれぞれに加算>
		//		for (int cnt = 0; cnt < cluster->GetControlPointIndicesCount(); cnt++) {
		//			int index = cluster->GetControlPointIndices()[cnt];//0.0019
		//			double weight = cluster->GetControlPointWeights()[cnt];//0.0013
		//			FbxMatrix influence = vertexTransformMatrix * weight;//0.0058
		//			clusterDeformation[index] += influence;//0.0020
		//		}
		//	}


		//	// <最終的な頂点座標を計算しVERTEXに変換>
		//	for (int cnt = 0; cnt < m_meshInfo[i].vertexCount; cnt++) {
		//		FbxVector4 outVertex = clusterDeformation[cnt].MultNormalize(m_fbxInfo.meshes[i]->GetControlPointAt(cnt));
		//		float x = (FLOAT)outVertex[0];
		//		float y = (FLOAT)outVertex[1];
		//		float z = (FLOAT)outVertex[2];

		//		m_meshInfo[i].vertex[cnt].pos.x = x;
		//		m_meshInfo[i].vertex[cnt].pos.y = y;
		//		m_meshInfo[i].vertex[cnt].pos.z = z;
		//	}
		//	//delete[] clusterDeformation;
		//}
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
		//SetTexture(i);
		m_pDevice->SetTexture(0, tex);

		m_pDevice->SetFVF(FVF_VERTEX_3D);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_meshInfo[i].indexCount, 0, m_meshInfo[i].polygonCount);
		//PrintFile();
	}
	//testCount++;
}

void Fbx::SetAnimationVertex() {
	double animationTime = m_start.GetSecondDouble();
	double stopTime = m_stop.GetSecondDouble();
	int count = 0;
	m_timeCount = m_start;
	m_animVertex.resize(m_fbxInfo.meshCount);

	while (animationTime <= stopTime)
	{
		count++;
		animationTime += FRAME;
	}

	m_count = count;

	for (int i = 0; i < m_fbxInfo.meshCount; i++)
	{
		m_animVertex[i].resize(count);
		for (int j = 0; j < count; j++)
		{
			m_animVertex[i][j].resize(m_meshInfo[i].vertexCount);
		}
	}

	int animCount = 0;

	while (animCount < count)
	{
		FbxNode* pNode = m_scene->GetRootNode();//0.0029
	// <移動、回転、拡大のための行列を作成>
		FbxMatrix globalPosition = pNode->EvaluateGlobalTransform(m_timeCount);//0.6313
		FbxVector4 t0 = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);//0.0024
		FbxVector4 r0 = pNode->GetGeometricRotation(FbxNode::eSourcePivot);//0.0020
		FbxVector4 s0 = pNode->GetGeometricScaling(FbxNode::eSourcePivot);//0.0017
		FbxAMatrix geometryOffset = FbxAMatrix(t0, r0, s0);//0.0081
		for (int i = 0; i < m_fbxInfo.meshCount; i++)
		{

			// <各頂点に掛けるための最終的な行列の配列>

			FbxMatrix* clusterDeformation = new FbxMatrix[m_fbxInfo.meshes[i]->GetControlPointsCount()];//1.9053
			memset(clusterDeformation, 0, sizeof(FbxMatrix) * m_fbxInfo.meshes[i]->GetControlPointsCount());//0.0167
			//全てのクラスタ情報が入る
			FbxSkin* skinDeformer = (FbxSkin*)m_fbxInfo.meshes[i]->GetDeformer(0, FbxDeformer::eSkin);//0.0220
			if (skinDeformer)
			{
				int clusterCount = skinDeformer->GetClusterCount();//0.0492
				// <各クラスタから各頂点に影響を与えるための行列作成>
				for (int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++) {
					// <クラスタ(ボーン)の取り出し>
					FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);//0.0321
					FbxMatrix vertexTransformMatrix;//0.0063
					FbxAMatrix referenceGlobalInitPosition;//0.0042
					FbxAMatrix clusterGlobalInitPosition;//0.0042
					FbxMatrix clusterGlobalCurrentPosition;//0.0063
					FbxMatrix clusterRelativeInitPosition;//0.0039
					FbxMatrix clusterRelativeCurrentPositionInverse;//0.0095
					cluster->GetTransformMatrix(referenceGlobalInitPosition);//0.0595
					referenceGlobalInitPosition *= geometryOffset;//0.0035
					cluster->GetTransformLinkMatrix(clusterGlobalInitPosition);//0.0566
					clusterGlobalCurrentPosition = cluster->GetLink()->EvaluateGlobalTransform(m_timeCount);//2.0852
					clusterRelativeInitPosition = clusterGlobalInitPosition.Inverse() * referenceGlobalInitPosition;//0.0378
					clusterRelativeCurrentPositionInverse = globalPosition.Inverse() * clusterGlobalCurrentPosition;//0.0705
					vertexTransformMatrix = clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;//0.0203
					// <上で作った行列に各頂点毎の影響度(重み)を掛けてそれぞれに加算>
					for (int cnt = 0; cnt < cluster->GetControlPointIndicesCount(); cnt++) {
						int index = cluster->GetControlPointIndices()[cnt];//0.0019
						double weight = cluster->GetControlPointWeights()[cnt];//0.0013
						FbxMatrix influence = vertexTransformMatrix * weight;//0.0058
						clusterDeformation[index] += influence;//0.0020
					}
				}


				// <最終的な頂点座標を計算しVERTEXに変換>
				for (int cnt = 0; cnt < m_meshInfo[i].vertexCount; cnt++) {
					FbxVector4 outVertex = clusterDeformation[cnt].MultNormalize(m_fbxInfo.meshes[i]->GetControlPointAt(cnt));
					float x = (FLOAT)outVertex[0];
					float y = (FLOAT)outVertex[1];
					float z = (FLOAT)outVertex[2];

					m_animVertex[i][animCount][cnt] = (D3DXVECTOR3(x, y, z));
					/*m_meshInfo[i].vertex[cnt].pos.x = x;
					m_meshInfo[i].vertex[cnt].pos.y = y;
					m_meshInfo[i].vertex[cnt].pos.z = z;*/
				}
				delete[] clusterDeformation;
			}
		}
		double timeCount = m_timeCount.GetSecondDouble();
		timeCount += FRAME;
		m_timeCount.SetSecondDouble(timeCount);
		animCount++;	
	}
}

void Fbx::SetSkinDeformer() {
	for(int i = 0; i < m_fbxInfo.meshCount; i++)
	{
		m_skinDeformer.push_back((FbxSkin*)m_fbxInfo.meshes[i]->GetDeformer(0, FbxDeformer::eSkin));
		if (m_skinDeformer[i])
		{
			int clusterCount = m_skinDeformer[i]->GetClusterCount();
			m_link.resize(clusterCount);
			for (int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++) 
			{
				FbxCluster* cluster = m_skinDeformer[i]->GetCluster(clusterIndex);//0.0321
				FbxNode* node = cluster->GetLink();
				m_link.push_back(node);
			}
		}
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
void Fbx::SetScaling(float scale) {
	m_scale = D3DXVECTOR3(scale, scale, scale);
}


void Fbx::SetScaling(float scaleX, float scaleY, float scaleZ) {
	m_scale = D3DXVECTOR3(scaleX, scaleY, scaleZ);
}

//OBB& Fbx::GetOBB()const {
//	if (m_isaabb) 
//	{
//		MessageBox(NULL, "OBB is disable", NULL, MB_OK);
//
//	}
//	/*return *m_obb;*/
//}

AABB& Fbx::GetAABB()const {
	if (!m_isaabb)
	{
		MessageBox(NULL, "AABB is disable", NULL, MB_OK);

	}
	return *m_aabb;
}

void Fbx::UpdateTime() {
	if (true)
	{
		//アニメーションの時間更新 Loopとか決めるならここ
		m_timeCount += m_frameTime;
		if (m_timeCount > m_stop)
		{
			m_timeCount = m_stop;
		}
		m_frame++;
		if (m_frame >= m_count)
		{
			m_frame = 0;
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
	std::string filename = "testUV.txt";
	std::ofstream writing_file;
	writing_file.open(filename, std::ios::out);
	int count = 0;

	for (int i = 0; i < m_meshInfo[0].vertexCount; i++)
	{
		writing_file << "x:" << m_meshInfo[0].vertex[i].pos.x << " y:" << m_meshInfo[0].vertex[i].pos.y << " z:" << m_meshInfo[0].vertex[i].pos.z << std::endl;
	}
}

void Start(LARGE_INTEGER *start) {
	QueryPerformanceCounter(start);
}

void End(LARGE_INTEGER *start, LARGE_INTEGER *end, LARGE_INTEGER *f){
	QueryPerformanceCounter(end);

	double time = static_cast<double>(end->QuadPart - start->QuadPart) * 1000.0 / f->QuadPart;
	MyOutputDebugString("time %lf[ms]\n\n", time);
}