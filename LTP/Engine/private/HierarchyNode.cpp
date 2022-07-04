#include "..\public\HierarchyNode.h"



CHierarchyNode::CHierarchyNode()
{
}


HRESULT CHierarchyNode::Initialize_HierarchyNode(CHierarchyNode* pParent, const char* pName, _float4x4* TransformationMatrix, _uint iDepth)
{
	if (iDepth != 0 && (pParent == nullptr || pName == nullptr || TransformationMatrix == nullptr)) return E_FAIL;

	m_pParent = pParent;
	m_szName = string(pName);
	memcpy(&m_matTransformation, TransformationMatrix, sizeof(_float4x4));
	XMStoreFloat4x4(&m_matCombinedTransformation, XMMatrixIdentity());
	XMStoreFloat4x4(&m_matUpdatedTransform, XMMatrixIdentity());
	XMStoreFloat4x4(&m_matOffset, XMMatrixIdentity());
	
	m_iDepth = iDepth;

	return S_OK;
}

HRESULT CHierarchyNode::Initialize_HierarchyNode(BONEDESC * desc)
{
	if (desc == nullptr)
		return E_FAIL;

	XMStoreFloat4x4(&m_matCombinedTransformation, XMMatrixIdentity());
	XMStoreFloat4x4(&m_matUpdatedTransform, XMMatrixIdentity());
	XMStoreFloat4x4(&m_matTransformation, XMMatrixIdentity());
	XMStoreFloat4x4(&m_matOffset, XMMatrixIdentity());


	m_iDepth = desc->mDepth;
	m_szName = desc->mCurrentBoneName;
	m_szParentName = desc->mParentBoneName;
	//m_matOffset = desc->mOffsetMat;
	Set_OffsetMatrix(&desc->mOffsetMat);
	m_matTransformation = desc->mTransMat;
	


	return S_OK;
}



void CHierarchyNode::Update_CombinedMatrix()
{
	if (m_pParent == nullptr)
	{
		m_matCombinedTransformation = m_matTransformation;
	}
	else
	{
		m_matCombinedTransformation = m_matTransformation.XMatrix() * (m_pParent->m_matCombinedTransformation).XMatrix();
	}

	m_matUpdatedTransform = m_matOffset.XMatrix() * m_matCombinedTransformation.XMatrix();
}


CHierarchyNode * CHierarchyNode::Create(CHierarchyNode* pParent, const char * pName, _float4x4* TransformationMatrix, _uint iDepth)
{
	CHierarchyNode*	pInstance = new CHierarchyNode();

	if (FAILED(pInstance->Initialize_HierarchyNode(pParent, pName,TransformationMatrix,iDepth)))
	{
		MSGBOX("Failed to Created CHierarchyNode");
		Safe_Release(pInstance);
	}
	return pInstance;
}
CHierarchyNode * CHierarchyNode::Create(BONEDESC* bonedesc)
{
	CHierarchyNode*	pInstance = new CHierarchyNode();

	if (FAILED(pInstance->Initialize_HierarchyNode(bonedesc)))
	{
		MSGBOX("Failed to Created CHierarchyNode");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHierarchyNode::Free()
{
}

