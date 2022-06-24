#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
public:
	CVIBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype(void* pArg)override;
	virtual HRESULT Initialize_Clone(void* pArg)override;


public:
	virtual HRESULT Render(class CShader* pShader, _uint iPassIndex);

protected:
	ID3D11Buffer*				m_pVB = nullptr;
	D3D11_BUFFER_DESC			m_VBDesc;
	D3D11_SUBRESOURCE_DATA		m_VBSubResourceData;
	//������ ����
	_uint						m_iNumVertices = 0;
	//���ؽ� ���۰� ��ΰ�(�ѹ��� �������� ���۸� ���ε��Ͽ� �׸����ִ�)
	_uint						m_iNumVertexBuffers = 0;


	_float3*					m_pVertices = nullptr;

protected:
	ID3D11Buffer*				m_pIB = nullptr;
	D3D11_BUFFER_DESC			m_IBDesc;
	D3D11_SUBRESOURCE_DATA		m_IBSubResourceData;

	//�ε���(�ﰢ��)�� �� ����
	_uint						m_iNumPrimitive = 0;
	//�ѹ� �׸��� ��� �ε����� �̾Ƽ� �׸��°�
	_uint						m_iNumIndicesPerPrimitive = 0;
	//�ε��� ���� (ex : DXGI_FORMAT_R16_UINT)
	DXGI_FORMAT					m_eIndexFormat;
	//�׸��� ��� (ex : D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	D3D11_PRIMITIVE_TOPOLOGY	m_eTopology;


protected:
	HRESULT Create_VertexBuffer();
	HRESULT Create_IndexBuffer();

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END