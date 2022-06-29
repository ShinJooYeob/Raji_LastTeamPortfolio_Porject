#pragma once
#include "Monster.h"

BEGIN(Engine)
class CNavigation;
END

BEGIN(Client)
class CMonster_Mahinasura_Minion final : public CMonster
{
private:
	explicit CMonster_Mahinasura_Minion(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	explicit CMonster_Mahinasura_Minion(const CMonster_Mahinasura_Minion& rhs);
	virtual ~CMonster_Mahinasura_Minion() = default;

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
	HRESULT				Once_AnimMotion(_double	dDeltaTime);
	HRESULT				Pattern_Change();
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

private://�ִϸ��̼� ���� �� �̺�Ʈ
	_double				m_dOnceCoolTime = 0;
	_uint				m_iOncePattern = 0;
	_uint				m_iOnceAnimNumber = 0;

	_double				m_dInfinity_CoolTime = 0;
	_uint				m_iInfinityPattern = 0;
	_uint				m_iInfinityAnimNumber = 0;

	_bool				m_bIOnceAnimSwitch = false;

private:
	_float				m_fDis = 0; //�Ÿ��� ���ϴ� ����
	_bool				m_bLookAtOn = true; //�迧�� On/Off


private:
	HRESULT SetUp_Components();
	HRESULT Adjust_AnimMovedTransform(_double dDeltatime);

public:
	static CMonster_Mahinasura_Minion* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

};

END