#include "stdafx.h"
#include "..\public\PlayerWeapon_Sword.h"
#include "Camera_Main.h"

CPlayerWeapon_Sword::CPlayerWeapon_Sword(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CPlayerWeapon(pDevice, pDeviceContext)
{
}

CPlayerWeapon_Sword::CPlayerWeapon_Sword(const CPlayerWeapon_Sword & rhs)
	: CPlayerWeapon(rhs)
{
}

HRESULT CPlayerWeapon_Sword::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));

	return S_OK;
}

HRESULT CPlayerWeapon_Sword::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());
	FAILED_CHECK(SetUp_Collider());
	FAILED_CHECK(SetUp_EtcInfo());

	FAILED_CHECK(Ready_ParticleDesc());

	return S_OK;
}

_int CPlayerWeapon_Sword::Update(_double fDeltaTime)
{
	if (false == m_pDissolveCom->Get_IsFadeIn() && 1.f <= m_pDissolveCom->Get_DissolvingRate())
	{
		m_pTextureParticleTransform->Set_IsOwnerDead(true);
		return 0;
	}
	if (__super::Update(fDeltaTime) < 0) return -1;





	switch (m_tPlayerWeaponDesc.eWeaponState)
	{
	case EWeaponState::STATE_STRUCTURE:
		Update_Structure(fDeltaTime);
		break;
	case EWeaponState::STATE_EQUIP:
		Update_Equip(fDeltaTime);
		break;
	case EWeaponState::STATE_NON_EQUIP:
		Update_NoEquip(fDeltaTime);
		break;
	}

	m_tPlayerWeaponDesc.eAttachedDesc.Set_DefaultBonePivot(_float3(1.f, 1.f, 1.f), _float3(90, -170, -10), _float3(0.0, 0.0, 0.0));
	m_pTransformCom->Set_MatrixState(CTransform::TransformState::STATE_POS, _float3(0.4f, 1.19f, 0.09f));

	m_pModel->Change_AnimIndex(0); 
	FAILED_CHECK(m_pModel->Update_AnimationClip(fDeltaTime, true));
	
	// Collider
	Update_Colliders();
	if (true == m_bActiveCollision)
	{
		FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_PlayerWeapon, this, m_pCollider));
	}

	if (true == m_bActiveCollision_1)
	{
		Update_Colliders_MainAttackCombo3();
		FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_PlayerWeapon, this, m_pCollider_MainAttack_Combo3));
	}

	if (true == m_bActiveCollision_2)
	{
		Update_Colliders_PowerAttackCombo3();
		FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_PlayerWeapon, this, m_pCollider_PowerAttack_Combo3));
	}

	if (true == m_bActiveCollision_3)
	{
		Update_Colliders_UltimateAttack();
		FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_PlayerWeapon, this, m_pCollider_Ultimate));
	}
	//

	FAILED_CHECK(m_pDissolveCom->Update_Dissolving(fDeltaTime));


	if (m_pTextureParticleTransform->Get_IsOwnerDead())
	{

		GetSingle(CUtilityMgr)->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[0]);
		m_pTextureParticleTransform->Set_IsOwnerDead(false);
	}
	m_pTextureParticleTransform->Set_MatrixState(CTransform::STATE_POS, m_pCollider->Get_ColliderPosition(rand() % 4 + 1));
	
	if (m_ParticlePassedTime < m_ParticleTargetTime)
	{
		static _double ThunderTimer = 0;
		ThunderTimer += fDeltaTime;
		m_ParticlePassedTime += (_float)fDeltaTime;
		m_pMeshParticleTransform->MovetoDir_bySpeed(m_vParticleMovingDir.XMVector(), 10.f, (_float)fDeltaTime);


		if (ThunderTimer > m_ParticleTargetTime * 0.0666667f)
		{
			ThunderTimer = 0;

			m_vecNonInstMeshDesc[0].eMeshType = COMPONENTPROTOTYPEID(Prototype_Mesh_Lightning_01 + rand() % 3);
			m_vecNonInstMeshDesc[0].vPosition = m_pMeshParticleTransform->Get_MatrixState(CTransform::STATE_POS) +
				XMVectorSetY(GetSingle(CUtilityMgr)->RandomFloat3(-1, 1).XMVector(), 0);
			m_vecNonInstMeshDesc[0].vLookDir =
				XMVector3Normalize(XMVectorSet(0, 8, 0, 0) + XMVectorSetY(GetSingle(CUtilityMgr)->RandomFloat3(-1, 1).XMVector(), 0));
			g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_Particle),
				TAG_OP(Prototype_NonInstanceMeshEffect), &m_vecNonInstMeshDesc[0]);
		}
	}
	else
	{

		m_pMeshParticleTransform->Set_IsOwnerDead(true);
		DeActive_Collision_2();
	}
	
	return _int();
}

_int CPlayerWeapon_Sword::LateUpdate(_double fDeltaTimer)
{
	if (false == m_pDissolveCom->Get_IsFadeIn() && 1.f <= m_pDissolveCom->Get_DissolvingRate())
	{
		return 0;
	}

	if (__super::LateUpdate(fDeltaTimer) < 0) return -1;

	switch (m_tPlayerWeaponDesc.eWeaponState)
	{
	case EWeaponState::STATE_STRUCTURE:
		LateUpdate_Structure(fDeltaTimer);
		break;
	case EWeaponState::STATE_EQUIP:
		LateUpdate_Equip(fDeltaTimer);
		break;
	case EWeaponState::STATE_NON_EQUIP:
		LateUpdate_NoEquip(fDeltaTimer);
		break;
	}


	_Matrix mat = m_fAttachedMatrix.XMatrix();
	mat.r[0] = XMVector3Normalize(mat.r[0]);
	mat.r[1] = XMVector3Normalize(mat.r[1]);
	mat.r[2] = XMVector3Normalize(mat.r[2]);


	
	
	if (true == m_bActiveTrail)
	{
		Update_Trail(&mat, fDeltaTimer);
		m_fCurTime_ClearTrail = 0.f;
	}
	else
	{
		m_fCurTime_ClearTrail += (_float)fDeltaTimer;
		if (m_fCurTime_ClearTrail >= m_fMaxTime_ClearTrail)
		{
			m_fCurTime_ClearTrail = 0.f;
			m_pSwordTrail->Set_TrailTurnOn(false, _float3(0.f, 0.f, 0.f), _float3(0.f, 0.f, 0.f));
		}
	}


	FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_PRENONBLEND, this));
	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL_ATTACHED, this, m_pTransformCom, m_pShaderCom, m_pModel, &m_fAttachedMatrix));
	FAILED_CHECK(m_pRendererCom->Add_TrailGroup(CRenderer::TRAIL_SWORD_DISTORT, m_pSwordTrail));

	// Render Colliders
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pCollider));

	if (true == m_bActiveCollision_1)
	{
		FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pCollider_MainAttack_Combo3));
	}

	if (true == m_bActiveCollision_2)
	{
		FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pCollider_PowerAttack_Combo3));
	}

	if (true == m_bActiveCollision_3)
	{
		FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pCollider_Ultimate));
	}
	//


	m_fAttachedMatrix = m_fAttachedMatrix.TransposeXMatrix();
	return _int();
}

_int CPlayerWeapon_Sword::Render()
{
	if (__super::Render() < 0)		return -1;

	FAILED_CHECK(m_pRendererCom->End_RenderTarget(TEXT("MRT_Material")));
	FAILED_CHECK(m_pRendererCom->Begin_RenderTarget(TEXT("MRT_OccludedMaterial")));
	NULL_CHECK_RETURN(m_pModel, E_FAIL);

	CGameInstance* pInstance = GetSingle(CGameInstance);

	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_VIEW), sizeof(_float4x4)));
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_PROJ), sizeof(_float4x4)));
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_AttechMatrix", &m_fAttachedMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pTransformCom->Bind_OnShader(m_pShaderCom, "g_WorldMatrix"));

	FAILED_CHECK(m_pDissolveCom->Render(19));

	FAILED_CHECK(m_pRendererCom->End_RenderTarget(TEXT("MRT_OccludedMaterial")));
	FAILED_CHECK(m_pRendererCom->Begin_RenderTarget(TEXT("MRT_Material")));

	return _int();
}

_int CPlayerWeapon_Sword::LateRender()
{
	return _int();
}

void CPlayerWeapon_Sword::Active_Trail(_bool bActivate)
{
	__super::Active_Trail(bActivate);

	if (true == m_bActiveTrail)
	{
		_Matrix mat = m_pTransformCom->Get_WorldMatrix() * m_tPlayerWeaponDesc.eAttachedDesc.Caculate_AttachedBoneMatrix();
		mat.r[0] = XMVector3Normalize(mat.r[0]);
		mat.r[1] = XMVector3Normalize(mat.r[1]);
		mat.r[2] = XMVector3Normalize(mat.r[2]);

		m_pSwordTrail->Set_TrailTurnOn(true, 
			mat.r[3] + mat.r[2] * 1.31f - mat.r[0] * 0.33f + mat.r[1] * 0.05f,
			mat.r[3] + mat.r[2] * 1.2f - mat.r[0] * 0.1f + mat.r[1] * 0.015f
		);


	}
	/*else
	{
		m_pSwordTrail->Set_TrailTurnOn(false, _float3(0.f, 0.f, 0.f), _float3(0.f, 0.f, 0.f));
	}*/
}

void CPlayerWeapon_Sword::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	if (CollisionTypeID::CollisionType_Monster == eConflictedObjCollisionType)
	{
		_Vector vDamageDir = XMVector3Normalize(pConflictedCollider->Get_ColliderPosition(iConflictedObjColliderIndex).XMVector() - m_pTransformCom->Get_MatrixState(CTransform::TransformState::STATE_POS));

		if (pMyCollider == m_pCollider_Ultimate)
		{
			pConflictedObj->Take_Damage(this, 1.f, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower);
			pConflictedCollider->Set_Conflicted(0.2f);
		}
		else
		{
			CUtilityMgr* pUtil = GetSingle(CUtilityMgr);

			pUtil->PlusSwordshieldSkillPersent(1.f);

			if (0.f > pConflictedObj->Take_Damage(this, m_fDamage, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower))
			{
				pUtil->SlowMotionStart(2.f, 0.02f);
			}
			pConflictedCollider->Set_Conflicted(0.5f);

			m_vecTextureParticleDesc[2].vFixedPosition = m_vecTextureParticleDesc[3].vFixedPosition = m_vecTextureParticleDesc[4].vFixedPosition
				= (pMyCollider->Get_ColliderPosition(iMyColliderIndex).XMVector() + pConflictedCollider->Get_ColliderPosition(iConflictedObjColliderIndex).XMVector()) * 0.5f
				 +XMVectorSet(0, 0.1f, 0, 0);

			for (_uint i = 2; i < 5; i ++)
				FAILED_CHECK_NONERETURN(pUtil->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[i]));

			_int iSelectSoundFileIndex = rand() % 2;
			_tchar pSoundFile[MAXLEN] = TEXT("");
			swprintf_s(pSoundFile, TEXT("Jino_Raji_Sword_Impact_%d.wav"), iSelectSoundFileIndex);
			g_pGameInstance->Play3D_Sound(pSoundFile, m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_PLAYER, 1.f);
			pUtil->Get_MainCamera()->Start_CameraShaking_Fov(55.f, 3.f, 0.2f, true);
		}
	}
}

_bool CPlayerWeapon_Sword::AbleToChangeWeapon()
{
	return (false == m_pDissolveCom->Get_IsDissolving());
}

void CPlayerWeapon_Sword::Dissolve_In(_double fTargetTime)
{
	m_pDissolveCom->Set_DissolveOn(true, fTargetTime);
}

void CPlayerWeapon_Sword::Dissolve_Out(_double fTargetTime)
{
	m_pDissolveCom->Set_DissolveOn(false, fTargetTime);
}

void CPlayerWeapon_Sword::EffectParticleOn(_uint iIndex, void* pArg)
{
	switch (iIndex)
	{
	case 0:
		m_ParticlePassedTime = 0;
		m_ParticleTargetTime = m_vecMeshParticleDesc[0].TotalParticleTime;
		m_vParticleMovingDir = *(_float3*)(pArg);

		m_pMeshParticleTransform->Set_IsOwnerDead(false);
		m_pMeshParticleTransform->Set_MatrixState(CTransform::STATE_POS, m_pCollider->Get_ColliderPosition(4));



		GetSingle(CUtilityMgr)->Create_MeshInstance(m_eNowSceneNum, m_vecMeshParticleDesc[0]);
		GetSingle(CUtilityMgr)->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[1]);

		Active_Collision_2();
		break;
	default:
		break;
	}

}

void CPlayerWeapon_Sword::Set_WeaponDamage(EAttackType eAttackType, _int iComboCount)
{
	int* pSkillPoint = GetSingle(CUtilityMgr)->Get_LightningSkillPointArry();

	switch (eAttackType)
	{
	case CPlayerWeapon::ATTACK_MAIN:
	{
		m_fDamage = m_Arr_MainAttackDamage[pSkillPoint[0]][iComboCount];
		break;
	}
	case CPlayerWeapon::ATTACK_STRONG:
	{
		m_fDamage = m_Arr_StrongAttackDamage[pSkillPoint[0]][iComboCount];
		break;
	}
	case CPlayerWeapon::ATTACK_SUB:
	{
		m_fDamage = m_fSubAttackDamage;
		break;
	}
	}
}

void CPlayerWeapon_Sword::Set_ShieldBashAttack(_bool bShieldBashAttack)
{
	if (false == m_bShieldBashAttack)
	{
		GetSingle(CUtilityMgr)->Get_MainCamera()->Start_CameraShaking_Fov(56.f, 1.f, 0.2f, true);
	}
	m_bShieldBashAttack = bShieldBashAttack;
}

_fVector CPlayerWeapon_Sword::Get_BonePos(const char * pBoneName)
{
	_Matrix BoneMatrix = m_pModel->Get_BoneMatrix(pBoneName);
	_Matrix TransformMatrix = BoneMatrix * m_pTransformCom->Get_WorldMatrix();
	_Vector vPos, vRot, vScale;
	XMMatrixDecompose(&vScale, &vRot, &vPos, TransformMatrix);

	return vPos;
}

void CPlayerWeapon_Sword::Update_AttachCamPos()
{
}

_int CPlayerWeapon_Sword::Update_Structure(_double fDeltaTime)
{
	m_pTransformCom->Turn_CCW(XMVectorSet(0.f, 1.f, 0.f, 0.f), fDeltaTime);

	return _int();
}

_int CPlayerWeapon_Sword::Update_Equip(_double fDeltaTime)
{
	return _int();
}

_int CPlayerWeapon_Sword::Update_NoEquip(_double fDeltaTime)
{
	return _int();
}

_int CPlayerWeapon_Sword::LateUpdate_Structure(_double fDeltaTime)
{
	return _int();
}

_int CPlayerWeapon_Sword::LateUpdate_Equip(_double fDeltaTime)
{
	Update_AttachMatrix();

	return _int();
}

_int CPlayerWeapon_Sword::LateUpdate_NoEquip(_double fDeltaTime)
{
	return _int();
}

void CPlayerWeapon_Sword::Update_AttachMatrix()
{
	m_fAttachedMatrix = m_pTransformCom->Get_WorldMatrix()  * m_tPlayerWeaponDesc.eAttachedDesc.Caculate_AttachedBoneMatrix();
}

void CPlayerWeapon_Sword::Update_Trail(_fMatrix * pMat, _double fDeltaTime)
{
	m_pSwordTrail->Update_SwordTrail(((*pMat).r[3] + (*pMat).r[2] * 1.31f - (*pMat).r[0] * 0.33f + (*pMat).r[1] * 0.05f),
		((*pMat).r[3] + (*pMat).r[2] * 1.2f - (*pMat).r[0] * 0.1f + (*pMat).r[1] * 0.015f),	fDeltaTime, 0.488765131f);
}

void CPlayerWeapon_Sword::Change_Pivot(ESwordPivot ePitvot)
{
	switch (ePitvot)
	{
	case ESwordPivot::SWORD_PIVOT_NORMAL:
		m_tPlayerWeaponDesc.eAttachedDesc.Set_DefaultBonePivot(_float3(1, 1, 1), _float3(-97, -120, -60), _float3(-0.661f, -0.04f, -1.133f));
		break;
	case ESwordPivot::SWORD_PIVOT_THROW:
		m_tPlayerWeaponDesc.eAttachedDesc.Set_DefaultBonePivot(_float3(1.f, 1.f, 1.f), _float3(90, 0, 0), _float3(-0.661f, -0.04f, -1.133f));
		break;
	case ESwordPivot::SWORD_PIVOT_TAKEDOWN:
		m_tPlayerWeaponDesc.eAttachedDesc.Set_DefaultBonePivot(_float3(1.f, 1.f, 1.f), _float3(80, 130, 0), _float3(-0.661f, -0.04f, -1.133f));
		break;
	}
}

HRESULT CPlayerWeapon_Sword::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_PlayerWeapon_Sword), TAG_COM(Com_Model), (CComponent**)&m_pModel));

	CTransform::TRANSFORMDESC tDesc = {};

	tDesc.fMovePerSec = 5;
	tDesc.fRotationPerSec = XMConvertToRadians(60);
	tDesc.fScalingPerSec = 1;
	tDesc.vPivot = _float3(0, 0, 0);

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));


	CSwordTrail::TRAILDESC tSwordDesc;
	tSwordDesc.iPassIndex = 2;
	//
	//m_pSwordTrail->Set_Color({ 0.065f, 0.065f, 0.065f, 1.f });
	tSwordDesc.vColor = _float4(0.065f, 0.065f, 0.065f, 1.f);
	//tSwordDesc.vColor = _float4(0.98046875f, 0.93359375f, 0.19140625f, 1.f);
	//tSwordDesc.vColor = _float4(0.587f, 0.972f, 0.941f, 1.f);


	tSwordDesc.iTextureIndex = 7;
	tSwordDesc.NoiseSpeed = 10000.f;
	tSwordDesc.NoiseDir = _float2(-1, 0);
	tSwordDesc.NoiseTextureIndex = 351;
	tSwordDesc.MaskTextureIndex = 158;
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_SwordTrail), TAG_COM(Com_SwordTrail), (CComponent**)&m_pSwordTrail, &tSwordDesc));

	CDissolve::DISSOLVEDESC	tDissolveDesc;
	tDissolveDesc.eDissolveModelType = CDissolve::DISSOLVE_ANIM_ATTACHED_OLCD;
	tDissolveDesc.pModel = m_pModel;
	tDissolveDesc.pShader = m_pShaderCom;
	tDissolveDesc.RampTextureIndex = 1;
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Dissolve), TAG_COM(Com_Dissolve), (CComponent**)&m_pDissolveCom, &tDissolveDesc));

	return S_OK;
}

HRESULT CPlayerWeapon_Sword::SetUp_EtcInfo()
{
	m_fMaxTime_ClearTrail = 0.2f;

	// Setup Damage
	m_Arr_MainAttackDamage[0] = { 1.f, 1.f, 2.f };
	m_Arr_MainAttackDamage[1] = { 1.f, 2.f, 2.f };
	m_Arr_MainAttackDamage[2] = { 1.f, 2.f, 3.f };
	m_Arr_MainAttackDamage[3] = { 2.f, 2.f, 3.f };

	m_Arr_StrongAttackDamage[0] = { 1.f, 1.f, 2.f };
	m_Arr_StrongAttackDamage[1] = { 1.f, 2.f, 2.f };
	m_Arr_StrongAttackDamage[2] = { 1.f, 2.f, 3.f };
	m_Arr_StrongAttackDamage[3] = { 2.f, 2.f, 3.f };

	m_fSubAttackDamage = 1.f;
	//

	return S_OK;
}

HRESULT CPlayerWeapon_Sword::SetUp_Collider()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider), (CComponent**)&m_pCollider));

	// Main Collider
	COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(3.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1);
	FAILED_CHECK(m_pCollider->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	ATTACHEDESC tAttachedDesc;
	tAttachedDesc.Initialize_AttachedDesc(m_tPlayerWeaponDesc.pOwner, "skd_l_palm", _float3(1), _float3(0), _float3(62.9406f, -0.55441f, -114.675f));

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1);
	FAILED_CHECK(m_pCollider->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(m_tPlayerWeaponDesc.pOwner, "skd_l_palm", _float3(1), _float3(0), _float3(62.9406f, -0.55441f, -114.675f));
	m_pCollider->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1);
	FAILED_CHECK(m_pCollider->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(m_tPlayerWeaponDesc.pOwner, "skd_l_palm", _float3(1), _float3(0), _float3(62.9406f, -0.55441f, -114.675f));
	m_pCollider->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1);
	FAILED_CHECK(m_pCollider->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(m_tPlayerWeaponDesc.pOwner, "skd_l_palm", _float3(1), _float3(0), _float3(62.9406f, -0.55441f, -114.675f));
	m_pCollider->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1);
	FAILED_CHECK(m_pCollider->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(m_tPlayerWeaponDesc.pOwner, "skd_l_palm", _float3(1), _float3(0), _float3(62.9406f, -0.55441f, -114.675f));
	m_pCollider->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1);
	FAILED_CHECK(m_pCollider->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(m_tPlayerWeaponDesc.pOwner, "skd_l_palm", _float3(1), _float3(0), _float3(62.9406f, -0.55441f, -114.675f));
	m_pCollider->Set_ParantBuffer();
	//


	// Main Attack Combo3 Collider
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider_1), (CComponent**)&m_pCollider_MainAttack_Combo3));

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(5.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1);
	FAILED_CHECK(m_pCollider_MainAttack_Combo3->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(2.5f, 3.5f, 4.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 1.75f, 0.f, 1);
	FAILED_CHECK(m_pCollider_MainAttack_Combo3->Add_ColliderBuffer(COLLIDER_OBB, &ColliderDesc));
	m_pCollider_MainAttack_Combo3->Set_ParantBuffer();
	//


	// Power Attack Combo3 Collider
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider_2), (CComponent**)&m_pCollider_PowerAttack_Combo3));

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(2.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 1.f, 1);
	FAILED_CHECK(m_pCollider_PowerAttack_Combo3->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(2.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 1.f, 1);
	FAILED_CHECK(m_pCollider_PowerAttack_Combo3->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pCollider_PowerAttack_Combo3->Set_ParantBuffer();
	//


	// Ultimate Attack Collider
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider_3), (CComponent**)&m_pCollider_Ultimate));

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(12.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 1.f, 1);
	FAILED_CHECK(m_pCollider_Ultimate->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(11.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 1.f, 1);
	FAILED_CHECK(m_pCollider_Ultimate->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pCollider_Ultimate->Set_ParantBuffer();
	//
	return S_OK;
}

void CPlayerWeapon_Sword::Update_Colliders()
{
	_Matrix mat = m_pTransformCom->Get_WorldMatrix() * m_tPlayerWeaponDesc.eAttachedDesc.Caculate_AttachedBoneMatrix();
	mat.r[0] = XMVector3Normalize(mat.r[0]);
	mat.r[1] = XMVector3Normalize(mat.r[1]);
	mat.r[2] = XMVector3Normalize(mat.r[2]);
	_Vector vPos = mat.r[3];

	m_pCollider->Update_Transform(0, mat);


	mat.r[3] = vPos + mat.r[2] * 0.9f - mat.r[0] * 0.1f + mat.r[1] * 0.02f;
	m_pCollider->Update_Transform(2, mat);

	mat.r[3] = vPos + mat.r[2] * 0.7f - mat.r[0] * 0.05f + mat.r[1] * 0.02f;
	m_pCollider->Update_Transform(3, mat);
		
	mat.r[3] = vPos + mat.r[2] * 0.5f - mat.r[0] * 0.02f + mat.r[1] * 0.02f;
	m_pCollider->Update_Transform(4, mat);

	mat.r[3] = vPos + mat.r[2] * 0.3f - mat.r[0] * 0.0f + mat.r[1] * 0.02f;
	m_pCollider->Update_Transform(5, mat);


	mat.r[3] = vPos + mat.r[2] * 1.15f - mat.r[0] * 0.23f + mat.r[1] * 0.05f;
	if (true == m_bShieldBashAttack)
	{
		mat.r[0] *= 20.f / 3.f;
		mat.r[1] *= 20.f / 3.f;
		mat.r[2] *= 20.f / 3.f;
	}

	m_pCollider->Update_Transform(1, mat);
}

void CPlayerWeapon_Sword::Update_Colliders_MainAttackCombo3()
{
	CTransform* pPlayerTransform = static_cast<CTransform*>(m_tPlayerWeaponDesc.pOwner->Get_Component(TAG_COM(Com_Transform)));
	_Vector vPlayerPos = pPlayerTransform->Get_MatrixState(CTransform::TransformState::STATE_POS);
	_Vector vPlayerLook = XMVector3Normalize(pPlayerTransform->Get_MatrixState(CTransform::TransformState::STATE_LOOK));

	_Matrix mat = pPlayerTransform->Get_WorldMatrix();
	mat.r[0] = XMVector3Normalize(mat.r[0]);
	mat.r[1] = XMVector3Normalize(mat.r[1]);
	mat.r[2] = XMVector3Normalize(mat.r[2]);
	mat.r[3] = vPlayerPos + (vPlayerLook * 2.1f);

	m_pCollider_MainAttack_Combo3->Update_Transform(0, mat);
	m_pCollider_MainAttack_Combo3->Update_Transform(1, mat);
}

void CPlayerWeapon_Sword::Update_Colliders_PowerAttackCombo3()
{
	_Matrix mat = m_pMeshParticleTransform->Get_WorldMatrix();

	mat.r[0] = XMVector3Normalize(mat.r[0]);
	mat.r[1] = XMVector3Normalize(mat.r[1]);
	mat.r[2] = XMVector3Normalize(mat.r[2]);

	m_pCollider_PowerAttack_Combo3->Update_Transform(0, mat);
	m_pCollider_PowerAttack_Combo3->Update_Transform(1, mat);
}

void CPlayerWeapon_Sword::Update_Colliders_UltimateAttack()
{
	CTransform* pPlayerTransform = static_cast<CTransform*>(m_tPlayerWeaponDesc.pOwner->Get_Component(TAG_COM(Com_Transform)));
	_Vector vPlayerPos = pPlayerTransform->Get_MatrixState(CTransform::TransformState::STATE_POS);
	_Vector vPlayerLook = XMVector3Normalize(pPlayerTransform->Get_MatrixState(CTransform::TransformState::STATE_LOOK));

	_Matrix mat = pPlayerTransform->Get_WorldMatrix();
	mat.r[0] = XMVector3Normalize(mat.r[0]);
	mat.r[1] = XMVector3Normalize(mat.r[1]);
	mat.r[2] = XMVector3Normalize(mat.r[2]);
	mat.r[3] = vPlayerPos;// +(vPlayerLook * 2.1f);

	m_pCollider_Ultimate->Update_Transform(0, mat);
	m_pCollider_Ultimate->Update_Transform(1, mat);
}


HRESULT CPlayerWeapon_Sword::Ready_ParticleDesc()
{
	m_pTextureParticleTransform = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_RETURN(m_pTextureParticleTransform, E_FAIL);
	m_pMeshParticleTransform = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_RETURN(m_pMeshParticleTransform, E_FAIL);
	

	CUtilityMgr* pUtil = GetSingle(CUtilityMgr);


#pragma region Texture
	//	0
	m_vecTextureParticleDesc.push_back(pUtil->Get_TextureParticleDesc(L"Sword_Saprk"));
	m_vecTextureParticleDesc[0].FollowingTarget = m_pTextureParticleTransform;
	m_vecTextureParticleDesc[0].iFollowingDir = FollowingDir_Look;

	GetSingle(CUtilityMgr)->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[0]);

	//1
	// 
	m_vecTextureParticleDesc.push_back(pUtil->Get_TextureParticleDesc(L"JY_TextureEft_5"));
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].FollowingTarget = m_pMeshParticleTransform;
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].TotalParticleTime = 9999999999999.f;

	//m_vecTextureParticleDesc.push_back(pUtil->Get_TextureParticleDesc(L"Sword_Saprk2"));
	//m_vecTextureParticleDesc[1].FollowingTarget = m_pMeshParticleTransform;
	//m_vecTextureParticleDesc[1].iFollowingDir = FollowingDir_Up;


	//2
	// 
	m_vecTextureParticleDesc.push_back(pUtil->Get_TextureParticleDesc(L"JY_TextureEft_4"));
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].FollowingTarget = nullptr;


	//3
	m_vecTextureParticleDesc.push_back(pUtil->Get_TextureParticleDesc(L"JY_TextureEft_6"));
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].FollowingTarget = nullptr;

	//4
	m_vecTextureParticleDesc.push_back(pUtil->Get_TextureParticleDesc(L"JY_TextureEft_7"));
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].FollowingTarget = nullptr;



#pragma endregion



#pragma region Mesh
	//	GetSingle(CUtilityMgr)->Create_MeshInstance(m_eNowSceneNum, m_vecMeshParticleDesc[0]);
	m_vecMeshParticleDesc.push_back(pUtil->Get_MeshParticleDesc(L"Sword_PowerAttack"));
	
	m_vecMeshParticleDesc[0].FollowingTarget = m_pMeshParticleTransform;
	m_vecMeshParticleDesc[0].iFollowingDir = FollowingDir_Up;
	m_vecTextureParticleDesc[1].TotalParticleTime = m_vecMeshParticleDesc[0].TotalParticleTime;

#pragma endregion

	
	{
		NONINSTNESHEFTDESC tNIMEDesc;
		tNIMEDesc.eMeshType = Prototype_Mesh_Lightning_01;

		tNIMEDesc.fMaxTime_Duration = 0.5f;
		tNIMEDesc.fAppearTime = 0.15f;

		tNIMEDesc.noisingdir = _float2(0, -1);

		tNIMEDesc.NoiseTextureIndex = 381;
		tNIMEDesc.MaskTextureIndex = 109;
		tNIMEDesc.iDiffuseTextureIndex = 273;
		tNIMEDesc.m_iPassIndex = 19;
		tNIMEDesc.vEmissive = _float4(1, 0.5f, 1.f, 0);
		tNIMEDesc.vLimLight = _float4(1, 1, 0.2f, 1);
		tNIMEDesc.vColor = _float3(1.f, 0, 0);

		tNIMEDesc.RotAxis = FollowingDir_Up;
		tNIMEDesc.RotationSpeedPerSec = 0.f;
		tNIMEDesc.vSize = _float3(0.1f, 0.1f, -0.2f);

		tNIMEDesc.fAlphaTestValue = 1.f;
		m_vecNonInstMeshDesc.push_back(tNIMEDesc);
	}

	return S_OK;
}


CPlayerWeapon_Sword * CPlayerWeapon_Sword::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CPlayerWeapon_Sword*	pInstance = NEW CPlayerWeapon_Sword(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CPlayerWeapon_Sword");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CPlayerWeapon_Sword::Clone(void * pArg)
{
	CPlayerWeapon_Sword*	pInstance = NEW CPlayerWeapon_Sword(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CPlayerWeapon_Sword");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayerWeapon_Sword::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
	Safe_Release(m_pSwordTrail);
	Safe_Release(m_pCollider);
	Safe_Release(m_pDissolveCom);
	Safe_Release(m_pTextureParticleTransform);
	Safe_Release(m_pMeshParticleTransform);
	Safe_Release(m_pCollider_MainAttack_Combo3);
	Safe_Release(m_pCollider_Ultimate);
	Safe_Release(m_pCollider_PowerAttack_Combo3);
}
