#pragma once

#include "MonsterWeapon.h"

#define AtkArmTotalCount 8

BEGIN(Client)

class CMahabalasura_AttackArms final : public CMonsterWeapon
{
public:
	typedef struct tagAttackArmDesc
	{
		_float fAtkArmLength = 5.f;
		_float3 vRotAxis = _float3(1, 0, 0);
	}ATADESC;


public:
	typedef struct TransformNTimeNDead
	{
		CTransform*		pTransform = nullptr;
		_float			fPassedTime = 0;
		_bool			bIsDead = false;
		_float3			vSubTarget = _float3(0);
	}TTD;


private:
	CMahabalasura_AttackArms(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CMahabalasura_AttackArms(const CMahabalasura_AttackArms& rhs);
	virtual ~CMahabalasura_AttackArms() = default;


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
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModel = nullptr;
	CCollider*			m_pCollider = nullptr;

	CTransform*			m_pPlayerTrs = nullptr;

	CModelInstance*		m_pModelInstance = nullptr;
	vector<CTransform*>		m_vecForRenderTransform;
	vector<_float4>		m_vecForLimLight;
	vector<_float4>		m_vecForEmissive;

	vector<TTD>				m_vecInstancedTransform;

	ATADESC				m_tDesc;

	//_float				m_fProgressTime = 0;
	_float				m_fTotalTime = 1.f;
	_float3				m_PlayerPos;
	_float3				m_DestPos[AtkArmTotalCount];
	_float3				m_StartPos[AtkArmTotalCount];
	_float4x4			m_BossMatrix;

	_int				m_iCount = 0;

	_int				m_iSoundCount = 0;


private:
	HRESULT		SetUp_Components();
	HRESULT		Adjust_AnimMovedTransform(_double fDeltatime);

public:
	static CMahabalasura_AttackArms* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};
END
