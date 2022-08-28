#pragma once
#include "Boss.h"

BEGIN(Client)
class CMahabalasura final : public CBoss
{
public:
	enum SkillAttackName {SKILL_SPEAR, SKILL_HAND, SKILL_SPEAR_RAIN, SKILL_COPY, SKILL_END};
private:
	CMahabalasura(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CMahabalasura(const CMahabalasura& rhs);
	virtual ~CMahabalasura() = default;

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

	virtual _float	Take_Damage(CGameObject* pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback = false, _float fKnockbackPower = 0.f) override;

public:
	void		Set_CopyOff(_bool State) 
	{
		m_bIsTeleport = State; 
		m_bIsCopySkill = State;
	}

	void		Set_Hit() { m_bIsHit = true; }

	/* Particle */
	virtual HRESULT Ready_ParticleDesc() override;
	virtual HRESULT Update_Particle(_double timer)override;

public:
	// JH
	void				Change_AnimIndex(_uint iAnimIndex);
	void				Set_OnCamLookAtMe(_bool bOn);
	//

private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModel = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CDissolve*			m_pDissolveCom = nullptr;

	//��ü
	CCollider*				m_pCollider = nullptr;
	vector<ATTACHEDESC>		m_vecAttachedDesc;

	_uint				m_iOldAnimIndex = INT_MAX;
	_uint				m_iAdjMovedIndex = 0;
	_uint				m_iAniNum = 0;

	_bool				m_bIsDissolveStart = false;
	_bool				m_bIsHalf = false;
	_bool				m_bIsWalk = true;
	_bool				m_bIsLookAt = true;
	_bool				m_bIsDIeAnimStart = false;

	CGameObject*		m_pPlayerObj = nullptr;
	CTransform*			m_pPlayerTransform = nullptr;
	_bool				m_bIsSpearTurn = false;

	_uint				m_iRainAttackCount = 0;

	//Weapon
	class CMahabalasura_Weapon*				m_pSpear = nullptr;

	//Arm
	_float									m_fArmAttackTime = 10.f;
	_bool									m_bIsArmAttack = false;
	vector<class CMahabalasura_Arms*>		m_pArms;

	//COPY
	_bool									m_bIsCopySkill = false;
	_bool									m_bIsNarasion = true;

	//TELEPORT
	_bool									m_bIsStartTeleport = true;
	_bool									m_bIsTeleport = false;
	_float									m_fTeleportDelay = 0.5f;
	_float									m_fTeleporCoolTime = 7.f;

	//HPBar
	class CHpUI*							m_pHPUI = nullptr;

	//Sound
	_bool									m_bIsTeleportSound = false;
	_bool									m_bIsTeleportAttack = false;

	// Particle
	CTransform*						m_pTextureParticleTransform = nullptr;
	CTransform*						m_pTextureParticleTransform1 = nullptr;
	CTransform*						m_pTextureParticleTransform2 = nullptr;

	_uint							mOnlyPattern = 0;
	_uint							mPatternCount2 = 0;

	_float							m_fNarrationTime = 12.f;


	vector<INSTPARTICLEDESC>								m_vecTextureParticleDesc;
	vector<INSTMESHDESC>									m_vecMeshParticleDesc;
	vector<NONINSTNESHEFTDESC>								m_vecNonInstMeshDesc;

	_bool								m_bInstanceMonsterDieSwitch = false;
	_int								m_iSkillNum = 0;


private:
	// JH
	void				Update_Direction(_double fDeltaTime);
	void				Update_Dead(_double fDeltaTime);

	_bool				m_bBlockUpdate = false;
	_bool				m_bBlockAnim = false;
	_bool				m_bOnceSwitch = false;
	_bool				m_bOncePlaySound = false;
	_uint				m_iNextAnimIndex = 0;
	_float				m_fDelayTime = 0.f;
	_int				m_iCutSceneStep = -1;
	_bool				m_bOnLookAtMe = false;
	//

private:
	HRESULT SetUp_Components();
	HRESULT	Adjust_AnimMovedTransform(_double fDeltatime);

public:
	static CMahabalasura* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;


};

END