#include "COBBTree.h"
#include <float.h>
#include "main.h"

static LPDIRECT3DDEVICE9 g_pd3dDevice;

COBBTree::COBBTree()
{
	pOBBTopNode = new OBBNODE;
}

COBBTree::~COBBTree()
{
	ReleaseNodes( pOBBTopNode );
}

void COBBTree::ReleaseNodes( OBBNODE *pOBBNode )
{
	if( pOBBNode->pOBBNodeL ) ReleaseNodes( pOBBNode->pOBBNodeL );
	if( pOBBNode->pOBBNodeR ) ReleaseNodes( pOBBNode->pOBBNodeR );

	delete pOBBNode;
	pOBBNode = NULL;
}

bool COBBTree::Create( LPD3DXMESH pMesh, int Level )
{
	// ���_�擾
	int VertexNum = pMesh->GetNumVertices();
	std::vector < D3DXVECTOR3 > Vertex;
	LPDIRECT3DVERTEXBUFFER9 pVB;
	pMesh->GetVertexBuffer( &pVB );

	D3DVERTEXBUFFER_DESC VDesc;
	pVB->GetDesc( &VDesc );
	int FVFSize = VDesc.Size / VertexNum;
	float *pf;
	pVB->Lock( 0, 0, (void**)&pf, D3DLOCK_DISCARD );
	for( int i = 0; i < VertexNum; ++i ){
		D3DXVECTOR3 Vec;
		Vec.x = *(pf++);
		Vec.y = *(pf++);
		Vec.z = *(pf++);
		Vertex.push_back( Vec );

		// ���_�t�H�[�}�b�g��float ��DWORD�̃f�[�^�����Ȃ��̂�4�o�C�g�P�ʂ�
		// �A�N�Z�X�\����( pf += ( FVFSize - 4 * 3 ) / 4 )
		// �O�̂��߃o�C�g�P�ʂŃA�N�Z�X����
		pf = (float *)( (char *)pf + ( FVFSize - 4 * 3 ) );
	}
	pVB->Unlock();

	// 3�p�|���S���擾
	int FaceNum = pMesh->GetNumFaces();
	FACES Faces;
	LPDIRECT3DINDEXBUFFER9 pIB;
	pMesh->GetIndexBuffer( &pIB );

	D3DINDEXBUFFER_DESC IDesc;
	pIB->GetDesc( &IDesc );

	if( IDesc.Format == D3DFMT_INDEX16 ){
		WORD *pw;
		pIB->Lock( 0, 0, (void**)&pw, D3DLOCK_DISCARD );
		for( int i = 0; i < FaceNum; ++i ){
			FACE Face;
			Face.Vertex[0] = Vertex[*(pw++)];
			Face.Vertex[1] = Vertex[*(pw++)];
			Face.Vertex[2] = Vertex[*(pw++)];
			Face.Center = ( Face.Vertex[0] + Face.Vertex[1] + Face.Vertex[2] ) / 3;
			Faces.push_back( Face );
		}
		pIB->Unlock();
	}
	else if( IDesc.Format == D3DFMT_INDEX32 ){ // �ő��ɑ��݂��Ȃ��Ƃ͎v�����O�̂���
		DWORD *pd;
		pIB->Lock( 0, 0, (void**)&pd, D3DLOCK_DISCARD );
		for( int i = 0; i < FaceNum; ++i ){
			FACE Face;
			Face.Vertex[0] = Vertex[*(pd++)];
			Face.Vertex[1] = Vertex[*(pd++)];
			Face.Vertex[2] = Vertex[*(pd++)];
			Face.Center = ( Face.Vertex[0] + Face.Vertex[1] + Face.Vertex[2] ) / 3;
			Faces.push_back( Face );
		}
		pIB->Unlock();
	}
	else return false;

	Create( Faces, Level, pOBBTopNode );
	
	return true;
}

void COBBTree::Create( FACES &Faces, int Level, OBBNODE *pOBBNode )
{
	CreateOBB( Faces, pOBBNode->OBBData );

	// �Œ��̎��̒��S�ɑ΂��ĎO�p�|���S�����E�ɂ��邩���ɂ��邩�؂蕪����
	// �Œ��̎��Ń|���S���Q���܂����������ł��Ȃ��ꍇ�͕ʂ̎��ōă`�������W
	FACES FacesL, FacesR;
	for( int j = 0; j < 3; ++j ){
		FacesL.clear();
		FacesR.clear();
		for( int i = 0; i < (int)Faces.size(); ++i ){
			D3DXVECTOR4 Vec4;
			D3DXVec3Transform( &Vec4, &Faces[i].Center, &pOBBNode->OBBData.Matrix );
			float v[3] = { Vec4.x, Vec4.y, Vec4.z };

			if( v[j] < pOBBNode->OBBData.Length[j] / 2 ) FacesL.push_back( Faces[i] );
			else FacesR.push_back( Faces[i] );
		}
		if( FacesL.size() > 0 && FacesR.size() > 0 ) break;
	}

	--Level;
	if( Level < 0 ) return;

	if( FacesL.size() > 0 ){
		pOBBNode->pOBBNodeL = new OBBNODE;
		Create( FacesL, Level, pOBBNode->pOBBNodeL );
	}
	if( FacesR.size() > 0 ){
		pOBBNode->pOBBNodeR = new OBBNODE;
		Create( FacesR, Level, pOBBNode->pOBBNodeR );
	}
}

// �^����ꂽ�|���S���Q���܂���OBB���쐬
void COBBTree::CreateOBB( std::vector < FACE > &Face, OBBDATA &OBBData )
{
	std::vector < D3DXVECTOR3 > Vertex;
	for( int j = 0; j < (int)Face.size(); ++j ){
		for( int i = 0; i < 3; ++i ){
			Vertex.push_back( Face[j].Vertex[i] );
		}
	}

	int Size = (int)Vertex.size();
	// ����
	D3DXVECTOR3 m( 0, 0, 0 );
	for( int i = 0; i < Size; ++i ){
		m += Vertex[i];
	}
	m /= (float)Size;

	// �����U�s��
	float C11 = 0, C22 = 0, C33 = 0, C12 = 0, C13 = 0,  C23 = 0;
	for( int i = 0; i < Size; ++i ){
		C11 += ( Vertex[i].x - m.x ) * ( Vertex[i].x - m.x );
		C22 += ( Vertex[i].y - m.y ) * ( Vertex[i].y - m.y );
		C33 += ( Vertex[i].z - m.z ) * ( Vertex[i].z - m.z );
		C12 += ( Vertex[i].x - m.x ) * ( Vertex[i].y - m.y );
		C13 += ( Vertex[i].x - m.x ) * ( Vertex[i].z - m.z );
		C23 += ( Vertex[i].y - m.y ) * ( Vertex[i].z - m.z );
	}
	C11 /= Size;
	C22 /= Size;
	C33 /= Size;
	C12 /= Size;
	C13 /= Size;
	C23 /= Size;

	float Matrix[3][3] = {
		{ C11, C12, C13 },
		{ C12, C22, C23 },
		{ C13, C23, C33 },
	};

	// jacobi�@�ŌŗL�l & �ŗL�x�N�g�����Z�o
	float EigenVectors[3][3];
	float EigenValue[3];
	Jacobi( Matrix, EigenVectors, EigenValue );

	// �ŗL�l���~���Ń\�[�g
	struct SORT{
		int ID;
		float Value;
	} Sort[3] = { { 0, EigenValue[0] }, { 1, EigenValue[1] }, { 2, EigenValue[2] } };

	for( int j = 0; j < 2; ++j ){
		for( int i = 2; i > j; --i ){
			if( Sort[i - 1].Value < Sort[i].Value ){
				SORT a = Sort[i];
				Sort[i] = Sort[i - 1];
				Sort[i - 1] = a;
			}
		}
	}

	for( int i = 0; i < 3; ++i ){
		OBBData.Axis[i].x = EigenVectors[0][Sort[i].ID];
		OBBData.Axis[i].y = EigenVectors[1][Sort[i].ID];
		OBBData.Axis[i].z = EigenVectors[2][Sort[i].ID];
	}

	// ���E�{�b�N�X���Z�o
	float min[3] = {  FLT_MAX,  FLT_MAX,  FLT_MAX };
	float max[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
	for( int j = 0; j < 3; ++j ){
		for( int i = 0; i < Size; ++i ){
			float a = D3DXVec3Dot( &Vertex[i], &OBBData.Axis[j] );
			if( min[j] > a ) min[j] = a;
			if( max[j] < a ) max[j] = a;
		}
	}

	OBBData.Center = OBBData.Axis[0] * ( ( min[0] + max[0] ) / 2 )
				   + OBBData.Axis[1] * ( ( min[1] + max[1] ) / 2 )
				   + OBBData.Axis[2] * ( ( min[2] + max[2] ) / 2 );

	for( int i = 0; i < 3; ++i ) OBBData.Length[i] = max[i] - min[i];
	D3DXVECTOR3 G = OBBData.Center
		- (	OBBData.Axis[0] * OBBData.Length[0]
		  + OBBData.Axis[1] * OBBData.Length[1]
		  + OBBData.Axis[2] * OBBData.Length[2] ) / 2;

	OBBData.Matrix = D3DXMATRIX(
		OBBData.Axis[0].x, OBBData.Axis[1].x, OBBData.Axis[2].x, 0,
		OBBData.Axis[0].y, OBBData.Axis[1].y, OBBData.Axis[2].y, 0,
		OBBData.Axis[0].z, OBBData.Axis[1].z, OBBData.Axis[2].z, 0,
		-D3DXVec3Dot( &OBBData.Axis[0], &G ), -D3DXVec3Dot( &OBBData.Axis[1], &G ), -D3DXVec3Dot( &OBBData.Axis[2], &G ), 1 );
}

void COBBTree::DrawOBB( OBBDATA OBBData )
{
	D3DXVECTOR3 G = OBBData.Center
		- (	OBBData.Axis[0] * OBBData.Length[0]
		  + OBBData.Axis[1] * OBBData.Length[1]
		  + OBBData.Axis[2] * OBBData.Length[2] ) / 2;

	D3DXVECTOR3 Axis[3] = { OBBData.Axis[0] * OBBData.Length[0],
							OBBData.Axis[1] * OBBData.Length[1],
							OBBData.Axis[2] * OBBData.Length[2] };

	VERTEX_XYZ_COLOR Vertex[8] = {
		{ G.x, G.y, G.z, D3DCOLOR_ARGB( 255, 255, 255, 255 ) },
		{ G.x + Axis[1].x, G.y + Axis[1].y, G.z + Axis[1].z, D3DCOLOR_ARGB( 255, 255, 255, 255 ) },
		{ G.x + Axis[1].x + Axis[2].x, G.y + Axis[1].y + Axis[2].y, G.z + Axis[1].z + Axis[2].z, D3DCOLOR_ARGB( 255, 255, 255, 255 ) },
		{ G.x + Axis[2].x, G.y + Axis[2].y, G.z + Axis[2].z, D3DCOLOR_ARGB( 255, 255, 255, 255 ) },

		{ G.x + Axis[0].x, G.y + Axis[0].y, G.z + Axis[0].z, D3DCOLOR_ARGB( 255, 255, 255, 255 ) },
		{ G.x + Axis[0].x + Axis[1].x, G.y + Axis[0].y + Axis[1].y, G.z + Axis[0].z + Axis[1].z, D3DCOLOR_ARGB( 255, 255, 255, 255 ) },
		{ G.x + Axis[0].x + Axis[1].x + Axis[2].x, G.y + Axis[0].y + Axis[1].y + Axis[2].y, G.z + Axis[0].z + Axis[1].z + Axis[2].z, D3DCOLOR_ARGB( 255, 255, 255, 255 ) },
		{ G.x + Axis[0].x + Axis[2].x, G.y + Axis[0].y + Axis[2].y, G.z + Axis[0].z + Axis[2].z, D3DCOLOR_ARGB( 255, 255, 255, 255 ) },
	};
	unsigned short Index[24] = {
		0, 1, 1, 2, 2, 3, 3, 0,
		4, 5, 5, 6, 6, 7, 7, 4,
		0, 4, 1, 5, 2, 6, 3, 7
	};
	g_pd3dDevice = GetDevice();

	g_pd3dDevice->SetFVF( D3DFVF_XYZ_COLOR );
	g_pd3dDevice->SetTexture( 0, NULL );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	g_pd3dDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 8, 12, Index, D3DFMT_INDEX16, Vertex, sizeof( VERTEX_XYZ_COLOR ) );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

void COBBTree::Draw( OBBNODE *pOBBNode, int DrawLevel, int Level )
{
	if( Level == DrawLevel ){
		DrawOBB( pOBBNode->OBBData );
		return;
	}
	++Level;

	if( pOBBNode->pOBBNodeL ) Draw( pOBBNode->pOBBNodeL, DrawLevel, Level );
	if( pOBBNode->pOBBNodeR ) Draw( pOBBNode->pOBBNodeR, DrawLevel, Level );
}

bool COBBTree::IsCollision( OBBDATA &BoxA, OBBDATA &BoxB )
{
	// BoxA��3����xyz���ɂȂ��Ԃɕϊ�
	D3DXVECTOR4 Axis[3];
	D3DXMATRIX Matrix = BoxA.Matrix;
	Matrix._41 = 0; Matrix._42 = 0; Matrix._43 = 0;
	for( int i = 0; i < 3; ++i ) D3DXVec3Transform( &Axis[i], &BoxB.Axis[i], &Matrix );

	D3DXVECTOR4 VecAtoBTrans;
	D3DXVec3Transform( &VecAtoBTrans, &( BoxB.Center - BoxA.Center ), &Matrix ); // ���s�ړ������̓L�����Z������Ȃ���΂Ȃ�Ȃ��̂�BoxA.Matrix�ł͂Ȃ�Matrix���g��

	// ���ʂȌv�Z���Ȃ����߂ɉ������炦
	float B[3][3] = {
		{ Axis[0].x, Axis[0].y, Axis[0].z },
		{ Axis[1].x, Axis[1].y, Axis[1].z },
		{ Axis[2].x, Axis[2].y, Axis[2].z }
	};

	float absB[3][3] = {
		{ fabs( B[0][0] ), fabs( B[0][1] ), fabs( B[0][2] ) },
		{ fabs( B[1][0] ), fabs( B[1][1] ), fabs( B[1][2] ) },
		{ fabs( B[2][0] ), fabs( B[2][1] ), fabs( B[2][2] ) }
	};

	float T[3] = { VecAtoBTrans.x, VecAtoBTrans.y, VecAtoBTrans.z }; 

	float a[3] = { BoxA.Length[0] / 2, BoxA.Length[1] / 2, BoxA.Length[2] / 2 };
	float b[3] = { BoxB.Length[0] / 2, BoxB.Length[1] / 2, BoxB.Length[2] / 2 };

	// �ȉ��A���胋�[�`��

	// ������ A.Axis[?]
	for( int i = 0; i < 3; ++i ){
		if( fabs( T[i] )
			> a[i] + b[0] * absB[0][i] + b[1] * absB[1][i] + b[2] * absB[2][i] ) return false;
	}

	// ������ B.Axis[?]
	for( int i = 0; i < 3; ++i ){
		if( fabs( T[0] * B[i][0] + T[1] * B[i][1] + T[2] * B[i][2] )
			> b[i] + a[0] * absB[i][0] + a[1] * absB[i][1] + a[2] * absB[i][2] ) return false;
	}

	// ������ A.Axis[?] x B.Axis[?]
	for( int j0 = 0; j0 < 3; ++j0 ){
		int j1 = ( j0 + 1 ) % 3;
		int j2 = ( j0 + 2 ) % 3;
		for( int i0 = 0; i0 < 3; ++i0 ){
			int i1 = ( i0 + 1 ) % 3;
			int i2 = ( i0 + 2 ) % 3;
			if( fabs( -T[j1] * B[i0][j2] + T[j2] * B[i0][j1] ) 
				> a[j1] * absB[i0][j2] + a[j2] * absB[i0][j1]
				+ b[i1] * absB[i2][j0] + b[i2] * absB[i1][j0] ) return false;
		}
	}

	return true;
}

bool COBBTree::CheckCollision( OBBNODE *pNodeA, OBBNODE *pNodeB, D3DXMATRIX &TransMat, D3DXMATRIX &RotMat )
{
	// BoxA���猩�����W�n��BoxB��ϊ�
	OBBDATA OBBDataB = pNodeB->OBBData;

	D3DXVECTOR4 Center;
	D3DXVec3Transform( &Center, &OBBDataB.Center, &TransMat );
	OBBDataB.Center.x = Center.x;
	OBBDataB.Center.y = Center.y;
	OBBDataB.Center.z = Center.z;

	for( int i = 0; i < 3; ++i ){
		D3DXVECTOR4 Vec;
		D3DXVec3Transform( &Vec, &OBBDataB.Axis[i], &RotMat );
		OBBDataB.Axis[i].x = Vec.x;
		OBBDataB.Axis[i].y = Vec.y;
		OBBDataB.Axis[i].z = Vec.z;
	}

	OBBNODE *pAL = pNodeA->pOBBNodeL, *pAR = pNodeA->pOBBNodeR, *pBL = pNodeB->pOBBNodeL, *pBR = pNodeB->pOBBNodeR;
	bool Result = false;
	if( IsCollision( pNodeA->OBBData, OBBDataB ) ){
		if( !pAL && !pAR && !pBL && !pBR ) Result = true;
		else{
			if(  pAL &&  pBL ) if( Result = CheckCollision( pAL, pBL, TransMat, RotMat ) ) goto EXIT;
			if(  pAL &&  pBR ) if( Result = CheckCollision( pAL, pBR, TransMat, RotMat ) ) goto EXIT;
			if(  pAR &&  pBL ) if( Result = CheckCollision( pAR, pBL, TransMat, RotMat ) ) goto EXIT;
			if(  pAR &&  pBR ) if( Result = CheckCollision( pAR, pBR, TransMat, RotMat ) ) goto EXIT;

			if( !pAL &&  pBL ) if( Result = CheckCollision( pNodeA, pBL, TransMat, RotMat ) ) goto EXIT;
			if( !pAL &&  pBR ) if( Result = CheckCollision( pNodeA, pBR, TransMat, RotMat ) ) goto EXIT;
			// ���Ɠ����Ȃ̂ŏȗ�
		//	if( !pAR &&  pBL ) if( Result = CheckCollision( pNodeA, pBL, TransMat, RotMat ) ) goto EXIT;
		//	if( !pAR &&  pBR ) if( Result = CheckCollision( pNodeA, pBR, TransMat, RotMat ) ) goto EXIT;

			if(  pAL && !pBL ) if( Result = CheckCollision( pAL, pNodeB, TransMat, RotMat ) ) goto EXIT;
			if(  pAR && !pBL ) if( Result = CheckCollision( pAR, pNodeB, TransMat, RotMat ) ) goto EXIT;
			// ���Ɠ����Ȃ̂ŏȗ�
		//	if(  pAL && !pBR ) if( Result = CheckCollision( pAL, pNodeB, TransMat, RotMat ) ) goto EXIT;
		//	if(  pAR && !pBR ) if( Result = CheckCollision( pAR, pNodeB, TransMat, RotMat ) ) goto EXIT;
		}
	}
EXIT:
	return Result;
}

bool COBBTree::CheckCollision( COBBTree &OBBTreeA, D3DXMATRIX &TransMatA,
					 COBBTree &OBBTreeB, D3DXMATRIX &TransMatB )
{
	D3DXMATRIX TransMat, InvMat;
	D3DXMatrixMultiply( &TransMat, &TransMatB, D3DXMatrixInverse( &InvMat, NULL, &TransMatA ) );

	D3DXMATRIX RotMat = TransMat;
	RotMat._41 = 0; RotMat._42 = 0; RotMat._43 = 0;
	return CheckCollision( OBBTreeA.pOBBTopNode, OBBTreeB.pOBBTopNode, TransMat, RotMat );
}

// �ȉ�NUMERICAL RECIPES in C ���
// http://www.library.cornell.edu/nr/bookcpdf/c11-1.pdf
#include <stdio.h>
#include <math.h>

void COBBTree::Rotate( float a[3][3], float s, float tau, int i, int j, int k, int l )
{
	float h, g;
	g = a[i][j];
	h = a[k][l];
	a[i][j] = g - s * ( h + g *tau );
	a[k][l] = h + s * ( g - h *tau );
}

bool COBBTree::Jacobi( float a[3][3], float v[3][3], float d[3] )
{
	int n = 3;
	int i, j, iq, ip;
	float tresh, theta, tau, t, sm, s, h, g, c, b[3], z[3];

	for( ip = 0; ip < n; ip++ ){
		for( iq = 0; iq < n; iq++ ) v[ip][iq] = 0.0f;
		v[ip][ip] = 1.0f;
	}
	for( ip = 0; ip < n; ip++ ){
		b[ip] = d[ip] = a[ip][ip];
		z[ip] = 0.0f;
	}
	for( i = 0; i < 50; i++ ){
		sm = 0.0f;
		for( ip = 0; ip < n - 1; ip++ ){
			for( iq = ip + 1; iq < n; iq++ ) sm += (float)fabs(a[ip][iq]);
		}

		if( sm == 0.0f ) return true;
		if( i < 3 ) tresh = 0.2f * sm / ( n * n );
		else tresh = 0.0f;
		for( ip = 0; ip < n - 1; ip++ ){
			for( iq = ip + 1; iq < n; iq++ ){
				g = 100.0f * (float)fabs( a[ip][iq] );
				if( i > 3 && ( fabs( d[ip] ) + g ) == fabs( d[ip] )
					&& ( fabs( d[iq] ) + g ) == fabs( d[iq] ) ) a[ip][iq] = 0.0f;
				else if( fabs( a[ip][iq] ) > tresh ){
					h = d[iq] - d[ip];
					if( ( fabs( h ) + g ) == fabs( h ) ) t = a[ip][iq] / h;
					else{
						theta = 0.5f * h / a[ip][iq];
						t = 1.0f / ( (float)fabs( theta ) + (float)sqrt( 1.0f + theta * theta ) );
						if( theta < 0.0f ) t = -t;
					}
					c = 1.0f / (float)sqrt( 1 + t * t );
					s = t * c;
					tau = s / ( 1.0f + c );
					h = t * a[ip][iq];
					z[ip] -= h;
					z[iq] += h;
					d[ip] -= h;
					d[iq] += h;
					a[ip][iq] = 0.0f;

					for( j = 0; j < ip; j++ ) Rotate( a, s, tau, j, ip, j, iq );
					for( j = ip + 1; j < iq; j++ ) Rotate( a, s, tau, ip, j, j, iq );
					for( j = iq + 1; j < n; j++ ) Rotate( a, s, tau, ip, j, iq, j );
					for( j = 0; j < n; j++ ) Rotate( v, s, tau, j, ip, j, iq );
				}
			}
		}
		for( ip = 0; ip < n; ip++ ){
			b[ip] += z[ip];
			d[ip] = b[ip];
			z[ip] = 0.0f;
		}
	}

	return false;
}
