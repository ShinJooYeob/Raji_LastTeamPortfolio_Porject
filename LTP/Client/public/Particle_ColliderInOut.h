#pragma once

#include "GameObject.h"

BEGIN(Client)

class CParticle_ColliderInOut : public CGameObject
{
public:
	typedef struct tagSettingColliderInOut
	{
		COLLIDERTYPE	ColliderType = COLLIDERTYPE_END;
		COLLIDERDESC	ColliderDesc;
		CTransform*		pTargetTransform = nullptr;

	}SETTINGCOLLIDERINOUT;


private:
	CParticle_ColliderInOut(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CParticle_ColliderInOut(const CParticle_ColliderInOut& rhs);
	virtual ~CParticle_ColliderInOut() = default;

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

	private:
	CRenderer*						m_pRendererCom = nullptr;
	CCollider*						m_pCollider = nullptr;

	SETTINGCOLLIDERINOUT			m_pColliderDesc;

private:
	HRESULT SetUp_Components();


public:
	static CParticle_ColliderInOut* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END