#pragma once
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	explicit CGameObject(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	explicit CGameObject(const CGameObject&  rhs);
	virtual ~CGameObject() = default;
public:
	virtual HRESULT Initialize_Prototype(void* pArg);
	virtual HRESULT Initialize_Clone(void* pArg);

	virtual _int Update(_double fDeltaTime);
	virtual _int LateUpdate(_double fDeltaTime);
	virtual _int Render();
	virtual _int LateRender();

	virtual void CollisionTriger(class CCollider* pMyCollider, _uint iMyColliderIndex, CGameObject* pConflictedObj, class CCollider* pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType) {};

	virtual void CollisionPhysX_Trigger(CGameObject* pTriggerObj, _uint id , COLLIDERTYPE_PhysXID eConflictedObjCollisionType){}
	virtual void CollisionPhysX_Rigid(CGameObject* pOtherObject, _uint id , COLLIDERTYPE_PhysXID eConflictedObjCollisionType){}

	virtual _float Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower);
	virtual _float Take_Damage_Instance(CGameObject* pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback = false, _float fKnockbackPower = 0.f);

public:
	virtual void Set_NowSceneNum(_uint eNowSceneNum) {	m_eNowSceneNum = eNowSceneNum; };

	virtual _fVector Get_BonePos(const char* pBoneName);
	virtual _fMatrix Get_BoneMatrix(const char* pBoneName);

	void Set_NameTag(const _tchar* szNameTag) {	m_szNameTag = szNameTag;};
	const _tchar* Get_NameTag() { return m_szNameTag; };
	
	virtual _float	Get_RenderSortValue() { return m_fRenderSortValue; };
	virtual _float	Compute_RenderSortValue();

	virtual void Set_IsDead()
	{
		m_bIsDead = true;
		m_bIsOwnerDead = true;
	}
	_bool Get_IsDead() {
		return m_bIsDead;
		m_bIsOwnerDead = true;
	}
	_bool	Get_IsOwerDead() { return m_bIsOwnerDead; };
	void	Set_IsOwerDead(_bool bBool) { m_bIsOwnerDead = bBool; };

	void Set_LimLight_N_Emissive(_float4 vLimLight = _float4(0), _float4 fEmissive = _float4(0));
	_float4 Get_LimLightValue() { return m_vLimLight; };
	_float4	Get_EmissiveValue() { return m_fEmissiveIntensive; };

	virtual HRESULT ReInitialize(void* pArg = nullptr) { return S_OK; };

	class CComponent* Get_Component(const _tchar* tagComponent);
	class CComponent* Find_Components(const _tchar* tagComponent);
	HRESULT Change_Component_by_NewAssign(_uint iScenenNum, const _tchar* tagPrototype, const _tchar* tagComponent, void* pArg = nullptr);
	HRESULT Change_Component_by_Parameter(CComponent* NewComponent, const _tchar* tagComponent, void* pArg = nullptr);

	_fVector Get_AttachCamPos();
	_fVector Get_AttachCamPosOffset();
	_fVector Get_AttachCamLook();

	void Set_AttachCamPos(_float3 fAttachCamPos);
	void Set_AttachCamPosOffset(_float3 fAttachCamPosOffset);

	virtual void Update_AttachCamPos();

	_float Get_NowHP() { return m_fHP; };
	_float Get_MaxHP() { return m_fMaxHP; };
	void	Set_NowHP(_float fHP) { m_fHP = fHP; };

	_float	Add_NowHP(_float fHP);

	_bool	Get_IsOcllusion() { return m_bIsOcllusionObject; }
	void	Set_IsOcllusion(_bool bBool) { m_bIsOcllusionObject = bBool; }


	_bool Get_OnKnockbackCol() { return m_bOnKnockbackCol; }
	_float Get_KnockbackColPower() { return m_fKnockbackColPower; }
	void Set_OnKnockbackCol(_bool bOnKnockbackCol) { m_bOnKnockbackCol = bOnKnockbackCol; }
	void Set_KnockbackColPower(_float fKnockbackColPower) { m_fKnockbackColPower = fKnockbackColPower; }
	
	_float Get_Damage() { return m_fDamage; }
	void Set_Damage(_float fNewDamage) { m_fDamage = fNewDamage; }

protected:
	map<const _tchar*, class CComponent**>	m_mapComponets;
	typedef map<const _tchar*, class CComponent**>	COMPONENTS;

protected:
	ID3D11Device*				m_pDevice = nullptr;
	ID3D11DeviceContext*		m_pDeviceContext = nullptr;
	_float3						m_vOldPos = _float3(0, 0, 0);
	_uint						m_eNowSceneNum = 0;
	const _tchar*				m_szNameTag = nullptr;
	_bool						m_bIsClone = false;
	_bool						m_bIsDead = false;

	_float						m_fRenderSortValue = 0;
	_bool						m_bIsOnScreen = false;

	_bool						m_bIsOcllusionObject = false;

	_float3						m_fAttachCamPos = _float3(0, 0, 0);
	_float3						m_fAttachCamPos_Offset = _float3(0, 0, 0);
	_float3						m_fAttachCamLook = _float3(0, 0, 0);
	_float3						m_fAttachCamLook_Offset  = _float3(0, 0, 0);

	_float4						m_vLimLight = _float3(0);
	_float4						m_fEmissiveIntensive = _float4(0);

	_float						m_fFrustumRadius = 1.f; 

	_float					m_fHP	= 32.f;
	_float					m_fMaxHP = 32.f;

	_bool						m_bOnKnockbackCol = false;
	_float						m_fKnockbackColPower = 0.f;
	_float						m_fDamage = 0.f;

private:
	class CShader*				m_pEngineShader = nullptr;
	_bool						m_bIsOwnerDead = false;

protected:
	HRESULT Add_Component(_uint iScenenNum, const _tchar* tagPrototype,const _tchar* tagComponent, CComponent** ppOut , void* pArg =nullptr);
	
public:
	virtual CGameObject* Clone(void* pArg = nullptr)PURE;
	virtual void Free() override;
};

END