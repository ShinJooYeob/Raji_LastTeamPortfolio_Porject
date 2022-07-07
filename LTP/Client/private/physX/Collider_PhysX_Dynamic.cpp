#include "stdafx.h"
#include "..\Public\PhysX\Collider_PhysX_Dynamic.h"


CCollider_PhysX_Dynamic ::CCollider_PhysX_Dynamic (ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CCollider_PhysX_Base(pDevice, pDeviceContext)
{
	mePhysX_ID = E_PHYTYPE_DYNAMIC;
}

CCollider_PhysX_Dynamic ::CCollider_PhysX_Dynamic (const CCollider_PhysX_Dynamic  & rhs)
	: CCollider_PhysX_Base(rhs)
{

}

HRESULT CCollider_PhysX_Dynamic ::Initialize_Prototype(void * pArg)
{
	if (FAILED(__super::Initialize_Prototype(pArg)))
		return E_FAIL;


	return S_OK;
}

HRESULT CCollider_PhysX_Dynamic ::Initialize_Clone(void * pArg)
{
	if (FAILED(__super::Initialize_Clone(pArg)))
		return E_FAIL;
	

	// Ű�� �ܺ� ���� �ۿ������� ����ó��
	//PxRigidDynamic* dynamic;
	//dynamic->setKinematicTarget();
	return S_OK;
}


HRESULT CCollider_PhysX_Dynamic ::Update_BeforeSimulation()
{
	if (FAILED(__super::Update_BeforeSimulation()))
		return E_FAIL;





	return S_OK;
}

HRESULT CCollider_PhysX_Dynamic ::Update_AfterSimulation()
{
	if (FAILED(__super::Update_AfterSimulation()))
		return E_FAIL;

	PxTransform trans =  mMain_Actor->getGlobalPose();
	mPxMainMatrix4x4 = PxMat44(trans);
	mPxMainMatrix4x4.scale(PxVec4(mScale,1));
	mMainTransform->Set_Matrix(PXMATTOMAT4x4(mPxMainMatrix4x4));

	return S_OK;
}


#ifdef _DEBUG

HRESULT CCollider_PhysX_Dynamic ::Render()
{
	FAILED_CHECK(__super::Render());

	mPxMainMatrix4x4 = mMain_Actor->getGlobalPose();
	mMainTransform->Set_Matrix(PXMATTOMAT4x4(mPxMainMatrix4x4));

	return S_OK;
}

#endif


HRESULT CCollider_PhysX_Dynamic::Set_ColiiderDesc(PHYSXDESC_DYNAMIC desc)
{
	// �浹 �� �ʱ�ȭ
	memcpy(&mPhysXDesc, &desc, sizeof(PHYSXDESC_DYNAMIC));

	// �� ������ �ݶ��̴� �ʱ�ȭ
	// ��ġ / ������ / ���� Ÿ�� / ����� �����켭 �ݶ��̴� ������Ʈ ����
	if (mMain_Actor)
		return E_FAIL;


	PxGeometry* gemo = nullptr;
	mMainTransform = mPhysXDesc.mTrnasform;

	_float3 scale = mMainTransform->Get_Scale();
	mScale = FLOAT3TOPXVEC3(scale);
	_float3 pos = mMainTransform->Get_MatrixState(CTransform::STATE_POS);

	gemo = Create_Geometry(desc.eShapeType, scale);
	NULL_CHECK_BREAK(gemo);

	// �ʱ���ġ ����
	mPxMainMatrix4x4 = MAT4X4TOPXMAT(mMainTransform->Get_WorldMatrix());
	PxTransform nomalTransform = GetPxTransform(mPxMainMatrix4x4);

	PxReal density = 5.f;

	mMain_Actor = GetSingle(CPhysXMgr)->CreateDynamic_BaseActor(nomalTransform, *gemo, density, FLOAT3TOPXVEC3(mPhysXDesc.mVelocity));
	NULL_CHECK_BREAK(mMain_Actor);
	Safe_Delete(gemo);
	mPxDynamicActor = static_cast<PxRigidDynamic*>(mMain_Actor);

	SetBaseFlag();	

	return S_OK;
}

HRESULT CCollider_PhysX_Dynamic::Set_RigidbodyFlag(PxRigidBodyFlag::Enum e, bool value)
{
	// eKINEMATIC // ��� ���� / ĳ���Ϳ�
	// eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES // ������� �� ������Ʈ
	// eENABLE_CCD  // ��� �浹 ����X  Kinecmatic ���� X
	// eFORCE_KINE_KINE_NOTIFICATIONS	// Kinecmatic Kinecmatic �浹 ó��
	// eFORCE_STATIC_KINE_NOTIFICATIONS // Kinecmatic Static �浹 ó��
	
	mPxDynamicActor->setRigidBodyFlag(e, value);
	return S_OK;

}

HRESULT CCollider_PhysX_Dynamic::Set_AddForce(PxVec3 foreVec, PxForceMode::Enum mode)
{
	mPxDynamicActor->addForce(foreVec, mode);
	return S_OK;
}

HRESULT CCollider_PhysX_Dynamic::Clear_Force(PxForceMode::Enum mode)
{
	mPxDynamicActor->clearForce();
	return S_OK;
}

void CCollider_PhysX_Dynamic::SetBaseFlag()
{
	// Base Flag
	// �⺻ ����

	mPxDynamicActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
	mPxDynamicActor->setActorFlag(PxActorFlag::eSEND_SLEEP_NOTIFIES, true);

	DYNAMICFLAG flag;
	flag.fSleepValue = 1;
	flag.fStabValue = 1;
	flag.fContactReportThreshold = 5;
	flag.fWakeCounter = 5;
	Set_DynamicFlag(flag);

	DYNAMICFORCE force;
	force.fMass = 1.0f;
	force.fMaxLinearSpeed = 10;
	force.fMaxAngleSpeed = 10;
	Set_DynamicValue(force);
}



HRESULT CCollider_PhysX_Dynamic::Set_DynamicFlag(DYNAMICFLAG flag)
{
	// �Ӱ谪 ���� 
	mPxDynamicActor->setSleepThreshold(flag.fSleepValue);
	mPxDynamicActor->setStabilizationThreshold(flag.fStabValue);
	// �浹�� ���� �Ӱ谪
	mPxDynamicActor->setContactReportThreshold(flag.fContactReportThreshold);
	mPxDynamicActor->setWakeCounter(flag.fWakeCounter);
//	#PxPairFlag�� �����ϼ���.
	return S_OK;

}

HRESULT CCollider_PhysX_Dynamic::Set_DynamicValue(DYNAMICFORCE desc)
{
	// ���� �ӵ� ����
	mPxDynamicActor->setMass(desc.fMass);
	mPxDynamicActor->setLinearVelocity(desc.fLinearVelocity);
	mPxDynamicActor->setAngularVelocity(desc.fAngleVelocity);

	if (desc.fMaxAngleSpeed != 0)
		mPxDynamicActor->setMaxAngularVelocity(desc.fMaxLinearSpeed);
	if (desc.fMaxAngleSpeed != 0)
		mPxDynamicActor->setMaxLinearVelocity(desc.fMaxAngleSpeed);

	if (desc.fDampingLinearSpeed != 0)
		mPxDynamicActor->setLinearDamping(desc.fDampingLinearSpeed);
	if (desc.fDampingAngleSpeed != 0)
		mPxDynamicActor->setMaxLinearVelocity(desc.fDampingAngleSpeed);

	return S_OK;

}

HRESULT CCollider_PhysX_Dynamic::Set_DynamicLock(PxRigidDynamicLockFlag::Enum e, bool value)
{
	// ȸ���� �̵������� Lock
	mPxDynamicActor->setRigidDynamicLockFlag(e, value);

	return S_OK;
}




CCollider_PhysX_Dynamic  * CCollider_PhysX_Dynamic ::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{

	CCollider_PhysX_Dynamic * pInstance = new CCollider_PhysX_Dynamic (pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Create Transform Prototype");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CCollider_PhysX_Dynamic ::Clone(void * pArg)
{
	CCollider_PhysX_Dynamic * pInstance = new CCollider_PhysX_Dynamic ((*this));

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Create Transform");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCollider_PhysX_Dynamic ::Free()
{
	__super::Free();




}
