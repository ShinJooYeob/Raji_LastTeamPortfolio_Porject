#pragma once
#include "MonsterWeapon.h"

BEGIN(Client)

class CChiedtuan_Weapon final : public CMonsterWeapon
{
public:
	enum KatanaPOS {KATANA_TR, KATANA_TL, KATANA_BR, KATANA_BL};

	typedef struct WeaponDesc
	{
		CGameObject* BossObj = nullptr;
		KatanaPOS m_KatanaPOS;
		ATTACHEDESC m_eAttachedDesc;
	}WEAPOPNDESC;
private:
	CChiedtuan_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CChiedtuan_Weapon(const CChiedtuan_Weapon& rhs);
	virtual ~CChiedtuan_Weapon() = default;

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


	void SwordTrailOnOff(_bool bBool);
public:
	void	Set_WeaponDesc(WEAPOPNDESC WeaponDesc) {
		m_WeaponDesc = WeaponDesc;
	}

	void	Set_WaistgirdScal() { m_pTransformCom->Scaled_All(_float3(0.6f)); }
	void	Set_SpinScal() { m_pTransformCom->Scaled_All(_float3(0.8f)); }
	void	Set_Dissolve(_bool FadeIn, _double Time = 1.f);

private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModel = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CDissolve*			m_pDissolveCom = nullptr;
	CCollider*			m_pCollider = nullptr;
	CSwordTrail*		m_pSwordTrail = nullptr;

	WEAPOPNDESC			m_WeaponDesc;

	_float4x4			m_fAttachedMatrix;

	ATTACHEDESC			m_AttachedDesc;

	_float3				m_ArrStopSwordTrailPos[2] = { _float3(0),_float3(0) };
	_float				m_StopTrailTimer = 0;
	_float				m_SwordTrailLength = 6.f;

private:
	void				Update_AttachMatrix();

private:
	HRESULT SetUp_Components();

public:
	static CChiedtuan_Weapon* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};
END