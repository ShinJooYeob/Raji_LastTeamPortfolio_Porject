#include "stdafx.h"
#include "..\public\Monster_Mahinasura_Minion.h"
#include "Player.h"
#include "HpUI.h"
#include "WorldTexture_Universal.h"

CMonster_Mahinasura_Minion::CMonster_Mahinasura_Minion(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CMonster(pDevice, pDeviceContext)
{
}

CMonster_Mahinasura_Minion::CMonster_Mahinasura_Minion(const CMonster_Mahinasura_Minion & rhs)
	: CMonster(rhs)
{
}

HRESULT CMonster_Mahinasura_Minion::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	if (pArg != nullptr)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, *((_float3*)pArg));

	//m_pTransformCom->Scaled_All(_float3(100, 100, 100));
	m_pTransformCom->Rotation_CW(XMVectorSet(0, 1, 0, 0), XMConvertToRadians(170));

	SetUp_Info();


#ifdef _DEBUG
	///////////////test
	//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(493.f, 7.100010f, 103.571f)); // Stage2
	//m_pNavigationCom->FindCellIndex(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
	///////////////
#endif

	m_pTransformCom->Scaled_All(_float3(1.5f,1.5f,1.5f));


	// Particle
	Set_DealyDIssolveTime(0.5f);

	return S_OK;
}

_int CMonster_Mahinasura_Minion::Update(_double dDeltaTime)
{
	if (__super::Update(dDeltaTime) < 0)
		return -1;

	if (__super::Update(dDeltaTime)  == UPDATE_SKIP)
		return UPDATE_SKIP;

	

	if (m_fHP <= 0)
	{
		m_bRepelOff = true;
		m_bGroggiOn = false;
		m_bLookAtOn = false;
		m_pDissolve->Update_Dissolving(dDeltaTime);
		m_pDissolve->Set_DissolveOn(false, 2.f);

		m_dDissolveTime += dDeltaTime;

		if (m_bDieSound == false && m_dDissolveTime >= 1.)
		{
			g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Die.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
			m_bDieSound = true;
		}

		if (m_dDissolveTime >= 2)
		{
			//g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Die.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
			Set_IsDead();
		}
	}

	// ANIFUNC
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

	Update_Collider(dDeltaTime);

	return _int();
}

_int CMonster_Mahinasura_Minion::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;


	if (__super::LateUpdate(dDeltaTime) == UPDATE_SKIP)
		return UPDATE_SKIP;


	if (m_bIsOnScreen)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}

	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this, m_pTransformCom, m_pShaderCom, m_pModel,nullptr, m_pDissolve));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

#ifdef _DEBUG
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pHandAttackColliderCom));
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pTailAttackColliderCom));
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

	return _int();
}

_int CMonster_Mahinasura_Minion::Render()
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

_int CMonster_Mahinasura_Minion::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;

	if (__super::LateRender() == UPDATE_SKIP)
		return UPDATE_SKIP;

	return _int();
}

void CMonster_Mahinasura_Minion::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	if (CollisionTypeID::CollisionType_Player == eConflictedObjCollisionType)
	{
		_Vector vDamageDir = XMVector3Normalize(pConflictedCollider->Get_ColliderPosition(iConflictedObjColliderIndex).XMVector() - m_pTransformCom->Get_MatrixState(CTransform::TransformState::STATE_POS));
		pConflictedObj->Take_Damage(this, 1.f, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower);
		pConflictedCollider->Set_Conflicted(1.f);
	}
}

_float CMonster_Mahinasura_Minion::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
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
		// JINO
		static_cast<CPlayer*>((g_pGameInstance->Get_GameObject_By_LayerIndex(m_eNowSceneNum, TAG_LAY(Layer_Player))))->Check_TargetingTarget(this);
		return -1.f;
	}

	return _float();
}

HRESULT CMonster_Mahinasura_Minion::Ready_ParticleDesc()
{
	// HandPos

	m_pTextureParticleTransform_RHand = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_RETURN(m_pTextureParticleTransform_RHand, E_FAIL);

	m_pTextureParticleTransform_LHand = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_RETURN(m_pTextureParticleTransform_LHand, E_FAIL);

	// TailPos
	m_pTextureParticleTransform_Tail = (CTransform*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Transform));
	NULL_CHECK_RETURN(m_pTextureParticleTransform_Tail, E_FAIL);



	//// 0
	//INSTPARTICLEDESC instanceDesc = GETPARTICLE->Get_TypeDesc_TextureInstance(CPartilceCreateMgr::TEXTURE_EFFECTJ_Bow_Default);
	//instanceDesc.TotalParticleTime = 99999.f;
	//instanceDesc.FollowingTarget = m_pTextureParticleTransform_BowUp;
	////	GETPARTICLE->Create_Texture_Effect_Desc(instanceDesc, m_eNowSceneNum);
	//m_vecTextureParticleDesc.push_back(instanceDesc);


	//// 1
	//instanceDesc.FollowingTarget = m_pTextureParticleTransform_BowBack;
	////	GETPARTICLE->Create_Texture_Effect_Desc(instanceDesc, m_eNowSceneNum);
	//m_vecTextureParticleDesc.push_back(instanceDesc);

	//// 9999���� �״´�. 
	//m_pTextureParticleTransform_BowUp->Set_IsOwnerDead(true);
	//m_pTextureParticleTransform_BowBack->Set_IsOwnerDead(true);



	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Update_Particle(_double timer)
{
	_Matrix mat_World = m_pTransformCom->Get_WorldMatrix();

	mat_World.r[0] = XMVector3Normalize(mat_World.r[0]);
	mat_World.r[1] = XMVector3Normalize(mat_World.r[1]);
	mat_World.r[2] = XMVector3Normalize(mat_World.r[2]);

	//mat_Tail.r[0] = XMVector3Normalize(mat_Tail.r[0]);
	//mat_Tail.r[1] = XMVector3Normalize(mat_Tail.r[1]);
	//mat_Tail.r[2] = XMVector3Normalize(mat_Tail.r[2]);


	mat_World.r[3] = m_pHandAttackColliderCom->Get_ColliderPosition(1).XMVector();
	m_pTextureParticleTransform_RHand->Set_Matrix(mat_World);

	mat_World.r[3] = m_pHandAttackColliderCom->Get_ColliderPosition(2).XMVector();
	m_pTextureParticleTransform_LHand->Set_Matrix(mat_World);



	//mat_Hand.r[0] = _Sfloat3(1,0,0);
	//mat_Hand.r[1] = _Sfloat3(0,1,0); 
	//mat_Hand.r[2] = _Sfloat3(0,0,1); 

	_Matrix mat_Hand = m_vecTailAttackAttachedDesc[1].Caculate_AttachedBoneMatrix_BlenderFixed(); 

	// m_pTailAttackColliderCom->Get_ColliderPosition(5).XMVector();
	m_pTextureParticleTransform_Tail->Set_Matrix(mat_Hand);


#ifdef _DEBUG
	if (KEYDOWN(DIK_V))
	{
		//	Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_TEST, m_pTextureParticleTransform_LHand);
		Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_MM_TAIL, m_pTransformCom);
	}

	if (KEYDOWN(DIK_C))
	{ 

		// SPAWNTEST
		{
			INSTPARTICLEDESC base = GETPARTICLE->Get_EffectSetting_Tex(
			//	CPartilceCreateMgr::Um_Spawn1_Image,
			//	CPartilceCreateMgr::Um_Spawn1_Image_suck,
			//	CPartilceCreateMgr::Um_Spawn2_Image,
			//	CPartilceCreateMgr::Um_Spawn2_Image_power,
			//	CPartilceCreateMgr::Um_Spawn2_Image_powerdown,
				CPartilceCreateMgr::Um_Spawn3_Imagepng,
			//	CPartilceCreateMgr::Um_Spawn3_Imagepng_ground,
			//	CPartilceCreateMgr::Um_Spawn3_Imagepng_ground2,
			//	CPartilceCreateMgr::Um_Spawn3_Imagepng_magic,
			//	CPartilceCreateMgr::Um_Spawn3_Imagepng_magic2,
			//	CPartilceCreateMgr::Um_Spawn3_Imagepng_Snow,
			//	CPartilceCreateMgr::Um_Spawn3_Imagepng_Snow2,
			//	CPartilceCreateMgr::Um_Spawn4_smoke,
				0,
				0,
				_float4(3.0f),
				_float4(3.f),
				0,
				_float3(0.1f),
				_float3(3.0f),
				1);

		//	base.ParticleStartRandomPosMin = _float3(0, 0.2f,0);
		//	base.ParticleStartRandomPosMax = _float3(0, 1.f,0);
			base.FollowingTarget = m_pPlayerTransform;
			base.iFollowingDir = FollowingDir_Look;
		//	base.vEmissive_SBB = _float3(1);
			

		//	base.TempBuffer_0.z = 0;
		//	base.TempBuffer_0.w = FollowingDir_Right;
		//	base.iFollowingDir = FollowingDir_Up;
		//	dust2_f.TempBuffer_1.x = 0.0f;

			GETPARTICLE->Create_Texture_Effect_Desc(base, m_eNowSceneNum);
		}

		{
			// ring
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(
				CPartilceCreateMgr::Um_Spawn2_Image,
				//	CPartilceCreateMgr::Um_Spawn2_Image_powerdown,
				0,
				0.3f,
				_float4(1.0f),
				_float4(0),
				1,
				_float3(0.5f),
				_float3(3.0f),
				1);
			testTex.iTextureLayerIndex = 10;

			testTex.ParticleStartRandomPosMin = _float3(0, 0.2f, 0);
			testTex.ParticleStartRandomPosMax = _float3(0, 1.5f, 0);
			testTex.FollowingTarget = m_pTransformCom;
			testTex.iFollowingDir = FollowingDir_Look;
			testTex.vEmissive_SBB = _float3(1, 0.5f, 0.5f);
			testTex.m_fAlphaTestValue = 0.2f;

			//	testTex.TempBuffer_0.z = 0;
			//	testTex.TempBuffer_0.w = FollowingDir_Right;
			//	testTex.iFollowingDir = FollowingDir_Up;
			//	testTex.TempBuffer_1.x = 0.0f;

			//  GETPARTICLE->Create_Texture_Effect_Desc(testTex, m_eNowSceneNum);
		}
		{
			// fire
			INSTPARTICLEDESC base = GETPARTICLE->Get_EffectSetting_Tex(
				// CPartilceCreateMgr::Um_Spawn3_Imagepng_Snow2,
				CPartilceCreateMgr::Um_Spawn4_smoke,
				0.01f,
				0.4f,
				_float4(0.98f, 0.27f, 0.61f, 0.8f),
				_float4(0.98f, 0.87f, 0.81f, 0.5f),
				//	_float4(1,1,1,0.0f),
				1,
				_float3(0.5f),
				_float3(0.5f),
				1);

			//	base.eParticleTypeID = InstanceEffect_Suck;;
			//	base.ePassID = InstancePass_BrightColor;

			base.iTextureLayerIndex = 20;
			base.iTextureLayerIndex = 47;
			base.iTextureLayerIndex = 17;
			base.iTextureLayerIndex = 46;

				_float val = 0.3f;
				base.ParticleStartRandomPosMin = _float3(-val, 1.0f,-val);
				base.ParticleStartRandomPosMax = _float3(val, 1.0f, val);
				base.FollowingTarget = m_pTransformCom;
				base.iFollowingDir = FollowingDir_Up;
				base.Particle_Power = 2.0f;
				base.vEmissive_SBB = _float3(0.1f,1.0f, 1.0f);

		//	GETPARTICLE->Create_Texture_Effect_Desc(base, m_eNowSceneNum);
		}



		{
			INSTMESHDESC testMesh = GETPARTICLE->Get_EffectSetting_Mesh(CPartilceCreateMgr::E_MESHINST_EFFECTJ::Um_MeshBase,
				Prototype_Mesh_SM_Baren_Weapon,
				0.01f,
				1.0f,
				_float4(0),
				_float4(0),
				1,
				_float3(0.1f),
				_float3(0.5f),
				1);

			testMesh.vPowerDirection = _float3(0, 1, 0);
			testMesh.eParticleTypeID = InstanceEffect_Fountain;
			testMesh.eInstanceCount = Prototype_ModelInstance_16;
			testMesh.TempBuffer_0.w = 298;
			testMesh.iMaskingTextureIndex = 101;
			testMesh.iNoiseTextureIndex = NONNOISE;

			testMesh.vEmissive_SBB = _float3(1, 0.1f, 0);
			testMesh.fDistortionNoisingPushPower = 10.0f;

			testMesh.ParticleStartRandomPosMin = _float3(0);
			testMesh.ParticleStartRandomPosMax = _float3(0);
			testMesh.Particle_Power = 5.0f;




			//	_Matrix mat = m_pTransformCom->Get_WorldMatrix();
			testMesh.FollowingTarget = m_pPlayerTransform;
			testMesh.iFollowingDir = FollowingDir_Up;
		//	GETPARTICLE->Create_MeshInst_DESC(testMesh, m_eNowSceneNum);
		}

	}
#endif // _DEBUG

	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Play_SpawnEffect()
{

	if (m_SpawnEffectAdjust == 0)
	{
		m_SpawnEffectAdjust++;

		g_pGameInstance->Play3D_Sound(TEXT("UM_Spawn_02.ogg"),
			m_pTransformCom->Get_MatrixState(CTransform::STATE_POS),
			CHANNELID::CHANNEL_MONSTER, 1.0f);


		{
			// ring
			INSTPARTICLEDESC testTex = GETPARTICLE->Get_EffectSetting_Tex(
				CPartilceCreateMgr::Um_Spawn2_Image,
				//	CPartilceCreateMgr::Um_Spawn2_Image_powerdown,
				0,
				0.3f,
				_float4(1.0f),
				_float4(0),
				1,
				_float3(0.5f),
				_float3(3.0f),
				1);
			testTex.iTextureLayerIndex = 18;

			testTex.ParticleStartRandomPosMin = _float3(0, 0.2f, 0);
			testTex.ParticleStartRandomPosMax = _float3(0, 1.5f, 0);
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
			// fire
			INSTPARTICLEDESC base = GETPARTICLE->Get_EffectSetting_Tex(
				// CPartilceCreateMgr::Um_Spawn3_Imagepng_Snow2,
				CPartilceCreateMgr::Um_Spawn4_smoke,
				1.5f,
				0.4f,
				_float4(0.98f, 0.27f, 0.61f, 0.8f),
				_float4(0.98f, 0.87f, 0.81f, 0.5f),
				//	_float4(1,1,1,0.0f),
				1,
				_float3(0.5f),
				_float3(0.5f),
				1);

			//	base.eParticleTypeID = InstanceEffect_Suck;;
			//	base.ePassID = InstancePass_BrightColor;

			base.iTextureLayerIndex = 20;
			base.iTextureLayerIndex = 47;
			base.iTextureLayerIndex = 17;
			base.iTextureLayerIndex = 46;

			_float val = 0.3f;
			base.ParticleStartRandomPosMin = _float3(-val, -1.0f, -val);
			base.ParticleStartRandomPosMax = _float3(val, 1.0f, val);
			base.FollowingTarget = m_pTransformCom;
			base.iFollowingDir = FollowingDir_Up;
			base.Particle_Power = 2.0f;
			base.vEmissive_SBB = _float3(0.1f, 1.0f, 1.0f);

			GETPARTICLE->Create_Texture_Effect_Desc(base, m_eNowSceneNum);
		}

	}
	

	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::SetUp_Info()
{

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS,_float3(2.f,0.f,2.f));


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_pPlayerTransform = static_cast<CTransform*>(pGameInstance->Get_Commponent_By_LayerIndex(m_eNowSceneNum, TAG_LAY(Layer_Player),TAG_COM(Com_Transform)));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::SetUp_Collider()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider), (CComponent**)&m_pColliderCom));
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_ColliderSub), (CComponent**)&m_pHandAttackColliderCom));
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_ColliderSubSub), (CComponent**)&m_pTailAttackColliderCom));

	/////////////////m_pColliderCom!@!@#$@!#$@#$@$!@%#$%@#$%%^^W@!
	COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(3.f, 3.f, 3.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	ATTACHEDESC tAttachedDesc;
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.f, -0.5f));
	m_vecAttachedDesc.push_back(tAttachedDesc);


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_head", _float3(1.f,1.f,1.f), _float3(0.f,0.f,0.f), _float3(0.f, 0.f, -0.8f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.8f, 0.8f, 0.8f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_spine_02", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.1f, -0.45f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_cloth_02", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, -0.15f, -0.2f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();
	//////////////////////////////////////////////////////////////////////




	/////////////////m_pAttackColliderCom!@!@#$@!#$@#$@$!@%#$%@#$%%^^W@!

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(5.f, 5.f, 5.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pHandAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.f, -0.5f));
	m_vecHandAttackAttachedDesc.push_back(tAttachedDesc);

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.7f, 0.7f, 0.7f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pHandAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_r_index_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.34938f,-0.11046f,-0.32727f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecHandAttackAttachedDesc.push_back(tAttachedDesc);
	m_pHandAttackColliderCom->Set_ParantBuffer();

	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.7f, 0.7f, 0.7f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pHandAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_l_index_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.34938f, -0.11046f, -0.32727f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecHandAttackAttachedDesc.push_back(tAttachedDesc);
	m_pHandAttackColliderCom->Set_ParantBuffer();
	//////////////////////////////////////////////////////////////////////



	////////////////////////////////////m_pTailAttackColliderCom!@#!@##!#@
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(7.f, 7.f, 7.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.f, -0.5f));
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_end", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 1.3931f, -0.3834f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_10", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 1.18f, -0.42061f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_09", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 1.0177f, -0.41792f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_08", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.9001f, -0.41846f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_07", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.7588f, -0.41846f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_06", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.62504f, -0.41846f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_05", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.5134f, -0.419f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_04", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.39583f, -0.419f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_03", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.27448f, -0.41954f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_02", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.15097f, -0.41792f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();


	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.3f, 0.3f, 0.3f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pTailAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_tail_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.040943f, -0.419f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
	m_vecTailAttackAttachedDesc.push_back(tAttachedDesc);
	m_pTailAttackColliderCom->Set_ParantBuffer();

	//////////////////////////////////////////////////////////////////////


	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::SetUp_Fight(_double dDeltaTime)
{
	m_fDistance = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).Get_Distance(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));


	//if (m_fDistance < 1)
	//{
	//	switch (m_iInfinityAnimNumber)
	//	{
	//	case 1:
	//		m_pTransformCom->Move_Backward(dDeltaTime * 0.6,m_pNavigationCom);
	//		break;
	//	case 21:
	//		m_pTransformCom->Move_Backward(dDeltaTime * 1.2, m_pNavigationCom);
	//		break;
	//	default:
	//		m_pTransformCom->Move_Backward(dDeltaTime, m_pNavigationCom);
	//		break;

	//	}
	//}

	if (m_bLookAtOn)
	{
		//m_pTransformCom->LookAt(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));

		_Vector vTarget = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
	
		//m_pTransformCom->Turn_Dir(XMVector3Normalize(m_pTransformCom->Get_MatrixScale(CTransform::STATE_LOOK)*0.9 + vTarget* 0.1));
		m_pTransformCom->Turn_Dir(vTarget,0.9f);
	}

	//CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	////����ϰ� �����̱�
	//if (pGameInstance->Get_DIKeyState(DIK_Y) & DIS_Press)
	//{
	//	m_pTransformCom->Move_Up(dDeltaTime);
	//}
	//if (pGameInstance->Get_DIKeyState(DIK_H) & DIS_Press)
	//{
	//	m_pTransformCom->Move_Down(dDeltaTime);
	//}

	//RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Update_Collider(_double dDeltaTime)
{
	m_pColliderCom->Update_ConflictPassedTime(dDeltaTime);
	m_pHandAttackColliderCom->Update_ConflictPassedTime(dDeltaTime);
	m_pTailAttackColliderCom->Update_ConflictPassedTime(dDeltaTime);

	//Collider
	_uint	iNumCollider = m_pColliderCom->Get_NumColliderBuffer();
	for (_uint i = 0; i < iNumCollider; i++)
		m_pColliderCom->Update_Transform(i, m_vecAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());

	if (m_bColliderAttackOn == true)
	{
		switch (m_eColliderType)
		{
		case Client::CMonster_Mahinasura_Minion::HANDATTACK:
			//HandAttackCollider
			iNumCollider = m_pHandAttackColliderCom->Get_NumColliderBuffer();
			for (_uint i = 0; i < iNumCollider; i++)
				m_pHandAttackColliderCom->Update_Transform(i, m_vecHandAttackAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());
			break;
		case Client::CMonster_Mahinasura_Minion::TAILATTACK:
			//TailAttackCollider
			iNumCollider = m_pTailAttackColliderCom->Get_NumColliderBuffer();
			for (_uint i = 0; i < iNumCollider; i++)
				m_pTailAttackColliderCom->Update_Transform(i, m_vecTailAttackAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());
			break;
		default:
			break;
		}
	}

	FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_Monster, this, m_pColliderCom));




	if (m_bColliderAttackOn == true)
	{
		switch (m_eColliderType)
		{
		case Client::CMonster_Mahinasura_Minion::HANDATTACK:
			FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_MonsterWeapon, this, m_pHandAttackColliderCom));
			break;
		case Client::CMonster_Mahinasura_Minion::TAILATTACK:
			FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_MonsterWeapon, this, m_pTailAttackColliderCom));
			break;
		default:
			break;
		}
	}

	if (m_bRepelOff != true)
		FAILED_CHECK(g_pGameInstance->Add_RepelGroup(m_pTransformCom, 1.f, m_pNavigationCom));

	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::PlayAnim(_double dDeltaTime)
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

HRESULT CMonster_Mahinasura_Minion::CoolTime_Manager(_double dDeltaTime)
{
	if (m_bStopCoolTimeOn == false)
	{
		m_dOnceCoolTime += dDeltaTime;
		m_dSpecial_CoolTime += dDeltaTime;
		m_dInfinity_CoolTime += dDeltaTime;
	}

	//�ѹ��� �����ϴ� �ִϸ��̼�

	if (m_dOnceCoolTime > 1.7 && m_fDistance < 3)
	{
		m_dOnceCoolTime = 0;
		m_dInfinity_CoolTime = 0;

		m_bIOnceAnimSwitch = true;

		m_bFastRunOn = false;

		Pattern_Change();
	}

	//�ݺ������� �����ϴ� �ִϸ��̼�
	if (m_dInfinity_CoolTime >= 1.5)
	{
		m_iInfinityPattern = rand() % 7;


		m_dInfinity_CoolTime = 0;

		m_bFastRunOn = false;
	}

	Special_Trigger(dDeltaTime);

	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Once_AnimMotion(_double dDeltaTime)
{
#ifdef _DEBUG
	// #DEBUG PatternSET
	// m_iOncePattern = 2;

	if (KEYPRESS(DIK_B))
		m_iOncePattern = 2;
#endif // _DEBUG

	switch (m_iOncePattern)
	{
	case 0:
		m_iOnceAnimNumber = 19; //QuickAttack
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 1:
		m_iOnceAnimNumber = 3; //_Dodge_Right
		break;
	case 2:
		m_iOnceAnimNumber = 20; //TailWhip
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 3:
		m_iOnceAnimNumber = 2; //Dodge_Back
		break;
	case 4:
		m_iOnceAnimNumber = 19; //QuickAttack
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 5:
		m_iOnceAnimNumber = 4; //_Dodge_Left
		break;
	case 6:
		m_iOnceAnimNumber = 20; //TailWhip
		m_eMonster_State = Anim_State::MONSTER_ATTACK;
		break;
	case 30:
		m_iOnceAnimNumber = 6; //Taunt
		break;
	case 40:
		m_iOnceAnimNumber = 15; //LightHit
		m_eMonster_State = Anim_State::MONSTER_HIT;
		break;
	case 41:
		m_iOnceAnimNumber = 16; //HeavyHit
		m_eMonster_State = Anim_State::MONSTER_HIT;
		break;
	case 42:
		m_iOnceAnimNumber = 8; //groggy
		break;
	case 43:
		m_iOnceAnimNumber = 9; //Trishul
		break;
	case 44:
		m_iOnceAnimNumber = 11; // Bow
		break;
	case 45:
		m_iOnceAnimNumber = 13; // Sword
		break;
	}

	if (m_eMonster_State == Anim_State::MONSTER_HIT)
	{
		Set_LimLight_N_Emissive();
	}
	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Pattern_Change()
{
	m_iOncePattern += 1;

	if (m_iOncePattern > 6)
	{
		m_iOncePattern = rand() % 7; //OncePattern Random
	}


	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Infinity_AnimMotion(_double dDeltaTime)
{
	switch (m_iInfinityPattern)
	{
	case 0:
		m_iInfinityAnimNumber = 0;
		break;
	case 1:
		m_pTransformCom->Move_Forward(dDeltaTime * 0.3, m_pNavigationCom);
		m_iInfinityAnimNumber = 1;
		break;
	case 2:
		m_iInfinityAnimNumber = 21;
		break;
	case 3:
		m_iInfinityAnimNumber = 21;
		break;
	case 4:
		m_iInfinityAnimNumber = 21;
		break;
	case 5:
		m_iInfinityAnimNumber = 21;
		break;
	case 6:
		m_iInfinityAnimNumber = 21;
		break;
	}

	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Special_Trigger(_double dDeltaTime)
{

	if (m_fDistance > 8 && m_dSpecial_CoolTime > 20)
	{
		m_dSpecial_CoolTime = 0;
		m_dOnceCoolTime = 0;
		m_dInfinity_CoolTime = 0;

		m_bIOnceAnimSwitch = true;
		m_iOncePattern = 30;
	}


	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Monster_Mahinasura_Minion), TAG_COM(Com_Model), (CComponent**)&m_pModel));
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
	HpDesc.m_Dimensions = 1.2f;
	m_fMaxHP = 15.f;
	m_fHP = m_fMaxHP;
	g_pGameInstance->Add_GameObject_Out_of_Manager((CGameObject**)(&m_pHPUI), m_eNowSceneNum, TAG_OP(Prototype_Object_UI_HpUI), &HpDesc);


	CDissolve::DISSOLVEDESC DissolveDesc;
	DissolveDesc.pModel = m_pModel;
	DissolveDesc.eDissolveModelType = CDissolve::DISSOLVE_ANIM;
	DissolveDesc.pShader = m_pShaderCom;
	DissolveDesc.RampTextureIndex = 0;
	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Dissolve), TAG_COM(Com_Dissolve), (CComponent**)&m_pDissolve, &DissolveDesc));

	SetUp_Collider();
	

	return S_OK;
}

HRESULT CMonster_Mahinasura_Minion::Adjust_AnimMovedTransform(_double dDeltaTime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.98)
	{
		m_iAdjMovedIndex = 0;

		m_bLookAtOn = true;

		m_dAcceleration = 1;

		m_bColliderAttackOn = false;

		m_iSoundIndex = 0;
		m_EffectAdjust = 0;

		m_bStopCoolTimeOn = false;

		if (PlayRate > 0.98 && m_bIOnceAnimSwitch == true)
		{
			m_bIOnceAnimSwitch = false;
			if (m_eMonster_State != Anim_State::MONSTER_HIT)
				m_dOnceCoolTime = 0;
			m_dInfinity_CoolTime = 0;
		}
		m_eMonster_State = Anim_State::MONSTER_IDLE;

		if (m_bGroggiOn == true)
		{
			m_bGroggiOn = false;
		}
	}
	
	if (PlayRate <= 0.98) //�ִϸ��̼��� ���� ��, 0.98�� ���� �������� ����
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
			m_bLookAtOn = false;
			break;
		}
		case 1:
		{
			m_dSoundTime += dDeltaTime;

			if (PlayRate > 0)
			{
				if (m_dSoundTime >= 0.7)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Wave_Mahinasura_Walk.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
					m_dSoundTime = 0;
				}
			}
			break;
		}
		case 2:
		{
			if (PlayRate >= 0.175 && PlayRate <= 0.5)
			{
				m_bLookAtOn = false;

				_float fSpeed = g_pGameInstance->Easing(TYPE_QuinticOut, 4.5f, 1.05f, (_float)PlayRate - 0.175f, 0.325f);
				m_pTransformCom->Move_Backward(dDeltaTime * fSpeed, m_pNavigationCom);


				if (m_iSoundIndex == 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Sigh_06.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.4f);
					m_iSoundIndex++;
				}
			}
			break;
		}
		case 3:
		{
			if (PlayRate >= 0.1 && PlayRate <= 0.5)
			{
				if (m_iAdjMovedIndex == 0)
				{
					m_TempLook = m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK);

					m_iAdjMovedIndex += 1;

					if (m_iSoundIndex == 0)
					{
						g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Sigh_06.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.4f);
						m_iSoundIndex++;
					}
				}
				//_Vector vRight = XMVector3Cross(XMLoadFloat3(&_float3(0.f, 1.f, 0.f)), XMLoadFloat3(&m_TempLook)); //Left
				//_float fSpeed = g_pGameInstance->Easing(TYPE_QuinticOut, 10.f, 3.f, (_float)PlayRate - 0.1f, 0.38f);
				//_float3 vDir;
				//XMStoreFloat3(&vDir, XMVector3Normalize(vRight) * fSpeed * (_float)dDeltaTime);
				//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pTransformCom->Get_MatrixState(CTransform::STATE_POS) + XMLoadFloat3(&vDir));

				_Vector vRight = XMVector3Cross(XMLoadFloat3(&_float3(0.f, 1.f, 0.f)), XMLoadFloat3(&m_TempLook)); //Left
				_float fSpeed = g_pGameInstance->Easing(TYPE_QuinticOut, 4.5f, 0.75f, (_float)PlayRate - 0.1f, 0.38f);
				m_pTransformCom->MovetoDir(vRight, dDeltaTime * fSpeed, m_pNavigationCom);
			}
			break;
		}
		case 4:
		{
			if (PlayRate>=0.1 && PlayRate <= 0.5)
			{
				if (m_iAdjMovedIndex == 0)
				{
					m_TempLook = m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK);

					m_iAdjMovedIndex += 1;

					if (m_iSoundIndex == 0)
					{
						g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Sigh_06.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.4f);
						m_iSoundIndex++;
					}
				}
				//_Vector vRight = XMVector3Cross(XMLoadFloat3(&_float3(0.f, 1.f, 0.f)), XMLoadFloat3(&m_TempLook)); //Left
				//_float fSpeed = g_pGameInstance->Easing(TYPE_QuinticOut, 10.f, 3.f, (_float)PlayRate - 0.1f, 0.38f);
				//_float3 vDir;
				//XMStoreFloat3(&vDir, XMVector3Normalize(-vRight) * fSpeed * (_float)dDeltaTime);
				//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pTransformCom->Get_MatrixState(CTransform::STATE_POS) + XMLoadFloat3(&vDir));

				_Vector vRight = XMVector3Cross(XMLoadFloat3(&_float3(0.f, 1.f, 0.f)), XMLoadFloat3(&m_TempLook)); //Left;
				_float fSpeed = g_pGameInstance->Easing(TYPE_QuinticOut, 4.5f, 0.75f, (_float)PlayRate - 0.1f, 0.38f);
				m_pTransformCom->MovetoDir(-vRight, dDeltaTime * fSpeed, m_pNavigationCom);
			}
			break;
		}
		case 6:
		{
			if (m_iSoundIndex == 0 && PlayRate > 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasure_Taunt.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}
			break;
		}
		case 8:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bGroggiOn = true;
				m_iAdjMovedIndex++;
			}
			if (PlayRate > 0 && PlayRate <= 0.98)
			{
				m_bLookAtOn = false;

				m_dAcceleration = 0.3;
			}
			break;
		}
		case 15:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bLookAtOn = false;
				m_dAcceleration = 0.5;
				m_iAdjMovedIndex++;
			}
			if (m_iSoundIndex == 0 && PlayRate > 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Hit_01.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}
			break;
		}
		case 16:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate > 0)
			{
				m_bLookAtOn = false;
				m_dAcceleration = 1;

				m_iAdjMovedIndex++;
			}
			else if (0.f < PlayRate && PlayRate <= 0.478f)
			{
				m_pTransformCom->Move_Backward(dDeltaTime, m_pNavigationCom);

				m_fKnockbackDir.y = 0;

				m_pTransformCom->Turn_Dir(m_fKnockbackDir.XMVector(), 0.9f);
			}

			if (m_iSoundIndex == 0 && PlayRate > 0)
			{
				g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Hit_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
				m_iSoundIndex++;
			}
			break;
		}
		case 18:
		{
			if (m_iAdjMovedIndex == 0)
			{
				m_bLookAtOn = false;
				m_bColliderAttackOn = true;
				m_eColliderType = CMonster_Mahinasura_Minion::HANDATTACK;

				m_iAdjMovedIndex++;
			}
			if (PlayRate >= 0.27272 && PlayRate <= 0.444)
			{

				_float EasingSpeed;
				EasingSpeed = GetSingle(CGameInstance)->Easing(TYPE_QuadIn, 2.25 , 3.3f, (_float)PlayRate -0.27272f, 0.17128f);

				m_pTransformCom->Move_Forward(dDeltaTime * EasingSpeed, m_pNavigationCom);
			}
			else if (PlayRate >= 0.444 && PlayRate <= 0.6)
			{
				_float EasingSpeed;
				EasingSpeed = GetSingle(CGameInstance)->Easing(TYPE_QuadOut, 3.3f , 1.5f,static_cast<_float>(PlayRate) -0.444f, 0.156f);

				m_pTransformCom->Move_Forward(dDeltaTime * EasingSpeed, m_pNavigationCom);
			}
			break;
		}
		case 19: {

			//		MeshDesc.vLimLight = _float4(0.06f, 0.76f, 0.18f, 1.f);

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(0.57f, 1.00f, 0.79f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_iAdjMovedIndex == 0 && PlayRate >= 0.24)
			{
				m_bLookAtOn = false;
				m_bColliderAttackOn = true;
				m_eColliderType = CMonster_Mahinasura_Minion::HANDATTACK;

				
				m_iAdjMovedIndex++;
			}
			if (PlayRate >= 0.24 && PlayRate <= 0.48)
			{
				m_pTransformCom->Move_Forward(dDeltaTime * 0.9, m_pNavigationCom);
				if (m_iSoundIndex == 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Sigh_03.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					g_pGameInstance->Play3D_Sound(TEXT("EH_M1_680.mp3"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_EFFECT, 0.5f);
					m_iSoundIndex++;
				}

			}
			else if (PlayRate >= 0.49 && PlayRate <= 0.84)
			{
				m_pTransformCom->Move_Forward(dDeltaTime * 1.8, m_pNavigationCom);
				if (m_iSoundIndex == 1)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Mahinasura_Sigh_04.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					g_pGameInstance->Play3D_Sound(TEXT("EH_M1_358.mp3"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_EFFECT, 0.5f);
					m_iSoundIndex++;
				}
			}


			if (m_EffectAdjust == 0 && PlayRate >= 0.10)
			{

			

				m_EffectAdjust++;
			}


			if (m_EffectAdjust == 1 && PlayRate >= 0.3)
			{
				// #TIME Hand 2
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_MM_HAND_L, m_pTextureParticleTransform_LHand);


				auto dust2_f = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::Um_Dust_2_FounTain,
					0.01f,
					0.3f,
					_float4(0.98f, 0.28f, 0.20f, 1),
					_float4(1.0f, 0.24f, 0.24f, 1),
					3,
					_float3(0.15f, 0.35f, 0.15f),
					_float3(0.15f, 0.35f, 0.15f),
					1);

				dust2_f.Particle_Power = 8;

				_Matrix mat = m_pTextureParticleTransform_LHand->Get_WorldMatrix();
				_Vector pos = mat.r[3] + mat.r[2] * 2.5f;
				dust2_f.vFixedPosition = pos;

				GETPARTICLE->Create_Texture_Effect_Desc(dust2_f, m_eNowSceneNum);

				m_EffectAdjust++;

			}
			if (m_EffectAdjust == 2 && PlayRate >= 0.45)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_MM_HAND_R, m_pTextureParticleTransform_RHand);

				auto dust2_f = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::Um_Dust_2_FounTain,
					0.01f,
					0.3f,
					_float4(0.98f, 0.28f, 0.20f, 1),
					_float4(1.0f, 0.24f, 0.24f, 1),
					3,
					_float3(0.15f, 0.35f, 0.15f),
					_float3(0.15f, 0.35f, 0.15f),
					1);

				dust2_f.Particle_Power = 8;

				_Matrix mat = m_pTextureParticleTransform_RHand->Get_WorldMatrix();
				_Vector pos = mat.r[3] + mat.r[2] * 2.5f;
				dust2_f.vFixedPosition = pos;

				GETPARTICLE->Create_Texture_Effect_Desc(dust2_f, m_eNowSceneNum);

				m_EffectAdjust++;
			}
			break;
		}
		case 20: {

			_float Value = g_pGameInstance->Easing_Return(TYPE_Linear, TYPE_Linear, 0, 1, (_float)PlayRate, 0.9f);
			Value = max(min(Value, 1.f), 0.f);
			Set_LimLight_N_Emissive(_float4(0.57f, 1.00f, 0.79f, Value), _float4(Value, Value*0.7f, Value, 0.9f));

			if (m_iAdjMovedIndex == 0)
			{
				m_bLookAtOn = false;
				m_bColliderAttackOn = true;
				m_eColliderType = CMonster_Mahinasura_Minion::TAILATTACK;

				m_iAdjMovedIndex++;
			}
			if (PlayRate >= 0.24 && PlayRate <= 0.6)
			{

				//_float EasingSpeed;
				//EasingSpeed = GetSingle(CGameInstance)->Easing(TYPE_CircularOut, 1.7f , 1.f,(_float)PlayRate-0.24f, 0.36f);
				//m_pTransformCom->Move_Forward(dDeltaTime * EasingSpeed);

				_float fSpeed = g_pGameInstance->Easing_Return(TYPE_SinInOut, TYPE_SinInOut, 1.5f, 3.f, (_float)PlayRate-0.24f, 0.36f); // PlayRate - 0.266666 and 0.5 - 0.266666
				m_pTransformCom->Move_Forward(dDeltaTime * fSpeed, m_pNavigationCom);

				//m_pTransformCom->Move_Forward(dDeltaTime * 1.2);

				if (m_iSoundIndex == 0)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Scorpion_Tail_Slash_02.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.5f);
					g_pGameInstance->Play3D_Sound(TEXT("EH_M1_694.mp3"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_EFFECT, 0.5f);
					m_iSoundIndex++;
				}
			}

			if (m_EffectAdjust == 0)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_MM_TAIL2, m_pTextureParticleTransform_Tail);
				m_EffectAdjust++;
			}
			if (m_EffectAdjust == 1 && PlayRate >= 0.3)
			{

				auto dust2_f = GETPARTICLE->Get_EffectSetting_Tex(CPartilceCreateMgr::Um_Dust_2_FounTain,
					0.6f,
					0.5f,
					_float4(0, 0, 0, 1),
					_float4(0, 0, 0, 0.0f),
					1,
					//	_float3(0.1f, 0.5f, 0.1f),
					//	_float3(0.1f, 0.5f, 0.1f),
					_float3(0.2f),
					_float3(0.1f),
					1);

				dust2_f.iTextureLayerIndex = 43;

				dust2_f.iFollowingDir = FollowingDir_Up;
				dust2_f.Particle_Power = 8.0f;
				dust2_f.ParticleStartRandomPosMin = _float3(-1, 1, -1);
				dust2_f.ParticleStartRandomPosMax = _float3(1, 3, 1);

				//_Matrix mat = m_pTransformCom->Get_WorldMatrix();
				//_Vector pos = mat.r[3];
				//dust2_f.vFixedPosition = pos;
				dust2_f.FollowingTarget = m_pTransformCom;

				GETPARTICLE->Create_Texture_Effect_Desc(dust2_f, m_eNowSceneNum);

				dust2_f.TargetColor = _float4(1);

				GETPARTICLE->Create_Texture_Effect_Desc(dust2_f, m_eNowSceneNum);


				m_EffectAdjust++;
			}

			if (m_EffectAdjust == 2 && PlayRate >= 0.25f)
			{
				Set_Play_MeshParticle(CPartilceCreateMgr::E_MESH_EFFECTJ::MESHEFFECT_MONSTER_MM_TAIL, m_pTransformCom);
				m_EffectAdjust++;
			}

			break;
		}
		case 21: {
			m_dSoundTime += dDeltaTime;

			if (PlayRate > 0 && PlayRate >= 0.125 && m_bFastRunOn == false)
			{
				m_pTransformCom->Move_Forward(dDeltaTime * 1.8, m_pNavigationCom);
				m_bFastRunOn = true;

				if (m_dSoundTime >= 0.55)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Wave_Mahinasura_Run.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
					m_dSoundTime = 0;
				}
			}
			else if (m_bFastRunOn = true)
			{
				m_pTransformCom->Move_Forward(dDeltaTime * 1.8, m_pNavigationCom);

				if (m_dSoundTime >= 0.55)
				{
					g_pGameInstance->Play3D_Sound(TEXT("EH_Wave_Mahinasura_Run.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 0.3f);
					m_dSoundTime = 0;
				}
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

CMonster_Mahinasura_Minion * CMonster_Mahinasura_Minion::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CMonster_Mahinasura_Minion*	pInstance = NEW CMonster_Mahinasura_Minion(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Mahinasura_Minion");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMonster_Mahinasura_Minion::Clone(void * pArg)
{
	CMonster_Mahinasura_Minion*	pInstance = NEW CMonster_Mahinasura_Minion(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Mahinasura_Minion");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonster_Mahinasura_Minion::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureParticleTransform_RHand);
	Safe_Release(m_pTextureParticleTransform_LHand);
	Safe_Release(m_pTextureParticleTransform_Tail);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
	Safe_Release(m_pColliderCom);
	Safe_Release(m_pHandAttackColliderCom);
	Safe_Release(m_pTailAttackColliderCom);
	Safe_Release(m_pHPUI);
	Safe_Release(m_pDissolve);
	
		

}
