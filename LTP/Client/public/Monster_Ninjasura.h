#pragma once
#include "Monster.h"

BEGIN(Engine)
class CNavigation;
END

BEGIN(Client)
class CMonster_Ninjasura final : public CMonster
{
public:
	enum Anim_State { MONSTER_IDLE, MONSTER_HIT, MONSTER_ATTACK, STATE_END };
private:
	explicit CMonster_Ninjasura(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	explicit CMonster_Ninjasura(const CMonster_Ninjasura& rhs);
	virtual ~CMonster_Ninjasura() = default;

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
	HRESULT Adjust_AnimMovedTransform(_double dDeltatime);

public:
	virtual void CollisionTriger(class CCollider* pMyCollider, _uint iMyColliderIndex, CGameObject* pConflictedObj, class CCollider* pConflictedCollider,
		_uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType) override;

	virtual _float	Take_Damage(CGameObject* pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback = false, _float fKnockbackPower = 0.f) override;

private:
	HRESULT				SetUp_Info();
	HRESULT				SetUp_Collider();

	HRESULT				SetUp_Fight(_double dDeltaTime);
	HRESULT				Update_Collider(_double dDeltaTime);

private:
	/* Particle */
	virtual HRESULT Ready_ParticleDesc() override;
	virtual HRESULT Update_Particle(_double timer)override;
	virtual HRESULT Play_SpawnEffect()override;

private: //�ִϸ��̼�
	HRESULT				PlayAnim(_double dDeltaTime);
	HRESULT				CoolTime_Manager(_double dDeltaTime);
	HRESULT				Once_AnimMotion(_double	dDeltaTime);
	HRESULT				Pattern_Change();
	HRESULT				Infinity_AnimMotion(_double	dDeltaTime);

private:
	CShader*			m_pShaderCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CModel*				m_pModel = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CMotionTrail*		m_pMotionTrail = nullptr;
	CDissolve*			m_pDissolve = nullptr;

private:
	CCollider*			m_pColliderCom = nullptr;
	vector<ATTACHEDESC> m_vecAttachedDesc;

	CCollider*			m_pAttackColliderCom = nullptr;
	vector<ATTACHEDESC> m_vecAttackAttachedDesc;

	_bool				m_bColliderAttackOn = false;

private:
	class CHpUI*		m_pHPUI = nullptr;

	_uint				m_iOldAnimIndex = INT_MAX;
	_uint				m_iAdjMovedIndex = 0;

private:
	CTransform*			m_pPlayerTransform = nullptr; //�÷��̾� Ʈ������ ����
	CNavigation*		m_pPlayerNavigation = nullptr; //�÷��̾� �׺�

private://�ִϸ��̼� ���� �� �̺�Ʈ
	Anim_State			m_eMonster_State = Anim_State::MONSTER_IDLE;

	//Anim Once Pattern
	_double				m_dOnceCoolTime = 0;
	_uint				m_iOncePattern = 0;
	_uint				m_iOnceAnimNumber = 0;

	_bool				m_bIOnceAnimSwitch = false;
	_bool				m_bStopCoolTimeOn = false;

	//Old Pattern
	_uint				m_iAfterPattern = 0;

	//Anim Infinity Pattern
	_double				m_dInfinity_CoolTime = 0;
	_uint				m_iInfinityPattern = 0;
	_uint				m_iInfinityAnimNumber = 0;

	//Anim Combo Pattern
	_bool				m_bComboAnimSwitch = false;

	_double				m_dAcceleration = 1;

private:
	_float				m_fDistance = 0;
	_bool				m_bLookAtOn = true; //LookAt On/Off

private: //MoveNumber
	_uint				m_iMoveNumber = 0;

	_uint				m_iBoolOnce = 0;

	_float4				m_fDirection;

private: //MotionTrail
	_double				m_MotionTrailTime = 0;
	_bool				m_bTurnMotion = false;
	_bool				m_bMotionTrailOn = false;


private:
	//Knockback
	_bool				m_bKnockbackOn = false;
	_float3				m_fKnockbackDir;

private://Sound
	_uint				m_iSoundIndex = 0;
	_double				m_dSoundTime = 0;
	_bool				m_bDieSound = false;

private://Dissolve
	_double				m_dDissolveTime = 0;

private://Repel
	_bool				m_bRepelOff = false;
	
private: // particle	
	CTransform*						m_pTextureParticleTransform_Hand = nullptr;
	CTransform*						m_pTextureParticleTransform_Leg = nullptr;
	// static const int				ShurikenSize = 3;
	// CGameObject*					m_ArrayShuriken[ShurikenSize] = {nullptr,};



public:
	static CMonster_Ninjasura* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

};

END
