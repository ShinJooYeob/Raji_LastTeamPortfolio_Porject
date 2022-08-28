	#include "stdafx.h"
#include "..\Public\Scene_Stage1.h"
#include "Scene_Loading.h"
#include "Camera_Main.h"
#include "TriggerObject.h"
#include "Player.h"
#include "StaticInstanceMapObject.h"
#include "MonsterBatchTrigger.h"
#include "MiniGameBuilding.h"

// #SCENE STAGE1

CScene_Stage1::CScene_Stage1(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CScene(pDevice,pDeviceContext)
{
}

HRESULT CScene_Stage1::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	m_pUtilMgr = GetSingle(CUtilityMgr);

	FAILED_CHECK(Ready_Light());

	FAILED_CHECK(Ready_Layer_MainCamera(TAG_LAY(Layer_Camera_Main)));
	FAILED_CHECK(Ready_Layer_Player(TAG_LAY(Layer_Player)));
	FAILED_CHECK(Ready_Layer_SkyBox(TAG_LAY(Layer_SkyBox)));
	FAILED_CHECK(Ready_Layer_Terrain(TAG_LAY(Layer_Terrain)));
	
	
	FAILED_CHECK(Ready_MiniGameBuilding(TAG_LAY(Layer_MiniGameBuilding)));
	FAILED_CHECK(Ready_MapData(L"Stage_1.dat", SCENE_STAGE1, TAG_LAY(Layer_StaticMapObj)));
	FAILED_CHECK(Ready_TriggerObject(L"Stage1Trigger.dat", SCENE_STAGE1, TAG_LAY(Layer_ColTrigger)));
			

	//FAILED_CHECK(Ready_TriggerObject(L"Stage1_Instance.dat", SCENE_STAGE1, TAG_LAY(Layer_ColTrigger)));

	//FAILED_CHECK(Ready_TriggerObject(L"Stage1_0.dat", SCENE_STAGE1, TAG_LAY(Layer_ColTrigger)));

	//TestMeshInstance2
	//L"Stage1_Instance.dat"
	//FAILED_CHECK(Ready_TriggerObject(L"Stage1_Instance.dat", SCENE_STAGE1, TAG_LAY(Layer_ColTrigger)));





	
	////_float Length = _float3(-64, 64, -64).Get_Distance(_float3(128.f, -128.f, -256.f).XMVector());

	//EH
	FAILED_CHECK(Ready_TriggerObject(L"Stage1_InstanceMonsterTrigger.dat", SCENE_STAGE1, TAG_LAY(Layer_ColTrigger)));

	//FAILED_CHECK(Ready_MonsterBatchTrigger(L"Stage1_MonsterTrigger_1.dat", SCENE_STAGE1, TAG_LAY(Layer_BatchMonsterTrigger)));
	//FAILED_CHECK(Ready_MonsterBatchTrigger(L"Stage1_MonsterTrigger_2.dat", SCENE_STAGE1, TAG_LAY(Layer_BatchMonsterTrigger)));
	//FAILED_CHECK(Ready_MonsterBatchTrigger(L"Stage1_MonsterTrigger_3.dat", SCENE_STAGE1, TAG_LAY(Layer_BatchMonsterTrigger)));
	//FAILED_CHECK(Ready_MonsterBatchTrigger(L"Stage1_MonsterTrigger_4.dat", SCENE_STAGE1, TAG_LAY(Layer_BatchMonsterTrigger)));
	//FAILED_CHECK(Ready_MonsterBatchTrigger(L"Stage1_MonsterTrigger_5.dat", SCENE_STAGE1, TAG_LAY(Layer_BatchMonsterTrigger)));
	FAILED_CHECK(Ready_MonsterBatchTrigger(L"Stage1_MonsterTrigger_6.dat", SCENE_STAGE1, TAG_LAY(Layer_BatchMonsterTrigger)));
	//FAILED_CHECK(Ready_MonsterBatchTrigger(L"Stage1_MonsterTrigger_7.dat", SCENE_STAGE1, TAG_LAY(Layer_BatchMonsterTrigger)));
	//

	FAILED_CHECK(Ready_PostPorcessing());


//	FAILED_CHECK(Ready_MapParticle());

	FAILED_CHECK(GETPARTICLE->Ready_MapParticle_Stage(SCENE_STAGE1));


	FAILED_CHECK(Ready_Layer_UI(TAG_LAY(Layer_UI)));

	g_pGameInstance->PlaySoundW(L"Jino_Stage1_Start.wav", CHANNEL_PLAYER);
	g_pGameInstance->PlayBGM(L"Jino_Stage1_Start_Wind.wav", 1);
	return S_OK;
}

_int CScene_Stage1::Update(_double fDeltaTime)
{
	//m_pPlayerTransform
	if (__super::Update(fDeltaTime) < 0)
		return -1;

	if (m_bIsNeedToSceneChange)
		return Change_to_NextScene();

	if (g_pGameInstance->Get_DIKeyState(DIK_RETURN)&DIS_Down)
	{
		FAILED_CHECK(m_pUtilMgr->Clear_RenderGroup_forSceneChange());
		FAILED_CHECK(g_pGameInstance->Scene_Change(CScene_Loading::Create(m_pDevice, m_pDeviceContext, SCENEID::SCENE_STAGE4), SCENEID::SCENE_LOADING));
		return 0;
	}


	if (m_iSceneStartChecker <= SceneChangeCopyFrame && CScene_Loading::m_iLoadingKinds == CScene_Loading::LOADINGKINDS_NORMAL)
	{
		FAILED_CHECK(m_pUtilMgr->Get_Renderer()->Copy_LastDeferredTexture());
		FAILED_CHECK(m_pUtilMgr->Get_Renderer()->Copy_LastDeferredToToonShadingTexture(1.f, true));
	}

	LIGHTDESC* pLightDesc = g_pGameInstance->Get_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0);
	_Vector vDir = XMVector3Normalize(XMVectorSetY( m_pPlayerTransform->Get_MatrixState(CTransform::STATE_POS),10) - XMVectorSet(128.f, -64.f, 256.f, 0));
	g_pGameInstance->Relocate_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0, XMVectorSet(128.f, -64.f, 256.f, 0) + vDir * 330.f);

	_float3 PlayerPos = m_pPlayerTransform->Get_MatrixState_Float3(CTransform::STATE_POS);
	if (PlayerPos.x > 34.4f && PlayerPos.x < 37.5f)
	{
		CGameInstance* pInstance = g_pGameInstance;
		_float3 vDiffuse = pInstance->Easing_Vector(TYPE_Linear, _float3(1.f), _float3(0.78125f, 0.78125f, 1.f), PlayerPos.x - 34.4f, 3.1f);
		_float3 vAmbient = pInstance->Easing_Vector(TYPE_Linear, _float3(1.f), _float3(0.6640625f, 0.65625f, 1.f), PlayerPos.x - 34.4f, 3.1f);
		_float vFogColor = pInstance->Easing(TYPE_Linear, 0.234375f, 0.5f, PlayerPos.x - 34.4f, 3.1f);


		pLightDesc->vDiffuse = _float4(vDiffuse, 1.f);
		pLightDesc->vAmbient = _float4(vAmbient, 1.f);
		m_pUtilMgr->Get_Renderer()->Set_FogColor(_float3(vFogColor));
		////pLightDesc->vDiffuse = _float4(0.78125f, 0.78125f, 1.f, 1.f);
		////pLightDesc->vAmbient = _float4(0.6640625f, 0.65625f, 1.f, 1.f);
	}




	return 0;
}

_int CScene_Stage1::LateUpdate(_double fDeltaTime)
{
	if (__super::LateUpdate(fDeltaTime) < 0)
		return -1;

	if (m_bIsNeedToSceneChange)
		return Change_to_NextScene();

	return 0;
}

_int CScene_Stage1::Render()
{
	if (__super::Render() < 0)
		return -1;

	if (CScene_Loading::m_iLoadingKinds == CScene_Loading::LOADINGKINDS_NORMAL)
	{
		if (m_fSceneStartTimer < 0.5f)
		{
			FAILED_CHECK(m_pUtilMgr->SCD_Rendering_Rolling(((_float)m_fSceneStartTimer), 0.5f, L"Target_ToonDeferredSceneChaging2"));
		}
		else if (m_fSceneStartTimer < 2.5f)
		{
			FAILED_CHECK(m_pUtilMgr->SCD_Rendering_FadeOut(((_float)m_fSceneStartTimer - 0.5f), 2.f, L"Target_ToonDeferredSceneChaging2"));
		}
	}

	return 0;
}

_int CScene_Stage1::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;

	return 0;
}

_int CScene_Stage1::Change_to_NextScene()
{

	FAILED_CHECK(m_pUtilMgr->Clear_RenderGroup_forSceneChange());
	FAILED_CHECK(g_pGameInstance->Scene_Change(CScene_Loading::Create(m_pDevice, m_pDeviceContext, (SCENEID) m_eNextScene), SCENEID::SCENE_LOADING));


	return _int();

}

void CScene_Stage1::Play_Scene_BGM()
{
	g_pGameInstance->PlayBGM(L"Jino_BGM_Stage1.wav");
}



HRESULT CScene_Stage1::Ready_Light()
{

	const LIGHTDESC* pLightDesc = g_pGameInstance->Get_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0);

	if (pLightDesc == nullptr)
	{

		LIGHTDESC LightDesc;

		LightDesc.eLightType = tagLightDesc::TYPE_DIRECTIONAL;
		LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
		LightDesc.vAmbient = _float4(1.0f);
		LightDesc.vSpecular = _float4(1);
		LightDesc.vVector = DefalutSunPosition;

		g_pGameInstance->Add_Light(LightDesc);
	}
	else
	{
		g_pGameInstance->Relocate_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0, DefalutSunPosition.XMVector());

	}


	



	return S_OK;
}

HRESULT CScene_Stage1::Ready_Layer_MainCamera(const _tchar * pLayerTag)
{
	CCamera::CAMERADESC CameraDesc;
	CameraDesc.vWorldRotAxis = _float3(0, 0, 0);
	CameraDesc.vEye = _float3(29.8301334f, 43.5636215f, 56.5241318f);
	CameraDesc.vAt = _float3(0, 0.f, 0);
	CameraDesc.vAxisY = _float3(0, 1, 0);

	CameraDesc.fFovy = XMConvertToRadians(60.f);
	CameraDesc.fAspect = _float(g_iWinCX) / g_iWinCY;
	CameraDesc.fNear = 0.2f;
	CameraDesc.fFar = CAMERAFAR;

	CameraDesc.iWinCX = g_iWinCX;
	CameraDesc.iWinCY = g_iWinCY;

	CameraDesc.TransformDesc.fMovePerSec = 5.f;
	CameraDesc.TransformDesc.fRotationPerSec = XMConvertToRadians(60.0f);
	CameraDesc.TransformDesc.fScalingPerSec = 1.f;


	m_pMainCam = (CCamera_Main*)(g_pGameInstance->Get_GameObject_By_LayerIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main)));

	if (m_pMainCam == nullptr)
	{
		FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STATIC, pLayerTag, TAG_OP(Prototype_Camera_Main), &CameraDesc));

		m_pMainCam = (CCamera_Main*)(g_pGameInstance->Get_GameObject_By_LayerIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main)));

		NULL_CHECK_RETURN(m_pMainCam, E_FAIL);
	}
	else 
	{
		m_pMainCam->Set_NowSceneNum(SCENE_STAGE1);
		m_pMainCam->Set_CameraDesc(CameraDesc);
	}
	
	m_pMainCam->Set_MaxTargetArmLength(10.f);
	m_pMainCam->Set_TargetArmLength(8.f);
	m_pMainCam->Set_MinTargetArmLength(5.f);
	m_pMainCam->Ortho_OnOff(false);

	return S_OK;
}

HRESULT CScene_Stage1::Ready_Layer_Player(const _tchar * pLayerTag)
{
	// End Pos : _float3(350.722f, 41.092f, 268.068f)

	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_Player), &_float3(280.833f,44.15f,261.232f)));//31.773f, 37.5f, 64.801f)));
	CGameObject* pPlayer = (CPlayer*)(g_pGameInstance->Get_GameObject_By_LayerIndex(SCENE_STAGE1, TAG_LAY(Layer_Player)));
	NULL_CHECK_RETURN(pPlayer, E_FAIL);

	if (CScene_Loading::m_iLoadingKinds == CScene_Loading::LOADINGKINDS_NORMAL)
	{
		//static_cast<CPlayer*>(pPlayer)->Set_State_FirstStart();
		m_pPlayerTransform = (CTransform*)pPlayer->Get_Component(TAG_COM(Com_Transform));
		NULL_CHECK_RETURN(m_pPlayerTransform, E_FAIL);

		CNavigation* PlayerNavi = (CNavigation*)pPlayer->Get_Component(TAG_COM(Com_Navaigation));
		PlayerNavi->FindCellIndex(m_pPlayerTransform->Get_MatrixState(CTransform::TransformState::STATE_POS));

		m_pMainCam = (CCamera_Main*)(g_pGameInstance->Get_GameObject_By_LayerIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main)));
		NULL_CHECK_RETURN(m_pMainCam, E_FAIL);

		static_cast<CPlayer*>(pPlayer)->Set_AttachCamPos(_float3(29.8301334f, 43.5636215f, 56.5241318f));
		m_pMainCam->Set_CameraInitState(XMVectorSet(29.8301334f, 43.5636215f, 56.5241318f, 1.f), XMVectorSet(0.242860183f, -0.570450962f, 0.784604728f, 0.f));
		pPlayer->Update(g_fDeltaTime);
		pPlayer->Update(g_fDeltaTime);
		pPlayer->Update(g_fDeltaTime);
		pPlayer->Update(g_fDeltaTime);
		pPlayer->Update(g_fDeltaTime);
		pPlayer->Update(g_fDeltaTime);
		static_cast<CPlayer*>(pPlayer)->Set_AttachCamPos(_float3(29.8301334f, 43.5636215f, 56.5241318f));
		m_pMainCam->Set_CameraInitState(XMVectorSet(29.8301334f, 43.5636215f, 56.5241318f, 1.f), XMVectorSet(0.242860183f, -0.570450962f, 0.784604728f, 0.f));


		m_pMainCam->Set_CameraMode(ECameraMode::CAM_MODE_NOMAL);
		m_pMainCam->Set_FocusTarget(pPlayer);
		m_pMainCam->Set_CameraInitState(XMVectorSet(29.8301334f, 43.5636215f, 56.5241318f, 1.f), XMVectorSet(0.242860183f, -0.570450962f, 0.784604728f, 0.f));

	}
	else
	{
		PPDDESC tDesc = (GetSingle(CUtilityMgr)->Set_SceneChangingData(SCENE_STAGE1));

		m_pPlayerTransform = (CTransform*)pPlayer->Get_Component(TAG_COM(Com_Transform));
		NULL_CHECK_RETURN(m_pPlayerTransform, E_FAIL);

		CNavigation* PlayerNavi = (CNavigation*)pPlayer->Get_Component(TAG_COM(Com_Navaigation));
		PlayerNavi->FindCellIndex(m_pPlayerTransform->Get_MatrixState(CTransform::TransformState::STATE_POS));


		m_iBuildingIndex = tDesc.ObjMgrLaterIdx;

	}

	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE1, TAG_LAY(Layer_PlayerIndicator), TAG_OP(Prototype_Object_PlayerIndicator)));
	
	
	return S_OK;
}

HRESULT CScene_Stage1::Ready_Layer_SkyBox(const _tchar * pLayerTag)
{
	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_SkyBox)));

	return S_OK;
}

HRESULT CScene_Stage1::Ready_Layer_Terrain(const _tchar * pLayerTag)
{
	//FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_Terrain)));



	return S_OK;
}

HRESULT CScene_Stage1::Ready_MapData(const _tchar * szMapDataFileName, SCENEID eSceneID, const _tchar * pLayerTag)
{
	//../bin/Resources/Data/Map/
	_tchar szFullPath[MAX_PATH] = L"../bin/Resources/Data/Map/";

	lstrcat(szFullPath, szMapDataFileName);



	CGameInstance* pInstance = g_pGameInstance;

	pInstance->Add_GameObject_To_Layer(eSceneID, pLayerTag, TAG_OP(Prototype_InstanceStaticMapObject));
	CStaticInstanceMapObject* pInstanceMapObject = (CStaticInstanceMapObject*)pInstance->Get_GameObject_By_LayerLastIndex(eSceneID, pLayerTag);
	NULL_CHECK_RETURN(pInstanceMapObject, E_FAIL);


	//HANDLE hFile = CreateFileW(szFullPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);


	HANDLE hFile = ::CreateFileW(szFullPath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);


	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte = 0;


	_uint iIDLength = 0;

	// �����ڵ����� �˸��� BOM
	//DWORD wc = 0xFF;
	//ReadFile(hFile, &wc, 3, &dwByte, NULL);

	while (true)
	{

		OBJELEMENT	tData{};
		_tchar szBuffer[MAX_PATH] = L"";
		// key �� �ε�
		ReadFile(hFile, &(iIDLength), sizeof(_uint), &dwByte, nullptr);
		ReadFile(hFile, (tData.ObjectID), sizeof(_tchar) * iIDLength, &dwByte, nullptr);
		//lstrcpy(tData.ObjectID, szBuffer);

		ReadFile(hFile, &(iIDLength), sizeof(_uint), &dwByte, nullptr);
		ReadFile(hFile, (tData.MeshID), sizeof(_tchar) * iIDLength, &dwByte, nullptr);
		//lstrcpy(tData.MeshID, szBuffer);

		ReadFile(hFile, &(tData.PassIndex), sizeof(_uint), &dwByte, nullptr);
		ReadFile(hFile, &(tData.FrustumRange), sizeof(_float), &dwByte, nullptr);
		ReadFile(hFile, &(tData.bIsOcllsuion), sizeof(_bool), &dwByte, nullptr);

		ReadFile(hFile, &(tData.matSRT.m[0][0]), sizeof(_float) * 16, &dwByte, nullptr);
		ReadFile(hFile, &(tData.matTransform.m[0][0]), sizeof(_float) * 16, &dwByte, nullptr);

		if (0 == dwByte)
			break;

		if (!lstrcmp(L"Prototype_EditorCursor", tData.ObjectID)) continue;

		// 14 -> 22
		//if (tData.PassIndex == 14)
		//	tData.PassIndex = 22;

		FAILED_CHECK(pInstanceMapObject->Add_InstanceMapObject(tData));

	}

	CloseHandle(hFile);

	return S_OK;
}

HRESULT CScene_Stage1::Ready_TriggerObject(const _tchar * szTriggerDataName, SCENEID eSceneID, const _tchar * pLayerTag)
{

	{

		CGameInstance* pInstance = g_pGameInstance;

		_tchar szFullPath[MAX_PATH] = L"../bin/Resources/Data/Trigger/";
		lstrcat(szFullPath, szTriggerDataName);


		HANDLE hFile = ::CreateFileW(szFullPath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);


		if (INVALID_HANDLE_VALUE == hFile)
		{
			__debugbreak();
			return E_FAIL;
		}

		DWORD	dwByte = 0;
		_int iIDLength = 0;




		while (true)
		{



			_uint eNumber = 0;
			_tchar eObjectID[MAX_PATH];
			_float4x4 WorldMat = XMMatrixIdentity();
			_float4x4 ValueData = XMMatrixIdentity();
			_float4x4 SubValueData = XMMatrixIdentity();

			ZeroMemory(eObjectID, sizeof(_tchar) * MAX_PATH);

			ReadFile(hFile, &(eNumber), sizeof(_uint), &dwByte, nullptr);
			ReadFile(hFile, &(iIDLength), sizeof(_int), &dwByte, nullptr);
			ReadFile(hFile, &(eObjectID), sizeof(_tchar) * iIDLength, &dwByte, nullptr);

			ReadFile(hFile, &(WorldMat), sizeof(_float4x4), &dwByte, nullptr);
			ReadFile(hFile, &(ValueData), sizeof(_float4x4), &dwByte, nullptr);
			ReadFile(hFile, &(SubValueData), sizeof(_float4x4), &dwByte, nullptr);
			if (0 == dwByte) break;



			FAILED_CHECK(pInstance->Add_GameObject_To_Layer(eSceneID, pLayerTag, eObjectID, &eNumber));

			CTriggerObject* pObject = (CTriggerObject*)(pInstance->Get_GameObject_By_LayerLastIndex(eSceneID, pLayerTag));

			NULL_CHECK_RETURN(pObject, E_FAIL);

			pObject->Set_eNumberNObjectID(eNumber, eObjectID);

			((CTransform*)pObject->Get_Component(TAG_COM(Com_Transform)))->Set_Matrix(WorldMat);

			pObject->Set_ValueMat(&ValueData);
			pObject->Set_SubValueMat(&SubValueData);

			pObject->After_Initialize();

		}

		CloseHandle(hFile);
	}








	return S_OK;
}

HRESULT CScene_Stage1::Ready_PostPorcessing()
{
	if (CScene_Loading::m_iLoadingKinds != CScene_Loading::LOADINGKINDS_NORMAL) return S_FALSE;

#ifndef _DEBUG
	LIGHTDESC* pLightDesc = g_pGameInstance->Get_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0);
	m_pUtilMgr->Get_Renderer()->Set_SunAtPoint(_float3(128.f, -64.f, 256.f));
	pLightDesc->vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	pLightDesc->vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
	//pLightDesc->vDiffuse = _float4(0.78125f, 0.78125f, 1.f, 1.f);
	//pLightDesc->vAmbient = _float4(0.6640625f, 0.65625f, 1.f, 1.f);
	pLightDesc->vSpecular = _float4(0.234375f, 0.234375f, 0.234375f, 1.f);

	CRenderer* pRenderer = m_pUtilMgr->Get_Renderer();


	for (_uint i = 0; i < POSTPROCESSING_END; i++)
		pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSINGID(i), false);


	pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSING_SHADOW, true);
	pRenderer->Set_ShadowIntensive(0.3f);

	pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSING_BLOOM, true);
	pRenderer->Set_BloomOverLuminceValue(1.0f);
	pRenderer->Set_BloomBrightnessMul(1.5f);

	pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSING_DOF, true);
	pRenderer->Set_DofLength(30.f);
	pRenderer->Set_DofBlurIntensive(1.f);

	pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSING_DDFOG, true);
	pRenderer->Set_FogColor(_float3{ 0.234375f });
	pRenderer->Set_FogHighlightColor(_float3{ 1.f });
	pRenderer->Set_FogStartDist(5.f);
	pRenderer->Set_FogGlobalDensity(0.1f);
	pRenderer->Set_FogHeightFalloff(0.1f);

	//POSTPROCESSING_GODRAY
	//POSTPROCESSING_LENSEFLARE
	//POSTPROCESSING_CAMMOTIONBLUR
#else
#ifdef DEBUGONSHADERSETTING

	LIGHTDESC* pLightDesc = g_pGameInstance->Get_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0);
	m_pUtilMgr->Get_Renderer()->Set_SunAtPoint(_float3(128.f, -64.f, 256.f));
	pLightDesc->vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	pLightDesc->vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
	//pLightDesc->vDiffuse = _float4(0.78125f, 0.78125f, 1.f, 1.f);
	//pLightDesc->vAmbient = _float4(0.6640625f, 0.65625f, 1.f, 1.f);
	pLightDesc->vSpecular = _float4(0.234375f, 0.234375f, 0.234375f, 1.f);

	CRenderer* pRenderer = m_pUtilMgr->Get_Renderer();


	for (_uint i = 0; i < POSTPROCESSING_END; i++)
		pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSINGID(i), false);


	pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSING_SHADOW, true);
	pRenderer->Set_ShadowIntensive(0.3f);

	pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSING_BLOOM, true);
	pRenderer->Set_BloomOverLuminceValue(1.0f);
	pRenderer->Set_BloomBrightnessMul(1.5f);

	pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSING_DOF, true);
	pRenderer->Set_DofLength(30.f);
	pRenderer->Set_DofBlurIntensive(1.f);

	pRenderer->OnOff_PostPorcessing_byParameter(POSTPROCESSING_DDFOG, true);
	pRenderer->Set_FogColor(_float3{ 0.234375f });
	pRenderer->Set_FogHighlightColor(_float3{ 1.f });
	pRenderer->Set_FogStartDist(5.f);
	pRenderer->Set_FogGlobalDensity(0.1f);
	pRenderer->Set_FogHeightFalloff(0.1f);
#endif

#endif // !_DEBUGee
	return S_OK;
}

HRESULT CScene_Stage1::Ready_MapParticle()
{
	INSTPARTICLEDESC tDesc = GetSingle(CUtilityMgr)->Get_TextureParticleDesc(TEXT("Jino_Stage1_FireParticle_0"));
	tDesc.FollowingTarget = nullptr;
	tDesc.vFixedPosition = _float3(32.2f, 42.8f, 65.4f);
	GetSingle(CUtilityMgr)->Create_TextureInstance(SCENE_STAGE1, tDesc);
	

	INSTPARTICLEDESC tDesc2 = GetSingle(CUtilityMgr)->Get_TextureParticleDesc(TEXT("Jino_Stage1_WaterFallParticle_0"));
	tDesc2.eInstanceCount = Prototype_VIBuffer_Point_Instance_4;
	tDesc2.FollowingTarget = nullptr;
	tDesc2.bBillboard = true;
	tDesc2.TextureChageFrequency = 1;
	vector<_float3> vParticlesPos;
	vParticlesPos.push_back(_float3(95.110130f, 35.100010f, 40.533039f));
	vParticlesPos.push_back(_float3(101.110130f, 35.100010f, 42.033039f));
	vParticlesPos.push_back(_float3(117.710f, 36.6f, 39.433f));
	GetSingle(CUtilityMgr)->Create_TextureInstance(SCENE_STAGE1, tDesc2, &vParticlesPos);


	INSTPARTICLEDESC tDesc3 = GetSingle(CUtilityMgr)->Get_TextureParticleDesc(TEXT("Jino_Stage1_WaterFallParticle_1"));
	tDesc3.FollowingTarget = nullptr;
	tDesc3.vFixedPosition = _float3(256.512f, 33.f, 191.703f);
	GetSingle(CUtilityMgr)->Create_TextureInstance(SCENE_STAGE1, tDesc3);

	INSTPARTICLEDESC tDesc4 = GetSingle(CUtilityMgr)->Get_TextureParticleDesc(TEXT("Jino_Stage1_FountainParticle_0"));
	tDesc4.FollowingTarget = nullptr;
	tDesc4.vFixedPosition = _float3(257.012054f, 24.5f, 180.302515f);
	GetSingle(CUtilityMgr)->Create_TextureInstance(SCENE_STAGE1, tDesc4);

	INSTPARTICLEDESC tDesc5 = GetSingle(CUtilityMgr)->Get_TextureParticleDesc(TEXT("Jino_Stage1_FountainParticle_1"));
	tDesc5.FollowingTarget = nullptr;
	tDesc5.vFixedPosition = _float3(256.811218f, 21.f, 191.899643f);
	tDesc5.TotalParticleTime = 999999999999.f;
	GetSingle(CUtilityMgr)->Create_TextureInstance(SCENE_STAGE1, tDesc5);

	INSTPARTICLEDESC tDesc6 = GetSingle(CUtilityMgr)->Get_TextureParticleDesc(TEXT("Jino_Stage1_Rain_0"));
	tDesc6.FollowingTarget = nullptr;
	tDesc6.vFixedPosition = _float3(256.811218f, 27.5f, 178.358f);
	GetSingle(CUtilityMgr)->Create_TextureInstance(SCENE_STAGE1, tDesc6);

	//Jino_Stage1_Rain_0
	/*vector<_float3> vParticlesPos = { _float3(42.010387f, 34.900013f, 53.302711f), _float3(46.964718f, 34.900013f, 53.425224f), _float3(51.797810f, 34.900013f, 53.236481f) };
	*/
	return S_OK;
}
	
HRESULT CScene_Stage1::Ready_MonsterBatchTrigger(const _tchar * szTriggerDataName, SCENEID eSceneID, const _tchar * pLayerTag)
{


	//../bin/Resources/Data/ParicleData/TextureParticle/
	_tchar szFullPath[MAX_PATH] = L"../bin/Resources/Data/MonsterBatchData/";
	lstrcat(szFullPath, szTriggerDataName);

	HANDLE hFile = ::CreateFileW(szFullPath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);


	if (INVALID_HANDLE_VALUE == hFile)
	{
		__debugbreak();
		return E_FAIL;
	}

	DWORD	dwByte = 0;

	_int iIDLength = 0;


	_float4x4 WorldMat = XMMatrixIdentity();
	_float4x4 ValueMat = XMMatrixIdentity();
	_tchar	 eObjectID[MAX_PATH] = L"";

	ReadFile(hFile, &(WorldMat), sizeof(_float4x4), &dwByte, nullptr);
	ReadFile(hFile, &(ValueMat), sizeof(_float4x4), &dwByte, nullptr);

	

	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(eSceneID, pLayerTag, TAG_OP(Prototype_MonsterBatchTrigger)));
	CMonsterBatchTrigger* pMonsterBatchTrigger = (CMonsterBatchTrigger*)(g_pGameInstance->Get_GameObject_By_LayerLastIndex(eSceneID, pLayerTag));

	NULL_CHECK_RETURN(pMonsterBatchTrigger, E_FAIL);

	CTransform * pTrigTransform = (CTransform*)pMonsterBatchTrigger->Get_Component(TAG_COM(Com_Transform));

	//////////////////////////////////////////////////////////////////////////��Ʈ���� �ֱ�

	pTrigTransform->Set_Matrix(WorldMat);
	pMonsterBatchTrigger->Set_ValueMat(&ValueMat);


	while (true)
	{
		ZeroMemory(eObjectID, sizeof(_tchar) * MAX_PATH);

		ReadFile(hFile, &(WorldMat), sizeof(_float4x4), &dwByte, nullptr);

		ReadFile(hFile, &(iIDLength), sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, &(eObjectID), sizeof(_tchar) * iIDLength, &dwByte, nullptr);


		if (0 == dwByte) break;
		pMonsterBatchTrigger->Add_MonsterBatch(WorldMat, eObjectID);
	}


	CloseHandle(hFile);


	return S_OK;
}

HRESULT CScene_Stage1::Ready_Layer_UI(const _tchar * pLayerTag)
{
	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_Object_PauseUI)));
	return S_OK;
}

HRESULT CScene_Stage1::Ready_MiniGameBuilding(const _tchar * pLayerTag)
{

	_uint iNum = 0;

	CMiniGameBuilding::MGBDESC tDesc;
	tDesc.vPosition = _float3(205.821f, 23.153f, 88.299f);
	tDesc.vScale = _float3(1.f);
	tDesc.vLookDir = _float3(0, 0, -1).Get_Nomalize();
	tDesc.eKindsOfMiniGame = CMiniGameBuilding::MINIGAME_CIRCUS;
	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_Object_MiniGameBuilding),&tDesc));

	if (m_iBuildingIndex >= (_int)iNum)
	{
		CMiniGameBuilding* pObj = (CMiniGameBuilding*)g_pGameInstance->Get_GameObject_By_LayerLastIndex(SCENEID::SCENE_STAGE1, pLayerTag);
		pObj->Set_OffRadiation();
		if (m_iBuildingIndex == (_int)iNum)
			pObj->Start_ReverseSceneChanging_CamAct();
	}
	iNum++;


	tDesc.vPosition = _float3(193.102f, 28.700f, 222.103f);
	tDesc.vScale = _float3(1.f);
	tDesc.vLookDir = _float3(0, 0, -1).Get_Nomalize();
	tDesc.eKindsOfMiniGame = CMiniGameBuilding::MINIGAME_FALLOFF;
	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_Object_MiniGameBuilding), &tDesc));

	if (m_iBuildingIndex >= (_int)iNum)
	{
		CMiniGameBuilding* pObj = (CMiniGameBuilding*)g_pGameInstance->Get_GameObject_By_LayerLastIndex(SCENEID::SCENE_STAGE1, pLayerTag);
		pObj->Set_OffRadiation();
		if (m_iBuildingIndex == (_int)iNum)
			pObj->Start_ReverseSceneChanging_CamAct();
	}
	iNum++;


	tDesc.vPosition = _float3(280.932f, 43.530f, 270.503f);
	tDesc.vScale = _float3(1.f);
	tDesc.vLookDir = _float3(1, 0, -2).Get_Nomalize();
	tDesc.eKindsOfMiniGame = CMiniGameBuilding::MINIGAME_VAMPIRESURVIAL;
	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_Object_MiniGameBuilding), &tDesc));

	if (m_iBuildingIndex >= (_int)iNum)
	{
		CMiniGameBuilding* pObj = (CMiniGameBuilding*)g_pGameInstance->Get_GameObject_By_LayerLastIndex(SCENEID::SCENE_STAGE1, pLayerTag);
		pObj->Set_OffRadiation();
		if (m_iBuildingIndex == (_int)iNum)
			pObj->Start_ReverseSceneChanging_CamAct();
	}
	iNum++;

	
	return S_OK;
}

CScene_Stage1 * CScene_Stage1::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
{
	CScene_Stage1* pTempLoby = NEW CScene_Stage1(pDevice,pDeviceContext);

	if (FAILED(pTempLoby->Initialize())) 
	{
		Safe_Release(pTempLoby); 
		MSGBOX("Failed to Creating CScene_Stage1");
		return nullptr;
	}

	return pTempLoby;

}

void CScene_Stage1::Free()
{
	__super::Free();
}
