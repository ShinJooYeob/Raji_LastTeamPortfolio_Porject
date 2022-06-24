#include "..\public\Graphic_Device.h"

IMPLEMENT_SINGLETON(CGraphic_Device)

CGraphic_Device::CGraphic_Device()
	: m_pDevice(nullptr)
	, m_pDeviceContext(nullptr)
{		
}

HRESULT CGraphic_Device::Initialize_Graphic_Device(HWND hWnd, WINMODE WinMode, _uint iWinCX, _uint iWinCY, ID3D11Device** ppDeviceOut, ID3D11DeviceContext** ppDeviceContextOut,
	ID3D11RenderTargetView** ppBackBufferRTV, ID3D11DepthStencilView** ppDepthStencilView, IDXGISwapChain**	ppSwapChain)
{
	_uint		iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL			FeatureLV;

	/* �׷��� ��ġ�� �ʱ�ȭ�Ѵ�. */
	FAILED_CHECK(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, iFlag, nullptr, 0, D3D11_SDK_VERSION, &m_pDevice, &FeatureLV, &m_pDeviceContext));

	/* ���ۿ� ������ �����Ͽ� ����ü�� ��ü�� �����Ѵ�. : ����۸� �����. */
	FAILED_CHECK(Ready_SwapChain(hWnd, WinMode, iWinCX, iWinCY));

	/* IDirect3DTexture9 */
	/* ID3D11Texture2D */
	/* ID3D11ShaderResourceView */
	/* ID3D11RenderTargetView */
	FAILED_CHECK(Ready_BackBufferRenderTargetView());

	FAILED_CHECK(Ready_DepthStencilRenderTargetView(iWinCX, iWinCY));

	/* ��ġ�� ���ε��س��� ����Ÿ�ٵ�� �������ٽǺ並 �����Ѵ�. */
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBufferRTV, m_pDepthStencilView);		
	
	D3D11_VIEWPORT			ViewPortDesc;
	ZeroMemory(&ViewPortDesc, sizeof(D3D11_VIEWPORT));
	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = (_float)iWinCX;
	ViewPortDesc.Height = (_float)iWinCY;
	ViewPortDesc.MinDepth = 0.f;
	ViewPortDesc.MaxDepth = 1.f;

	m_pDeviceContext->RSSetViewports(1, &ViewPortDesc);

	*ppDeviceOut = m_pDevice;
	*ppDeviceContextOut = m_pDeviceContext;
	*ppBackBufferRTV = m_pBackBufferRTV;
	*ppDepthStencilView = m_pDepthStencilView;
	*ppSwapChain = m_pSwapChain;

	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pDeviceContext);

	Safe_AddRef(m_pBackBufferRTV);
	Safe_AddRef(m_pDepthStencilView);
	Safe_AddRef(m_pSwapChain);

	return S_OK;
}

HRESULT CGraphic_Device::Clear_BackBuffer_View(_float4 vClearColor)
{
	if (nullptr == m_pDeviceContext)
	{
		__debugbreak();
		return E_FAIL;
	}

	/* ����۸� �ʱ�ȭ�Ѵ�.  */
	m_pDeviceContext->ClearRenderTargetView(m_pBackBufferRTV, (_float*)&vClearColor);

	return S_OK;
}

HRESULT CGraphic_Device::Clear_DepthStencil_View()
{
	if (nullptr == m_pDeviceContext)
	{
		__debugbreak();
		return E_FAIL;
	}

	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	return S_OK;
}

HRESULT CGraphic_Device::Present()
{
	if (nullptr == m_pSwapChain)
	{
		__debugbreak();
		return E_FAIL;
	}

	return m_pSwapChain->Present(0, 0);	
}


HRESULT CGraphic_Device::Ready_SwapChain(HWND hWnd, WINMODE eWinMode, _uint iWinCX, _uint iWinCY)
{
	IDXGIDevice*			pDevice = nullptr;
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDevice);

	IDXGIAdapter*			pAdapter = nullptr;
	pDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pAdapter);

	IDXGIFactory*			pFactory = nullptr;
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	DXGI_SWAP_CHAIN_DESC		SwapChain;
	ZeroMemory(&SwapChain, sizeof(DXGI_SWAP_CHAIN_DESC));
			
	SwapChain.BufferDesc.Width = iWinCX;
	SwapChain.BufferDesc.Height = iWinCY;
	SwapChain.BufferDesc.RefreshRate.Numerator = 60;
	SwapChain.BufferDesc.RefreshRate.Denominator = 1;	
	SwapChain.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	SwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChain.SampleDesc.Quality = 0;
	SwapChain.SampleDesc.Count = 1;
	SwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChain.BufferCount = 1;
	SwapChain.OutputWindow = hWnd;	
	SwapChain.Windowed = eWinMode;
	SwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	FAILED_CHECK(pFactory->CreateSwapChain(m_pDevice, &SwapChain, &m_pSwapChain));

	Safe_Release(pFactory);
	Safe_Release(pAdapter);
	Safe_Release(pDevice);

	return S_OK;
}


HRESULT CGraphic_Device::Ready_BackBufferRenderTargetView()
{
	if (nullptr == m_pDevice)
	{
		__debugbreak();
		return E_FAIL;
	}

	ID3D11Texture2D*		pBackBufferTexture = nullptr;

	FAILED_CHECK(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture));

	FAILED_CHECK(m_pDevice->CreateRenderTargetView(pBackBufferTexture, nullptr, &m_pBackBufferRTV));

	Safe_Release(pBackBufferTexture);	

	return S_OK;
}

HRESULT CGraphic_Device::Ready_DepthStencilRenderTargetView(_uint iWinCX, _uint iWinCY)
{
	if (nullptr == m_pDevice)
	{
		__debugbreak();
		return E_FAIL;
	}

	ID3D11Texture2D*		pDepthStencilTexture = nullptr;
	
	D3D11_TEXTURE2D_DESC	TextureDesc;
	ZeroMemory(&TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	TextureDesc.Width = iWinCX;
	TextureDesc.Height = iWinCY;
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

	/* RenderTarget */
	/* ShaderResource */
	/* DepthStencil */

	FAILED_CHECK(m_pDevice->CreateDepthStencilView(pDepthStencilTexture, nullptr, &m_pDepthStencilView));

	Safe_Release(pDepthStencilTexture);

	return S_OK;
}

void CGraphic_Device::Free()
{
	_ulong RefChecker = 0;
	
	RefChecker += Safe_Release(m_pSwapChain);
	RefChecker += Safe_Release(m_pDepthStencilView);
	RefChecker += Safe_Release(m_pBackBufferRTV);
	RefChecker += Safe_Release(m_pDeviceContext);
	ID3D11Device* ForCheckDevice = m_pDevice;
	RefChecker += Safe_Release(ForCheckDevice);

//#define USE_DEBUG_STRING

	if (RefChecker > 0)
	{
		OutputDebugStringW(L"Device isn't Deleted");
#if defined USE_DEBUG_STRING



		ID3D11Debug* d3dDebug;
		HRESULT hr = m_pDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&d3dDebug));
		if (SUCCEEDED(hr))
		{
			OutputDebugStringW(L"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \r\n");
			OutputDebugStringW(L"                                                                    D3D11 Live Object ref Count Checker \r\n");
			OutputDebugStringW(L"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \r\n");

			hr = d3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

			OutputDebugStringW(L"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \r\n");
			OutputDebugStringW(L"                                                                    D3D11 Live Object ref Count Checker END \r\n");
			OutputDebugStringW(L"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \r\n");
		}
		if (d3dDebug != nullptr)            d3dDebug->Release();
		__debugbreak();
#else


#endif

	}


}
