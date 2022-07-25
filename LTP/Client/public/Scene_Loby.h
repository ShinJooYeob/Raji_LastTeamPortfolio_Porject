#pragma once

#include "Scene.h"

BEGIN(Client)
class CScene_Loby final : public CScene
{
private:
	explicit CScene_Loby(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext);
	virtual ~CScene_Loby() = default;

public:
	virtual HRESULT Initialize();
	virtual _int Update(_double fDeltaTime)override;
	virtual _int LateUpdate(_double fDeltaTime)override;
	virtual _int Render()override;
	virtual _int LateRender()override;

	virtual _int Change_to_NextScene()override;

private:
	HRESULT Ready_Light();
	HRESULT Ready_Camera(const _tchar* pLayerTag);
	//HRESULT Ready_Layer_SkyBox(const _tchar* pLayerTag);


	HRESULT Ready_UI(const _tchar* pLayerTag);


	

private:
	class CCamera_Main*				m_pMainCam = nullptr;
public:
	static CScene_Loby* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext);
	virtual void Free() override;
};

END