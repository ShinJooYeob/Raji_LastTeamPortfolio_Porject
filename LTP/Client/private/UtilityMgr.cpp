#include "stdafx.h"
#include "..\public\UtilityMgr.h"
#include "..\public\AssimpCreateMgr.h"
#include "MainApp.h"
#include"SkillUI.h"
#include "Camera_Main.h"
#include "InstanceEffect.h"
#include "RadialBlurUI.h"
#include "HitEffectUI.h"

IMPLEMENT_SINGLETON(CUtilityMgr);

CUtilityMgr::CUtilityMgr()
{
}

HRESULT CUtilityMgr::Initialize_UtilityMgr(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, CMainApp * pMainApp)
{
	if (nullptr == pMainApp || nullptr == pDevice || nullptr == pDeviceContext)
		return E_FAIL;

	m_pDevice = pDevice;
	m_pDeviceContext = pDeviceContext;
	m_pMainApp = pMainApp;


	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pDeviceContext);

	ZeroMemory(m_StartTime, sizeof(clock_t)*E_DEBUGTIMER::DEBUGTIMER_END);


	FAILED_CHECK(g_pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Texture_ScreenEffectUI),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"ScreenEffectUI.txt")));

	m_pTexture = (CTexture*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Texture_Util));
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	FAILED_CHECK(m_pTexture->Change_TextureLayer(L"NoiseTexture"));


	m_pDissolveTexture = (CTexture*)g_pGameInstance->Clone_Component(SCENE_STATIC, L"Prototype_Texture_Dissolve");
	NULL_CHECK_RETURN(m_pDissolveTexture, E_FAIL);


	m_pVIBufferRect = (CVIBuffer_Rect*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_VIBuffer_Rect));
	NULL_CHECK_RETURN(m_pVIBufferRect, E_FAIL);

	m_pRectShader = (CShader*)g_pGameInstance->Clone_Component(SCENE_STATIC, TAG_CP(Prototype_Shader_VT));
	NULL_CHECK_RETURN(m_pRectShader, E_FAIL);


	FAILED_CHECK(g_pGameInstance->Add_GameObject_Prototype(L"Prototype_RadialBlurUI", CRadialBlurUI::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STATIC, TAG_LAY(Layer_ScreenEffect), L"Prototype_RadialBlurUI"));
	m_pRadialUI = (CRadialBlurUI*)g_pGameInstance->Get_GameObject_By_LayerLastIndex(SCENEID::SCENE_STATIC, TAG_LAY(Layer_ScreenEffect));


	FAILED_CHECK(g_pGameInstance->Add_GameObject_Prototype(L"Prototype_HitEffectUI", CHitEffectUI::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENEID::SCENE_STATIC, TAG_LAY(Layer_ScreenEffect), L"Prototype_HitEffectUI"));
	m_pHitEffectUI = (CHitEffectUI*)g_pGameInstance->Get_GameObject_By_LayerLastIndex(SCENEID::SCENE_STATIC, TAG_LAY(Layer_ScreenEffect));
	

	// PathReLoad
	GetSingle(CAssimpCreateMgr)->Save_To_Effect();

	FAILED_CHECK(Ready_Particles());


	UIDESC tUIDesc;
	tUIDesc.fCX = g_iWinCX;
	tUIDesc.fCY = (g_iWinCY);
	tUIDesc.fX = g_iWinCX * 0.5f;
	tUIDesc.fY = g_iWinCY * 0.5f;

	FAILED_CHECK(m_pLoadingSCD.Initialize_SCDDesc(tUIDesc));
	FAILED_CHECK(m_pLoadingSCD.pRenderer->Copy_LastDeferredToToonShadingTexture(0));
	

	return S_OK;
}

_float CUtilityMgr::RandomFloat(_float Min, _float Max)
{
	if (Min >= Max) // bad input
	{
		_float temp = Min;
		Min = Max;
		Max = temp;
	}


	_uint RandNum = rand();
	_uint iDigit = CountDigit(RandNum);
	while (!iDigit)
	{
		RandNum = rand();
		iDigit = CountDigit(RandNum);
	}
	_uint Power = _uint(pow(10, iDigit - 1));
	//_float f = (RandNum) / _float(Power);
	_float f = (RandNum % Power) / _float(Power);
	return (f * (Max - Min)) + Min;
}

_float3 CUtilityMgr::RandomFloat3(_float Min, _float Max)
{
	if (Min >= Max) // bad input
	{
		_float temp = Min;
		Min = Max;
		Max = temp;
	}
	return _float3(RandomFloat(Min, Max), RandomFloat(Min, Max), RandomFloat(Min, Max));
}

_float3 CUtilityMgr::RandomFloat3(_float3 Min, _float3 Max)
{
	if (Min.x >= Max.x) // bad input
	{
		_float temp = Min.x;
		Min.x = Max.x;
		Max.x = temp;
	}
	if (Min.y >= Max.y) // bad input
	{
		_float temp = Min.y;
		Min.y = Max.y;
		Max.y = temp;
	}

	if (Min.z >= Max.z) // bad input
	{
		_float temp = Min.z;
		Min.z = Max.z;
		Max.z = temp;
	}

	return _float3(RandomFloat(Min.x, Max.x), RandomFloat(Min.y, Max.y), RandomFloat(Min.z, Max.z));
}

_float CUtilityMgr::MinFloat(_float a, _float b)
{
	return a < b ? a:b;
}

_float CUtilityMgr::MaxFloat(_float a, _float b)
{
	return a < b ? b : a;
}


void CUtilityMgr::SlowMotionStart(_float fTargetTime , _float TargetSpeed , _float TargetCurveRate )
{
	NULL_CHECK_BREAK(m_pMainApp);
	m_pMainApp->SlowMotionStart(fTargetTime, TargetSpeed, TargetCurveRate);
}

_float CUtilityMgr::Get_SlowMotionSpeed()
{
	NULL_CHECK_BREAK(m_pMainApp);
	return m_pMainApp->Get_SlowMotionSpeed();
}

_bool CUtilityMgr::Get_IsSlowed()
{
	return m_pMainApp->Get_IsSlowed();
}

void CUtilityMgr::Start_DebugTimer(E_DEBUGTIMER type)
{
	m_StartTime[type] = clock();
	// �����ڵ带 �����Ѵ�.
}

void CUtilityMgr::End_DebugTimer(E_DEBUGTIMER type, wstring debugLog)
{
	if (m_StartTime[type] == 0)
	{
#ifdef _DEBUG
		wstring log = L"__BEFORE_CALL_Start_DebugTimer_FUNC__\n";
		OutputDebugStringW(log.c_str());
		return;
#endif
	}

#ifdef _DEBUG
	{
		_double EndTimer = ((int)clock() - m_StartTime[type]) / (CLOCKS_PER_SEC / 1000);
		wstring debug = L"__ENDTIME: " + to_wstring(EndTimer) + L"ms__"
			+ debugLog + L"___\n"; ;

		OutputDebugStringW(debug.c_str());

		m_StartTime[type] = 0;
	}
#endif

}


HRESULT CUtilityMgr::Create_TextureInstance(_uint eSceneID, INSTPARTICLEDESC& tParticleDesc)
{
	switch (tParticleDesc.eParticleTypeID)
	{
	case InstanceEffect_Ball:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Ball"), &tParticleDesc));
		break;
	case InstanceEffect_Straight:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Straight"), &tParticleDesc));
		break;
	case InstanceEffect_Cone:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Cone"), &tParticleDesc));
		break;
	case InstanceEffect_Spread:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Spread"), &tParticleDesc));
		break;
	case InstanceEffect_Suck:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Suck"), &tParticleDesc));
		break;
	case InstanceEffect_Fountain:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Fountain"), &tParticleDesc));
		break;


	case InstanceEffect_End:
		break;
	default:
		break;
	}




	return S_OK;
}

HRESULT CUtilityMgr::Create_TextureInstance(_uint eSceneID, INSTPARTICLEDESC & tParticleDesc, vector<_float3>* vPosition)
{

	tParticleDesc.FollowingTarget = nullptr;

	switch (tParticleDesc.eParticleTypeID)
	{
	case InstanceEffect_Ball:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Ball"), &tParticleDesc));
		break;
	case InstanceEffect_Straight:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Straight"), &tParticleDesc));
		break;
	case InstanceEffect_Cone:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Cone"), &tParticleDesc));
		break;
	case InstanceEffect_Spread:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Spread"), &tParticleDesc));
		break;
	case InstanceEffect_Suck:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Suck"), &tParticleDesc));
		break;
	case InstanceEffect_Fountain:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_InstanceEffect_Fountain"), &tParticleDesc));
		break;

	case InstanceEffect_End:
		break;
	default:
		break;
	}
	FAILED_CHECK(((CInstanceEffect*)(g_pGameInstance->Get_GameObject_By_LayerLastIndex(eSceneID, TAG_LAY(Layer_Particle))))->Set_AsMapParticle(*vPosition));


	return S_OK;
}

HRESULT CUtilityMgr::Create_MeshInstance(_uint eSceneID, INSTMESHDESC & tParticleDesc)
{

	switch (tParticleDesc.eParticleTypeID)
	{
	case InstanceEffect_Ball:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_MeshEffect_Ball"), &tParticleDesc));
		break;
	case InstanceEffect_Straight:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_MeshEffect_Straight"), &tParticleDesc));
		break;
	case InstanceEffect_Cone:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_MeshEffect_Cone"), &tParticleDesc));
		break;
	case InstanceEffect_Spread:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_MeshEffect_Spread"), &tParticleDesc));
		break;
	case InstanceEffect_Suck:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_MeshEffect_Suck"), &tParticleDesc));
		break;
	case InstanceEffect_Fountain:
		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_To_Layer(eSceneID, TAG_LAY(Layer_Particle), TEXT("ProtoType_GameObjectObject_MeshEffect_Fountain"), &tParticleDesc));
		break;


	case InstanceEffect_End:
		break;
	default:
		break;
	}

	return S_OK;
}

HRESULT CUtilityMgr::Bind_UtilTex_OnShader(UTILTEXTUREID eID, CShader * pShader, const char * szhlslConstName, _uint iTextureIndex)
{

	switch (eID)
	{
	case Client::CUtilityMgr::UTILTEX_NOISE:
		FAILED_CHECK(m_pTexture->Change_TextureLayer(L"NoiseTexture"));
		break;
	case Client::CUtilityMgr::UTILTEX_MASK:
		FAILED_CHECK(m_pTexture->Change_TextureLayer(L"MaskTexture"));
		break;
	case Client::CUtilityMgr::UTILTEX_MINIGAMETEX:
		FAILED_CHECK_NONERETURN(m_pTexture->Change_TextureLayer(L"MGBT"));
		break;
	default:
		break;
	}


	FAILED_CHECK(m_pTexture->Bind_OnShader(pShader, szhlslConstName, iTextureIndex));

	return S_OK;
}

ID3D11ShaderResourceView * CUtilityMgr::Get_UtilTex_SRV(UTILTEXTUREID eID, _uint iTextureIndex)
{
	switch (eID)
	{
	case Client::CUtilityMgr::UTILTEX_NOISE:
		FAILED_CHECK_NONERETURN(m_pTexture->Change_TextureLayer(L"NoiseTexture"));
		break;
	case Client::CUtilityMgr::UTILTEX_MASK:
		FAILED_CHECK_NONERETURN(m_pTexture->Change_TextureLayer(L"MaskTexture"));
		break;
	case Client::CUtilityMgr::UTILTEX_MINIGAMETEX:
		FAILED_CHECK_NONERETURN(m_pTexture->Change_TextureLayer(L"MGBT"));
		break;
	default:
		break;
	}


	return m_pTexture->Get_ShaderResourceView(iTextureIndex);
}

HRESULT CUtilityMgr::Bind_DissolveTex_OnShader(CShader * pShader, _uint iRampTextureIndex)
{
	if (iRampTextureIndex < 1) iRampTextureIndex = 1;

	FAILED_CHECK(m_pDissolveTexture->Bind_OnShader(pShader, "g_DissolveNoiseTexture", 0));
	FAILED_CHECK(m_pDissolveTexture->Bind_OnShader(pShader, "g_BurnRampTexture", iRampTextureIndex));


	return S_OK;
}

INSTPARTICLEDESC CUtilityMgr::Get_TextureParticleDesc(const _tchar * szFileName)
{
	auto iter = find_if(m_mapTextureParticles.begin(), m_mapTextureParticles.end(), CTagStringFinder(szFileName));

	if (iter == m_mapTextureParticles.end())
	{
		__debugbreak();
		return INSTPARTICLEDESC();
	}

	return iter->second;

}

INSTMESHDESC CUtilityMgr::Get_MeshParticleDesc(const _tchar * szFileName)
{
	auto iter = find_if(m_mapMeshParticles.begin(), m_mapMeshParticles.end(), CTagStringFinder(szFileName));

	if (iter == m_mapMeshParticles.end())
	{
		__debugbreak();
		return INSTMESHDESC();
	}

	return iter->second;

}

HRESULT CUtilityMgr::Copy_LastDeferredToToonShadingTexture(_float fToonRate,_bool bIsSecond)
{
	return m_pLoadingSCD.pRenderer->Copy_LastDeferredToToonShadingTexture(fToonRate, bIsSecond);
}

HRESULT CUtilityMgr::SCD_Rendering()
{

	FAILED_CHECK(m_pLoadingSCD.Render_SCD(1));

	return S_OK;
}

HRESULT CUtilityMgr::SCD_Rendering_Rolling(_float RollingStartTime, _float RollingTargetTime,const _tchar* szRenderTargetTag)
{
#define NumRollingTexture 10
	_uint RollingRate = min(_uint(RollingStartTime / RollingTargetTime * _float(NumRollingTexture)) , NumRollingTexture - 1);


	FAILED_CHECK_NONERETURN(m_pTexture->Change_TextureLayer(L"NoiseTexture"));
	FAILED_CHECK(m_pTexture->Bind_OnShader(m_pLoadingSCD.pShader, "g_NoiseTexture", SceneChangeNoiseIndex));
	FAILED_CHECK(m_pLoadingSCD.pShader->Set_Texture("g_DiffuseTexture", g_pGameInstance->Get_SRV(szRenderTargetTag)));
	FAILED_CHECK(m_pLoadingSCD.Render_SCD_Rolling(RollingRate));
	//PS_PaperCurlOut
	return S_OK;
}

HRESULT CUtilityMgr::SCD_Rendering_FadeOut(_float RollingStartTime, _float RollingTargetTime, const _tchar * szRenderTargetTag)
{
	_float FadeIntensive = min(max(RollingStartTime / RollingTargetTime,0.f ),1.f);


	FAILED_CHECK_NONERETURN(m_pTexture->Change_TextureLayer(L"NoiseTexture"));
	FAILED_CHECK(m_pTexture->Bind_OnShader(m_pLoadingSCD.pShader, "g_NoiseTexture", SceneChangeNoiseIndex));
	FAILED_CHECK(m_pLoadingSCD.pShader->Set_Texture("g_SourTexture", g_pGameInstance->Get_SRV(szRenderTargetTag)));
	FAILED_CHECK(m_pLoadingSCD.Render_SCD_FadeOut( 8, FadeIntensive));

	return S_OK;
}

CCamera_Main* CUtilityMgr::Get_MainCamera()
{
	CCamera_Main* pMainCam = nullptr;
	pMainCam = ((CCamera_Main*)(g_pGameInstance->Get_GameObject_By_LayerIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main))));
	return pMainCam;
}

void CUtilityMgr::Set_RadialBlurTargetPos_ByWorldPos(_float3 vPos)
{
	NULL_CHECK_BREAK(m_pRadialUI);

	m_pRadialUI->Set_TargetPos_ByWorldPos(vPos);
}

void CUtilityMgr::Set_IsRadialBlurFadeIn(_bool bBool, _float fZoomRadialSize, _float fZoomPower, _float TargetTimer)
{
	NULL_CHECK_BREAK(m_pRadialUI);
	m_pRadialUI->Set_IsRadialIn(bBool,  fZoomRadialSize,  fZoomPower,  TargetTimer);
}

void CUtilityMgr::Set_HitEffect(_float Intensive, _float HitTime, _float3 vColor)
{
	NULL_CHECK_BREAK(m_pHitEffectUI);
	m_pHitEffectUI->Set_HitEffect(Intensive , HitTime, vColor);
}

HRESULT CUtilityMgr::Clear_RenderGroup_forSceneChange()
{
	NULL_CHECK_RETURN(m_pRenderer, E_FAIL);

	FAILED_CHECK(m_pRenderer->Copy_LastDeferredTexture());

	g_pGameInstance->Clear_CollisionGroup();
	return  S_OK;
}

void CUtilityMgr::Set_Renderer(CRenderer * pRenderer)
{
	m_pRenderer = pRenderer;
	Safe_AddRef(m_pRenderer);
}

void CUtilityMgr::Plus_SKillPoint(_int PointCount)
{
	m_iSkillPoint += PointCount; 
	if (m_iSkillPoint > 18) m_iSkillPoint = 18;

	INSTPARTICLEDESC tDesc[3];

	tDesc[0]= Get_TextureParticleDesc(L"JY_TextureEft_4");
	tDesc[0].FollowingTarget = nullptr;

	//3
	tDesc[1] = (Get_TextureParticleDesc(L"JY_TextureEft_6"));
	tDesc[1].FollowingTarget = nullptr;
	tDesc[1].eInstanceCount = Prototype_VIBuffer_Point_Instance_4;

	//4
	tDesc[2] = (Get_TextureParticleDesc(L"JY_TextureEft_7"));
	tDesc[2].FollowingTarget = nullptr;

	tDesc[0].vFixedPosition = tDesc[1].vFixedPosition = tDesc[2].vFixedPosition
		= g_pGameInstance->Get_TargetPostion_Vector(PLV_PLAYER) + XMVectorSet(0,.5f,0,0);

	for (_uint i = 0; i < 2; i++)
		Create_TextureInstance(g_pGameInstance->Get_NowSceneNum(), tDesc[i]);

}

HRESULT CUtilityMgr::Ready_SceneChangingData(_uint eSceneID, _uint iLayerIndex)
{
	m_tForSceneChangingData = m_pRenderer->Get_PostProcessingData();

	m_tForSceneChangingData.PlayerWorldMat = ((CTransform*)(g_pGameInstance->Get_Commponent_By_LayerIndex(eSceneID, TAG_LAY(Layer_Player), TAG_COM(Com_Transform))))->Get_WorldFloat4x4();
	m_tForSceneChangingData.CamWorldMat =		((CCamera_Main*)(g_pGameInstance->Get_GameObject_By_LayerLastIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main))))->Get_Camera_Transform()->Get_WorldFloat4x4();
	m_tForSceneChangingData.ObjMgrLaterIdx = iLayerIndex;

	return S_OK;
}

PPDDESC CUtilityMgr::Set_SceneChangingData(_uint eSceneID)
{

	m_pRenderer->Set_PostProcessingData(m_tForSceneChangingData);

	((CTransform*)(g_pGameInstance->Get_Commponent_By_LayerIndex(eSceneID, TAG_LAY(Layer_Player), TAG_COM(Com_Transform))))->Set_Matrix(m_tForSceneChangingData.PlayerWorldMat);

	((CCamera_Main*)(g_pGameInstance->Get_GameObject_By_LayerLastIndex(SCENE_STATIC, TAG_LAY(Layer_Camera_Main))))->Get_Camera_Transform()->Set_Matrix(m_tForSceneChangingData.CamWorldMat);



	return m_tForSceneChangingData;
}


_uint CUtilityMgr::CountDigit(_uint iNum)
{
	string tmp;
	tmp = to_string(iNum);
	return _uint(tmp.size());
}

HRESULT CUtilityMgr::Ready_Particles()
{
	FAILED_CHECK(Ready_TextureParticles());
	FAILED_CHECK(Ready_MeshParticles());

	return S_OK;
}

HRESULT CUtilityMgr::Ready_TextureParticles()
{

	//../Bin/Resources/Data/ParicleData/ParticlePathData/TextureParticlePath.txt
	//../Bin/Resources/Data/ParicleData/ParticlePathData/MeshParticlePath.txt

	m_mapTextureParticles.clear();

	wifstream		fin;

	_tchar FullFilePath[MAX_PATH] = L"../Bin/Resources/Data/ParicleData/ParticlePathData/TextureParticlePath.txt";

	fin.open(FullFilePath);


	vector<LOADPARTICLE> tPathList;


	//_tchar		szTextureFilePath[MAX_PATH] = TEXT("");
	_tchar		szFileNameBuffer[MAX_PATH] = TEXT("");



	if (!fin.fail())
	{
		_tchar	szPadding[64] = L"";
		_tchar	szStateKey[MAX_PATH] = L"";
		_tchar	szCount[MAX_PATH] = L"";
		_tchar	szPath[MAX_PATH] = L"";



		while (true)
		{

			// '|' ������ ��� ���ڿ� �Է� ó��

			lstrcpy(szPadding, L"");
			lstrcpy(szStateKey, L"");
			lstrcpy(szCount, L"");
			lstrcpy(szPath, L"");


			fin.getline(szPadding, MAX_PATH, '|');
			fin.getline(szStateKey, MAX_PATH, '|');
			fin.getline(szCount, MAX_PATH, '|');
			fin.getline(szPath, MAX_PATH);

			if (fin.eof())
				break;

			lstrcpy(szFileNameBuffer, L"");

			_wsplitpath_s(szPath, nullptr, 0, nullptr, 0, szFileNameBuffer, MAX_PATH, nullptr, 0);

			LOADPARTICLE tParticlePath;

			tParticlePath.szFilePath = szPath;
			tParticlePath.szFileName = szFileNameBuffer;

			tPathList.push_back(tParticlePath);

		}

		fin.close();		// close �Լ��� ���� ����(��ü Ÿ���̾ �Ҹ� ������ �˾Ƽ� ������ ���� ���� �Ҹ� ����)
	}


	for (_uint i = 0 ; i < tPathList.size(); i++)
	{
		INSTPARTICLEDESC m_tParticleDesc;


		HANDLE hFile = ::CreateFileW(tPathList[i].szFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);


		if (INVALID_HANDLE_VALUE == hFile)
		{
			DEBUGBREAK;
			return E_FAIL;
		}


		DWORD	dwByte = 0;
		_int iIDLength = 0;
		_tchar szTempBuffer[MAX_PATH] = L"";




		ReadFile(hFile, &(m_tParticleDesc.eParticleTypeID), sizeof(eInstanceEffectID), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.eInstanceCount), sizeof(COMPONENTPROTOTYPEID), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.ePassID), sizeof(eInstancePassID), &dwByte, nullptr);

		ReadFile(hFile, &(m_tParticleDesc.bBillboard), sizeof(_bool), &dwByte, nullptr);


		ReadFile(hFile, &(m_tParticleDesc.vFixedPosition), sizeof(_float3), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.vPowerDirection), sizeof(_float3), &dwByte, nullptr);


		lstrcpy(szTempBuffer, L"");
		ReadFile(hFile, &(iIDLength), sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, (szTempBuffer), sizeof(_tchar) * iIDLength, &dwByte, nullptr);
		lstrcpy(m_tParticleDesc.szTextureProtoTypeTag, szTempBuffer);
		ZeroMemory(szTempBuffer, sizeof(_tchar) * MAX_PATH);


		lstrcpy(szTempBuffer, L"");
		ReadFile(hFile, &(iIDLength), sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, (szTempBuffer), sizeof(_tchar) * iIDLength, &dwByte, nullptr);
		lstrcpy(m_tParticleDesc.szTextureLayerTag, szTempBuffer);
		ZeroMemory(szTempBuffer, sizeof(_tchar) * MAX_PATH);


		ReadFile(hFile, &(m_tParticleDesc.iTextureLayerIndex), sizeof(_int), &dwByte, nullptr);


		ReadFile(hFile, &(m_tParticleDesc.iNoiseTextureIndex), sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.iMaskingTextureIndex), sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.vNoisePushingDir), sizeof(_float2), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.fAppearTimer), sizeof(_float), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.fDistortionNoisingPushPower), sizeof(_float), &dwByte, nullptr);

		ReadFile(hFile, &(m_tParticleDesc.TextureChageFrequency), sizeof(_uint), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.vTextureXYNum), sizeof(_float2), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.iFigureCount_In_Texture), sizeof(_int), &dwByte, nullptr);


		ReadFile(hFile, &(m_tParticleDesc.TotalParticleTime), sizeof(_float), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.EachParticleLifeTime), sizeof(_float), &dwByte, nullptr);


		ReadFile(hFile, &(m_tParticleDesc.SizeChageFrequency), sizeof(_uint), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.ParticleSize), sizeof(_float3), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.ParticleSize2), sizeof(_float3), &dwByte, nullptr);


		ReadFile(hFile, &(m_tParticleDesc.ColorChageFrequency), sizeof(_uint), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.TargetColor), sizeof(_float4), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.TargetColor2), sizeof(_float4), &dwByte, nullptr);



		ReadFile(hFile, &(m_tParticleDesc.fMaxBoundaryRadius), sizeof(_float), &dwByte, nullptr);


		ReadFile(hFile, &(m_tParticleDesc.Particle_Power), sizeof(_float), &dwByte, nullptr);

		ReadFile(hFile, &(m_tParticleDesc.PowerRandomRange), sizeof(_float2), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.SubPowerRandomRange_RUL), sizeof(_float3), &dwByte, nullptr);

		ReadFile(hFile, &(m_tParticleDesc.ParticleStartRandomPosMin), sizeof(_float3), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.ParticleStartRandomPosMax), sizeof(_float3), &dwByte, nullptr);


		ReadFile(hFile, &(m_tParticleDesc.AlphaBlendON), sizeof(_bool), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.bEmissive), sizeof(_bool), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.vEmissive_SBB), sizeof(_float3), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.m_fAlphaTestValue), sizeof(_float), &dwByte, nullptr);



		ReadFile(hFile, &(m_tParticleDesc.TempBuffer_0), sizeof(_float4), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.TempBuffer_1), sizeof(_float4), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.TempBuffer_2), sizeof(_float4), &dwByte, nullptr);
		ReadFile(hFile, &(m_tParticleDesc.TempBuffer_3), sizeof(_float4), &dwByte, nullptr);




		m_mapTextureParticles.emplace(tPathList[i].szFileName,	m_tParticleDesc );


		CloseHandle(hFile);
	}



	return S_OK;
}

HRESULT CUtilityMgr::Ready_MeshParticles()
{
	m_mapMeshParticles.clear();

	wifstream		fin;
	//
	_tchar FullFilePath[MAX_PATH] = L"../Bin/Resources/Data/ParicleData/ParticlePathData/MeshParticlePath.txt";

	fin.open(FullFilePath);


	vector<LOADPARTICLE> tPathList;


	//_tchar		szTextureFilePath[MAX_PATH] = TEXT("");
	_tchar		szFileNameBuffer[MAX_PATH] = TEXT("");



	if (!fin.fail())
	{
		_tchar	szPadding[64] = L"";
		_tchar	szStateKey[MAX_PATH] = L"";
		_tchar	szCount[MAX_PATH] = L"";
		_tchar	szPath[MAX_PATH] = L"";



		while (true)
		{

			// '|' ������ ��� ���ڿ� �Է� ó��

			lstrcpy(szPadding, L"");
			lstrcpy(szStateKey, L"");
			lstrcpy(szCount, L"");
			lstrcpy(szPath, L"");


			fin.getline(szPadding, MAX_PATH, '|');
			fin.getline(szStateKey, MAX_PATH, '|');
			fin.getline(szCount, MAX_PATH, '|');
			fin.getline(szPath, MAX_PATH);

			if (fin.eof())
				break;

			lstrcpy(szFileNameBuffer, L"");

			_wsplitpath_s(szPath, nullptr, 0, nullptr, 0, szFileNameBuffer, MAX_PATH, nullptr, 0);

			LOADPARTICLE tParticlePath;

			tParticlePath.szFilePath = szPath;
			tParticlePath.szFileName = szFileNameBuffer;

			tPathList.push_back(tParticlePath);

		}

		fin.close();		// close �Լ��� ���� ����(��ü Ÿ���̾ �Ҹ� ������ �˾Ƽ� ������ ���� ���� �Ҹ� ����)
	}


	for (_uint i = 0; i < tPathList.size(); i++)
	{
		INSTMESHDESC m_tMeshDesc;


		HANDLE hFile = ::CreateFileW(tPathList[i].szFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			DEBUGBREAK;
			return E_FAIL;
		}


		DWORD	dwByte = 0;
		_int iIDLength = 0;



		ReadFile(hFile, &(m_tMeshDesc.eParticleTypeID), sizeof(eInstanceEffectID), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.eInstanceCount), sizeof(COMPONENTPROTOTYPEID), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.ePassID), sizeof(eMeshInstancePassID), &dwByte, nullptr);

		ReadFile(hFile, &(m_tMeshDesc.vFixedPosition), sizeof(_float3), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.vPowerDirection), sizeof(_float3), &dwByte, nullptr);

		_tchar szTempBuffer[MAX_PATH] = L"";
		lstrcpy(szTempBuffer, L"");

		ReadFile(hFile, &(iIDLength), sizeof(_int), &dwByte, nullptr);

		ReadFile(hFile, (szTempBuffer), sizeof(_tchar) * iIDLength, &dwByte, nullptr);
		lstrcpy(m_tMeshDesc.szModelMeshProtoTypeTag, szTempBuffer);

		ReadFile(hFile, &(m_tMeshDesc.iModelAnimIndex), sizeof(_int), &dwByte, nullptr);


		ReadFile(hFile, &(m_tMeshDesc.iNoiseTextureIndex), sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.iMaskingTextureIndex), sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.vNoisePushingDir), sizeof(_float2), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.fAppearTimer), sizeof(_float), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.fDistortionNoisingPushPower), sizeof(_float), &dwByte, nullptr);


		ReadFile(hFile, &(m_tMeshDesc.TotalParticleTime), sizeof(_float), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.EachParticleLifeTime), sizeof(_float), &dwByte, nullptr);


		ReadFile(hFile, &(m_tMeshDesc.SizeChageFrequency), sizeof(_uint), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.ParticleSize), sizeof(_float3), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.ParticleSize2), sizeof(_float3), &dwByte, nullptr);


		ReadFile(hFile, &(m_tMeshDesc.ColorChageFrequency), sizeof(_uint), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.TargetColor), sizeof(_float4), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.TargetColor2), sizeof(_float4), &dwByte, nullptr);



		ReadFile(hFile, &(m_tMeshDesc.fMaxBoundaryRadius), sizeof(_float), &dwByte, nullptr);


		ReadFile(hFile, &(m_tMeshDesc.Particle_Power), sizeof(_float), &dwByte, nullptr);

		ReadFile(hFile, &(m_tMeshDesc.PowerRandomRange), sizeof(_float2), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.SubPowerRandomRange_RUL), sizeof(_float3), &dwByte, nullptr);

		ReadFile(hFile, &(m_tMeshDesc.ParticleStartRandomPosMin), sizeof(_float3), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.ParticleStartRandomPosMax), sizeof(_float3), &dwByte, nullptr);


		ReadFile(hFile, &(m_tMeshDesc.bAutoTurn), sizeof(_bool), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.bIsOclusion), sizeof(_bool), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.bEmissive), sizeof(_bool), &dwByte, nullptr);


		ReadFile(hFile, &(m_tMeshDesc.vEmissive_SBB), sizeof(_float3), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.fRotSpeed_Radian), sizeof(_float), &dwByte, nullptr);


		ReadFile(hFile, &(m_tMeshDesc.TempBuffer_0), sizeof(_float4), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.TempBuffer_1), sizeof(_float4), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.TempBuffer_2), sizeof(_float4), &dwByte, nullptr);
		ReadFile(hFile, &(m_tMeshDesc.TempBuffer_3), sizeof(_float4), &dwByte, nullptr);


		m_mapMeshParticles.emplace(tPathList[i].szFileName, m_tMeshDesc);


		CloseHandle(hFile);
	}







	return S_OK;
}


void CUtilityMgr::Free()
{
	m_pLoadingSCD.Free();

	Safe_Release(m_pRenderer);
	Safe_Release(m_pTexture);
	Safe_Release(m_pDissolveTexture);


	Safe_Release(m_pVIBufferRect);
	Safe_Release(m_pRectShader);

	
	Safe_Release(m_pDevice);
	Safe_Release(m_pDeviceContext);
}
