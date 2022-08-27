#include "stdafx.h"
#include "..\public\Monster_Vayusura_Minion.h"

#include "HpUI.h"

CMonster_Vayusura_Minion::CMonster_Vayusura_Minion(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CMonster(pDevice, pDeviceContext)
{
}

CMonster_Vayusura_Minion::CMonster_Vayusura_Minion(const CMonster_Vayusura_Minion & rhs)
	: CMonster(rhs)
{
}

HRESULT CMonster_Vayusura_Minion::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	if (pArg != nullptr)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, *((_float3*)pArg));

	m_pTransformCom->Rotation_CW(XMVectorSet(0, 1, 0, 0), XMConvertToRadians(170));


	SetUp_Info();


#ifdef _DEBUG
	///////////////////test
	//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(493.f, 7.100010f, 103.571f)); // Stage2
	//m_pNavigationCom->FindCellIndex(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
	///////////////////
#endif

// Particle
	Set_DealyDIssolveTime(1.5f,1.5f);

	return S_OK;
}

_int CMonster_Vayusura_Minion::Update(_double dDeltaTime)
{
	if (__super::Update(dDeltaTime) < 0)return -1;

	if (__super::Update(dDeltaTime) == UPDATE_SKIP)
		return UPDATE_SKIP;

	m_pMotionTrail->Update_MotionTrail(dDeltaTime);

	if (m_fHP <= 0)
	{
		m_bRepelOff = true;
		m_bLookAtOn = false;
		m_pDissolve->Update_Dissolving(dDeltaTime);
		m_pDissolve->Set_DissolveOn(false, 2.f);

		m_dDissolveTime += dDeltaTime;

		if (m_bDieSound == false && m_dDissolveTime >= 1.)
		{
			g_pGameInstance->Play3D_Sound(TEXT("EH_Vayusura_Screech_04.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
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
	FAILED_CHECK(m_pModel->Update_AnimationClip(dDeltaTime * m_dAcceleration, m_bIsOnScreen));
	FAILED_CHECK(Adjust_AnimMovedTransform(dDeltaTime));


	if (m_pHPUI != nullptr)
		m_pHPUI->Update(dDeltaTime);

	Update_Collider(dDeltaTime);

	//////////////////////
	Player_Comparison(dDeltaTime);
	//////////////////////
	return _int();
}

_int CMonster_Vayusura_Minion::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;

	//////////
	if (m_bIsOnScreen)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}
	//////////
	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this,m_pTransformCom,m_pShaderCom,m_pModel, nullptr, m_pDissolve));
	FAILED_CHECK(m_pRendererCom->Add_TrailGroup(CRenderer::TRAIL_MOTION, m_pMotionTrail));

	//FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

#ifdef _DEBUG
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pAttackColliderCom));
#endif

	if (m_SpawnDealytime <= 0 && m_bIsSpawnDissolove == false)
	{
		m_pDissolve->Set_DissolveOn(true, m_SpawnDissolveTime);
		m_pDissolve->Update_Dissolving(dDeltaTime);

		if (m_pDissolve->Get_IsDissolving() == false)
			m_bIsSpawnDissolove = true;
	}

	if (m_pHPUI != nullptr)
	{
		m_pHPUI->LateUpdate(dDeltaTime);


	}
	return _int();
}

_int CMonster_Vayusura_Minion::Render()
{
	if (__super::Render() < 0)
		return -1;

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

_int CMonster_Vayusura_Minion::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;



	return _int();
}

void CMonster_Vayusura_Minion::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	if (CollisionTypeID::CollisionType_Player == eConflictedObjCollisionType)
	{
		_Vector vDamageDir = XMVector3Normalize(pConflictedCollider->Get_ColliderPosition(iConflictedObjColliderIndex).XMVector() - m_pTransformCom->Get_MatrixState(CTransform::TransformState::STATE_POS));
		if (-2 == pConflictedObj->Take_Damage(this, 1.f, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower))
		{
			m_pHPUI->Set_ADD_HitCount(1);
			m_fHP += -1;
			m_bIOnceAnimSwitch = true;
		}
		pConflictedCollider->Set_Conflicted(1.f);
	}
}

_float CMonster_Vayusura_Minion::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
{
	m_pHPUI->Set_ADD_HitCount((_int)fDamageAmount);
	m_fHP += -fDamageAmount;
	m_bIOnceAnimSwitch = true;

	if (0 >= m_fHP)
	{
		return -1.f;
	}

	return _float();
}

HRESULT CMonster_Vayusura_Minion::SetUp_Info()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_pPlayerTransform = static_cast<CTransform*>(pGameInstance->Get_Commponent_By_LayerIndex(m_eNowSceneNum, TAG_LAY(Layer_Player), TAG_COM(Com_Transform)));

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::SetUp_Collider()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider), (CComponent**)&m_pColliderCom));
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_ColliderSub), (CComponent**)&m_pAttackColliderCom));

	/////////////////m_pColliderCom!@!@#$@!#$@#$@$!@%#$%@#$%%^^W@!
	COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(5.f, 5.f, 5.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	ATTACHEDESC tAttachedDesc;
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.033178f, -0.45067f));
	m_vecAttachedDesc.push_back(tAttachedDesc);

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "head", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.010466f, -0.6897f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_02", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.031359f, -0.49888f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "calf_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.0445425f, -0.046337f, -0.21746f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.20648f, 0.069229f, -0.51353f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "middle_01_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.39241f, 0.083289f, -0.65896f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "index_02_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.6475f, 0.08306f, -0.69517f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.20648f, 0.069229f, -0.51353f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "middle_01_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.39241f, 0.083289f, -0.65896f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "index_02_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.6475f, 0.08306f, -0.69517f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();
	//////////////////////////////////////////////////////




	//////////////////////////m_pAttackColliderCom
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(5.f, 5.f, 5.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.033178f, -0.45067f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "head", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.010466f, -0.6897f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_02", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.031359f, -0.49888f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "calf_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.0445425f, -0.046337f, -0.21746f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.20648f, 0.069229f, -0.51353f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "middle_01_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.39241f, 0.083289f, -0.65896f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "index_02_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.6475f, 0.08306f, -0.69517f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.20648f, 0.069229f, -0.51353f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "middle_01_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.39241f, 0.083289f, -0.65896f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "index_02_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.6475f, 0.08306f, -0.69517f));
	m_vecAttackAttachedDesc.push_back(tAttachedDesc);
	m_pAttackColliderCom->Set_ParantBuffer();
	///////////////////////////////////////////////
	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::SetUp_Fight(_double dDeltaTime)
{
	m_fDistance = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).Get_Distance(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));


	m_fPlayerPos = m_pPlayerTransform->Get_MatrixState_Float3(CTransform::STATE_POS);


	if (m_bLookAtOn)
	{

		_Vector vTarget = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
		m_pTransformCom->Turn_Dir(vTarget, 0.9f);
	}



	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Update_Collider(_double dDeltaTime)
{
	m_pColliderCom->Update_ConflictPassedTime(dDeltaTime);
	m_pAttackColliderCom->Update_ConflictPassedTime(dDeltaTime);


	//Collider
	_uint	iNumCollider = m_pColliderCom->Get_NumColliderBuffer();
	for (_uint i = 0; i < iNumCollider; i++)
		m_pColliderCom->Update_Transform(i, m_vecAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());

	if (m_bColliderAttackOn == true)
	{
		//AttackCollider
		_uint	iNumCollider = m_pAttackColliderCom->Get_NumColliderBuffer();
		for (_uint i = 0; i < iNumCollider; i++)
			m_pAttackColliderCom->Update_Transform(i, m_vecAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());

		FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_MonsterWeapon, this, m_pAttackColliderCom));
	}

	FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_Monster, this, m_pColliderCom));

	if (m_bRepelOff != true)
		FAILED_CHECK(g_pGameInstance->Add_RepelGroup(m_pTransformCom, 1.5f));

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::PlayAnim(_double dDeltaTime)
{
	SetUp_Fight(dDeltaTime);

	CoolTime_Manager(dDeltaTime);

	if (true == m_bIOnceAnimSwitch)
	{
		Once_AnimMotion(dDeltaTime);
		m_pModel->Change_AnimIndex(m_iOnceAnimNumber);
	}
	else
	{
		Infinity_AnimMotion(dDeltaTime);
		m_pModel->Change_AnimIndex(m_iInfinityAnimNumber);
	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::CoolTime_Manager(_double dDeltaTime)
{
	//�ѹ��� �����ϴ� �ִϸ��̼�


	if (m_bIOnceAnimSwitch == true)
	{
		m_dInfinity_CoolTime = 0;
		m_iInfinityPattern = 0;

		m_iOncePattern = 40;
	}

	//�ݺ������� �����ϴ� �ִϸ��̼�
	m_dInfinity_CoolTime += dDeltaTime;
	if (m_dInfinity_CoolTime >= 2)
	{
		//m_iInfinityPattern = rand() % 2;

		m_iInfinityPattern += 1;
		if (m_iInfinityPattern > 4)
		{
			m_iInfinityPattern = 0;
		}

		m_dInfinity_CoolTime = 0;


		CUtilityMgr* pUtil = GetSingle(CUtilityMgr);

		XMStoreFloat4(&m_fDirection,XMVector3Normalize(m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK) * pUtil->RandomFloat(-1,1)+ m_pTransformCom->Get_MatrixState(CTransform::STATE_RIGHT) * pUtil->RandomFloat(-1, 1)));

		if (m_fDistance > 7)
		{
			m_iInfinityPattern = 10;

			m_dAttackOn = true;

			if (m_iAttackStartSound == 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Wave_Vayusura_Attack.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);

				m_iAttackStartSound++;
			}
		}

	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Once_AnimMotion(_double dDeltaTime)
{


	switch (m_iOncePattern)
	{
	case 40:
	{
		m_iOnceAnimNumber = 4;
		break;
	}
	default:
	{
		m_iOnceAnimNumber = 4;
		break;
	}
	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Infinity_AnimMotion(_double dDeltaTime)
{
#ifdef _DEBUG
	// #DEBUG PatternSET
	// m_iOncePattern = 2;

	if (KEYPRESS(DIK_B))
		m_iOncePattern = 0;
#endif // _DEBUG

	switch (m_iInfinityPattern)
	{
	case 0:
		if (m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y < m_fPlayerPos.y + 6)
		{
			m_pTransformCom->MovetoDir(XMLoadFloat4(&_float4(0.f, 1.f, 0.f, 0.f)), dDeltaTime * 0.5);

			m_pTransformCom->MovetoDir(XMLoadFloat4(&m_fDirection), dDeltaTime * 0.5);
		}
		m_iInfinityAnimNumber = 0; // flapping
		m_bLookAtOn = true;
		break;
	case 1:
		if (m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y > m_fPlayerPos.y + 3)
		{
			m_pTransformCom->MovetoDir(XMLoadFloat4(&_float4(0.f, 1.f, 0.f, 0.f)), -dDeltaTime * 0.5);

			m_pTransformCom->MovetoDir(XMLoadFloat4(&m_fDirection), dDeltaTime * 0.5);
		}
		m_iInfinityAnimNumber = 0;
		m_bLookAtOn = true;
		break;
	case 2:
		if (m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y < m_fPlayerPos.y + 6 ||
			m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y > m_fPlayerPos.y + 3)
		{
			m_bLookAtOn = false;

			m_pTransformCom->MovetoDir(XMLoadFloat4(&m_fDirection), dDeltaTime * 0.7);
			//m_pTransformCom->LookDir(XMLoadFloat4(&m_fDirection));

			m_pTransformCom->Turn_Dir(XMLoadFloat4(&m_fDirection), 0.9f);

			m_iInfinityAnimNumber = 1;
		}
		else {
			m_bLookAtOn = true;
			m_iInfinityAnimNumber = 2;
		}
		break;
	case 3:
		if (m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y < m_fPlayerPos.y + 6 ||
			m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y > m_fPlayerPos.y + 3)
		{
			m_bLookAtOn = false;

			m_pTransformCom->MovetoDir(XMLoadFloat4(&m_fDirection), dDeltaTime * 0.7);
			//m_pTransformCom->LookDir(XMLoadFloat4(&m_fDirection));
			m_pTransformCom->Turn_Dir(XMLoadFloat4(&m_fDirection), 0.9f);

			m_iInfinityAnimNumber = 1;
		}
		else {
			m_bLookAtOn = true;
			m_iInfinityAnimNumber = 2;
		}
		break;
	case 10:
		if (m_dAttackOn == true)
		{
			m_dSpeedTime = 0;

			m_TempPlayerPos = m_pPlayerTransform->Get_MatrixState_Float3(CTransform::STATE_POS);
			m_TempPlayerPos.y += 0.2f;
			_float TempDis = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).Get_Distance(XMLoadFloat3(&m_TempPlayerPos));
			if (TempDis > 1.f) //if (m_fDistance > 0.3f)
			{

				m_bLookAtOn = false;
				m_iInfinityAnimNumber = 5;

				_Vector vTarget = XMVector3Normalize(XMLoadFloat3(&m_TempPlayerPos) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
				m_pTransformCom->Turn_Dir(vTarget, 0.9f);

				_float fMyPosY = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y;

				if (fMyPosY >= m_fPlayerPos.y)
				{
					m_pTransformCom->Move_Forward(dDeltaTime * 4); //navi gogo
				}
				else
				{
					_float3 fLook = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_LOOK);
					fLook.y = 0;

					m_pTransformCom->MovetoDir(fLook.Get_Nomalize(),dDeltaTime * 4); //navi gogo
				}
			}
			else {
				m_dAttackOn = false;
			}
		}
		else {
			//m_bLookAtOn = false;
			//m_iInfinityAnimNumber = 2;
			//m_pTransformCom->Move_Up(dDeltaTime * 0.6748241f);
			//_float3 fLook = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_LOOK);
			//fLook.y = 0;

			//m_pTransformCom->MovetoDir(fLook.Get_Nomalize(), dDeltaTime * 1.2345625f); //navi gogo

			///////////test

			m_bLookAtOn = false;
			m_iInfinityAnimNumber = 2;

			if (m_dSpeedTime <= 1)
			{
				m_dSpeedTime += dDeltaTime;
			}
			_float fSpeed = g_pGameInstance->Easing(TYPE_SinOut, 0.f, 1.f, (_float)m_dSpeedTime,1.f); // PlayRate - 0.266666 and 0.5 - 0.266666
			m_pTransformCom->Move_Up(dDeltaTime * fSpeed);


			_float3 fLook = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_LOOK);
			fLook.y = 0;

			m_pTransformCom->MovetoDir(fLook.Get_Nomalize(), dDeltaTime * (1- fSpeed) * 4.f); //navi gogo

			////////////////////////////////////


			//m_pTransformCom->Move_Backward(dDeltaTime);
		}
		break;
	}

	//���� ���� �ڵ忡�� ���̽�2�� ���̽�3 üũ���� ���� �׸��� ���̽� 0�̶� ���̽�1�� ���� �������� ���µ� �̰� ����ó���� �÷��̾� ������ �������� > < �̷������� �ε�ȣ �Կ��� Dir ���� �ٲٱ� 
	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Player_Comparison(_double dDeltaTime)
{
	_float3 fPlayerPos = m_pPlayerTransform->Get_MatrixState_Float3(CTransform::STATE_POS);
	_float3 fMonsterPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

	if (fPlayerPos.y >= fMonsterPos.y)
	{
		fMonsterPos.y = fPlayerPos.y;
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, fMonsterPos);
	}
	return S_OK;

}

HRESULT CMonster_Vayusura_Minion::Ready_ParticleDesc()
{

	m_pTextureParticleTransform_HEAD = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_HEAD);

	m_pTextureParticleTransform_WingR = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_WingR);

	m_pTextureParticleTransform_WingL = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_WingL);

	m_pTextureParticleTransform_Foot = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_Foot);
	mPlaneTimer = 0;
	mFlyTimer = 0;
	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Update_Particle(_double timer)
{
	_Matrix mat_World = m_pTransformCom->Get_WorldMatrix();
	//	ATTACHEDESC boneDesc = m_vecAttachedDesc[0]->Get_WeaponDesc().eAttachedDesc;
	//	_Vector Vec_WeaponPos = boneDesc.Get_AttachedBoneWorldPosition_BlenderFixed();
	//	_Matrix mat_Weapon = boneDesc.Caculate_AttachedBoneMatrix_BlenderFixed();

	mat_World.r[0] = XMVector3Normalize(mat_World.r[0]);
	mat_World.r[1] = XMVector3Normalize(mat_World.r[1]);
	mat_World.r[2] = XMVector3Normalize(mat_World.r[2]);

	mat_World.r[3] = m_pColliderCom->Get_ColliderPosition(1).XMVector();
	m_pTextureParticleTransform_HEAD->Set_Matrix(mat_World); // Head

	mat_World.r[3] = m_pColliderCom->Get_ColliderPosition(6).XMVector();
	m_pTextureParticleTransform_WingR->Set_Matrix(mat_World); // Wing_r 6  

	mat_World.r[3] = m_pColliderCom->Get_ColliderPosition(8).XMVector();
	m_pTextureParticleTransform_WingL->Set_Matrix(mat_World); // Wing_l 8 

//	mat_World.r[3] = m_pColliderCom->Get_ColliderPosition(3).XMVector();
//	m_pTextureParticleTransform_Foot->Set_Matrix(mat_World); // foot

	mat_World.r[3] = XMVectorSetY(mat_World.r[3], m_pPlayerTransform->Get_MatrixState_Float3(CTransform::STATE_POS).y);

	m_pTextureParticleTransform_Foot->Set_Matrix(mat_World); // player

	if (mPlaneTimer >= 0)
		mPlaneTimer -= timer;

	if (mFlyTimer >= 0)
		mFlyTimer -= timer;


	if (KEYDOWN(DIK_V))
	{
	//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_VM_Test, m_pTextureParticleTransform_HEAD);
		Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_VM_Cash2, m_pTextureParticleTransform_HEAD);
	//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_VM_Cash2, m_pTransformCom);
	//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_VM_Cash2, m_pPlayerTransform);


	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Play_SpawnEffect()
{
	if (m_SpawnEffectAdjust == 0)
	{
		m_SpawnEffectAdjust++;

		g_pGameInstance->Play3D_Sound(TEXT("UM_Spawn_05.ogg"),
			m_pTransformCom->Get_MatrixState(CTransform::STATE_POS),
			CHANNELID::CHANNEL_MONSTER, 0.8f);
		{
			// ring
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(
				CPartilceCreateMgr::Um_Spawn2_Image,
				//	CPartilceCreateMgr::Um_Spawn2_Image_powerdown,
				0,
				0.6f,
				_float4(1.0f),
				_float4(0.0f),
				1,
				_float3(0.5f),
				_float3(3.0f),
				1);
			testTex.iTextureLayerIndex = 20;
			testTex.eParticleTypeID = InstanceEffect_Ball;
			testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_64;



			testTex.ParticleStartRandomPosMin = _float3(0, 1.2f, 0);
			testTex.ParticleStartRandomPosMax = _float3(0, 1.2f, 0);
			testTex.FollowingTarget = m_pTransformCom;
			testTex.iFollowingDir = FollowingDir_Look;
			testTex.vEmissive_SBB = _float3(1, 0.5f, 0.5f);
			testTex.m_fAlphaTestValue = 0.2f;

			//	testTex.TempBuffer_0.z = 0;
			//	testTex.TempBuffer_0.w = FollowingDir_Right;
			//	testTex.iFollowingDir = FollowingDir_Up;
			//	testTex.TempBuffer_1.x = 0.0f;

			GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);
		}

		{
			// ring
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(
				CPartilceCreateMgr::Um_Spawn4_smoke,
				0,
				0.4f,
				_float4(1.0f),
				_float4(0.0f),
				1,
				_float3(0.5f),
				_float3(0.7f),
				1);
			testTex.iTextureLayerIndex = 20;
			testTex.eParticleTypeID = InstanceEffect_Ball;
			testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_64;



			testTex.ParticleStartRandomPosMin = _float3(0, 1.2f, 0);
			testTex.ParticleStartRandomPosMax = _float3(0, 1.2f, 0);
			testTex.FollowingTarget = m_pTransformCom;
			testTex.iFollowingDir = FollowingDir_Look;
			testTex.vEmissive_SBB = _float3(1, 0.5f, 0.5f);
			testTex.m_fAlphaTestValue = 0.2f;
			testTex.Particle_Power = 1.0f;

			GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);
		}
	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Monster_Vayusura_Minion), TAG_COM(Com_Model), (CComponent**)&m_pModel));
	FAILED_CHECK(m_pModel->Change_AnimIndex(0));


	CMotionTrail::MOTIONTRAILDESC tMotionDesc;

	tMotionDesc.iNumTrailCount = 5;
	tMotionDesc.pModel = m_pModel;
	tMotionDesc.pShader = m_pShaderCom;
	tMotionDesc.iPassIndex = 5;

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_MotionTrail), TAG_COM(Com_MotionTrail), (CComponent**)&m_pMotionTrail, &tMotionDesc));

	CTransform::TRANSFORMDESC tDesc = {};

	tDesc.fMovePerSec = 5;
	tDesc.fRotationPerSec = XMConvertToRadians(60);
	tDesc.vPivot = _float3(0, 0, 0);
	tDesc.fScalingPerSec = 1;

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));


	CHpUI::HPDesc HpDesc;
	HpDesc.m_HPType = CHpUI::HP_MONSTER;
	HpDesc.m_pObjcect = this;
	HpDesc.m_vPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);
	HpDesc.m_Dimensions = 1.f;
	m_fMaxHP = 5.f;
	m_fHP = m_fMaxHP;
	g_pGameInstance->Add_GameObject_Out_of_Manager((CGameObject**)(&m_pHPUI), m_eNowSceneNum, TAG_OP(Prototype_Object_UI_HpUI), &HpDesc);

	CDissolve::DISSOLVEDESC DissolveDesc;
	DissolveDesc.pModel = m_pModel;
	DissolveDesc.eDissolveModelType = CDissolve::DISSOLVE_ANIM;
	DissolveDesc.pShader = m_pShaderCom;
	DissolveDesc.RampTextureIndex = 8;
	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Dissolve), TAG_COM(Com_Dissolve), (CComponent**)&m_pDissolve, &DissolveDesc));

	SetUp_Collider();

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Adjust_AnimMovedTransform(_double dDeltaTime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.98)
	{
		m_iAdjMovedIndex = 0;
		m_bColliderAttackOn = false;
		m_dAcceleration = 1;

		m_EffectAdjust = 0;

		m_iSoundIndex = 0;
		m_iAttackStartSound = 0;
		Set_LimLight_N_Emissive();

		if (PlayRate > 0.98 && m_bIOnceAnimSwitch == true)
		{
			m_bIOnceAnimSwitch = false;
			m_dOnceCoolTime = 0;
			m_dInfinity_CoolTime = 0;
		}
	}

	if (PlayRate <= 0.98) //�ִϸ��̼��� ���� ��, 0.98�� ���� �������� ����
	{
		switch (iNowAnimIndex)
		{
		case 0:
		{
			if (m_iSoundIndex == 0 && PlayRate >= 0.3777)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Vayusura_Dive_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.7f);
				m_iSoundIndex++;
			}
			break;
		}
		case 1:
		{
			if (m_iSoundIndex == 0 && PlayRate >= 0.4166)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Vayusura_Dive_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.7f);
				m_iSoundIndex++;
			}
			break;
		}
		case 2:
		{
			if (m_iSoundIndex == 0 && PlayRate >= 0.3888)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Vayusura_Dive_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.7f);
				m_iSoundIndex++;
			}
			break;
		}
		case 4:
		{
			if (m_iAdjMovedIndex == 0)
			{
				m_dAcceleration = 1;
				m_iAdjMovedIndex++;
			}
			if (PlayRate > 0 && PlayRate <= 0.95)
			{
				m_bIOnceAnimSwitch = true;
				
				if (m_iSoundIndex == 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Vayusura_Screech_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					m_iSoundIndex++;
				}
			}
			else if (PlayRate >= 0.95)
			{
				m_bIOnceAnimSwitch = false;
			}

			
			break;
		}
		case 5:
		{
			_float Value = 0.5f;
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));
			

			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bColliderAttackOn = true;
				m_iAdjMovedIndex++;
			}


			

			if (PlayRate > 0.15f && PlayRate < 0.9f)
			{
				_float FootY = m_pTextureParticleTransform_HEAD->Get_MatrixState_Float3(CTransform::STATE_POS).y;
				_float PY = m_pPlayerTransform->Get_MatrixState_Float3(CTransform::STATE_POS).y;

				if (mPlaneTimer <= 0)
					m_pMotionTrail->Add_MotionBuffer(m_pTransformCom->Get_WorldFloat4x4(), _float4(0.71f, 0.8f, 0.8f, 1.f), 0.8f);



				if (mFlyTimer <= 0)
				{
					Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_VM_Cash2, m_pTextureParticleTransform_HEAD);
					mFlyTimer = 0.5;
				}


				if (fabs((FootY)-(PY)) < 2.0f && mPlaneTimer <= 0)
				{
					mPlaneTimer = 0.07f;
					Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_VM_Plane, m_pTextureParticleTransform_Foot);


					{
						INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
							Prototype_Mesh_SM_meteo,
							0.01f,
							0.5f,
							// _float4(1),
							_float4(1.0f, 1.0f, 1.0f, 1),
							_float4(0.0f, 0.0f, 0.0f, 1),
							1,
							_float3(1).XMVector() * 5.0f,
							_float3(1).XMVector() * 2.0f,
							1);

						testMesh.fDistortionNoisingPushPower = 0;
						testMesh.ePassID = MeshPass_MaskingNoising;
						testMesh.eParticleTypeID = InstanceEffect_Fountain;
						testMesh.eInstanceCount = Prototype_ModelInstance_8;
						_float randpower = GetSingle(CUtilityMgr)->RandomFloat(3, 8);

						testMesh.Particle_Power = randpower;
						testMesh.iNoiseTextureIndex = NONNOISE;

						testMesh.ParticleStartRandomPosMin = _float3(-1,0,-1);
						testMesh.ParticleStartRandomPosMax = _float3(1, 0, 1);
						_Matrix mat = m_pTransformCom->Get_WorldMatrix();
						_Vector pos = mat.r[3];
						testMesh.vFixedPosition = pos;

						GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
					}

				}
			}

	


			if (m_iSoundIndex == 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_M1_1145.mp3"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}
			break;
		}
		default:
			break;
		}

		//switch (iNowAnimIndex)
		//{
		//case 1://�ִϸ��̼� �ε������� ����ָ� ��
		//	if (m_iAdjMovedIndex == 0 && PlayRate > 0.0) // �̷��� �Ǹ� ���� �ִϸ��̼ǿ��� �����Ǵ� �ð� ������ ���� �ٷ� ���� ��, PlayRate�� 0�� >= �������� >�� �ϼ�
		//	{

		//		m_iAdjMovedIndex++; //�ִϸ��̼��� ������ �� �ѹ��� �ߵ���Ű�� ���� ++��Ų��.
		//	}
		//	else if (m_iAdjMovedIndex == 1 && PlayRate > 0.7666666666666666) //Ư�� ������ �÷��� ����Ʈ���Ŀ� ���������
		//	{


		//		m_iAdjMovedIndex++;
		//	}

		//	break;
		//case 2:

		//	break;
		//}




	}

	m_iOldAnimIndex = iNowAnimIndex;
	return S_OK;
}

CMonster_Vayusura_Minion * CMonster_Vayusura_Minion::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CMonster_Vayusura_Minion*	pInstance = NEW CMonster_Vayusura_Minion(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Vayusura_Minion");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMonster_Vayusura_Minion::Clone(void * pArg)
{
	CMonster_Vayusura_Minion*	pInstance = NEW CMonster_Vayusura_Minion(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Vayusura_Minion");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonster_Vayusura_Minion::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
	Safe_Release(m_pColliderCom);
	Safe_Release(m_pAttackColliderCom);
	Safe_Release(m_pHPUI);
	Safe_Release(m_pDissolve);
	Safe_Release(m_pMotionTrail);
	

	Safe_Release(m_pTextureParticleTransform_HEAD);
	Safe_Release(m_pTextureParticleTransform_WingR);
	Safe_Release(m_pTextureParticleTransform_WingL);
	Safe_Release(m_pTextureParticleTransform_Foot);
}
