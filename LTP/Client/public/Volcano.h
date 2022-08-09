#pragma once
#include "MonsterWeapon.h"

BEGIN(Client)
class CVolcano final : public CMonsterWeapon
{
private:
	CVolcano(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CVolcano(const CVolcano& rhs);
	virtual ~CVolcano() = default;

public:
	virtual HRESULT Initialize_Prototype(void* pArg)override;
	virtual HRESULT Initialize_Clone(void* pArg)override;

public:
	virtual _int Update(_double fDeltaTime)override;
	virtual _int LateUpdate(_double fDeltaTime)override;
	virtual _int Render()override;
	virtual _int LateRender()override;

	virtual void CollisionTriger(class CCollider* pMyCollider, _uint iMyColliderIndex, CGameObject* pConflictedObj, class CCollider* pConflictedCollider,
		_uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType) override;

	static void VolcanoCount2Zero() { iPatterenCount = 0; }

private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModel = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CCollider*			m_pCollider = nullptr;

	static				_uint iPatterenCount;
private:
	_float				m_fAliveTime = 3.f;
	_float				m_fCurTime_Duration = 0;
	NONINSTNESHEFTDESC	m_tVolcanoDesc;
	NONINSTNESHEFTDESC	m_tSubFlameDesc;

private:
	HRESULT		Ready_MeshDesc();
	HRESULT		SetUp_Components();
	HRESULT		Setup_MeshDesc();

public:
	static CVolcano* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END