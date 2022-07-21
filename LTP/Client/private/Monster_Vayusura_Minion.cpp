#include "stdafx.h"
#include "..\public\Monster_Vayusura_Minion.h"


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

	///////////////////test

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(198.943f, 29.2f, 179.853f));

	//m_pNavigationCom->FindCellIndex(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));
	///////////////////

	return S_OK;
}

_int CMonster_Vayusura_Minion::Update(_double dDeltaTime)
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

_int CMonster_Vayusura_Minion::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;

	//////////
	if (m_bIsOnScreen)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}
	//////////
	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this,m_pTransformCom,m_pShaderCom,m_pModel));

	//FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

#ifdef _DEBUG
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pAttackColliderCom));
#endif

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

	_uint NumMaterial = m_pModel->Get_NumMaterial();

	for (_uint i = 0; i < NumMaterial; i++)
	{
		for (_uint j = 0; j < AI_TEXTURE_TYPE_MAX; j++)
			FAILED_CHECK(m_pModel->Bind_OnShader(m_pShaderCom, i, j, MODLETEXTYPE(j)));
		FAILED_CHECK(m_pModel->Render(m_pShaderCom, 3, i, "g_BoneMatrices"));
	}



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
		pConflictedObj->Take_Damage(this, 1.f, vDamageDir, m_bOnKnockbackCol, m_fKnockbackColPower);
		pConflictedCollider->Set_Conflicted(1.f);
	}
}

_float CMonster_Vayusura_Minion::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
{
	return _float();
}

HRESULT CMonster_Vayusura_Minion::SetUp_Info()
{

	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, _float3(2.f, 0.f, 2.f));


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
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.033178f, -0.45067f));
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
	ColliderDesc.vScale = _float3(0.7f, 0.7f, 0.7f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pAttackColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "spine_01", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(0.f, 0.033178f, -0.45067f)); //������ ���ڿ� ���� �� ��ġ �״�� �־��� �� �ٸ� z�� -�� ���ٰ�
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

	FAILED_CHECK(g_pGameInstance->Add_RepelGroup(m_pTransformCom, 1.5f, m_pNavigationCom));
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

	//m_dOnceCoolTime += dDeltaTime;

	//if (m_dOnceCoolTime > 2 && m_fDistance < 3 || m_bComboAnimSwitch == true)
	//{
	//	m_dOnceCoolTime = 0;
	//	m_dInfinity_CoolTime = 0;

	//	if (m_bIOnceAnimSwitch == false)
	//	{
	//		Pattern_Change();


	//		m_bIOnceAnimSwitch = true;
	//	}
	//}

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
			//m_TempPlayerPos = m_pPlayerTransform->Get_MatrixState_Float3(CTransform::STATE_POS);

			m_dAttackOn = true;
		}

	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Once_AnimMotion(_double dDeltaTime)
{

	switch (m_iOncePattern)
	{
	case 0:
		m_iOnceAnimNumber = 5; //Vayusura_Dive
		break;
	case 1:
		m_iOnceAnimNumber = 5; //Vayusura_Dive
		break;

	}

	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Infinity_AnimMotion(_double dDeltaTime)
{
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

HRESULT CMonster_Vayusura_Minion::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Monster_Vayusura_Minion), TAG_COM(Com_Model), (CComponent**)&m_pModel));
	FAILED_CHECK(m_pModel->Change_AnimIndex(0));


	CTransform::TRANSFORMDESC tDesc = {};

	tDesc.fMovePerSec = 5;
	tDesc.fRotationPerSec = XMConvertToRadians(60);
	tDesc.vPivot = _float3(0, 0, 0);
	tDesc.fScalingPerSec = 1;

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));


	return S_OK;
}

HRESULT CMonster_Vayusura_Minion::Adjust_AnimMovedTransform(_double dDeltaTime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.98)
	{
		m_iAdjMovedIndex = 0;

		if (PlayRate > 0.98 && m_bIOnceAnimSwitch == true)
		{
			m_bIOnceAnimSwitch = false;
			m_dOnceCoolTime = 0;
			m_dInfinity_CoolTime = 0;
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
}
