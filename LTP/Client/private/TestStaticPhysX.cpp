#include "stdafx.h"
#include "..\public\TestStaticPhysX.h"


CTestStaticPhysX::CTestStaticPhysX(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CGameObject(pDevice, pDeviceContext)
{
}

CTestStaticPhysX::CTestStaticPhysX(const CTestStaticPhysX & rhs)
	: CGameObject(rhs)
{
}

HRESULT CTestStaticPhysX::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CTestStaticPhysX::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(0, 0, 0));
	m_pTransformCom->Scaled_All(_float3(1, 1, 1));

//	mTrans.transform(PxVec3(0, 0, 0));
//	PxRigidDynamic* asd = GetSingle(CPhysXMgr)->gPhysics->createRigidDynamic(mTrans);
//	GetSingle(CPhysXMgr)->CreateSphere_Actor(asd, CPhysXMgr::gMaterial, 5.0f);

	// �浹ü �ޱ�
	mActor = GetSingle(CPhysXMgr)->CreateDynamic(PxTransform(0, 0, 0), PxBoxGeometry(1,1,1));
		;
	GetSingle(CPhysXMgr)->CreateSphere_Actor(mActor, GetSingle(CPhysXMgr)->gMaterial, 10.0f);

	
	return S_OK;
}

_int CTestStaticPhysX::Update(_double fDeltaTime)
{

	if (__super::Update(fDeltaTime) < 0)return -1;
	Update_Trans2Px();

//	FAILED_CHECK(m_pModel->Update_AnimationClip(fDeltaTime, true));


	return _int();
}

_int CTestStaticPhysX::LateUpdate(_double fDeltaTime)
{
	if (__super::LateUpdate(fDeltaTime) < 0)return -1;

	FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));

	Update_Px2Trans();

	return _int();
}

_int CTestStaticPhysX::Render()
{
	if (__super::Render() < 0)		
		return -1;

	NULL_CHECK_RETURN(m_pModel, E_FAIL);

	CGameInstance* pInstance = GetSingle(CGameInstance);
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_VIEW), sizeof(_float4x4)));
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_PROJ), sizeof(_float4x4)));

	FAILED_CHECK(m_pTransformCom->Bind_OnShader(m_pShaderCom, "g_WorldMatrix"));

	_uint NumMaterial = m_pModel->Get_NumMaterial();

	for (_uint i = 0; i < NumMaterial; i++)
	{
		for (_uint j = 0; j < AI_TEXTURE_TYPE_MAX; j++)
			FAILED_CHECK(m_pModel->Bind_OnShader(m_pShaderCom, i, j, MODLETEXTYPE(j)));

		FAILED_CHECK(m_pModel->Render(m_pShaderCom, 2, i, "g_BoneMatrices"));
	}
	return _int();
}

_int CTestStaticPhysX::LateRender()
{
	return _int();
}



HRESULT CTestStaticPhysX::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VNAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_MONSTER_BULLET(VAYUSURA_LEADER_BULLET), TAG_COM(Com_Model), (CComponent**)&m_pModel));

	CTransform::TRANSFORMDESC tDesc = {};

	tDesc.fMovePerSec = 5;
	tDesc.fRotationPerSec = XMConvertToRadians(60);
	tDesc.fScalingPerSec = 1.f;
	tDesc.vPivot = _float3(0, 0, 0);

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));

	return S_OK;
}

HRESULT CTestStaticPhysX::Update_Trans2Px()
{
	// Transform ��ġ PX�� ������Ʈ
	mTrans = PxTransform(*(PxVec3*)&m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS));
	return S_OK;
}

HRESULT CTestStaticPhysX::Update_Px2Trans()
{
	mTrans = mActor->getGlobalPose();
	_float3 vec3 = *(_float3*)&mTrans.p;
	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, vec3);


	return S_OK;
}



CTestStaticPhysX * CTestStaticPhysX::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CTestStaticPhysX*	pInstance = new CTestStaticPhysX(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		DEBUGBREAK;
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTestStaticPhysX::Clone(void * pArg)
{
	CTestStaticPhysX*	pInstance = new CTestStaticPhysX(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		DEBUGBREAK;
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTestStaticPhysX::Free()
{
	__super::Free();


	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
}
