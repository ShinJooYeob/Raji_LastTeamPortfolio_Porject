#pragma once
#include "Base.h"

BEGIN(Engine)
class CFrustumMgr :public CBase
{
	DECLARE_SINGLETON(CFrustumMgr);

private:
	explicit CFrustumMgr();
	virtual ~CFrustumMgr() = default;

public:
	HRESULT Initialize_FrustumMgr(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);

public:
	//이 함수는 매 프레임 당 한번만 실행 어차피 매 프레임 같은 투영, 뷰 행렬일테니까 
	HRESULT SetUp_WorldFrustumPlane();
	HRESULT SetUp_LightFrustumPlane();

	//이 함수를 이제 객체별로 전달해서 그려야할지 여부를 판단
	_bool IsNeedToRender(_float3 vWorldPosition, _float fLenth = 1.4142135623f);
	_bool IsNeedToLightRender(_float3 vWorldPosition, _float fLenth = 1.4142135623f);

private:
	_float3 vDefaultProjectFrustumCubePos[8];
	_float4 tWorldFrustumPlane[6];
	_float4 tLightFrustumPlane[6];

private:
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pDeviceContext = nullptr;

public:
	virtual void Free() override;

};
END

