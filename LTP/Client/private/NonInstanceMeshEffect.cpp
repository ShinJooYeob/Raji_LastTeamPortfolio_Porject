#include "stdafx.h"
#include "..\public\NonInstanceMeshEffect.h"


CNonInstanceMeshEffect::CNonInstanceMeshEffect(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	: CGameObject(pDevice, pDeviceContext)
{
}

CNonInstanceMeshEffect::CNonInstanceMeshEffect(const CNonInstanceMeshEffect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CNonInstanceMeshEffect::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));

	return S_OK;
}

HRESULT CNonInstanceMeshEffect::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	NULL_CHECK_RETURN(pArg, E_FAIL);
	memcpy(&m_tMeshDesc, pArg, sizeof(NONINSTNESHEFTDESC));


	if (!((m_tMeshDesc.m_iPassIndex >= 23 && m_tMeshDesc.m_iPassIndex <= 24) || (m_tMeshDesc.m_iPassIndex >= 16 && m_tMeshDesc.m_iPassIndex <= 20)))
	{
		__debugbreak();
		return E_FAIL;
	}


	FAILED_CHECK(SetUp_Components());
	


	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_tMeshDesc.vPosition);
	m_pTransformCom->LookDir(m_tMeshDesc.vLookDir.XMVector());

	m_pTransformCom->Scaled_All(m_tMeshDesc.vSize);


	switch (m_tMeshDesc.RotAxis)
	{
	case FollowingDir_Right:
		m_vRotAxis = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_RIGHT);
		break;
	case FollowingDir_Up:
		m_vRotAxis = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_UP);
		break;
	case FollowingDir_Look:
		m_vRotAxis = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_LOOK);
		break;
	default:
		__debugbreak();
		break;
	}

	if (m_tMeshDesc.OnceStartRot)
	{
		_float Old = m_pTransformCom->Get_TurnSpeed();
		m_pTransformCom->Set_TurnSpeed(1);
		m_pTransformCom->Turn_CW(m_vRotAxis.XMVector(), XMConvertToRadians(m_tMeshDesc.OnceStartRot));
		m_pTransformCom->Set_TurnSpeed(Old);

	}

	m_pTransformCom->Turn_CW(m_vRotAxis.XMVector(), m_tMeshDesc.StartRot);
	

	switch (m_tMeshDesc.MoveDir)
	{
	case FollowingDir_Right:
		m_vMoveDir = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_RIGHT);
		break;
	case FollowingDir_Up:
		m_vMoveDir = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_UP);
		break;
	case FollowingDir_Look:
		m_vMoveDir = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_LOOK);
		break;
	default:
		__debugbreak();
		break;
	}

	Set_LimLight_N_Emissive( m_tMeshDesc.vLimLight ,  m_tMeshDesc.vEmissive );

	if (m_tMeshDesc.SizeSpeed != 0)
	{
		m_pTransformCom->Set_ScalingSpeed(m_tMeshDesc.SizeSpeed);
	}

	if (m_tMeshDesc.m_bNotDead)
		m_fCurTime_Duration = 99999999999999999999999.f;

	return S_OK;
}

_int CNonInstanceMeshEffect::Update(_double fDeltaTime)
{
	if (m_bIsDead) return 0;

	if (__super::Update(fDeltaTime) < 0) return -1;

	if (m_fCurTime_Duration > m_tMeshDesc.fMaxTime_Duration)
	{
		if (m_tMeshDesc.m_bNotDead) return 0;
		else
		{
			if (m_tMeshDesc.m_bReverseSizing)
			{
				m_fReverseSizePassedTimer +=(_float)fDeltaTime;
				if (m_fReverseSizePassedTimer > m_tMeshDesc.m_bReverseSizingTimer)
				{
					Set_IsDead();
					return 0;
				}

				if (m_tMeshDesc.SizeSpeed != 0)
				{

					_float3 OldScale = m_pTransformCom->Get_Scale();

					if (m_tMeshDesc.vSizingRUL.x != 0)
						m_pTransformCom->Scaling(CTransform::STATE_RIGHT, m_tMeshDesc.vSizingRUL.x * -fDeltaTime*2.f);
					if (m_tMeshDesc.vSizingRUL.y != 0)
						m_pTransformCom->Scaling(CTransform::STATE_UP, m_tMeshDesc.vSizingRUL.y * -fDeltaTime);
					if (m_tMeshDesc.vSizingRUL.z != 0)
						m_pTransformCom->Scaling(CTransform::STATE_LOOK, m_tMeshDesc.vSizingRUL.z * -fDeltaTime*2.f);


					_float3 NowScale = m_pTransformCom->Get_Scale();

					if ((m_tMeshDesc.vSizingRUL.x != 0) && ((OldScale.x - m_tMeshDesc.vSizieLimit.x) *(NowScale.x - m_tMeshDesc.vSizieLimit.x) < 0))
						m_pTransformCom->Scaled(CTransform::STATE_RIGHT, OldScale.x);
					if ((m_tMeshDesc.vSizingRUL.y != 0) && ((OldScale.y - m_tMeshDesc.vSizieLimit.y) *(NowScale.y - m_tMeshDesc.vSizieLimit.y) < 0))
						m_pTransformCom->Scaled(CTransform::STATE_UP, OldScale.y);
					if ((m_tMeshDesc.vSizingRUL.z != 0) && ((OldScale.z - m_tMeshDesc.vSizieLimit.z) *(NowScale.z - m_tMeshDesc.vSizieLimit.z) < 0))
						m_pTransformCom->Scaled(CTransform::STATE_LOOK, OldScale.z);
				}

			}
			else
			{
				Set_IsDead();
				return 0;
			}
		}
	}


	m_fCurTime_Duration += (_float)fDeltaTime;

	m_pTransformCom->Turn_CW(m_vRotAxis.XMVector(), fDeltaTime);

	if (m_tMeshDesc.MoveSpeed != 0)
	{
		m_pTransformCom->MovetoDir_bySpeed(m_vMoveDir.XMVector(), m_tMeshDesc.MoveSpeed, fDeltaTime);
	}
	if (!m_fReverseSizePassedTimer && m_tMeshDesc.SizeSpeed != 0)
	{
		_float3 OldScale = m_pTransformCom->Get_Scale();

		if (m_tMeshDesc.vSizingRUL.x != 0)
			m_pTransformCom->Scaling(CTransform::STATE_RIGHT, m_tMeshDesc.vSizingRUL.x * fDeltaTime);
		if (m_tMeshDesc.vSizingRUL.y != 0 )
			m_pTransformCom->Scaling(CTransform::STATE_UP, m_tMeshDesc.vSizingRUL.y * fDeltaTime);
		if (m_tMeshDesc.vSizingRUL.z != 0 )
			m_pTransformCom->Scaling(CTransform::STATE_LOOK, m_tMeshDesc.vSizingRUL.z * fDeltaTime);

		_float3 NowScale = m_pTransformCom->Get_Scale();

		if ((m_tMeshDesc.vSizingRUL.x != 0) &&((OldScale.x - m_tMeshDesc.vSizieLimit.x) *(NowScale.x - m_tMeshDesc.vSizieLimit.x) < 0))
			m_pTransformCom->Scaled(CTransform::STATE_RIGHT, OldScale.x);
		if ((m_tMeshDesc.vSizingRUL.y != 0) && ((OldScale.y - m_tMeshDesc.vSizieLimit.y) *(NowScale.y - m_tMeshDesc.vSizieLimit.y) < 0))
			m_pTransformCom->Scaled(CTransform::STATE_UP, OldScale.y);
		if ((m_tMeshDesc.vSizingRUL.z != 0) && ((OldScale.z - m_tMeshDesc.vSizieLimit.z) *(NowScale.z - m_tMeshDesc.vSizieLimit.z) < 0))
			m_pTransformCom->Scaled(CTransform::STATE_LOOK, OldScale.z);

	}

	//m_tMeshDesc.NoiseTextureIndex = 381;
	//m_tMeshDesc.MaskTextureIndex = 10;
	//m_tMeshDesc.iDiffuseTextureIndex = 300;
	//m_tMeshDesc.m_iPassIndex = 19;
	//m_tMeshDesc.vEmissive = _float4(1, 0.5f, 1.f, 0);
	//m_tMeshDesc.vLimLight = _float4(1, 0, 0, 1);


	//Set_LimLight_N_Emissive(m_tMeshDesc.vLimLight, m_tMeshDesc.vEmissive);




	return _int();
}

_int CNonInstanceMeshEffect::LateUpdate(_double fDeltaTimer)
{
	if (m_bIsDead) return 0;
	if (m_fCurTime_Duration > m_tMeshDesc.fMaxTime_Duration && m_fReverseSizePassedTimer > m_tMeshDesc.m_bReverseSizingTimer)		return 0;

	if (__super::LateUpdate(fDeltaTimer) < 0) return -1;


	if (m_tMeshDesc.m_iPassIndex == 23)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND_NOLIGHT, this));
	}
	else if (m_tMeshDesc.m_iPassIndex > 17)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}
	else
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_DISTORTION, this));
	}

	return _int();
}

_int CNonInstanceMeshEffect::Render()
{
	if (m_bIsDead) return 0;
	if (m_fCurTime_Duration > m_tMeshDesc.fMaxTime_Duration && m_fReverseSizePassedTimer > m_tMeshDesc.m_bReverseSizingTimer)		return 0;

	if (__super::Render() < 0)		return -1;



	NULL_CHECK_RETURN(m_pModel, E_FAIL);

	CGameInstance* pInstance = GetSingle(CGameInstance);


	//_float4 color = _float4(1.f, 0.734375f, 0.75234375f, 1);
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_vColor", &m_tMeshDesc.vColor, sizeof(_float4)));
	
	
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_VIEW), sizeof(_float4x4)));
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_PROJ), sizeof(_float4x4)));
	FAILED_CHECK(m_pTransformCom->Bind_OnShader(m_pShaderCom, "g_WorldMatrix"));

	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_fTimer", &m_fCurTime_Duration, sizeof(_float)));
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_fAppearTimer", &m_tMeshDesc.fAppearTime, sizeof(_float)));
	if (m_tMeshDesc.m_bReverseSizing)
	{
		_float MaxTime = m_tMeshDesc.fMaxTime_Duration + m_tMeshDesc.m_bReverseSizingTimer;
		FAILED_CHECK(m_pShaderCom->Set_RawValue("g_fMaxTime", &MaxTime, sizeof(_float)));
	}
	else
	{
		FAILED_CHECK(m_pShaderCom->Set_RawValue("g_fMaxTime", &m_tMeshDesc.fMaxTime_Duration, sizeof(_float)));
	}
	
	FAILED_CHECK(m_pShaderCom->Set_RawValue("noisingdir", &m_tMeshDesc.noisingdir, sizeof(_float2)));
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_fDistortionNoisingPushPower", &m_tMeshDesc.fDistortionNoisingPushPower, sizeof(_float)));

	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_fAlphaTestValue", &m_tMeshDesc.fAlphaTestValue, sizeof(_float)));

	
	FAILED_CHECK(GetSingle(CUtilityMgr)->Bind_UtilTex_OnShader(CUtilityMgr::UTILTEX_NOISE, m_pShaderCom, "g_NoiseTexture", m_tMeshDesc.NoiseTextureIndex));
	FAILED_CHECK(GetSingle(CUtilityMgr)->Bind_UtilTex_OnShader(CUtilityMgr::UTILTEX_MASK, m_pShaderCom, "g_SourTexture", m_tMeshDesc.MaskTextureIndex));
	FAILED_CHECK(m_pShaderCom->Set_Texture("g_BackBufferTexture", g_pGameInstance->Get_SRV(L"Target_ReferenceDefferred")));

	_uint NumMaterial = m_pModel->Get_NumMaterial();

	for (_uint i = 0; i < NumMaterial; i++)
	{
		for (_uint j = 0; j < AI_TEXTURE_TYPE_MAX; j++)
		{
			if (j == 1)
			{
				FAILED_CHECK(GetSingle(CUtilityMgr)->Bind_UtilTex_OnShader(CUtilityMgr::UTILTEX_NOISE, m_pShaderCom, "g_DiffuseTexture", m_tMeshDesc.iDiffuseTextureIndex));
			}
			else
			{
				FAILED_CHECK(m_pModel->Bind_OnShader(m_pShaderCom, i, j, MODLETEXTYPE(j)));
			}
		}

		FAILED_CHECK(m_pModel->Render(m_pShaderCom, m_tMeshDesc.m_iPassIndex, i));
	}

	return _int();
}

_int CNonInstanceMeshEffect::LateRender()
{
	return _int();
}

HRESULT CNonInstanceMeshEffect::ReInitialize(_float3 vPosition, _float3 vLookDir)
{

	m_tMeshDesc.vPosition = vPosition;
	m_tMeshDesc.vLookDir = vLookDir;

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_tMeshDesc.vPosition);
	m_pTransformCom->LookDir(m_tMeshDesc.vLookDir.XMVector());

	m_pTransformCom->Scaled_All(m_tMeshDesc.vSize);

	switch (m_tMeshDesc.RotAxis)
	{
	case FollowingDir_Right:
		m_vRotAxis = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_RIGHT);
		break;
	case FollowingDir_Up:
		m_vRotAxis = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_UP);
		break;
	case FollowingDir_Look:
		m_vRotAxis = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_LOOK);
		break;
	default:
		__debugbreak();
		break;
	}

	if (m_tMeshDesc.OnceStartRot)
	{
		_float Old = m_pTransformCom->Get_TurnSpeed();
		m_pTransformCom->Set_TurnSpeed(1);
		m_pTransformCom->Turn_CW(m_vRotAxis.XMVector(), XMConvertToRadians(m_tMeshDesc.OnceStartRot));
		m_pTransformCom->Set_TurnSpeed(Old);

	}

	m_pTransformCom->Turn_CW(m_vRotAxis.XMVector(), m_tMeshDesc.StartRot);


	switch (m_tMeshDesc.MoveDir)
	{
	case FollowingDir_Right:
		m_vMoveDir = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_RIGHT);
		break;
	case FollowingDir_Up:
		m_vMoveDir = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_UP);
		break;
	case FollowingDir_Look:
		m_vMoveDir = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_LOOK);
		break;
	default:
		__debugbreak();
		break;
	}

	Set_LimLight_N_Emissive(m_tMeshDesc.vLimLight, m_tMeshDesc.vEmissive);

	if (m_tMeshDesc.SizeSpeed != 0)
	{
		m_pTransformCom->Set_ScalingSpeed(m_tMeshDesc.SizeSpeed);
	}

	m_fCurTime_Duration = 0.f;

	return S_OK;
}


HRESULT CNonInstanceMeshEffect::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VNAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(m_tMeshDesc.eMeshType), TAG_COM(Com_Model), (CComponent**)&m_pModel));

	CTransform::TRANSFORMDESC tDesc = {};
	tDesc.fMovePerSec = 30;
	tDesc.fRotationPerSec = XMConvertToRadians(m_tMeshDesc.RotationSpeedPerSec);
	tDesc.fScalingPerSec = 1;
	tDesc.vPivot = _float3(0, 0, 0);
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));

	return S_OK;
}


CNonInstanceMeshEffect * CNonInstanceMeshEffect::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CNonInstanceMeshEffect*	pInstance = NEW CNonInstanceMeshEffect(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CNonInstanceMeshEffect");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CNonInstanceMeshEffect::Clone(void * pArg)
{
	CNonInstanceMeshEffect*	pInstance = NEW CNonInstanceMeshEffect(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CNonInstanceMeshEffect");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CNonInstanceMeshEffect::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pModel);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pParentTranscom);

}
