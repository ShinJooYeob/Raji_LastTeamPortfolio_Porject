#pragma once

#include "Component.h"


BEGIN(Engine)


class ENGINE_DLL CSwordTrail final : public CComponent
{
public:
	typedef struct tagSwordTrailDesc
	{
		_float4 vColor = _float4(1);
		_uint	iTextureIndex = 1;
		_uint	iPassIndex = 0;
		_float	NoiseSpeed = 1;
		_float2 NoiseDir = _float2(0, 1);
		_uint	NoiseTextureIndex = 0;
		_uint	MaskTextureIndex = 0;
	}TRAILDESC;

private:
	typedef struct tagSourceNDestPoint
	{
		_float3 vSourPoint;
		_float3 vDestPoint;
	}TRAILPOINT;

private:
	CSwordTrail(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CSwordTrail(const CSwordTrail& rhs);
	virtual ~CSwordTrail() = default;

private:
	virtual HRESULT Initialize_Prototype(const _tchar*	szTextureFilePath ,_uint iNumTrailBufferCount);
	virtual HRESULT Initialize_Clone(void * pArg)override;


public:
	_uint Update_SwordTrail(_float3 tSourPoint, _float3 tDestPoint, _double fDeltaTime,_float Rate = 0.5f);
	virtual HRESULT Render() override;


public:
	void Set_TrailTurnOn(_bool bBool, _float3 tSourPoint, _float3 tDestPoint);
	void Set_Color(_float4 vColor) { m_tDesc.vColor = vColor; };
	void Set_TextureIndex(_uint iIndex) { m_tDesc.iTextureIndex = iIndex; };
	void Set_PassIndex(_uint iIndex) { m_tDesc.iPassIndex = iIndex; };
	_bool Get_IsDistortion() {	return (m_tDesc.iPassIndex == 2);};

	
private:
	class CVIBuffer_Point_Instance*	m_pVIBuffer = nullptr;
	class CShader*					m_pShader   = nullptr;
	class CTexture*					m_pTexture = nullptr;
	class CTexture*					m_pNoiseTexture = nullptr;

private:
	list<TRAILPOINT>				m_TrailPointList;
	_uint							m_iNumTrailPoints;

	_bool							m_bDrawTrail = false;

	_float							m_PassedTime = 0;
	TRAILDESC						m_tDesc;

public:
	static CSwordTrail* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext,const _tchar*	szTextureFilePath ,_uint iNumTrailPoints = 10);
	virtual CComponent* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END






