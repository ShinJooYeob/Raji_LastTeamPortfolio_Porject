#pragma once
#include "VIBuffer.h"
#include "Model.h"

BEGIN(Engine)
class CHierarchyNode;

class CMeshContainer final : public CVIBuffer
{

private:
	explicit CMeshContainer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	explicit CMeshContainer(const CMeshContainer& rhs);
	virtual ~CMeshContainer() = default;

public:
	virtual HRESULT Initialize_Prototype(CModel::MODELTYPE eMeshtype, aiMesh* pAIMesh, _fMatrix& TransformMatrix);
	virtual HRESULT Initialize_Prototype(CModel::MODELTYPE eMeshtype, MESHDESC* pAIMesh, _fMatrix& TransformMatrix);
	virtual HRESULT Initialize_Clone(void* pArg);

	HRESULT Bind_AffectingBones_OnShader(CShader* pShader, _fMatrix& DefultPivotMatrix, _float4x4* pBoneMatrices, const char* szBoneName, const vector<CHierarchyNode*>* pVecHierarchyNodes);
	HRESULT Bind_AffectingBones_OnShader(CShader* pShader, _fMatrix& DefultPivotMatrix, _float4x4* pBoneMatrices, const char* szBoneName, vector<_float4x4>* pUpdateMatrix,	_bool bBool);
public:
	_uint		Get_NumPrimitive() { return m_iNumPrimitive; }
	_uint		Get_MaterialIndex();
	_uint		Get_NumAffectingBones() { return m_iNumAffectingBones; };
	aiMesh*		Get_AiMesh() { return m_pAIMesh; };
	HRESULT		Add_AffectingBoneIndex(_uint iHierarchyIndex);
	//void		Set_OffSetMatrix(_float4x4* OffSetMatrix);
	void		Get_InstancingData(FORINSTDATA* pOut);
	void		Get_IndexBufferData(FORINDEXDATA* pOut);

	void		Set_TargetPararntNodeIndex(_uint iNodeIndex) { m_iParantHierarchyNodeIndex = iNodeIndex; }
	//_uint		Get_TargetPararntNodeIndex() {return m_iParantHierarchyNodeIndex ; }
	

	const vector<_uint>& Get_AffectingBoneIndes() const
	{
		return m_vecAffectingBoneIndex;
	}
private:
	//�� �Ž��� ����ϴ� ���׸����� �ε���
	_uint		m_MaterialIndex = 0;
	//�� �Ž��� ������ ��ġ�� ���� �� ����
	_uint		m_iNumAffectingBones = 0;
	//�� �Ž���		AiMesh
	aiMesh*			m_pAIMesh = nullptr;
	_uint			m_iParantHierarchyNodeIndex = 0;

	/* ���� �޽ÿ� ������ �ִ� ����. */
	vector<_uint>		m_vecAffectingBoneIndex;
	FACEINDICES32*		m_pIndices = nullptr;

	//_float4x4		m_matOffSet = XMMatrixIdentity();
private:
	HRESULT Ready_NonAnimMeshContainer(aiMesh* pAIMesh, _fMatrix& TransformMatrix);
	HRESULT Ready_AnimMeshContainer(aiMesh* pAIMesh);
	HRESULT Ready_SkinnedInfo(aiMesh* pAIMesh, VTXANIMMODEL* pVertices);

	HRESULT Ready_NonAnimMeshContainer(MESHDESC* meshDesc, _fMatrix& TransformMatrix);
	HRESULT Ready_AnimMeshContainer(MESHDESC* meshDesc);
	HRESULT Ready_SkinnedInfo(MESHDESC* meshDesc, VTXANIMMODEL* pVertices);

public:
	static CMeshContainer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, 
		CModel::MODELTYPE eMeshtype, aiMesh* pAIMesh, _fMatrix& TransformMatrix);

	static CMeshContainer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext,
		CModel::MODELTYPE eMeshtype, MESHDESC* meshdesc, _fMatrix& TransformMatrix);

	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END