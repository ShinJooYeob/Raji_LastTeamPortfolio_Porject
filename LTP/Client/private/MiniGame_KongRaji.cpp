#include "stdafx.h"
#include "..\public\MiniGame_KongRaji.h"
#include "Camera_Main.h"
#include "Scene.h"
#include "PartilceCreateMgr.h"
#include "WorldTexture_Universal.h"
#include "KongRajiTrigger.h"

/*
1. Main Cam -> FocusTarget Settomg
2. Target Obj->Set_AttachCamPos()
3. Main Cam->Lock_CamLook(true, Look)
4. Main Cam->Set_TargetArmLength, Max, Min, Or Cur
*/

CMiniGame_KongRaji::CMiniGame_KongRaji(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CGameObject(pDevice, pDeviceContext)
{
}

CMiniGame_KongRaji::CMiniGame_KongRaji(const CMiniGame_KongRaji & rhs)
	: CGameObject(rhs)
{
}


HRESULT CMiniGame_KongRaji::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CMiniGame_KongRaji::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	if (pArg != nullptr)
		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, *((_float3*)pArg));


	m_pTransformCom->Rotation_CW(XMVectorSet(0, 1, 0, 0), XMConvertToRadians(180));


	SetUp_Info();
	SetUp_Texture();

	Camera_Pos();


	m_pNavigationCom->Set_CurNavCellIndex(m_iNaviIndex);
	m_pTransformCom->LookDir(XMVectorSet(-1.f, 0.f, 0.f, 0.f));
	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, XMVectorSet(53.42f,33.49f,40.f,1.f));


	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_DonkeyKong_Trigger), TAG_OP(Prototype_Object_KongRajiTrigger)));
	//FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_DonkeyKong_Trigger), TAG_OP(Prototype_Object_DonkeyKong_BulletTrigger)));



	return S_OK;

}

_int CMiniGame_KongRaji::Update(_double dDeltaTime)
{
	if (__super::Update(dDeltaTime) < 0)return -1;

	if (m_fHP <= 0)
	{
		m_pDissolve->Update_Dissolving(dDeltaTime);
		m_pDissolve->Set_DissolveOn(false, 2.f);

		m_dDissolveTime += dDeltaTime;

		//if (m_bDieSound == false && m_dDissolveTime >= 1.)
		//{
		//	g_pGameInstance->Play3D_Sound(TEXT("EH_Wave_Tezabsura_Damage_2.wav"), m_pTransformCom->Get_MatrixState(CTransform::STATE_POS), CHANNELID::CHANNEL_MONSTER, 1.f);
		//	m_bDieSound = true;
		//}

		if (m_dDissolveTime >= 2)
		{
			Set_IsDead();
		}
	}

	Play_MiniGame(dDeltaTime);

	m_pModel->Change_AnimIndex(m_iAnimIndex, 0.1f);


	m_bIsOnScreen = g_pGameInstance->IsNeedToRender(m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS), m_fFrustumRadius);


	FAILED_CHECK(m_pModel->Update_AnimationClip(dDeltaTime * 1, m_bIsOnScreen));

	FAILED_CHECK(Adjust_AnimMovedTransform(dDeltaTime));

	Update_Collider(dDeltaTime);

	m_pNavigationCom->Set_CurNavCellIndex(m_iNaviIndex);

	//test
	//m_pNavigationCom->Set_CurNavCellIndex(7);
	//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));

	int a = 10;
	return _int();
}

_int CMiniGame_KongRaji::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;

	if (m_bIsOnScreen)
	{
		FAILED_CHECK(m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this));
	}

	FAILED_CHECK(m_pRendererCom->Add_ShadowGroup(CRenderer::SHADOW_ANIMMODEL, this, m_pTransformCom, m_pShaderCom, m_pModel, nullptr, m_pDissolve));

#ifdef _DEBUG
	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));
#endif

	return _int();
}

_int CMiniGame_KongRaji::Render()
{
	if (__super::Render() < 0)
		return -1;

	NULL_CHECK_RETURN(m_pModel, E_FAIL);

	CGameInstance* pInstance = GetSingle(CGameInstance);
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_VIEW), sizeof(_float4x4)));
	FAILED_CHECK(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pInstance->Get_Transform_Float4x4_TP(PLM_PROJ), sizeof(_float4x4)));


	FAILED_CHECK(m_pTransformCom->Bind_OnShader(m_pShaderCom, "g_WorldMatrix"));

	FAILED_CHECK(m_pDissolve->Render(3)); //������ ���ο��� ���� ���׸����� ã���ְ� ����

#ifdef _DEBUG
	FAILED_CHECK(m_pNavigationCom->Render());
#endif

	return _int();
}

_int CMiniGame_KongRaji::LateRender()
{
	return _int();
}

void CMiniGame_KongRaji::Set_IsDead()
{
	__super::Set_IsDead();


	//CUI_Texture_Universal::UI_TEXTURE_UNIVERSALDESC UI_Texture_UniversalDesc;

	//UI_Texture_UniversalDesc.iUI_TextureType = CUI_Texture_Universal::UI_TEXT;
	//UI_Texture_UniversalDesc.iTextureIndex = 3;

	//UI_Texture_UniversalDesc.fSizeX = 700.f;
	//UI_Texture_UniversalDesc.fSizeY = 500.f;
	//UI_Texture_UniversalDesc.fX = 640.f;
	//UI_Texture_UniversalDesc.fY = 360.f;
	//UI_Texture_UniversalDesc.fDepth = 10.f;

	//g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_UI_Texture_Universal), TAG_OP(Prototype_Object_UI_Texture_Universal), &UI_Texture_UniversalDesc);

}

void CMiniGame_KongRaji::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
}

_float CMiniGame_KongRaji::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
{
	//m_pHPUI->Set_ADD_HitCount((_int)fDamageAmount);
	//m_fHP += -fDamageAmount;


	if (0 >= m_fHP)
	{
		return -1.f;
	}

	return _float();
}

void CMiniGame_KongRaji::Update_AttachCamPos()
{
	_Vector vMyPos = XMVectorSet(40.f, 40.f, 40.f, 1.f);
	_float3 vBonePos = Get_BonePos("skd_hip");
	m_fAttachCamPos_Offset.y = 0.f;
	m_fAttachCamPos_Offset.x = 0.f;
	m_fAttachCamPos_Offset.z = -15.f;
	m_pMainCamera->Set_TargetArmLength(0.f);
	XMStoreFloat3(&m_fAttachCamPos, vMyPos + m_fAttachCamPos_Offset.XMVector());
	//m_fAttachCamPos_Offset���� �ǹ� ����

	CCamera_Main* pMainCam = ((CCamera_Main*)(g_pGameInstance->Get_GameObject_By_LayerIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main))));
	_float _fCameraArmLength = pMainCam->Get_TargetArmLength();
	CTransform* pCamTransform = pMainCam->Get_Camera_Transform();

	XMStoreFloat3(&m_fAttachCamPos, m_fAttachCamPos.XMVector() - pCamTransform->Get_MatrixState(CTransform::TransformState::STATE_LOOK) * _fCameraArmLength);

	//m_fAttachCamLook = XMVector3Normalize((XMVectorSetW(vBonePos.XMVector() - m_fAttachCamPos.XMVector(), 0.f))) + m_fAttachCamLook_Offset.XMVector();
	//ī�޶� �ٶ󺸴� ������ �� �ּ����� �˷��ְ� ��ó�� �� ���밪 �־��൵ ��
	m_pMainCamera->Lock_CamLook(true, XMVectorSet(0.f, 0.f, 1.f, 0.f));

	//Bone is Look
	//m_pMainCamera->Lock_CamLook(true,XMVector3Normalize(vBonePos.XMVector()- m_fAttachCamPos.XMVector()));

	//Dir is Look
	//m_pMainCamera->Lock_CamLook(true, XMVector3Normalize(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS) - m_fAttachCamPos.XMVector()));


	/*m_fAttachCamPos = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);
	m_fAttachCamPos.y += 2.f;
	m_fAttachCamPos.z -= 4.f;*/
}

void CMiniGame_KongRaji::Set_HeightPos(_float3 fColliderPos[HEIGHT_END])
{
	m_fHeightPos[HEIGHT_ONE_POINT] = fColliderPos[HEIGHT_ONE_POINT];
	m_fHeightPos[HEIGHT_TWO_POINT] = fColliderPos[HEIGHT_TWO_POINT];
}

HRESULT CMiniGame_KongRaji::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VAM), TAG_COM(Com_Shader), (CComponent**)&m_pShaderCom));

	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Mesh_Player), TAG_COM(Com_Model), (CComponent**)&m_pModel));
	FAILED_CHECK(m_pModel->Change_AnimIndex(0));

	CTransform::TRANSFORMDESC tDesc = {};

	tDesc.fMovePerSec = 5;
	tDesc.fRotationPerSec = XMConvertToRadians(60);
	tDesc.vPivot = _float3(0, 0, 0);
	tDesc.fScalingPerSec = 1;

	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom, &tDesc));


	CDissolve::DISSOLVEDESC DissolveDesc;
	DissolveDesc.pModel = m_pModel;
	DissolveDesc.eDissolveModelType = CDissolve::DISSOLVE_ANIM;
	DissolveDesc.pShader = m_pShaderCom;
	DissolveDesc.RampTextureIndex = 4;
	FAILED_CHECK(Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Dissolve), TAG_COM(Com_Dissolve), (CComponent**)&m_pDissolve, &DissolveDesc));


	CNavigation::NAVIDESC NaviDesc;
	NaviDesc.iCurrentIndex = 0;
	if (FAILED(__super::Add_Component(m_eNowSceneNum, TAG_CP(Prototype_Navigation), TAG_COM(Com_Navaigation), (CComponent**)&m_pNavigationCom, &NaviDesc)))
		return E_FAIL;


	SetUp_Collider();

	return S_OK;
}

HRESULT CMiniGame_KongRaji::Adjust_AnimMovedTransform(_double dDeltatime)
{
	_uint iNowAnimIndex = m_pModel->Get_NowAnimIndex();
	_double PlayRate = m_pModel->Get_PlayRate();

	if (iNowAnimIndex != m_iOldAnimIndex || PlayRate > 0.98)
		m_iAdjMovedIndex = 0;


	if (PlayRate <= 0.98)
	{
		switch (iNowAnimIndex)
		{
		case 1://�ִϸ��̼� �ε������� ����ָ� ��
			if (m_iAdjMovedIndex == 0 && PlayRate > 0.0) // �̷��� �Ǹ� ���� �ִϸ��̼ǿ��� �����Ǵ� �ð� ������ ���� �ٷ� ����
			{

				m_iAdjMovedIndex++;
			}
			else if (m_iAdjMovedIndex == 1 && PlayRate > 0.7666666666666666) //Ư�� ������ �÷��� ����Ʈ���Ŀ� ���������
			{


				m_iAdjMovedIndex++;
			}

			break;
		case 2:

			break;
		}
	}


	m_iOldAnimIndex = iNowAnimIndex;
	return S_OK;
}

HRESULT CMiniGame_KongRaji::SetUp_Info()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	m_pMainCamera = reinterpret_cast<CCamera_Main*>(pGameInstance->Get_GameObject_By_LayerIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main)));

	RELEASE_INSTANCE(CGameInstance);



	m_fHP = 100;

	ZeroMemory(&m_JumpDesc, sizeof(JUMPDESC));

	m_JumpDesc.fJumpPower = 5.f;

	return S_OK;
}

HRESULT CMiniGame_KongRaji::SetUp_Texture()
{
	CWorldTexture_Universal::WORLDTEXTURE_UNIVERSALDESC WorldTexture_UniversalDesc;

	WorldTexture_UniversalDesc.iWorldTextureNumber = CWorldTexture_Universal::DONKEYKONG_MAP;
	WorldTexture_UniversalDesc.fScale = _float3(32.f, 20.f, 20.f);
	WorldTexture_UniversalDesc.fPositioning = _float3(0.f, 0.f, -0.5f);
	WorldTexture_UniversalDesc.dDuration = 100000000;
	WorldTexture_UniversalDesc.pObject = this;

	WorldTexture_UniversalDesc.bBillboardOn = true;
	WorldTexture_UniversalDesc.bMagnetOn = false;
	WorldTexture_UniversalDesc.pSwitch = nullptr;

	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(m_eNowSceneNum, TAG_LAY(Layer_WorldTexture_Universal), TAG_OP(Prototype_Object_WorldTexture_Universal), &WorldTexture_UniversalDesc));
	return S_OK;
}

HRESULT CMiniGame_KongRaji::Play_MiniGame(_double dDeltaTime)
{
	Keyboard_Input(dDeltaTime);
	Jumping(dDeltaTime);
	Change_Anim();

	return S_OK;
}

HRESULT CMiniGame_KongRaji::Keyboard_Input(_double dDeltatime)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_fMyPos = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS);

	if (pGameInstance->Get_DIKeyState(DIK_W) & DIS_Press && m_bMoveToHeightOn == true)
	{
		if (m_fHeightPos[CMiniGame_KongRaji::HEIGHT_TWO_POINT].y + 0.1f >= m_fMyPos.y)
		{
			m_pTransformCom->Move_Up(dDeltatime);
			m_bMoveToWidthOn = false;
		}


		m_bChangeAnimOn = true;
		m_iCurrentAnimIndex = ANIM_CLIMB_UP;
		m_pTransformCom->LookDir(XMVectorSet(0.f, 0.f, 1.f, 0.f));
	}
	if (pGameInstance->Get_DIKeyState(DIK_S) & DIS_Press && m_bMoveToHeightOn == true)
	{
		if (m_fHeightPos[CMiniGame_KongRaji::HEIGHT_ONE_POINT].y <= m_fMyPos.y)
		{
			m_pTransformCom->Move_Down(dDeltatime);
			m_bMoveToWidthOn = false;
		}


		m_bChangeAnimOn = true;
		m_iCurrentAnimIndex = ANIM_CLIMB_DOWN;
		m_pTransformCom->LookDir(XMVectorSet(0.f, 0.f, 1.f, 0.f));
	}
	if (pGameInstance->Get_DIKeyState(DIK_A) & DIS_Press && m_bMoveToWidthOn == true)
	{
		m_pTransformCom->MovetoDir(XMVectorSet(-1.f, 0.f, 0.f, 0.f), dDeltatime, m_pNavigationCom);
		m_pTransformCom->Turn_Dir(XMVectorSet(-1.f, 0.f, 0.f, 0.f), 0.5f);

		m_bChangeAnimOn = true;

		if (false == m_JumpDesc.bJump)
		{
			m_iCurrentAnimIndex = ANIM_WALK;
			m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));
		}
	}
	if (pGameInstance->Get_DIKeyState(DIK_D) & DIS_Press && m_bMoveToWidthOn == true)
	{
		m_pTransformCom->MovetoDir(XMVectorSet(1.f, 0.f, 0.f, 0.f), dDeltatime, m_pNavigationCom);
		m_pTransformCom->Turn_Dir(XMVectorSet(1.f, 0.f, 0.f, 0.f), 0.5f);

		m_bChangeAnimOn = true;

		if (false == m_JumpDesc.bJump)
		{
			m_iCurrentAnimIndex = ANIM_WALK;
			m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));
		}
	}

	if (pGameInstance->Get_DIKeyState(DIK_SPACE) & DIS_Down)
	{
		if (false == m_JumpDesc.bJump)
		{
			m_JumpDesc.fJumpY = m_pTransformCom->Get_MatrixState_Float3(CTransform::STATE_POS).y;


			m_JumpDesc.bJump = true;
			m_iCurrentAnimIndex = ANIM_JUMP;

			m_bMoveToWidthOn = true;
			m_bMoveToHeightOn = false;

		}

	}

	m_fTempHeight = m_pNavigationCom->Get_NaviHeight(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS));


	//�׺� ���� �¿�� ������ ���
	//m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, m_pNavigationCom->Get_NaviPosition(m_pTransformCom->Get_MatrixState(CTransform::STATE_POS)));

	RELEASE_INSTANCE(CGameInstance);



	return S_OK;
}

HRESULT CMiniGame_KongRaji::Change_Anim()
{
	if (m_bChangeAnimOn)
	{
		m_iAnimIndex = m_iCurrentAnimIndex;

		m_bChangeAnimOn = false;
	}
	else {
		m_iAnimIndex = ANIM_IDLE;
	}
	return S_OK;
}

HRESULT CMiniGame_KongRaji::Jumping(_double TimeDelta)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (true == m_JumpDesc.bJump)
	{
		_Vector	vPosition = m_pTransformCom->Get_MatrixState(CTransform::STATE_POS);

		_float4	fTempPos;
		XMStoreFloat4(&fTempPos, vPosition);
		fTempPos.y = m_JumpDesc.fJumpY + (_float)(m_JumpDesc.fJumpPower * m_JumpDesc.dTime - 9.8f * m_JumpDesc.dTime * m_JumpDesc.dTime * 0.5f);
		m_JumpDesc.dTime += TimeDelta;

		if (m_fTempHeight > fTempPos.y)
		{
			m_JumpDesc.bJump = false;
			m_JumpDesc.dTime = 0;

			fTempPos.y = m_fTempHeight+0.1f;
		}

		m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, XMLoadFloat4(&fTempPos));

		//���� �ִϸ��̼� ������ ��
		m_bChangeAnimOn = true;
		m_iCurrentAnimIndex = ANIM_JUMP;
	}
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CMiniGame_KongRaji::SetUp_Collider()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider), (CComponent**)&m_pColliderCom));


	COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.5f, 1.5f, 1.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	ATTACHEDESC tAttachedDesc;
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_hip", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.074084f, -0.861011f, -75.1948f));
	m_vecAttachedDesc.push_back(tAttachedDesc);



	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(1.f, 1.f, 1.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(0.f, 0.f, 0.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	tAttachedDesc = ATTACHEDESC();
	tAttachedDesc.Initialize_AttachedDesc(this, "skd_hip", _float3(1.f, 1.f, 1.f), _float3(0.f, 0.f, 0.f), _float3(-0.074084f, -0.861011f, -75.1948f));
	m_vecAttachedDesc.push_back(tAttachedDesc);
	m_pColliderCom->Set_ParantBuffer();
	return S_OK;
}

HRESULT CMiniGame_KongRaji::Update_Collider(_double dDeltaTime)
{
	m_pColliderCom->Update_ConflictPassedTime(dDeltaTime);

	//Collider
	_uint	iNumCollider = m_pColliderCom->Get_NumColliderBuffer();
	for (_uint i = 0; i < iNumCollider; i++)
		m_pColliderCom->Update_Transform(i, m_vecAttachedDesc[i].Caculate_AttachedBoneMatrix_BlenderFixed());

	FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_Player, this, m_pColliderCom));

	FAILED_CHECK(g_pGameInstance->Add_RepelGroup(m_pTransformCom, 1.f, m_pNavigationCom));


	return S_OK;
}

HRESULT CMiniGame_KongRaji::Camera_Pos()
{
	Update_AttachCamPos();

	return S_OK;
}

CMiniGame_KongRaji * CMiniGame_KongRaji::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CMiniGame_KongRaji*	pInstance = NEW CMiniGame_KongRaji(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CMiniGame_KongRaji");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMiniGame_KongRaji::Clone(void * pArg)
{
	CMiniGame_KongRaji*	pInstance = NEW CMiniGame_KongRaji(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CMiniGame_KongRaji");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMiniGame_KongRaji::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModel);
	Safe_Release(m_pDissolve);

	Safe_Release(m_pColliderCom);
	Safe_Release(m_pNavigationCom);
}
