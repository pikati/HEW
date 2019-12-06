#ifndef __COBBTREE_H__
#define __COBBTREE_H__

#include <d3dx9.h>
#include <vector>

#define for if( 0 );else for

struct FACE{
	D3DXVECTOR3 Vertex[3];
	D3DXVECTOR3 Center;
};

typedef std::vector < FACE > FACES;

struct OBBDATA{
	D3DXMATRIX Matrix;
	D3DXVECTOR3 Axis[3];
	float Length[3];
	D3DXVECTOR3 Center;
};

struct OBBNODE{
	OBBNODE *pOBBNodeL, *pOBBNodeR;
	OBBDATA OBBData;
	OBBNODE(){ pOBBNodeL = NULL; pOBBNodeR = NULL; }
};

#define D3DFVF_XYZ_COLOR		( D3DFVF_XYZ | D3DFVF_DIFFUSE )

struct VERTEX_XYZ_COLOR{
    FLOAT x, y, z;
	D3DCOLOR color;
};

class COBBTree
{
public:
	COBBTree();
	~COBBTree();
	bool Create( LPD3DXMESH pMesh, int Level );
	void Draw( int DrawLevel ){ Draw( pOBBTopNode, DrawLevel, 0 ); };
	bool CheckCollision( COBBTree &OBBTreeA, D3DXMATRIX &TransMatA,
						 COBBTree &OBBTreeB, D3DXMATRIX &TransMatB );
private:
	void Create( FACES &Face, int Level, OBBNODE *pOBBNode );
	void CreateOBB( std::vector < FACE > &Face, OBBDATA &OBBData );
	void Rotate( float a[3][3], float s, float tau, int i, int j, int k, int l );
	bool Jacobi( float a[3][3], float v[3][3], float d[3] );
	void DrawOBB( OBBDATA OBBData );
	void Draw( OBBNODE *pOBBNode, int DrawLevel, int Level );
	void ReleaseNodes( OBBNODE *pOBBNode );
	bool IsCollision( OBBDATA &BoxA, OBBDATA &BoxB );
	bool CheckCollision( OBBNODE *pNodeA, OBBNODE *pNodeB, D3DXMATRIX &TransMat, D3DXMATRIX &RotMat );

public:
	OBBNODE *pOBBTopNode;
};

#endif // __COBBTREE_H__
