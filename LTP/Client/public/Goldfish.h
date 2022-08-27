#pragma once

#include "Monster.h"

BEGIN(Client)

class CGoldfish final : public CMonster
{
	enum AnimationType { ANIM_RUN_Frame1, ANIM_RUN_Frame2, ANIM_END };

	typedef struct tagState
	{
		CTransform*		pTransform = nullptr;
		_uint			iAnimType = ANIM_END;

		_float4			fRimRight = _float4(0.5f, 0.5f, 0.5f, 1.f);
		_float4			fEmissive = _float4(0.5f, 0.5f, 0.5f, 0.8f); //R,G,B W==���䰪
		_float4			fDissolve = _float4(0.f, 1.f, 0.5f, 1.f);//1�帥�ð�, ������ �ð�, ���䰡�� ,0�̸� ������ ���� 1�̸� ������

		_int			iHp = 3;

		_uint			iMyIndex = 0;
		_uint			iRouteIndex = 0;
		_bool			bDirChangeOn = false;
	}TRANSFORM_STATE;

	typedef struct tagInstanceInfo
	{
		_float4x4 fValueMat;  //m[0][0] : MeshInstanceMonsterEnum, m[0][1] : Monster Max Size, m[0][2] : Cell Max Size, m[0][3] : Cell Count,
							  //m[1][0] : Life Count, m[1][1] : Monster Hit Count, m[1][2] : TriggerDistance,
							  //m[2][0]~m[2][2] : X,Y,Z
		_float4x4 fSubValueMat;
		void*		Object = nullptr;
	}INSTANCE_INFO;

private:
	CGoldfish(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CGoldfish(const CGoldfish& rhs);
	virtual ~CGoldfish() = default;

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

public:
	virtual void CollisionTriger(class CCollider* pMyCollider, _uint iMyColliderIndex, CGameObject* pConflictedObj, class CCollider* pConflictedCollider,
		_uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType) override;

	virtual _float	Take_Damage(CGameObject* pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback = false, _float fKnockbackPower = 0.f) override;

private:
	HRESULT	SetUp_Info();

private:
	HRESULT FollowMe(_double dDeltaTime);
	HRESULT	Update_VectorGroup(_double dDeltaTime);
	HRESULT Adjust_AnimMovedTransform(_double dDeltatime);

private:
	HRESULT	Instance_Route();

private:
	CShader*			m_pShaderCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;

	CTransform*			m_pPlayerTransformCom = nullptr;

	CModel*				m_pModel[ANIM_END] = { nullptr };
	CModelInstance*		m_pModelInstance[ANIM_END] = { nullptr };

	vector<TRANSFORM_STATE> m_vecInstancedTransform;

	vector<CTransform*> m_ModelTransGroup[ANIM_END];
	vector<_float4>		m_vecRimLight[ANIM_END];
	vector<_float4>		m_vecEmissive[ANIM_END];
	vector<_float4>		m_vecDissolve[ANIM_END];//1�帥�ð�, ������ �ð�, ���䰡�� ,0�̸� ������ ���� 1�̸� ������


	INSTANCE_INFO		m_Instance_Info;
	const _tchar*		m_charModellInstanceType = nullptr;
	class CInstanceMonsterBatchTrigger*	m_pBatchTrigger = nullptr;



	_uint				m_iOldAnimIndex = INT_MAX;
	_uint				m_iAdjMovedIndex = 0;

	_uint				m_iTempAnimNumber = 0;

	_double				m_dAcceleration = 1.;

	_float3				m_fRoute[5][3];

public:
	static CGoldfish* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};
END
