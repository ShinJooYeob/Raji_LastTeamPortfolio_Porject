#include "..\Public\Renderer.h"
#include "GameObject.h"
#include "Camera.h"

#include "RenderTargetMgr.h"
#include "Graphic_Device.h"
#include "Input_Device.h"
#include "ComponentMgr.h"
#include "PipeLineMgr.h"
#include "LightMgr.h"

#include "VIBuffer_Rect.h"
#include "VIBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Model.h"
#include "Dissolve.h"



CRenderer::CRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CComponent(pDevice, pDeviceContext)
	, m_pRenderTargetMgr(CRenderTargetMgr::GetInstance())
	, m_pLightMgr(CLightMgr::GetInstance())
	, m_pGraphicDevice(CGraphic_Device::GetInstance())
{
	Safe_AddRef(m_pRenderTargetMgr);
	Safe_AddRef(m_pLightMgr);
	Safe_AddRef(m_pGraphicDevice);
	ZeroMemory(m_PostProcessingOn, sizeof(_bool) * POSTPROCESSING_END);
}
#define ShadowMapQuality 5

HRESULT CRenderer::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));



	_uint		iNumViewports = 1;

	D3D11_VIEWPORT		Viewport;

	m_pDeviceContext->RSGetViewports(&iNumViewports, &Viewport);

	/* For.Target_Diffuse */
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget( TEXT("Target_MtrlDiffuse"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_ReferenceMtrlDiffuse"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_EnvMappedMask"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	
	/* For.Target_Normal */
	/* ��ֺ����� ���, ����ȭ�ϱⰡ ����. */
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_MtrlNormal"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 1.f)));
	/* For.Target_Emissive*/
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_MtrlEmissive"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	/* For.Target_SpecularMap */
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_MtrlSpecular"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 1.f, 0.f)));
	/* For.Target_Depth */
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_Depth"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(1.f, 0.f, 0.f, 1.f)));
	/* For.Target_WorldPosition */
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_WorldPosition"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(1.f, 0.f, 0.f, 1.f)));

	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_LimLight"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	/* For.Target_OccludedMaskMap */
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_OccludedMaskMap"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));

	

	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_OldWorldPosition"), (_uint)Viewport.Width, (_uint)Viewport.Height,
		DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(1.f, 0.f, 0.f, 1.f),false));


	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_VelocityMap"), (_uint)Viewport.Width, (_uint)Viewport.Height,
		DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(1.f, 0.f, 0.f, 1.f)));

	/* For.Target_Shade */
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_LightShade"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 1.f)));
	/* For.Target_Specular */
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_LightSpecular"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));


	/* For.Target_Shadow*/
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_Shadow"), (_uint)Viewport.Width * ShadowMapQuality, (_uint)Viewport.Height * ShadowMapQuality, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaledShadow"), (_uint)(Viewport.Width * 0.5f), (_uint)(Viewport.Height * 0.5f), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_ReferenceDownScaledShadow"), (_uint)(Viewport.Width * 0.5f), (_uint)(Viewport.Height * 0.5f), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_UpScaledBluredShadow"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));


	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_Defferred"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_ReferenceDefferred"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DeferredSceneChaging"), (_uint)Viewport.Width, (_uint)Viewport.Height,
		DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f), false));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_MtrlDiffuseSceneChaging"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R16G16B16A16_UNORM,
		_float4(0.f, 0.f, 0.f, 0.f), false));

	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_ToonDeferredSceneChaging"), (_uint)Viewport.Width, (_uint)Viewport.Height,
		DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f), false));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_ToonDeferredSceneChaging2"), (_uint)Viewport.Width, (_uint)Viewport.Height,
		DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f), false));



	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_BluredDefferred"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));

	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaledEmissiveMask"), (_uint)(Viewport.Width * 0.5f), (_uint)(Viewport.Height * 0.5f), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_BluredEmissiveMask"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaledMulMaskBluredEmissive"), (_uint)(Viewport.Width * 0.5f), (_uint)(Viewport.Height * 0.5f), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_MulMaskBluredEmissive"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));

	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_AvgLuminece"), (_uint)1, (_uint)1, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_LumineceMask"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	

	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_GodRay"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_ReferenceOclussion"), (_uint)(Viewport.Width * 0.5f), (_uint)(Viewport.Height * 0.5f), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaledRefOclussion"), (_uint)(Viewport.Width * 0.5f), (_uint)(Viewport.Height * 0.5f), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_Oclussion"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_LenseFlare"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));


	

	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaled_By2"), (_uint)(Viewport.Width / 2), (_uint)(Viewport.Height / 2), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaled_By3"), (_uint)(Viewport.Width / 3), (_uint)(Viewport.Height / 3), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaled_By4"), (_uint)(Viewport.Width / 4), (_uint)(Viewport.Height / 4), DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaled_By5"), (_uint)(Viewport.Width / 5), (_uint)(Viewport.Height / 5), DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_DownScaled_By6"), (_uint)(Viewport.Width / 6), (_uint)(Viewport.Height / 6), DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_UpScaled_By2"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_UpScaled_By3"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_UpScaled_By4"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_UpScaled_By5"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_UpScaled_By6"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f)));
	FAILED_CHECK(m_pRenderTargetMgr->Add_RenderTarget(TEXT("Target_BlurNCoppyed"), (_uint)Viewport.Width, (_uint)Viewport.Height, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 0.f, 0.f, 0.f)));



	/* For.MRT_Deferred : ��ü���� �׸��� ���ε�. */
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Material"), TEXT("Target_MtrlDiffuse")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Material"), TEXT("Target_MtrlNormal")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Material"), TEXT("Target_MtrlSpecular")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Material"), TEXT("Target_MtrlEmissive")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Material"), TEXT("Target_Depth")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Material"), TEXT("Target_WorldPosition")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Material"), TEXT("Target_LimLight")));


	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OccludedMaterial"), TEXT("Target_MtrlDiffuse")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OccludedMaterial"), TEXT("Target_MtrlNormal")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OccludedMaterial"), TEXT("Target_MtrlSpecular")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OccludedMaterial"), TEXT("Target_MtrlEmissive")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OccludedMaterial"), TEXT("Target_Depth")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OccludedMaterial"), TEXT("Target_WorldPosition")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OccludedMaterial"), TEXT("Target_LimLight")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OccludedMaterial"), TEXT("Target_OccludedMaskMap")));
	

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_OldWorld"), TEXT("Target_OldWorldPosition")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_VelocityMap"), TEXT("Target_VelocityMap")));
	

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Effect"), TEXT("Target_MtrlDiffuse")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Effect"), TEXT("Target_MtrlNormal")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Effect"), TEXT("Target_MtrlSpecular")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Effect"), TEXT("Target_MtrlEmissive")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Effect"), TEXT("Target_WorldPosition")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Effect"), TEXT("Target_LimLight")));


	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EnvMap"), TEXT("Target_EnvMappedMask")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EnvMap"), TEXT("Target_MtrlNormal")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EnvMap"), TEXT("Target_MtrlSpecular")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EnvMap"), TEXT("Target_MtrlEmissive")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EnvMap"), TEXT("Target_WorldPosition")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EnvMap"), TEXT("Target_LimLight")));


	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_CopyMtrlDiffuse"), TEXT("Target_ReferenceMtrlDiffuse")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_BlurNCoppyed"), TEXT("Target_BlurNCoppyed")));
	
	
	/* For.MRT_LightAcc : ���� �׸��� ���ε� */
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_LightAcc"), TEXT("Target_LightShade")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_LightAcc"), TEXT("Target_LightSpecular")));
	

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DefferredNReference"), TEXT("Target_Defferred")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DefferredNReference"), TEXT("Target_ReferenceDefferred")));
	
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Defferred"), TEXT("Target_Defferred")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ReferenceDefferred"), TEXT("Target_ReferenceDefferred")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_BluredDefferred"), TEXT("Target_BluredDefferred")));



	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DeferredSceneChaging"), TEXT("Target_DeferredSceneChaging")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DeferredSceneChaging"), TEXT("Target_MtrlDiffuseSceneChaging")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ToonDeferredSceneChaging"), TEXT("Target_ToonDeferredSceneChaging")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ToonDeferredSceneChaging2"), TEXT("Target_ToonDeferredSceneChaging2")));

	

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DefferredForNonLightObject"), TEXT("Target_Defferred")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DefferredForNonLightObject"), TEXT("Target_Depth")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DefferredForNonLightObject"), TEXT("Target_WorldPosition")));

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DistortionObject"), TEXT("Target_Defferred")));

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_SubDistortionObject"), TEXT("Target_Defferred")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_SubDistortionObject"), TEXT("Target_Depth")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_SubDistortionObject"), TEXT("Target_WorldPosition")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_SubDistortionObject"), TEXT("Target_MtrlEmissive")));
	
	/* For.MRT_LightAcc : �׸��� �׸��� ���ε� */
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Shadow"), TEXT("Target_Shadow")));

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ShadowDownScaling"), TEXT("Target_ReferenceDownScaledShadow")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ShadowDownScaling"), TEXT("Target_DownScaledRefOclussion")));
	
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ShadowVBlur"), TEXT("Target_DownScaledShadow")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ShadowHBlur_N_UpScaling"), TEXT("Target_UpScaledBluredShadow")));


	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EmissiveVBlur_N_DownScaling"), TEXT("Target_DownScaledEmissiveMask")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EmissiveHBlur_N_UpScaling"), TEXT("Target_BluredEmissiveMask")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DownSclaedMulMaskBluredEmissive"), TEXT("Target_DownScaledMulMaskBluredEmissive")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_MulMaskBluredEmissive"), TEXT("Target_MulMaskBluredEmissive")));
	
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_AvgLuminece"), TEXT("Target_AvgLuminece")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_MakeLumiMask"), TEXT("Target_LumineceMask")));


	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_GodRay"), TEXT("Target_GodRay")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Oclussion"), TEXT("Target_Oclussion")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ReferenceOclussion"), TEXT("Target_ReferenceOclussion")));


	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_LenseFlareNDefferd"), TEXT("Target_Defferred")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_LenseFlareNDefferd"), TEXT("Target_LenseFlare")));
	
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DownScaled_By2"), TEXT("Target_DownScaled_By2")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DownScaled_By3"), TEXT("Target_DownScaled_By3")));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DownScaled_By4"), TEXT("Target_DownScaled_By4")));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DownScaled_By5"), TEXT("Target_DownScaled_By5")));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DownScaled_By6"), TEXT("Target_DownScaled_By6")));

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_UpScaled_By2"), TEXT("Target_UpScaled_By2")));
	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_UpScaled_By3"), TEXT("Target_UpScaled_By3")));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_UpScaled_By4"), TEXT("Target_UpScaled_By4")));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_UpScaled_By5"), TEXT("Target_UpScaled_By5")));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_UpScaled_By6"), TEXT("Target_UpScaled_By6")));



	m_pVIBuffer = CVIBuffer_Rect::Create(m_pDevice, m_pDeviceContext);
	NULL_CHECK_RETURN(m_pVIBuffer, E_FAIL);

	m_pShader = CShader::Create(m_pDevice, m_pDeviceContext, TEXT("Shader_Deferred.hlsl"), VTXTEX_DECLARATION::Elements, VTXTEX_DECLARATION::iNumElements);
	NULL_CHECK_RETURN(m_pShader, E_FAIL);


#ifdef _DEBUG

	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_MtrlDiffuse"), 1280 - 50, 50, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_MtrlNormal"), 1280 - 50, 150, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_MtrlSpecular"), 1280 - 50, 250, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_MtrlEmissive"), 1280 - 50, 350, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_Depth"), 1280 - 50, 450, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_LimLight"), 1280 - 50, 550, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_Defferred"), 1280 - 50, 650, 100, 100));

	

	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_LightShade"), 1280 - 150, 50, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_LightSpecular"), 1280 - 150, 150, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_Shadow"), 1280 - 150, 250, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_UpScaledBluredShadow"), 1280 - 150, 350, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_AvgLuminece"), 1280 - 150, 450, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_LumineceMask"), 1280 - 150, 550, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_BluredEmissiveMask"), 1280 - 150, 650, 100, 100));
	

	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_Oclussion"), 1280 - 250, 50, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_GodRay"), 1280 - 250, 150, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_LenseFlare"), 1280 - 250, 250, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_OldWorldPosition"), 1280 - 250, 350, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_VelocityMap"), 1280 - 250, 450, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_MtrlDiffuseSceneChaging"), 1280 - 250, 550, 100, 100));
	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_ToonDeferredSceneChaging"), 1280 - 250, 650, 100, 100));
	

	FAILED_CHECK(Add_DebugRenderTarget(TEXT("Target_OccludedMaskMap"), 1280 - 350, 50, 100, 100));
	
	
	
#endif
	//POSTPROCESSING_SHADOW, POSTPROCESSING_BLOOM, POSTPROCESSING_DOF, POSTPROCESSING_DDFOG, POSTPROCESSING_GODRAY, POSTPROCESSING_LENSEFLARE,


	XMStoreFloat4x4(&m_WVPmat.WorldMatrix, XMMatrixIdentity());

	m_WVPmat.WorldMatrix._11 = Viewport.Width;
	m_WVPmat.WorldMatrix._22 = Viewport.Height;
	m_WVPmat.WorldMatrix._33 = 1.f;
	memcpy(&m_WVPmat.WorldMatrix.m[3][0], &_float4(Viewport.Width * 0.5f - (Viewport.Width * 0.5f), -Viewport.Height * 0.5f + (Viewport.Height * 0.5f), 0.f, 1.f), sizeof(_float4));

	XMStoreFloat4x4(&m_WVPmat.WorldMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_WVPmat.WorldMatrix)));
	XMStoreFloat4x4(&m_WVPmat.ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_WVPmat.ProjMatrix, XMMatrixTranspose(XMMatrixOrthographicLH(Viewport.Width, Viewport.Height, 0.f, 1.f)));


	m_LightWVPmat.ViewMatrix = XMMatrixTranspose(XMMatrixLookAtLH(XMVectorSet(0, 10, -10, 1), XMVectorSet(m_vSunAtPoint.x, m_vSunAtPoint.y, m_vSunAtPoint.z, 1), XMVectorSet(0, 1, 0, 0)));

	_Matrix LightProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(60.f), 1, 0.2f, 600);
	GetSingle(CPipeLineMgr)->Set_Transform(PLM_LIGHTPROJ, LightProj);
	m_LightWVPmat.ProjMatrix = XMMatrixTranspose(LightProj);
	

	ID3D11Texture2D*		pDepthStencilTexture = nullptr;

	D3D11_TEXTURE2D_DESC	TextureDesc;
	ZeroMemory(&TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	TextureDesc.Width = (_uint)Viewport.Width * ShadowMapQuality;
	TextureDesc.Height = (_uint)Viewport.Height * ShadowMapQuality;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.SampleDesc.Count = 1;

	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	FAILED_CHECK(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pDepthStencilTexture));
	FAILED_CHECK(m_pDevice->CreateDepthStencilView(pDepthStencilTexture, nullptr, &m_LightDepthStencil));
	Safe_Release(pDepthStencilTexture);



	TextureDesc.Width = 1;
	TextureDesc.Height = 1;
	FAILED_CHECK(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pDepthStencilTexture));
	FAILED_CHECK(m_pDevice->CreateDepthStencilView(pDepthStencilTexture, nullptr, &m_AvgLumiDepthStencil));
	Safe_Release(pDepthStencilTexture);

	

	for (_uint i = 0; i < 5; i++)
	{
		TextureDesc.Width = (_uint)(Viewport.Width / (i + 2.f));
		TextureDesc.Height = (_uint)(Viewport.Height / (i + 2.f));
		FAILED_CHECK(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pDepthStencilTexture));
		FAILED_CHECK(m_pDevice->CreateDepthStencilView(pDepthStencilTexture, nullptr, &m_DownScaledDepthStencil[i]));
		Safe_Release(pDepthStencilTexture);
	}


	FAILED_CHECK(GetSingle(CComponentMgr)->Add_Component_Prototype(0, L"Prototype_Texture_Util",
		CTexture::Create(m_pDevice, m_pDeviceContext, L"UtilityTexture.txt")));


	m_pTexture = (CTexture*)GetSingle(CComponentMgr)->Clone_Component(0, L"Prototype_Texture_Util",nullptr);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	FAILED_CHECK(m_pTexture->Change_TextureLayer(L"NoiseTexture"));





	return S_OK;
}

HRESULT CRenderer::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));



	return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eRenderID, CGameObject * pGameObject)
{
	if (eRenderID >= RENDER_END ||
		pGameObject == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}

	if (eRenderID == CRenderer::RENDER_BLEND)
		pGameObject->Compute_RenderSortValue();

	m_RenderObjectList[eRenderID].emplace_back(pGameObject);
	
	Safe_AddRef(pGameObject);


	return S_OK;
}

HRESULT CRenderer::Add_ShadowGroup(SHADOWGROUP eShadowID, CGameObject * pGameObject, CTransform * pTransform, 
	CShader * pShader, CModel* pModel, _float4x4 * AttacehdMatrix, CDissolve* pDissolve)
{
	if (!m_PostProcessingOn[POSTPROCESSING_SHADOW]) return S_FALSE;

	if (pGameObject == nullptr || pTransform == nullptr || pShader == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}

	if (eShadowID < SHADOW_ANIMMODEL || eShadowID >= SHADOW_END || pModel == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}

	if ((eShadowID == SHADOW_ANIMMODEL_ATTACHED || eShadowID == SHADOW_NONANIMMODEL_ATTACHED) && AttacehdMatrix == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}

	SHADOWDESC tDesc;

	tDesc.pGameObject = pGameObject;
	tDesc.pTransform = pTransform;
	tDesc.pModel = pModel;
	tDesc.pShader = pShader;
	tDesc.pDissolve = pDissolve;


	if (tDesc.pGameObject->Get_IsOcllusion())
		tDesc.fIsOcllusion = 0.9f;
	else 
		tDesc.fIsOcllusion = 1.f;

	if (AttacehdMatrix)
		tDesc.AttacehdMatrix = AttacehdMatrix->TransposeXMatrix();


	Safe_AddRef(tDesc.pGameObject);
	m_ShadowObjectList[eShadowID].push_back(tDesc);

	return S_OK;
}

HRESULT CRenderer::Add_ShadowGroup_InstanceModel(INSTANCESHADOWGROUP eShadowID, CGameObject * pGameObject,
	vector<CTransform*>* pvecTransform, CModelInstance* pModelInst,
	CShader * pShader, CModel * pModel, vector<_float4x4>* pvecTransformfloat4x4, vector<_float4>* pvecTimer)
{
	if (!m_PostProcessingOn[POSTPROCESSING_SHADOW]) return S_FALSE;

	if (pGameObject == nullptr || pShader == nullptr || pModelInst == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}

	if (eShadowID < INSTSHADOW_ANIMINSTANCE || eShadowID >= INSTSHADOW_END || pModel == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}
	if (pvecTransform == nullptr && pvecTransformfloat4x4 == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}


	INSTSHADOWDESC tDesc;


	tDesc.pGameObject = pGameObject;
	tDesc.pvecTransform = pvecTransform;
	tDesc.pvecTransformfloat4x4 = pvecTransformfloat4x4;
	tDesc.pModel = pModel;
	tDesc.pShader = pShader;
	tDesc.pModelInstance = pModelInst;
	tDesc.pvecTimer = pvecTimer;

	if (tDesc.pGameObject->Get_IsOcllusion())
		tDesc.fIsOcllusion = 0.9f;
	else
		tDesc.fIsOcllusion = 1.f;



	Safe_AddRef(tDesc.pGameObject);
	m_InstanceShadowList[eShadowID].push_back(tDesc);




	return S_OK;
}

HRESULT CRenderer::Add_TrailGroup(TRAILGROUP eTrailID, CComponent * pTrailComponent)
{
	if (eTrailID >= TRAILGROUP::TRAIL_END)
	{
		__debugbreak();
		return E_FAIL;
	}

	m_TrailList[eTrailID].push_back(pTrailComponent);
	Safe_AddRef(pTrailComponent);


	return S_OK;
}


HRESULT CRenderer::Add_DebugGroup(CComponent * pComponent)
{
	if (!m_PostProcessingOn[POSTPROCESSING_DEBUGCOLLIDER]) return S_FALSE;

	m_DebugObjectList.push_back(pComponent);
	Safe_AddRef(pComponent);

	return S_OK;
}

HRESULT CRenderer::Render_RenderGroup(_double fDeltaTime)
{
	FAILED_CHECK(m_pRenderTargetMgr->Clear_All_RenderTargetColor());

	FAILED_CHECK(Ready_For_Update(fDeltaTime));
	

	FAILED_CHECK(Render_ShadowMap());

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Material")));
	FAILED_CHECK(Render_Priority());
	FAILED_CHECK(Render_NonBlend());
	FAILED_CHECK(Render_Blend());
	FAILED_CHECK(Render_MotionTrail());
	FAILED_CHECK(Render_AfterObj());
	FAILED_CHECK(Render_EffectObj());
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Material")));

	FAILED_CHECK(Render_BlurShadow());
	FAILED_CHECK(Apply_OccludedMask());
	FAILED_CHECK(Render_Lights(fDeltaTime));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_DefferredNReference")));
	FAILED_CHECK(Render_DeferredTexture());
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_DefferredNReference")));



	//////////MRT_DefferredForNonLightObject//////////////
	FAILED_CHECK(Render_NonBlend_NoLight());
	FAILED_CHECK(Render_EnvMappedObj());
	FAILED_CHECK(Render_SwordTrail());
	FAILED_CHECK(Render_DistortionObject());
	FAILED_CHECK(Render_SubDistortionObject());








	FAILED_CHECK(Render_EmissiveBlur());
	if (m_PostProcessingOn[POSTPROCESSING_SHADOW] && m_PostProcessingOn[POSTPROCESSING_GODRAY])
		FAILED_CHECK(Render_GodRay());
	if (m_PostProcessingOn[POSTPROCESSING_DOF])
		FAILED_CHECK(Render_DepthOfField());
	if (m_PostProcessingOn[POSTPROCESSING_SHADOW] && m_PostProcessingOn[POSTPROCESSING_LENSEFLARE])
		FAILED_CHECK(Render_LesnFlare());
	if (m_PostProcessingOn[POSTPROCESSING_DDFOG])
		FAILED_CHECK(Render_DDFog());

	if (m_PostProcessingOn[POSTPROCESSING_CAMMOTIONBLUR])
		FAILED_CHECK(Render_CameraMotionBlur());
	
	if (m_PostProcessingOn[POSTPROCESSING_BLOOM])
		FAILED_CHECK(Render_Bloom());

	FAILED_CHECK(Render_ScreenEffect());
	FAILED_CHECK(Render_JJBMiniGame());

	FAILED_CHECK(Copy_DeferredToBackBuffer());
	FAILED_CHECK(Render_UI());


#ifdef _DEBUG
	if (m_PostProcessingOn[POSTPROCESSING_DEBUGCOLLIDER])
		FAILED_CHECK(Render_Debug());
	if (m_PostProcessingOn[POSTPROCESSING_DEBUGTARGET])
		FAILED_CHECK(m_pRenderTargetMgr->Render_DebugBuffer(TEXT("MRT_DebugRender")));
#endif



	ID3D11ShaderResourceView* pSRV[8] = { nullptr };
	m_pDeviceContext->PSSetShaderResources(0, 8, pSRV);

	return S_OK;
}


HRESULT CRenderer::Clear_RenderGroup_forSceneChaging()
{

	NULL_CHECK_RETURN(m_pLightMgr, E_FAIL);

	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for (auto& RenderObject : m_RenderObjectList[i])
		{
			Safe_Release(RenderObject);
		}
		m_RenderObjectList[i].clear();
	}

	for (_uint i =0; i < SHADOW_END; i++)
	{
		for (auto& ShadowDesc : m_ShadowObjectList[i])
		{
			Safe_Release(ShadowDesc.pGameObject);
		}
		m_ShadowObjectList[i].clear();
	}

	for (_uint i = 0; i < INSTSHADOW_END; i++)
	{
		for (auto& ShadowDesc : m_InstanceShadowList[i])
		{
			Safe_Release(ShadowDesc.pGameObject);
		}
		m_InstanceShadowList[i].clear();
	}

	

	for (_uint i = 0; i < TRAIL_END; ++i)
	{
		for (auto& RenderObject : m_TrailList[i])
		{
			Safe_Release(RenderObject);
		}
		m_TrailList[i].clear();
	}


	for (auto& DebugObject : m_DebugObjectList)
	{
		Safe_Release(DebugObject);
	}
	m_DebugObjectList.clear();


	m_pLightMgr->Clear_PointLightList();

	return S_OK;
}



const _tchar * CRenderer::Get_DebugRenderTargetTag(_uint iIndex)
{
	if (iIndex >= m_szDebugRenderTargetList.size())
	{
		__debugbreak();
		return nullptr;
	}

	return m_szDebugRenderTargetList[iIndex].c_str();
}





HRESULT CRenderer::Render_Priority()
{
	for (auto& RenderObject : m_RenderObjectList[RENDER_PRIORITY])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_PRIORITY].clear();
	return S_OK;
}


HRESULT CRenderer::Render_NonBlend()
{
	for (auto& RenderObject : m_RenderObjectList[RENDER_PRENONBLEND])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_PRENONBLEND].clear();



	for (auto& RenderObject : m_RenderObjectList[RENDER_NONBLEND])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_NONBLEND].clear();


	for (auto& RenderObject : m_RenderObjectList[RENDER_SUBNONBLEND])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_SUBNONBLEND].clear();

	return S_OK;
}

HRESULT CRenderer::Render_Lights(_double fDeltaTime)
{
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_LightAcc")));

	m_pLightMgr->Set_SunAtPoint(m_vSunAtPoint);
	
	FAILED_CHECK(m_pLightMgr->Render(m_pShader, m_pVIBuffer, &m_WVPmat, fDeltaTime));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_LightAcc")));

	return S_OK;
}

HRESULT CRenderer::Render_DeferredTexture()
{

	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);

	_float4x4		ViewMatrixInv, ProjMatrixInv;

	XMStoreFloat4x4(&ViewMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW))));
	XMStoreFloat4x4(&ProjMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ))));

	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrixInv", &ViewMatrixInv, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrixInv", &ProjMatrixInv, sizeof(_float4x4)));


	FAILED_CHECK(m_pShader->Set_RawValue("g_vCamPosition", &pPipeLineMgr->Get_TargetPostion_float4(PLV_CAMERA), sizeof(_float4)));

	


	FAILED_CHECK(m_pShader->Set_Texture("g_DiffuseTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlDiffuse"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_ShadeTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_LightShade"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_SpecularTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_LightSpecular"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_WorldPosTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_WorldPosition"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_ShadowMapTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_UpScaledBluredShadow"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_NormalTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlNormal"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_EmissiveTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlEmissive"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_LimLightTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_LimLight"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_MaskTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_AvgLuminece"))));
	
	
	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 3));
	//�̹� �н����� ���� �׷���
	//FAILED_CHECK(Copy_DeferredToReference());


	return S_OK;
}

HRESULT CRenderer::Copy_DeferredToReference()
{
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_ReferenceDefferred")));
	

	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Defferred"))));
	

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));


	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 0));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_ReferenceDefferred")));
	return S_OK;
}



HRESULT CRenderer::Copy_DeferredToBackBuffer()
{
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Defferred"))));


	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));
	
	
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 14));

	return S_OK;
}

HRESULT CRenderer::Ready_DepthStencilBuffer(_uint iDSVIndex, D3D11_VIEWPORT* pOutOldViewPort)
{
	if (iDSVIndex >= 5 || pOutOldViewPort == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}


	m_pDeviceContext->ClearDepthStencilView(m_DownScaledDepthStencil[iDSVIndex], D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);


	_uint		iNumViewports = 1;
	D3D11_VIEWPORT		OldViewPortDesc;
	m_pDeviceContext->RSGetViewports(&iNumViewports, &OldViewPortDesc);

	D3D11_VIEWPORT			ViewPortDesc;
	ZeroMemory(&ViewPortDesc, sizeof(D3D11_VIEWPORT));
	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = (_float)(OldViewPortDesc.Width / (iDSVIndex + 2.f));
	ViewPortDesc.Height = (_float)(OldViewPortDesc.Height / (iDSVIndex + 2.f));
	ViewPortDesc.MinDepth = 0.f;
	ViewPortDesc.MaxDepth = 1.f;

	m_pDeviceContext->RSSetViewports(iNumViewports, &ViewPortDesc);


	*pOutOldViewPort = OldViewPortDesc;

	return S_OK;
}

HRESULT CRenderer::Render_BlurShadow()
{
	if (!m_PostProcessingOn[POSTPROCESSING_SHADOW]) return S_FALSE;
	


		D3D11_VIEWPORT		OldViewPortDesc;


		FAILED_CHECK(Ready_DepthStencilBuffer(0, &OldViewPortDesc));
		FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_ShadowDownScaling"), m_DownScaledDepthStencil[0]));


		CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);

		_float4x4		ViewMatrixInv, ProjMatrixInv;

		XMStoreFloat4x4(&ViewMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW))));
		XMStoreFloat4x4(&ProjMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ))));

		FAILED_CHECK(m_pShader->Set_RawValue("g_fShadowIntensive", &m_fShadowIntensive, sizeof(_float)));
		

		FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrixInv", &ViewMatrixInv, sizeof(_float4x4)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrixInv", &ProjMatrixInv, sizeof(_float4x4)));

		FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

		FAILED_CHECK(m_pShader->Set_RawValue("g_LightViewMatrix", &m_LightWVPmat.ViewMatrix, sizeof(_float4x4)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_LightProjMatrix", &m_LightWVPmat.ProjMatrix, sizeof(_float4x4)));

		FAILED_CHECK(m_pShader->Set_Texture("g_WorldPosTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_WorldPosition"))));
		FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Shadow"))));



		LIGHTDESC* pLightDesc = m_pLightMgr->Get_LightDesc(LIGHTDESC::TYPE_DIRECTIONAL, 0);
		if (!pLightDesc) return S_FALSE;

		_Vector vSunDir = XMVector3Normalize(XMVectorSet(m_vSunAtPoint.x, m_vSunAtPoint.y, m_vSunAtPoint.z, 1) - XMVectorSetW(pLightDesc->vVector.XMVector(), 1));

		_Matrix vCamWorldMat = pPipeLineMgr->Get_Transform_Float4x4(PLM_VIEW).InverseXMatrix();
		_Vector vCamLook = XMVector3Normalize(vCamWorldMat.r[2]);




		_float3 vSunPos = pLightDesc->vVector.XMVector();
		_Matrix mView = pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW);
		_Matrix mProj = pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ);

		_Matrix mViewProjection = mView * mProj;
		_float3 vSunPosSS = vSunPos.Multiply_Matrix_AsPosVector(mViewProjection);

		vSunPosSS.x = (vSunPosSS.x * 0.5f) + 0.5f;
		vSunPosSS.y = (vSunPosSS.y * -0.5f) + 0.5f;


		const float dotCamSun = -XMVectorGetX(XMVector3Dot(XMVectorSetW(vCamLook, 0), XMVectorSetW(vSunDir, 0)));
		if (dotCamSun <= 0.0f)
		{
			vSunPosSS.x = -100.f;
			vSunPosSS.y = -100.f;
		}

		FAILED_CHECK(m_pShader->Set_RawValue("SunPos", &vSunPosSS, sizeof(_float2)));

		FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 8));

		FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_ShadowDownScaling")));







		FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_ShadowVBlur"), m_DownScaledDepthStencil[0]));


		m_fTexleSize = 3.f;
		FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &m_fTexleSize, sizeof(_float)));

		FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDownScaledShadow"))));
		FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 6));

		m_pDeviceContext->RSSetViewports(1, &OldViewPortDesc);
		FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_ShadowVBlur")));






		FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_ShadowHBlur_N_UpScaling")));

		FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_DownScaledShadow"))));
		FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 7));

		FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_ShadowHBlur_N_UpScaling")));


	

	return S_OK;
}

HRESULT CRenderer::Caculate_AvgLuminence()
{


	m_pDeviceContext->ClearDepthStencilView(m_AvgLumiDepthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);


	_uint		iNumViewports = 1;
	D3D11_VIEWPORT		OldViewPortDesc;
	m_pDeviceContext->RSGetViewports(&iNumViewports, &OldViewPortDesc);

	D3D11_VIEWPORT			ViewPortDesc;
	ZeroMemory(&ViewPortDesc, sizeof(D3D11_VIEWPORT));
	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = 1;
	ViewPortDesc.Height =1;
	ViewPortDesc.MinDepth = 0.f;
	ViewPortDesc.MaxDepth = 1.f;

	m_pDeviceContext->RSSetViewports(iNumViewports, &ViewPortDesc);
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_AvgLuminece"), m_AvgLumiDepthStencil));


	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));


	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Defferred"))));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 10));

	m_pDeviceContext->RSSetViewports(1, &OldViewPortDesc);
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_AvgLuminece")));






	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_MakeLumiMask")));
	
	FAILED_CHECK(m_pShader->Set_RawValue("g_fOverLuminence", &m_fOverLuminece, sizeof(_float)));


	FAILED_CHECK(m_pShader->Set_Texture("g_MaskTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_AvgLuminece"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Defferred"))));
	
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 11));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_MakeLumiMask")));

	return S_OK;
}

HRESULT CRenderer::Render_Bloom()
{
	FAILED_CHECK(Make_BluredDeffered(2.f));
	FAILED_CHECK(Caculate_AvgLuminence());

	m_fTexleSize = 2.f;
	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &m_fTexleSize, sizeof(_float)));


	D3D11_VIEWPORT OldVp;
	FAILED_CHECK(Ready_DepthStencilBuffer(0, &OldVp));

	wstring TargetMrt = L"MRT_DownScaled_By" + to_wstring((_uint)(2));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TargetMrt.c_str(), m_DownScaledDepthStencil[0]));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_LumineceMask"))));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 6));


	m_pDeviceContext->RSSetViewports(1, &OldVp);
	FAILED_CHECK(m_pRenderTargetMgr->End(TargetMrt.c_str()));


	wstring TargetUpMrt = L"MRT_UpScaled_By" + to_wstring((_uint)(2));
	wstring TargetTex = L"Target_DownScaled_By" + to_wstring((_uint)(2));
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TargetUpMrt.c_str()));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TargetTex.c_str())));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 7));
	FAILED_CHECK(m_pRenderTargetMgr->End(TargetUpMrt.c_str()));




	FAILED_CHECK(m_pRenderTargetMgr->Begin(L"MRT_Defferred"));

	
	FAILED_CHECK(m_pShader->Set_Texture("g_MaskTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_UpScaled_By2"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_BluredTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_BluredDefferred"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_WorldPosTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_AvgLuminece"))));


	FAILED_CHECK(m_pShader->Set_RawValue("g_fBloomMul", &m_fBloomBrightnessMul, sizeof(_float)));
	

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 13));


	FAILED_CHECK(m_pRenderTargetMgr->End(L"MRT_Defferred"));
	FAILED_CHECK(Copy_DeferredToReference());


	return S_OK;
}

HRESULT CRenderer::Make_BluredDeffered(_float TexelSize)
{
	//Target_BluredDefferred
	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_BluredDefferred")));

	D3D11_VIEWPORT OldVp;
	FAILED_CHECK(Ready_DepthStencilBuffer(0, &OldVp));

	wstring TargetMrt = L"MRT_DownScaled_By" + to_wstring((_uint)(2));


	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &TexelSize, sizeof(_float)));

	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TargetMrt.c_str()));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TargetMrt.c_str(), m_DownScaledDepthStencil[0]));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Defferred"))));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 6));


	m_pDeviceContext->RSSetViewports(1, &OldVp);
	FAILED_CHECK(m_pRenderTargetMgr->End(TargetMrt.c_str()));


	wstring TargetTex = L"Target_DownScaled_By" + to_wstring((_uint)(2));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_BluredDefferred")));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TargetTex.c_str())));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 7));
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_BluredDefferred")));


	return S_OK;
}

HRESULT CRenderer::Make_BluredRenderTarget(const _tchar * szTag, _float TexelSize)
{
	
	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_BlurNCoppyed")));

	D3D11_VIEWPORT OldVp;
	FAILED_CHECK(Ready_DepthStencilBuffer(0, &OldVp));

	wstring TargetMrt = L"MRT_DownScaled_By" + to_wstring((_uint)(2));


	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &TexelSize, sizeof(_float)));

	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TargetMrt.c_str()));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TargetMrt.c_str(), m_DownScaledDepthStencil[0]));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(szTag)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 6));


	m_pDeviceContext->RSSetViewports(1, &OldVp);
	FAILED_CHECK(m_pRenderTargetMgr->End(TargetMrt.c_str()));


	wstring TargetTex = L"Target_DownScaled_By" + to_wstring((_uint)(2));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_BlurNCoppyed")));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TargetTex.c_str())));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 7));
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_BlurNCoppyed")));

	return S_OK;
}

HRESULT CRenderer::Copy_OrignNBlured_To_Defferd(const _tchar * szOriginTag, const _tchar * szBluredTag)
{

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Defferred")));


	FAILED_CHECK(m_pShader->Set_Texture("g_MaskTexture", m_pRenderTargetMgr->Get_SRV(szOriginTag)));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(szBluredTag)));


	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));


	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 25));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Defferred")));
	FAILED_CHECK(Copy_DeferredToReference());
	return S_OK;
}

HRESULT CRenderer::Render_DDFog()
{

	LIGHTDESC* pLightDesc = m_pLightMgr->Get_LightDesc(LIGHTDESC::TYPE_DIRECTIONAL, 0);
	if (!pLightDesc) return S_FALSE;

	_float3 vToSunDir = - XMVector3Normalize(XMVectorSet(m_vSunAtPoint.x, m_vSunAtPoint.y, m_vSunAtPoint.z, 1) - XMVectorSetW(pLightDesc->vVector.XMVector(), 1));


	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Defferred")));
	
	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);

	_float4x4		ViewMatrixInv, ProjMatrixInv;

	XMStoreFloat4x4(&ViewMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW))));
	XMStoreFloat4x4(&ProjMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ))));

	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrixInv", &ViewMatrixInv, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrixInv", &ProjMatrixInv, sizeof(_float4x4)));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));


	FAILED_CHECK(m_pShader->Set_RawValue("g_vCamPosition", &pPipeLineMgr->Get_TargetPostion_float4(PLV_CAMERA), sizeof(_float4)));
	
	FAILED_CHECK(m_pShader->Set_RawValue("FogColor", &m_vFogColor, sizeof(_float3)));
	FAILED_CHECK(m_pShader->Set_RawValue("FogHighlightColor", &m_vFogHighlightColor, sizeof(_float3)));
	FAILED_CHECK(m_pShader->Set_RawValue("FogStartDist", &m_fFogStartDist, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_RawValue("FogGlobalDensity", &m_fFogGlobalDensity, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_RawValue("FogHeightFalloff", &m_fFogHeightFalloff, sizeof(_float)));
	
	//float fHighlightColorFactor = -D3DXVec3Dot(g_Camera.GetWorldAhead(), &g_vDirLightDir) * 1.5f * abs(g_fTimeOfDay - 0.5f);

	FAILED_CHECK(m_pShader->Set_Texture("g_WorldPosTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_WorldPosition"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_MaskTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_GodRay"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_UpScaledTexture1", m_pRenderTargetMgr->Get_SRV(TEXT("Target_LenseFlare"))));
	
	
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 15));

	FAILED_CHECK(m_pRenderTargetMgr->End(L"MRT_Defferred"));
	FAILED_CHECK(Copy_DeferredToReference());




	return S_OK;
}

HRESULT CRenderer::Render_GodRay()
{


	LIGHTDESC* pLightDesc = m_pLightMgr->Get_LightDesc(LIGHTDESC::TYPE_DIRECTIONAL, 0);
	if (!pLightDesc) return S_FALSE;

	_Vector vSunDir =  XMVector3Normalize(XMVectorSet(m_vSunAtPoint.x, m_vSunAtPoint.y, m_vSunAtPoint.z, 1) - XMVectorSetW(pLightDesc->vVector.XMVector(), 1) );

	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);

	_Matrix vCamWorldMat = pPipeLineMgr->Get_Transform_Float4x4(PLM_VIEW).InverseXMatrix();
	_Vector vCamLook = XMVector3Normalize(vCamWorldMat.r[2]);


	const float dotCamSun = -XMVectorGetX(XMVector3Dot(XMVectorSetW(vCamLook, 0), XMVectorSetW(vSunDir, 0)));
	if (dotCamSun <= 0.0f) 
		return S_FALSE;


	_float3 vSunPos = pLightDesc->vVector.XMVector();
	//_float3 vSunPos = -200.0f * vSunDir;
	//_float3 vEyePos = vCamWorldMat.r[3];
	//vSunPos.x += vEyePos.x;
	//vSunPos.z += vEyePos.z;
	
	_Matrix mView = pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW);
	_Matrix mProj = pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ);

	_Matrix mViewProjection = mView * mProj;

	//_float3 vSunPosSS = XMVector3TransformCoord(XMVectorSetW(vSunPos.XMVector(), 1), mView);
	//
	//vSunPosSS = XMVector3TransformCoord(vSunPosSS.XMVector(),mProj);
	m_vSunPosSS  =	vSunPos.Multiply_Matrix_AsPosVector(mViewProjection);

	m_vSunPosSS.x = (m_vSunPosSS.x * 0.5f) + 0.5f;
	m_vSunPosSS.y = (m_vSunPosSS.y * -0.5f) + 0.5f;
	m_vSunPosSS.w = 1.;

	static const float fMaxSunDist = 2.f;
	float fMaxDist = max(abs(m_vSunPosSS.x), abs(m_vSunPosSS.y));

	//_float SunDist = _float3(vSunPosSS.x, vSunPosSS.y,0).Get_Lenth();
	//if (SunDist >= fMaxSunDist)
	//{
	//	return S_FALSE;
	//}
	if (fMaxDist >= fMaxSunDist)
	{
		return S_FALSE;
	}

	_float GodRayIntensive = m_fGodrayIntensity;
	// Attenuate the sun color based on how far the sun is from the view
	//if (fMaxDist >= 1.0f)
	//{
	//	//vSunColorAtt = vSunColorAtt.XMVector() * (fMaxSunDist - fMaxDist);
	//	GodRayIntensive *= (1 - fMaxDist) / fMaxSunDist + 1.f;
	//}
	GodRayIntensive *= fMaxSunDist - fMaxDist;


	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_ReferenceOclussion"), TEXT("Target_ReferenceOclussion")));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_Oclussion"), TEXT("Target_Oclussion")));



	D3D11_VIEWPORT		OldViewPortDesc;
	FAILED_CHECK(Ready_DepthStencilBuffer(0, &OldViewPortDesc));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_ReferenceOclussion"), m_DownScaledDepthStencil[0]));
	m_fTexleSize = 2.f;
	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &m_fTexleSize, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_DownScaledRefOclussion"))));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 6));
	m_pDeviceContext->RSSetViewports(1, &OldViewPortDesc);
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_ReferenceOclussion")));


	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Oclussion")));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceOclussion"))));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 7));
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Oclussion")));





	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_GodRay")));


	_float4x4		ViewMatrixInv, ProjMatrixInv;


	_float fGodRayNumDelta = 1.f / (m_fGodrayLength - 1.f); 

	FAILED_CHECK(m_pShader->Set_RawValue("SunPos", &m_vSunPosSS, sizeof(_float2)));
	FAILED_CHECK(m_pShader->Set_RawValue("InitDecay", &m_fInitDecay, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_RawValue("DistDecay", &m_fDistDecay, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_RawValue("RayColor", &m_vGodRayColor, sizeof(_float3)));
	FAILED_CHECK(m_pShader->Set_RawValue("MaxDeltaLen", &m_fMaxDeltaLen, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_fGodRayLength", &m_fGodrayLength, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_fGodRayNumDelta", &fGodRayNumDelta, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_SunSize", &m_SunSize, sizeof(_float)));

	

	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Oclussion"))));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 16));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_GodRay")));




	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Defferred")));

	FAILED_CHECK(m_pShader->Set_RawValue("g_fGodRayIntensity", &GodRayIntensive, sizeof(_float)));
	

	FAILED_CHECK(m_pShader->Set_Texture("g_MaskTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_GodRay"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));



	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 17));




	FAILED_CHECK(m_pRenderTargetMgr->End(L"MRT_Defferred"));
	FAILED_CHECK(Copy_DeferredToReference());




	return S_OK;
}

HRESULT CRenderer::Render_LesnFlare()
{



	LIGHTDESC* pLightDesc = m_pLightMgr->Get_LightDesc(LIGHTDESC::TYPE_DIRECTIONAL, 0);
	if (!pLightDesc) return S_FALSE;

	_Vector vSunDir = XMVector3Normalize(XMVectorSet(m_vSunAtPoint.x, m_vSunAtPoint.y, m_vSunAtPoint.z, 1) - XMVectorSetW(pLightDesc->vVector.XMVector(), 1));

	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);

	_Matrix vCamWorldMat = pPipeLineMgr->Get_Transform_Float4x4(PLM_VIEW).InverseXMatrix();
	_Vector vCamLook = XMVector3Normalize(vCamWorldMat.r[2]);

	const float dotCamSun = -XMVectorGetX(XMVector3Dot(XMVectorSetW(vCamLook, 0), XMVectorSetW(vSunDir, 0)));
	if (dotCamSun <= 0.0f)
		return S_FALSE;

	_float3 vSunPos = pLightDesc->vVector.XMVector();



	_Matrix mView = pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW);
	_Matrix mProj = pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ);

	_Matrix mViewProjection = mView * mProj;

	m_vSunPosSS = vSunPos.Multiply_Matrix_AsPosVector(mViewProjection);

	m_vSunPosSS.x = (m_vSunPosSS.x * 0.5f) + 0.5f;
	m_vSunPosSS.y = (m_vSunPosSS.y * -0.5f) + 0.5f;
	m_vSunPosSS.w = 1.f;


	static const float fMaxSunDist = 2.f;
	float fMaxDist = max(abs(m_vSunPosSS.x), abs(m_vSunPosSS.y));

	if (fMaxDist >= fMaxSunDist)
	{
		return S_FALSE;
	}



	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_LenseFlareNDefferd")));



	FAILED_CHECK(m_pShader->Set_RawValue("SunPos", &m_vSunPosSS, sizeof(_float2)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_LensfaleSupportSunSize", &m_LensfalreSupportSunSize, sizeof(_float)));


	FAILED_CHECK(m_pTexture->Bind_OnShader(m_pShader, "g_NoiseTexture", m_iLensefalreNoiseTexIndex));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 18));

	FAILED_CHECK(m_pRenderTargetMgr->End(L"MRT_LenseFlareNDefferd"));
	FAILED_CHECK(Copy_DeferredToReference());


	return S_OK;
}

HRESULT CRenderer::Render_MotionTrail()
{
	for (auto& pMotionTrailComponet : m_TrailList[TRAIL_MOTION])
	{
		if (pMotionTrailComponet != nullptr)
		{
			FAILED_CHECK(pMotionTrailComponet->Render());
		}
		Safe_Release(pMotionTrailComponet);
	}
	m_TrailList[TRAIL_MOTION].clear();

	return S_OK;
}

HRESULT CRenderer::Render_SwordTrail()
{
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_DefferredForNonLightObject")));
	for (auto& pSwordTrailComponet : m_TrailList[TRAIL_SWORD])
	{
		if (pSwordTrailComponet != nullptr)
		{
			FAILED_CHECK(pSwordTrailComponet->Render());
		}

		Safe_Release(pSwordTrailComponet);
	}
	m_TrailList[TRAIL_SWORD].clear();
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_DefferredForNonLightObject")));
	FAILED_CHECK(Copy_DeferredToReference());

	return S_OK;
}

HRESULT CRenderer::Render_EmissiveBlur()
{
	m_fTexleSize = 3.f;

	FAILED_CHECK(Make_BluredDeffered(m_fTexleSize));


	//Target_BluredDefferred
	//ILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EmissiveVBlur_N_DownScaling"), TEXT("Target_DownScaledEmissiveMask")));
	//ILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_EmissiveHBlur_N_UpScaling"), TEXT("Target_BluredEmissiveMask")));3

	D3D11_VIEWPORT OldVp;
	FAILED_CHECK(Ready_DepthStencilBuffer(0, &OldVp));

	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &m_fTexleSize, sizeof(_float)));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_EmissiveVBlur_N_DownScaling"), m_DownScaledDepthStencil[0]));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlEmissive"))));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 6));
	m_pDeviceContext->RSSetViewports(1, &OldVp);
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_EmissiveVBlur_N_DownScaling")));

	
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_EmissiveHBlur_N_UpScaling")));

	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &m_fTexleSize, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_DownScaledEmissiveMask"))));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 7));
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_EmissiveHBlur_N_UpScaling")));




	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DownSclaedMulMaskBluredEmissive"), TEXT("Target_DownScaledMulMaskBluredEmissive")));
	//FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_MulMaskBluredEmissive"), TEXT("Target_MulMaskBluredEmissive")));



	FAILED_CHECK(Ready_DepthStencilBuffer(0, &OldVp));
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_DownSclaedMulMaskBluredEmissive"), m_DownScaledDepthStencil[0]));
	
	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &m_fTexleSize, sizeof(_float)));

	FAILED_CHECK(m_pShader->Set_Texture("g_MaskTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlEmissive"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 12));
	m_pDeviceContext->RSSetViewports(1, &OldVp);
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_DownSclaedMulMaskBluredEmissive")));
	

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_MulMaskBluredEmissive")));

	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &m_fTexleSize, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_DownScaledMulMaskBluredEmissive"))));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 7));
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_MulMaskBluredEmissive")));






	FAILED_CHECK(m_pRenderTargetMgr->Begin(L"MRT_Defferred"));


	FAILED_CHECK(m_pShader->Set_Texture("g_MaskTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_BluredEmissiveMask"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_EmissiveTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlEmissive"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_BluredTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_BluredDefferred"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_UpScaledTexture1", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MulMaskBluredEmissive"))));
	
	

	
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 19));



	FAILED_CHECK(m_pRenderTargetMgr->End(L"MRT_Defferred"));
	FAILED_CHECK(Copy_DeferredToReference());





	return S_OK;
}

HRESULT CRenderer::Copy_NowWorld2OldWorld()
{
	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_OldWorld")));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_OldWorld")));

	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_WorldPosition"))));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 0));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_OldWorld")));


	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);


	m_OldViewMat = pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW);
	m_OldProjMat = pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ);
	return S_OK;
}

HRESULT CRenderer::Copy_RenderTarget(const _tchar * szCopyTag)
{
	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_UpScaled_By3")));
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_UpScaled_By3")));
	
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(szCopyTag)));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 0));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_UpScaled_By3")));
	return S_OK;
}

HRESULT CRenderer::Copy_BluredMtrlDiffuse(_float TexelSize)
{

	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_CopyMtrlDiffuse")));

	D3D11_VIEWPORT OldVp;
	FAILED_CHECK(Ready_DepthStencilBuffer(0, &OldVp));

	wstring TargetMrt = L"MRT_DownScaled_By" + to_wstring((_uint)(2));


	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &TexelSize, sizeof(_float)));

	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TargetMrt.c_str()));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TargetMrt.c_str(), m_DownScaledDepthStencil[0]));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 6));


	m_pDeviceContext->RSSetViewports(1, &OldVp);
	FAILED_CHECK(m_pRenderTargetMgr->End(TargetMrt.c_str()));


	wstring TargetTex = L"Target_DownScaled_By" + to_wstring((_uint)(2));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_CopyMtrlDiffuse")));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TargetTex.c_str())));
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 7));
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_CopyMtrlDiffuse")));






	return S_OK;
}

HRESULT CRenderer::Copy_CompletelyLastDeferredTexture()
{
	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_DeferredSceneChaging")));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_DeferredSceneChaging")));

	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Defferred"))));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 27));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_DeferredSceneChaging")));



	return S_OK;
}
HRESULT CRenderer::Copy_CompletelyLastDeferredTexToNowTex(_float fRate, ID3D11ShaderResourceView* pSRV)
{
	NULL_CHECK_RETURN(pSRV, E_FAIL);

	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_DeferredSceneChaging"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_SourTexture", pSRV));

	FAILED_CHECK(m_pShader->Set_RawValue("g_MixRate", &fRate, sizeof(_float)));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 28));


	return S_OK;
}
HRESULT CRenderer::Copy_MiniGameDeferredTexToNowTex(_float fRate, ID3D11ShaderResourceView * pminGameClearSRV, ID3D11ShaderResourceView * pBGSRV)
{
	NULL_CHECK_RETURN(pminGameClearSRV, E_FAIL);
	NULL_CHECK_RETURN(pBGSRV, E_FAIL);

	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", pminGameClearSRV));
	FAILED_CHECK(m_pShader->Set_Texture("g_SourTexture", pBGSRV));

	FAILED_CHECK(m_pShader->Set_RawValue("g_MixRate", &fRate, sizeof(_float)));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 29));
	return S_OK;
}
HRESULT CRenderer::Copy_LastDeferredTexture(_float fToonMaxIntensive)
{
	//TEXT("Target_DeferredSceneChaging")));
	//TEXT("Target_ToonDeferredSceneChaging")));

	FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_DeferredSceneChaging")));
	
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_DeferredSceneChaging")));

	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Defferred"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_DiffuseTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlDiffuse"))));
	FAILED_CHECK(m_pTexture->Bind_OnShader(m_pShader, "g_NoiseTexture", SceneChangeNoiseIndex));


	FAILED_CHECK(m_pShader->Set_RawValue("g_fToonMaxIntensive", &fToonMaxIntensive, sizeof(_float)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 24));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_DeferredSceneChaging")));



	return S_OK;
}
HRESULT CRenderer::Copy_LastDeferredToToonShadingTexture(_float fToonShadingIntensive, _bool bIsScecond)
{

	_float fToonValue = max(min(fToonShadingIntensive, 1.f), 0.000001f);
	
	if (bIsScecond)
	{
		FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_ToonDeferredSceneChaging2")));

		FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_ToonDeferredSceneChaging2")));


		FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_DeferredSceneChaging"))));
		FAILED_CHECK(m_pShader->Set_Texture("g_DiffuseTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlDiffuseSceneChaging"))));

		FAILED_CHECK(m_pShader->Set_RawValue("g_fToonShadingValue", &fToonValue, sizeof(_float)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

		FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 23));

		FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_ToonDeferredSceneChaging2")));
	}
	else
	{
		FAILED_CHECK(m_pRenderTargetMgr->Clear_SpecificMRT(TEXT("MRT_ToonDeferredSceneChaging")));

		FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_ToonDeferredSceneChaging")));


		FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_DeferredSceneChaging"))));
		FAILED_CHECK(m_pShader->Set_Texture("g_DiffuseTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlDiffuseSceneChaging"))));

		FAILED_CHECK(m_pShader->Set_RawValue("g_fToonShadingValue", &fToonValue, sizeof(_float)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
		FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

		FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 23));

		FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_ToonDeferredSceneChaging")));

	}


	

	return S_OK;
}

HRESULT CRenderer::Begin_RenderTarget(const _tchar * szTargetName)
{
	return m_pRenderTargetMgr->Begin(szTargetName);
}

HRESULT CRenderer::End_RenderTarget(const _tchar * szTargetName)
{
	return m_pRenderTargetMgr->End(szTargetName);
}

HRESULT CRenderer::Make_VelocityMap()
{
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_VelocityMap")));

	FAILED_CHECK(m_pShader->Set_Texture("g_WorldPosTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_WorldPosition"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_OldWorldPosTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_OldWorldPosition"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_NormalTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_MtrlNormal"))));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));


	
		

	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);

	_float4x4		NowViewMatrix, NowProjMatrix;

	_float4x4		OldViewMatrix = m_OldViewMat.TransposeXMatrix();
	_float4x4		OldProjMatrix = m_OldProjMat.TransposeXMatrix();

	XMStoreFloat4x4(&NowViewMatrix, XMMatrixTranspose(pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW)));
	XMStoreFloat4x4(&NowProjMatrix, XMMatrixTranspose(pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ)));


	FAILED_CHECK(m_pShader->Set_RawValue("g_matNowView", &NowViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_matNowProj", &NowProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pShader->Set_RawValue("g_matOldView", &OldViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_matOldProj", &OldProjMatrix, sizeof(_float4x4)));


	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 21));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_VelocityMap")));


	return S_OK;
}
 
HRESULT CRenderer::Render_CameraMotionBlur()
{
	FAILED_CHECK(Make_VelocityMap());
	//g_VelocityMapTexture


	FAILED_CHECK(m_pRenderTargetMgr->Begin(L"MRT_Defferred"));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));


	FAILED_CHECK(m_pShader->Set_Texture("g_VelocityMapTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_VelocityMap"))));
	//FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_VelocityMap"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));

	
	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 22));

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Defferred")));

	FAILED_CHECK(Copy_NowWorld2OldWorld());
	FAILED_CHECK(Copy_DeferredToReference());

	return S_OK;
}

HRESULT CRenderer::Render_DepthOfField()
{
	m_fTexleSize = m_fDofBlurIntensive;
	FAILED_CHECK(m_pShader->Set_RawValue("g_fTexelSize", &m_fTexleSize, sizeof(_float)));

	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));
	
	/* Multi GausianBlur
	//for (_uint i = 0;  i < 5;  i++)
	//{
	//	D3D11_VIEWPORT OldVp;
	//	FAILED_CHECK(Ready_DepthStencilBuffer(i, &OldVp));

	//	wstring TargetMrt = L"MRT_DownScaled_By" + to_wstring((_uint)(2 + i));

	//	FAILED_CHECK(m_pRenderTargetMgr->Begin(TargetMrt.c_str(), m_DownScaledDepthStencil[i]));

	//	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_Defferred"))));

	//	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 0));


	//	m_pDeviceContext->RSSetViewports(1, &OldVp);
	//	FAILED_CHECK(m_pRenderTargetMgr->End(TargetMrt.c_str()));


	//	wstring TargetUpMrt = L"MRT_UpScaled_By" + to_wstring((_uint)(2 + i));
	//	wstring TargetTex = L"Target_DownScaled_By" + to_wstring((_uint)(2 + i));
	//	FAILED_CHECK(m_pRenderTargetMgr->Begin(TargetUpMrt.c_str()));

	//	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TargetTex.c_str())));

	//	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 0));

	//	FAILED_CHECK(m_pRenderTargetMgr->End(TargetUpMrt.c_str()));
	//}

	//FAILED_CHECK(m_pRenderTargetMgr->Begin(L"MRT_Defferred"));

	//FAILED_CHECK(m_pShader->Set_Texture("g_UpScaledTexture1", m_pRenderTargetMgr->Get_SRV(TEXT("Target_UpScaled_By2"))));
	//FAILED_CHECK(m_pShader->Set_Texture("g_UpScaledTexture2", m_pRenderTargetMgr->Get_SRV(TEXT("Target_UpScaled_By3"))));
	//FAILED_CHECK(m_pShader->Set_Texture("g_UpScaledTexture3", m_pRenderTargetMgr->Get_SRV(TEXT("Target_UpScaled_By4"))));
	//FAILED_CHECK(m_pShader->Set_Texture("g_UpScaledTexture4", m_pRenderTargetMgr->Get_SRV(TEXT("Target_UpScaled_By5"))));
	//FAILED_CHECK(m_pShader->Set_Texture("g_UpScaledTexture5", m_pRenderTargetMgr->Get_SRV(TEXT("Target_UpScaled_By6"))));

	//FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 5));


	//FAILED_CHECK(m_pRenderTargetMgr->End(L"MRT_Defferred"));

	*/

	FAILED_CHECK(Make_BluredDeffered(m_fTexleSize));


	FAILED_CHECK(m_pRenderTargetMgr->Begin(L"MRT_Defferred"));
	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);

	_float4x4		ViewMatrixInv, ProjMatrixInv;

	XMStoreFloat4x4(&ViewMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW))));
	XMStoreFloat4x4(&ProjMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ))));

	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrixInv", &ViewMatrixInv, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrixInv", &ProjMatrixInv, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_vDofTargetPosition", &pPipeLineMgr->Get_TargetPostion_float4(PLV_PLAYER), sizeof(_float3)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_fDofTargetLength", &m_fDofLength, sizeof(_float)));

	
	
	FAILED_CHECK(m_pShader->Set_Texture("g_UpScaledTexture1", m_pRenderTargetMgr->Get_SRV(TEXT("Target_BluredDefferred"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_ReferenceDefferred"))));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 9));


	FAILED_CHECK(m_pRenderTargetMgr->End(L"MRT_Defferred"));
	FAILED_CHECK(Copy_DeferredToReference());

	return S_OK;
}

HRESULT CRenderer::Render_ShadowMap()
{
	m_pDeviceContext->ClearDepthStencilView(m_LightDepthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);


	_uint		iNumViewports = 1;
	D3D11_VIEWPORT		OldViewPortDesc;
	m_pDeviceContext->RSGetViewports(&iNumViewports, &OldViewPortDesc);

	D3D11_VIEWPORT			ViewPortDesc;
	ZeroMemory(&ViewPortDesc, sizeof(D3D11_VIEWPORT));
	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = (_float)OldViewPortDesc.Width * ShadowMapQuality;
	ViewPortDesc.Height = (_float)OldViewPortDesc.Height * ShadowMapQuality;
	ViewPortDesc.MinDepth = 0.f;
	ViewPortDesc.MaxDepth = 1.f;




	m_pDeviceContext->RSSetViewports(iNumViewports, &ViewPortDesc);
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Shadow"), m_LightDepthStencil));

	LIGHTDESC* pLightDesc = m_pLightMgr->Get_LightDesc(LIGHTDESC::TYPE_DIRECTIONAL, 0);


	if (pLightDesc)
	{
		_Matrix LightView = XMMatrixLookAtLH(XMVectorSetW(pLightDesc->vVector.XMVector(), 1), XMVectorSet(m_vSunAtPoint.x, m_vSunAtPoint.y, m_vSunAtPoint.z, 1), XMVectorSet(0, 1, 0, 0));
		GetSingle(CPipeLineMgr)->Set_Transform(PLM_LIGHTVIEW, LightView);
		m_LightWVPmat.ViewMatrix = XMMatrixTranspose(LightView);
	}


	FAILED_CHECK(Render_ShadowGroup());


	m_pDeviceContext->RSSetViewports(iNumViewports, &OldViewPortDesc);
	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Shadow")));


	return S_OK;
}

HRESULT CRenderer::Render_ShadowGroup()
{
	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);

	_Vector vCamWorldPosition = pPipeLineMgr->Get_Transform_Float4x4(PLM_VIEW).InverseXMatrix().r[3];


	//SHADOW_ANIMMODEL, SHADOW_ANIMMODEL_ATTACHED, SHADOW_NONANIMMODEL, SHADOW_NONANIMMODEL_ATTACHED, SHADOW_TERRAIN, SHADOW_END

	if (m_PostProcessingOn[POSTPROCESSING_SHADOW])
	{


#pragma region SHADOW_ANIMMODEL

		m_bShadowLightMatBindedChecker = false;
		for (auto& ShadowDesc : m_ShadowObjectList[SHADOW_ANIMMODEL])
		{
			if (!ShadowDesc.pGameObject->Get_IsOwerDead() )
			//	&& XMVectorGetX(XMVector3Length(ShadowDesc.pTransform->Get_MatrixState(CTransform::STATE_POS) - vCamWorldPosition)) < CAMERAFAR )
			{
				
				if (!m_bShadowLightMatBindedChecker)
				{
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightViewMatrix", &m_LightWVPmat.ViewMatrix, sizeof(_float4x4)));
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightProjMatrix", &m_LightWVPmat.ProjMatrix, sizeof(_float4x4)));
					m_bShadowLightMatBindedChecker = true;
				}
				FAILED_CHECK(ShadowDesc.pTransform->Bind_OnShader(ShadowDesc.pShader, "g_WorldMatrix"));

				FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_fOclussionObject", &ShadowDesc.fIsOcllusion, sizeof(_float)));

				if (ShadowDesc.pDissolve == nullptr)
				{
					_uint NumMaterial = ShadowDesc.pModel->Get_NumMaterial();
					for (_uint i = 0; i < NumMaterial; i++)
					{
						FAILED_CHECK(ShadowDesc.pModel->Render(ShadowDesc.pShader, 0, i, "g_BoneMatrices"));
					}
				}
				else
				{
					FAILED_CHECK(ShadowDesc.pDissolve->Render_Shadow(0));
				}
			
			}
			Safe_Release(ShadowDesc.pGameObject);
		}
		m_ShadowObjectList[SHADOW_ANIMMODEL].clear();

#pragma endregion


#pragma region SHADOW_ANIMMODEL_ATTACHED

		m_bShadowLightMatBindedChecker = false;
		for (auto& ShadowDesc : m_ShadowObjectList[SHADOW_ANIMMODEL_ATTACHED])
		{
			if (!ShadowDesc.pGameObject->Get_IsOwerDead())
				//	&& XMVectorGetX(XMVector3Length(ShadowDesc.pTransform->Get_MatrixState(CTransform::STATE_POS) - vCamWorldPosition)) < CAMERAFAR )
			{
				if (!m_bShadowLightMatBindedChecker)
				{
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightViewMatrix", &m_LightWVPmat.ViewMatrix, sizeof(_float4x4)));
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightProjMatrix", &m_LightWVPmat.ProjMatrix, sizeof(_float4x4)));
					m_bShadowLightMatBindedChecker = true;
				}
				FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_fOclussionObject", &ShadowDesc.fIsOcllusion, sizeof(_float)));
				FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_AttechMatrix", &ShadowDesc.AttacehdMatrix, sizeof(_float4x4)));
				FAILED_CHECK(ShadowDesc.pTransform->Bind_OnShader(ShadowDesc.pShader, "g_WorldMatrix"));


				if (ShadowDesc.pDissolve == nullptr)
				{

					_uint NumMaterial = ShadowDesc.pModel->Get_NumMaterial();

					for (_uint i = 0; i < NumMaterial; i++)
					{
						FAILED_CHECK(ShadowDesc.pModel->Render(ShadowDesc.pShader, 1, i, "g_BoneMatrices"));
					}
				}
				else
				{
					FAILED_CHECK(ShadowDesc.pDissolve->Render_Shadow(1));
				}


			}
			Safe_Release(ShadowDesc.pGameObject);

		}
		m_ShadowObjectList[SHADOW_ANIMMODEL_ATTACHED].clear();


#pragma endregion


#pragma region SHADOW_NONANIMMODEL

		m_bShadowLightMatBindedChecker = false;
		for (auto& ShadowDesc : m_ShadowObjectList[SHADOW_NONANIMMODEL])
		{
			if (!ShadowDesc.pGameObject->Get_IsOwerDead())
				//	&& XMVectorGetX(XMVector3Length(ShadowDesc.pTransform->Get_MatrixState(CTransform::STATE_POS) - vCamWorldPosition)) < CAMERAFAR )
			{
				if (!m_bShadowLightMatBindedChecker)
				{
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightViewMatrix", &m_LightWVPmat.ViewMatrix, sizeof(_float4x4)));
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightProjMatrix", &m_LightWVPmat.ProjMatrix, sizeof(_float4x4)));
					m_bShadowLightMatBindedChecker = true;
				}
				FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_fOclussionObject", &ShadowDesc.fIsOcllusion, sizeof(_float)));
				FAILED_CHECK(ShadowDesc.pTransform->Bind_OnShader(ShadowDesc.pShader, "g_WorldMatrix"));



				if (ShadowDesc.pDissolve == nullptr)
				{

					_uint NumMaterial = ShadowDesc.pModel->Get_NumMaterial();

					for (_uint i = 0; i < NumMaterial; i++)
					{
						FAILED_CHECK(ShadowDesc.pModel->Render(ShadowDesc.pShader, 0, i));
					}
				}
				else
				{
					FAILED_CHECK(ShadowDesc.pDissolve->Render_Shadow(0));
				}



			}
			Safe_Release(ShadowDesc.pGameObject);
		}
		m_ShadowObjectList[SHADOW_NONANIMMODEL].clear();


#pragma endregion

#pragma region SHADOW_NONANIMMODEL_ATTACHED

		m_bShadowLightMatBindedChecker = false;
		for (auto& ShadowDesc : m_ShadowObjectList[SHADOW_NONANIMMODEL_ATTACHED])
		{
			if (!ShadowDesc.pGameObject->Get_IsOwerDead())
				//	&& XMVectorGetX(XMVector3Length(ShadowDesc.pTransform->Get_MatrixState(CTransform::STATE_POS) - vCamWorldPosition)) < CAMERAFAR )
			{
				if (!m_bShadowLightMatBindedChecker)
				{
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightViewMatrix", &m_LightWVPmat.ViewMatrix, sizeof(_float4x4)));
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightProjMatrix", &m_LightWVPmat.ProjMatrix, sizeof(_float4x4)));
					m_bShadowLightMatBindedChecker = true;
				}
				FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_fOclussionObject", &ShadowDesc.fIsOcllusion, sizeof(_float)));
				FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_AttechMatrix", &ShadowDesc.AttacehdMatrix, sizeof(_float4x4)));
				FAILED_CHECK(ShadowDesc.pTransform->Bind_OnShader(ShadowDesc.pShader, "g_WorldMatrix"));


				if (ShadowDesc.pDissolve == nullptr)
				{
					_uint NumMaterial = ShadowDesc.pModel->Get_NumMaterial();

					for (_uint i = 0; i < NumMaterial; i++)
					{
						FAILED_CHECK(ShadowDesc.pModel->Render(ShadowDesc.pShader, 1, i));
					}
				}
				else
				{
					FAILED_CHECK(ShadowDesc.pDissolve->Render_Shadow(1));
				}


			}
			Safe_Release(ShadowDesc.pGameObject);

		}
		m_ShadowObjectList[SHADOW_NONANIMMODEL_ATTACHED].clear();

#pragma endregion


#pragma region SHADOW_TERRAIN

		m_bShadowLightMatBindedChecker = false;
		for (auto& ShadowDesc : m_ShadowObjectList[SHADOW_TERRAIN])
		{
			//if (!ShadowDesc.pGameObject->Get_IsOwerDead())
			//	//	&& XMVectorGetX(XMVector3Length(ShadowDesc.pTransform->Get_MatrixState(CTransform::STATE_POS) - vCamWorldPosition)) < CAMERAFAR )
			//{
			//	if (!m_bShadowLightMatBindedChecker)
			//	{
			//		FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightViewMatrix", &m_LightWVPmat.ViewMatrix, sizeof(_float4x4)));
			//		FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightProjMatrix", &m_LightWVPmat.ProjMatrix, sizeof(_float4x4)));
			//		m_bShadowLightMatBindedChecker = true;
			//	}

			//	FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_fOclussionObject", &ShadowDesc.fIsOcllusion, sizeof(_float)));
			//	CVIBuffer* pVIBuffer = (CVIBuffer*)ShadowDesc.pGameObject->Get_Component(L"Com_VIBuffer");
			//	NULL_CHECK_RETURN(pVIBuffer, E_FAIL);

			//	FAILED_CHECK(ShadowDesc.pTransform->Bind_OnShader(ShadowDesc.pShader, "g_WorldMatrix"));
			//	FAILED_CHECK(pVIBuffer->Render(ShadowDesc.pShader, 0));
			//}
			Safe_Release(ShadowDesc.pGameObject);
		}
		m_ShadowObjectList[SHADOW_TERRAIN].clear();

#pragma endregion 


#pragma region SHADOW_INSTANIMMODEL

		m_bShadowLightMatBindedChecker = false;
		for (auto& ShadowDesc : m_InstanceShadowList[INSTSHADOW_ANIMINSTANCE])
		{
			if (!ShadowDesc.pGameObject->Get_IsOwerDead())
			{
				if (!m_bShadowLightMatBindedChecker)
				{
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightViewMatrix", &m_LightWVPmat.ViewMatrix, sizeof(_float4x4)));
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightProjMatrix", &m_LightWVPmat.ProjMatrix, sizeof(_float4x4)));
					m_bShadowLightMatBindedChecker = true;
				}

				FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_fOclussionObject", &ShadowDesc.fIsOcllusion, sizeof(_float)));


				if (!ShadowDesc.pvecTransformfloat4x4)
				{
					FAILED_CHECK(ShadowDesc.pModelInstance->Render(ShadowDesc.pShader, 0, ShadowDesc.pvecTransform,0,nullptr,nullptr, ShadowDesc.pvecTimer));

				}
				else
				{
					FAILED_CHECK(ShadowDesc.pModelInstance->Render_By_float4x4(ShadowDesc.pShader, 0,
						ShadowDesc.pvecTransformfloat4x4, 0, nullptr, nullptr, ShadowDesc.pvecTimer));

				}
			}

			Safe_Release(ShadowDesc.pGameObject);
		}
		m_InstanceShadowList[INSTSHADOW_ANIMINSTANCE].clear();

#pragma endregion

#pragma region SHADOW_INSTNONANIMMODEL

		m_bShadowLightMatBindedChecker = false;
		for (auto& ShadowDesc : m_InstanceShadowList[INSTSHADOW_NONANIMINSTANCE])
		{
			if (!ShadowDesc.pGameObject->Get_IsOwerDead())
			{
				if (!m_bShadowLightMatBindedChecker)
				{
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightViewMatrix", &m_LightWVPmat.ViewMatrix, sizeof(_float4x4)));
					FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_LightProjMatrix", &m_LightWVPmat.ProjMatrix, sizeof(_float4x4)));
					m_bShadowLightMatBindedChecker = true;
				}

				FAILED_CHECK(ShadowDesc.pShader->Set_RawValue("g_fOclussionObject", &ShadowDesc.fIsOcllusion, sizeof(_float)));

				if (!ShadowDesc.pvecTransformfloat4x4)
				{
					FAILED_CHECK(ShadowDesc.pModelInstance->Render(ShadowDesc.pShader, 0, ShadowDesc.pvecTransform, 0,
						nullptr, nullptr, ShadowDesc.pvecTimer));

				}
				else
				{
					FAILED_CHECK(ShadowDesc.pModelInstance->Render_By_float4x4(ShadowDesc.pShader, 0,
						ShadowDesc.pvecTransformfloat4x4, 0, nullptr, nullptr, ShadowDesc.pvecTimer));

				}

			}
			Safe_Release(ShadowDesc.pGameObject);
		}
		m_InstanceShadowList[INSTSHADOW_NONANIMINSTANCE].clear();

#pragma endregion

	}
	else
	{
		for (_uint i = 0 ; i< SHADOW_END; i++)
		{
			for (auto& ShadowDesc : m_ShadowObjectList[i])
			{
				Safe_Release(ShadowDesc.pGameObject);
			}
			m_ShadowObjectList[i].clear();
		}

		for (_uint i = 0; i < INSTSHADOW_END; i++)
		{
			for (auto& ShadowDesc : m_InstanceShadowList[i])
			{
				Safe_Release(ShadowDesc.pGameObject);
			}
			m_InstanceShadowList[i].clear();
		}
	}


	return S_OK;
}

HRESULT CRenderer::Apply_OccludedMask()
{

	//Target_UpScaled_By3
	FAILED_CHECK(Copy_RenderTarget(TEXT("Target_Depth")));

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Material")));
	//Target_UpScaled_By3


	FAILED_CHECK(m_pShader->Set_Texture("g_TargetTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_OccludedMaskMap"))));
	FAILED_CHECK(m_pShader->Set_Texture("g_DepthTexture", m_pRenderTargetMgr->Get_SRV(TEXT("Target_UpScaled_By3"))));

	CPipeLineMgr*		pPipeLineMgr = GetSingle(CPipeLineMgr);
	_float4x4		ViewMatrixInv, ProjMatrixInv;

	XMStoreFloat4x4(&ViewMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_VIEW))));
	XMStoreFloat4x4(&ProjMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLineMgr->Get_Transform_Matrix(PLM_PROJ))));

	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrixInv", &ViewMatrixInv, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrixInv", &ProjMatrixInv, sizeof(_float4x4)));

	FAILED_CHECK(m_pShader->Set_RawValue("g_vOcdMaskColor", &m_vOcdMaskColor, sizeof(_float4)));
	
	FAILED_CHECK(m_pShader->Set_RawValue("g_WorldMatrix", &m_WVPmat.WorldMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ViewMatrix", &m_WVPmat.ViewMatrix, sizeof(_float4x4)));
	FAILED_CHECK(m_pShader->Set_RawValue("g_ProjMatrix", &m_WVPmat.ProjMatrix, sizeof(_float4x4)));

	FAILED_CHECK(m_pVIBuffer->Render(m_pShader, 26));


	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Material")));
	return S_OK;
}

HRESULT CRenderer::Add_DebugRenderTarget(const _tchar * szTargetTag, _float fX, _float fY, _float fCX, _float fCY)
{
#ifdef _DEBUG
	FAILED_CHECK(m_pRenderTargetMgr->Ready_DebugDesc(szTargetTag, fX, fY, fCX, fCY));
#endif // _DEBUG

	FAILED_CHECK(m_pRenderTargetMgr->Add_MRT(TEXT("MRT_DebugRender"), szTargetTag));

	m_szDebugRenderTargetList.push_back(szTargetTag);

	return S_OK;
}

HRESULT CRenderer::Ready_For_Update(_double fDelataTimme)
{
	m_vSunPosSS = _float4(0);

	return S_OK;
}

void CRenderer::OnOff_PostPorcessing(POSTPROCESSINGID eID)
{
	m_PostProcessingOn[eID] = !m_PostProcessingOn[eID];

	if (eID == POSTPROCESSING_CAMMOTIONBLUR && m_PostProcessingOn[eID])
	{
		m_OldViewMat = GetSingle(CPipeLineMgr)->Get_Transform_Matrix(PLM_VIEW);
		m_OldProjMat = GetSingle(CPipeLineMgr)->Get_Transform_Matrix(PLM_PROJ);
	}
}

void CRenderer::OnOff_PostPorcessing_byParameter(POSTPROCESSINGID eID, _bool bBool)
{
	 m_PostProcessingOn[eID] = bBool;

	if (eID == POSTPROCESSING_CAMMOTIONBLUR && m_PostProcessingOn[eID])
	{
		m_OldViewMat = GetSingle(CPipeLineMgr)->Get_Transform_Matrix(PLM_VIEW);
		m_OldProjMat = GetSingle(CPipeLineMgr)->Get_Transform_Matrix(PLM_PROJ);
	}

}

HRESULT CRenderer::Render_NonBlend_NoLight()
{
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_DefferredForNonLightObject")));

	for (auto& RenderObject : m_RenderObjectList[RENDER_NONBLEND_NOLIGHT])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}

	m_RenderObjectList[RENDER_NONBLEND_NOLIGHT].clear();


	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_DefferredForNonLightObject")));
	FAILED_CHECK(Copy_DeferredToReference());

	return S_OK;
}

HRESULT CRenderer::Render_Blend()
{

	//FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Defferred")));

	m_RenderObjectList[RENDER_BLEND].sort([](CGameObject* pSour, CGameObject* pDest)->_bool
	{
		return pSour->Get_RenderSortValue() > pDest->Get_RenderSortValue();
	});

	for (auto& RenderObject : m_RenderObjectList[RENDER_BLEND])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_BLEND].clear();

	//FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Defferred")));
	//FAILED_CHECK(Copy_DeferredToReference());


	//FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Defferred")));

	m_RenderObjectList[RENDER_SUBBLEND].sort([](CGameObject* pSour, CGameObject* pDest)->_bool
	{
		return pSour->Get_RenderSortValue() > pDest->Get_RenderSortValue();
	});

	for (auto& RenderObject : m_RenderObjectList[RENDER_SUBBLEND])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_SUBBLEND].clear();

	//FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Defferred")));
	//FAILED_CHECK(Copy_DeferredToReference());

	return S_OK;
}

HRESULT CRenderer::Render_AfterObj()
{
	//FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Defferred")));

	for (auto& RenderObject : m_RenderObjectList[RENDER_AFTERALLOBJ])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_AFTERALLOBJ].clear();

	//FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Defferred")));
	//FAILED_CHECK(Copy_DeferredToReference());

	return S_OK;
}

HRESULT CRenderer::Render_DistortionObject()
{

	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_DistortionObject")));

	for (auto& pSwordTrailComponet : m_TrailList[TRAIL_SWORD_DISTORT])
	{
		if (pSwordTrailComponet != nullptr)
		{
			FAILED_CHECK(pSwordTrailComponet->Render());
		}

		Safe_Release(pSwordTrailComponet);
	}
	m_TrailList[TRAIL_SWORD_DISTORT].clear();


	for (auto& RenderObject : m_RenderObjectList[RENDER_DISTORTION])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_DISTORTION].clear();

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_DistortionObject")));
	FAILED_CHECK(Copy_DeferredToReference());
	

	return S_OK;
}

HRESULT CRenderer::Render_SubDistortionObject()
{
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_SubDistortionObject")));
	

	for (auto& RenderObject : m_RenderObjectList[RENDER_SUBDISTORTION])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_SUBDISTORTION].clear();

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_SubDistortionObject")));
	FAILED_CHECK(Copy_DeferredToReference());
	
	return S_OK;
}

HRESULT CRenderer::Render_EffectObj()
{

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Material")));
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Effect")));

	for (auto& RenderObject : m_RenderObjectList[RENDER_EFFECT])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_EFFECT].clear();

	FAILED_CHECK(m_pRenderTargetMgr->End(TEXT("MRT_Effect")));
	FAILED_CHECK(m_pRenderTargetMgr->Begin(TEXT("MRT_Material")));



	return S_OK;
}

HRESULT CRenderer::Render_EnvMappedObj()
{
	for (auto& RenderObject : m_RenderObjectList[RENDER_ENVMAPPED])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_ENVMAPPED].clear();

	return S_OK;
}



HRESULT CRenderer::Render_ScreenEffect()
{

	m_RenderObjectList[RENDER_SCREENEFFECT].sort([](CGameObject* pSour, CGameObject* pDest)->_bool
	{
		return pSour->Get_RenderSortValue() > pDest->Get_RenderSortValue();
	});
	for (auto& RenderObject : m_RenderObjectList[RENDER_SCREENEFFECT])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_SCREENEFFECT].clear();


	return S_OK;
}

HRESULT CRenderer::Render_JJBMiniGame()
{
	FAILED_CHECK(m_pRenderTargetMgr->Begin(L"MRT_Defferred"));


	m_RenderObjectList[RENDER_JJBMINIGAME].sort([](CGameObject* pSour, CGameObject* pDest)->_bool
	{
		return pSour->Get_RenderSortValue() > pDest->Get_RenderSortValue();
	});
	for (auto& RenderObject : m_RenderObjectList[RENDER_JJBMINIGAME])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_JJBMINIGAME].clear();

	FAILED_CHECK(m_pRenderTargetMgr->End(L"MRT_Defferred"));
	FAILED_CHECK(Copy_DeferredToReference());
	return S_OK;
}

HRESULT CRenderer::Render_UI()
{

	m_RenderObjectList[RENDER_UI].sort([](CGameObject* pSour, CGameObject* pDest)->_bool
	{
		return pSour->Get_RenderSortValue() > pDest->Get_RenderSortValue();
	});
	for (auto& RenderObject : m_RenderObjectList[RENDER_UI])
	{
		if (RenderObject != nullptr)
		{
			FAILED_CHECK(RenderObject->Render());
		}
		Safe_Release(RenderObject);
	}
	m_RenderObjectList[RENDER_UI].clear();


	return S_OK;
}

PPDDESC CRenderer::Get_PostProcessingData()
{
	PPDDESC tResult;


	memcpy(tResult.bPostProcessingArr, m_PostProcessingOn, sizeof(_bool)*POSTPROCESSING_END);

	LIGHTDESC* pLightDesc = m_pLightMgr->Get_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0);
	tResult.SunPos = pLightDesc->vVector;
	tResult.SunAt = m_vSunAtPoint;

	tResult.vDiffuse = pLightDesc->vDiffuse;
	tResult.vAmbient = pLightDesc->vAmbient;
	tResult.vSpecular = pLightDesc->vSpecular;

	tResult.fShadowIntensive = m_fShadowIntensive;

	tResult.fSunSize = m_SunSize;
	tResult.fGodrayLength = m_fGodrayLength;
	tResult.fGodrayIntensity = m_fGodrayIntensity;
	tResult.fStartDecay = m_fInitDecay ;
	tResult.fDistDecay = m_fDistDecay;
	tResult.fMaxDeltaLen = m_fMaxDeltaLen ;


	tResult.fLensfalreSupportSunSize = m_LensfalreSupportSunSize ;
	tResult.fLensefalreNoiseTexIndex= (_float)m_iLensefalreNoiseTexIndex ;

	tResult.fBloomOverLuminceValue = m_fOverLuminece;
	tResult.fBloomBrightnessMul = m_fBloomBrightnessMul;

	tResult.fDofLength = m_fDofLength;
	tResult.fDofBlurIntensive = m_fDofBlurIntensive;

	tResult.vFogColor		=	m_vFogColor ;
	tResult.vFogHighlightColor = m_vFogHighlightColor;
	tResult.fFogStartDist = m_fFogStartDist ;
	tResult.fFogGlobalDensity = m_fFogGlobalDensity ;
	tResult.fFogHeightFalloff	= m_fFogHeightFalloff ;
	

	return tResult;
}

void CRenderer::Set_PostProcessingData(PPDDESC & tDesc)
{

	memcpy(m_PostProcessingOn, tDesc.bPostProcessingArr, sizeof(_bool)*POSTPROCESSING_END);

	LIGHTDESC* pLightDesc = m_pLightMgr->Get_LightDesc(tagLightDesc::TYPE_DIRECTIONAL, 0);

	pLightDesc->vVector = tDesc.SunPos;
	m_vSunAtPoint = tDesc.SunAt;

	pLightDesc->vDiffuse = tDesc.vDiffuse;
	pLightDesc->vAmbient = tDesc.vAmbient;
	pLightDesc->vSpecular = tDesc.vSpecular;

	m_fShadowIntensive = tDesc.fShadowIntensive;

	m_SunSize = tDesc.fSunSize;
	m_fGodrayLength = tDesc.fGodrayLength;
	m_fGodrayIntensity = tDesc.fGodrayIntensity;
	m_fInitDecay = tDesc.fStartDecay;
	m_fDistDecay = tDesc.fDistDecay;
	m_fMaxDeltaLen = tDesc.fMaxDeltaLen;

	m_LensfalreSupportSunSize = tDesc.fLensfalreSupportSunSize;
	m_iLensefalreNoiseTexIndex = (_uint)tDesc.fLensefalreNoiseTexIndex;

	m_fOverLuminece = tDesc.fBloomOverLuminceValue;
	m_fBloomBrightnessMul = tDesc.fBloomBrightnessMul;

	m_fDofLength = tDesc.fDofLength;
	m_fDofBlurIntensive = tDesc.fDofBlurIntensive;

	m_vFogColor = tDesc.vFogColor;
	m_vFogHighlightColor = tDesc.vFogHighlightColor;
	m_fFogStartDist = tDesc.fFogStartDist;
	m_fFogGlobalDensity = tDesc.fFogGlobalDensity;
	m_fFogHeightFalloff = tDesc.fFogHeightFalloff;



}

#ifdef _DEBUG

HRESULT CRenderer::Render_Debug()
{
	FAILED_CHECK(m_pShader->Apply(20));

	for (auto& pComponent : m_DebugObjectList)
	{
		if (nullptr != pComponent)
			pComponent->Render();

		Safe_Release(pComponent);
	}

	m_DebugObjectList.clear();

	return S_OK;
}
#endif // _DEBUG

CRenderer * CRenderer::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CRenderer* pInstance = new CRenderer(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg))) 
	{
		MSGBOX("Failed to Creating CRenderer");
		Safe_Release(pInstance);
	}


	return pInstance;
}

CComponent * CRenderer::Clone(void * pArg)
{
	this->AddRef();
	return this;
}

void CRenderer::Free()
{
	__super::Free();

	for (_uint i = 0; i < 5; i++)
	{
		Safe_Release(m_DownScaledDepthStencil[i]);
	}
	Safe_Release(m_LightDepthStencil);
	Safe_Release(m_AvgLumiDepthStencil);
	
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pShader);
	Safe_Release(m_pTexture);
	
	Safe_Release(m_pRenderTargetMgr);
	Safe_Release(m_pLightMgr);
	Safe_Release(m_pGraphicDevice);

	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for (auto& RenderObject : m_RenderObjectList[i])
		{
			Safe_Release(RenderObject);
		}
		m_RenderObjectList[i].clear();
	}

	for (_uint i = 0; i < SHADOW_END; i++)
	{
		for (auto& ShadowDesc : m_ShadowObjectList[i])
		{
			Safe_Release(ShadowDesc.pGameObject);
		}
		m_ShadowObjectList[i].clear();
	}
	for (_uint i = 0; i < INSTSHADOW_END; i++)
	{
		for (auto& ShadowDesc : m_InstanceShadowList[i])
		{
			Safe_Release(ShadowDesc.pGameObject);
		}
		m_InstanceShadowList[i].clear();
	}



	for (_uint i = 0; i < TRAIL_END; ++i)
	{
		for (auto& RenderObject : m_TrailList[i])
		{
			Safe_Release(RenderObject);
		}
		m_TrailList[i].clear();
	}


	for (auto& DebugObject : m_DebugObjectList)
	{
		Safe_Release(DebugObject);
	}
	m_DebugObjectList.clear();

}
