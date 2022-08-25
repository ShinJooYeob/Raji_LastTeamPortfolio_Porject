#pragma once

#include "TriggerObject.h"

BEGIN(Client)
class CPlayer;

class CGearPuzzleTrigger final : public CTriggerObject
{
protected:
	CGearPuzzleTrigger(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CGearPuzzleTrigger(const CGearPuzzleTrigger& rhs);
	virtual ~CGearPuzzleTrigger() = default;

public:
	virtual HRESULT		Initialize_Prototype(void* pArg) override;
	virtual HRESULT		Initialize_Clone(void* pArg) override;
	virtual HRESULT		After_Initialize() override;


public:
	virtual _int					Update(_double fDeltaTime) override;
	virtual _int					LateUpdate(_double fDeltaTimer) override;
	virtual _int					Render() override;
	virtual _int					LateRender() override;

	virtual _int					Active_Trigger(CGameObject* pTarget, _double fDeltaTime) override;
	virtual _int					DeActive_Trigger(CGameObject* pTarget, _double fDeltaTime) override;

	virtual EParkourTriggerType 	Get_ParkourTriggerType();

	virtual void					CollisionTriger(class CCollider* pMyCollider, _uint iMyColliderIndex, CGameObject* pConflictedObj, class CCollider* pConflictedCollider,
									_uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType) override;

private:
	HRESULT							SetUp_Components();
	HRESULT							SetUp_EtcInfo();

private:
	class CCamera_Main*			m_pMainCamera;

	_float						m_fPassedTime = 0;
	_bool						m_bClearChecker = false;

public:
	static CGearPuzzleTrigger*		Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CGameObject*			Clone(void* pArg);
	virtual void					Free() override;
};

END