#pragma once


#include "Base.h"
BEGIN(Engine)

class CCollisionMgr final : public CBase
{
public:
	enum CollsionThreadStateID
	{
		CTS_ENTER, CTS_PROCESSING, CTS_SCENECHANGING, CTS_SCENECHANGINGCLEARFINISHED,  CTS_END
	};

	DECLARE_SINGLETON(CCollisionMgr);


	typedef struct tagColliderObject
	{
		class  CGameObject* pCollisionObject = nullptr;
		class CCollider* pCollider = nullptr;
	}COLLIDERELEMENTS;


	typedef struct tagRepelObject
	{
		class  CTransform* pRepelObjTransform = nullptr;
		_float fRadious = 0.5f;
		class CNavigation* pNavigation = nullptr;
		_bool IsKinect = false;
	}REPELELEMENT;

public:
	typedef struct tagEditPointCollider
	{
		CCollider* vCollider;
		CGameObject* GameObject = nullptr;
	}EDITPOINTCOLLIDER;

private:
	explicit CCollisionMgr();
	virtual ~CCollisionMgr() = default;


public:
	HRESULT Initialize_CollisionMgr(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	HRESULT Inspect_Collision();

public:
	HRESULT Add_CollisionGroup(CollisionTypeID eType, class CGameObject* pCollisionObject, class CCollider* pCollider);
	HRESULT Add_RepelGroup(class CTransform* pTransform, _float fRadious = 0.5f, class CNavigation* pNavigation = nullptr, _bool IsKinect = false);
	
	void	Clear_CollisionGroup();

public:
	//MapTool
	HRESULT		 Add_NaviPointCollider(EDITPOINTCOLLIDER Collider);
	CGameObject* NaviPointCollision(_Vector pos, _Vector dir);


public:
	HRESULT		Processing_RepelCollision(_bool* _IsClientQuit, CRITICAL_SECTION* _CriSec);
	HRESULT		Processing_MainCollision(_bool* _IsClientQuit, CRITICAL_SECTION* _CriSec);

private:

	HRESULT Inspect_MainCollision();
	HRESULT Inspect_RepelGroup();

	HRESULT Inspect_Player_To_MonsterWeapon();
	HRESULT Inspect_PlayerWeapon_To_Monster();
	HRESULT Inspect_DynamicObject_To_PlayerNPlayerWeapon();
	HRESULT Inspect_NPC_To_Player();
	HRESULT Inspect_Terrain_To_All();

	void	Start_InspectMainCollision();
	void	Start_InspectRepelCollision();

	HRESULT	Inspect_PlayerParkur_To_ParkurObj();

	HRESULT	Inspect_MiniGame_Jino();

private:
	list<COLLIDERELEMENTS>		m_CollisionGroupList[CollisionType_END];
	list<REPELELEMENT>		m_RepelObjectList;
	
	list<EDITPOINTCOLLIDER>		m_EditPointCollider;

	CollsionThreadStateID		m_eRepelCollisionThreadState = CTS_ENTER;
	CollsionThreadStateID		m_eCollisionThreadState = CTS_ENTER;

	CRITICAL_SECTION* m_pCriSec = nullptr;

private:
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;

public:
	virtual void Free() override;
};

END