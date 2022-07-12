#pragma once
#include "MapObject.h"


BEGIN(Client)

class CDemon_Tree :public CMapObject
{
private:
	CDemon_Tree(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CDemon_Tree(const CDemon_Tree& rhs);
	virtual ~CDemon_Tree() = default;

public:
	virtual HRESULT Initialize_Prototype(void* pArg)override;
	virtual HRESULT Initialize_Clone(void* pArg)override;

public:
	virtual _int Update(_double fDeltaTime)override;
	virtual _int LateUpdate(_double fDeltaTime)override;
	virtual _int Render()override;
	virtual _int LateRender()override;

private:
//	CShader*						m_pShaderCom = nullptr;
//	CRenderer*						m_pRendererCom = nullptr;
	CTransform*						m_pTransformCom = nullptr;
//	CModel*							m_pModel = nullptr;

	_int							m_iCompleteCount = 0;//�� ������ �´����� üũ

	vector<class CTreeMesh*>			m_pTreeMeshs;
private:
	HRESULT SetUp_Components();

public:
	static CDemon_Tree* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END