#pragma once

#include "Base.h"

BEGIN(Client)
class CCollider_PhysX_Base;
END

BEGIN(Engine)


// �� ���͸� �����ؼ� ����Ѵ�.
typedef PxJoint* (*JointCreateFunction)(PxRigidActor* a0, const PxTransform& t0, PxRigidActor* a1, const PxTransform& t1);


enum E_SHAPE_TYPE
{
	// �⺻ ����
	SHAPE_NONE,
	// �⺻ Ʈ����
	SHAPE_BASE_TRIGGER,
	SHAPE_END,
};

//enum E_PSHYS_COL_TYPE
//{
//	COLLISION_NONE,
//	//	COLLISION_STATIC,
//	//	COLLISION_DYNAMIC,
//	COLLISION_END,
//};
//

class CPhysXMgr final : public CBase
{
	DECLARE_SINGLETON(CPhysXMgr)


public:
	CPhysXMgr();
	virtual ~CPhysXMgr() = default;

public:
	HRESULT					Initialize_PhysX(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	HRESULT					Update_PhysX(_double timedelta);
	HRESULT					LateUpdate_PhysX(_double timedelta);
	HRESULT					Renderer();


	PxFoundation*			Get_Foundation();
	PxPhysics*				Get_PhysicsCreater();
	PxCooking*				Get_PhysicsCooking();
	PxScene*				Get_PhysicsScene();
	
public: // Create
	// Actor
	HRESULT					CreateBox_Actor(PxRigidActor* actor, PxMaterial* Material, PxVec3 halfExtent);
	HRESULT					CreateSphere_Actor(PxRigidActor* actor, PxMaterial* Material, _float halfExtent);
	PxRigidDynamic*			CreateDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
	PxRigidDynamic*			CreateDynamic_BaseActor(const PxTransform& t, const PxGeometry& geometry, PxReal density, const PxVec3& velocity = PxVec3(0));
	PxRigidStatic*			CreateStatic_BaseActor(const PxTransform& t, const PxGeometry& geometry);
	PxRigidStatic*			CreateStatic_Base_ShapeActor(const PxTransform& t, PxShape& shape);

	// Shape
	PxShape*				CreateDemoShape(E_SHAPE_TYPE type,const PxGeometry& geom, bool isExclusive = false);

	// Plane
	HRESULT					Create_Plane();

public: // Message
	HRESULT Add_TriggerMsg(PxTriggerPair* msg);
	HRESULT Add_ContactMsg(PxContactPair* msg);
	HRESULT Add_CollisionObject(CCollider_PhysX_Base* ComPhysX);


	// ANY
	void					KEYTEST();
	HRESULT					ResetScene();

private:
	HRESULT CreateBase_Plane(PxVec3 point);
	HRESULT CreateStack_Test(const PxTransform& trans, PxU32 size, PxReal halfExtent);
	HRESULT Clean_Phyics();
	HRESULT Create_Cook();

	HRESULT Render_Actor(const PxRigidActor* actor);
	HRESULT RenderShape(const PxGeometryHolder& h);
	

private:
	HRESULT					Initialize_PhysXLib();
	HRESULT					Call_CollisionFunc_Trigger();
	HRESULT					Call_CollisionFunc_Contect();
	CGameObject*			Find_GameObject(PxRigidActor* searchActor);
	CCollider_PhysX_Base*	Find_ComPxCollider(PxRigidActor* searchActor);
	HRESULT					ReleasePhysXCom();


private:
	ID3D11Device*				m_pDevice = nullptr;
	ID3D11DeviceContext*		m_pDeviceContext = nullptr;

	PxDefaultAllocator			mAllocCallback;
	PxDefaultErrorCallback		mErrorCallback;

	PxDefaultCpuDispatcher*		mDisPatcher = nullptr;

	PxFoundation*				mFoundation = nullptr;
	PxPhysics*					mPhysics = nullptr;
	// �� �޽� ����
	PxCooking*					mCooking = nullptr;

	PxScene*					mScene = nullptr;
	PxMaterial*					mMaterial = nullptr;

	PxPvd*						mPvd = nullptr;

	// MessageContainer
	list<PxTriggerPair*>		mListPxTriggerPair;
	list<PxContactPair*>		mListContactPair;
	list<CCollider_PhysX_Base*>	mListPshysXComColiders;


public:
	static PxPhysics*			gPhysics;
	static PxCooking*			gCooking;
	static PxFoundation*		gFoundation;
	static PxMaterial*			gMaterial;

	static PxMaterial*			gMaterial1;
	static PxMaterial*			gMaterial2;


	static _float3 gDebugValue1;
	static _float3 gDebugValue2;
	static _float3 gDebugValue3;
	static _float3 gDebugValue4;

	static PxTolerancesScale			gToleranceScale;

public:
	HRESULT	CreateDemoMap();	
	HRESULT	CreateDemoMap_StaticBox(PxTransform px, PxVec3 scale, _bool trigger = false);
	HRESULT	CreateDemoMap_StaticSphere(PxTransform px, PxVec3 scale, _bool trigger = false);
	
//	HRESULT Add_TriggerMsg(const PxTriggerPair& msg);

public:
	virtual void Free() override;
};


// �浹 ���� �ݹ��Լ�
class CContactReportCallback
	:public PxSimulationEventCallback
{
	// �浹 �ݹ��Լ�
	// ���������ؼ� �ݹ��� �޽��ϴ�.
	// OnAdvance�� �����ϰ�  PxScene::fetchResults()���� ȣ��
	// sendPendingReports = true��  PxScene::flushSimulation() ���� ȣ��


public:
	// PxSimulationEventCallback��(��) ���� ��ӵ�
	virtual void onConstraintBreak(PxConstraintInfo * constraints, PxU32 count) override;
	virtual void onWake(PxActor ** actors, PxU32 count) override;
	virtual void onSleep(PxActor ** actors, PxU32 count) override;
	virtual void onContact(const PxContactPairHeader & pairHeader, const PxContactPair * pairs, PxU32 nbPairs) override;
	virtual void onTrigger(PxTriggerPair * pairs, PxU32 count) override;
	virtual void onAdvance(const PxRigidBody * const * bodyBuffer, const PxTransform * poseBuffer, const PxU32 count) override;
};



class CFiterCallback :
	public PxSimulationFilterCallback
{
	// PxSimulationFilterCallback��(��) ���� ��ӵ�
	virtual PxFilterFlags pairFound(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor * a0, const PxShape * s0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor * a1, const PxShape * s1, PxPairFlags & pairFlags) override;
	virtual void pairLost(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, bool objectRemoved) override;
	virtual bool statusChange(PxU32 & pairID, PxPairFlags & pairFlags, PxFilterFlags & filterFlags) override;
};


class CContactModifyCallback :
	public PxContactModifyCallback
{
public:
	// ���� ���� ����
	virtual void onContactModify(PxContactModifyPair * const pairs, PxU32 count) override;
};

END
