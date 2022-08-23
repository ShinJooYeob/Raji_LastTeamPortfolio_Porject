#pragma once

#include "Scene.h"
#include <physx/PxActor.h>

// JIHWAN
// Assimp Sample Scene
// Phyx Sample Scene

BEGIN(Client)
class CScene_Stage6 final : public CScene
{
private:
	explicit CScene_Stage6(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext);
	virtual ~CScene_Stage6() = default;

public:
	virtual HRESULT Initialize();
	virtual _int Update(_double fDeltaTime)override;
	virtual _int LateUpdate(_double fDeltaTime)override;
	virtual _int Render()override;
	virtual _int LateRender()override;


	virtual _int Change_to_NextScene() override;

	virtual void Play_Scene_BGM() override;

private:
	HRESULT Ready_Light();
	HRESULT Ready_Layer_MainCamera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_SkyBox(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Terrain(const _tchar* pLayerTag);
	HRESULT Ready_Layer_AssimpModelTest(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_TestMapObject(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Monster_Boss(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_MapObject(const _tchar* pLayerTag);
	HRESULT	Ready_MapData(const _tchar* szMapDataFileName, SCENEID eSceneID, const _tchar* pLayerTag);
	HRESULT	Ready_TriggerObject(const _tchar * szTriggerDataName, SCENEID eSceneID, const _tchar * pLayerTag);
	HRESULT	Ready_MonsterBatchTrigger(const _tchar * szTriggerDataName, SCENEID eSceneID, const _tchar * pLayerTag);
	HRESULT Ready_Layer_UI(const _tchar* pLayerTag);
	   	
	HRESULT Ready_Layer_InteractObject(const _tchar * pLayerTag);
	HRESULT	Ready_EnvMappedWater(const _tchar * pLayerTag);

	HRESULT Ready_MiniGameBuilding(const _tchar* pLayerTag);
	
	HRESULT Ready_Layer_Phycis();
	HRESULT Ready_LoadEffectMesh();




	HRESULT Ready_PostPorcessing();
private:
	class CCamera_Main*				m_pMainCam = nullptr;
	CUtilityMgr*					m_pUtilMgr = nullptr;
	CTransform*						m_pPlayerTransform = nullptr;
	_int							m_iBuildingIndex = -1;

	class CPhyxSampleTest*			m_pPhySample = nullptr;
public:
	static CScene_Stage6* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext);
	virtual void Free() override;
};

END