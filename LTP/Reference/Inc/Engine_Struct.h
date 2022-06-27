#pragma once

namespace Engine
{

	typedef struct tagVertex_Point
	{
		XMFLOAT3			vPosition;
		float				fPSize;
	}VTXPOINT;

	typedef struct ENGINE_DLL tagVertex_Point_Instance_Matrix_Declaration
	{
		static const unsigned int iNumElements = 8;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];
	}VTXPOINT_INSTMAT_DECLARATION;

	typedef struct tagVertex_Instance_Matrix
	{
		XMFLOAT4			vRight;
		XMFLOAT4			vUp;
		XMFLOAT4			vLook;
		XMFLOAT4			vTranslation;

		XMFLOAT4			vUV_WHSize;
		XMFLOAT4			vColor;
	}VTXINSTMAT;



	typedef struct tagAttachBoneMatrixPtr
	{
		_float4x4*			pUpdatedNodeMat;
		_float4x4*			pDefaultPivotMat;
	}ATTACHBONEMATRIX_PTR;


	typedef struct tagColliderDesc
	{
		_float3 vScale; /* ��� */
		_float4 vRotation;
		_float4 vPosition;
	} COLLIDERDESC;

	typedef struct tagKeyFrame
	{
		_float3		vScale;
		_float4		vRotation;
		_float3		vPosition;
		_double		Time;
	}KEYFRAME;


	typedef struct tagMeshMaterialDesc
	{
		class CTexture*	pTexture;
	}MESHMATERIALDESC;

	typedef struct tagLightDesc
	{
		enum TYPE { TYPE_DIRECTIONAL, TYPE_POINT, TYPE_END };

		TYPE		eLightType = TYPE_END;
		_float4		vDiffuse;
		_float4		vAmbient;
		_float4		vSpecular;
		//Directional : ���� / Point : ��ġ
		_float4		vVector;
		_float		fRange;

		_bool		bIsLightDead = false;
		_float		fTargetDeadTime = FLT_MAX;
		_float		fPassedTime = 0;
	}LIGHTDESC;

	typedef struct tagVertex_Model
	{
		XMFLOAT3			vPosition;
		XMFLOAT3			vNormal;
		XMFLOAT2			vTexUV;
		XMFLOAT3			vTangent;
	}VTXMODEL;

	typedef struct ENGINE_DLL tagVertex_Model_Declaration
	{
		static const unsigned int iNumElements = 4;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];
	}VTXMODEL_DECLARATION;


	typedef struct tagVertex_Animation_Model
	{
		XMFLOAT3			vPosition;
		XMFLOAT3			vNormal;
		XMFLOAT2			vTexUV;
		XMFLOAT3			vTangent;
		XMUINT4				vBlendIndex;
		XMFLOAT4			vBlendWeight;
	}VTXANIMMODEL;

	typedef struct ENGINE_DLL tagVertex_AnimModel_Declaration
	{
		static const unsigned int iNumElements = 6;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];
	}VTXANIMMODEL_DECLARATION;


	typedef struct tagVertex_Texture
	{
		XMFLOAT3			vPosition;
		XMFLOAT2			vTexUV;
	}VTXTEX;

	typedef struct ENGINE_DLL tagVertex_Texture_Declaration
	{
		static const unsigned int iNumElements = 2;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];
	}VTXTEX_DECLARATION;


	typedef struct tagVertex_Color
	{
		XMFLOAT3			vPosition;
		XMFLOAT4			vColor;
	}VTXCOL;

	typedef struct ENGINE_DLL tagVertex_Color_Declaration
	{
		static const unsigned int iNumElements = 2;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];
	}VTXCOL_DECLARATION;



	typedef struct tagVertex_CubeTexture
	{
		XMFLOAT3			vPosition;
		XMFLOAT3			vTexUV;
	}VTXCUBETEX;

	typedef struct ENGINE_DLL tagVertex_Cube_Texture_Declaration
	{
		static const unsigned int iNumElements = 2;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];
	}VTXCUBETEX_DECLARATION;




	typedef struct tagVertex_Normal_Texture
	{
		XMFLOAT3			vPosition;
		XMFLOAT3			vNormal;
		XMFLOAT2			vTexUV;
	}VTXNORTEX;

	typedef struct ENGINE_DLL tagVertex_Normal_Texture_Declaration
	{
		static const unsigned int iNumElements = 3;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];
	}VTXNORMTEX_DECLARATION;


	typedef struct tagVertex_Normal_Cube_Texture
	{
		XMFLOAT3			vPosition;
		XMFLOAT3			vNormal;
		XMFLOAT3			vTexUV;
	}VTXNORCUBTEX;

	typedef struct ENGINE_DLL tagVertex_Normal_Cube_Texture_Declaration
	{
		static const unsigned int iNumElements = 3;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];
	}VTXNORMCUBETEX_DECLARATION;



	typedef struct tagLineIndices32
	{
		unsigned long	_0, _1;
	}LINEINDICES32;


	typedef struct tagLineIndices16
	{
		unsigned short	_0, _1;
	}LINEINDICES16;

	typedef struct tagFaceIndices32
	{
		unsigned long	_0, _1, _2;
	}FACEINDICES32;


	typedef struct tagFaceIndices16
	{
		unsigned short	_0, _1, _2;
	}FACEINDICES16;



	typedef struct tagWorldViewProjMatirx
	{
		_float4x4		WorldMatrix;
		_float4x4		ViewMatrix;
		_float4x4		ProjMatrix;
	}MATRIXWVP;


	typedef struct ENGINE_DLL tag_FilePath
	{
		wchar_t FullPath[260] = L"";
		wchar_t FileName[256] = L"";
		wchar_t Extension[32] = L"";
		unsigned int FileCount = 0;
	}MYFILEPATH;

	typedef struct tag_MeshDesc
	{
		// �޽ÿ� �ʿ��� ����
		_uint			mPrimitiveTypes;
		_uint			mNumVertices;
		_uint			mNumFaces;

		_float3*		mVertices;
		_float3*		mNormals;
		_float3*		mTangents;
		//	_float3*		mTextureCoords[AI_MAX_NUMBER_OF_TEXTURECOORDS];
		FACEINDICES32*	mFaces;

		//	unsigned int mNumUVComponents[AI_MAX_NUMBER_OF_TEXTURECOORDS];
		_uint			mMaterialIndex;

		_uint			mNumAffectingBones = 0; // �����ִ� ������
		_uint*			mAffectingBones; // �����ִ� ������ �ε���

		// C_STRUCT aiColor4D* mColors[AI_MAX_NUMBER_OF_COLOR_SETS];
		// C_STRUCT aiBone** mBones;
		// C_STRUCT aiString mName;
		// unsigned int mNumAnimMeshes;
		// C_STRUCT aiAnimMesh** mAnimMeshes;
		// unsigned int mMethod;
		// C_STRUCT aiAABB mAABB;



	}MESHDESC;



	typedef struct tag_MatDesc
	{
		wchar_t MatName[MAX_TEXTURE_TYPE][MAX_PATH] = { L"" };

	}MATDESC;

	typedef struct tag_BoneDesc
	{
		tag_BoneDesc()
		{
			XMStoreFloat4x4(&mOffsetMat, XMMatrixIdentity());
		}

		tag_BoneDesc(const char* parentBoneName, const char* CurrentBoneName, _float4x4 offsetmat, _uint depth)
		{
			strcpy_s(mParentBoneName, parentBoneName);
			strcpy_s(mCurrentBoneName, CurrentBoneName);
			mOffsetMat = offsetmat;
			mDepth = depth;
		}

		// �θ�� ����� offsetMat
		char 		mParentBoneName[MAX_PATH] = "";
		char		mCurrentBoneName[MAX_PATH] = "";
		_float4x4	mOffsetMat;

		// ������ �ִ� �� �ε���

		_uint		mDepth = 0;

	}BONEDESC;

	typedef struct tag_AnimationBoneDesc
	{
		tag_AnimationBoneDesc() {}

		tag_AnimationBoneDesc(const char* name, _uint keyframes, _int hierindex)
		{
			strcpy_s(mBoneName, name);
			mNumKeyFrames = keyframes;
			mHierarchyNodeIndex = hierindex;
			mKeyFrames = new KEYFRAME[mNumKeyFrames];
		}


		char 		mBoneName[MAX_PATH] = "";
		_int		mHierarchyNodeIndex = -1;
		_uint		mNumKeyFrames = 0;
		KEYFRAME*	mKeyFrames = nullptr;


	}ANIBONES;

	typedef struct tag_AnimationDesc
	{
		// �ִϸ��̼� �̸� / �ð� / 
		tag_AnimationDesc() {}

		tag_AnimationDesc(const char* name, double d, double t)
		{
			strcpy_s(mAniName, name);
			mDuration = d;
			mTicksPerSecond = t;


		}
		char 		mAniName[MAX_PATH] = "";
		double		mDuration = 0;
		double		mTicksPerSecond = 0;

		_uint		mNumAniBones = 0;
		ANIBONES*	mAniBones = nullptr;;
	}ANIDESC;


	

	typedef struct tag_ModelDesc
	{
		_uint mModelType = 0;
		wchar_t mFBXFileName[MAX_PATH] = L"";
		wchar_t mFBXFullPath[MAX_PATH] = L"";

		// Ready_MeshContainers
		_uint			mNumMeshes;
		MESHDESC*		mMeshDesc = nullptr;;

		_uint			mNumMaterials;
		MATDESC*		mMaterials = nullptr;;

		_uint			mNumBones;
		BONEDESC*		mBones = nullptr;;

		// Dynamic Mesh
		_uint			mNumAnimations;
		ANIDESC*		mAnimations = nullptr;;


	}MODELDESC;



}