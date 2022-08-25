#include "..\public\Model.h"
#include "MeshContainer.h"
#include "Texture.h"
#include "HierarchyNode.h"
#include "AnimationClip.h"
#include "ClipBone.h"
#include "VIBuffer_Model_Instance.h"
#include "Transform.h"
#include "Shader.h"


_bool CModel::MODEL_TOOLPATH_FLAG = false;

CModel::CModel(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	: CComponent(pDevice, pDeviceContext)
{
}

CModel::CModel(const CModel & rhs)
	: CComponent(rhs),
	m_eModelType(rhs.m_eModelType),

	m_iNumMeshContainers(rhs.m_iNumMeshContainers),
	m_vecMeshContainerArr(rhs.m_vecMeshContainerArr),

	m_MeshMaterialDesc(rhs.m_MeshMaterialDesc),
	m_iNumMaterials(rhs.m_iNumMaterials),

	//m_vecHierarchyNode(rhs.m_vecHierarchyNode),
	m_iNumAnimationClip(rhs.m_iNumAnimationClip),
	m_vecAnimator(rhs.m_vecAnimator),

	m_DefaultPivotMatrix(rhs.m_DefaultPivotMatrix),

	m_pModelDesc(rhs.m_pModelDesc),
	m_iNumTotalPrimitive(rhs.m_iNumTotalPrimitive)
{

	//�Ž� �����̳� ���� ����
	for (_uint i = 0; i < m_iNumMaterials; i++)
	{
		for (auto& pMeshcontainer : m_vecMeshContainerArr[i])
			Safe_AddRef(pMeshcontainer);
	}

	//�Ž��� ������ �ؽ�ó ���� ����
	Safe_AddRef(m_MeshMaterialDesc.pTexture);

	//�ִϸ��̼� ���� ����
	for (auto& pAnimationClip : m_vecAnimator)
		Safe_AddRef(pAnimationClip);

	
	if (TYPE_ANIM == m_eModelType)
	{
		//�ִϸ��̼��� ����ϴ� �𵨵��� �������� �޾ƿ;���
		if (m_pModelDesc)
		{
			FAILED_CHECK_NONERETURN(Ready_HierarchyNodes(m_pModelDesc));
			sort(m_vecHierarchyNode.begin(), m_vecHierarchyNode.end(), [](CHierarchyNode* pSour, CHierarchyNode* pDest)
			{
				return pSour->Get_Depth() < pDest->Get_Depth();

			});
		}

		else
		{
			if (FAILED(Ready_HierarchyNodes((rhs.m_pScene)->mRootNode)))
			{
				MSGBOX("Failed to Clone HierarchyNode");
				__debugbreak();
			}

			sort(m_vecHierarchyNode.begin(), m_vecHierarchyNode.end(), [](CHierarchyNode* pSour, CHierarchyNode* pDest)
			{
				return pSour->Get_Depth() < pDest->Get_Depth();
			});
		}

		_uint iNumHierarchyNodes = _uint(m_vecHierarchyNode.size());
		for (_uint i = 0; i < iNumHierarchyNodes; i++)
		{
			_float4x4 matOffSet = (rhs.m_vecHierarchyNode[i])->Get_OffsetMatrix();
			m_vecHierarchyNode[i]->Set_OffsetMatrix(&matOffSet);
		}

		m_vecCurrentKeyFrameIndices.resize(rhs.m_vecCurrentKeyFrameIndices.size());

		for (_uint i = 0; i < m_vecCurrentKeyFrameIndices.size(); i++)
		{
			m_vecCurrentKeyFrameIndices[i].resize(rhs.m_vecCurrentKeyFrameIndices[i].size());
		}
	}



}
HRESULT CModel::Initialize_Prototype(MODELTYPE eModelType, const char * pModelFilePath, const char * pModelFileName, _fMatrix& DefaultPivotMatrix, _uint iAnimCount)
{
	FAILED_CHECK(__super::Initialize_Prototype(nullptr));

	ZeroMemory(&m_MeshMaterialDesc, sizeof(MESHMATERIALDESC));

	m_eModelType = eModelType;
	m_DefaultPivotMatrix = DefaultPivotMatrix;

	char	szFullPath[MAX_PATH] = "";
	char	szFilePath[MAX_PATH] = "";

	if (MODEL_TOOLPATH_FLAG == false)
	{
		strcpy_s(szFullPath, "../bin/Resources/Mesh/");

	if (TYPE_NONANIM == m_eModelType)
		strcat_s(szFullPath, "StaticMesh/");
	else
		strcat_s(szFullPath, "DynamicMesh/");


	strcat_s(szFullPath, pModelFilePath);
	strcat_s(szFullPath, "/");
	strcpy_s(szFilePath, szFullPath);
	strcat_s(szFullPath, pModelFileName);
	}

	else
	{
		strcpy_s(szFullPath, pModelFilePath);
		strcpy_s(szFilePath, pModelFileName);

	}

	_uint		iFlag = 0;

	if (TYPE_NONANIM == m_eModelType)
		iFlag = aiProcess_PreTransformVertices | aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_CalcTangentSpace;
	else
		iFlag = aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_CalcTangentSpace;

	m_pScene = m_Importer.ReadFile(szFullPath, iFlag);

	NULL_CHECK_RETURN(m_pScene, E_FAIL);

	if (TYPE_ANIM == m_eModelType)
	{
		//�ִϸ��̼��� ����ϴ� �𵨵��� �������� �޾ƿ;���
		FAILED_CHECK(Ready_HierarchyNodes(m_pScene->mRootNode));

		sort(m_vecHierarchyNode.begin(), m_vecHierarchyNode.end(), [](CHierarchyNode* pSour, CHierarchyNode* pDest)
		{
			return pSour->Get_Depth() < pDest->Get_Depth();
		});


#ifdef _DEBUG
		{

			string szLog = "Model Name : " + string(pModelFileName) + "		Num Bones : " + to_string(m_vecHierarchyNode.size()) + "\n";
			wstring DebugLog;
			DebugLog.assign(szLog.begin(), szLog.end());

			OutputDebugStringW(DebugLog.c_str());
		}

		//for (auto& pNode : m_vecHierarchyNode)
		//{
		//	string szLog = "HierarchyNode Name : " + string(pNode->Get_Name()) + "\n";
		//	wstring DebugLog;
		//	DebugLog.assign(szLog.begin(), szLog.end());

		//	OutputDebugStringW(DebugLog.c_str());

		//}

#endif

	}
	FAILED_CHECK(Ready_MeshContainers(DefaultPivotMatrix));

	FAILED_CHECK(Ready_Materials(szFilePath));





	if (TYPE_ANIM == m_eModelType)
	{
		//�� ������ �Ž��� ���û��¿� ���� ���� �� �ֱ� ������ �������ִ� ��Ʈ������ �������� ����
		FAILED_CHECK(Ready_OffsetMatrices());

		FAILED_CHECK(Ready_Animation());
#ifdef _DEBUG
		string ttszLog = "Num AnimationClip: " + to_string(m_iNumAnimationClip) + "\n";
		wstring ttDebugLog;
		ttDebugLog.assign(ttszLog.begin(), ttszLog.end());

		OutputDebugStringW(ttDebugLog.c_str());

#endif
		if (iAnimCount != 1)
			FAILED_CHECK(Ready_MoreAnimation(szFullPath, iAnimCount, iFlag));

	}
	
	m_iNumTotalPrimitive = 0;

	for (_uint i = 0 ; i <m_iNumMaterials;	i++ )
	{
		for (auto& pMeshContainer : m_vecMeshContainerArr[i])
		{
			m_iNumTotalPrimitive += pMeshContainer->Get_NumPrimitive();
		}
	}


	return S_OK;
}

HRESULT CModel::Initialize_Prototype(MODELTYPE eModelType, MODELDESC* desc, _fMatrix & DefaultPivotMatrix)
{
	FAILED_CHECK(__super::Initialize_Prototype(nullptr));


	// DatFile�� ������ �ε� �׽�Ʈ
	if (eModelType == CModel::TYPE_ANIM)
	{
		m_eModelType = eModelType;
		m_DefaultPivotMatrix = DefaultPivotMatrix;

		m_pScene = nullptr;
		m_pModelDesc = desc; // �׽�Ʈ�� ���ڷ� �ް� ���� �� ����
		
		// ������ �ִ� �� ������Ʈ
		FAILED_CHECK(Ready_MeshContainers(DefaultPivotMatrix));
		FAILED_CHECK(Ready_Materials(m_pModelDesc->mFBXFullPath));

		// �� �ε�
		FAILED_CHECK(Ready_HierarchyNodes(m_pModelDesc));
		sort(m_vecHierarchyNode.begin(), m_vecHierarchyNode.end(), [](CHierarchyNode* pSour, CHierarchyNode* pDest)
		{
			return pSour->Get_Depth() < pDest->Get_Depth();

		});

		// �����ִ� �� ����Ʈ 
		//FAILED_CHECK(Ready_OffsetMatrices(m_pModelDesc));

		// �ִϸ��̼� �ʱ�ȭ
		FAILED_CHECK(Ready_Animation(m_pModelDesc));


	}
	else
	{
		m_eModelType = eModelType;
		m_DefaultPivotMatrix = DefaultPivotMatrix;

		m_pScene = nullptr;
		m_pModelDesc = desc;

		FAILED_CHECK(Ready_MeshContainers(DefaultPivotMatrix));
		FAILED_CHECK(Ready_Materials(m_pModelDesc->mFBXFullPath));
	}


	m_iNumTotalPrimitive = 0;

	for (_uint i = 0; i < m_iNumMaterials; i++)
	{
		for (auto& pMeshContainer : m_vecMeshContainerArr[i])
		{
			m_iNumTotalPrimitive += pMeshContainer->Get_NumPrimitive();
		}
	}

	return S_OK;
}

HRESULT CModel::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(nullptr));




	return S_OK;
}

HRESULT CModel::Change_AnimIndex(_uint iAnimIndex, _double ExitTime, _bool bBlockAnimUntilReturnChange)
{
	if (iAnimIndex >= m_iNumAnimationClip)
		return E_FAIL;

	if (iAnimIndex == m_iNowAnimIndex) return S_FALSE;

	m_bIsChagingAnim = true;


	if (m_AnimExitAcc)
	{
		_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);
	}

	m_AnimExitAcc = 0;
	m_TotalAnimExitTime = ExitTime;

	if (!m_bIsSwapFunctionCalled)
	{
		m_OldPlayTimeAcc = m_NowPlayTimeAcc;
		m_iOldAnimIndex = m_iNowAnimIndex;
	}

	m_NowPlayTimeAcc = 0;
	m_iNowAnimIndex = iAnimIndex;


	m_iNextAnimIndex = iAnimIndex;
	m_bIsBlockAnim = bBlockAnimUntilReturnChange;

	m_KindsOfAnimChange = 0;
	m_bIsUntill = false;

	m_bIsSwapFunctionCalled = true;
	return S_OK;
}

HRESULT CModel::Change_AnimIndex_UntilNReturn(_uint iAnimIndex, _uint iUntilIndex, _uint iReturnIndex, _double ExitTime, _bool bBlockAnimUntilReturnChange)
{
	if (iAnimIndex >= m_iNumAnimationClip || iReturnIndex >= m_iNumAnimationClip)
		return E_FAIL;


	if (iReturnIndex == m_iNextAnimIndex && iAnimIndex == m_iNowAnimIndex && iReturnIndex == m_iReturnIndex) return S_FALSE;



	if (!m_bIsSwapFunctionCalled &&(m_bIsChagingAnim || m_AnimExitAcc)) // m_AnimExitAcc ��ȯ ���̿��ٸ�
	{
		_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);
	}

	m_bIsChagingAnim = true;


	m_AnimExitAcc = 0;
	m_TotalAnimExitTime = ExitTime;

	if (!m_bIsSwapFunctionCalled)
	{

		m_OldPlayTimeAcc = m_NowPlayTimeAcc;
		m_iOldAnimIndex = m_iNowAnimIndex;

	}

	m_NowPlayTimeAcc = 0;
	m_iNowAnimIndex = iAnimIndex;


	m_iNextAnimIndex = iUntilIndex;
	m_iReturnIndex = iReturnIndex;
	m_bIsBlockAnim = bBlockAnimUntilReturnChange;
	m_KindsOfAnimChange = 2;
	m_bIsUntill = true;
	m_bIsSwapFunctionCalled = true;

	return S_OK;
}

HRESULT CModel::Change_AnimIndex_UntilNReturn_Must(_uint iAnimIndex, _uint iUntilIndex, _uint iReturnIndex, _double ExitTime, _bool bBlockAnimUntilReturnChange)
{
	if (iAnimIndex >= m_iNumAnimationClip || iReturnIndex >= m_iNumAnimationClip)
		return E_FAIL;


	if (!m_bIsSwapFunctionCalled&&(m_bIsChagingAnim || m_AnimExitAcc)) // m_AnimExitAcc ��ȯ ���̿��ٸ�
	{
		_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);
	}

	m_bIsChagingAnim = true;


	m_AnimExitAcc = 0;
	m_TotalAnimExitTime = ExitTime;

	if (!m_bIsSwapFunctionCalled)
	{

		m_OldPlayTimeAcc = m_NowPlayTimeAcc;
		m_iOldAnimIndex = m_iNowAnimIndex;

	}

	m_NowPlayTimeAcc = 0;
	m_iNowAnimIndex = iAnimIndex;


	m_iNextAnimIndex = iUntilIndex;
	m_iReturnIndex = iReturnIndex;
	m_bIsBlockAnim = bBlockAnimUntilReturnChange;
	m_KindsOfAnimChange = 2;
	m_bIsUntill = true;
	m_bIsSwapFunctionCalled = true;

	return S_OK;
}

HRESULT CModel::Change_AnimIndex_UntilTo(_uint iAnimIndex, _uint iReturnIndex, _double ExitTime, _bool bBlockAnimUntilReturnChange)
{
	if (iAnimIndex >= m_iNumAnimationClip || iReturnIndex >= m_iNumAnimationClip)
		return E_FAIL;


	if (iReturnIndex == m_iNextAnimIndex && iAnimIndex == m_iNowAnimIndex) return S_FALSE;

	if (!m_bIsSwapFunctionCalled && (m_bIsChagingAnim || m_AnimExitAcc)) // m_AnimExitAcc ��ȯ ���̿��ٸ�
	{
		_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);
	}

	m_bIsChagingAnim = true;

	
	m_AnimExitAcc = 0;
	m_TotalAnimExitTime = ExitTime;

	if (!m_bIsSwapFunctionCalled)
	{

		m_OldPlayTimeAcc = m_NowPlayTimeAcc;
		m_iOldAnimIndex = m_iNowAnimIndex;

	}

	m_NowPlayTimeAcc = 0;
	m_iNowAnimIndex = iAnimIndex;


	m_iNextAnimIndex = iReturnIndex;
	m_bIsBlockAnim = bBlockAnimUntilReturnChange;
	m_KindsOfAnimChange = 0;
	m_bIsUntill = true;

	m_bIsSwapFunctionCalled = true;
	return S_OK;
}



HRESULT CModel::Change_AnimIndex_ReturnTo(_uint iAnimIndex, _uint iReturnIndex, _double ExitTime, _bool bBlockAnimUntilReturnChange)
{
	if (iAnimIndex >= m_iNumAnimationClip || iReturnIndex >= m_iNumAnimationClip)
		return E_FAIL;

	if (iReturnIndex == m_iNextAnimIndex && iAnimIndex == m_iNowAnimIndex) return S_FALSE;


	m_bIsChagingAnim = true;

	if (!m_bIsSwapFunctionCalled && m_AnimExitAcc)
	{
		_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);
	}
	m_AnimExitAcc = 0;
	m_TotalAnimExitTime = ExitTime;

	if (!m_bIsSwapFunctionCalled)
	{
		m_OldPlayTimeAcc = m_NowPlayTimeAcc;
		m_iOldAnimIndex = m_iNowAnimIndex;
	}


	m_NowPlayTimeAcc = 0;
	m_iNowAnimIndex = iAnimIndex;


	m_iNextAnimIndex = iReturnIndex;

	m_bIsBlockAnim = bBlockAnimUntilReturnChange;
	m_KindsOfAnimChange = 1;
	m_bIsUntill = false;

	m_bIsSwapFunctionCalled = true;
	return S_OK;
}

HRESULT CModel::Change_AnimIndex_ReturnTo_Must(_uint iAnimIndex, _uint iReturnIndex, _double ExitTime, _bool bBlockAnimUntilReturnChange)
{
	if (iAnimIndex >= m_iNumAnimationClip || iReturnIndex >= m_iNumAnimationClip)
		return E_FAIL;

	//if (iReturnIndex == m_iNextAnimIndex) return S_FALSE;


	m_bIsChagingAnim = true;

	if (!m_bIsSwapFunctionCalled && m_AnimExitAcc)
	{
		_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
		m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);
	}
	m_AnimExitAcc = 0;
	m_TotalAnimExitTime = ExitTime;

	if (!m_bIsSwapFunctionCalled)
	{

		m_OldPlayTimeAcc = m_NowPlayTimeAcc;
		m_iOldAnimIndex = m_iNowAnimIndex;

	}

	m_NowPlayTimeAcc = 0;
	m_iNowAnimIndex = iAnimIndex;


	m_iNextAnimIndex = iReturnIndex;

	m_bIsBlockAnim = bBlockAnimUntilReturnChange;
	m_KindsOfAnimChange = 1;
	m_bIsUntill = false;

	m_bIsSwapFunctionCalled = true;
	return S_OK;
}



_double CModel::Get_PlayRate()
{
 	return m_vecAnimator[m_iNowAnimIndex]->Get_PlayRate(m_NowPlayTimeAcc);
}

void CModel::Set_OldAnimIndex(_uint iAnimIndex)
{
	m_iOldAnimIndex = iAnimIndex;
}

HRESULT CModel::Remove_CertainKeyFrameIndex(_uint iAnimIndex)
{
	if (iAnimIndex >= m_vecAnimator.size())
		return E_FAIL;

	_uint iNumAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[iAnimIndex].size());
	m_vecCurrentKeyFrameIndices[iAnimIndex].clear();
	m_vecCurrentKeyFrameIndices[iAnimIndex].resize(iNumAnimKeyFrameIdx);

	return S_OK;
}

HRESULT CModel::Bind_OnShader(CShader * pShader, _uint iMaterialIndex, _uint eTextureType, const char * pHlslConstValueName)
{
	if (eTextureType == 0) return S_FALSE;

	if (iMaterialIndex  >= m_iNumMaterials|| pShader == nullptr || m_MeshMaterialDesc.pTexture == nullptr)
		return E_FAIL;

	FAILED_CHECK(m_MeshMaterialDesc.pTexture->Change_TextureLayer(to_wstring(iMaterialIndex).c_str()));

	if (FAILED(m_MeshMaterialDesc.pTexture->NullCheckTexture(eTextureType)))
	{
		pShader->Set_Texture(pHlslConstValueName, nullptr);
		return S_FALSE;
	}
	

	if (FAILED(m_MeshMaterialDesc.pTexture->Bind_OnShader(pShader, pHlslConstValueName, eTextureType)))
	{
#ifdef  _DEBUG
		OutputDebugStringW(L"Failed to Bind 3D Model Texture on Shader\n");
#endif //  _DEBUG
		return S_FALSE;
	}


	return S_OK;
}

HRESULT CModel::Update_AnimationClip(_double fDeltaTime,_bool IsUpdateAll)
{
#ifdef _DEBUG
	fDeltaTime *= m_fDebugAnimPlaySpeed;
#endif // _DEBUG

	m_bIsSwapFunctionCalled = false;
	switch (m_KindsOfAnimChange)
	{
	case 0:
	{
		if (!m_bIsChagingAnim)
		{
			//�ش� �ִϸ��̼��� ���� Ʈ��������Ʈ������ �������ְ�
			FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byClipBones(&m_bIsChagingAnim, fDeltaTime, &m_NowPlayTimeAcc,
				&m_vecHierarchyNode, &(m_vecCurrentKeyFrameIndices[m_iNowAnimIndex]), IsUpdateAll));

			if (m_bIsChagingAnim)
			{
				m_OldPlayTimeAcc = m_NowPlayTimeAcc;
				m_iOldAnimIndex = m_iNowAnimIndex;

				m_NowPlayTimeAcc = 0;

		

				if (m_iNowAnimIndex < m_iNextAnimIndex)
				{
					m_iNowAnimIndex = m_iNowAnimIndex + 1;
				}
				else
				{
					m_bIsUntill = false;
					m_iNowAnimIndex = m_iNowAnimIndex;
					m_TotalAnimExitTime = 0;
					m_bIsBlockAnim = false;
				}

				m_AnimExitAcc = 0;
			}

		}



		if (m_bIsChagingAnim)
		{
			m_AnimExitAcc += fDeltaTime;

			if (m_AnimExitAcc <= m_TotalAnimExitTime)
			{
				if (IsUpdateAll)
				{
					FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byEasing_OldAnim(m_iNowAnimIndex, m_vecAnimator[m_iOldAnimIndex], m_iOldAnimIndex,
						m_OldPlayTimeAcc, m_AnimExitAcc / m_TotalAnimExitTime, &m_vecHierarchyNode, &m_vecCurrentKeyFrameIndices));
				}

			}
			else
			{

				//���� �ִϸ��̼� �ʱ�ȭ
				_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
				m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
				m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);

				m_OldPlayTimeAcc = 0;

				m_bIsChagingAnim = false;
				m_AnimExitAcc = 0;

				FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byClipBones(&m_bIsChagingAnim, fDeltaTime, &m_NowPlayTimeAcc,
					&m_vecHierarchyNode, &(m_vecCurrentKeyFrameIndices[m_iNowAnimIndex]), IsUpdateAll));
			}

		}

	}
	break;

	case 1: //ReturnTo
	{
		if (!m_bIsChagingAnim)
		{
			//�ش� �ִϸ��̼��� ���� Ʈ��������Ʈ������ �������ְ�
			FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byClipBones(&m_bIsChagingAnim, fDeltaTime, &m_NowPlayTimeAcc,
				&m_vecHierarchyNode, &(m_vecCurrentKeyFrameIndices[m_iNowAnimIndex]), IsUpdateAll));

			if (m_bIsChagingAnim)
			{
				m_OldPlayTimeAcc = m_NowPlayTimeAcc;
				m_iOldAnimIndex = m_iNowAnimIndex;
				m_NowPlayTimeAcc = 0;
				m_iNowAnimIndex = m_iNextAnimIndex;
				m_AnimExitAcc = 0;
				m_KindsOfAnimChange = 0;
				m_bIsBlockAnim = false;

			}

		}



		if (m_bIsChagingAnim)
		{
			m_AnimExitAcc += fDeltaTime;

			if (m_AnimExitAcc <= m_TotalAnimExitTime)
			{

				if (IsUpdateAll)
					FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byEasing_OldAnim(m_iNowAnimIndex, m_vecAnimator[m_iOldAnimIndex], m_iOldAnimIndex,
						m_OldPlayTimeAcc, m_AnimExitAcc / m_TotalAnimExitTime, &m_vecHierarchyNode, &m_vecCurrentKeyFrameIndices));

			}
			else
			{

				//���� �ִϸ��̼� �ʱ�ȭ
				_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
				m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
				m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);

				m_OldPlayTimeAcc = 0;
				m_bIsChagingAnim = false;

				m_AnimExitAcc = 0;

				FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byClipBones(&m_bIsChagingAnim, fDeltaTime, &m_NowPlayTimeAcc,
					&m_vecHierarchyNode, &(m_vecCurrentKeyFrameIndices[m_iNowAnimIndex]), IsUpdateAll));


				if (m_bIsChagingAnim)
				{
					m_OldPlayTimeAcc = m_NowPlayTimeAcc;
					m_iOldAnimIndex = m_iNowAnimIndex;
					m_NowPlayTimeAcc = 0;
					m_TotalAnimExitTime = 0.15f;
					m_iNowAnimIndex = m_iNextAnimIndex;
					m_AnimExitAcc = 0;
					m_KindsOfAnimChange = 0;
				}

			}

		}

	}
	break;


	case 2: // UntilNReturn

	{
		if (!m_bIsChagingAnim)
		{
			//�ش� �ִϸ��̼��� ���� Ʈ��������Ʈ������ �������ְ�
			FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byClipBones(&m_bIsChagingAnim, fDeltaTime, &m_NowPlayTimeAcc,
				&m_vecHierarchyNode, &(m_vecCurrentKeyFrameIndices[m_iNowAnimIndex]), IsUpdateAll));

			if (m_bIsChagingAnim)
			{
				m_OldPlayTimeAcc = m_NowPlayTimeAcc;
				m_iOldAnimIndex = m_iNowAnimIndex;

				m_NowPlayTimeAcc = 0;

				if (m_iNowAnimIndex < m_iNextAnimIndex)
				{
					m_iNowAnimIndex = m_iNowAnimIndex + 1;
				}
				else
				{
					m_bIsUntill = false;
					m_KindsOfAnimChange = 0;
					m_iNowAnimIndex = m_iReturnIndex;
					m_iNextAnimIndex = m_iReturnIndex;
				}

				m_AnimExitAcc = 0;
			}

		}



		if (m_bIsChagingAnim)
		{
			m_AnimExitAcc += fDeltaTime;

			if (m_AnimExitAcc <= m_TotalAnimExitTime)
			{
				if (IsUpdateAll)
				{
					FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byEasing_OldAnim(m_iNowAnimIndex, m_vecAnimator[m_iOldAnimIndex], m_iOldAnimIndex,
						m_OldPlayTimeAcc, m_AnimExitAcc / m_TotalAnimExitTime, &m_vecHierarchyNode, &m_vecCurrentKeyFrameIndices));
				}

			}
			else
			{

				//���� �ִϸ��̼� �ʱ�ȭ
				_uint iNumOldAnimKeyFrameIdx = _uint(m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].size());
				m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].clear();
				m_vecCurrentKeyFrameIndices[m_iOldAnimIndex].resize(iNumOldAnimKeyFrameIdx);

				m_OldPlayTimeAcc = 0;

				m_bIsChagingAnim = false;
				m_AnimExitAcc = 0;

				FAILED_CHECK(m_vecAnimator[m_iNowAnimIndex]->Update_TransformMatrices_byClipBones(&m_bIsChagingAnim, fDeltaTime, &m_NowPlayTimeAcc,
					&m_vecHierarchyNode, &(m_vecCurrentKeyFrameIndices[m_iNowAnimIndex]), IsUpdateAll));
			}

		}



	}
	break;
	default:
		break;
	}



	


	//���ŵ� ��Ʈ������ ���� �Ĺ��ε� ��Ʈ������ ������Ʈ ���ش�.
	for (auto& pHierarchyNode : m_vecHierarchyNode)
		pHierarchyNode->Update_CombinedMatrix();

	return S_OK;
}

HRESULT CModel::Render(CShader * pShader, _uint iPassIndex,_uint iMaterialIndex, const char* szBoneValueName)
{
	if (iMaterialIndex >= m_iNumMaterials || nullptr == m_MeshMaterialDesc.pTexture)
		return E_FAIL;

	if (TYPE_ANIM == m_eModelType)
	{
		NULL_CHECK_RETURN(szBoneValueName, E_FAIL);
		_float4x4		BoneMatrices[150];
		_Matrix matDefualtPivot = m_DefaultPivotMatrix.XMatrix();

		for (auto& pMeshContainer : m_vecMeshContainerArr[iMaterialIndex])
		{
			FAILED_CHECK(pMeshContainer->Bind_AffectingBones_OnShader(pShader, matDefualtPivot, BoneMatrices, szBoneValueName, &m_vecHierarchyNode));
			FAILED_CHECK(pMeshContainer->Render(pShader, iPassIndex));
		}
	}
	else
	{
		for (auto& pMeshContainer : m_vecMeshContainerArr[iMaterialIndex])
		{

			FAILED_CHECK(pMeshContainer->Render(pShader, iPassIndex));
		}


	}





	return S_OK;
}

#define PrimitiveCullingNum 8000

HRESULT CModel::Render_ForInstancing(class CShader* pShader, _uint iPassIndex, _uint iMaterialIndex, class CVIBuffer_Model_Instance* pInstacneBuffer,
									vector<class CTransform*>* pvecWorldMatrixs, const char* szBoneValueName, 
	_float fFrustumsize, vector<_float4>*  pvecLimLight, vector<_float4>*  pvecEmissive, vector<_float4>*  pvecTimmer , _bool bPrimitiveCullingOn)
{
	if (iMaterialIndex >= m_iNumMaterials || nullptr == m_MeshMaterialDesc.pTexture)
		return E_FAIL;

	if (TYPE_ANIM == m_eModelType)
	{
		NULL_CHECK_RETURN(szBoneValueName, E_FAIL);
		_float4x4		BoneMatrices[150];
		_Matrix matDefualtPivot = m_DefaultPivotMatrix.XMatrix();

		_uint iMeshConstainerIndex = 0;

		for (auto& pMeshContainer : m_vecMeshContainerArr[iMaterialIndex])
		{

			//if(bPrimitiveCullingOn && pMeshContainer->Get_NumPrimitive() > PrimitiveCullingNum) 
			//	continue;

			FAILED_CHECK(pMeshContainer->Bind_AffectingBones_OnShader(pShader, matDefualtPivot, BoneMatrices, szBoneValueName, &m_vecHierarchyNode));

			FAILED_CHECK(pInstacneBuffer->Render(pShader, iPassIndex, iMaterialIndex, iMeshConstainerIndex,
				pMeshContainer, pvecWorldMatrixs, fFrustumsize, pvecLimLight, pvecEmissive, pvecTimmer));


			iMeshConstainerIndex++;
		}
	}
	else
	{
		_uint iMeshConstainerIndex = 0;

		for (auto& pMeshContainer : m_vecMeshContainerArr[iMaterialIndex])
		{

			//if (bPrimitiveCullingOn && pMeshContainer->Get_NumPrimitive() > PrimitiveCullingNum) 
			//	continue;

			FAILED_CHECK(pInstacneBuffer->Render(pShader, iPassIndex, iMaterialIndex, iMeshConstainerIndex, pMeshContainer,
				pvecWorldMatrixs, fFrustumsize, pvecLimLight, pvecEmissive, pvecTimmer));

			iMeshConstainerIndex++;
		}


	}





	return S_OK;
}

HRESULT CModel::Render_ForInstancing_float4x4(CShader * pShader, _uint iPassIndex, _uint iMaterialIndex, CVIBuffer_Model_Instance * pInstacneBuffer,
	vector<_float4x4>* pvecWorldMatrixs, const char * szBoneValueName, _float fFrustumsize, vector<_float4>*  pvecLimLight,
	vector<_float4>*  pvecEmissive, vector<_float4>*  pvecTiemer ,_bool bPrimitiveCullingOn)
{
	if (iMaterialIndex >= m_iNumMaterials || nullptr == m_MeshMaterialDesc.pTexture)
		return E_FAIL;

	if (TYPE_ANIM == m_eModelType)
	{
		NULL_CHECK_RETURN(szBoneValueName, E_FAIL);
		_float4x4		BoneMatrices[150];
		_Matrix matDefualtPivot = m_DefaultPivotMatrix.XMatrix();

		_uint iMeshConstainerIndex = 0;

		for (auto& pMeshContainer : m_vecMeshContainerArr[iMaterialIndex])
		{
			//if (bPrimitiveCullingOn && pMeshContainer->Get_NumPrimitive() > PrimitiveCullingNum) 
			//	continue;

			FAILED_CHECK(pMeshContainer->Bind_AffectingBones_OnShader(pShader, matDefualtPivot, BoneMatrices, szBoneValueName, &m_vecHierarchyNode));

			FAILED_CHECK(pInstacneBuffer->Render_float4x4(pShader, iPassIndex, iMaterialIndex, iMeshConstainerIndex,
				pMeshContainer, pvecWorldMatrixs, fFrustumsize, pvecLimLight, pvecEmissive, pvecTiemer));
			iMeshConstainerIndex++;
		}
	}
	else
	{
		_uint iMeshConstainerIndex = 0;

		for (auto& pMeshContainer : m_vecMeshContainerArr[iMaterialIndex])
		{

			//if (bPrimitiveCullingOn && pMeshContainer->Get_NumPrimitive() > PrimitiveCullingNum)
			//	continue;

			FAILED_CHECK(pInstacneBuffer->Render_float4x4(pShader, iPassIndex, iMaterialIndex, iMeshConstainerIndex, pMeshContainer, 
				pvecWorldMatrixs, fFrustumsize, pvecLimLight, pvecEmissive, pvecTiemer));
			iMeshConstainerIndex++;
		}


	}



	return S_OK;
}

ATTACHBONEMATRIX_PTR CModel::Find_AttachMatrix_InHirarchyNode(const char * pName)
{
	ATTACHBONEMATRIX_PTR tReturn;

	CHierarchyNode* pNode = Find_HierarchyNode(pName);

	NULL_CHECK_BREAK(pNode);

	tReturn.pUpdatedNodeMat = pNode->Get_UpdatedTransformMat();
	tReturn.pDefaultPivotMat = &m_DefaultPivotMatrix;
	return tReturn;
}

_uint CModel::Get_HaveAnimNum()
{
	if (m_eModelType == TYPE_NONANIM)
		return 0;
	else
	{
		return _uint(m_vecAnimator.size());
	}

	return _uint();
}

_Matrix CModel::Caculate_AttachedBone(CHierarchyNode * pNode)
{
	return pNode->Get_UpdatedMatrix() * m_DefaultPivotMatrix.XMatrix();;
}

const CMeshContainer * CModel::Find_aiMesh(aiMesh * comparemesh) const
{
	if (m_pScene == nullptr)
		return nullptr;

	for (_uint i = 0; i < m_iNumMaterials; i++)
	{
		for (auto& pMeshContainer : m_vecMeshContainerArr[i])
		{
			aiMesh*		pAIMesh = pMeshContainer->Get_AiMesh();
			if (comparemesh == pAIMesh)
				return pMeshContainer;
		}
	}

	return nullptr;
}

const vector<_uint>& CModel::Get_VecMeshes_AffectingBoneIndes(aiMesh * comparemesh) const
{
	auto mesh = Find_aiMesh(comparemesh);

	if (mesh)
		return mesh->Get_AffectingBoneIndes();

	vector<_uint> vectirint;
	return vectirint;

}


const vector<CHierarchyNode*>& CModel::Get_VecBones() const
{
	return m_vecHierarchyNode;
}

const vector<CAnimationClip*>& CModel::Get_VecAni() const
{
	return m_vecAnimator;
}
_fMatrix CModel::Get_BoneMatrix(const char * pBoneName)
{
	_Matrix BoneMatrix = XMMatrixIdentity();

	CHierarchyNode*		pNode = Find_HierarchyNode(pBoneName);
	if (nullptr == pNode)
		return BoneMatrix;
	
	BoneMatrix = pNode->Get_UpdatedMatrix() * m_DefaultPivotMatrix.XMatrix();

	BoneMatrix.r[0] = XMVector3Normalize(BoneMatrix.r[0]);
	BoneMatrix.r[1] = XMVector3Normalize(BoneMatrix.r[1]);
	BoneMatrix.r[2] = XMVector3Normalize(BoneMatrix.r[2]);

	return BoneMatrix;
}

_fMatrix CModel::Get_BoneMatrix_byNode(CHierarchyNode * pHierarchyNode)
{
	_Matrix BoneMatrix = XMMatrixIdentity();

	if (nullptr == pHierarchyNode)
		return BoneMatrix;

	BoneMatrix = pHierarchyNode->Get_UpdatedMatrix() * m_DefaultPivotMatrix.XMatrix();

	BoneMatrix.r[0] = XMVector3Normalize(BoneMatrix.r[0]);
	BoneMatrix.r[1] = XMVector3Normalize(BoneMatrix.r[1]);
	BoneMatrix.r[2] = XMVector3Normalize(BoneMatrix.r[2]);

	return BoneMatrix;
}

CHierarchyNode * CModel::Get_HierarchyNode(const char * pBoneName)
{
	return Find_HierarchyNode(pBoneName);
}


HRESULT CModel::Ready_HierarchyNodes(aiNode * pNode, CHierarchyNode * pParent, _uint iDepth)
{
	NULL_CHECK_RETURN(pNode, E_FAIL);

	_float4x4		matTransformation;
	memcpy(&matTransformation, &pNode->mTransformation, sizeof(_float4x4));

	CHierarchyNode*		pHierarchyNode = CHierarchyNode::Create(pParent, pNode->mName.data, &matTransformation, iDepth);
	NULL_CHECK_RETURN(pHierarchyNode, E_FAIL);

	m_vecHierarchyNode.push_back(pHierarchyNode);

	for (_uint i = 0; i < pNode->mNumChildren; ++i)
		FAILED_CHECK( Ready_HierarchyNodes(pNode->mChildren[i], pHierarchyNode, iDepth + 1));
	

	return S_OK;
}
HRESULT CModel::Ready_HierarchyNodes(MODELDESC* desc)
{
	for (_uint i = 0; i < desc->mNumBones; ++i)
	{
		CHierarchyNode*		pHierarchyNode = CHierarchyNode::Create(&desc->mBones[i]);
		NULL_CHECK_RETURN(pHierarchyNode, E_FAIL);
		m_vecHierarchyNode.push_back(pHierarchyNode);
	}

	// For. Search ParentBone

	// �θ� �� ã��
	for (auto& node : m_vecHierarchyNode)
	{
		CHierarchyNode* parentNode = Find_HierarchyNode(node->Get_AssimpParentName());
		if(parentNode)
			node->Set_Parent(parentNode);
		else 
			node->Set_Parent(nullptr);
	}

	return S_OK;
}

HRESULT CModel::Ready_Animation(MODELDESC * desc)
{
	NULL_CHECK_RETURN(desc, E_FAIL);

	//�ش� �𵨿� �����ش� �� �ִϸ��̼��� ����
	m_iNumAnimationClip = desc->mNumAnimations;
	m_vecAnimator.reserve(m_iNumAnimationClip);
	m_vecCurrentKeyFrameIndices.resize(m_iNumAnimationClip);


	// �ִϸ��̼� ����
	for (_uint i = 0; i < m_iNumAnimationClip; ++i)
	{
		ANIDESC* anidesc = &desc->mAnimations[i];

		CAnimationClip* pAinmationClip = CAnimationClip::Create(anidesc);
		NULL_CHECK_RETURN(pAinmationClip, E_FAIL);
		m_vecAnimator.push_back(pAinmationClip);
		m_vecCurrentKeyFrameIndices[i].resize(pAinmationClip->Get_NumClipBone());
	}
	return S_OK;
}



HRESULT CModel::Ready_OffsetMatrices()
{

	for (_uint i = 0 ; i < m_iNumMaterials; i++)
	{
		for (auto& pMeshContainer : m_vecMeshContainerArr[i])
		{
			_uint		iNumAffectingBones = pMeshContainer->Get_NumAffectingBones();
			aiMesh*		pAIMesh = pMeshContainer->Get_AiMesh();

			NULL_CHECK_RETURN(pAIMesh, E_FAIL);

			//if (!iNumAffectingBones)
			//{
			//	_uint iNodeIndex = 0;
			//	CHierarchyNode*		pHierarchyNode = Find_HierarchyNode(pAIMesh->mName.data, &iNodeIndex);
			//	NULL_CHECK_RETURN(pHierarchyNode, E_FAIL);
			//	pMeshContainer->Set_TargetPararntNodeIndex(iNodeIndex);

			//}
			//else
			//{

				//������ �Ž����� ������ �޴� ��� ������ ��ȸ�ϸ鼭
				for (_uint j = 0; j < iNumAffectingBones; j++)
				{

					//Ư�� �Ž��� ������ �޴� ���� �� j��° ���� 
					//�̸��� ���� ���� ���������� ã�Ƽ�
					_uint iNodeIndex = 0;
					CHierarchyNode*		pHierarchyNode = Find_HierarchyNode(pAIMesh->mBones[j]->mName.data, &iNodeIndex);

					NULL_CHECK_RETURN(pHierarchyNode, E_FAIL);

					_float4x4		OffsetMatrix;
					memcpy(&OffsetMatrix, &(pAIMesh->mBones[j]->mOffsetMatrix), sizeof(_float4x4));

					//�������� ������ ��Ʈ������ ��������
					pHierarchyNode->Set_OffsetMatrix(&OffsetMatrix);
					//pMeshContainer->Set_OffSetMatrix(&OffsetMatrix);
					pMeshContainer->Add_AffectingBoneIndex(iNodeIndex);
				}

			//}
		}
	}

	return S_OK;
}
HRESULT CModel::Ready_OffsetMatrices(MODELDESC* modelDesc)
{
	NULL_CHECK_RETURN(modelDesc, E_FAIL);

	// modelDesc

	//for (_uint i = 0; i < m_iNumMaterials; i++)
	//{
	//	for (auto& pMeshContainer : m_vecMeshContainerArr[i])
	//	{
	//		_uint		iNumAffectingBones = pMeshContainer->Get_NumAffectingBones();
	//		aiMesh*		pAIMesh = pMeshContainer->Get_AiMesh();

	//		NULL_CHECK_RETURN(pAIMesh, E_FAIL);

	//			//������ �Ž����� ������ �޴� ��� ������ ��ȸ�ϸ鼭
	//		for (_uint j = 0; j < iNumAffectingBones; j++)
	//		{

	//			//Ư�� �Ž��� ������ �޴� ���� �� j��° ���� 
	//			//�̸��� ���� ���� ���������� ã�Ƽ�
	//			_uint iNodeIndex = 0;
	//			CHierarchyNode*		pHierarchyNode = Find_HierarchyNode(pAIMesh->mBones[j]->mName.data, &iNodeIndex);

	//			NULL_CHECK_RETURN(pHierarchyNode, E_FAIL);

	//			_float4x4		OffsetMatrix;
	//			memcpy(&OffsetMatrix, &(pAIMesh->mBones[j]->mOffsetMatrix), sizeof(_float4x4));

	//			//�������� ������ ��Ʈ������ ��������
	//			pHierarchyNode->Set_OffsetMatrix(&OffsetMatrix);
	//			//pMeshContainer->Set_OffSetMatrix(&OffsetMatrix);
	//			pMeshContainer->Add_AffectingBoneIndex(iNodeIndex);
	//		}

	//		//}
	//	}
	//}

	////// ������ �ִ� �� �ε���
	////m_iNumAffectingBones = modelDesc->mNumAffectingBones;
	////if (m_iNumAffectingBones == 0)
	////	return E_FAIL;

	////m_vecAffectingBoneIndex.reserve(m_iNumAffectingBones);
	////for (_uint i = 0; i < m_iNumAffectingBones; ++i)
	////{
	////	m_vecAffectingBoneIndex.push_back(meshdesc->mAffectingBones[i]);
	////}

	return E_FAIL;
}



HRESULT CModel::Ready_MeshContainers(_fMatrix& TransformMatrix)
{
	if (m_pModelDesc)
	{

		m_iNumMeshContainers = m_pModelDesc->mNumMeshes;
		m_iNumMaterials = m_pModelDesc->mNumMaterials;;

		m_vecMeshContainerArr = new MESHCONTAINERS[m_iNumMaterials];

		for (_uint i = 0; i < m_iNumMeshContainers; ++i)
		{
			CMeshContainer*		pMeshContainer = CMeshContainer::Create(m_pDevice, m_pDeviceContext, m_eModelType, &m_pModelDesc->mMeshDesc[i], TransformMatrix);
			NULL_CHECK_RETURN(pMeshContainer, E_FAIL);
			m_vecMeshContainerArr[m_pModelDesc->mMeshDesc[i].mMaterialIndex].push_back(pMeshContainer);
#ifdef _DEBUG
			//string Name = m_pScene->mMeshes[i]->mName.data;
			//string ttszLog ="Meterial Index : "+ to_string(m_pScene->mMeshes[i]->mMaterialIndex) + "  MeshName: " + Name + " Affecting Bond Num : " + to_string(m_pScene->mMeshes[i]->mNumBones) + "\n";
			//wstring ttDebugLog;
			//ttDebugLog.assign(ttszLog.begin(), ttszLog.end());

			//OutputDebugStringW(ttDebugLog.c_str());

#endif
			

		}
	}

	else
	{

		NULL_CHECK_RETURN(m_pScene, E_FAIL);

		m_iNumMeshContainers = m_pScene->mNumMeshes;
		m_iNumMaterials = m_pScene->mNumMaterials;

		m_vecMeshContainerArr = new MESHCONTAINERS[m_iNumMaterials];

		for (_uint i = 0; i < m_iNumMeshContainers; ++i)
		{
			CMeshContainer*		pMeshContainer = CMeshContainer::Create(m_pDevice, m_pDeviceContext, m_eModelType, m_pScene->mMeshes[i], TransformMatrix);
			NULL_CHECK_RETURN(pMeshContainer, E_FAIL);
			m_vecMeshContainerArr[m_pScene->mMeshes[i]->mMaterialIndex].push_back(pMeshContainer);

#ifdef _DEBUG
			//string Name = m_pScene->mMeshes[i]->mName.data;
			//string ttszLog ="Meterial Index : "+ to_string(m_pScene->mMeshes[i]->mMaterialIndex) + "  MeshName: " + Name + " Affecting Bond Num : " + to_string(m_pScene->mMeshes[i]->mNumBones) + "\n";
			//wstring ttDebugLog;
			//ttDebugLog.assign(ttszLog.begin(), ttszLog.end());

			//OutputDebugStringW(ttDebugLog.c_str());

#endif
		}
	}

	return S_OK;
}

HRESULT CModel::Ready_Materials(const char * pModelFilePath)
{

	NULL_CHECK_RETURN(m_pScene, E_FAIL);


	ZeroMemory(&m_MeshMaterialDesc, sizeof(MESHMATERIALDESC));

	m_MeshMaterialDesc.pTexture = CTexture::Create(m_pDevice, m_pDeviceContext);

	NULL_CHECK_RETURN(m_MeshMaterialDesc.pTexture, E_FAIL);

	for (_uint i = 0; i < m_iNumMaterials; ++i)
	{

		FAILED_CHECK(m_MeshMaterialDesc.pTexture->Insert_Empty_TextureLayer((_tchar*)(to_wstring(i).c_str())));

		for (_uint j = 1; j < AI_TEXTURE_TYPE_MAX; ++j)
		{
			aiString	TexturePath;

			if (FAILED(m_pScene->mMaterials[i]->GetTexture(aiTextureType(j), 0, &TexturePath)))
				continue;

			char		szFullPath[MAX_PATH] = "";
			char		szFileName[MAX_PATH] = "";
			char		szExt[MAX_PATH] = "";

			_splitpath_s(TexturePath.data, nullptr, 0, nullptr, 0, szFileName, MAX_PATH, szExt, MAX_PATH);


			if (!strcmp(szExt, ".tga"))
			{
				ZeroMemory(szExt, sizeof(char)*MAX_PATH);
				strcpy_s(szExt, ".png");
			}


			strcpy_s(szFullPath, pModelFilePath);
			strcat_s(szFullPath, szFileName);
			strcat_s(szFullPath, szExt);


			_tchar		szTextureFullPath[MAX_PATH] = TEXT("");
			MultiByteToWideChar(CP_ACP, 0, szFullPath, (int)strlen(szFullPath), szTextureFullPath, MAX_PATH);

			FAILED_CHECK(m_MeshMaterialDesc.pTexture->Insert_Texture_On_BindedLayer(j, szTextureFullPath));


		}
	}

	return S_OK;
}

HRESULT CModel::Ready_Materials(const wchar_t * pModelFilePath)
{
	if (m_pModelDesc == nullptr)
		return E_FAIL;

	m_pScene = nullptr;

	ZeroMemory(&m_MeshMaterialDesc, sizeof(MESHMATERIALDESC));
	m_MeshMaterialDesc.pTexture = CTexture::Create(m_pDevice, m_pDeviceContext);
	NULL_CHECK_RETURN(m_MeshMaterialDesc.pTexture, E_FAIL);

	for (_uint i = 0; i < m_iNumMaterials; ++i)
	{
		FAILED_CHECK(m_MeshMaterialDesc.pTexture->Insert_Empty_TextureLayer((_tchar*)(to_wstring(i).c_str())));

//		FAILED_CHECK(m_MeshMaterialDesc.pTexture->Insert_Empty_TextureLayer((_tchar*)(to_wstring(i).c_str())));

		for (_uint j = 1; j < AI_TEXTURE_TYPE_MAX; ++j)
		{
			wstring		TexturePath;
			TexturePath = m_pModelDesc->mMaterials[i].MatName[j];
			string		TexturePathstr = CHelperClass::Convert_Wstr2str(TexturePath);
		


			// �𵨰� ���� ���
			char		szFullPath[MAX_PATH] = "";
			char		szFileName[MAX_PATH] = "";
			char		szExt[MAX_PATH] = "";

			_splitpath_s(TexturePathstr.c_str(), nullptr, 0, nullptr, 0, szFileName, MAX_PATH, szExt, MAX_PATH);


			if (!strcmp(szExt, ".tga"))
			{
				ZeroMemory(szExt, sizeof(char)*MAX_PATH);
				strcpy_s(szExt, ".png");
			}

			wstring wstr = pModelFilePath;
			string fullpath = CHelperClass::Convert_Wstr2str(wstr);
			strcpy_s(szFullPath, fullpath.c_str());
			char		szFilePath[MAX_PATH] = "";

			_splitpath_s(szFullPath, nullptr, 0, szFilePath, MAX_PATH, nullptr, 0, nullptr, 0);
			strcat_s(szFilePath, szFileName);
			strcat_s(szFilePath, szExt);



			_tchar		szTextureFullPath[MAX_PATH] = TEXT("");
			MultiByteToWideChar(CP_ACP, 0, szFilePath, (int)strlen(szFilePath), szTextureFullPath, MAX_PATH);
			
			FAILED_CHECK(m_MeshMaterialDesc.pTexture->Insert_Texture_On_BindedLayer(j, szTextureFullPath));
		}
	}

	return S_OK;
}

HRESULT CModel::Ready_Animation()
{
	NULL_CHECK_RETURN(m_pScene, E_FAIL);

	//�ش� �𵨿� �����ش� �� �ִϸ��̼��� ����
	m_iNumAnimationClip = m_pScene->mNumAnimations;
	m_vecCurrentKeyFrameIndices.resize(m_iNumAnimationClip);


	//��ŭ ��� �ִϸ��̼��� ��ȸ�ϸ鼭
	for (_uint i = 0 ; i < m_iNumAnimationClip; i++)
	{
		//�ش� �𵨿� �����ϴ� i��° �ִϸ��̼�
		aiAnimation* paiAnimation = m_pScene->mAnimations[i];

		//�� ������ �ִϸ��̼� Ŭ���� �ϳ� �����
		CAnimationClip* pAinmationClip = CAnimationClip::Create(paiAnimation->mName.data, paiAnimation->mDuration, paiAnimation->mTicksPerSecond);
		NULL_CHECK_RETURN(pAinmationClip,E_FAIL);


#ifdef _DEBUG
		string szLog = "Anim Name : " + string(paiAnimation->mName.data) + "\n";
		wstring DebugLog;
		DebugLog.assign(szLog.begin(), szLog.end());

		OutputDebugStringW(DebugLog.c_str());
#endif


		//���� �ִϸ��̼� Ŭ���� �ִϸ��̼� �� ������ŭ ������ Ȯ���ϰ�
		pAinmationClip->Reserve(paiAnimation->mNumChannels);
		m_vecCurrentKeyFrameIndices[i].resize(paiAnimation->mNumChannels);

		for (_uint j = 0 ; j < paiAnimation->mNumChannels; j++)
		{
			//�ش� �ִϸ��̼ǿ��� ������ �޴� j��° ���� ������ �̿��ؼ�
			aiNodeAnim*	pAIChannel = paiAnimation->mChannels[j];

			//�ش� ���� ���� �̸��� ���̾Ű ��带 ã�Ƽ�
			_uint iNodeIndex = 0;
			CHierarchyNode*		pHierarchyNode = Find_HierarchyNode(pAIChannel->mNodeName.data,&iNodeIndex);
			NULL_CHECK_RETURN(pHierarchyNode, E_FAIL);

			//�ش� ���� �����
			CClipBone* pClipBone = CClipBone::Create(pAIChannel->mNodeName.data, _int(iNodeIndex));
			NULL_CHECK_RETURN(pClipBone,E_FAIL);

			//�ش� ���� �ִ� Ű������(�ش� ���� �ִϸ��̼� ������� ���������ϴ� ����)�� ���ؼ�
			_uint		iNumKeyFrames = max(pAIChannel->mNumScalingKeys, pAIChannel->mNumRotationKeys);
			iNumKeyFrames = max(iNumKeyFrames, pAIChannel->mNumPositionKeys);

			//�ش� ������ Ű������ ������ Ȯ���س���
			pClipBone->Reserve(iNumKeyFrames);

			//���� �������� ���� ���������� ä���ֱ� ���� ����
			//ex �� 5�������� 3�����ӹۿ� ���� �ִϸ��̼��� ���� ���� �������� �����ϴ� �뵵
			_float3		vScale;
			_float4		vRotation;
			_float3		vPosition;
			_double		Time;

			//��� Ű�������� ��ȸ�ϸ鼭
			for (_uint k = 0 ; k < iNumKeyFrames; k++)
			{
				//Ű�������� �����Ѵ�
				KEYFRAME*			pKeyFrame = new KEYFRAME;
				ZeroMemory(pKeyFrame, sizeof(KEYFRAME));


				//���� �������� ���� ���������� ä���ֱ� ���� ���� �˻�
				if (pAIChannel->mNumScalingKeys > k)
				{
					vScale = _float3(pAIChannel->mScalingKeys[k].mValue);
					Time = pAIChannel->mScalingKeys[k].mTime;
				}
				if (pAIChannel->mNumRotationKeys > k)
				{
					vRotation = _float4(pAIChannel->mRotationKeys[k].mValue);
					Time = pAIChannel->mRotationKeys[k].mTime;
				}
				if (pAIChannel->mNumPositionKeys > k)
				{
					vPosition = _float3(pAIChannel->mPositionKeys[k].mValue);
					Time = pAIChannel->mPositionKeys[k].mTime;
				}

				//���� �˻縦 ��ģ ������ ������ Ű�����ӿ� �־��ְ�
				pKeyFrame->vScale = vScale;
				pKeyFrame->vRotation = vRotation;
				pKeyFrame->vPosition = vPosition;
				pKeyFrame->Time = Time;

				//Ű�������� ��������� ���� �ش� Ű������(������)�� �־��ش�
				pClipBone->Add_KeyFrame(pKeyFrame);
			}

			//Ű�����ӱ��� �� ä���� ���� �����Ǿ����� �ش� ���� �ִϸ��̼� Ŭ���� �־��ְ�
			pAinmationClip->Add_ClipBone(pClipBone);
		}

		//���������� ���� ���� ������ ��� �� ������ �ִϸ��̼��� ���ϸ����Ϳ� �־��ش�.
		m_vecAnimator.push_back(pAinmationClip);
	}


	return S_OK;
}

HRESULT CModel::Ready_MoreAnimation(const char * szFileFullPath, _uint iAnimCount, _uint iFlag )
{
	char FullPath[MAX_PATH] = "";

	strcpy_s(FullPath, string(szFileFullPath).substr(0,strlen(szFileFullPath) - 4).c_str());


	for (_uint AnimIndex = 0; AnimIndex< iAnimCount - 1; AnimIndex++)
	{
		char LoopFileFullPath[MAX_PATH] = "";
		char LoopFilePath[MAX_PATH] = "";
		sprintf_s(LoopFilePath, "_%d.FBX", AnimIndex);

		strcpy_s(LoopFileFullPath, FullPath);
		strcat_s(LoopFileFullPath, LoopFilePath);


		const aiScene*				pScene = nullptr;
		Importer				Importer;

		pScene = Importer.ReadFile(LoopFileFullPath, iFlag);


		NULL_CHECK_RETURN(pScene, E_FAIL);

		//�ش� �𵨿� �����ش� �� �ִϸ��̼��� ����
		_uint iNumAnimClip = pScene->mNumAnimations;
		m_iNumAnimationClip += iNumAnimClip;
		_uint iNumOldAnimClip = _uint(m_vecCurrentKeyFrameIndices.size());
		m_vecCurrentKeyFrameIndices.resize(m_iNumAnimationClip);


#ifdef _DEBUG
		string ttszLog = "Num AnimationClip: " + to_string(m_iNumAnimationClip) + "\n";
		wstring ttDebugLog;
		ttDebugLog.assign(ttszLog.begin(), ttszLog.end());

		OutputDebugStringW(ttDebugLog.c_str());

#endif
		//��ŭ ��� �ִϸ��̼��� ��ȸ�ϸ鼭
		for (_uint i = 0; i < iNumAnimClip; i++)
		{
			//�ش� �𵨿� �����ϴ� i��° �ִϸ��̼�
			aiAnimation* paiAnimation = pScene->mAnimations[i];

			//�� ������ �ִϸ��̼� Ŭ���� �ϳ� �����
			CAnimationClip* pAinmationClip = CAnimationClip::Create(paiAnimation->mName.data, paiAnimation->mDuration, paiAnimation->mTicksPerSecond);
			NULL_CHECK_RETURN(pAinmationClip, E_FAIL);

#ifdef _DEBUG
			string szLog = "Anim Name : " + string(paiAnimation->mName.data) + "\n";
			wstring DebugLog;
			DebugLog.assign(szLog.begin(), szLog.end());

			OutputDebugStringW(DebugLog.c_str());
#endif


			//���� �ִϸ��̼� Ŭ���� �ִϸ��̼� �� ������ŭ ������ Ȯ���ϰ�
			pAinmationClip->Reserve(paiAnimation->mNumChannels);
			m_vecCurrentKeyFrameIndices[iNumOldAnimClip + i].resize(paiAnimation->mNumChannels);


			for (_uint j = 0; j < paiAnimation->mNumChannels; j++)
			{
				//�ش� �ִϸ��̼ǿ��� ������ �޴� j��° ���� ������ �̿��ؼ�
				aiNodeAnim*	pAIChannel = paiAnimation->mChannels[j];

				//�ش� ���� ���� �̸��� ���̾Ű ��带 ã�Ƽ�
				_uint iNodeIndex = 0;
				CHierarchyNode*		pHierarchyNode = Find_HierarchyNode(pAIChannel->mNodeName.data, &iNodeIndex);
				NULL_CHECK_RETURN(pHierarchyNode, E_FAIL);

				//�ش� ���� �����
				CClipBone* pClipBone = CClipBone::Create(pAIChannel->mNodeName.data, _int(iNodeIndex));
				NULL_CHECK_RETURN(pClipBone, E_FAIL);

				//�ش� ���� �ִ� Ű������(�ش� ���� �ִϸ��̼� ������� ���������ϴ� ����)�� ���ؼ�
				_uint		iNumKeyFrames = max(pAIChannel->mNumScalingKeys, pAIChannel->mNumRotationKeys);
				iNumKeyFrames = max(iNumKeyFrames, pAIChannel->mNumPositionKeys);

				//�ش� ������ Ű������ ������ Ȯ���س���
				pClipBone->Reserve(iNumKeyFrames);

				//���� �������� ���� ���������� ä���ֱ� ���� ����
				//ex �� 5�������� 3�����ӹۿ� ���� �ִϸ��̼��� ���� ���� �������� �����ϴ� �뵵
				_float3		vScale;
				_float4		vRotation;
				_float3		vPosition;
				_double		Time;

				//��� Ű�������� ��ȸ�ϸ鼭
				for (_uint k = 0; k < iNumKeyFrames; k++)
				{
					//Ű�������� �����Ѵ�
					KEYFRAME*			pKeyFrame = new KEYFRAME;
					ZeroMemory(pKeyFrame, sizeof(KEYFRAME));


					//���� �������� ���� ���������� ä���ֱ� ���� ���� �˻�
					if (pAIChannel->mNumScalingKeys > k)
					{
						vScale = _float3(pAIChannel->mScalingKeys[k].mValue);
						Time = pAIChannel->mScalingKeys[k].mTime;
					}
					if (pAIChannel->mNumRotationKeys > k)
					{
						vRotation = _float4(pAIChannel->mRotationKeys[k].mValue);
						Time = pAIChannel->mRotationKeys[k].mTime;
					}
					if (pAIChannel->mNumPositionKeys > k)
					{
						vPosition = _float3(pAIChannel->mPositionKeys[k].mValue);
						Time = pAIChannel->mPositionKeys[k].mTime;
					}

					//���� �˻縦 ��ģ ������ ������ Ű�����ӿ� �־��ְ�
					pKeyFrame->vScale = vScale;
					pKeyFrame->vRotation = vRotation;
					pKeyFrame->vPosition = vPosition;
					pKeyFrame->Time = Time;

					//Ű�������� ��������� ���� �ش� Ű������(������)�� �־��ش�
					pClipBone->Add_KeyFrame(pKeyFrame);
				}

				//Ű�����ӱ��� �� ä���� ���� �����Ǿ����� �ش� ���� �ִϸ��̼� Ŭ���� �־��ְ�
				pAinmationClip->Add_ClipBone(pClipBone);
			}

			//���������� ���� ���� ������ ��� �� ������ �ִϸ��̼��� ���ϸ����Ϳ� �־��ش�.
			m_vecAnimator.push_back(pAinmationClip);
		}


		Importer.FreeScene();
	}

	return S_OK;
}

CHierarchyNode * CModel::Find_HierarchyNode(const char * pName, _uint* pNodeIndex )
{

	CHierarchyNode*	pHierarchyNode = nullptr;

	for (_uint i = 0 ; i< m_vecHierarchyNode.size(); i++)
	{
		if(!strcmp(m_vecHierarchyNode[i]->Get_Name(), pName))
		{
			pHierarchyNode = (m_vecHierarchyNode[i]);
			if (pNodeIndex != nullptr)
				*pNodeIndex = i;
			break;
		}
	}
	return pHierarchyNode;
}

CModel * CModel::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, MODELTYPE eModelType, const char * pModelFilePath, const char * pModelFileName, _fMatrix& TransformMatrix, _uint iAnimCount)
{
	CModel*	pInstance = new CModel(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(eModelType, pModelFilePath, pModelFileName, TransformMatrix, iAnimCount)))
	{
		MSGBOX("Failed to Created CModel");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CModel * CModel::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, MODELTYPE eModelType, MODELDESC * desc, _fMatrix & TransformMatrix, _uint iAnimCount)
{
	CModel*	pInstance = new CModel(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(eModelType, desc, TransformMatrix)))
	{
		MSGBOX("Failed to Created CModel");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CModel::Clone(void * pArg)
{
	CModel*	pInstance = new CModel(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CModel");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CModel::Free()
{
	__super::Free();
	
	for (auto& pAnimationClip : m_vecAnimator)
	{
		Safe_Release(pAnimationClip);
	}
	m_vecAnimator.clear();

	for (auto& pHierarchyNode : m_vecHierarchyNode)
			Safe_Release(pHierarchyNode);


	for (_uint i = 0; i < m_iNumMaterials; i++)
	{
		for (auto& pMeshcontainer : m_vecMeshContainerArr[i])
		{
			CMeshContainer* TempForRelease = pMeshcontainer;
			Safe_Release(TempForRelease);
		}
		if (!m_bIsClone)
			m_vecMeshContainerArr[i].clear();
	}
	if (!m_bIsClone)
	{
		m_Importer.FreeScene();
		Safe_Delete_Array(m_vecMeshContainerArr);

	//	Safe_Delete(m_pModelDesc);
	}


	Safe_Release(m_MeshMaterialDesc.pTexture);

	for (_uint i = 0; i < m_vecCurrentKeyFrameIndices.size(); i++)
	{
		m_vecCurrentKeyFrameIndices[i].clear();
	}
	m_vecCurrentKeyFrameIndices.clear();


}
