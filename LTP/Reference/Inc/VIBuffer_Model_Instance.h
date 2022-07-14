#pragma once

#include "VIBuffer.h"

BEGIN(Engine)
class CMeshContainer;
class CTransform;

#define MAXMATERAILCOUNT 64

class CVIBuffer_Model_Instance final : public CVIBuffer
{
private:
	typedef struct tagIndexBufferDesc
	{
		ID3D11Buffer*				pIB = nullptr;
		D3D11_BUFFER_DESC			IBDesc;
		DXGI_FORMAT					eIndexFormat;
		D3D11_PRIMITIVE_TOPOLOGY	eTopology;
		_uint						iNumPrimitive;
		D3D11_SUBRESOURCE_DATA		IBSubResourceData;

		_uint						iIndexCountPerInstance;
	}INDEXBUFFERDESC;


public:
	CVIBuffer_Model_Instance(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CVIBuffer_Model_Instance(const CVIBuffer_Model_Instance& rhs);
	virtual ~CVIBuffer_Model_Instance() = default;

public:
	virtual HRESULT Initialize_Prototype(_uint iNumInstance);
	virtual HRESULT Initialize_Clone(void* pArg) override;
	virtual HRESULT Render(class CShader* pShader, _uint iPassIndex, _uint iMatreialIndex ,_uint iMeshContainerIndex 
		,CMeshContainer* pMeshContainer, vector<CTransform*>* pvecWorldMatrixs, _float fFrustumsize ,
		vector<_float4>*  pvecLimLight, vector<_float4>*  pvecEmissive, vector<_float4>*  pvecTimmer);

	virtual HRESULT Render_float4x4(class CShader* pShader, _uint iPassIndex, _uint iMatreialIndex, _uint iMeshContainerIndex
		, CMeshContainer* pMeshContainer, vector<_float4x4>* pvecWorldMatrixs, _float fFrustumsize,
		vector<_float4>*  pvecLimLight, vector<_float4>*  pvecEmissive, vector<_float4>*  pvecTiemer);

private:
	/* �ν��Ͻ��ϳ��� ǥ���Ǿ���� ����� �������μ� �ν��Ͻ��� ������ŭ ������ �ִ� ���� ���� . */
	ID3D11Buffer*				m_pVBInstance;
	D3D11_BUFFER_DESC			m_VBInstDesc;
	D3D11_SUBRESOURCE_DATA		m_VBInstSubResource;
	_uint						m_iNumInstance = 0;

	vector<INDEXBUFFERDESC>		m_vecIndexBufferArr[MAXMATERAILCOUNT];

public:
	static CVIBuffer_Model_Instance* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, _uint iNumInstance);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END