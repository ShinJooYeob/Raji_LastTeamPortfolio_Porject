#pragma once
#include "Monster.h"

BEGIN(Engine)
class CNavigation;
END

BEGIN(Client)

class CMonster_Vayusura_Minion final : public CMonster
{
private:
	explicit CMonster_Vayusura_Minion(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	explicit CMonster_Vayusura_Minion(const CMonster_Vayusura_Minion& rhs);
	virtual ~CMonster_Vayusura_Minion() = default;

public:
	virtual HRESULT Initialize_Prototype(void* pArg)override;
	virtual HRESULT Initialize_Clone(void* pArg)override;

public:
	virtual _int Update(_double dDeltaTime)override;
	virtual _int LateUpdate(_double dDeltaTime)override;
	virtual _int Render()override;
	virtual _int LateRender()override;

private:
	HRESULT				SetUp_Info();

	HRESULT				SetUp_Fight(_double dDeltaTime);

private: //�ִϸ��̼�
	HRESULT				PlayAnim(_double dDeltaTime);
	HRESULT				CoolTime_Manager(_double dDeltaTime);
	//HRESULT				Once_AnimMotion(_double	dDeltaTime);
	//HRESULT				Pattern_Change();
	HRESULT				Infinity_AnimMotion(_double	dDeltaTime);

private:
	CShader*			m_pShaderCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CModel*				m_pModel = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CNavigation*		m_pNavigationCom = nullptr;


	_uint				m_iOldAnimIndex = INT_MAX;
	_uint				m_iAdjMovedIndex = 0;

private:
	CTransform*			m_pPlayerTransform = nullptr; //�÷��̾� Ʈ������ ����

//private://�ִϸ��̼� ���� �� �̺�Ʈ
//		//Anim Once Pattern
//	_double				m_dOnceCoolTime = 0;
//	_uint				m_iOncePattern = 0;
//	_uint				m_iOnceAnimNumber = 0;
//
//	_bool				m_bIOnceAnimSwitch = false;

	//Anim Infinity Pattern
	_double				m_dInfinity_CoolTime = 0;
	_int				m_iInfinityPattern = -1;
	_uint				m_iInfinityAnimNumber = 0;

	_double				m_dAcceleration = 1;

private:
	_float				m_fDistance = 0;
	_bool				m_bLookAtOn = true; //LookAt On/Off

	_float3				m_fPlayerPos;

	_float3				m_TempPlayerPos; //Old Player Position

	//Distance
	_float4				m_fDirection;


	_bool				m_dAttackOn = true;

private:
	HRESULT SetUp_Components();
	HRESULT Adjust_AnimMovedTransform(_double dDeltatime);

public:
	static CMonster_Vayusura_Minion* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

};

END