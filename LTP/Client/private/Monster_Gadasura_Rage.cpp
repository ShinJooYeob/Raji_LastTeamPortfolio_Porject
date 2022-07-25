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
	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(216.357f, 29.2f, 188.583f));

	m_pNavigationCom->FindCellIndex(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));

	m_pTransformCom->LookAtExceptY(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS), 1);
	//////////////////////////////

	return S_OK;
}

_int CMonster_Gadasura_Rage::Update(_double dDeltaTime)
{

	if (__super::Update(dDeltaTime) < 0)return -1;

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

	if (m_pWeapon != nullptr)
		m_pWeapon->Update(dDeltaTime);

	Update_Collider(dDeltaTime);

	return _int();
}

_int CMonster_Gadasura_Rage::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;

	//////////
	if (m_bIsOnScreen)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}

	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this, m_pTransformCom, m_pShaderCom, m_pModel));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

#ifdef _DEBUG
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));
#endif

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));


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
		FAILED_CHECK(m_pModel->Render(m_pShaderCom, 3, i, "g_BoneMatrices"));
	}



	return _int();
}

_int CMonster_Gadasura_Rage::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;

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

	m_dSpecial_CoolTime = 0;
	m_dOnceCoolTime = 0;
	m_dInfinity_CoolTime = 0;


	m_bIOnceAnimSwitch = true;
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

	if (m_fHP <= 0)
	{
		Set_IsDead();
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
	MonsterWeaponDesc.eAttachedDesc.Initialize_AttachedDesc(this, "skd_r_wrist", _float3(1, 1, 1), _float3(0, 0, 0), _float3(-2.535f, -0.075f, -3.03f));

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
	//�ѹ��� �����ϴ� �ִϸ��̼�

	m_dOnceCoolTime += dDeltaTime;
	m_dSpecial_CoolTime += dDeltaTime;

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
	m_dInfinity_CoolTime += dDeltaTime;
	if (m_dInfinity_CoolTime >= 1.5)
	{
		m_iInfinityPattern = rand() % 7;


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
	// #DEBUG PatternSET
//	m_iOncePattern = 51;
//	m_iOncePattern = 0;
	if(KEYPRESS(DIK_B))
		m_iOncePattern = 0;

	switch (m_iOncePattern)
	{
	case 0:
		m_iOnceAnimNumber = 26; //Hollogram start
		m_bComboAnimSwitch = true;
		break;
	case 1:
		m_iOnceAnimNumber = 27; //Hollogram Run
		m_bComboAnimSwitch = true;
		break;
	case 2:
		m_iOnceAnimNumber = 28; //Hollogram Run
		m_bComboAnimSwitch = true;
		break;
	case 3:
		m_iOnceAnimNumber = 29; //Hollogram End
		m_bComboAnimSwitch = false;
		break;
	case 4:
		m_iOnceAnimNumber = 23; //TripleSmash
		m_bComboAnimSwitch = true;
		break;
	case 5:
		m_iOnceAnimNumber = 5; //Back
		m_bComboAnimSwitch = false;
		break;
	case 6:
		m_iOnceAnimNumber = 25; //Rage Run
		m_bComboAnimSwitch = true;
		break;
	case 7:
		m_iOnceAnimNumber = 14; //Rage Run
		m_bComboAnimSwitch = true;
		break;
	case 8:
		m_iOnceAnimNumber = 21; //Rage Run Attack
		m_bComboAnimSwitch = true;
		break;
	case 9:
		m_iOnceAnimNumber = 3; //Right Move
		m_bComboAnimSwitch = false;
		break;
	case 10:
		m_iOnceAnimNumber = 17; //Attack1 
		m_bComboAnimSwitch = true;
		break;
	case 11:
		m_iOnceAnimNumber = 25; //Rage Run Start
		m_bComboAnimSwitch = true;
		break;
	case 12:
		m_iOnceAnimNumber = 15; //Rage Run
		m_bComboAnimSwitch = true;
		break;
	case 13:
		m_iOnceAnimNumber = 21; //Rage Run Attack
		m_bComboAnimSwitch = true;
		break;
	case 14:
		m_iOnceAnimNumber = 23; //TripleSmash
		m_bComboAnimSwitch = true;
		break;
	case 15:
		m_iOnceAnimNumber = 4; //Left Move
		m_bComboAnimSwitch = false;
		break;
	case 16:
		m_iOnceAnimNumber = 22; //Taunt
		m_bComboAnimSwitch = false;
		break;
	case 17:
		m_iOnceAnimNumber = 18; //Attack2
		m_bComboAnimSwitch = false;
		break;
	case 40:
		m_iOnceAnimNumber = 11; //right hit
		break;
	case 41:
		m_iOnceAnimNumber = 12; //HeavyHit
		break;
	case 42:
		m_iOnceAnimNumber = 6; //groggy
		break;
	case 51:
		m_iOnceAnimNumber = 20; //stomp Attack
		m_bComboAnimSwitch = false;
		break;

	}

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Pattern_Change()
{

	m_iOncePattern += 1;

	if (m_iOncePattern >= 18)
	{
		m_iOncePattern = 0; //OncePattern Random
	}


	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Infinity_AnimMotion(_double dDeltaTime)
{
	switch (m_iInfinityPattern)
	{
	case 0:
		m_iInfinityAnimNumber = 0;
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
	default:
		m_iInfinityAnimNumber = 0;
		break;
	}

	return S_OK;
}

HRESULT CMonster_Gadasura_Rage::Special_Trigger(_double dDeltaTime)
{

	if (m_fDistance < 2 && m_dSpecial_CoolTime > 15)
	{
		m_dSpecial_CoolTime = 0;
		m_dOnceCoolTime = 0;
		m_dInfinity_CoolTime = 0;

		m_bIOnceAnimSwitch = true;
		m_iOncePattern = 51;
	}

	if (m_fDistance > 8 && m_dSpecial_CoolTime > 7)
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
	NULL_CHECK_RETURN(m_pTextureParticleTransform_Hand, E_FAIL);

	m_pTextureParticleTransform_Demo1 = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_RETURN(m_pTextureParticleTransform_Demo1, E_FAIL);

	m_pTextureParticleTransform_Demo2 = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_RETURN(m_pTextureParticleTransform_Demo2, E_FAIL);

	m_pTextureParticleTransform_Demo3 = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_RETURN(m_pTextureParticleTransform_Demo3, E_FAIL);


	return S_OK;
}
HRESULT CMonster_Gadasura_Rage::Update_Particle(_double timer)
{
	_Matrix mat_World = m_pTransformCom->Get_WorldMatrix();
	ATTACHEDESC boneDesc = m_pWeapon->Get_WeaponDesc().eAttachedDesc;
	_Vector Vec_WeaponPos = boneDesc.Get_AttachedBoneWorldPosition_BlenderFixed();
	_Matrix mat_Weapon = boneDesc.Caculate_AttachedBoneMatrix_BlenderFixed();



	mat_World.r[0] = XMVector3Normalize(mat_World.r[0]);
	mat_World.r[1] = XMVector3Normalize(mat_World.r[1]);
	mat_World.r[2] = XMVector3Normalize(mat_World.r[2]);
	m_pTextureParticleTransform_Demo1->Set_Matrix(mat_World);


	m_pTextureParticleTransform_Hand->Set_Matrix(mat_Weapon);

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
	m_fMaxHP = 15.f;
	m_fHP = m_fMaxHP;
	g_pGameInstance->Add_GameObject_Out_of_Manager((CGameObject**)(&m_pHPUI), m_eNowSceneNum, TAG_OP(Prototype_Object_UI_HpUI), &HpDesc);


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
		case 3:
		{
			if (PlayRate >= 0.28571 && PlayRate <= 0.571428)
				m_pTransformCom->Move_Right(dDeltaTime * 1.5, m_pNavigationCom);
			break;
		}
		case 4:
		{
			if (PlayRate >= 0.22222 && PlayRate <= 0.44444)
				m_pTransformCom->Move_Left(dDeltaTime * 1.5, m_pNavigationCom);
			break;
		}
		case 5:
		{//�ӵ� ���ߴ°� ��
			if (PlayRate >= 0.266666 && PlayRate <= 0.5)
			{
				_float fSpeed = g_pGameInstance->Easing(TYPE_QuinticOut, 2.7f, 1.2f, (_float)PlayRate - 0.266666f, 0.2334f); // PlayRate - 0.266666 and 0.5 - 0.266666
				m_pTransformCom->Move_Backward(dDeltaTime * fSpeed, m_pNavigationCom);
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
				m_dAcceleration = 0.7;
				m_iAdjMovedIndex++;
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
			else if (0.f < PlayRate && PlayRate <= 0.8636)
			{
				m_pTransformCom->Move_Backward(dDeltaTime, m_pNavigationCom);

				m_fKnockbackDir.y = 0;

				m_pTransformCom->Turn_Dir(m_fKnockbackDir.XMVector(), 0.9f);
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
			break;
		}
		case 17:
		{
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


			if (m_EffectAdjust == 0 && PlayRate >= 0.1f)
			{
			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLRUN0, m_pTransformCom);
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash2, m_pTextureParticleTransform_Hand);
				//Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash3, m_pTextureParticleTransform_Hand);


				// #TIME Attack1
				m_EffectAdjust++;
			}
			//if (m_EffectAdjust == 1 && PlayRate >= 0.3f)
			//{
			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLBOUND1, m_pTransformCom);
			//	m_EffectAdjust++;
			//}





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
				m_iAdjMovedIndex++;
			}
			break;
		}
		case 20:
		{
			m_bLookAtOn = false;

			

			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.4205607)
			{
				CMonster_Bullet_Universal::MONSTER_BULLET_UNIVERSALDESC Monster_BulletDesc;

				Monster_BulletDesc.iBulletMeshNumber = CMonster_Bullet_Universal::GADASURA_SINKHOLE;
				Monster_BulletDesc.fSpeedPerSec = 15.f;
				Monster_BulletDesc.fScale = _float3(7.5f, 7.5f, 7.5f);

				Monster_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_BulletDesc.fPositioning = _float3(0.f, 0.f, 1.8f);


				Monster_BulletDesc.Object = this;

				Monster_BulletDesc.dDuration = 5;

				Monster_BulletDesc.bBornAttachOn = true;
				Monster_BulletDesc.pBoneName = "skd_l_ball";

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Bullet_Universal), &Monster_BulletDesc));

		
				m_iAdjMovedIndex++;
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
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLBOUND1, m_pTransformCom);
				m_EffectAdjust++;
			}

			break;
		}
		case 21:
		{
			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(0.27f, 0.94f, 0.38f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.29411)
			{
				m_bWeaponAttackSwitch = true;
				m_iAdjMovedIndex++;
			}

			if (PlayRate <= 0.588235)
			{
				m_pTransformCom->Move_Forward(dDeltaTime * 1.5);
			}
			else
			{
				m_bWeaponAttackSwitch = false;
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
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash1, m_pTextureParticleTransform_Demo1);
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
			break;
		}
		case 23:
		{
			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(0.7f, 0.51f, 0.38f, Value), _float4(Value, Value*0.7f, Value, 0.9f));


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
			
				m_iAdjMovedIndex++;
			}
			else if(m_iAdjMovedIndex == 3) {
				m_bLookAtOn = false;
				//m_bWeaponAttackSwitch = false;
			}

			if (m_EffectAdjust == 0 && PlayRate >= 0.08f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE0, m_pTransformCom);
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE2, m_pTransformCom);


				// test

			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE0, m_pTransformCom); // traill
			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE2, m_pTransformCom); //fire
			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);

			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLRUN0, m_pTransformCom); // WIND
			//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash0, m_pTransformCom); // 

				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 1 && PlayRate >= 0.2)
			{
				// #TIME SmashAttack
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);

				m_EffectAdjust++;

			}

			if (m_EffectAdjust == 2 && PlayRate >= 0.38f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE0, m_pTransformCom);
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE2, m_pTransformCom);

				m_EffectAdjust++;

			}
			if (m_EffectAdjust == 3 && PlayRate >= 0.4689655)
			{
				// #TIME SmashAttack
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);

				m_EffectAdjust++;

			}

			if (m_EffectAdjust == 4 && PlayRate >= 0.62f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE0, m_pTransformCom);
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE2, m_pTransformCom);

				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 5 && PlayRate >= 0.751724)
			{
				// #TIME SmashAttack
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);

				m_EffectAdjust++;

			}

			break;
		}
		case 24:
		{
			m_pTransformCom->Move_Forward(dDeltaTime * 0.6, m_pNavigationCom);

			break;
		}
		case 25:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.9574)
			{
				m_bLookAtOn = false;
				m_iAdjMovedIndex++;
			}
			else if(PlayRate >= 0.9574 && PlayRate <= 0.98){
				m_bLookAtOn = true;
				m_pTransformCom->Move_Forward(dDeltaTime * 2.25, m_pNavigationCom);
			}

			break;
		}
		case 26:
		{
			if (m_EffectAdjust == 0 && PlayRate > 0.1f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_SKILLTRIPLE3, m_pTransformCom);
				m_EffectAdjust++;
			}

			break;
		}
		
		case 27:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0) //0.4347826
			{

				CGadasura_Rage_Hollogram::GADASURA_HOLLOGRAMDESC HollogramDesc;

				HollogramDesc.Object = this;
				HollogramDesc.dDuration = 5;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE7, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Gadasura_Rage_Hollogram),&HollogramDesc));
				m_iAdjMovedIndex++;
			}

			if (m_EffectAdjust == 0 && PlayRate > 0.2f)
			{
					Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash3, m_pTransformCom);
				m_EffectAdjust++;
			}
			if (m_EffectAdjust == 1 && PlayRate > 0.6f)
			{
					Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_GL_Cash3, m_pTransformCom);
				m_EffectAdjust++;
			}

			break;
		}
		case 28:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.7826)
			{

				CGadasura_Rage_Hollogram::GADASURA_HOLLOGRAMDESC HollogramDesc;

				HollogramDesc.Object = this;
				HollogramDesc.dDuration = 5;

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE7, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Gadasura_Rage_Hollogram), &HollogramDesc));
				m_iAdjMovedIndex++;
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

	Safe_Release(m_pTextureParticleTransform_Hand);
	Safe_Release(m_pTextureParticleTransform_Demo1);
	Safe_Release(m_pTextureParticleTransform_Demo2);
	Safe_Release(m_pTextureParticleTransform_Demo3);

}