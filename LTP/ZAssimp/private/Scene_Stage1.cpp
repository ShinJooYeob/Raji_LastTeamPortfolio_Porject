#include "stdafx.h"
#include "..\Public\Scene_Stage1.h"
#include "Scene_Loading.h"
#include "Camera_Main.h"



CScene_Stage1::CScene_Stage1(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CScene(pDevice,pDeviceContext)
{
}





HRESULT CScene_Stage1::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;


	FAILED_CHECK(Ready_Light());

	FAILED_CHECK(Ready_Layer_MainCamera(TAG_LAY(Layer_Camera_Main)));
	FAILED_CHECK(Ready_Layer_SkyBox(TAG_LAY(Layer_SkyBox)));
	FAILED_CHECK(Ready_Layer_Terrain(TAG_LAY(Layer_Terrain)));
	
	
			

	return S_OK;
}

_int CScene_Stage1::Update(_double fDeltaTime)
{
	if (__super::Update(fDeltaTime) < 0)
		return -1;

	if (m_bIsNeedToSceneChange)
		return Change_to_NextScene();




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

#ifdef _DEBUG
	if (!g_bIsShowFPS)
		SetWindowText(g_hWnd, TEXT("Scene_Stage1"));
#endif // _DEBUG

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

	FAILED_CHECK(GetSingle(CUtilityMgr)->Clear_RenderGroup_forSceneChange());
	FAILED_CHECK(g_pGameInstance->Scene_Change(CScene_Loading::Create(m_pDevice, m_pDeviceContext, (SCENEID) m_eNextScene), SCENEID::SCENE_LOADING));


	return _int();

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
		LightDesc.vVector = _float4(0, 256, -128, 0);

		g_pGameInstance->Add_Light(LightDesc);
	}
	else
	{
		g_pGameInstance->Relocate_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0, _float4(0, 256, -128, 0).XMVector());
	}


	return S_OK;
}

HRESULT CScene_Stage1::Ready_Layer_MainCamera(const _tchar * pLayerTag)
{
	CCamera::CAMERADESC CameraDesc;
	CameraDesc.vWorldRotAxis = _float3(0, 0, 0);
	CameraDesc.vEye = _float3(0, 5.f, -10.f);
	CameraDesc.vAt = _float3(0, 0.f, 0);
	CameraDesc.vAxisY = _float3(0, 1, 0);

	CameraDesc.fFovy = XMConvertToRadians(60.f);
	CameraDesc.fAspect = _float(g_iWinCX) / g_iWinCY;
	CameraDesc.fNear = 0.2f;
	CameraDesc.fFar = 300.f;

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
	}
	
	return S_OK;
}

HRESULT CScene_Stage1::Ready_Layer_SkyBox(const _tchar * pLayerTag)
{
	//FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_SkyBox)));

	return S_OK;
}

HRESULT CScene_Stage1::Ready_Layer_Terrain(const _tchar * pLayerTag)
{
	//FAILED_CHECK(g_pGameInstance->Add_GameObject_To_Layer(SCENE_STAGE1, pLayerTag, TAG_OP(Prototype_Terrain)));



	return S_OK;
}

CScene_Stage1 * CScene_Stage1::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
{
	CScene_Stage1* pTempLoby = new CScene_Stage1(pDevice,pDeviceContext);

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