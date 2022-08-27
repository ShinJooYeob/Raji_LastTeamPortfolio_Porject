#include "stdafx.h"
#include "..\public\Monster_Ninjasura.h"
#include "Monster_Bullet_Universal.h"
#include "HpUI.h"

CMonster_Ninjasura::CMonster_Ninjasura(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CMonster(pDevice, pDeviceContext)
{
}

CMonster_Ninjasura::CMonster_Ninjasura(const CMonster_Ninjasura & rhs)
	: CMonster(rhs)
{
}

HRESULT CMonster_Ninjasura::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CMonster_Ninjasura::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	if (pArg != nullptr)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, *((_float3*)pArg));

	m_pTransformCom->Rotation_CW(XMVectorSet(0, 1, 0, 0), XMConvertToRadians(170));


	SetUp_Info();


#ifdef _DEBUG
	//////////////////testPosition
	//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(493.f, 7.100010f, 103.571f)); // Stage2
	//m_pNavigationCom->FindCellIndex(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
	//////////////////////////////
#endif
	// Particle
	 Set_DealyDIssolveTime(2.5f);
	return S_OK;
}

_int CMonster_Ninjasura::Update(_double dDeltaTime)
{

	if (__super::Update(dDeltaTime) < 0)return -1;
	if (__super::Update(dDeltaTime) == UPDATE_SKIP)
		return UPDATE_SKIP;
	if (m_fHP <= 0)
	{
		m_bRepelOff = true;
		m_bLookAtOn = false;
		m_pDissolve->Update_Dissolving(dDeltaTime);
		m_pDissolve->Set_DissolveOn(false, 2.f);

		m_dDissolveTime += dDeltaTime;

		m_bMotionTrailOn = false;
		if (m_bDieSound == false && m_dDissolveTime >= 1.)
		{
			g_pGameInstance->Play3D_Sound(TEXT("EH_Ninja_Hit_Vox_04.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
			m_bDieSound = true;
		}
		if (m_dDissolveTime >= 2)
		{
			Set_IsDead();
		}
	}

	//������ ������ bBlockAnimUntilReturnChange���� true�� �����ؼ� �����۵��� �ȴٸ� false�� �ȴ�.
	//m_pModel->Change_AnimIndex();
	//m_pModel->Change_AnimIndex_ReturnTo(); //� �ִϸ��̼��� ������ Ư�� �ִϸ��̼����� ����
	//m_pModel->Change_AnimIndex_ReturnTo_Must(); //�߰��� �ִϸ��̼��� ĵ���ϰ� �ٸ� �ִϸ��̼��� ���۽�Ŵ
	//m_pModel->Change_AnimIndex_UntilTo(); //1~5���� �����ٰ� ��ɾ �Է��ϸ� 1~5���� ���ư�
	//m_pModel->Change_AnimIndex_UntilNReturn();//1~5���� ������ �� ���� Ư�� �ִϸ��̼����� Return ��ų ���
	//m_pModel->Change_AnimIndex_UntilNReturn_Must(); //1~5���� ������ �� ���� Ư�� �ִϸ��̼����� Return ��ų �� ������ �ٸ� �ִϸ��̼��� ���۽�ų �� ����



	PlayAnim(dDeltaTime);

	m_bIsOnScreen = g_pGameInstance->IsNeedToRender(m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS), m_fFrustumRadius);
	if (m_fHP > 0)
	{
		FAILED_CHECK(m_pModel->Update_AnimationClip(dDeltaTime * m_dAcceleration, m_bIsOnScreen));
	}
	FAILED_CHECK(Adjust_AnimMovedTransform(dDeltaTime));

	//////////////Motion Test
	m_pMotionTrail->Update_MotionTrail(dDeltaTime);
	/////////////////////////

	if (m_pHPUI != nullptr && m_bMotionTrailOn == false)
		m_pHPUI->Update(dDeltaTime);

	Update_Collider(dDeltaTime);

	return _int();
}

_int CMonster_Ninjasura::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;
	if (__super::LateUpdate(dDeltaTime) == UPDATE_SKIP)
		return UPDATE_SKIP;
	//////////
	if (m_bIsOnScreen && false == m_bMotionTrailOn)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}
	//////////////Motion Test
	FAILED_CHECK(m_pRendererCom->Add_TrailGroup(CRenderer::TRAIL_MOTION, m_pMotionTrail));
	////////////////

	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this, m_pTransformCom, m_pShaderCom, m_pModel));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

#ifdef _DEBUG
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pAttackColliderCom));
#endif

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));

	if (m_SpawnDealytime <= 0 && m_bIsSpawnDissolove == false)
	{
		m_pDissolve->Set_DissolveOn(true, m_SpawnDissolveTime);
		m_pDissolve->Update_Dissolving(dDeltaTime);

		if (m_pDissolve->Get_IsDissolving() == false)
			m_bIsSpawnDissolove = true;
	}

	if (m_pHPUI != nullptr && m_bMotionTrailOn == false)
	{
		m_pHPUI->LateUpdate(dDeltaTime);
	}

	return _int();
}

_int CMonster_Ninjasura::Render()
{
	if (__super::Render() < 0)
		return -1;
	if (__super::Render() == UPDATE_SKIP)
		return UPDATE_SKIP;
	NULL_CHECK_RETURN(m_pModel, E_FAIL);

	CGameInstance* pInstance = GetSingle(CGameInstance);
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_VIEW), sizeof(_float4x4)));
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_PROJ), sizeof(_float4x4)));


	FAILED_CHECK(m_pTransformCom->Bind_OnShader(m_pShaderCom, "g_WorldMatrix"));

	FAILED_CHECK(m_pDissolve->Render(3)); //������ ���ο��� ���� ���׸����� ã���ְ� ����

	//_uint NumMaterial = m_pModel->Get_NumMaterial();

	//for (_uint i = 0; i < NumMaterial; i++)
	//{
	//	for (_uint j = 0; j < AI_TEXTURE_TYPE_MAX; j++)
	//		FAILED_CHECK(m_pModel->Bind_OnShader(m_pShaderCom, i, j, MODLETEXTYPE(j)));
	//	FAILED_CHECK(m_pModel->Render(m_pShaderCom, 3, i, "g_BoneMatrices"));
	//}



	return _int();
}

_int CMonster_Ninjasura::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;
	if (__super::LateRender() == UPDATE_SKIP)
		return UPDATE_SKIP;
	return _int();
}

void CMonster_Ninjasura::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	if (CollisionTypeID::CollisionType_Player == eConflictedObjCollisionType)
	{
		_Vector vDamageDir = XMVector3Normalize(pConflictedCollider->Get_ColliderPosition(iConflictedObjColliderIndex).XMVector() - m_pTransformCom->Get_MatrixState(CTransform::TransformState::STATE_POS));
		pConflictedObj->Take_Damage(this, 1.f, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower);
		pConflictedCollider->Set_Conflicted(1.f);
	}
}

_float CMonster_Ninjasura::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
{
	m_pHPUI->Set_ADD_HitCount((_int)fDamageAmount);
	m_fHP += -fDamageAmount;

	m_bStopCoolTimeOn = true;
	m_bMotionTrailOn = false;

	m_bIOnceAnimSwitch = true;
	if (m_eMonster_State != Anim_State::MONSTER_ATTACK)
	{
		if (bKnockback == false)
		{
			m_bKnockbackOn = false;

			_int iRand_Num = rand() % 3;
			if (2 == iRand_Num)
			{
				m_iOncePattern = 40;
			}
		}
		else {
			m_bKnockbackOn = true;

			_int iRand_Num = rand() % 3;
			if (2 == iRand_Num)
			{
				m_iOncePattern = 40;
			}

			XMStoreFloat3(&m_fKnockbackDir, vDamageDir);
		}


		if (m_fHP < 5 && m_iBoolOnce == 0)
		{
			m_iOncePattern = 42;
			m_dOnceCoolTime = 0;
			m_dInfinity_CoolTime = 0;

			m_iBoolOnce += 1;
		}
	}

	if (0 >= m_fHP)
	{
		return -1.f;
	}

	return _float();
}


HRESULT CMonster_Ninjasura::SetUp_Info()
{

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(2.f, 0.f, 2.f));


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_pPlayerTransform = static_cast<CTransform*>(pGameInstance->Get_Commponent_By_LayerIndex(m_eNowSceneNum, TAG_LAY(Layer_Player), TAG_COM(Com_Transform)));
	m_pPlayerNavigation = static_cast<CNavigation*>(pGameInstance->Get_Commponent_By_LayerIndex(m_eNowSceneNum, TAG_LAY(Layer_Player), TAG_COM(Com_Navaigation)));

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

HRESULT CMonster_Ninjasura::SetUp_Collider()
{

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider), (CComponent**)&m_pColliderCom));
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_ColliderSub), (CComponent**)&m_pAttackColliderCom));

	/////////////////////////m_pColliderCom
	COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(3.f, 3.f, 3.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	ATTACHEDESC tAttachedDesc;
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.023774f, -1.1029f));
	m_vecAttachedDesc.push_back(tAttachedDesc);


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "head", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.01186f, -1.5361f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "pelvis", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.008054f, -0.4974f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "thigh_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.006605f, -1.0128f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();
	//////////////////////////////////////////////


	/////////////////////////////////////////////m_pAttackColliderCom
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(5.f, 5.f, 5.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.f, -0.5f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.7f, 0.7f, 0.7f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "pelvis", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.f, -0.008054f, -0.9948f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.7f, 0.7f, 0.7f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_twist_01_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.50823f, -0.094688f, -1.0442f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.7f, 0.7f, 0.7f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "sword_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.82335f, -0.24675f, -0.77251f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.7f, 0.7f, 0.7f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_twist_01_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.50823f, -0.094688f, -1.0442f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.7f, 0.7f, 0.7f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "sword_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.82335f, -0.24675f, -0.77251f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();
	/////////////////////////////////////////////

	return S_OK;
}

HRESULT CMonster_Ninjasura::SetUp_Fight(_double dDeltaTime)
{
	m_fDistance = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).Get_Distance(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));


	if (m_fDistance >= 0.3)
	{
		if (m_bLookAtOn)
		{
			//m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));


			_Vector vTarget = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));

			//m_pTransformCom->Turn_Dir(XMVector3Normalize(m_pTransformCom->Get_MatrixScale(CTransform::STATE_LOOK)*0.9 + vTarget* 0.1));
			m_pTransformCom->Turn_Dir(vTarget, 0.9f);
		}
	}


	return S_OK;
}

HRESULT CMonster_Ninjasura::Update_Collider(_double dDeltaTime)
{
	m_pColliderCom->Update_ConflictPassedTime(dDeltaTime);
	m_pAttackColliderCom->Update_ConflictPassedTime(dDeltaTime);

	//m_pColliderCom
	_uint	iNumCollider = m_pColliderCom->Get_NumColliderBuffer();
	for (_uint i = 0; i < iNumCollider; i++)
		m_pColliderCom->Update_Transform(i, m_vecAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());

	FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_Monster, this, m_pColliderCom));

	//m_pAttackColliderCom
	if (m_bColliderAttackOn == true)
	{
		iNumCollider = m_pAttackColliderCom->Get_NumColliderBuffer();
		for (_uint i = 0; i < iNumCollider; i++)
			m_pAttackColliderCom->Update_Transform(i, m_vecAttackAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());

		FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_MonsterWeapon, this, m_pAttackColliderCom));
	}

	if (m_bMotionTrailOn == false && m_bRepelOff != true)
		FAILED_CHECK(g_pGameInstance->Add_RepelGroup(m_pTransformCom, 1.5f, m_pNavigationCom));

	return S_OK;
}

HRESULT CMonster_Ninjasura::Ready_ParticleDesc()
{
	m_pTextureParticleTransform_Hand = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_Hand);

	m_pTextureParticleTransform_Leg = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_Leg);

	return S_OK;
}

HRESULT CMonster_Ninjasura::Update_Particle(_double timer)
{
	//	_Matrix mat_World = m_vecAttachedDesc[0].Caculate_AttachedBoneMatrix_BlenderFixed();
	_Matrix mat_World = m_pTransformCom->Get_WorldMatrix();
	mat_World.r[0] = XMVector3Normalize(mat_World.r[0]);
	mat_World.r[1] = XMVector3Normalize(mat_World.r[1]);
	mat_World.r[2] = XMVector3Normalize(mat_World.r[2]);

	mat_World.r[3] = m_pColliderCom->Get_ColliderPosition(2).XMVector();
	m_pTextureParticleTransform_Leg->Set_Matrix(mat_World); // Leg


	mat_World.r[3] = m_vecAttackAttachedDesc[2].Get_AttachedBoneWorldPosition();
	m_pTextureParticleTransform_Hand->Set_Matrix(mat_World); // 

	


	if (KEYDOWN(DIK_V))
	{
		//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Test, m_pTextureParticleTransform_Demo1);
		// Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash2, m_pTextureParticleTransform_Demo2);
		// Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash4, m_pPlayerTransform);

		//	_float4(0.25f, 0.18f, 1, 1),
		//	_float4(0.15f, 0.38f, 1, 1),

		{
			INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
			//	Prototype_Mesh_SM_ControlPointMatch_Square_02,
				Prototype_Mesh_SM_Box_Basic,
				0.01f,
				0.5f,
			//	_float4(0.15f, 0.38f, 1, 1),
			//	_float4(0.25f, 0.18f, 1, 1),
				_float4(0),
				_float4(0),
				1,
				_float3(1.5f),
				_float3(0.5f),
				1);

			testMesh.vPowerDirection = _float3(0, 1, 0);
			testMesh.eParticleTypeID = InstanceEffect_Fountain;
			testMesh.eInstanceCount = Prototype_ModelInstance_32;
			testMesh.TempBuffer_0.w = 270;
			testMesh.iMaskingTextureIndex = 101;
			testMesh.iNoiseTextureIndex= NONNOISE;

			testMesh.vEmissive_SBB = _float3(1, 0, 0);
			testMesh.fDistortionNoisingPushPower = 10.0f;

			testMesh.ParticleStartRandomPosMin = _float3(0);
			testMesh.ParticleStartRandomPosMax = _float3(0);
			testMesh.Particle_Power = 3;

			
				

		//	_Matrix mat = m_pTransformCom->Get_WorldMatrix();
			_Matrix mat = m_pTextureParticleTransform_Hand->Get_WorldMatrix();
			_Vector pos = mat.r[3];
			testMesh.vFixedPosition = pos;
		//	testMesh.FollowingTarget = m_pTextureParticleTransform_Hand;

		//	GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
		}


		{
			INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_Mesh_MaskApper,
				Prototype_Mesh_SM_Ninjasura_Knife,
				0.5f,
				0,
				//	_float4(0.15f, 0.38f, 1, 1),
				//	_float4(0.25f, 0.18f, 1, 1),
				_float4(0),
				_float4(0),
				0,
				_float3(3.0f),
				_float3(3.0f),
				1);

			//testMesh.vPowerDirection = _float3(0, 1, 0);
			//testMesh.eParticleTypeID = InstanceEffect_Suck;
			testMesh.eInstanceCount = Prototype_ModelInstance_4;
			//testMesh.TempBuffer_0.w = 270;
			//testMesh.iMaskingTextureIndex = 101;
			//testMesh.iNoiseTextureIndex = NONNOISE;

			//testMesh.vEmissive_SBB = _float3(1, 0, 0);
			//testMesh.fDistortionNoisingPushPower = 10.0f;

			_float Val = 1.0f;
			testMesh.ParticleStartRandomPosMin = _float3(-Val, -1.f, -Val);
			testMesh.ParticleStartRandomPosMax = _float3(Val, 1.0f, Val);
			//testMesh.Particle_Power = 3;

			testMesh.FollowingTarget = m_pTextureParticleTransform_Hand;
			testMesh.iFollowingDir = FollowingDir_Right;

			GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
		}

	}

	if (KEYDOWN(DIK_C))
	{
		{

			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_3,
				0,
				0.5f,
				_float4(1),
				_float4(1, 1, 1, 0.5f),
				0,
				_float3(0.5f),
				_float3(0.1f),
				0);
			//	testTex.eParticleTypeID = InstanceEffect_Straight;
			//	testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_16;
				//	testTex.ePassID = InstancePass_MaskingNoising_Bright;
				//	testTex.ePassID = InstancePass_MaskingNoising;


			testTex.ParticleStartRandomPosMin = _float3(0, 3, 0);
			testTex.ParticleStartRandomPosMax = _float3(0, 3, 0);
			testTex.Particle_Power = 2.0f;

			//testTex.iTextureLayerIndex = 20;
			//testTex.iMaskingTextureIndex = 74;
			//testTex.iMaskingTextureIndex = 68;
			//testTex.iNoiseTextureIndex = 350;

			//testTex.TempBuffer_1.y = 0;
			//testTex.TempBuffer_1.x = 0;

		//	testTex.m_fAlphaTestValue = 0.5f;

			testTex.FollowingTarget = m_pTransformCom;
			testTex.vPowerDirection = _float3(0, 1, 0);
			testTex.SubPowerRandomRange_RUL = _float3(-1, 3, -1);
		//	GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

		}

		{
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_2_png,
				3.f,
				0.5f,
				_float4(1),
				_float4(1, 1, 1, 0.5f),
				0,
				_float3(1.0f),
				_float3(0.3f),
				0);
			//	testTex.eParticleTypeID = InstanceEffect_Straight;
				testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_128;
				testTex.ePassID = InstancePass_BrightColor;
				//	testTex.ePassID = InstancePass_MaskingNoising;s
				// testTex.vEmissive_SBB = _float3(1, 1, 0.3f);


			testTex.ParticleStartRandomPosMin = _float3(-1,0,-1);
			testTex.ParticleStartRandomPosMax = _float3(1,0,1);
			testTex.Particle_Power = 5.0f;

			//testTex.iTextureLayerIndex = 20;
			//testTex.iMaskingTextureIndex = 74;
			//testTex.iMaskingTextureIndex = 68;
			//testTex.iNoiseTextureIndex = 350;

			//testTex.TempBuffer_1.y = 0;
			//testTex.TempBuffer_1.x = 0;

		//	testTex.m_fAlphaTestValue = 0.2f;


			testTex.FollowingTarget = m_pTransformCom;
			testTex.iFollowingDir = FollowingDir_Up;
		//	GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

		}
		{
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::JY_TextureEft_8,
				0,
				0,
				_float4(0.17f, 0.60f, 1.0f, 0.8f),
				_float4(0.15f, 0.91f, 0.66f, 0.1f),
				1,
				_float3(4.0f),
				_float3(5.0f),
				1);



			testTex.FollowingTarget = m_pTransformCom;
			testTex.iFollowingDir = FollowingDir_Up;
			GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

		}

		{
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Sunder_1,
				0,
				0,
				_float4(0.17f, 0.60f, 1.0f, 0.8f),
				_float4(0.15f, 0.91f, 0.66f, 0.1f),
				1,
				_float3(0.1f, 1, 0.1f).XMVector() * 5.0f,
				_float3(0.1f, 1, 0.1f).XMVector() * 3.f,
				0);
			//	testTex.eParticleTypeID = InstanceEffect_Straight;
			  testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_32;
			//  testTex.ePassID = InstancePass_BrightColor;
			//	testTex.ePassID = InstancePass_MaskingNoising;
			//  testTex.vEmissive_SBB = _float3(1, 1, 1);



			testTex.FollowingTarget = m_pTransformCom;
			testTex.iFollowingDir = FollowingDir_Look;
		//	GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

		}

		{
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Sunder_1,
				0,
				0,
				_float4(1),
				_float4(1, 1, 1, 0.5f),
				0,
				_float3(0.1f, 1, 0.1f).XMVector() * 10.f,
				_float3(0.1f, 1, 0.1f).XMVector() * 0.1f,
				1);
			testTex.eParticleTypeID = InstanceEffect_Straight;
			testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_16;
			//	testTex.ePassID = InstancePass_OriginColor;
			//	testTex.ePassID = InstancePass_BrightColor;
			testTex.vEmissive_SBB = _float3(0.5f,0.1f,0.1f);

			testTex.Particle_Power = -0.5f;

			testTex.iTextureLayerIndex = 29;
			testTex.ParticleStartRandomPosMin = _float3(-5, 5, -5);
			testTex.ParticleStartRandomPosMax = _float3(5, 15, 5);

		//	testTex.vPowerDirection = _float3(1, 1, 1);
		//	testTex.SubPowerRandomRange_RUL = _float3(1, 1, 1);

			//	testTex.iMaskingTextureIndex = 74;
			//	testTex.iNoiseTextureIndex = 160;
			//	testTex.TempBuffer_1.y = 0.0f;

			////	testTex.FollowingTarget = m_pTextureParticleTransform_Demo1;
			testTex.FollowingTarget = m_pTransformCom;
			testTex.iFollowingDir = FollowingDir_Up;

			//_Matrix mat = m_pTextureParticleTransform_Demo1->Get_WorldMatrix();
			//_Vector pos = mat.r[3] - mat.r[2] * 3.0f;
			//testTex.vFixedPosition = pos;


			GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);


		}



	}

	return S_OK;
}

HRESULT CMonster_Ninjasura::Play_SpawnEffect()
{
	if (m_SpawnEffectAdjust == 0)
	{
		m_SpawnEffectAdjust++;

		g_pGameInstance->Play3D_Sound(TEXT("UM_Spawn_08.ogg"),
			m_pTransformCom->Get_MatrixState(CTransform::STATE_POS),
			CHANNELID::CHANNEL_MONSTER, 1.0f);

		{
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Hit_2_DisDiffuse,
				0.8f,
				0.4f,
				_float4(1),
				_float4(1, 1, 1, 0.0f),
				1,
				_float3(0.05f, 1.2f, 0.05f),
				_float3(0.05f, 1.5f, 0.05f),
				1);
			//	testTex.eParticleTypeID = InstanceEffect_Ball;
			//	testTex.ePassID = InstancePass_OriginColor;
			//	testTex.ePassID = InstancePass_BrightColor;
			testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_32;

			testTex.vEmissive_SBB = _float3(1, 1.f, 0.5f);

			testTex.Particle_Power = 2.f;

			_float val = 0.7f;
			testTex.ParticleStartRandomPosMin = _float3(-val, 0.0f, -val);
			testTex.ParticleStartRandomPosMax = _float3(val, 2.f, val);

			testTex.vPowerDirection = _float3(1, 1, 1);
			testTex.SubPowerRandomRange_RUL = _float3(1, 1, 1);

			testTex.iTextureLayerIndex = 3;
			testTex.TempBuffer_1.y = 0.0f;

			testTex.FollowingTarget = m_pTransformCom;

			GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);
		}

	}


	if (m_SpawnEffectAdjust == 1 && m_SpawnDealytime <= 1.0f)
	{
		m_SpawnEffectAdjust++;

		g_pGameInstance->Play3D_Sound(TEXT("UM_Spawn_06_0.ogg"),
			m_pTransformCom->Get_MatrixState(CTransform::STATE_POS),
			CHANNELID::CHANNEL_MONSTER, 1.0f);

		// smoke
		{
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_2_png,
				0.05f,
				0.5f,
				_float4(1),
				_float4(1, 1, 1, 0.5f),
				0,
				_float3(0.5f),
				_float3(0.3f),
				0);
			//	testTex.eParticleTypeID = InstanceEffect_Straight;
			testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_128;
			testTex.ePassID = InstancePass_BrightColor;
			//	testTex.ePassID = InstancePass_MaskingNoising;s
			// testTex.vEmissive_SBB = _float3(1, 1, 0.3f);
			testTex.vEmissive_SBB = _float3(1, 0.5f, 0.3f);

			_float val = 0.8f;
			testTex.ParticleStartRandomPosMin = _float3(-val, 0, -val);
			testTex.ParticleStartRandomPosMax = _float3(val, 0, val);
			testTex.Particle_Power = 5.0f;

			//testTex.iTextureLayerIndex = 20;
			//testTex.iMaskingTextureIndex = 74;
			//testTex.iMaskingTextureIndex = 68;
			//testTex.iNoiseTextureIndex = 350;

			//testTex.TempBuffer_1.y = 0;
			//testTex.TempBuffer_1.x = 0;

		//	testTex.m_fAlphaTestValue = 0.2f;


			testTex.FollowingTarget = m_pTransformCom;
			testTex.iFollowingDir = FollowingDir_Up;
			GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

		}

	}

	return S_OK;
}

HRESULT CMonster_Ninjasura::PlayAnim(_double dDeltaTime)
{
	SetUp_Fight(dDeltaTime);

	CoolTime_Manager(dDeltaTime);

	if (true == m_bIOnceAnimSwitch)
	{
		Once_AnimMotion(dDeltaTime);
		_uint i = m_pModel->Get_NowAnimIndex();
		switch (i)
		{
			//case 1:
			//	m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			//	break;
			//case 2:
			//	m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			//	break;
		case 3:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			break;
		case 11:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			break;
		case 16:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			break;
		case 17:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			break;
		case 21:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.2f);
			break;
		default:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.15f);
			break;
		}
	}
	else
	{
		Infinity_AnimMotion(dDeltaTime);
		m_pModel->Change_AnimIndex(m_iInfinityAnimNumber);
	}

	return S_OK;
}

HRESULT CMonster_Ninjasura::CoolTime_Manager(_double dDeltaTime)
{
	//�ѹ��� �����ϴ� �ִϸ��̼�
	if (m_bStopCoolTimeOn == false)
	{
		m_dOnceCoolTime += dDeltaTime;
		m_dInfinity_CoolTime += dDeltaTime;
	}

	if (m_dOnceCoolTime > 2 || m_bComboAnimSwitch == true)
	{
		m_dOnceCoolTime = 0;
		m_dInfinity_CoolTime = 0;

		if (m_bIOnceAnimSwitch == false)
		{
			Pattern_Change();


			m_bIOnceAnimSwitch = true;
		}
	}

	//�ݺ������� �����ϴ� �ִϸ��̼�
	if (m_dInfinity_CoolTime >= 1.5)
	{
		//m_iInfinityPattern = rand() % 7;


		m_dInfinity_CoolTime = 0;
		m_dOnceCoolTime += 10;
	}

	return S_OK;
}

HRESULT CMonster_Ninjasura::Once_AnimMotion(_double dDeltaTime)
{
#ifdef _DEBUG
	// #DEBUG PatternSET
	// m_iOncePattern = 2;

	if (KEYPRESS(DIK_B))
		m_iOncePattern = 1;
#endif // _DEBUG

	switch (m_iOncePattern)
	{
	case 0:
		m_iOnceAnimNumber = 20;
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 1:
		m_iOnceAnimNumber = 2; //Rush Ready
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 2:
		m_iOnceAnimNumber = 3; //Rush start
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 3:
		m_iOnceAnimNumber = 11; //Attack1 Ready
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 4:
		m_iOnceAnimNumber = 12; //Attack1 Fire
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 5:
		m_iOnceAnimNumber = 20;
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 6:
		m_iOnceAnimNumber = 2; //Rush Ready
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 7:
		m_iOnceAnimNumber = 3; //Rush start
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 8:
		m_iOnceAnimNumber = 19; //throw Knife
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 9:
		m_iOnceAnimNumber = 20;
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 10:
		m_iOnceAnimNumber = 2; //Rush Ready
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 11:
		m_iOnceAnimNumber = 3; //Rush start
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 12:
		m_iOnceAnimNumber = 15; //Spinning Start
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 13:
		m_iOnceAnimNumber = 16; //Spinning Attack
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 14:
		m_iOnceAnimNumber = 17; //Spinning Attack
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 15:
		m_iOnceAnimNumber = 16; //Spinning Attack
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 16:
		m_iOnceAnimNumber = 18; //Spinning End
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 17:
		m_iOnceAnimNumber = 20;
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 18:
		m_iOnceAnimNumber = 2; //Rush Ready
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 19:
		m_iOnceAnimNumber = 3; //Rush start
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 20:
		m_iOnceAnimNumber = 13; //Attack2 Ready
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 21:
		m_iOnceAnimNumber = 14; //Attack2 Fire
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 40:
		m_iOnceAnimNumber = 5;
		m_eMonster_State = Anim_State::MONSTER_HIT;
		break;
	case 42:
		m_iOnceAnimNumber = 7;
		break;
	}

	return S_OK;
}

HRESULT CMonster_Ninjasura::Pattern_Change()
{

	m_iOncePattern += 1;

	if (m_iOncePattern >= 22)
	{
		if (m_iAfterPattern < 22)
		{
			m_iOncePattern = m_iAfterPattern;
		}
		else {
			m_iOncePattern = 0; //OncePattern Random
			m_iAfterPattern = m_iOncePattern + 1;
		}
	}


	return S_OK;
}

HRESULT CMonster_Ninjasura::Infinity_AnimMotion(_double dDeltaTime)
{
	switch (m_iInfinityPattern)
	{
	case 0:
		m_iInfinityAnimNumber = 0;
		break;
	case 1:
		m_iInfinityAnimNumber = 0;
		break;
	case 2:
		m_iInfinityAnimNumber = 0;
		break;
	case 3:
		m_iInfinityAnimNumber = 0;
		break;
	case 4:
		m_iInfinityAnimNumber = 0;
		break;
	case 5:
		m_iInfinityAnimNumber = 0;
		break;
	case 6:
		m_iInfinityAnimNumber = 0;
		break;
	default:
		m_iInfinityAnimNumber = 0;
		break;
	}

	return S_OK;
}

HRESULT CMonster_Ninjasura::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Monster_Ninjasura), TAG_COM(Com_Model), (CComponent**)&m_pModel));
	FAILED_CHECK(m_pModel->Change_AnimIndex(0));


	CTransform::TRANSFORMDESC tDesc = {};

	tDesc.fMovePerSec = 5;
	tDesc.fRotationPerSec = XMConvertToRadians(60);
	tDesc.vPivot = _float3(0, 0, 0);
	tDesc.fScalingPerSec = 1;

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));

	////////////Motion Test
	CMotionTrail::MOTIONTRAILDESC tMotionDesc;

	tMotionDesc.iNumTrailCount = 6;
	tMotionDesc.pModel = m_pModel;
	tMotionDesc.pShader = m_pShaderCom;
	tMotionDesc.iPassIndex = 5;

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_MotionTrail), TAG_COM(Com_MotionTrail), (CComponent**)&m_pMotionTrail, &tMotionDesc));
	///////////////////////////


	CHpUI::HPDesc HpDesc;
	HpDesc.m_HPType = CHpUI::HP_MONSTER;
	HpDesc.m_pObjcect = this;
	HpDesc.m_vPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);
	HpDesc.m_Dimensions = 1.5f;
	m_fMaxHP = 35.f;
	m_fHP = m_fMaxHP;
	g_pGameInstance->Add_GameObject_Out_of_Manager((CGameObject**)(&m_pHPUI), m_eNowSceneNum, TAG_OP(Prototype_Object_UI_HpUI), &HpDesc);


	CDissolve::DISSOLVEDESC DissolveDesc;
	DissolveDesc.pModel = m_pModel;
	DissolveDesc.eDissolveModelType = CDissolve::DISSOLVE_ANIM;
	DissolveDesc.pShader = m_pShaderCom;
	DissolveDesc.RampTextureIndex = 14;
	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Dissolve), TAG_COM(Com_Dissolve), (CComponent**)&m_pDissolve, &DissolveDesc));


	SetUp_Collider();

	return S_OK;
}

HRESULT CMonster_Ninjasura::Adjust_AnimMovedTransform(_double dDeltaTime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.95)
	{
		m_iAdjMovedIndex = 0;

		m_bLookAtOn = false;

		m_dAcceleration = 1;

		m_bColliderAttackOn = false;

		m_iSoundIndex = 0;
		m_bStopCoolTimeOn = false;
		m_EffectAdjust = 0;

		if (PlayRate > 0.95 && m_bIOnceAnimSwitch == true)
		{
			m_bIOnceAnimSwitch = false;
			if (m_eMonster_State != Anim_State::MONSTER_HIT)
				m_dOnceCoolTime = 0;
			m_dInfinity_CoolTime = 0;
		}
		m_eMonster_State = Anim_State::MONSTER_IDLE;
	}

	if (PlayRate <= 0.95) //�ִϸ��̼��� ���� ��, 0.98�� ���� �������� ����
	{
		switch (iNowAnimIndex)
		{
		case 2:
		{
			if (PlayRate >= 0.9)
			{
				m_bIOnceAnimSwitch = false;

				

			}

			if (m_EffectAdjust == 0 && PlayRate >= 0.1)
			{
				{
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::JY_TextureEft_8,
						0,
						0,
						_float4(0.17f, 0.60f, 1.0f, 0.8f),
						_float4(0.15f, 0.91f, 0.66f, 0.1f),
						1,
						_float3(4.0f),
						_float3(5.0f),
						1);

					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Up;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				}

				{
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Sunder_1,
						0,
						0,
						_float4(0.17f, 0.60f, 1.0f, 0.8f),
						_float4(0.15f, 0.91f, 0.66f, 0.1f),
						1,
						_float3(0.1f, 1, 0.1f).XMVector() * 5.0f,
						_float3(0.1f, 1, 0.1f).XMVector() * 3.f,
						1);
					//	testTex.eParticleTypeID = InstanceEffect_Straight;
					testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_16;
					//  testTex.ePassID = InstancePass_BrightColor;
					//	testTex.ePassID = InstancePass_MaskingNoising;
					//  testTex.vEmissive_SBB = _float3(1, 1, 1);

					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Look;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				}
				m_EffectAdjust++;

			}
			break;
		}
		case 3:
		{
			m_bLookAtOn = false;
			if (m_iAdjMovedIndex == 0)
			{
				m_iMoveNumber = rand() % 5;
				m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));

				m_bColliderAttackOn = true;

				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninjasura_DashSwoosh_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.5f);
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninja_Blade.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);

				m_iAdjMovedIndex++;
			}
			if (PlayRate <= 0.1)
			{
				m_MotionTrailTime += dDeltaTime;
				if (m_MotionTrailTime > 0.03)
				{
					m_bMotionTrailOn = true;

					CUtilityMgr* pUtil = GetSingle(CUtilityMgr);

					if (false == m_bTurnMotion)
					{
						XMStoreFloat4(&m_fDirection, XMVector3Normalize(m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK) * pUtil->RandomFloat(0, 1) + m_pTransformCom->Get_MatrixState(CTransform::STATE_RIGHT) * pUtil->RandomFloat(-1, 0)));
						m_bTurnMotion = true;
					}
					else
					{
						XMStoreFloat4(&m_fDirection, XMVector3Normalize(m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK) * pUtil->RandomFloat(0, 1) + m_pTransformCom->Get_MatrixState(CTransform::STATE_RIGHT) * pUtil->RandomFloat(0, 1)));
						m_bTurnMotion = false;
					}

					m_pMotionTrail->Add_MotionBuffer(m_pTransformCom->Get_WorldFloat4x4(), _float4(0.45f, 0.f, 1.f, 1.f), 1.f);
					m_MotionTrailTime = 0;
				}
				m_pTransformCom->MovetoDir_bySpeed(XMLoadFloat4(&m_fDirection), 60.f, dDeltaTime, m_pNavigationCom);
			}
			else
			{
				if (m_iAfterPattern != 3 && m_iAfterPattern != 20) ////////////����3�϶� �Ϻη� �ȳ����� �ϱ� ���� ����ó��!@#!#$@!#$!@$!@$
				{
					m_bIOnceAnimSwitch = false;
					m_bMotionTrailOn = false;
				}
			}

			if (m_EffectAdjust == 0)
			{
				{

				INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Sunder_1,
					0,
					0,
					_float4(1),
					_float4(1, 1, 1, 0.5f),
					0,
					_float3(0.1f, 1, 0.1f).XMVector() * 10.f,
					_float3(0.1f, 1, 0.1f).XMVector() * 0.1f,
					1);
				testTex.eParticleTypeID = InstanceEffect_Straight;
				testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_16;
				//	testTex.ePassID = InstancePass_OriginColor;
				//	testTex.ePassID = InstancePass_BrightColor;
				testTex.vEmissive_SBB = _float3(0.5f, 0.1f, 0.1f);

				testTex.Particle_Power = -0.5f;

				testTex.iTextureLayerIndex = 29;
				testTex.ParticleStartRandomPosMin = _float3(-5, 5, -5);
				testTex.ParticleStartRandomPosMax = _float3(5, 15, 5);

				//	testTex.vPowerDirection = _float3(1, 1, 1);
				//	testTex.SubPowerRandomRange_RUL = _float3(1, 1, 1);

					//	testTex.iMaskingTextureIndex = 74;
					//	testTex.iNoiseTextureIndex = 160;
					//	testTex.TempBuffer_1.y = 0.0f;

					////	testTex.FollowingTarget = m_pTextureParticleTransform_Demo1;
				testTex.FollowingTarget = m_pTransformCom;
				testTex.iFollowingDir = FollowingDir_Up;

				//_Matrix mat = m_pTextureParticleTransform_Demo1->Get_WorldMatrix();
				//_Vector pos = mat.r[3] - mat.r[2] * 3.0f;
				//testTex.vFixedPosition = pos;


				GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);
				}
				m_EffectAdjust++;
			}

			break;
		}
		case 4:
		{
			m_bLookAtOn = false;

			if (m_iAdjMovedIndex == 0)
			{
				m_iMoveNumber = rand() % 2;

				m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));

				m_iAdjMovedIndex++;
			}
			if (PlayRate <= 0.1)
			{

				switch (m_iMoveNumber)
				{
				case 0:
					m_pTransformCom->Move_Right(dDeltaTime * 4, m_pNavigationCom);
					break;
				case 1:
					m_pTransformCom->Move_Left(dDeltaTime * 4, m_pNavigationCom);
					break;
				default:
					break;
				}
			}
			break;
		}
		case 5:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0 && m_bKnockbackOn == false)
			{
				m_dAcceleration = 0.7;
				m_iAdjMovedIndex++;

				if (m_iSoundIndex == 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Ninja_Hit_Vox_03.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					m_iSoundIndex++;
				}
			}
			if (m_bKnockbackOn == true)
			{
				if (m_iAdjMovedIndex == 0 && PlayRate > 0)
				{
					m_bLookAtOn = false;
					m_dAcceleration = 0.7;
					m_iAdjMovedIndex++;


					if (m_iSoundIndex == 0)
					{
						g_pGameInstance->Play3D_Sound(TEXT("EH_Ninja_Grunt_Vox_03.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
						m_iSoundIndex++;
					}
				}
				else if (0.f < PlayRate && PlayRate <= 0.6428)
				{
					if (PlayRate >= 0 && PlayRate <= 0.6428)
						m_pTransformCom->Move_Backward(dDeltaTime* 0.5, m_pNavigationCom);

					m_fKnockbackDir.y = 0;

					m_pTransformCom->Turn_Dir(m_fKnockbackDir.XMVector(), 0.9f);
				}
			}
			break;
		}
		case 11:
		{
			m_bMotionTrailOn = true;
			if (PlayRate <= 0.75)
			{
				m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));

				m_MotionTrailTime += dDeltaTime;
				if (m_MotionTrailTime > 0.1)
				{
					m_pMotionTrail->Add_MotionBuffer(m_pTransformCom->Get_WorldFloat4x4(), _float4(0.45f, 0.f, 1.f, 1.f), 1.f);
					m_MotionTrailTime = 0;
				}
			}

			if (m_EffectAdjust == 0 && PlayRate >= 0.2)
			{

				{
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::JY_TextureEft_8,
						0,
						0,
						_float4(0.73f, 0.39f, 0.88f, 0.8f),
						_float4(0.39f, 0.88f, 0.73f, 0.3f),
						1,
						_float3(4.0f),
						_float3(5.0f),
						1);



					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Up;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				}


				{
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Sunder_1,
						0,
						0,
						_float4(0.73f, 0.39f, 0.88f, 1.0f),
						_float4(0.39f, 0.88f, 0.73f, 1.0f),
						3,
						_float3(0.1f, 1, 0.1f).XMVector() * 5.0f,
						_float3(0.1f, 1, 0.1f).XMVector() * 3.f,
						1);
					testTex.vEmissive_SBB = _float3(1, 0.5f, 1);


					//	testTex.eParticleTypeID = InstanceEffect_Straight;
					testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_32;
					testTex.ePassID = InstancePass_OriginColor;

					//  testTex.ePassID = InstancePass_BrightColor;
					//	testTex.ePassID = InstancePass_MaskingNoising;
					//  testTex.vEmissive_SBB = _float3(1, 1, 1);

					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Look;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				}

		

				m_EffectAdjust++;
			}
			break;
		}
		case 12:
		{
			m_bColliderAttackOn = true;
			m_bLookAtOn = false;
			if (PlayRate <= 0.20)
			{
				m_MotionTrailTime += dDeltaTime;
				if (m_MotionTrailTime > 0.05)
				{
					m_pMotionTrail->Add_MotionBuffer(m_pTransformCom->Get_WorldFloat4x4(), _float4(0.45f, 0.f, 1.f, 1.f), 1.f);
					m_MotionTrailTime = 0;
				}

				m_pTransformCom->Move_Forward(dDeltaTime * 10, m_pNavigationCom);
			}
			else
			{
				m_bMotionTrailOn = false;
				if (m_iAdjMovedIndex == 0)
				{
					m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));
					m_iAdjMovedIndex++;
				}
			}
			if (m_iSoundIndex == 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninjasura_DashSwoosh_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.5f);
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninjasura_Sword_Sheath_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);
				m_iSoundIndex++;
			}

			if (m_EffectAdjust == 0)
			{
				{

					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Sunder_1,
						0,
						0,
						_float4(1),
						_float4(1, 1, 1, 0.5f),
						0,
						_float3(0.1f, 1, 0.1f).XMVector() * 10.f,
						_float3(0.1f, 1, 0.1f).XMVector() * 0.1f,
						1);
					testTex.eParticleTypeID = InstanceEffect_Straight;
					testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_16;
					//	testTex.ePassID = InstancePass_OriginColor;
					//	testTex.ePassID = InstancePass_BrightColor;
					testTex.vEmissive_SBB = _float3(0.5f, 0.1f, 0.1f);

					testTex.Particle_Power = -0.5f;

					testTex.iTextureLayerIndex = 29;
					testTex.ParticleStartRandomPosMin = _float3(-5, 5, -5);
					testTex.ParticleStartRandomPosMax = _float3(5, 15, 5);

					//	testTex.vPowerDirection = _float3(1, 1, 1);
					//	testTex.SubPowerRandomRange_RUL = _float3(1, 1, 1);

						//	testTex.iMaskingTextureIndex = 74;
						//	testTex.iNoiseTextureIndex = 160;
						//	testTex.TempBuffer_1.y = 0.0f;

						////	testTex.FollowingTarget = m_pTextureParticleTransform_Demo1;
					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Up;

					//_Matrix mat = m_pTextureParticleTransform_Demo1->Get_WorldMatrix();
					//_Vector pos = mat.r[3] - mat.r[2] * 3.0f;
					//testTex.vFixedPosition = pos;


					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);
				}
				m_EffectAdjust++;
			}

			break;
		}
		case 13:
		{
			if (PlayRate <= 0.83333)
			{
				m_bMotionTrailOn = true;
				m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));

				m_MotionTrailTime += dDeltaTime;
				if (m_MotionTrailTime > 0.1)
				{
					m_pMotionTrail->Add_MotionBuffer(m_pTransformCom->Get_WorldFloat4x4(), _float4(0.45f, 0.f, 1.f, 1.f), 1.f);
					m_MotionTrailTime = 0;
				}
			}

			if (m_EffectAdjust == 0)
			{
				{
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::JY_TextureEft_8,
						0,
						0,
						_float4(0.73f, 0.39f, 0.88f, 0.8f),
						_float4(0.39f, 0.88f, 0.73f, 0.3f),
						1,
						_float3(4.0f),
						_float3(5.0f),
						1);



					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Up;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				}


				{
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Sunder_1,
						0,
						0,
						_float4(0.73f, 0.39f, 0.88f, 1.0f),
						_float4(0.39f, 0.88f, 0.73f, 1.0f),
						3,
						_float3(0.1f, 1, 0.1f).XMVector() * 5.0f,
						_float3(0.1f, 1, 0.1f).XMVector() * 3.f,
						1);
					testTex.vEmissive_SBB = _float3(1, 0.5f, 1);


					//	testTex.eParticleTypeID = InstanceEffect_Straight;
					testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_32;
					testTex.ePassID = InstancePass_OriginColor;

					//  testTex.ePassID = InstancePass_BrightColor;
					//	testTex.ePassID = InstancePass_MaskingNoising;
					//  testTex.vEmissive_SBB = _float3(1, 1, 1);

					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Look;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				}



				m_EffectAdjust++;

			}
			break;
		}
		case 14:
		{
			m_bColliderAttackOn = true;
			m_bLookAtOn = false;
			if (PlayRate <= 0.20)
			{
				m_MotionTrailTime += dDeltaTime;
				if (m_MotionTrailTime > 0.05)
				{
					m_pMotionTrail->Add_MotionBuffer(m_pTransformCom->Get_WorldFloat4x4(), _float4(0.45f, 0.f, 1.f, 1.f), 1.f);
					m_MotionTrailTime = 0;
				}

				m_pTransformCom->Move_Forward(dDeltaTime * 5, m_pNavigationCom);
			}
			else
			{
				m_bMotionTrailOn = false;
				if (m_iAdjMovedIndex == 0)
				{
					m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));
					m_iAdjMovedIndex++;
				}
			}
			if (m_iSoundIndex == 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninjasura_DashSwoosh_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.5f);
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninjasura_Sword_Sheath_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);
				m_iSoundIndex++;
			}

			if (m_EffectAdjust == 0)
			{
				{

					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Sunder_1,
						0,
						0,
						_float4(1),
						_float4(1, 1, 1, 0.5f),
						0,
						_float3(0.1f, 1, 0.1f).XMVector() * 10.f,
						_float3(0.1f, 1, 0.1f).XMVector() * 0.1f,
						1);
					testTex.eParticleTypeID = InstanceEffect_Straight;
					testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_16;
					//	testTex.ePassID = InstancePass_OriginColor;
					//	testTex.ePassID = InstancePass_BrightColor;
					testTex.vEmissive_SBB = _float3(0.5f, 0.1f, 0.1f);

					testTex.Particle_Power = -0.5f;

					testTex.iTextureLayerIndex = 29;
					testTex.ParticleStartRandomPosMin = _float3(-5, 5, -5);
					testTex.ParticleStartRandomPosMax = _float3(5, 15, 5);

					//	testTex.vPowerDirection = _float3(1, 1, 1);
					//	testTex.SubPowerRandomRange_RUL = _float3(1, 1, 1);

						//	testTex.iMaskingTextureIndex = 74;
						//	testTex.iNoiseTextureIndex = 160;
						//	testTex.TempBuffer_1.y = 0.0f;

						////	testTex.FollowingTarget = m_pTextureParticleTransform_Demo1;
					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Up;

					//_Matrix mat = m_pTextureParticleTransform_Demo1->Get_WorldMatrix();
					//_Vector pos = mat.r[3] - mat.r[2] * 3.0f;
					//testTex.vFixedPosition = pos;


					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);
				}
				m_EffectAdjust++;
			}


			break;
		}
		case 16:
		{

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			m_bColliderAttackOn = true;
			//m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));
			_Vector vTarget = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
			m_pTransformCom->Turn_Dir(vTarget, 0.7f);

			if (PlayRate > 0 && PlayRate <= 0.95)
			{
				_float fSpeed = g_pGameInstance->Easing_Return(TYPE_SinInOut, TYPE_SinInOut, 0, 2.852698f, (_float)PlayRate, 0.95f); // PlayRate - 0.266666 and 0.5 - 0.266666
				m_pTransformCom->Move_Forward(dDeltaTime * fSpeed, m_pNavigationCom);
				m_dAcceleration = 0.8;
			}
			if (m_iSoundIndex == 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninjasura_Spin_Attack_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);
				m_iSoundIndex++;
			}
			if (m_EffectAdjust == 0)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash0, m_pTextureParticleTransform_Hand);
				m_EffectAdjust++;
			}
			break;
		}
		case 17:
		{

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(0.0f, 0.0f, 1.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			m_bColliderAttackOn = true;
			//m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));
			_Vector vTarget = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
			m_pTransformCom->Turn_Dir(vTarget, 0.7f);

			if (PlayRate > 0 && PlayRate <= 0.95)
			{
				_float fSpeed = g_pGameInstance->Easing_Return(TYPE_SinInOut, TYPE_SinInOut, 0, 2.852698f, (_float)PlayRate, 0.95f); // PlayRate - 0.266666 and 0.5 - 0.266666
				m_pTransformCom->Move_Forward(dDeltaTime * fSpeed, m_pNavigationCom);
				m_dAcceleration = 0.8;
			}
			if (m_iSoundIndex == 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninjasura_Spin_Attack_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);
				m_iSoundIndex++;
			}

			if (m_EffectAdjust == 0)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash0, m_pTextureParticleTransform_Hand);
				m_EffectAdjust++;
			}
			break;
		}
		case 18:
		{

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(0.0f, 1.0f, 0.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_iSoundIndex == 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninjasura_Spin_Attack_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);
				m_iSoundIndex++;
			}

			break;
		}
		case 19:
		{
			if (PlayRate > 0)
			{
				_Vector vTarget = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));

				m_pTransformCom->Turn_Dir(vTarget, 0.9f);
			}
			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.60714)
			{

				CMonster_Bullet_Universal::MONSTER_BULLET_UNIVERSALDESC Monster_BulletDesc;

				Monster_BulletDesc.iBulletMeshNumber = CMonster_Bullet_Universal::NINJASURA_KNIFE;
				Monster_BulletDesc.fSpeedPerSec = 15.f;
				Monster_BulletDesc.fScale = _float3(0.9f);
				//	Monster_BulletDesc.fScale = _float3(0.01f);

				Monster_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_BulletDesc.fPositioning = _float3(0.5f, 3.f, 1.5f); //������ ���� �ٲٸ� ���� fPos.y�� �ٲ������


				Monster_BulletDesc.Object = this;

				Monster_BulletDesc.dDuration = 10;

				Monster_BulletDesc.bBornAttachOn = true;
				Monster_BulletDesc.pBoneName = "lowerarm_twist_01_r";


				_float3 fPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

				fPos.y += 3.f;


				_Vector vLook = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - XMLoadFloat3(&fPos));

				CGameObject* ShurkenObj = nullptr;
				CTransform* ShurkenTrans = nullptr;

				// smoke
				INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_3,
					10.0f,
					0.4f,
					_float4(1, 1, 1, 0.6f),
					_float4(1, 1, 1, 0.3f),
					1,
					_float3(2.0f),
					_float3(0.1f),
					1);
				//	testTex.eParticleTypeID = InstanceEffect_Straight;
				testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_16;
				//	testTex.ePassID = InstancePass_MaskingNoising_Bright;
				//	testTex.ePassID = InstancePass_MaskingNoising;

				testTex.ParticleStartRandomPosMin = _float3(0, 0, 0);
				testTex.ParticleStartRandomPosMax = _float3(0, 0.5f, 0);

				testTex.Particle_Power = 5.0f;

				//testTex.iTextureLayerIndex = 20;
				testTex.iMaskingTextureIndex = 74;
				//testTex.iMaskingTextureIndex = 68;
				testTex.iNoiseTextureIndex = 350;

				testTex.vEmissive_SBB = _float3(1.0f, 0.5f, 0.5f);
				testTex.m_fAlphaTestValue = 0.5f;
				testTex.vPowerDirection = _float3(0, 1, 0);
				testTex.SubPowerRandomRange_RUL = _float3(-1, 3, -1);


				XMStoreFloat3(&Monster_BulletDesc.fLook, XMVector3Normalize(vLook * 0.85f + m_pTransformCom->Get_MatrixState(CTransform::STATE_RIGHT) * -0.15f));
				ShurkenObj = (g_pGameInstance->Add_GameObject_GetObject(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Bullet_Universal), &Monster_BulletDesc));
				ShurkenTrans = static_cast<CTransform*>(ShurkenObj->Get_Component(TAG_COM(Com_Transform)));
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash2, ShurkenTrans);



				XMStoreFloat3(&Monster_BulletDesc.fLook, XMVector3Normalize(vLook * 1.f + m_pTransformCom->Get_MatrixState(CTransform::STATE_RIGHT) * 0.f));
				ShurkenObj = (g_pGameInstance->Add_GameObject_GetObject(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Bullet_Universal), &Monster_BulletDesc));
				ShurkenTrans = static_cast<CTransform*>(ShurkenObj->Get_Component(TAG_COM(Com_Transform)));
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash2, ShurkenTrans);
				testTex.FollowingTarget = ShurkenTrans;
				// testTex.iFollowingDir;
				GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				XMStoreFloat3(&Monster_BulletDesc.fLook, XMVector3Normalize(vLook * 0.85f + m_pTransformCom->Get_MatrixState(CTransform::STATE_RIGHT) * 0.15f));
				ShurkenObj = (g_pGameInstance->Add_GameObject_GetObject(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Bullet_Universal), &Monster_BulletDesc));
				ShurkenTrans = static_cast<CTransform*>(ShurkenObj->Get_Component(TAG_COM(Com_Transform)));
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash2, ShurkenTrans);

				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninja_Moon_Throw.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);

				m_iAdjMovedIndex++;
			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.3157)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Ninja_Grunt_Vox_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);

				m_iSoundIndex++;
			}

			if (m_EffectAdjust == 0 && PlayRate >= 0.3157)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash1, m_pTransformCom);
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_NL_Cash3, m_pTextureParticleTransform_Hand);

				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 1 && PlayRate >= 0.3)
			{
				{
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_3,
						1.0f,
						0.5f,
						_float4(1),
						_float4(1, 1, 1, 0.5f),
						0,
						_float3(0.6f),
						_float3(0.1f),
						1);
					//	testTex.eParticleTypeID = InstanceEffect_Ball;
					testTex.ePassID = InstancePass_MaskingNoising;
					testTex.ePassID = InstancePass_MaskingNoising_Bright;


					testTex.ParticleStartRandomPosMin = _float3(0, 0, 0);
					testTex.ParticleStartRandomPosMax = _float3(0, 0, 0);

					testTex.iTextureLayerIndex = 20;
					testTex.iMaskingTextureIndex = 74;
					testTex.iMaskingTextureIndex = 68;
					testTex.iNoiseTextureIndex = 350;
					testTex.TempBuffer_1.y = 0;

					// _Matrix mat = m_pTextureParticleTransform_Hand->Get_WorldMatrix();
					// _Vector pos = mat.r[3] - mat.r[2] * 0;
					// testTex.vFixedPosition = pos;

					testTex.m_fAlphaTestValue = 0.5f;
					testTex.FollowingTarget = m_pTextureParticleTransform_Hand;


					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);
				}

				m_EffectAdjust++;
			}

			break;
		}
		case 20:
		{
			m_dSoundTime += dDeltaTime;

			if (PlayRate >= 0.35714 && PlayRate <= 0.76785)
			{
				m_bLookAtOn = true;
				if (m_dSoundTime >= 0.2)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Vayusura_Secondary_Wing_Flap_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);
					m_dSoundTime = 0;
				}
			}
			else
			{
				m_bLookAtOn = false;
			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.2417)
			{

				g_pGameInstance->Play3D_Sound(TEXT("EH_M1_2215.mp3"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 1.f);

				m_iSoundIndex++;
			}


			if (m_EffectAdjust == 0 && PlayRate >= 0.2417)
			{
				{
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_2_png,
						2.5f,
						0.5f,
						_float4(1),
						_float4(1, 1, 1, 0.5f),
						0,
						_float3(1.0f),
						_float3(0.3f),
						0);
					//	testTex.eParticleTypeID = InstanceEffect_Straight;
					testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_128;
					testTex.ePassID = InstancePass_BrightColor;
					//	testTex.ePassID = InstancePass_MaskingNoising;s
					// testTex.vEmissive_SBB = _float3(1, 1, 0.3f);
					 testTex.vEmissive_SBB = _float3(1, 0.5f, 0.3f);


					testTex.ParticleStartRandomPosMin = _float3(-1, 0, -1);
					testTex.ParticleStartRandomPosMax = _float3(1, 0, 1);
					testTex.Particle_Power = 5.0f;

					//testTex.iTextureLayerIndex = 20;
					//testTex.iMaskingTextureIndex = 74;
					//testTex.iMaskingTextureIndex = 68;
					//testTex.iNoiseTextureIndex = 350;

					//testTex.TempBuffer_1.y = 0;
					//testTex.TempBuffer_1.x = 0;

				//	testTex.m_fAlphaTestValue = 0.2f;


					testTex.FollowingTarget = m_pTransformCom;
					testTex.iFollowingDir = FollowingDir_Up;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

					m_EffectAdjust++;
				}
			}
		}
		}

	}

	m_iOldAnimIndex = iNowAnimIndex;
	return S_OK;
}

CMonster_Ninjasura * CMonster_Ninjasura::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CMonster_Ninjasura*	pInstance = NEW CMonster_Ninjasura(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Ninjasura");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMonster_Ninjasura::Clone(void * pArg)
{
	CMonster_Ninjasura*	pInstance = NEW CMonster_Ninjasura(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Ninjasura");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonster_Ninjasura::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
	////////////Motion Test
	Safe_Release(m_pMotionTrail);
	////////////
	Safe_Release(m_pColliderCom);
	Safe_Release(m_pAttackColliderCom);
	Safe_Release(m_pHPUI);
	Safe_Release(m_pDissolve);

	Safe_Release(m_pTextureParticleTransform_Hand);
	Safe_Release(m_pTextureParticleTransform_Leg);
	
	//for (_uint i = 0; i<ShurikenSize;i++)
	//{
	//	Safe_Release(m_ArrayShuriken[i]);
	//}

}