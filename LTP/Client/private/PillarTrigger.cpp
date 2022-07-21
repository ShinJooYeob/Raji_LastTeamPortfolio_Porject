#include "stdafx.h"
#include "..\public\PillarTrigger.h"
#include "Player.h"

CPillarTrigger::CPillarTrigger(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	: CTriggerObject(pDevice, pDeviceContext)
{
}

CPillarTrigger::CPillarTrigger(const CPillarTrigger & rhs)
	: CTriggerObject(rhs)
{
}

HRESULT CPillarTrigger::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));

	return S_OK;
}

HRESULT CPillarTrigger::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(nullptr));

	FAILED_CHECK(SetUp_Components());

	FAILED_CHECK(SetUp_EtcInfo());

	return S_OK;
}

HRESULT CPillarTrigger::After_Initialize()
{
	m_ePillarTriggerType = static_cast<EPillarTriggerState>((_int)m_fValueMat._11);

	return S_OK;
}

_int CPillarTrigger::Update(_double fDeltaTime)
{
	if (__super::Update(fDeltaTime) < 0) return -1;

	FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_NPC, this, m_pColliderCom));

	return _int();
}

_int CPillarTrigger::LateUpdate(_double fDeltaTimer)
{
	if (__super::LateUpdate(fDeltaTimer) < 0) return -1;


#ifdef _DEBUG
	FAILED_CHECK(GetSingle(CUtilityMgr)->Get_Renderer()->Add_DebugGroup(m_pColliderCom));
#endif // _DEBUG

	return _int();
}

_int CPillarTrigger::Render()
{
	if (__super::Render() < 0)		return -1;

	return _int();
}

_int CPillarTrigger::LateRender()
{
	return _int();
}

_int CPillarTrigger::Active_Trigger(CGameObject * pTarget, _double fDeltaTime)
{
	return _int();
}

_int CPillarTrigger::DeActive_Trigger(CGameObject * pTarget, _double fDeltaTime)
{
	return _int();
}

CPillarTrigger::EParkourTriggerType CPillarTrigger::Get_ParkourTriggerType()
{
	return EParkourTriggerType::PACUR_PILLAR;
}

void CPillarTrigger::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	if (CollisionTypeID::CollisionType_Player == eConflictedObjCollisionType)
	{
		CPlayer* pPlayer = static_cast<CPlayer*>(pConflictedObj);
		switch (m_ePillarTriggerType)
		{
		case EPillarTriggerState::STATE_NORMAL:
		{
			pPlayer->Set_CurParkourTrigger(this);
			if (pPlayer->Get_CurParkurTriger() != this &&
				CPlayer::PILLAR_ANIM_JUMP == pPlayer->Get_CurPlayAnimation() ||
				CPlayer::LEDGE_ANIM_FALLING == pPlayer->Get_CurPlayAnimation() ||
				CPlayer::BASE_ANIM_JUMP == pPlayer->Get_CurPlayAnimation())
			{
				pPlayer->Set_State_PillarGrabStart(true, g_fDeltaTime);
			}
			else if (g_pGameInstance->Get_DIKeyState(DIK_SPACE) & DIS_Down)
			{
				pPlayer->Set_State_PillarStart(g_fDeltaTime);
			}
		}
			break;
		case EPillarTriggerState::STATE_TOP:
		{
			pPlayer->Set_CurParkourTrigger(this);
			pPlayer->Set_PillarBlockClimbUp(true, m_pTransformCom->Get_MatrixState_Float3(CTransform::TransformState::STATE_POS).y);
			/*if (g_pGameInstance->Get_DIKeyState(DIK_SPACE) & DIS_Down)
			{*/
				//pPlayer->Set_State_PillarStart(g_fDeltaTime);
			//}
		}
			break;
		}

	}
}

void CPillarTrigger::Set_Pos(_float3 fPos)
{
	m_pTransformCom->Set_MatrixState(CTransform::TransformState::STATE_POS, fPos);
}

void CPillarTrigger::Set_PillarType(EPillarTriggerState eType)
{
	m_ePillarTriggerType = eType;
}

HRESULT CPillarTrigger::SetUp_Components()
{
	return S_OK;
}

HRESULT CPillarTrigger::SetUp_EtcInfo()
{
	return S_OK;
}

CPillarTrigger * CPillarTrigger::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CPillarTrigger*	pInstance = NEW CPillarTrigger(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CPillarTrigger");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CPillarTrigger::Clone(void * pArg)
{
	CPillarTrigger*	pInstance = NEW CPillarTrigger(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CPillarTrigger");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPillarTrigger::Free()
{
	__super::Free();

}
