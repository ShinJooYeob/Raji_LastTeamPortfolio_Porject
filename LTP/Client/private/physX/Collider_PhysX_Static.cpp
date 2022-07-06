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

	if (FAILED(__super::Update_BeforeSimulation()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCollider_PhysX_Static::Update_AfterSimulation()
{
	if (FAILED(__super::Update_AfterSimulation()))
		return E_FAIL;


	return S_OK;
}


#ifdef _DEBUG
HRESULT CCollider_PhysX_Static::Render()
{
	FAILED_CHECK(__super::Render());

	

	return S_OK;
}
#endif

CCollider_PhysX_Static * CCollider_PhysX_Static::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{

	CCollider_PhysX_Static* pInstance = new CCollider_PhysX_Static(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Create Transform Prototype");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CCollider_PhysX_Static::Clone(void * pArg)
{
	CCollider_PhysX_Static* pInstance = new CCollider_PhysX_Static((*this));

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

	PxGeometry* gemo = nullptr;

	mMainTransform = mPhysXDesc.mTrnasform;

	_float3 scale = mMainTransform->Get_Scale();
	_float3 halfscale = _float3(scale.x*0.5f, scale.y*0.5f, scale.z*0.5f);

	_float3 pos = mMainTransform->Get_MatrixState(CTransform::STATE_POS);

	switch (mPhysXDesc.eShapeType)
	{
	case Client::E_GEOMAT_BOX:
		gemo = NEW PxBoxGeometry(FLOAT3TOPXVEC3(halfscale));
		break;
	case Client::E_GEOMAT_SPEHE:
		gemo = NEW PxSphereGeometry(PxReal(halfscale.x));
		break;
	case Client::E_GEOMAT_CAPSULE:
		gemo = NEW PxCapsuleGeometry(PxReal(halfscale.x), PxReal(halfscale.y));
		break;
	case Client::E_GEOMAT_SHAPE:

		break;
	case Client::E_GEOMAT_VERTEX:
		break;
	case Client::E_GEOMAT_TRIANGLE:
		break;
	case Client::E_GEOMAT_END:
		break;

	default:
		break;
	}

	PxTransform pxtrans = PxTransform(FLOAT3TOPXVEC3(pos));
	_Sfloat4x4 float4x4 = mMainTransform->Get_WorldFloat4x4();
	_Squternion q = _Squternion::CreateFromRotationMatrix(float4x4);
	pxtrans.q = *(PxQuat*)&q;

	NULL_CHECK_BREAK(gemo);

	mMain_Actor = GetSingle(CPhysXMgr)->CreateStatic_BaseActor(pxtrans, *gemo);
	NULL_CHECK_BREAK(mMain_Actor);
	Safe_Delete(gemo);

	return S_OK;
}
