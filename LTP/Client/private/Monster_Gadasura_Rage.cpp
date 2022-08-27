#include "stdafx.h"
#include "..\public\Monster_Gadasura_Rage.h"
#include "Monster_Bullet_Universal.h"
#include "Monster_Weapon_Universal.h"
#include "Gadasura_Rage_Hollogram.h"
#include "Monster_Texture_Bullet.h"
#include "HpUI.h"
#include "Monster_Weapon_Universal.h"

CMonster_Gadasura_Rage::CMonster_Gadasura_Rage(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CMonster(pDevice, pDeviceContext)
{
}

CMonster_Gadasura_Rage::CMonster_Gadasura_Rage(const CMonster_Gadasura_Rage & rhs)
	: CMonster(rhs)
{
}

HRESULT CMonster_Gadasura_Rage::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));
	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	if (pArg != nullptr)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, *((_float3*)pArg));



	SetUp_Info();

	SetUp_Weapon();


	//////////////////testPosition
	//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(493.f, 7.100010f, 103.571f)); // Stage2
	//m_pNavigationCom->FindCellIndex(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
	//////////////////////////////

	// Particle
	 Set_DealyDIssolveTime(1.0f);

	return S_OK;
}

_int CMonster_Gadasura_Rage::Update(_double dDeltaTime)
{

	if (__super::Update(dDeltaTime) < 0)return -1;

	if (__super::Update(dDeltaTime) == UPDATE_SKIP)
		return UPDATE_SKIP;

	if (m_fHP <= 0)
	{
		m_bLookAtOn = false;
		m_pDissolve->Update_Dissolving(dDeltaTime);
		m_pDissolve->Set_DissolveOn(false, 2.f);

		m_dDissolveTime += dDeltaTime;

		if (m_bDieSound == false && m_dDissolveTime >= 1.)
		{
			g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Hit_05.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
			m_bDieSound = true;
		}

		if (m_dDissolveTime >= 2)
		{
			//	g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Die.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
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

	if (m_pHPUI != nullptr)
		m_pHPUI->Update(dDeltaTime);

	if (m_pWeapon != nullptr)
		m_pWeapon->Update(dDeltaTime);

	Update_Collider(dDeltaTime);

	return _int();
}

_int CMonster_Gadasura_Rage::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;

	if (__super::LateUpdate(dDeltaTime) == UPDATE_SKIP)
		return UPDATE_SKIP;

	//////////
	if (m_bIsOnScreen)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}

	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this, m_pTransformCom, m_pShaderCom, m_pModel, nullptr, m_pDissolve));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

#ifdef _DEBUG
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));
#endif

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));

	if (m_SpawnDealytime <= 0 && m_bIsSpawnDissolove == false)
	{
		m_pDissolve->Set_DissolveOn(true, m_SpawnDissolveTime);
		m_pDissolve->Update_Dissolving(dDeltaTime);

		if (m_pDissolve->Get_IsDissolving() == false)
			m_bIsSpawnDissolove = true;
	}

	if (m_pHPUI != nullptr)
		m_pHPUI->LateUpdate(dDeltaTime);

	if (m_pWeapon != nullptr)
		m_pWeapon->LateUpdate(dDeltaTime);
	return _int();
}

_int CMonster_Gadasura_Rage::Render()
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

_int CMonster_Gadasura_Rage::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;
	if (__super::LateRender() == UPDATE_SKIP)
		return UPDATE_SKIP;
	return _int();
}

void CMonster_Gadasura_Rage::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	if (CollisionTypeID::CollisionType_Player == eConflictedObjCollisionType)
	{
		_Vector vDamageDir = XMVector3Normalize(pConflictedCollider->Get_ColliderPosition(iConflictedObjColliderIndex).XMVector() - m_pTransformCom->Get_MatrixState(CTransform::TransformState::STATE_POS));
		pConflictedObj->Take_Damage(this, 1.f, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower);
		pConflictedCollider->Set_Conflicted(1.f);
	}
}

_float CMonster_Gadasura_Rage::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
{
	m_pHPUI->Set_ADD_HitCount((_int)fDamageAmount);
	m_fHP += -fDamageAmount;

	m_bStopCoolTimeOn = true;

	m_dSpecial_CoolTime = 0;


	m_bIOnceAnimSwitch = true;
	if (m_eMonster_State != Anim_State::MONSTER_ATTACK)
	{
		if (bKnockback == false)
		{
			m_iOncePattern = 40;
		}
		else {
			m_iOncePattern = 41;

			XMStoreFloat3(&m_fKnockbackDir, vDamageDir);
		}

		if (m_fHP < 5 && m_iBoolOnce == 0)
		{
			m_iOncePattern = 42;
			m_dSpecial_CoolTime = 0;
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

HRESULT CMonster_Gadasura_Rage::SetUp_Info()
{

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(2.f, 0.f, 2.f));


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_pPlayerTransform = static_cast<CTransform*>(pGameInstance->Get_Commponent_By_LayerIndex(m_eNowSceneNum, TAG_LAY(Layer_Player), TAG_COM(Com_Transform)));

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::SetUp_Weapon()
{
	CMonster_Weapon_Universal::Monster_Weapon_UniversalDesc MonsterWeaponDesc;
	MonsterWeaponDesc.iMonsterWeaponMeshNumber = CMonster_Weapon_Universal::GADASURA_RAGE_WEAPON;
	MonsterWeaponDesc.Object = this;
	MonsterWeaponDesc.eAttachedDesc.Initialize_AttachedDesc(this, "skd_r_wrist", _float3(1.f, 1.f, 1.f), _float3(0, 0, 0), _float3(-2.535f, -0.075f, -3.03f));

	g_pGameInstance->Add_GameObject_Out_of_Manager((CGameObject**)(&m_pWeapon), m_eNowSceneNum, TAG_OP(Prototype_Object_Monster_Weapon_Universal), &MonsterWeaponDesc);

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::SetUp_Collider()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider), (CComponent**)&m_pColliderCom));

	/////////////////m_pColliderCom!@!@#$@!#$@#$@$!@%#$%@#$%%^^W@!
	COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(6.f, 6.f, 6.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	ATTACHEDESC tAttachedDesc;
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.00047f, -0.027856f, -1.8269f));
	m_vecAttachedDesc.push_back(tAttachedDesc);


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_head", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.13306f, -2.6351f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(2.f, 2.f, 2.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_spine_03", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.030646f, -2.3865f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(2.f, 2.f, 2.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_pelvis", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.004822f, -1.4863f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_r_knee", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.30817f, -0.017663f, -0.88963f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_r_ankle", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.30817f, 0.16343f, -0.15622f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_l_knee", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.30817f, -0.017663f, -0.88963f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_l_ankle", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.30817f, 0.16343f, -0.15622f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();



	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_r_arm", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.47793f, 0.16684f, -2.5459f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();



	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.5f, 1.5f, 1.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_r_elbow", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.96232f, 0.20043f, -2.3494f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();



	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_l_arm", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.47793f, 0.16684f, -2.5459f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.5f, 1.5f, 1.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_l_elbow", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.96232f, 0.20043f, -2.3494f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::SetUp_Fight(_double dDeltaTime)
{
	m_fDistance = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).Get_Distance(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));


	if (m_bLookAtOn)
	{
		//m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));


		_Vector vTarget = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));

		//m_pTransformCom->Turn_Dir(XMVector3Normalize(m_pTransformCom->Get_MatrixScale(CTransform::STATE_LOOK)*0.9 + vTarget* 0.1));
		m_pTransformCom->Turn_Dir(vTarget, 0.9f);
	}



	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Update_Collider(_double dDeltaTime)
{
	m_pColliderCom->Update_ConflictPassedTime(dDeltaTime);

	//Collider
	_uint	iNumCollider = m_pColliderCom->Get_NumColliderBuffer();
	for (_uint i = 0; i < iNumCollider; i++)
		m_pColliderCom->Update_Transform(i, m_vecAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());

	FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_Monster, this, m_pColliderCom));

	if (m_bRepelOff != true)
		FAILED_CHECK(g_pGameInstance->Add_RepelGroup(m_pTransformCom, 1.5f, m_pNavigationCom));

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::PlayAnim(_double dDeltaTime)
{
	SetUp_Fight(dDeltaTime);

	CoolTime_Manager(dDeltaTime);

	if (true == m_bIOnceAnimSwitch)
	{
		Once_AnimMotion(dDeltaTime);
		_uint i = m_pModel->Get_NowAnimIndex();
		switch (i)
		{
		case 6:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.2f);
			break;
		case 14:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			break;
		case 15:
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
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
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

HRESULT CMonster_Gadasura_Rage::CoolTime_Manager(_double dDeltaTime)
{
	if (m_bStopCoolTimeOn == false)
	{
		m_dOnceCoolTime += dDeltaTime;
		m_dSpecial_CoolTime += dDeltaTime;
		m_dInfinity_CoolTime += dDeltaTime;
	}

	//_double Once = m_dOnceCoolTime;
	//wstring tt = L"Once Time = " + to_wstring(Once) + L"\n";
	////tt.substr(4, 10).c_str(); 
	////OutputDebugStringW(tt.substr(4, 10).c_str());
	//OutputDebugStringW(tt.c_str());


	//�ѹ��� �����ϴ� �ִϸ��̼�

	if (m_dOnceCoolTime > 2 && m_fDistance < 5 || m_bComboAnimSwitch == true)
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
		m_iInfinityPattern = rand() % 6;


		m_dInfinity_CoolTime = 0;
	}
	if (m_bComboAnimSwitch == false && m_bIOnceAnimSwitch == false)
	{
		Special_Trigger(dDeltaTime);
	}
	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Once_AnimMotion(_double dDeltaTime)
{
#ifdef _DEBUG
	// #DEBUG PatternSET
	// m_iOncePattern = 2;

	if (KEYPRESS(DIK_B))
		m_iOncePattern = 4;
#endif // _DEBUG

	switch (m_iOncePattern)
	{
	case 0:
		m_iOnceAnimNumber = 26; //Hollogram start
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 1:
		m_iOnceAnimNumber = 27; //Hollogram Run
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 2:
		m_iOnceAnimNumber = 28; //Hollogram Run
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 3:
		m_iOnceAnimNumber = 29; //Hollogram End
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 4:
		m_iOnceAnimNumber = 23; //TripleSmash
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 5:
		m_iOnceAnimNumber = 5; //Back
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 6:
		m_iOnceAnimNumber = 25; //Rage Run
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 7:
		m_iOnceAnimNumber = 14; //Rage Run
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 8:
		m_iOnceAnimNumber = 21; //Rage Run Attack
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 9:
		m_iOnceAnimNumber = 3; //Right Move
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 10:
		m_iOnceAnimNumber = 17; //Attack1 
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 11:
		m_iOnceAnimNumber = 25; //Rage Run Start
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 12:
		m_iOnceAnimNumber = 15; //Rage Run
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 13:
		m_iOnceAnimNumber = 21; //Rage Run Attack
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 14:
		m_iOnceAnimNumber = 23; //TripleSmash
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 15:
		m_iOnceAnimNumber = 4; //Left Move
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 16:
		m_iOnceAnimNumber = 22; //Taunt
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 17:
		m_iOnceAnimNumber = 18; //Attack2
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 40:
		m_iOnceAnimNumber = 11; //right hit
		m_eMonster_State = Anim_State::MONSTER_HIT;
		break;
	case 41:
		m_iOnceAnimNumber = 12; //HeavyHit
		m_eMonster_State = Anim_State::MONSTER_HIT;
		break;
	case 42:
		m_iOnceAnimNumber = 6; //groggy
		break;
	case 51:
		m_iOnceAnimNumber = 20; //stomp Attack
		m_bComboAnimSwitch = false;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;

	}

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Pattern_Change()
{

	m_iOncePattern += 1;

	if (m_iOncePattern >= 18)
	{
		if (m_iAfterPattern < 18)
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

HRESULT CMonster_Gadasura_Rage::Infinity_AnimMotion(_double dDeltaTime)
{
	switch (m_iInfinityPattern)
	{
	case 0:
		m_iInfinityAnimNumber = 24;
		break;
	case 1:
		m_iInfinityAnimNumber = 24;
		break;
	case 2:
		m_iInfinityAnimNumber = 24;
		break;
	case 3:
		m_iInfinityAnimNumber = 24;
		break;
	case 4:
		m_iInfinityAnimNumber = 24;
		break;
	case 5:
		m_iInfinityAnimNumber = 24;
		break;
	case 6:
		m_iInfinityAnimNumber = 24;
		break;
	case 20:
		m_iInfinityAnimNumber = 0;
		break;
	default:
		m_iInfinityAnimNumber = 0;
		break;
	}

	if (m_eMonster_State == Anim_State::MONSTER_HIT)
	{
		Set_LimLight_N_Emissive();
	}

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Special_Trigger(_double dDeltaTime)
{

	if (m_fDistance < 2 && m_dSpecial_CoolTime > 10)
	{
		m_dSpecial_CoolTime = 0;
		m_dOnceCoolTime = 0;
		m_dInfinity_CoolTime = 0;

		m_bIOnceAnimSwitch = true;
		m_iOncePattern = 51;
	}

	if (m_fDistance > 8 && m_dSpecial_CoolTime > 10)
	{
		m_dSpecial_CoolTime = 0;
		m_dOnceCoolTime = 0;
		m_dInfinity_CoolTime = 0;

		m_bIOnceAnimSwitch = true;
		m_iOncePattern = 11;
	}

	return S_OK;
}
HRESULT CMonster_Gadasura_Rage::Ready_ParticleDesc()
{
	m_pTextureParticleTransform_Hand = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_Hand);

	m_pTextureParticleTransform_Demo1 = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_Demo1);

	m_pTextureParticleTransform_Demo2 = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_Demo2);

	m_pTextureParticleTransform_Demo3 = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_BREAK(m_pTextureParticleTransform_Demo3);
	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Update_Particle(_double timer)
{
	_Matrix mat_World = m_pTransformCom->Get_WorldMatrix();

	_Matrix mat_Weapon = (*m_pWeapon->Get_VecAttachedDesc())[0].Caculate_AttachedBoneMatrix_BlenderFixed();
	m_pTextureParticleTransform_Hand->Set_Matrix(mat_Weapon);

	mat_World.r[0] = XMVector3Normalize(mat_World.r[0]);
	mat_World.r[1] = XMVector3Normalize(mat_World.r[1]);
	mat_World.r[2] = XMVector3Normalize(mat_World.r[2]);
	m_pTextureParticleTransform_Demo1->Set_Matrix(mat_World);

#ifdef _DEBUG
	if (KEYDOWN(DIK_V))
	{
		// Stone mesh
	//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash0, m_pTransformCom);
		// trail
		// Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Attack2, m_pTransformCom);
		// ton
		// Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash1, m_pTransformCom);
		// Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLBOUND0, m_pTransformCom);

		 Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);
		
		{
			// Fragment
			INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase4_TurnAuto,
				//	Prototype_Mesh_SM_Box_Basic,
				Prototype_Mesh_SM_4E_IceShards_01,
				0.01f,
				0.8f,
				//	_float4(1,0,0,1),
				//	_float4(1,0,0,1),
				_float4(0.98f, 0.49f, 0.25f, 0.0f),
				_float4(0),
				1,
				_float3(10),
				_float3(0.1f),
				1);

			//	testMesh.eParticleTypeID = InstanceEffect_Fountain;
			testMesh.eInstanceCount = Prototype_ModelInstance_16;
			testMesh.ePassID = MeshPass_MaskingNoising;

			_float val = 1.5f;
			testMesh.ParticleStartRandomPosMin = _float3(-val, -0.5f, -val);
			testMesh.ParticleStartRandomPosMax = _float3(val, -0.5f, val);

			testMesh.TempBuffer_0.w = 276;
			testMesh.TempBuffer_0.w = 317;

			testMesh.iMaskingTextureIndex = NONNMASK;
			testMesh.iMaskingTextureIndex = 122;
			testMesh.iNoiseTextureIndex = 289;
			testMesh.vEmissive_SBB = _float3(1.f, 0.0f, 0.1f);
			testMesh.Particle_Power = 20.0f;

			testMesh.SubPowerRandomRange_RUL = _float3(1, 1, 1);
			testMesh.fRotSpeed_Radian = XMConvertToRadians(max(1080, 0));

			testMesh.TempBuffer_1.x = 1.0f;


			//testMesh.TempBuffer_0.x = 1;
			//testMesh.TempBuffer_0.y = FollowingDir_Right;

			_Matrix mat = m_pTransformCom->Get_WorldMatrix();
			_Vector pos = mat.r[3] + mat.r[2] * 3;
			testMesh.vFixedPosition = pos;

			//	testMesh.FollowingTarget = m_pTransformCom;
			//	testMesh.iFollowingDir = FollowingDir_Look;

		//	GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);

		}


		{
			// Stones
			INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
			//	Prototype_Mesh_SM_4E_IceShards_01,
				Prototype_Mesh_SM_Reorgeaskil04_stone1_7,
			//	Prototype_Mesh_SM_sinkhole,
				0.01f,
				0.5f,
				_float4(0.98f, 0.1f, 0.0f, 1),
				_float4(0.96f, 0.05f, 0.0f, 1),
				4,
				_float3(5.0f, 12.f, 5.f).XMVector()*0.4f,
				_float3(3.0f).XMVector() * 0.1f,
				1);

			//	SM_4E_IceShards_01
			//	SM_4E_IceShards_02
			//	SM_4E_IceShards_03


			testMesh.eParticleTypeID = InstanceEffect_Fountain;
			testMesh.eInstanceCount = Prototype_ModelInstance_32;
			
			// testMesh.ePassID = MeshPass_Distortion_ColorMix;
			testMesh.ePassID = MeshPass_MaskingNoising_Appear_Bright;
			testMesh.ePassID = MeshPass_MaskingNoising;
			testMesh.ePassID = MeshPass_MaskingNoising_Bright;
			

			testMesh.Particle_Power = 10.0f;
			testMesh.ParticleStartRandomPosMin = _float3(-2, 0, -2);
			testMesh.ParticleStartRandomPosMax = _float3(2, 0, 2);
			testMesh.vEmissive_SBB = _float3(0.5f,0.5f,0.1f);

			testMesh.iMaskingTextureIndex = 57;
			testMesh.iNoiseTextureIndex = 289;
			testMesh.iNoiseTextureIndex = 337;
			
			testMesh.TempBuffer_0.z = 1;

			//testMesh.FollowingTarget = m_pTransformCom;
			_Matrix mat = m_pTransformCom->Get_WorldMatrix();
			_Vector pos = mat.r[3] + mat.r[2] * 3;
			testMesh.vFixedPosition = pos;

			testMesh.bAutoTurn = true;
			testMesh.fRotSpeed_Radian = XMConvertToRadians(720);

		//	GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
		}

		{
			// toninst
			INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
				Prototype_Mesh_SM_SG_tornado,
			//	Prototype_Mesh_SM_Ghost_Chase_Sphere01,
				0.01f,
				0.5f,
				_float4(0.98f, 0.1f, 0.0f, 1),
				_float4(0.96f, 0.05f, 0.0f, 1),
				1,
				_float3(2.0f),
				_float3(2.0f),
				1);



			testMesh.eInstanceCount = Prototype_ModelInstance_32;
		//	testMesh.eParticleTypeID = InstanceEffect_Suck;
				testMesh.vNoisePushingDir = _float2(0,1);

				testMesh.ePassID = MeshPass_MaskingNoising_Appear;
			//	testMesh.ePassID = MeshPass_MaskingNoising;
			//	testMesh.ePassID = MeshPass_MaskingNoising_Bright;
			//
			//
				testMesh.Particle_Power = 3;
				_float val = 3;
				testMesh.ParticleStartRandomPosMin = _float3(-val, -2, -val);
				testMesh.ParticleStartRandomPosMax = _float3(val, 1, val);
			//	testMesh.vEmissive_SBB = _float3(1.f, 0.1f, 0.1f);
			//
				testMesh.iMaskingTextureIndex = 102;
			//	testMesh.iMaskingTextureIndex = 109;
				testMesh.iNoiseTextureIndex = 211;
				testMesh.iNoiseTextureIndex = 219;


			//testMesh.FollowingTarget = m_pTransformCom;
			_Matrix mat = m_pTransformCom->Get_WorldMatrix();
			_Vector pos = mat.r[3] + mat.r[2]*0.0f;
			testMesh.vFixedPosition = pos;

		//	testMesh.bAutoTurn = true;
		//	testMesh.fRotSpeed_Radian = XMConvertToRadians(30);
		
		//	GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
		}

		


	}

	if (KEYDOWN(DIK_C))
	{
		
		{
			// dust
			INSTPARTICLEDESC testa = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Dust_2,
				0.03f,
				2.0f,
				_float4(0.98f, 0.1f, 0.0f, 1),
				_float4(0.96f, 0.05f, 0.0f, 1),
				1,
				_float3(1, 1.5f, 1).XMVector()*0.4f,
				_float3(1, 1.5f, 1).XMVector()*0.2f,
				2);
			testa.vEmissive_SBB = _float3(1, 0.3f, 0);

			testa.eInstanceCount = Prototype_VIBuffer_Point_Instance_64;
			testa.ePassID = InstancePass_BrightColor;
			testa.ParticleStartRandomPosMin = _float3(-2, 2, -2);
			testa.ParticleStartRandomPosMax = _float3(2, 5, 2);
			testa.Particle_Power = 10;

			_Matrix mat = m_pTransformCom->Get_WorldMatrix();
			_Vector pos = mat.r[3] + mat.r[2] * 2.0f;
			testa.vFixedPosition = pos;

		//	GETPARTICLE->Create_Texture_Effect_Desc(testa, m_eNowSceneNum);
		}

		{
			// fire
			INSTPARTICLEDESC testa = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_2,
				1.f,
				0.5f,
				_float4(0.98f, 0.1f, 0.0f, 1),
				_float4(0.86f, 0.05f, 0.0f, 1),
				0,
				_float3(1, 1.5f, 1).XMVector()*0.8f,
				_float3(1, 1, 1).XMVector()*0.5f,
				0);
			testa.vEmissive_SBB = _float3(1.f, 0.1f, 1.f);

			testa.eInstanceCount = Prototype_VIBuffer_Point_Instance_32;
			//	testa.ePassID = InstancePass_BrightColor;
			//	testa.ParticleStartRandomPosMin = _float3(-1.0f, 2, -1.0f);
			//	testa.ParticleStartRandomPosMax = _float3(1.0f, 5, 1.0f);
			testa.Particle_Power = 12;

			_Matrix mat = m_pTransformCom->Get_WorldMatrix();
			_Vector pos = mat.r[3] + mat.r[2] * 2.f;
			testa.vFixedPosition = pos;

		//	GETPARTICLE->Create_Texture_Effect_Desc(testa, m_eNowSceneNum);
		}

		{
			// image
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Imgae_1,
				0,
				1.f,
				_float4(0.1f, 0.1f, 0.1f, 1.f),
				_float4(1.f),
				1,
				_float3(5.f),
				_float3(5.f),
				1);
			testTex.vEmissive_SBB = _float3(1.f, 1.f, 0);

			//	testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_64;
			testTex.ePassID = InstancePass_OriginColor;
			testTex.ParticleStartRandomPosMin = _float3(0, 0.3f, 0);
			testTex.ParticleStartRandomPosMax = _float3(0, 0.3f, 0);

			_float rotSpeed = 0.1f;
			testTex.TempBuffer_0.z = rotSpeed;
			testTex.TempBuffer_0.w = FollowingDir_Look;


			testTex.iTextureLayerIndex = 108; // TextureChange
		//	testTex.m_fAlphaTestValue = 0.001f;

			testTex.FollowingTarget = m_pTransformCom;
			GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

			testTex.ParticleStartRandomPosMin = _float3(0, 2.0f, 0);
			testTex.ParticleStartRandomPosMax = _float3(0, 2.0f, 0);
			testTex.iTextureLayerIndex = 111;
			GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);



		}



	}
#endif // _DEBUG

	return S_OK;
}
HRESULT CMonster_Gadasura_Rage::Play_SpawnEffect()
{
	if (m_SpawnEffectAdjust == 0)
	{
		m_SpawnEffectAdjust++;

		g_pGameInstance->Play3D_Sound(TEXT("UM_Spawn_03.ogg"),
			m_pTransformCom->Get_MatrixState(CTransform::STATE_POS),
			CHANNELID::CHANNEL_MONSTER, 1.0f);

		{
			Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash1, m_pTransformCom);
		}
	}

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Monster_Gadasura_Rage), TAG_COM(Com_Model), (CComponent**)&m_pModel));
	FAILED_CHECK(m_pModel->Change_AnimIndex(0));


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
	HpDesc.m_Dimensions = 1.5f;
	m_fMaxHP = 25.f;
	m_fHP = m_fMaxHP;
	g_pGameInstance->Add_GameObject_Out_of_Manager((CGameObject**)(&m_pHPUI), m_eNowSceneNum, TAG_OP(Prototype_Object_UI_HpUI), &HpDesc);


	CDissolve::DISSOLVEDESC DissolveDesc;
	DissolveDesc.pModel = m_pModel;
	DissolveDesc.eDissolveModelType = CDissolve::DISSOLVE_ANIM;
	DissolveDesc.pShader = m_pShaderCom;
	DissolveDesc.RampTextureIndex = 5;
	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Dissolve), TAG_COM(Com_Dissolve), (CComponent**)&m_pDissolve, &DissolveDesc));



	SetUp_Collider();

	m_fFrustumRadius = 2.5;

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Adjust_AnimMovedTransform(_double dDeltaTime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.98)
	{
		m_iAdjMovedIndex = 0;
		m_dAcceleration = 1;

		m_EffectAdjust = 0;

		m_bLookAtOn = true;
		m_bWeaponAttackSwitch = false;

		m_iSoundIndex = 0;

		m_bStopCoolTimeOn = false;
		if (PlayRate > 0.98 && m_bIOnceAnimSwitch == true)
		{
			m_bIOnceAnimSwitch = false;
			if (m_eMonster_State != Anim_State::MONSTER_HIT)
				m_dOnceCoolTime = 0;
			m_dInfinity_CoolTime = 0;
		}
		m_eMonster_State = Anim_State::MONSTER_IDLE;
	}

	if (PlayRate <= 0.98) //�ִϸ��̼��� ���� ��, 0.98�� ���� �������� ����
	{
		switch (iNowAnimIndex)
		{

		case 0:
		{
			m_bLookAtOn = false;
			break;
		}

		case 3:
		{
			if (PlayRate >= 0.28571 && PlayRate <= 0.571428)
			{
				m_pTransformCom->Move_Right(dDeltaTime * 1.5, m_pNavigationCom);

				if (m_iSoundIndex == 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_04.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					m_iSoundIndex++;
				}
			}
			break;
		}
		case 4:
		{
			if (PlayRate >= 0.22222 && PlayRate <= 0.44444)
			{
				m_pTransformCom->Move_Left(dDeltaTime * 1.5, m_pNavigationCom);

				if (m_iSoundIndex == 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_04.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					m_iSoundIndex++;
				}
			}
			break;
		}
		case 5:
		{//�ӵ� ���ߴ°� ��
			if (PlayRate >= 0.266666 && PlayRate <= 0.5)
			{
				_float fSpeed = g_pGameInstance->Easing(TYPE_QuinticOut, 2.7f, 1.2f, (_float)PlayRate - 0.266666f, 0.2334f); // PlayRate - 0.266666 and 0.5 - 0.266666
				m_pTransformCom->Move_Backward(dDeltaTime * fSpeed, m_pNavigationCom);

				if (m_iSoundIndex == 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_04.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					m_iSoundIndex++;
				}
			}
			break;
		}
		case 6:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_iAdjMovedIndex++;
				m_bLookAtOn = false;
			}
			break;
		}
		case 11:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bLookAtOn = false;
				m_dAcceleration = 0.7;
				m_iAdjMovedIndex++;
			}
			if (m_iSoundIndex == 0 && PlayRate > 0.238)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			break;
		}
		case 12:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bLookAtOn = false;
				m_dAcceleration = 0.7;
				m_iAdjMovedIndex++;
			}
			else if (0.f < PlayRate && PlayRate <= 0.4444)
			{
				m_pTransformCom->Move_Backward(dDeltaTime, m_pNavigationCom);

				m_fKnockbackDir.y = 0;

				m_pTransformCom->Turn_Dir(m_fKnockbackDir.XMVector(), 0.9f);
			}
			if (m_iSoundIndex == 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Rage_Gadasura_Spawn_04.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			break;
		}
		case 14:
		{
			if (m_iAdjMovedIndex == 0)
			{
				m_bLookAtOn = true;
				m_iAdjMovedIndex++;
			}
			m_pTransformCom->Move_Forward(dDeltaTime * 2.25, m_pNavigationCom);

			m_dSoundTime += dDeltaTime;
			if (m_dSoundTime >= 0.4)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_bare01.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_dSoundTime = 0;

				_Matrix mat = m_pTransformCom->Get_WorldMatrix();
				INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Imgae_2,
					0.05f,
					0.8f,
					//	_float4(0.71f, 0.29f, 0.98f, 1),
					_float4(0.98f, 0.15f, 0.84f, 1.0f),
					//	_float4(0.98f, 0.15f, 0.84f, 1.0f),
					_float4(1),
					0,
					_float3(2.9f),
					_float3(3),
					1);
				testTex.vEmissive_SBB = _float3(1, 0.01f, 1);
				testTex.vPowerDirection = mat.r[2];
				_Vector pos = mat.r[3] + mat.r[1] * 0.2f;
				testTex.vFixedPosition = pos;
				//	testTex.iTextureLayerIndex = 112;

				GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

			}
			break;
		}
		case 15:
		{
			if (m_iAdjMovedIndex == 0)
			{
				m_bLookAtOn = true;
				m_iAdjMovedIndex++;
			}
			m_pTransformCom->Move_Forward(dDeltaTime * 2.25, m_pNavigationCom);

			m_dSoundTime += dDeltaTime;
			if (m_dSoundTime >= 0.4)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_bare01.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_dSoundTime = 0;
			}
			break;
		}
		case 17:
		{

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bLookAtOn = false;
				m_iAdjMovedIndex++;
			}
			else if (PlayRate >= 0.2155 &&PlayRate <= 0.3879)
			{
				m_bWeaponAttackSwitch = true;
			}
			else if (m_iAdjMovedIndex == 1 && PlayRate >= 0.3879)
			{
				m_bWeaponAttackSwitch = false;
				m_iAdjMovedIndex++;
			}

			if (m_iSoundIndex == 0 && PlayRate > 0.2155)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 1 && PlayRate >= 0.3017)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Gada_Swing_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}


			if (m_EffectAdjust == 0 && PlayRate >= 0.1f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Attack1, m_pTransformCom);


				m_EffectAdjust++;

			}

			if (m_EffectAdjust == 1 && PlayRate >= 0.3f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Attack0, m_pTransformCom);

				m_EffectAdjust++;

			}

			

			if (m_EffectAdjust == 2 && PlayRate >= 0.35f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);

				{
					INSTPARTICLEDESC testa = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Dust_2,
						0.03f,
						2.0f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.96f, 0.05f, 0.0f, 1),
						1,
						_float3(1, 1.5f, 1).XMVector()*0.4f,
						_float3(1, 1.5f, 1).XMVector()*0.2f,
						2);
					testa.vEmissive_SBB = _float3(1, 0.3f, 0);

					testa.eInstanceCount = Prototype_VIBuffer_Point_Instance_64;
					testa.ePassID = InstancePass_BrightColor;
					testa.ParticleStartRandomPosMin = _float3(-1.0f, 2, -1.0f);
					testa.ParticleStartRandomPosMax = _float3(1.0f, 5, 1.0f);
					testa.Particle_Power = 8;

					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3] + mat.r[2] * 3.0f;
					testa.vFixedPosition = pos;

					GETPARTICLE->Create_Texture_Effect_Desc(testa, m_eNowSceneNum);
				}


				m_EffectAdjust++;
			}
			

			break;
		}
		case 18:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bLookAtOn = false;
				m_iAdjMovedIndex++;
			}
			else if (PlayRate >= 0.1754 && PlayRate <= 0.3879)
			{

				m_bWeaponAttackSwitch = true;
			}
			else if (m_iAdjMovedIndex == 1 && PlayRate >= 0.3879)
			{
				m_bWeaponAttackSwitch = false;
			}

			if (m_iSoundIndex == 0 && PlayRate > 0.2192)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_03.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 1 && PlayRate >= 0.2631)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Gada_Swing_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}

			if (m_EffectAdjust == 0 && PlayRate >= 0.3f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Attack2, m_pTransformCom);
				m_EffectAdjust++;

			}



			if (m_EffectAdjust == 1 && PlayRate >= 0.35f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);

				{
					INSTPARTICLEDESC testa = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Dust_2,
						0.03f,
						2.0f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.96f, 0.05f, 0.0f, 1),
						1,
						_float3(1, 1.5f, 1).XMVector()*0.4f,
						_float3(1, 1.5f, 1).XMVector()*0.2f,
						2);
					testa.vEmissive_SBB = _float3(1, 0.3f, 0);

					testa.eInstanceCount = Prototype_VIBuffer_Point_Instance_64;
					testa.ePassID = InstancePass_BrightColor;
					testa.ParticleStartRandomPosMin = _float3(-1.0f, 2, -1.0f);
					testa.ParticleStartRandomPosMax = _float3(1.0f, 5, 1.0f);
					testa.Particle_Power = 8;

					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3] + mat.r[2] * 3.0f;
					testa.vFixedPosition = pos;

					GETPARTICLE->Create_Texture_Effect_Desc(testa, m_eNowSceneNum);
				}


				m_EffectAdjust++;
			}


			break;
		}
		case 19:
		{
			//�޽� �ν��Ͻ� �������
			m_bLookAtOn = false;

			if (PlayRate > 0 && PlayRate <= 0.539215)
			{
				m_dAcceleration = 2.5;

				if (PlayRate >= 0.3465)
					m_bWeaponAttackSwitch = true;
			}
			else {
				m_dAcceleration = 1;
				m_bWeaponAttackSwitch = false;
			}

			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.539215)
			{
				CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC Monster_Texture_BulletDesc;

				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::GADASURA_TERRAIN_BULLET;
				Monster_Texture_BulletDesc.fSpeedPerSec = 15;
				Monster_Texture_BulletDesc.fScale = _float3(1.f, 1.f, 1.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.45f, 3.f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 0.7;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));

				ZeroMemory(&Monster_Texture_BulletDesc, sizeof(CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC));
				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::NONTEXTURE_SPHERE;
				Monster_Texture_BulletDesc.fSpeedPerSec = 0;
				Monster_Texture_BulletDesc.fScale = _float3(4.f, 4.f, 4.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.f, 2.5f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 110.1;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));

				m_iAdjMovedIndex++;
			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.4455)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_03.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 1 && PlayRate >= 0.4950)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Gada_Swing_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 2 && PlayRate >= 0.5445)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Ground_Hit_Light.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			break;
		}
		case 20:
		{

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			m_bLookAtOn = false;

			

			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.4205607)
			{
				//CMonster_Bullet_Universal::MONSTER_BULLET_UNIVERSALDESC Monster_BulletDesc;

				//Monster_BulletDesc.iBulletMeshNumber = CMonster_Bullet_Universal::GADASURA_SINKHOLE;
				//Monster_BulletDesc.fSpeedPerSec = 15.f;
				//Monster_BulletDesc.fScale = _float3(7.5f, 7.5f, 7.5f);

				//Monster_BulletDesc.Object_Transform = m_pTransformCom;
				//Monster_BulletDesc.fPositioning = _float3(0.f, 0.f, 1.8f);


				//Monster_BulletDesc.Object = this;

				//Monster_BulletDesc.dDuration = 5;

				//Monster_BulletDesc.bBornAttachOn = true;
				//Monster_BulletDesc.pBoneName = "skd_l_ball";

				//	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Bullet_Universal), &Monster_BulletDesc));

				CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC Monster_Texture_BulletDesc;

				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::NONTEXTURE_SPHERE;
				Monster_Texture_BulletDesc.fSpeedPerSec = 0;
				Monster_Texture_BulletDesc.fScale = _float3(7.f, 7.f, 7.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.f, 2.f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 0.1;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));

		
				m_iAdjMovedIndex++;
			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.4)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_05.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Gada_Swing_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 1 && PlayRate >= 0.4245)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_M1_827.mp3"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			
			if (m_EffectAdjust == 0 && PlayRate >= 0.1f)
			{
				// #TIME StopBoundAttack
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLBOUND0, m_pTransformCom);
				m_EffectAdjust++;
			}
			if (m_EffectAdjust == 1 && PlayRate >= 0.3f)
			{
				// #TIME StopBoundAttack
			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLBOUND1, m_pTransformCom);
				m_EffectAdjust++;



			}

			if (m_EffectAdjust == 2 && PlayRate >= 0.42050607)
			{

				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GM_Cash3, m_pTransformCom);

				{
					INSTPARTICLEDESC testa = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_2,
						1.f,
						0.5f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.86f, 0.05f, 0.0f, 1),
						0,
						_float3(1, 1.5f, 1).XMVector()*0.8f,
						_float3(1, 1, 1).XMVector()*0.5f,
						0);
					testa.vEmissive_SBB = _float3(1.f, 0.1f, 1.f);

					testa.eInstanceCount = Prototype_VIBuffer_Point_Instance_32;
					//	testa.ePassID = InstancePass_BrightColor;
					//	testa.ParticleStartRandomPosMin = _float3(-1.0f, 2, -1.0f);
					//	testa.ParticleStartRandomPosMax = _float3(1.0f, 5, 1.0f);
					testa.Particle_Power = 12;

					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3] + mat.r[2] * 2.f;
					testa.vFixedPosition = pos;

					GETPARTICLE->Create_Texture_Effect_Desc(testa, m_eNowSceneNum);


				}
				{
					// Stones
					INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
						Prototype_Mesh_SM_Reorgeaskil04_stone1_7,
						0.01f,
						0.5f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.96f, 0.05f, 0.0f, 1),
						4,
						_float3(5.0f, 12.f, 5.f).XMVector()*0.4f,
						_float3(3.0f).XMVector() * 0.1f,
						1);



					testMesh.eParticleTypeID = InstanceEffect_Fountain;
					testMesh.eInstanceCount = Prototype_ModelInstance_32;
					testMesh.ePassID = MeshPass_MaskingNoising_Bright;


					testMesh.Particle_Power = 10.0f;
					testMesh.ParticleStartRandomPosMin = _float3(-2, 0, -2);
					testMesh.ParticleStartRandomPosMax = _float3(2, 0, 2);
					testMesh.vEmissive_SBB = _float3(0.5f, 0.5f, 0.1f);

					testMesh.iMaskingTextureIndex = 57;
					testMesh.iNoiseTextureIndex = 289;
					testMesh.iNoiseTextureIndex = 337;

					testMesh.TempBuffer_0.z = 1;

					//testMesh.FollowingTarget = m_pTransformCom;
					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3] + mat.r[2] * 3;
					testMesh.vFixedPosition = pos;

					testMesh.bAutoTurn = true;
					testMesh.fRotSpeed_Radian = XMConvertToRadians(720);

					GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
				}



				m_EffectAdjust++;
			
			}


			break;
		}
		case 21:
		{

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.29411)
			{
				m_bWeaponAttackSwitch = true;
				m_iAdjMovedIndex++;
			}else if (m_iAdjMovedIndex == 1 && PlayRate >= 0.3529)
			{
				CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC Monster_Texture_BulletDesc;

				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::NONTEXTURE_SPHERE;
				Monster_Texture_BulletDesc.fSpeedPerSec = 0;
				Monster_Texture_BulletDesc.fScale = _float3(8.f, 8.f, 8.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.f, 3.f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 0.2;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));

				m_iAdjMovedIndex++;
			}

			if (PlayRate <= 0.588235)
			{
				m_pTransformCom->Move_Forward(dDeltaTime * 1.5, m_pNavigationCom);
			}
			else
			{
				m_bWeaponAttackSwitch = false;
			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.1176)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_bare03.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 1 && PlayRate >= 0.29411)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Gada_Swing_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				g_pGameInstance->Play3D_Sound(TEXT("EH_bare03.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 2 && PlayRate >= 0.5882)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_bare03.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 3 && PlayRate >= 0.8823)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_bare03.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}

			if (m_EffectAdjust == 0 && PlayRate >= 0.12f)
			{

				// #TIME Run Attack
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLRUN0, m_pTransformCom);
				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 1 && PlayRate >= 0.25f)
			{

				// #TIME Run Attack
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLRUN0, m_pTransformCom);
				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 2 && PlayRate >= 0.29411)
			{
				// #TIME Run Attack
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLRUN1, m_pTextureParticleTransform_Demo1);
				m_EffectAdjust++;
			}

			break;
		}
		case 22:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bLookAtOn = false;
				m_iAdjMovedIndex++;
			}

			if (m_iSoundIndex == 0 && PlayRate > 0.2702)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Ground_Hit_Light.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 1 && PlayRate > 0.4054)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Scream_Pain_05.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}
			break;
		}
		case 23:
		{

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));


			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.2)
			{
				//m_bWeaponAttackSwitch = true;

				CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC Monster_Texture_BulletDesc;

				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::GADASURA_TERRAIN_BULLET;
				Monster_Texture_BulletDesc.fSpeedPerSec = 15;
				Monster_Texture_BulletDesc.fScale = _float3(1.f, 1.f, 1.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.45f, 3.f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 0.7;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));


				ZeroMemory(&Monster_Texture_BulletDesc, sizeof(CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC));
				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::NONTEXTURE_SPHERE;
				Monster_Texture_BulletDesc.fSpeedPerSec = 0;
				Monster_Texture_BulletDesc.fScale = _float3(4.f, 4.f, 4.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.f, 2.5f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 110.1;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));

				   
				m_iAdjMovedIndex++;
			}
			else if (m_iAdjMovedIndex == 1 && PlayRate >= 0.4689655)
			{
				CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC Monster_Texture_BulletDesc;

				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::GADASURA_TERRAIN_BULLET;
				Monster_Texture_BulletDesc.fSpeedPerSec = 15;
				Monster_Texture_BulletDesc.fScale = _float3(1.f, 1.f, 1.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.45f, 3.f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 0.7;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));


				ZeroMemory(&Monster_Texture_BulletDesc, sizeof(CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC));
				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::NONTEXTURE_SPHERE;
				Monster_Texture_BulletDesc.fSpeedPerSec = 0;
				Monster_Texture_BulletDesc.fScale = _float3(4.f, 4.f, 4.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.f, 2.5f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 110.1;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));

				m_iAdjMovedIndex++;
			}
			else if (m_iAdjMovedIndex == 2 && PlayRate >= 0.751724)
			{
				CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC Monster_Texture_BulletDesc;

				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::GADASURA_TERRAIN_BULLET;
				Monster_Texture_BulletDesc.fSpeedPerSec = 15;
				Monster_Texture_BulletDesc.fScale = _float3(1.f, 1.f, 1.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.45f, 3.f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 0.7;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));


				ZeroMemory(&Monster_Texture_BulletDesc, sizeof(CMonster_Texture_Bullet::MONSTER_TEXTURE_BULLETDESC));
				Monster_Texture_BulletDesc.iBulletTextureNumber = CMonster_Texture_Bullet::NONTEXTURE_SPHERE;
				Monster_Texture_BulletDesc.fSpeedPerSec = 0;
				Monster_Texture_BulletDesc.fScale = _float3(4.f, 4.f, 4.f);

				Monster_Texture_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_Texture_BulletDesc.fPositioning = _float3(0.f, 0.f, 2.5f);


				Monster_Texture_BulletDesc.Object = this;

				Monster_Texture_BulletDesc.dDuration = 110.1;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Texture_Bullet), &Monster_Texture_BulletDesc));
			
				m_iAdjMovedIndex++;
			}
			else if(m_iAdjMovedIndex == 3) {
				m_bLookAtOn = false;
				//m_bWeaponAttackSwitch = false;
			}

//// SOUND //// 
			switch (m_iSoundIndex)
			{
			case 0: {
				if (PlayRate >= 0.1724)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Gada_Swing_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 1.f);
					m_iSoundIndex++;
				}
				break;
			}
			case 1: {
				if (PlayRate >= 0.2)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Ground_Hit_Heavy.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					m_iSoundIndex++;
				}
				break;
			}
			case 2: {
				if (PlayRate >= 0.4275)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Gada_Swing_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 1.f);
					m_iSoundIndex++;
				}
				break;
			}
			case 3: {
				if (PlayRate >= 0.4689655)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Ground_Hit_Heavy.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					m_iSoundIndex++;
				}
				break;
			}
			case 4: {
				if (PlayRate >= 0.7379)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Charge_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Gada_Swing_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 1.f);
					m_iSoundIndex++;
				}
				break;
			}
			case 5: {
				if (PlayRate >= 0.751724)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Gadasura_Ground_Hit_Heavy.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					m_iSoundIndex++;
				}
				break;
			}
			default:
				break;
				}
				//// SOUND //// 
				
			// Routin
			if (m_EffectAdjust == 0 && PlayRate >= 0)
			{
				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 1 && PlayRate >= 0.08)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE0, m_pTransformCom);
				m_EffectAdjust++;
			}
			if (m_EffectAdjust == 2 && PlayRate >= 0.2)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash0, m_pTransformCom);

				{
					// Stones
					INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
						Prototype_Mesh_SM_Reorgeaskil04_stone1_7,
						0.01f,
						0.5f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.96f, 0.05f, 0.0f, 1),
						4,
						_float3(5.0f, 12.f, 5.f).XMVector()*0.4f,
						_float3(3.0f).XMVector() * 0.1f,
						1);



					testMesh.eParticleTypeID = InstanceEffect_Fountain;
					testMesh.eInstanceCount = Prototype_ModelInstance_32;
					testMesh.ePassID = MeshPass_MaskingNoising_Bright;


					testMesh.Particle_Power = 10.0f;
					testMesh.ParticleStartRandomPosMin = _float3(-2, 0, -2);
					testMesh.ParticleStartRandomPosMax = _float3(2, 0, 2);
					testMesh.vEmissive_SBB = _float3(0.5f, 0.5f, 0.1f);

					testMesh.iMaskingTextureIndex = 57;
					testMesh.iNoiseTextureIndex = 289;
					testMesh.iNoiseTextureIndex = 337;

					testMesh.TempBuffer_0.z = 1;

					//testMesh.FollowingTarget = m_pTransformCom;
					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3] + mat.r[2] * 3;
					testMesh.vFixedPosition = pos;

					testMesh.bAutoTurn = true;
					testMesh.fRotSpeed_Radian = XMConvertToRadians(720);

					GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
				}

				m_EffectAdjust++;

			}

			if (m_EffectAdjust == 3 && PlayRate >= 0.21)
			{
				
				//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE2, m_pTransformCom);
				
				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 4 && PlayRate >= 0.375)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE0, m_pTransformCom);

				m_EffectAdjust++;
			}
			if (m_EffectAdjust == 5 && PlayRate >= 0.4689655)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash0, m_pTransformCom);
				{
					// Stones
					INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
						Prototype_Mesh_SM_Reorgeaskil04_stone1_7,
						0.01f,
						0.5f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.96f, 0.05f, 0.0f, 1),
						4,
						_float3(5.0f, 12.f, 5.f).XMVector()*0.4f,
						_float3(3.0f).XMVector() * 0.1f,
						1);



					testMesh.eParticleTypeID = InstanceEffect_Fountain;
					testMesh.eInstanceCount = Prototype_ModelInstance_32;
					testMesh.ePassID = MeshPass_MaskingNoising_Bright;


					testMesh.Particle_Power = 10.0f;
					testMesh.ParticleStartRandomPosMin = _float3(-2, 0, -2);
					testMesh.ParticleStartRandomPosMax = _float3(2, 0, 2);
					testMesh.vEmissive_SBB = _float3(0.5f, 0.5f, 0.1f);

					testMesh.iMaskingTextureIndex = 57;
					testMesh.iNoiseTextureIndex = 289;
					testMesh.iNoiseTextureIndex = 337;

					testMesh.TempBuffer_0.z = 1;

					//testMesh.FollowingTarget = m_pTransformCom;
					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3] + mat.r[2] * 3;
					testMesh.vFixedPosition = pos;

					testMesh.bAutoTurn = true;
					testMesh.fRotSpeed_Radian = XMConvertToRadians(720);

					GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
				}

				m_EffectAdjust++;

			}

			if (m_EffectAdjust == 6 && PlayRate >= 0.5)
			{
			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE2, m_pTransformCom);
				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 7 && PlayRate >= 0.62)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE0, m_pTransformCom);

				m_EffectAdjust++;
			}
			if (m_EffectAdjust == 8 && PlayRate >= 0.751724)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash0, m_pTransformCom);

				{
					// Stones
					INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
						Prototype_Mesh_SM_Reorgeaskil04_stone1_7,
						0.01f,
						0.5f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.96f, 0.05f, 0.0f, 1),
						4,
						_float3(5.0f, 12.f, 5.f).XMVector()*0.4f,
						_float3(3.0f).XMVector() * 0.1f,
						1);



					testMesh.eParticleTypeID = InstanceEffect_Fountain;
					testMesh.eInstanceCount = Prototype_ModelInstance_32;
					testMesh.ePassID = MeshPass_MaskingNoising_Bright;


					testMesh.Particle_Power = 10.0f;
					testMesh.ParticleStartRandomPosMin = _float3(-2, 0, -2);
					testMesh.ParticleStartRandomPosMax = _float3(2, 0, 2);
					testMesh.vEmissive_SBB = _float3(0.5f, 0.5f, 0.1f);

					testMesh.iMaskingTextureIndex = 57;
					testMesh.iNoiseTextureIndex = 289;
					testMesh.iNoiseTextureIndex = 337;

					testMesh.TempBuffer_0.z = 1;

					//testMesh.FollowingTarget = m_pTransformCom;
					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3] + mat.r[2] * 3;
					testMesh.vFixedPosition = pos;

					testMesh.bAutoTurn = true;
					testMesh.fRotSpeed_Radian = XMConvertToRadians(720);

					GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
				}

				m_EffectAdjust++;

			}


			break;
		}
		case 24:
		{
			m_dSoundTime += dDeltaTime;

			if (m_dSoundTime >= 0.57)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_bare03.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_dSoundTime = 0;
			}

			m_pTransformCom->Move_Forward(dDeltaTime * 0.6, m_pNavigationCom);

			break;
		}
		case 25:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate <= 0.9574)
			{
				m_bLookAtOn = false;
				m_iAdjMovedIndex++;
			}
			else if(PlayRate >= 0.9574 && PlayRate <= 0.98)
			{
				m_bLookAtOn = true;
				m_pTransformCom->Move_Forward(dDeltaTime * 2.25, m_pNavigationCom);
			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.3191)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Rage_Gadasura_Scream_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.7f);
				m_iSoundIndex++;
			}
			else if (m_iSoundIndex == 1 && PlayRate >= 0.9574)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_bare01.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}

			if (m_EffectAdjust == 0 && PlayRate >= 0.4)
			{
			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash1, m_pTransformCom);

				m_EffectAdjust++;
			}

			break;
		}
		case 26:
		{
			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_EffectAdjust == 0 && PlayRate > 0.1f)
			{

			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash0, m_pTransformCom);


				m_EffectAdjust++;
			}
	
			
			if (m_EffectAdjust == 1 && PlayRate >= 0.7)
			{

				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash2, m_pTransformCom);

				

				{
					// image
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Imgae_1,
						0.1f,
						1.f,
						_float4(1, 1, 1, 1),
						_float4(1, 1, 1, 0.1f),
						1,
						_float3(7.f),
						_float3(7.f),
						1);
					testTex.vEmissive_SBB = _float3(1.f, 0.1f, 1.f);

					//	testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_64;
					testTex.ePassID = InstancePass_OriginColor;
					testTex.ParticleStartRandomPosMin = _float3(0, 0.2f, 0);
					testTex.ParticleStartRandomPosMax = _float3(0, 0.2f, 0);

					testTex.TempBuffer_0.z = 50;
					testTex.TempBuffer_0.w = FollowingDir_Look;

					testTex.iTextureLayerIndex = 108; // TextureChange
					testTex.m_fAlphaTestValue = 0.01f;

					testTex.FollowingTarget = m_pTransformCom;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				}


				m_EffectAdjust++;

			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.4477)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Rage_Gadasura_Scream_03.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_EFFECT, 0.7f);
				m_iSoundIndex++;
			}



			break;
		}
		
		case 27:
		{
			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f,  Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_iAdjMovedIndex == 0 && PlayRate > 0) //0.4347826
			{

				CGadasura_Rage_Hollogram::GADASURA_HOLLOGRAMDESC HollogramDesc;

				HollogramDesc.Object = this;
				HollogramDesc.dDuration = 5;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE7, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Gadasura_Rage_Hollogram),&HollogramDesc));
				m_iAdjMovedIndex++;
			}
			
			if (m_EffectAdjust == 0)
			{

				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash3, m_pTransformCom);
				
				{
					INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
						Prototype_Mesh_SM_meteo,
						0.01f,
						0.5f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.96f, 0.05f, 0.0f, 1),
						4,
						_float3(5).XMVector() * 2.f,
						_float3(5).XMVector() * 0.2f,
						1);


					testMesh.eParticleTypeID = InstanceEffect_Fountain;
					testMesh.eInstanceCount = Prototype_ModelInstance_32;

					// testMesh.ePassID = MeshPass_Distortion_ColorMix;
					testMesh.ePassID = MeshPass_MaskingNoising_Appear_Bright;
					testMesh.ePassID = MeshPass_MaskingNoising;
					testMesh.ePassID = MeshPass_MaskingNoising_Bright;


					testMesh.Particle_Power = 12.f;
					testMesh.ParticleStartRandomPosMin = _float3(-2, 0, -2);
					testMesh.ParticleStartRandomPosMax = _float3(2, 0, 2);
					testMesh.vEmissive_SBB = _float3(1.f, 0.1f, 0.1f);

					testMesh.iMaskingTextureIndex = 57;
					testMesh.iNoiseTextureIndex = 289;
					testMesh.iNoiseTextureIndex = 337;


					//testMesh.FollowingTarget = m_pTransformCom;
					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3];
					testMesh.vFixedPosition = pos;

					testMesh.bAutoTurn = true;
					testMesh.fRotSpeed_Radian = XMConvertToRadians(720);

					GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
				}

				m_EffectAdjust++;
			}


			break;
		}
		case 28:
		{
			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(1.0f, 0.0f, 0.0f,  Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.7826)
			{

				CGadasura_Rage_Hollogram::GADASURA_HOLLOGRAMDESC HollogramDesc;

				HollogramDesc.Object = this;
				HollogramDesc.dDuration = 5;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE7, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Gadasura_Rage_Hollogram), &HollogramDesc));
				m_iAdjMovedIndex++;
			}

			if (m_EffectAdjust == 0 )
			{

				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash2, m_pTransformCom);

				{
					// image
					INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_Imgae_1,
						0.1f,
						1.f,
						_float4(1, 1, 1, 1),
						_float4(1, 1, 1, 0.1f),
						1,
						_float3(7.f),
						_float3(7.f),
						1);
					testTex.vEmissive_SBB = _float3(1.f, 0.1f, 1.f);

					//	testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_64;
					testTex.ePassID = InstancePass_OriginColor;
					testTex.ParticleStartRandomPosMin = _float3(0, 0.2f, 0);
					testTex.ParticleStartRandomPosMax = _float3(0, 0.2f, 0);

					testTex.TempBuffer_0.z = 50;
					testTex.TempBuffer_0.w = FollowingDir_Look;


					testTex.iTextureLayerIndex = 108; // TextureChange
					testTex.m_fAlphaTestValue = 0.01f;

					testTex.FollowingTarget = m_pTransformCom;
					GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);

				}

				m_EffectAdjust++;
							   				 			  
			}

			if (m_EffectAdjust == 1 && PlayRate > 0.7826)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash3, m_pTransformCom);


				{
					INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
						Prototype_Mesh_SM_meteo,
						0.01f,
						0.5f,
						_float4(0.98f, 0.1f, 0.0f, 1),
						_float4(0.96f, 0.05f, 0.0f, 1),
						4,
						_float3(5).XMVector() * 2.f,
						_float3(5).XMVector() * 0.2f,
						1);


					testMesh.eParticleTypeID = InstanceEffect_Fountain;
					testMesh.eInstanceCount = Prototype_ModelInstance_32;

					// testMesh.ePassID = MeshPass_Distortion_ColorMix;
					testMesh.ePassID = MeshPass_MaskingNoising_Appear_Bright;
					testMesh.ePassID = MeshPass_MaskingNoising;
					testMesh.ePassID = MeshPass_MaskingNoising_Bright;


					testMesh.Particle_Power = 12.f;
					testMesh.ParticleStartRandomPosMin = _float3(-2, 0, -2);
					testMesh.ParticleStartRandomPosMax = _float3(2, 0, 2);
					testMesh.vEmissive_SBB = _float3(1.f, 0.1f, 0.1f);

					testMesh.iMaskingTextureIndex = 57;
					testMesh.iNoiseTextureIndex = 289;
					testMesh.iNoiseTextureIndex = 337;


					//testMesh.FollowingTarget = m_pTransformCom;
					_Matrix mat = m_pTransformCom->Get_WorldMatrix();
					_Vector pos = mat.r[3];
					testMesh.vFixedPosition = pos;

					testMesh.bAutoTurn = true;
					testMesh.fRotSpeed_Radian = XMConvertToRadians(720);

					GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
				}
				m_EffectAdjust++;
			}


			break;
		}

		default:
			break;

		}

	}

	m_iOldAnimIndex = iNowAnimIndex;
	return S_OK;
}

CMonster_Gadasura_Rage * CMonster_Gadasura_Rage::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CMonster_Gadasura_Rage*	pInstance = NEW CMonster_Gadasura_Rage(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Gadasura_Rage");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMonster_Gadasura_Rage::Clone(void * pArg)
{
	CMonster_Gadasura_Rage*	pInstance = NEW CMonster_Gadasura_Rage(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Gadasura_Rage");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonster_Gadasura_Rage::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
	Safe_Release(m_pColliderCom);
	Safe_Release(m_pHPUI);
	Safe_Release(m_pWeapon);
	Safe_Release(m_pDissolve);

	Safe_Release(m_pTextureParticleTransform_Hand);
	Safe_Release(m_pTextureParticleTransform_Demo1);
	Safe_Release(m_pTextureParticleTransform_Demo2);
	Safe_Release(m_pTextureParticleTransform_Demo3);

}