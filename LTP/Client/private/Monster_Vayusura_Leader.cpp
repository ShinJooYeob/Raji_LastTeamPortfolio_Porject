#include "stdafx.h"
#include "..\public\Monster_Vayusura_Leader.h"
#include "Monster_Bullet_Universal.h"


CMonster_Vayusura_Leader::CMonster_Vayusura_Leader(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CMonster(pDevice, pDeviceContext)
{
}

CMonster_Vayusura_Leader::CMonster_Vayusura_Leader(const CMonster_Vayusura_Leader & rhs)
	: CMonster(rhs)
{
}

HRESULT CMonster_Vayusura_Leader::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CMonster_Vayusura_Leader::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	if (pArg != nullptr)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, *((_float3*)pArg));

	m_pTransformCom->Rotation_CW(XMVectorSet(0, 1, 0, 0), XMConvertToRadians(170));


	SetUp_Info();

	return S_OK;
}

_int CMonster_Vayusura_Leader::Update(_double dDeltaTime)
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

	return _int();
}

_int CMonster_Vayusura_Leader::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;

	//////////
	if (m_bIsOnScreen)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}
	//////////

	//FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this, m_pTransformCom, m_pShaderCom, m_pModel));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

	return _int();
}

_int CMonster_Vayusura_Leader::Render()
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

_int CMonster_Vayusura_Leader::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;

	return _int();
}

void CMonster_Vayusura_Leader::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	if (CollisionTypeID::CollisionType_Player == eConflictedObjCollisionType)
	{
		_Vector vDamageDir = XMVector3Normalize(pConflictedCollider->Get_ColliderPosition(iConflictedObjColliderIndex).XMVector() - m_pTransformCom->Get_MatrixState(CTransform::TransformState::STATE_POS));
		pConflictedObj->Take_Damage(this, 1.f, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower);
		pConflictedCollider->Set_Conflicted(1.f);
	}
}

_float CMonster_Vayusura_Leader::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
{
	if (0 >= m_fHP)
	{
		return -1.f;
	}

	return _float();
}

HRESULT CMonster_Vayusura_Leader::SetUp_Info()
{

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(2.f, 0.f, 2.f));


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_pPlayerTransform = static_cast<CTransform*>(pGameInstance->Get_Commponent_By_LayerIndex(m_eNowSceneNum, TAG_LAY(Layer_Player), TAG_COM(Com_Transform)));

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

HRESULT CMonster_Vayusura_Leader::SetUp_Fight(_double dDeltaTime)
{
	m_fDistance = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).Get_Distance(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS));


	m_fPlayerPos = m_pPlayerTransform->Get_MatrixState_Float3(CTransform::STATE_POS);


	if (m_bLookAtOn)
	{

		_Vector vTarget = XMVector3Normalize(m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));

		m_pTransformCom->Turn_Dir(vTarget, 0.95f);
	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Leader::PlayAnim(_double dDeltaTime)
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

HRESULT CMonster_Vayusura_Leader::CoolTime_Manager(_double dDeltaTime)
{
	//�ѹ��� �����ϴ� �ִϸ��̼�

	m_dOnceCoolTime += dDeltaTime;

	if (m_dOnceCoolTime > 6)
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
	if (m_dInfinity_CoolTime >= 2.5)
	{
		m_iInfinityPattern = rand() % 4;


		CUtilityMgr* pUtil = GetSingle(CUtilityMgr);

		XMStoreFloat4(&m_fDirection, XMVector3Normalize(m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK) * pUtil->RandomFloat(-1, 1) + m_pTransformCom->Get_MatrixState(CTransform::STATE_RIGHT) * pUtil->RandomFloat(-1, 1)));

		if (m_fDistance > 12)
		{
			m_iInfinityPattern = 10;
		}

		m_dInfinity_CoolTime = 0;
	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Leader::Once_AnimMotion(_double dDeltaTime)
{

	switch (m_iOncePattern)
	{
	case 0:
		m_iOnceAnimNumber = 6; //Vayusura_Dive
		break;
	case 1:
		m_iOnceAnimNumber = 6; //Vayusura_Dive
		break;

	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Leader::Pattern_Change()
{

	m_iOncePattern += 1;

	if (m_iOncePattern > 1)
	{
		m_iOncePattern = 0;
	}


	return S_OK;
}

HRESULT CMonster_Vayusura_Leader::Infinity_AnimMotion(_double dDeltaTime)
{
	switch (m_iInfinityPattern)
	{
	case 0:
		if (m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y < m_fPlayerPos.y + 7)
		{
			m_pTransformCom->MovetoDir(XMLoadFloat4(&_float4(0.f, 1.f, 0.f, 0.f)), dDeltaTime * 0.5);

			m_pTransformCom->MovetoDir(XMLoadFloat4(&m_fDirection), dDeltaTime * 0.5);
		}
		m_iInfinityAnimNumber = 0; // flapping
		break;
	case 1:
		if (m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y > m_fPlayerPos.y + 4)
		{
			m_pTransformCom->MovetoDir(XMLoadFloat4(&_float4(0.f, 1.f, 0.f, 0.f)), -dDeltaTime * 0.5);

			m_pTransformCom->MovetoDir(XMLoadFloat4(&m_fDirection), dDeltaTime * 0.5);
		}
		m_iInfinityAnimNumber = 0;
		break;
	case 2:
		if (m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y < m_fPlayerPos.y + 7 ||
			m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y > m_fPlayerPos.y + 3)
		{

			m_pTransformCom->MovetoDir(XMLoadFloat4(&m_fDirection), dDeltaTime * 0.5);
		}
		m_iInfinityAnimNumber = 1;
		break;
	case 3:
		if (m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y < m_fPlayerPos.y + 7 ||
			m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y > m_fPlayerPos.y + 3)
		{

			m_pTransformCom->MovetoDir(XMLoadFloat4(&m_fDirection), dDeltaTime * 0.5);
		}
		m_iInfinityAnimNumber = 1;
		break;
	case 10:
	{
		_float3 fTempPlayerPos = m_fPlayerPos;

		fTempPlayerPos.y += 5;

		_Vector vTarget = XMVector3Normalize(XMLoadFloat3(&fTempPlayerPos) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
		//m_pTransformCom->Turn_Dir(vTarget, 0.9f);
		if (m_fDistance > 7)
		{
			m_pTransformCom->Turn_Dir(vTarget, 0.9f);

			m_pTransformCom->MovetoDir(vTarget, dDeltaTime );
			m_iInfinityAnimNumber = 2;
		}
		else {

		}
		break;
	}
	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Leader::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Monster_Vayusura_Leader), TAG_COM(Com_Model), (CComponent**)&m_pModel));
	FAILED_CHECK(m_pModel->Change_AnimIndex(0));


	CTransform::TRANSFORMDESC tDesc = {};

	tDesc.fMovePerSec = 5;
	tDesc.fRotationPerSec = XMConvertToRadians(60);
	tDesc.vPivot = _float3(0, 0, 0);
	tDesc.fScalingPerSec = 1;

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));


	return S_OK;
}

HRESULT CMonster_Vayusura_Leader::Adjust_AnimMovedTransform(_double dDeltaTime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.98)
	{
		m_iAdjMovedIndex = 0;

		m_bLookAtOn = true;

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
		case 1://�ִϸ��̼� �ε������� ����ָ� ��
			if (m_iAdjMovedIndex == 0 && PlayRate > 0.0) // �̷��� �Ǹ� ���� �ִϸ��̼ǿ��� �����Ǵ� �ð� ������ ���� �ٷ� ���� ��, PlayRate�� 0�� >= �������� >�� �ϼ�
			{

				m_iAdjMovedIndex++; //�ִϸ��̼��� ������ �� �ѹ��� �ߵ���Ű�� ���� ++��Ų��.
			}
			else if (m_iAdjMovedIndex == 1 && PlayRate > 0.7666666666666666) //Ư�� ������ �÷��� ����Ʈ���Ŀ� ���������
			{


				m_iAdjMovedIndex++;
			}

			break;
		case 2:
			break;
		case 6:
			if (m_iAdjMovedIndex == 0 && PlayRate > 0) // �̷��� �Ǹ� ���� �ִϸ��̼ǿ��� �����Ǵ� �ð� ������ ���� �ٷ� ���� ��, PlayRate�� 0�� >= �������� >�� �ϼ�
			{
				m_bAttackFrieOn = false;

				CMonster_Bullet_Universal::MONSTER_BULLET_UNIVERSALDESC Monster_BulletDesc;

				Monster_BulletDesc.iBulletMeshNumber = CMonster_Bullet_Universal::VAYUSURA_LEADER_BULLET;
				Monster_BulletDesc.fSpeedPerSec = 10;
				Monster_BulletDesc.fScale = _float3(0.1f,0.1f,0.1f);

				Monster_BulletDesc.Object_Transform = m_pTransformCom;
				Monster_BulletDesc.fPositioning = _float3(-0.0016327f, 0.0032063f, 0.023993f);


				Monster_BulletDesc.Object = this;

				Monster_BulletDesc.dDuration = 15;

				Monster_BulletDesc.bBornAttachOn = true;
				Monster_BulletDesc.pBoneName = "heel_twist_01_r";

				FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_MonsterBullet), TAG_OP(Prototype_Object_Monster_Bullet_Universal), &Monster_BulletDesc));
				m_iAdjMovedIndex++; //�ִϸ��̼��� ������ �� �ѹ��� �ߵ���Ű�� ���� ++��Ų��.
			}
			else if (m_iAdjMovedIndex == 1 && PlayRate >= 0.792411)
			{
				m_bAttackFrieOn = true;
			}
			break;
		}
	}

	m_iOldAnimIndex = iNowAnimIndex;
	return S_OK;
}

CMonster_Vayusura_Leader * CMonster_Vayusura_Leader::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CMonster_Vayusura_Leader*	pInstance = NEW CMonster_Vayusura_Leader(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Vayusura_Leader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMonster_Vayusura_Leader::Clone(void * pArg)
{
	CMonster_Vayusura_Leader*	pInstance = NEW CMonster_Vayusura_Leader(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CMonster_Vayusura_Leader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonster_Vayusura_Leader::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
}