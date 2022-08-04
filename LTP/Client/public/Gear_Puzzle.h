#pragma once
#include "MapObject.h"


BEGIN(Client)

class CGear_Puzzle :public CMapObject
{
private:
	CGear_Puzzle(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CGear_Puzzle(const CGear_Puzzle& rhs);
	virtual ~CGear_Puzzle() = default;

public:
	virtual HRESULT Initialize_Prototype(void* pArg)override;
	virtual HRESULT Initialize_Clone(void* pArg)override;

public:
	virtual _int Update(_double dDeltaTime)override;
	virtual _int LateUpdate(_double dDeltaTime)override;
	virtual _int Render()override;
	virtual _int LateRender()override;

private:
	HRESULT SetUp_Components();
	HRESULT	SetUp_Collider();
	

private:
	HRESULT Update_Collider(_double dDeltaTime);

private:
	CShader*			m_pShaderCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CModel*				m_pModel = nullptr;

	CCollider*			m_pColliderCom = nullptr;

public:
	static CGear_Puzzle* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END