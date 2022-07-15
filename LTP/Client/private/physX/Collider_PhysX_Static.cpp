#include "stdafx.h"
#include "..\Public\PhysX\Collider_PhysX_Static.h"


CCollider_PhysX_Static::CCollider_PhysX_Static(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CCollider_PhysX_Base(pDevice, pDeviceContext)
{
	mePhysX_ID = E_PHYTYPE_STATIC;
}

CCollider_PhysX_Static::CCollider_PhysX_Static(const CCollider_PhysX_Static & rhs)
	: CCollider_PhysX_Base(rhs)
{

}


HRESULT CCollider_PhysX_Static::Initialize_Prototype(void * pArg)
{
	if (FAILED(__super::Initialize_Prototype(pArg)))
		return E_FAIL;


	return S_OK;
}

HRESULT CCollider_PhysX_Static::Initialize_Clone(void * pArg)
{
	if (FAILED(__super::Initialize_Clone(pArg)))
		return E_FAIL;

	
	return S_OK;
}


HRESULT CCollider_PhysX_Static::Update_BeforeSimulation()
{
	
	FAILED_CHECK(__super::Update_BeforeSimulation());

	if (E_STATIC_BUFFER == mStaticID)
	{
		if (mMainTransform == nullptr)
			return E_FAIL;
	}

	if (mPhysXDesc.bTrigger)
	{
		if (mMain_Actor == nullptr || mMainTransform == nullptr)
			return E_FAIL;

		return S_OK;
	}
	

	return S_OK;
}

HRESULT CCollider_PhysX_Static::Update_AfterSimulation()
{
	FAILED_CHECK(__super::Update_AfterSimulation());

	if (E_STATIC_BUFFER == mStaticID)
	{
		mPxMainMatrix4x4 = MAT4X4TOPXMAT(mMainTransform->Get_WorldMatrix());

	}
	else
	{
		if (mPhysXDesc.bTrigger)
			return S_OK;

		// ���� ���� �� ����
	}	


	return S_OK;
}


#ifdef _DEBUG
HRESULT CCollider_PhysX_Static::Render()
{
	if (E_STATIC_BUFFER == mStaticID)
	{
		
		// ��翡 ���� �����
		m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);
		m_pDeviceContext->IASetInputLayout(m_pInputLayout);
		m_pBasicEffect->SetWorld(XMMatrixIdentity());

		m_pBasicEffect->SetView(GetSingle(CGameInstance)->Get_Transform_Matrix(PLM_VIEW));
		m_pBasicEffect->SetProjection(GetSingle(CGameInstance)->Get_Transform_Matrix(PLM_PROJ));
		m_pBasicEffect->Apply(m_pDeviceContext);

		m_pBatch->Begin();
		// ��� ���� �׷��ش�.
		mRenderColor = DirectX::Colors::White;
		RenderBuffer(mPhysXDesc.eShapeType, mPxMainMatrix4x4, mRenderColor);
		m_pBatch->End();

	}
	else
	{
		if (mPhysXDesc.bTrigger)
			mRenderColor = DirectX::Colors::Green;
		else
			mRenderColor = DirectX::Colors::Red;

		FAILED_CHECK(__super::Render());
	}
	return S_OK;
}
#endif

CCollider_PhysX_Static * CCollider_PhysX_Static::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{

	CCollider_PhysX_Static* pInstance = NEW CCollider_PhysX_Static(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Create Transform Prototype");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CCollider_PhysX_Static::Clone(void * pArg)
{
	CCollider_PhysX_Static* pInstance = NEW CCollider_PhysX_Static((*this));

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Create Transform");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCollider_PhysX_Static::Free()
{
	__super::Free();

}

HRESULT CCollider_PhysX_Static::Set_ColiiderDesc(PHYSXDESC_STATIC desc)
{
	// �浹 �� �ʱ�ȭ
	memcpy(&mPhysXDesc, &desc, sizeof(PHYSXDESC_STATIC));


	// �� ������ �ݶ��̴� �ʱ�ȭ
	// ��ġ / ������ / ���� Ÿ�� / ����� �����켭 �ݶ��̴� ������Ʈ ����
	if (mMain_Actor)
		return E_FAIL;

	mMainTransform = mPhysXDesc.mTrnasform;
	mMainGameObject = mPhysXDesc.mGameObect;

	_float3 scale = mMainTransform->Get_Scale();
	_float3 pos = mMainTransform->Get_MatrixState(CTransform::STATE_POS);

	// ������Ʈ�� ����
	PxGeometry* gemo = nullptr;
	gemo = Create_Geometry(desc.eShapeType, scale);
	NULL_CHECK_BREAK(gemo);

	mPxMainMatrix4x4 = MAT4X4TOPXMAT(mMainTransform->Get_WorldMatrix());
	PxTransform nomalTransform = GetPxTransform(mPxMainMatrix4x4);

	// ��� ����
	PxShape* shape = nullptr;
	if (desc.bTrigger)
		shape = GetSingle(CPhysXMgr)->CreateDemoShape(SHAPE_BASE_TRIGGER, *gemo, false);
	else
		shape = GetSingle(CPhysXMgr)->CreateDemoShape(SHAPE_NONE,*gemo,false);
	NULL_CHECK_BREAK(shape);

	// ���� ����
	mMain_Actor = GetSingle(CPhysXMgr)->CreateStatic_Base_ShapeActor(nomalTransform, *shape);
	NULL_CHECK_BREAK(mMain_Actor);
	mPxRigStaticActor = static_cast<PxRigidStatic*>(mPxRigStaticActor);

	PxShape* shapes[1];
	const PxU32 numShapes = 1;
	mMain_Actor->getShapes(shapes, numShapes);
	mMainShape = shapes[0];
	NULL_CHECK_BREAK(mMainShape);

	Safe_Delete(gemo);
	
	// Flag
	mMain_Actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	mMain_Actor->setActorFlag(PxActorFlag::eSEND_SLEEP_NOTIFIES, false);
	// DebugName
	// mMain_Actor->setName("NONE");

	return S_OK;
}

HRESULT CCollider_PhysX_Static::Set_ColiiderBufferDesc(PHYSXDESC_STATIC desc)
{
	mMain_Actor = nullptr;
	mStaticID = CCollider_PhysX_Static::E_STATIC_BUFFER;
	memcpy(&mPhysXDesc, &desc, sizeof(PHYSXDESC_STATIC));
	mMainTransform = mPhysXDesc.mTrnasform;
	mMainGameObject = mPhysXDesc.mGameObect;
	mPxMainMatrix4x4 = MAT4X4TOPXMAT(mMainTransform->Get_WorldMatrix());
	return S_OK;

}

HRESULT CCollider_PhysX_Static::Set_eDISABLE_SIMULATION(bool b)
{
	mMain_Actor->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, b);
	return S_OK;
}
