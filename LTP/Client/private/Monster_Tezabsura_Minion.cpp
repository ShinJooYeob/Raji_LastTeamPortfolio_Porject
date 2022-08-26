#include "stdafx.h"
#include "..\public\Monster_Tezabsura_Minion.h"
#include "Monster_Bullet_Universal.h"
#include "HpUI.h"

CMonster_Tezabsura_Minion::CMonster_Tezabsura_Minion(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CMonster(pDevice, pDeviceContext)
{
}

CMonster_Tezabsura_Minion::CMonster_Tezabsura_Minion(const CMonster_Tezabsura_Minion & rhs)
	: CMonster(rhs)
{
}

HRESULT CMonster_Tezabsura_Minion::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	if (pArg != nullptr)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, *((_float3*)pArg));

	m_pTransformCom->Rotation_CW(XMVectorSet(0, 1, 0, 0), XMConvertToRadians(170));


	SetUp_Info();


	m_fJumpPower = 4.5f;


#ifdef _DEBUG
	//////////////////testPosition
	//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(493.f, 7.100010f, 103.571f)); // Stage2
	//m_pNavigationCom->FindCellIndex(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
	//////////////////
#endif

	// Partilce
	Set_DealyDIssolveTime(3.0f, 0.5f);

	return S_OK;
}

_int CMonster_Tezabsura_Minion::Update(_double dDeltaTime)
{

	if (__super::Update(dDeltaTime) < 0)return -1;

	if (__super::Update(dDeltaTime) == UPDATE_SKIP)
		return UPDATE_SKIP;

	if (m_SpawnDealytime <= 0 && m_bIsSpawnDissolove == false)
	{
		m_pDissolve->Set_DissolveOn(true, m_SpawnDissolveTime);
		m_pDissolve->Update_Dissolving(dDeltaTime);

		if (m_pDissolve->Get_IsDissolving() == false)
			m_bIsSpawnDissolove = true;
	}

	if (m_fHP <= 0)
	{
		m_bRepelOff = true;
		m_bLookAtOn = false;
		m_pDissolve->Update_Dissolving(dDeltaTime);
		m_pDissolve->Set_DissolveOn(false, 2.f);

		m_dDissolveTime += dDeltaTime;

		if (m_bDieSound == false && m_dDissolveTime >= 1.)
		{
			g_pGameInstance->Play3D_Sound(TEXT("EH_Wave_Tezabsura_Damage_2.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 1.f);
			m_bDieSound = true;
		}

		if (m_dDissolveTime >= 2)
		{
			Set_IsDead();
		}
	}

	if (g_pGameInstance->Get_DIKeyState(DIK_X)&DIS_Down)
	{


		GetSingle(CUtilityMgr)->Create_MeshInstance(m_eNowSceneNum, m_vecMeshParticleDesc[0]);

	}


	//������ ������ bBlockAnimUntilReturnChange���� true�� �����ؼ� �����۵��� �ȴٸ� false�� �ȴ�.
	//m_pModel->Change_AnimIndex();
	//m_pModel->Change_AnimIndex_ReturnTo(); //� �ִϸ��̼��� ������ Ư�� �ִϸ��̼����� ����
	//m_pModel->Change_AnimIndex_ReturnTo_Must(); //�߰��� �ִϸ��̼��� ĵ���ϰ� �ٸ� �ִϸ��̼��� ���۽�Ŵ
	//m_pModel->Change_AnimIndex_UntilTo(); //1~5���� �����ٰ� ��ɾ �Է��ϸ� 1~5���� ���ư�
	//m_pModel->Change_AnimIndex_UntilNReturn();//1~5���� ������ �� ���� Ư�� �ִϸ��̼����� Return ��ų ���
	//m_pModel->Change_AnimIndex_UntilNReturn_Must(); //1~5���� ������ �� ���� Ư�� �ִϸ��̼����� Return ��ų �� ������ �ٸ� �ִϸ��̼��� ���۽�ų �� ����



	PlayAnim(dDeltaTime);
	Jumping(dDeltaTime);

	m_bIsOnScreen = g_pGameInstance->IsNeedToRender(m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS), m_fFrustumRadius);

	//if (m_pModel->Get_NowAnimIndex() == 8 ||m_pModel->Get_NowAnimIndex() == 9 || m_pModel->Get_NowAnimIndex() == 10)
	//{
	//FAILED_CHECK(m_pModel->Update_AnimationClip(dDeltaTime * m_dAcceleration * 1.6452f, m_bIsOnScreen));
	//}
	//else
	//{
	//FAILED_CHECK(m_pModel->Update_AnimationClip(dDeltaTime * m_dAcceleration, m_bIsOnScreen));
	//}
	if (m_fHP > 0)
	{
		FAILED_CHECK(m_pModel->Update_AnimationClip(dDeltaTime * m_dAcceleration, m_bIsOnScreen));
	}
	FAILED_CHECK(Adjust_AnimMovedTransform(dDeltaTime));

	if (m_pHPUI != nullptr)
		m_pHPUI->Update(dDeltaTime);

	Update_Collider(dDeltaTime);

	FAILED_CHECK(Update_ParticleTransform(dDeltaTime));
	return _int();
}

_int CMonster_Tezabsura_Minion::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;
	if (__super::LateUpdate(dDeltaTime) == UPDATE_SKIP)
		return UPDATE_SKIP;
	///////////
	if (m_bIsOnScreen)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}
	///////////

	//FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this, m_pTransformCom, m_pShaderCom, m_pModel, nullptr, m_pDissolve));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

#ifdef _DEBUG
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));
#endif

	if(m_bJumpingOn == false)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));


	if (m_pHPUI != nullptr)
		m_pHPUI->LateUpdate(dDeltaTime);

	return _int();
}

_int CMonster_Tezabsura_Minion::Render()
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

_int CMonster_Tezabsura_Minion::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;
	if (__super::LateRender() == UPDATE_SKIP)
		return UPDATE_SKIP;
	return _int();
}

void CMonster_Tezabsura_Minion::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	if (CollisionTypeID::CollisionType_Player == eConflictedObjCollisionType)
	{
		_Vector vDamageDir = XMVector3Normalize(pConflictedCollider->Get_ColliderPosition(iConflictedObjColliderIndex).XMVector() - m_pTransformCom->Get_MatrixState(CTransform::TransformState::STATE_POS));
		pConflictedObj->Take_Damage(this, 1.f, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower);
		pConflictedCollider->Set_Conflicted(1.f);
	}
}

_float CMonster_Tezabsura_Minion::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();

	if (iNowAnimIndex >= 8 && iNowAnimIndex <= 10)
		return _float();

	m_pHPUI->Set_ADD_HitCount((_int)fDamageAmount);
	m_fHP += -fDamageAmount;

	m_bStopCoolTimeOn = true;

	m_dSpecial_CoolTime = 0;


	m_bIOnceAnimSwitch = true;
	if (m_eMonster_State != Anim_State::MONSTER_ATTACK)
	{
		if (bKnockback == false)
		{
			m_bKnockbackOn = false;
			m_iOncePattern = 40;
		}
		else {
			m_bKnockbackOn = true;
			m_iOncePattern = 40;

			XMStoreFloat3(&m_fKnockbackDir, vDamageDir);
		}

		if (m_fHP < 5 && m_iBoolOnce == 0)
		{
			m_iOncePattern = 41;
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

HRESULT CMonster_Tezabsura_Minion::SetUp_Info()
{

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(2.f, 0.f, 2.f));


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_pPlayerTransform = static_cast<CTransform*>(pGameInstance->Get_Commponent_By_LayerIndex(m_eNowSceneNum, TAG_LAY(Layer_Player), TAG_COM(Com_Transform)));

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::SetUp_Collider()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider), (CComponent**)&m_pColliderCom));


	/////////////////m_pColliderCom!@!@#$@!#$@#$@$!@%#$%@#$%%^^W@!
	COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(5.f, 5.f, 5.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	ATTACHEDESC tAttachedDesc;
	tAttachedDesc.Initialize_AttachedDesc(this, "pelvis", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.f, 0.11513f, -1.4121f));
	m_vecAttachedDesc.push_back(tAttachedDesc);



	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "head", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.05226f, -2.3082f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.5f, 1.5f, 1.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.088488f, -1.5709f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "calf_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.20107f, 0.07767f, -0.81758f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "calf_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.20107f, 0.07767f, -0.81758f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.61184f, 0.26749f, -1.9888f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_twist_02_r", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.84824f, 0.23265f, -1.9768f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.61184f, 0.26749f, -1.9888f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "lowerarm_twist_02_l", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.84824f, 0.23265f, -1.9768f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();

	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::SetUp_Fight(_double dDeltaTime)
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

HRESULT CMonster_Tezabsura_Minion::Update_Collider(_double dDeltaTime)
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

HRESULT CMonster_Tezabsura_Minion::PlayAnim(_double dDeltaTime)
{
	SetUp_Fight(dDeltaTime);

	CoolTime_Manager(dDeltaTime);

	if (true == m_bIOnceAnimSwitch)
	{
		Once_AnimMotion(dDeltaTime);
		_uint i = m_pModel->Get_NowAnimIndex();
		switch (i)
		{
		case 1:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			break;
		case 9:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.f);
			break;
		default:
			m_pModel->Change_AnimIndex(m_iOnceAnimNumber, 0.15f); //1�� ������ ������ // (i == 1 || i == 8 || i == 9 || i == 10) ? 0 :
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

HRESULT CMonster_Tezabsura_Minion::CoolTime_Manager(_double dDeltaTime)
{
	if (m_bStopCoolTimeOn == false)
	{
		m_dOnceCoolTime += dDeltaTime;
		m_dSpecial_CoolTime += dDeltaTime;
		m_dInfinity_CoolTime += dDeltaTime;
	}

	//�ѹ��� �����ϴ� �ִϸ��̼�

	if (m_dOnceCoolTime > 2 || m_bComboAnimSwitch == true)
	{
		m_dOnceCoolTime = 0;
		m_dInfinity_CoolTime = 0;

		//if (m_bComboAnimSwitch == false) ���⿡ ������ ���ݸ� ������
		//{
		//	Special_Trigger(dDeltaTime);
		//}
		if (m_bIOnceAnimSwitch == false)
		{
			Pattern_Change();


			m_bIOnceAnimSwitch = true;
		}
	}

	//�ݺ������� �����ϴ� �ִϸ��̼�
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

HRESULT CMonster_Tezabsura_Minion::Once_AnimMotion(_double dDeltaTime)
{
#ifdef _DEBUG
	// #DEBUG PatternSET
	// m_iOncePattern = 2;

	if (KEYPRESS(DIK_B))
		m_iOncePattern = 0;
#endif // _DEBUG

	switch (m_iOncePattern)
	{
	case 0:
		m_iOnceAnimNumber = 12; //Attack
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 1:
		m_iOnceAnimNumber = 8; //JumpStart
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 2:
		m_iOnceAnimNumber = 9; //JumpLoop
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 3:
		m_iOnceAnimNumber = 10; //JumpEnd
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 4:
		m_iOnceAnimNumber = 12; //Attack
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 5:
		m_iOnceAnimNumber = 8; //JumpStart
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 6:
		m_iOnceAnimNumber = 9; //JumpLoop
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 7:
		m_iOnceAnimNumber = 10; //JumpEnd
		m_bComboAnimSwitch = true;
		m_iAfterPattern = m_iOncePattern + 1;
		break;
	case 8:
		m_iOnceAnimNumber = 12; //Attack
		m_bComboAnimSwitch = false;
		m_iAfterPattern = m_iOncePattern + 1;
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;

	case 30:
		m_iOnceAnimNumber = 11; //Kick Attack
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 40:
		m_iOnceAnimNumber = 7;
		m_eMonster_State = Anim_State::MONSTER_HIT;
		break;
	case 41:
		m_iOnceAnimNumber = 3;
		break;
	}

	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::Pattern_Change()
{

	m_iOncePattern += 1;


	if (m_iOncePattern >= 9)
	{
		if (m_iAfterPattern < 9)
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

HRESULT CMonster_Tezabsura_Minion::Infinity_AnimMotion(_double dDeltaTime)
{
	switch (m_iInfinityPattern)
	{
	case 0:
		m_iInfinityAnimNumber = 0;
		break;
	case 1:
		m_iInfinityAnimNumber = 1;
		break;
	case 2:
		m_iInfinityAnimNumber = 1;
		break;
	case 3:
		m_iInfinityAnimNumber = 1;
		break;
	case 4:
		m_iInfinityAnimNumber = 1;
		break;
	case 5:
		m_iInfinityAnimNumber = 1;
		break;
	case 6:
		m_iInfinityAnimNumber = 1;
		break;
	}

	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::Special_Trigger(_double dDeltaTime)
{

	if (m_fDistance < 2 && m_dSpecial_CoolTime > 5)
	{
		m_dSpecial_CoolTime = 0;
		m_dOnceCoolTime = 0;
		m_dInfinity_CoolTime = 0;

		m_bIOnceAnimSwitch = true;
		m_iOncePattern = 30;
	}


	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::Jumping(_double dDeltaTime)
{

	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	//if (iNowAnimIndex >= 8 && iNowAnimIndex <= 10) �̰� �´°�
	//{
	//	m_bLookAtOn = false;

	//	_uint TargetAnimIndex = iNowAnimIndex - 8;

	//	if (PlayRate <=0 && iNowAnimIndex == 8)
	//	{
	//		m_fJumpTempPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);
	//	}

	//	_float fJumpY = 0;
	//	if (PlayRate + TargetAnimIndex >= 0.5f && PlayRate + TargetAnimIndex <= 2.5f)
	//	{
	//		fJumpY  = GetSingle(CGameInstance)->Easing_Return(TYPE_SinOut, TYPE_QuadInOut, 0, m_fJumpPower, PlayRate + TargetAnimIndex - 0.5f, 2.f);
	//	}
	//	else
	//	{
	//		fJumpY = 0;
	//	}
	//	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_fJumpTempPos.XMVector() + XMVectorSet(0, fJumpY, 0, 0));
	//}

	if (iNowAnimIndex >= 8 && iNowAnimIndex <= 10)
	{
		m_bLookAtOn = false;

		_uint TargetAnimIndex = iNowAnimIndex - 8;

		if (PlayRate <= 0 && iNowAnimIndex == 8)
		{
			m_fJumpTempPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);
		}

		_float fJumpY = 0;
		if (PlayRate + TargetAnimIndex >= 0.5f && PlayRate + TargetAnimIndex <= 2.5f)
		{
			fJumpY = GetSingle(CGameInstance)->Easing_Return(TYPE_SinOut, TYPE_QuadInOut, 0, m_fJumpPower, (_float)PlayRate + TargetAnimIndex - 0.5f, 2.f);

			m_pTransformCom->Move_Forward(dDeltaTime*0.8,m_pNavigationCom);
		}
		else
		{
			fJumpY = 0;
		}


		_float Value = max(min(fJumpY / m_fJumpPower, 1.f), 0.f);
		Set_LimLight_N_Emissive(_float4(0.35f, 0.9f, 0.35f, Value), _float4(Value, Value*0.7f, Value, 0.9f));


		_float3		fPosition = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);

		fPosition.y = m_fJumpTempPos.y + fJumpY;
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, XMLoadFloat3(&fPosition));
	}

	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::Ready_ParticleDesc()
{
	//m_pTextureParticleTransform = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	//m_pMeshParticleTransform	= (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	//NULL_CHECK_RETURN(m_pTextureParticleTransform, E_FAIL);
	//NULL_CHECK_RETURN(m_pMeshParticleTransform, E_FAIL);
	//m_pTextureParticleTransform->Set_TurnSpeed(1);


	CUtilityMgr* pUtil = GetSingle(CUtilityMgr);

	//Monster_Tazabsura_Minon_1
	//


	m_vecTextureParticleDesc.push_back(pUtil->Get_TextureParticleDesc(L"Monster_Tazabsura_Minon_3"));
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].FollowingTarget = nullptr;
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].eParticleTypeID = InstanceEffect_Fountain;
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].Particle_Power = 10;
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].EachParticleLifeTime = 0.35f;
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].fMaxBoundaryRadius = 2.f;
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].vPowerDirection = _float3(0, 1, 0);
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].Particle_Power = 20.f;
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].SizeChageFrequency = 1;
	//m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].ParticleSize2 = _float3(0.5f);



	m_vecTextureParticleDesc.push_back(pUtil->Get_TextureParticleDesc(L"Monster_Tazabsura_Minon_4"));
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].SizeChageFrequency = 1;
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].Particle_Power = 20;
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].ParticleSize2 = _float3(0.1f);
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].EachParticleLifeTime = (0.4f);
	m_vecTextureParticleDesc[m_vecTextureParticleDesc.size() - 1].bBillboard = true;

	//////////////////////////////////////////////////////////////////////////

	m_vecMeshParticleDesc.push_back(pUtil->Get_MeshParticleDesc(L"Monster_Tezabsura_Spring"));
	ZeroMemory(m_vecMeshParticleDesc[0].szModelMeshProtoTypeTag, sizeof(_tchar) * 128);
	lstrcpy(m_vecMeshParticleDesc[0].szModelMeshProtoTypeTag, TAG_CP(Prototype_Mesh_Tornado));
	m_vecMeshParticleDesc[0].ParticleSize = _float3(0.4f, 0.15f, 0.4f);
	m_vecMeshParticleDesc[0].fAppearTimer = 0.15f;
	m_vecMeshParticleDesc[0].EachParticleLifeTime = 0.4f;
	m_vecMeshParticleDesc[0].vNoisePushingDir = _float2(0, 1.f);
	m_vecMeshParticleDesc[0].ParticleSize = _float3(0.4f, 0.1f, 0.4f);

	m_vecMeshParticleDesc.push_back(pUtil->Get_MeshParticleDesc(L"Monster_Tezabsura_Br"));


	//////////////////////////////////////////////////////////////////////////
#pragma region Mesh
	NONINSTNESHEFTDESC tNIMEDesc;



	tNIMEDesc.eMeshType = Prototype_Mesh_Plat_Wall;
	tNIMEDesc.fAppearTime = 0.5f;
	tNIMEDesc.fMaxTime_Duration = tNIMEDesc.fAppearTime*2.f + 0.15f;

	tNIMEDesc.noisingdir = _float2(-1, 0);

	tNIMEDesc.NoiseTextureIndex = 381;
	tNIMEDesc.MaskTextureIndex = 33;
	tNIMEDesc.iDiffuseTextureIndex = 369;
	tNIMEDesc.m_iPassIndex = 19;
	tNIMEDesc.vEmissive = _float4(1, 0.5f, 1.f, 0);
	tNIMEDesc.vLimLight = _float4(0.35f, 0.85f, 0.35f, 1);
	tNIMEDesc.NoiseTextureIndex = 381;
	tNIMEDesc.vColor = _float4(0.35f, 0.85f, 0.35f, 1);

	tNIMEDesc.RotAxis = FollowingDir_Right;
	tNIMEDesc.RotationSpeedPerSec = 90.f / (tNIMEDesc.fMaxTime_Duration - tNIMEDesc.fAppearTime*2.f);
	tNIMEDesc.vSize = _float3(0.1125f, 0.1125f, 0.1125f);
	tNIMEDesc.vLimLight = _float4(_float3(vOldRimLightColor), 1);

	tNIMEDesc.MoveDir = FollowingDir_Look;
	tNIMEDesc.MoveSpeed = 15.f;


	tNIMEDesc.m_CheckerBuffer = Prototype_Object_Monster_Tezabsura_Minion;
	//0
	m_vecNonMeshParticleDesc.push_back(tNIMEDesc);
#pragma endregion
	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::Play_SpawnEffect()
{
	if (m_SpawnEffectAdjust == 0)
	{
		m_SpawnEffectAdjust++;
		Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_SPAWN_TM, m_pTransformCom);
		
	}

	if (m_SpawnEffectAdjust == 1 && m_SpawnDealytime <= 2.1f)
	{
		m_SpawnEffectAdjust++;
		g_pGameInstance->Play3D_Sound(TEXT("UM_Spawn_09.ogg"),
			m_pTransformCom->Get_MatrixState(CTransform::STATE_POS),
			CHANNELID::CHANNEL_MONSTER, 1.0f);
	}



	if (m_SpawnEffectAdjust == 2 && m_SpawnDealytime <= 1.3f)
	{
		m_SpawnEffectAdjust++;


		{
			// Stones
			INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
				Prototype_Mesh_SM_Reorgeaskil04_stone1_7,
				0.01f,
				0.5f,
				_float4(0.98f, 0.1f, 0.0f, 0),
				_float4(0.96f, 0.05f, 0.0f,0),
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
			testMesh.vEmissive_SBB = _float3(1.0f, 0.1f, 0.1f);

			testMesh.iMaskingTextureIndex = 57;
			testMesh.iNoiseTextureIndex = 337;

			testMesh.TempBuffer_0.w = 274;

			testMesh.TempBuffer_1.x = 1.0f;
			testMesh.TempBuffer_0.z = 1;

			testMesh.FollowingTarget = m_pTransformCom;
			testMesh.iFollowingDir = FollowingDir_Up;

			testMesh.bAutoTurn = true;
			testMesh.fRotSpeed_Radian = XMConvertToRadians(720);

			GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
		}

	}

	if (m_SpawnEffectAdjust == 2 && m_SpawnDealytime <= 0.5f)
	{
		m_SpawnEffectAdjust++;

		// smoke
		{
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::E_TEXTURE_EFFECTJ::Um_FireMask_2_png,
				0.05f,
				0.5f,
				_float4(0.12f, 1.0f, 0.15f, 1),
				_float4(0.32f, 0.85f, 0.25f, 1.0f),
				1,
				_float3(1.0f),
				_float3(0.5f),
				1);
			//	testTex.eParticleTypeID = InstanceEffect_Straight;
			testTex.eInstanceCount = Prototype_VIBuffer_Point_Instance_128;
			testTex.ePassID = InstancePass_BrightColor;
			//	testTex.ePassID = InstancePass_MaskingNoising;s
			// testTex.vEmissive_SBB = _float3(1, 1, 0.3f);
			testTex.vEmissive_SBB = _float3(1, 0.5f, 0.3f);

			_float val = 0.8f;
			testTex.ParticleStartRandomPosMin = _float3(-val, 0, -val);
			testTex.ParticleStartRandomPosMax = _float3(val, 0, val);
			testTex.Particle_Power = 8.0f;

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

HRESULT CMonster_Tezabsura_Minion::Update_ParticleTransform(_double fDeltaTime)
{
	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Monster_Tezabsura_Minion), TAG_COM(Com_Model), (CComponent**)&m_pModel));
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
	HpDesc.m_Dimensions = 1.f;
	m_fMaxHP = 18.f;
	m_fHP = m_fMaxHP;
	g_pGameInstance->Add_GameObject_Out_of_Manager((CGameObject**)(&m_pHPUI), m_eNowSceneNum, TAG_OP(Prototype_Object_UI_HpUI), &HpDesc);



	CDissolve::DISSOLVEDESC DissolveDesc;
	DissolveDesc.pModel = m_pModel;
	DissolveDesc.eDissolveModelType = CDissolve::DISSOLVE_ANIM;
	DissolveDesc.pShader = m_pShaderCom;
	DissolveDesc.RampTextureIndex = 4;
	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Dissolve), TAG_COM(Com_Dissolve), (CComponent**)&m_pDissolve, &DissolveDesc));


	SetUp_Collider();

	return S_OK;
}

HRESULT CMonster_Tezabsura_Minion::Adjust_AnimMovedTransform(_double dDeltaTime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.95)
	{
		m_iAdjMovedIndex = 0;

		m_bLookAtOn = true;
		m_dAcceleration = 1;

		m_iSoundIndex = 0;

		if (iNowAnimIndex < 8 || iNowAnimIndex >10)
			m_bJumpingOn = false;
		
		m_bStopCoolTimeOn = false;
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
		switch (iNowAnimIndex)
		{
		case 0:
		{
			if (PlayRate > 0)
			{
				m_bLookAtOn = false;
			}

			break;
		}
		case 1:
			if (PlayRate > 0)
			{
				m_pTransformCom->Move_Forward(dDeltaTime * 1.05, m_pNavigationCom);


				if (m_iSoundIndex == 0 && PlayRate > 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Footstep_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
					m_iSoundIndex++;
				}else if (m_iSoundIndex == 1 && PlayRate >= 0.5)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Footstep_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
					m_iSoundIndex++;
				}

				//else if (m_iSoundIndex == 2 && PlayRate >= 0.8064)
				//{
				//	g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Footstep_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
				//	m_iSoundIndex++;
				//}

				//switch (m_iSoundIndex)
				//{
				//case 0:
				//{
				//	if (PlayRate > 0.1)
				//	{
				//		g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Footstep_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
				//		m_iSoundIndex++;
				//	}
				//	break;
				//}
				//case 1:
				//{
				//	if ( PlayRate >= 0.3225)
				//	{
				//		g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Footstep_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
				//		m_iSoundIndex++;
				//	}
				//	break;
				//}
				//case 2:
				//{
				//	if (PlayRate >= 0.5)
				//	{
				//		g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Footstep_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
				//		m_iSoundIndex++;
				//	}
				//	break;
				//}
				//case 3:
				//{
				//	if (PlayRate >= 0.8064)
				//	{
				//		g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Footstep_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
				//		m_iSoundIndex++;
				//	}
				//	break;
				//}
				//default:
				//	break;
				//}
			}
			break;
		case 3:
		{
			m_bLookAtOn = false;
			break;
		}
		case 7:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0 && m_bKnockbackOn == false)
			{
				m_bLookAtOn = false;
				m_dAcceleration = 0.7;
				m_iAdjMovedIndex++;
			}
			if (m_bKnockbackOn == true)
			{
				if (m_iAdjMovedIndex == 0 && PlayRate > 0)
				{
					m_bLookAtOn = false;
					m_dAcceleration = 0.7;
					m_iAdjMovedIndex++;
				}
				else if (0.f < PlayRate && PlayRate <= 0.38)
				{
					m_pTransformCom->Move_Backward(dDeltaTime* 0.5, m_pNavigationCom);

					m_fKnockbackDir.y = 0;

					m_pTransformCom->Turn_Dir(m_fKnockbackDir.XMVector(), 0.9f);
				}
			}

			if (m_iSoundIndex == 0 && PlayRate > 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Get_Hit_Pain_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
				m_iSoundIndex++;
			}
			break;
		}
		case 8:
		{
			if (m_iAdjMovedIndex == 0)
			{
				//m_dAcceleration = 1.6452f;
				m_bJumpingOn = true;

				m_iAdjMovedIndex++;
			}else if (m_iAdjMovedIndex == 1 && PlayRate > 0.2f)
			{


				//m_vecMeshParticleDesc[0].vFixedPosition = (m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)
				//	+ m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK) *0.2f +
				//	+m_pTransformCom->Get_MatrixState(CTransform::STATE_UP) *1.f);

				//m_vecMeshParticleDesc[0].vPowerDirection =
				//	XMVector3Normalize((m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)
				//		 - (m_vecMeshParticleDesc[0].vFixedPosition.XMVector())));
					
				m_vecTextureParticleDesc[0].vFixedPosition = m_vecMeshParticleDesc[0].vFixedPosition 
					= m_pTransformCom->Get_MatrixState(CTransform::STATE_POS) + m_pTransformCom->Get_MatrixState(CTransform::STATE_UP) * 0.35f;
				m_vecMeshParticleDesc[0].vPowerDirection = 
					-((m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)
					+ m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK) *0.15f +
					+m_pTransformCom->Get_MatrixState(CTransform::STATE_UP) *1.f)-
					m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));

				GetSingle(CUtilityMgr)->Create_MeshInstance(m_eNowSceneNum, m_vecMeshParticleDesc[0]);


				GetSingle(CUtilityMgr)->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[0]);


				m_iAdjMovedIndex++;
			}
			if (m_iSoundIndex == 0 && PlayRate >= 0.5882)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Get_Hit_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
				m_iSoundIndex++;
			}
			break;
		}
		case 9:
		{
			if (m_iAdjMovedIndex == 0)
			{
				//m_dAcceleration = 1.6452f;
				m_bJumpingOn = true;

				m_iAdjMovedIndex++;
			}
			break;
		}
		case 10:
		{
			if (m_iAdjMovedIndex == 0)
			{
				//m_dAcceleration = 1.6452f;
				m_bJumpingOn = true;

				m_iAdjMovedIndex++;
			}else if (m_iAdjMovedIndex == 1 && PlayRate > 0.6f)
			{

				m_vecTextureParticleDesc[0].vFixedPosition = m_vecTextureParticleDesc[1].vFixedPosition 
					= m_pTransformCom->Get_MatrixState(CTransform::STATE_POS) + m_pTransformCom->Get_MatrixState(CTransform::STATE_UP) * 0.35f;

				GetSingle(CUtilityMgr)->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[0]);
				GetSingle(CUtilityMgr)->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[1]);


				m_iAdjMovedIndex++;
			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.421)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_rockjump03.ogg"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.7f);
				m_iSoundIndex++;
			}

			break;
		}
		case 11:
		{
			m_bLookAtOn = false;
			{
				_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
				Value = max(min(Value, 1.f), 0.f);
				Set_LimLight_N_Emissive(_float4(0.35f, 0.9f, 0.35f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			}
			if (PlayRate > 0.2f && m_iAdjMovedIndex == 0)
			{


				m_vecNonMeshParticleDesc[0].vPosition = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS) +
					m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK) * 1.55f;
				m_vecNonMeshParticleDesc[0].vLookDir = (m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK));

				m_vecTextureParticleDesc[1].vFixedPosition = m_vecTextureParticleDesc[0].vFixedPosition = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS) +
					m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK) * 6.f;

				g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_PlayerEffect), TAG_OP(Prototype_Object_Monster_Bullet_Plat), &m_vecNonMeshParticleDesc[0]);
				m_iAdjMovedIndex++;
			}
			if (PlayRate >= 0.415555 && PlayRate <= 0.7222)
			{
				m_pTransformCom->Move_Forward(dDeltaTime * 1.5);
				m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));
			}
			if (PlayRate > 0.5744f && m_iAdjMovedIndex == 1)
			{
				GetSingle(CUtilityMgr)->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[0]);
				GetSingle(CUtilityMgr)->Create_TextureInstance(m_eNowSceneNum, m_vecTextureParticleDesc[1]);


				m_iAdjMovedIndex++;

			}

			if (m_iSoundIndex == 0 && PlayRate >= 0.4285)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Tezabsura_Get_Hit_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.3f);
				g_pGameInstance->Play3D_Sound(TEXT("EH_M1_1138.mp3"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.3f);
				m_iSoundIndex++;
			}
			break;
		}
		case 12:
		{

			{
				_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
				Value = max(min(Value, 1.f), 0.f);
				Set_LimLight_N_Emissive(_float4(0.35f, 0.9f, 0.35f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			}

			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.57142)
			{
				m_bLookAtOn = false;

				CMonster_Bullet_Universal::MONSTER_BULLET_UNIVERSALDESC Monster_BulletDesc;

				Monster_BulletDesc.iBulletMeshNumber = CMonster_Bullet_Universal::TEZABSURA_MINION_BULLET;
				Monster_BulletDesc.fSpeedPerSec = 10;
				Monster_BulletDesc.fScale = _float3(0.75f, 0.75f, 0.75f);

				Monster_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_BulletDesc.fPositioning = _float3(0.001f, 2.f, 1.5f);


				Monster_BulletDesc.Object = this;

				Monster_BulletDesc.dDuration = 15;

				Monster_BulletDesc.bBornAttachOn = false;
				Monster_BulletDesc.pBoneName = "jaw_01";

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Bullet_Universal), &Monster_BulletDesc));

				m_iAdjMovedIndex++;
			}
			if (m_iSoundIndex == 0 && PlayRate >= 0.4642)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Tezaabsura_Spit_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_SUBEFFECT, 0.3f);
				m_iSoundIndex++;
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

CMonster_Tezabsura_Minion * CMonster_Tezabsura_Minion::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CMonster_Tezabsura_Minion*	pInstance = NEW CMonster_Tezabsura_Minion(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Tezabsura_Minion");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMonster_Tezabsura_Minion::Clone(void * pArg)
{
	CMonster_Tezabsura_Minion*	pInstance = NEW CMonster_Tezabsura_Minion(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Tezabsura_Minion");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonster_Tezabsura_Minion::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
	Safe_Release(m_pDissolve);

	Safe_Release(m_pHPUI);
	Safe_Release(m_pColliderCom);
	

	Safe_Release(m_pTextureParticleTransform);
	Safe_Release(m_pMeshParticleTransform);

	
		
}
