#include "stdafx.h"
#include "..\Public\PhysX\PhysXMgr.h"
#include "..\Public\Player.h"
#include "..\Public\Camera_Main.h"
#include "..\TestObject_PhysX.h"
#include "..\PhysX\Collider_PhysX_Static.h"



#define							PVD_HOST "127.0.0.1"
#define							MAX_NUM_ACTOR_SHAPES 128

IMPLEMENT_SINGLETON(CPhysXMgr)

PxMaterial* CPhysXMgr::gMaterial = nullptr;
PxMaterial* CPhysXMgr::gMaterial1 = nullptr;
PxMaterial* CPhysXMgr::gMaterial2 = nullptr;
PxPhysics* CPhysXMgr::gPhysics = nullptr;
PxCooking* CPhysXMgr::gCooking = nullptr;
PxFoundation* CPhysXMgr::gFoundation = nullptr;

_float3 CPhysXMgr::gDebugValue1 = _float3::Zero();
_float3 CPhysXMgr::gDebugValue2 = _float3::Zero();
_float3 CPhysXMgr::gDebugValue3 = _float3::Zero();
_float3 CPhysXMgr::gDebugValue4 = _float3::Zero();

PxTolerancesScale	CPhysXMgr::gToleranceScale;


// Scene�� �浹 ���� ����
PxFilterFlags SampleSubmarineFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	// Ʈ���� �浹�� ����
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlag::eDEFAULT;
	}
	
//	pairFlags = PxPairFlag::eCONTACT_DEFAULT;


	// ������ �浹 ����
	pairFlags = PxPairFlag::eSOLVE_CONTACT
		| PxPairFlag::eDETECT_DISCRETE_CONTACT
		| PxPairFlag::eNOTIFY_TOUCH_FOUND;
		//| PxPairFlag::eNOTIFY_TOUCH_PERSISTS
	//	| PxPairFlag::eNOTIFY_CONTACT_POINTS;


	// �浹 ���� ���� / ���߿�
	// if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))

	return PxFilterFlag::eDEFAULT;
}

static CContactReportCallback gContactReportCallback; // �浹 �̺�Ʈ �ݹ� Scene�� ����
static CFiterCallback gFiterCallback; // �浹 ���� �ݹ�


CPhysXMgr::CPhysXMgr()
{
}

HRESULT CPhysXMgr::Initialize_PhysX(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
{
	m_pDevice = pDevice;
	m_pDeviceContext = pDeviceContext;

	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pDeviceContext);

	FAILED_CHECK(Initialize_PhysXLib());
	//CreateBase_Plane(PxVec3(0, -10, 0));

	return S_OK;

}
static float X = 0;
static float Z = 0;

HRESULT CPhysXMgr::Update_PhysX(_double timedelta)
{
	// Tick
	if (mScene)
	{
		// Debugger���� ����Ǵ� �� Ȯ��
		mScene->simulate((PxReal)timedelta);
	}
	return S_OK;
}

HRESULT CPhysXMgr::LateUpdate_PhysX(_double timedelta)
{
	// Collider
	if (mScene) {}

	if (mScene)
	{
		// ��� ������Ʈ
		mScene->fetchResults(true);
	//	mScene->fetchResults(false);

	//	mScene->flushSimulation(false);
	}


	// Call_CollisionFunc_Trigger();
	// Call_CollisionFunc_Contect();
	ReleasePhysXCom();

	return S_OK;
}



HRESULT CPhysXMgr::Renderer()
{
//	PxShape* shapes[MAX_NUM_ACTOR_SHAPES];

	// ��� ��ü ��������
	// PxU32 numActor = mScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
	//if (numActor)
	//{
	//	// ��� ������ ��ü Get
	//	std::vector<PxRigidActor*> actors(numActor);
	//	mScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC,
	//		reinterpret_cast<PxActor**>(&actors[0]), numActor);

	//	for (auto& actor : actors)
	//	{
	//		PxTransform tr =  actor->getGlobalPose();
	//		Render_Actor(actor);
	//	}
	//}
	
	return S_OK;

}


static float stackZ = 0.f;

void CPhysXMgr::KEYTEST()
{
	if (KEYDOWN(DIK_C))
	{	
		for (PxU32 i = 0; i < 5; i++)
			CreateStack_Test(PxTransform(PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);
	}


	if (KEYDOWN(DIK_V))
	{
		PxVec3 Box1Pos = PxVec3(10, 0, -50);
		PxVec3 Box2Pos = PxVec3(-10, 0, -50);

		PxVec3 BOXScale = PxVec3(5, 30, 5);

		PxRigidStatic* BoxActor1 = mPhysics->createRigidStatic(PxTransform(Box1Pos));
		PxRigidStatic* BoxActor2 = mPhysics->createRigidStatic(PxTransform(Box2Pos));
		CreateBox_Actor(BoxActor1, mMaterial, BOXScale);
		CreateBox_Actor(BoxActor2, mMaterial, BOXScale);
	}

	if (KEYDOWN(DIK_SPACE))
	{
		// Test
		CCamera_Main* pMainCam = ((CCamera_Main*)(g_pGameInstance->Get_GameObject_By_LayerIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main))));
		CTransform* pCamTransform = pMainCam->Get_Camera_Transform();
		NULL_CHECK_BREAK(pCamTransform);
		PxVec3 CamPos = *(PxVec3*)&pCamTransform->Get_MatrixState_Float3(CTransform::STATE_POS);
		PxTransform trans3 = PxTransform(CamPos);
		CreateDynamic(trans3, PxSphereGeometry(3), PxVec3(0, -50, -100));
	}


}

HRESULT CPhysXMgr::ResetScene()
{
	if (mScene)
	{
		PX_RELEASE(mScene);
		FAILED_CHECK(Initialize_PhysXLib());
	}
	return S_OK;
	
}

HRESULT CPhysXMgr::CreateBase_Plane(PxVec3 point)
{
	PxRigidStatic* groundPlane = PxCreatePlane(*mPhysics, PxPlane(point, PxVec3(0,1,0)), *mMaterial);
	mScene->addActor(*groundPlane);
	return S_OK;
}

//Test
HRESULT CPhysXMgr::CreateStack_Test(const PxTransform & trans, PxU32 size, PxReal halfExtent)
{
	PxShape* shape = mPhysics->createShape(PxBoxGeometry(halfExtent, halfExtent, halfExtent), *mMaterial);
	
	for (PxU32 i = 0; i < size; i++)
	{
		for (PxU32 j = 0; j < size - i; j++)
		{
			PxTransform localTm(PxVec3(PxReal(j * 2) - PxReal(size - i), PxReal(i * 2 + 1), 0) * halfExtent);
			PxRigidDynamic* body = mPhysics->createRigidDynamic(trans.transform(localTm));
			NULL_CHECK_BREAK(body);
			body->attachShape(*shape);
			PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
			mScene->addActor(*body);
		}
	}
	PX_RELEASE(shape);

	return S_OK;
}

HRESULT CPhysXMgr::Clean_Phyics()
{

#ifdef _DEBUG
	PxCloseExtensions();
#endif // _DEBUG

	PX_RELEASE(mDisPatcher);
	PX_RELEASE(mScene);
	PX_RELEASE(mMaterial);
	PX_RELEASE(gMaterial1);
	PX_RELEASE(gMaterial2);


	PX_RELEASE(mPhysics);
	PX_RELEASE(mCooking);
#ifdef _DEBUG
	PxPvdTransport* transport = mPvd->getTransport();
	PX_RELEASE(mPvd);
	PX_RELEASE(transport);
#endif // _DEBUG
	PX_RELEASE(mFoundation);


	return S_OK;

}

HRESULT CPhysXMgr::Create_Cook()
{
	// ���� �޽� ����
	PxVec3 convexVerts[] = { PxVec3(0,1,0),PxVec3(1,0,0),PxVec3(-1,0,0),PxVec3(0,0,1),
	PxVec3(0,0,-1) };

	// ���̾ƿ� ����
	PxConvexMeshDesc convexDesc;
	convexDesc.points.count = 5;
	convexDesc.points.stride = sizeof(PxVec3);
	convexDesc.points.data = convexVerts;
	convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

	// CookLib ����ؼ� ���� ����
	PxDefaultMemoryOutputStream buf;
	PxConvexMeshCookingResult::Enum result;
	if (!mCooking->cookConvexMesh(convexDesc, buf, &result))
		return NULL;
	PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
	PxConvexMesh* convexMesh = mPhysics->createConvexMesh(input);

	// �޽� �ν��Ͻ��� �������� �߰��ϴ� ����
	PxRigidActor* aConvexActor = mPhysics->createRigidStatic(PxTransform(0, 0, 0));

	PxShape* aConvexShape = PxRigidActorExt::createExclusiveShape(*aConvexActor,
		PxConvexMeshGeometry(convexMesh), *mMaterial);
	NULL_CHECK_BREAK(aConvexShape);

	mScene->addActor(*aConvexActor);


	//// Triangle Mesh Ex
	//PxTriangleMeshDesc meshDesc;
	//// ������ Model���� �����ϵ��� �����Ѵ�.
	//meshDesc.points.count = nbVerts;
	//meshDesc.points.stride = sizeof(PxVec3);
	//meshDesc.points.data = verts;

	//meshDesc.triangles.count = triCount;
	//meshDesc.triangles.stride = 3 * sizeof(PxU32);
	//meshDesc.triangles.data = indices32;

	//PxDefaultMemoryOutputStream writeBuffer;
	//PxTriangleMeshCookingResult::Enum result;
	//bool status = cooking.cookTriangleMesh(meshDesc, writeBuffer, result);
	//if (!status)
	//	return NULL;

	//PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	//return physics.createTriangleMesh(readBuffer);


	//PxTriangleMesh* aTriangleMesh = theCooking->createTriangleMesh(meshDesc,
	//	thePhysics->getPhysicsInsertionCallback());


	// ����
	int numCols = 10;
	int numRows = 10;

	// ���� ���÷� X*Z
	PxHeightFieldSample* samples = NEW PxHeightFieldSample[(sizeof(PxHeightFieldSample) * (numCols * numRows))];
	// ���� ����
	PxHeightFieldDesc hfDesc;
	hfDesc.format = PxHeightFieldFormat::eS16_TM;
	hfDesc.nbColumns = numCols;
	hfDesc.nbRows = numRows;
	hfDesc.samples.data = samples;
	hfDesc.samples.stride = sizeof(PxHeightFieldSample);

	// ���� Ŭ���� cook Ŭ������ ���ø��� ���� ���� ���� == ���� ��������
	PxHeightField* aHeightField = mCooking->createHeightField(hfDesc,
		mPhysics->getPhysicsInsertionCallback());


	// ���� ���� �ν��Ͻ�
	PxHeightFieldGeometry hfGeom(aHeightField, PxMeshGeometryFlags(1), PxReal(10.f), PxReal(numCols), PxReal(numCols));

	// ���Ϳ� ���� ���� �ޱ�
	PxRigidActor* aHieightFieldActor = mPhysics->createRigidStatic(PxTransform(0, 0, 0));

	PxShape* aHeightFieldShape = PxRigidActorExt::createExclusiveShape(*aHieightFieldActor,
		hfGeom, *mMaterial);

	mScene->addActor(*aHieightFieldActor);

	return S_OK;
}

HRESULT CPhysXMgr::Create_Plane()
{
	PxRigidStatic* Plane = PxCreatePlane(*mPhysics, PxPlane( 0, 1, 0, 0), *mMaterial);
	mScene->addActor(*Plane);
	return S_OK;

}

HRESULT CPhysXMgr::Add_TriggerMsg(PxTriggerPair* msg)
{
	// �浹ü �˻�����
	mListPxTriggerPair.push_back(msg);

	return S_OK;
}

HRESULT CPhysXMgr::Add_ContactMsg(PxContactPair* msg)
{
	// �浹ü �˻�����
	mListContactPair.push_back(msg);
	return S_OK;
}

HRESULT CPhysXMgr::Add_CollisionObject(CCollider_PhysX_Base * ComPhysX)
{
	// �浹ü ������Ʈ���� �߰����ش�.
	if (ComPhysX)
	{
		mListPshysXComColiders.push_back(ComPhysX);
		Safe_AddRef(ComPhysX);
	}

	return S_OK;
}


HRESULT CPhysXMgr::Render_Actor(const PxRigidActor* actor )
{
	bool sleeping = actor->is<PxRigidDynamic>() ? actor->is<PxRigidDynamic>()->isSleeping() : false;

	if (sleeping)
		return S_FALSE;

	PxShape* shapes[MAX_NUM_ACTOR_SHAPES];
	const PxU32 numShapes = actor->getNbShapes();
	if (numShapes >= MAX_NUM_ACTOR_SHAPES)
		return E_FAIL;

	actor->getShapes(shapes, numShapes);

	// ��� ���� �׷��ش�.
	for (PxU32 j = 0; j < numShapes; j++)
	{
		const PxMat44 shpaeWorld(PxShapeExt::getGlobalPose(*shapes[j], *actor));
		const PxGeometryHolder h = shapes[j]->getGeometry();
		RenderShape(h);

		int debug = 5;
	}

	return S_OK;
}

HRESULT CPhysXMgr::RenderShape(const PxGeometryHolder & h)
{
	const PxGeometry& geom =  h.any();

	switch (geom.getType())
	{
	case PxGeometryType::eSPHERE:		
	{
		const PxSphereGeometry& sphereGeom = static_cast<const PxSphereGeometry&>(geom);
		// sphereGeom.radius;
		break;
	}

	case PxGeometryType::eBOX:
	{
		const PxBoxGeometry& boxGeom = static_cast<const PxBoxGeometry&>(geom);
		//	boxGeom.halfExtents.x;
		break;
	}
	case PxGeometryType::eCAPSULE:
	{
		const PxCapsuleGeometry& capsuleGeom = static_cast<const PxCapsuleGeometry&>(geom);
		//	const PxF32 radius = capsuleGeom.radius;
		//	const PxF32 halfHeight = capsuleGeom.halfHeight;		

	}
		break;

	//case PxGeometryType::eCONVEXMESH:
	//	PxConvexMeshGeometry
	//	break;

	//case PxGeometryType::eTRIANGLEMESH:
	//	PxTriangleMeshGeometry
	//	break;


	default:
		break;


	}


	return S_OK;
}

PxFoundation * CPhysXMgr::Get_Foundation()
{
	NULL_CHECK_BREAK(mFoundation);
	return mFoundation;
}

PxPhysics * CPhysXMgr::Get_PhysicsCreater()
{
//	NULL_CHECK_BREAK(mPhysics);
	return mPhysics;
}

PxCooking * CPhysXMgr::Get_PhysicsCooking()
{

	NULL_CHECK_BREAK(mCooking);
	return mCooking;
//	return nullptr;
}

PxScene * CPhysXMgr::Get_PhysicsScene()
{
//	NULL_CHECK_BREAK(mScene);
	return mScene;
}

HRESULT CPhysXMgr::Initialize_PhysXLib()
{
	
	// Init
	gToleranceScale.length = 100;
	gToleranceScale.speed = 981;

	// Ʈ���� Ÿ��

	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, 
		mAllocCallback,
		mErrorCallback);
	NULL_CHECK_BREAK(mFoundation);
	gFoundation = mFoundation;

	// �޽� ����ũ�� �ش�Ǵ� ���� ����
	// mPhysics->getPhysicsInsertionCallback();
	mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, PxCookingParams(gToleranceScale));
	NULL_CHECK_BREAK(mCooking);
	gCooking = mCooking; 

	


#ifdef  _DEBUG

	mPvd = PxCreatePvd(*mFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	mPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, gToleranceScale, true, mPvd);
	NULL_CHECK_BREAK(mPhysics);
	gPhysics = mPhysics;

	//PX_RELEASE(transport);

	PxInitExtensions(*mPhysics, mPvd);

#else
	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, gToleranceScale);
	NULL_CHECK_BREAK(mPhysics);
	gPhysics = mPhysics;

#endif


	PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -9.81f, 0.0f);


	sceneDesc.simulationEventCallback = &gContactReportCallback;
	sceneDesc.filterShader = SampleSubmarineFilterShader;
	sceneDesc.filterCallback = &gFiterCallback;
	
//	sceneDesc.filterShader = &contactReportFilterShader;

//	sceneDesc.contactModifyCallback = PxDefaultSimulationFilterShader;


	mDisPatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = mDisPatcher;

	mScene = mPhysics->createScene(sceneDesc);

#ifdef _DEBUG
	PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
#endif // DEBUG

	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	gMaterial = mMaterial;

	gMaterial1 = mPhysics->createMaterial(0.3f, 0.3f, 0.5f);
	gMaterial2 = mPhysics->createMaterial(0.8f, 0.8f, 1.0f);

	return S_OK;
}

HRESULT CPhysXMgr::Call_CollisionFunc_Trigger()
{
	if (mListPxTriggerPair.empty())
		return S_OK;

	PxTriggerPair* triggerdata = mListPxTriggerPair.front();
	mListPxTriggerPair.pop_front();

	COLLIDERTYPE_PhysXID type = COLLIDER_PHYSX_END;

	if (triggerdata->status &PxPairFlag::eNOTIFY_TOUCH_FOUND)
		type = COLLIDER_PHYSX_TRIGGERIN;

	else if (triggerdata->status &PxPairFlag::eNOTIFY_TOUCH_LOST)
		type = COLLIDER_PHYSX_TRIGGEROUT;

	if (type == COLLIDER_PHYSX_END)
		return S_OK;

	CCollider_PhysX_Base* col1 = Find_ComPxCollider(triggerdata->otherActor);
	CCollider_PhysX_Base* col2 = Find_ComPxCollider(triggerdata->triggerActor);

	Safe_Delete(triggerdata);

	if (col1 == nullptr || col2 == nullptr)
		return E_FAIL;

	col1->Get_GameObject()->CollisionPhysX_Trigger(col2->Get_GameObject(), col2->Get_ObjectID(), type);
	

	return S_OK;
}

HRESULT CPhysXMgr::Call_CollisionFunc_Contect()
{

	if (mListContactPair.empty())
		return S_OK;

	// ���� ������Ʈ / ���� ������Ʈ �浹 �Ǵ�

	while (mListContactPair.empty() == false)
	{
		PxContactPair* contectData = mListContactPair.front();
		mListContactPair.pop_front();

		COLLIDERTYPE_PhysXID colType = COLLIDER_PHYSX_END;

		if (contectData->events &PxPairFlag::eNOTIFY_TOUCH_FOUND)
			colType = COLLIDER_PHYSX_CONECTIN;

		else if (contectData->events &PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
			colType = COLLIDER_PHYSX_CONECTSTAY;

		else if (contectData->events &PxPairFlag::eNOTIFY_TOUCH_LOST)
			colType = COLLIDER_PHYSX_CONECTOUT;

		else if (colType == COLLIDER_PHYSX_END)
			return E_FAIL;

		PxRigidActor* act1 = contectData->shapes[0]->getActor();
		PxRigidActor* act2 = contectData->shapes[1]->getActor();

		CCollider_PhysX_Base* col1 = Find_ComPxCollider(act1);
		CCollider_PhysX_Base* col2 = Find_ComPxCollider(act2);

		Safe_Delete(contectData);

		if (col1 == nullptr || col2 == nullptr)
			return E_FAIL;

		col1->Get_GameObject()->CollisionPhysX_Rigid(col2->Get_GameObject(), col2->Get_ObjectID(), colType);

	}

	



	return S_OK;
}

CGameObject * CPhysXMgr::Find_GameObject(PxRigidActor * searchActor)
{
	for (auto& obj: mListPshysXComColiders)
	{
		if (searchActor == obj->Get_ColliderActor())
			return obj->Get_GameObject();
	}

	return nullptr;
}


CCollider_PhysX_Base * CPhysXMgr::Find_ComPxCollider(PxRigidActor * searchActor)
{
	for (auto& obj : mListPshysXComColiders)
	{
		if (searchActor == obj->Get_ColliderActor())
			return obj;
	}
	return nullptr;
}


HRESULT CPhysXMgr::ReleasePhysXCom()
{
	for (auto& com : mListPshysXComColiders)
		Safe_Release(com);
	mListPshysXComColiders.clear();
	return S_OK;
}


HRESULT CPhysXMgr::CreateBox_Actor(PxRigidActor* actor, PxMaterial* Material, PxVec3 halfExtent)
{
	PxShape* shape = mPhysics->createShape(PxBoxGeometry(halfExtent.x, halfExtent.y, halfExtent.z), *Material);
	shape->setContactOffset(1);

	NULL_CHECK_BREAK(shape);
	actor->attachShape(*shape);
	mScene->addActor(*actor);
	shape->release();
	return S_OK;
}

HRESULT CPhysXMgr::CreateSphere_Actor(PxRigidActor * actor, PxMaterial * Material, _float halfExtent)
{
	PxShape* shape = mPhysics->createShape(PxSphereGeometry(halfExtent), *Material);
	NULL_CHECK_BREAK(shape);
	actor->attachShape(*shape);
	mScene->addActor(*actor);
	shape->release();
	return S_OK;
}

PxShape * CPhysXMgr::CreateDemoShape(E_SHAPE_TYPE type, const PxGeometry & geom, bool isExclusive)
{
	PxShape* shape = nullptr;
	if (type == SHAPE_NONE)
	{
		const PxShapeFlags shapeFlags = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSIMULATION_SHAPE;
		shape = mPhysics->createShape(geom, *mMaterial, isExclusive, shapeFlags);
		return shape;
	}
	else if (type == SHAPE_BASE_TRIGGER)
	{
		const PxShapeFlags shapeFlags = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eTRIGGER_SHAPE;
		shape = mPhysics->createShape(geom, *mMaterial, isExclusive, shapeFlags);
		return shape;

	}
	
	return nullptr;

}

PxRigidDynamic* CPhysXMgr::CreateDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity)
{
	PxTransform testrans = PxTransform(PxVec3(0, 0, 0));

	PxRigidDynamic* dynamic = PxCreateDynamic(*mPhysics, testrans, geometry, *mMaterial, 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);
	mScene->addActor(*dynamic);
	return dynamic;
}

PxRigidDynamic * CPhysXMgr::CreateDynamic_BaseActor(const PxTransform & t,const PxGeometry& geometry,PxReal density,  const PxVec3 & velocity)
{


	PxRigidDynamic* actor = PxCreateDynamic(*mPhysics, t, geometry, *gMaterial1,density);
	NULL_CHECK_BREAK(actor);
	actor->setAngularDamping(0.05f);
	actor->setLinearVelocity(velocity);
	mScene->addActor(*actor);
	return actor;
}

PxRigidStatic * CPhysXMgr::CreateStatic_BaseActor(const PxTransform & t, const PxGeometry& geometry)
{
	PxRigidStatic* actor = PxCreateStatic(*mPhysics, t, geometry, *gMaterial2);
	NULL_CHECK_BREAK(actor);
	mScene->addActor(*actor);
	return actor;
}

PxRigidStatic * CPhysXMgr::CreateStatic_Base_ShapeActor(const PxTransform & t, PxShape& shape)
{
	PxRigidStatic* actor = PxCreateStatic(*mPhysics, t, shape);
	NULL_CHECK_BREAK(actor);
	mScene->addActor(*actor);
	return actor;
}




HRESULT CPhysXMgr::CreateDemoMap()
{
	// �浹 �׽�Ʈ�� ���� �� ����
	PxTransform pxTrnas;
	PxVec3		pxScale = PxVec3(1,1,1);

	pxTrnas.p = PxVec3(0, -1, 0);
	pxScale = PxVec3(100, 0.5f, 100);
	CreateDemoMap_StaticBox(pxTrnas,pxScale);
	
	pxTrnas.p = PxVec3(-5, 2, 0);
	pxScale = PxVec3(3, 3, 3);

	CreateDemoMap_StaticBox(pxTrnas,pxScale);
	
	pxTrnas.p = PxVec3(5, 1, 0);
	pxScale = PxVec3(4, 3, 4);
	CreateDemoMap_StaticBox(pxTrnas, pxScale);

	pxTrnas.p = PxVec3(2, 1, 6);
	pxScale = PxVec3(4, 4, 4);
	CreateDemoMap_StaticBox(pxTrnas, pxScale,true);

	return S_OK;
}

HRESULT CPhysXMgr::CreateDemoMap_StaticBox(PxTransform px, PxVec3 scale, _bool triger)
{
	_uint nowScene = g_pGameInstance->Get_TargetSceneNum();

	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer
	(nowScene, TAG_LAY(Layer_ColBase), TAG_OP(Prototype_Object_Static_PhysX)));
	CTestObject_PhysX* obj =
		static_cast<CTestObject_PhysX*>(g_pGameInstance->Get_GameObject_By_LayerLastIndex(nowScene, TAG_LAY(Layer_ColBase)));
	obj->Set_ColSetID(E_PHYTYPE_STATIC);

	triger ? obj->Set_ModelSetting(CTestObject_PhysX::MODEL_EMPTY) : obj->Set_ModelSetting(CTestObject_PhysX::MODEL_GEMETRY);

	CTransform* objTrans = (CTransform*)obj->Get_Component(TAG_COM(Com_Transform));
	CCollider_PhysX_Static* colStatic = (CCollider_PhysX_Static*)obj->Get_Component(TAG_COM(Com_Collider_PhysX));
	objTrans->Set_MatrixState(CTransform::STATE_POS, PXVEC3TOFLOAT3(px.p));
	objTrans->Scaled_All(PXVEC3TOFLOAT3(scale));

	CCollider_PhysX_Base::PHYSXDESC_STATIC createStatic;
	createStatic.bTrigger = triger;
	createStatic.eShapeType = E_GEOMAT_BOX;
	createStatic.mGameObect = obj;
	createStatic.mTrnasform = objTrans;
	NULL_CHECK_BREAK(createStatic.mTrnasform);
	colStatic->Set_ColiiderDesc(createStatic);
	return S_OK;
}

HRESULT CPhysXMgr::CreateDemoMap_StaticSphere(PxTransform px, PxVec3 scale, _bool triger)
{
	_uint nowScene = g_pGameInstance->Get_TargetSceneNum();

	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer
	(nowScene, TAG_LAY(Layer_ColBase), TAG_OP(Prototype_Object_Static_PhysX)));
	CTestObject_PhysX* obj =
		static_cast<CTestObject_PhysX*>(g_pGameInstance->Get_GameObject_By_LayerLastIndex(nowScene, TAG_LAY(Layer_ColBase)));
	obj->Set_ColSetID(E_PHYTYPE_STATIC);

	triger ? obj->Set_ModelSetting(CTestObject_PhysX::MODEL_EMPTY) : obj->Set_ModelSetting(CTestObject_PhysX::MODEL_GEMETRY);

	CTransform* objTrans = (CTransform*)obj->Get_Component(TAG_COM(Com_Transform));
	CCollider_PhysX_Static* colStatic = (CCollider_PhysX_Static*)obj->Get_Component(TAG_COM(Com_Collider_PhysX));
	objTrans->Set_MatrixState(CTransform::STATE_POS, PXVEC3TOFLOAT3(px.p));
	objTrans->Scaled_All(PXVEC3TOFLOAT3(scale));

	CCollider_PhysX_Base::PHYSXDESC_STATIC createStatic;
	createStatic.bTrigger = triger;
	createStatic.eShapeType = E_GEOMAT_SPEHE;
	createStatic.mGameObect = obj;
	createStatic.mTrnasform = objTrans;
	NULL_CHECK_BREAK(createStatic.mTrnasform);
	colStatic->Set_ColiiderDesc(createStatic);
	return S_OK;
}


void CPhysXMgr::Free()
{
	
	for (auto& hair : mListContactPair)
		Safe_Delete(hair);
	mListContactPair.clear();

	Clean_Phyics();

	Safe_Release(m_pDevice);
	Safe_Release(m_pDeviceContext);
	ReleasePhysXCom();
}


void CContactReportCallback::onConstraintBreak(PxConstraintInfo* /*constraints*/, PxU32 /*count*/)
{
	// PxConstraintInfo �� ���� ������ �������� ȣ��
	OutputDebugStringW(L"onConstraintBreak");
	OutputDebugStringW(L"\n");

}

void CContactReportCallback::onWake(PxActor** /*actors*/, PxU32 /*count*/)
{
	// �ƾ ���� ȣ�� // eSEND_SLEEP_NOTIFIES ������ 
	// A->wakeUp()
	OutputDebugStringW(L"onWake");
	OutputDebugStringW(L"\n");
}

void CContactReportCallback::onSleep(PxActor** /*actors*/, PxU32 /*count*/)
{
	// A->putToSleep() �ÿ� ȣ��
	OutputDebugStringW(L"onSleep");
	OutputDebugStringW(L"\n");
}


void CContactReportCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 count)
{
	// ���� �̺�Ʈ �߻� �� ȣ��
	// pair�� ȣ�� �ѽ��� ���Ϳ� ���� ȣ��ȴ�.
	// #PxSimulationFilterCallback ����
//	 OutputDebugStringW(L"onContact\n");

	while (count--)
	{
		const PxContactPair& current = *pairs++;

		if (current.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			//OutputDebugStringW(L"Add onContact 1\n");
			PxContactPair* Currentt = NEW PxContactPair;
			memcpy(Currentt, &current, sizeof(PxContactPair));
			GetSingle(CPhysXMgr)->Add_ContactMsg(Currentt);
		}

		//else if (current.events & PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
		//{
		//	OutputDebugStringW(L"Add onContact 2\n");
		//	PxContactPair* Currentt = NEW PxContactPair;
		//	memcpy(Currentt, &current, sizeof(PxContactPair));
		//	GetSingle(CPhysXMgr)->Add_ContactMsg(Currentt);

		//}
		//else if (current.events & PxPairFlag::eNOTIFY_TOUCH_LOST)
		//{
		//	OutputDebugStringW(L"Add onContact 3\n");
		//	PxContactPair* Currentt = NEW PxContactPair;
		//	memcpy(Currentt, &current, sizeof(PxContactPair));
		//	GetSingle(CPhysXMgr)->Add_ContactMsg(Currentt);
		//}
		

	}
}

void CContactReportCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	//PxShapeFlag::eTRIGGER_SHAPE �� ���� �̺�Ʈ ����
	while (count--)
	{
		const PxTriggerPair& current = *pairs++;

		// ignore pairs when shapes have been deleted
		if (current.flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;

		if (current.status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			OutputDebugStringW(L"Add Trigger 1\n");
			PxTriggerPair* Currentt = NEW PxTriggerPair;
			memcpy(Currentt, &current, sizeof(PxTriggerPair));
			GetSingle(CPhysXMgr)->Add_TriggerMsg(Currentt);

		}
		if (current.status & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			OutputDebugStringW(L"Add Trigger 2\n");
			PxTriggerPair* Currentt = NEW PxTriggerPair;
			memcpy(Currentt, &current, sizeof(PxTriggerPair));
			GetSingle(CPhysXMgr)->Add_TriggerMsg(Currentt);

		}
	}
}

void CContactReportCallback::onAdvance(const PxRigidBody*const*, const PxTransform*, const PxU32)
{
	// flush �϶��� ȣ��
	OutputDebugStringW(L"onAdvance");
	OutputDebugStringW(L"\n");
}

static	PxFilterFlags triggersUsingFilterCallback(PxFilterObjectAttributes /*attributes0*/, PxFilterData /*filterData0*/,
	PxFilterObjectAttributes /*attributes1*/, PxFilterData /*filterData1*/,
	PxPairFlags& pairFlags, const void* /*constantBlock*/, PxU32 /*constantBlockSize*/)
{
	//	printf("contactReportFilterShader\n");

	PX_ASSERT(getImpl() == FILTER_CALLBACK);

	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	//if (usesCCD())
	//	pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT | PxPairFlag::eNOTIFY_TOUCH_CCD;

	return PxFilterFlag::eCALLBACK;
}

PxFilterFlags CFiterCallback::pairFound(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor * a0, const PxShape * s0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor * a1, const PxShape * s1, PxPairFlags & pairFlags)
{
	return PxFilterFlags();
}

void CFiterCallback::pairLost(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, bool objectRemoved)
{
}

bool CFiterCallback::statusChange(PxU32 & pairID, PxPairFlags & pairFlags, PxFilterFlags & filterFlags)
{
	return false;
}

