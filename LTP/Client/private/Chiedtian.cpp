#include "stdafx.h"
#include "..\public\Chiedtian.h"
#include "Chiedtuan_Weapon.h"

CChiedtian::CChiedtian(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CBoss(pDevice, pDeviceContext)
{
}

CChiedtian::CChiedtian(const CChiedtian & rhs)
	: CBoss(rhs)
{
}

HRESULT CChiedtian::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CChiedtian::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	if (pArg != nullptr)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, *((_float3*)pArg));

	m_pTransformCom->Rotation_CW(XMVectorSet(0, 1, 0, 0), XMConvertToRadians(170));

	m_pTransformCom->Scaled_All(_float3(1.5f, 1.5f, 1.5f));

	m_pModel->Change_AnimIndex(0);

	m_fAttackCoolTime = 5.f;
	m_fSkillCoolTime = 8.f;
	m_bIsHit = false;

	m_pPlayerObj = (CGameObject*)g_pGameInstance->Get_GameObject_By_LayerIndex(m_eNowSceneNum,
		TEXT("Layer_Player"));

	ATTACHEDESC		eAttachedDesc;

	eAttachedDesc.Initialize_AttachedDesc(this, "middle_metacarpal_r", XMVectorSet(1,1,1, 0.f), XMVectorSet(0.f, 90.f, 0.f, 0.f), XMVectorSet(-203.92f * 0.02f, 22.9994f * 0.02f-1.f, -285.096f * 0.02f, 1.f));
	//eAttachedDesc.Initialize_AttachedDesc(this, "middle_metacarpal_r", XMVectorSet(1, 1, 1, 0.f), XMVectorSet(-0.f, 0.f, 0.f, 0.f), XMVectorSet(-0.f, 0.f, -0.f, 1.f));
	//eAttachedDesc.Initialize_AttachedDesc(this, "middle_metacarpal_r", XMVectorSet(100.f, 100.f, 100.f, 0.f), XMVectorSet(90.f, 0.f, 180.f, 0.f), XMVectorSet(-203.64f, 22.821, -298.01, 1.f));

	/*CChiedtuan_Weapon* ChiedtuanWeapon = nullptr;
	g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum,TEXT("Weapon"), TAG_OP(Prototype_Object_Boss_ChiedtianWeapon), &eAttachedDesc);*/
	//m_pWeapons.push_back(ChiedtuanWeapon);


	return S_OK;
}

_int CChiedtian::Update(_double fDeltaTime)
{
	if (__super::Update(fDeltaTime) < 0)return -1;

	m_fAttackCoolTime -= (_float)fDeltaTime;
	m_fSkillCoolTime -= (_float)fDeltaTime;
	m_fJumpTime -= (_float)fDeltaTime;
	
	if (m_bIsFireAttack)
		m_fFireTime -= (_float)fDeltaTime;

	if (m_fFireTime <= 0 && m_bIsFireAttack)
	{
		m_fFireTime = 10.f;
		m_bIsFireAttack = false;

		m_pModel->Change_AnimIndex_ReturnTo(14, 0);
	}

	if (m_bIsSpinAttack)
		m_fSpinTime -= (_float)fDeltaTime;

	if (m_fSpinTime <= 0 && m_bIsSpinAttack)
	{
		m_fSpinTime = 14.f;
		m_bIsSpinAttack = false;

		m_fAttackCoolTime = 1.f;
		m_fSkillCoolTime = 6.f;

		m_pModel->Change_AnimIndex(0, 2.f);
	}


	if (m_bIsLookAt)
	{
		CTransform* PlayerTransform = (CTransform*)m_pPlayerObj->Get_Component(TAG_COM(Com_Transform));
		_float3 PlayerPos = PlayerTransform->Get_MatrixState(CTransform::STATE_POS);

		PlayerPos.y = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y;
		_Vector Dir = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);
		Dir = XMVector3Normalize(PlayerPos.XMVector() - XMVectorSetY(Dir, PlayerPos.y));
		m_pTransformCom->Turn_Dir(Dir, 0.90f);

		m_fRange = XMVectorGetX(XMVector3Length(XMLoadFloat3(&PlayerPos) - m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));
	}


	//if (g_pGameInstance->Get_DIKeyState(DIK_M)& DIS_Down)
	//{
	//	m_pModel->Change_AnimIndex(m_iAniNum);
	//	++m_iAniNum;
	//}

	//if (m_iAniNum > 13)
	//	m_iAniNum = 0;

	//m_pModel->Change_AnimIndex(0);

	if (g_pGameInstance->Get_DIKeyState(DIK_N)& DIS_Down)
	{
		m_fTestHPIndex += 0.2f;
	}
	if (m_fTestHPIndex >= 1.4f)
		m_bIsHalf = true;

	//�¾�����
	if (m_bIsHit)
	{
		m_bIsHit = false;
		m_bIsAttack = true;
		m_pModel->Change_AnimIndex_UntilNReturn(2, 3, 0);
	}
	else if (!m_bIsHit && !m_bIsAttack && m_fRange < 10.f &&m_fJumpTime <= 0)
	{
		m_bIsAttack = true;
		m_pModel->Change_AnimIndex_ReturnTo(10, 0);
	}
	//�Ϲ� ����
	//else if (m_fAttackCoolTime <= 0 && !m_bIsAttack && !m_bIsHit)
	//{
	//	m_bIsAttack = true;

	//	//if (m_fRange < 15.f)
	//	//{
	//	//	m_bIsBackJump = true;
	//	//	m_pModel->Change_AnimIndex_ReturnTo(10, 5);
	//	//}
	//	//else
	//	//{
	//	//	m_bIsBackJump = false;
	//	//	m_pModel->Change_AnimIndex_ReturnTo(5, 0);
	//	//}

	//	m_pModel->Change_AnimIndex_ReturnTo(5, 0);

	//}
	//��ų ����
	else if (m_fSkillCoolTime <= 0 && !m_bIsAttack && !m_bIsHit)
	{
		//_int iRandom = rand() & 2;
		//m_bIsAttack = true;

		//switch (iRandom)
		//{
		//case ATTACK_FIRE:
		//{
		//	m_pModel->Change_AnimIndex_ReturnTo(12, 13);
		//}
		//	break;
		//case ATTACK_SPIN:
		//{
		//	m_pModel->Change_AnimIndex_UntilNReturn(7, 8, 9);
		//}
		//	break;

		//case ATTACK_WHINING:
		//{
		//	m_pModel->Change_AnimIndex_ReturnTo(6, 0);
		//}
		//	break;

		//}
		
		m_bIsAttack = true;
		m_pModel->Change_AnimIndex_UntilNReturn(7, 8, 9);
	}


	m_bIsOnScreen = g_pGameInstance->IsNeedToRender(m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS), m_fFrustumRadius);
	FAILED_CHECK(m_pModel->Update_AnimationClip(fDeltaTime * (m_fAnimmultiple* m_fTestHPIndex), m_bIsOnScreen));
	FAILED_CHECK(Adjust_AnimMovedTransform(fDeltaTime));

	for (auto& Weapon : m_pWeapons)
		Weapon->Update(fDeltaTime);

	return _int();
}

_int CChiedtian::LateUpdate(_double fDeltaTime)
{
	if (__super::LateUpdate(fDeltaTime) < 0)return -1;


	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this, m_pTransformCom, m_pShaderCom, m_pModel));
	FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	m_vOldPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);
	//g_pGameInstance->Set_TargetPostion(PLV_PLAYER, m_vOldPos);

	for (auto& Weapon : m_pWeapons)
		Weapon->LateUpdate(fDeltaTime);

	return _int();
}

_int CChiedtian::Render()
{
	if (__super::Render() < 0)		return -1;

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

_int CChiedtian::LateRender()
{
	if (__super::LateRender() < 0)		return -1;

	return _int();
}

HRESULT CChiedtian::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Boss_Chieftian), TAG_COM(Com_Model), (CComponent**)&m_pModel));
	FAILED_CHECK(m_pModel->Change_AnimIndex(0));


	CTransform::TRANSFORMDESC tDesc = {};

	tDesc.fMovePerSec = 5;
	tDesc.fRotationPerSec = XMConvertToRadians(60);
	tDesc.fScalingPerSec = 1;
	tDesc.vPivot = _float3(0, 0, 0);

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));


	return S_OK;
}

HRESULT CChiedtian::Adjust_AnimMovedTransform(_double fDeltatime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.98)
		m_iAdjMovedIndex = 0;


	if (PlayRate <= 0.98)
	{
		switch (iNowAnimIndex)
		{
		case 0:
			//Idle
			if (PlayRate > 0.f)
			{
				m_bIsAttack = false;
				m_bIsLookAt = true;
				//m_bIsBackJump = false;

			}
			break;
		case 1://�ִϸ��̼� �ε������� ����ָ� ��

			break;
		case 2:

			break;

		case 3:
			break;

		case 4:
		{

		}

		break;

		case 5:
		{
			if (m_iAdjMovedIndex == 0 && PlayRate < 0.2926829268)
			{
				m_bIsLookAt = false;
				m_iAdjMovedIndex++;
			}
		}

		break;

		case 6:
		{

		}
			break;

		case 7://SpinAttackStartAnim
		{
			m_bIsLookAt = false;
		}

		break;

		case 9://SpinAttackAnim
		{
			_float3 MonsterPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);

			CTransform* PlayerTransform = (CTransform*)m_pPlayerObj->Get_Component(TAG_COM(Com_Transform));
			_float3 PlayerPos = PlayerTransform->Get_MatrixState(CTransform::STATE_POS);

			PlayerPos.y = MonsterPos.y;

			_float3 vGoalDir = (PlayerPos.XMVector() - MonsterPos.XMVector());

			m_pTransformCom->Turn_CW(XMVectorSet(0.f,1.f,0.f,0.f), fDeltatime);
			m_pTransformCom->MovetoDir(XMLoadFloat3(&vGoalDir), fDeltatime * 0.3);

		}

		break;

		case 10://Jump Animation
		{
			if (m_iAdjMovedIndex == 0 && PlayRate < 0.2926829268)
			{
				m_bIsLookAt = false;
				m_iAdjMovedIndex++;
			}
			/*if (m_bIsBackJump)
			{
				if (PlayRate > 0.317073170 && PlayRate < 0.63414634146)
				{
					m_bIsLookAt = true;

					_float3 MonsterPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);

					_float3 GoalPos = XMLoadFloat3(&MonsterPos) + (XMVector3Normalize(m_pTransformCom->Get_MatrixState(CTransform::STATE_LOOK)) * -2.f);

					_float3 vGoalDir = (GoalPos.XMVector() - MonsterPos.XMVector());

					_float fLength = g_pGameInstance->Easing(TYPE_CircularIn, 0.f, vGoalDir.Get_Lenth(), (_float)PlayRate - 0.317073170f, 0.31707317146f);

					m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, (MonsterPos.XMVector() + vGoalDir.Get_Nomalize() * fLength));
				}
			}
			else
			{
				if (PlayRate > 0.317073170 && PlayRate < 0.63414634146)
				{
					m_bIsLookAt = true;

					_float3 MonsterPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);

					CTransform* PlayerTransform = (CTransform*)m_pPlayerObj->Get_Component(TAG_COM(Com_Transform));
					_float3 PlayerPos = PlayerTransform->Get_MatrixState(CTransform::STATE_POS);

					PlayerPos.y = MonsterPos.y;

					_float3 vGoalDir = (PlayerPos.XMVector() - MonsterPos.XMVector());

					_float fLength = g_pGameInstance->Easing(TYPE_CircularIn, 0.f, vGoalDir.Get_Lenth(), (_float)PlayRate - 0.317073170f, 0.31707317146f);

					m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, (MonsterPos.XMVector() + vGoalDir.Get_Nomalize() * fLength));
				}
			}*/
			if (PlayRate > 0.317073170 && PlayRate < 0.63414634146)
			{
				m_bIsLookAt = true;

				_float3 MonsterPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);

				CTransform* PlayerTransform = (CTransform*)m_pPlayerObj->Get_Component(TAG_COM(Com_Transform));
				_float3 PlayerPos = PlayerTransform->Get_MatrixState(CTransform::STATE_POS);

				PlayerPos.y = MonsterPos.y;

				_float3 vGoalDir = (PlayerPos.XMVector() - MonsterPos.XMVector());

				_float fLength = g_pGameInstance->Easing(TYPE_CircularIn, 0.f, vGoalDir.Get_Lenth(), (_float)PlayRate - 0.317073170f, 0.31707317146f);

				m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, (MonsterPos.XMVector() + vGoalDir.Get_Nomalize() * fLength));
			}
			if (m_iAdjMovedIndex == 1 && PlayRate > 0.63414634146)
			{
				m_bIsLookAt = false;
				m_iAdjMovedIndex++;
			}
		}
		break;

		case 12: //FireAttackStartAnim
		{
			m_bIsLookAt = false;
			m_fAnimmultiple = 2.f;
		}
		break;

		case 13: //FireAttack
		{
			m_bIsLookAt = true;

			m_pTransformCom->Move_Forward(fDeltatime * 1.2);

		}
		break;

		case 14: //FireAttackEnd
		{
			m_bIsLookAt = false;


			//�������
		}
		break;

		}
	}
	else
	{
		//if (iNowAnimIndex == 0)
		//{
		//	m_bIsAttack = false;
		//	m_bIsLookAt = true;
		//}
		/*if (iNowAnimIndex == 6 || iNowAnimIndex == 7)
		{
			m_bIsLookAt = true;
			m_fAttackCoolTime = 5.f - m_fTestHPIndex;
		}

		if (iNowAnimIndex == 5 || iNowAnimIndex == 4)
		{
			m_fSkillCoolTime = 8.f - m_fTestHPIndex;
			m_fAttackCoolTime = 5.f - m_fTestHPIndex;
		}

		if (iNowAnimIndex == 3)
		{
			m_bIsLookAt = true;
			m_fSkillCoolTime = 8.f - m_fTestHPIndex;
			m_fAttackCoolTime = 5.f - m_fTestHPIndex;
		}*/

		if (iNowAnimIndex == 5)
		{
			m_bIsLookAt = true;
			m_fAttackCoolTime = 4.f;
			m_fSkillCoolTime = 2.f;

			m_pModel->Change_AnimIndex(0);
		}
		if (iNowAnimIndex == 8)
		{
			m_bIsSpinAttack = true;
			m_fSpinTime = 14.f;
		}
		if (iNowAnimIndex == 10)
		{

			m_bIsLookAt = true;
			m_fJumpTime = 3.f;

		}
		if (iNowAnimIndex == 12)
		{
			m_bIsLookAt = true;
			m_bIsFireAttack = true;
			m_fFireTime = 10.f;
		}
		if (iNowAnimIndex == 14)
		{
			m_bIsLookAt = true;
			m_fAttackCoolTime = 0.5f;
			m_fSkillCoolTime = 6.f;
			m_fAnimmultiple = 1.f;
		}
	}


	m_iOldAnimIndex = iNowAnimIndex;
	return S_OK;
}

CChiedtian * CChiedtian::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CChiedtian*	pInstance = new CChiedtian(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CChiedtian");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CChiedtian::Clone(void * pArg)
{
	CChiedtian*	pInstance = new CChiedtian(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created  Clone CChiedtian");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CChiedtian::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);

	for (auto& Weapon : m_pWeapons)
		Safe_Release(Weapon);

	m_pWeapons.clear();
}
