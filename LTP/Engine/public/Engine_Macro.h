#pragma once



#ifdef ENGINE_EXPORTS
#define ENGINE_DLL	_declspec(dllexport)
#else
#define ENGINE_DLL	_declspec(dllimport)
#endif // DEBUG

// IMGUI�� ���� ����ϱ� �Ҵ� �� NEW�� �����
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define NEW new ( _NORMAL_BLOCK, __FILE__,__LINE__ )

#else
#define NEW new

#endif


#define CAMERAFAR 300.f

#define EASING_PI 3.1415926535f

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

#define GetSingle(SINGLETON) SINGLETON::GetInstance()
#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL;	}

#define DIS_Up				0b00000001
#define DIS_Down			0b00000110
#define DIS_DoubleDown		0b00000100
#define DIS_Press			0b11111111

#define SceneChangeNoiseIndex 434

#define D3D11COLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
//#define D3D11COLOR_ARGB(a,r,g,b) \
//    ((D3DCOLOR)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))

#define NOT_EXIST_VECTOR		_float3(99999999.f,99999999.f,99999999.f)
#define NOT_EXIST_FLOAT			-999999999.f

//// ��
//#define COLOR_GRAY		(D3DCOLOR_ARGB(255, 124, 124, 124))
//#define COLOR_BLUE      (D3DCOLOR_XRGB(0, 0, 255))
//#define COLOR_WHITE     (D3DCOLOR_XRGB(255, 255, 255))
//#define COLOR_BLACK     (D3DCOLOR_XRGB(0, 0, 0))
//#define COLOR_RED		(D3DCOLOR_XRGB(255, 0, 0))
//#define COLOR_GREEN		(D3DCOLOR_XRGB(0, 255, 0))
//#define COLOR_YELLOW    (D3DCOLOR_XRGB(255, 255, 0))
//#define COLOR_CYAN      (D3DCOLOR_XRGB(0, 255, 255))
//#define COLOR_MAGENTA   (D3DCOLOR_XRGB(255, 0, 255))

#define BEGIN(p)	namespace p {
#define END			}


 

#define MSGBOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("System Message"), MB_OK);

#define MAX_TEXTURE_TYPE				18


//�̱���////////////////////////////////////////////////////////////////////////
#define NO_COPY(CLASSNAME)								\
		private:										\
		CLASSNAME(const CLASSNAME&);					\
		CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)					\
		NO_COPY(CLASSNAME)								\
		private:										\
		static CLASSNAME*	m_pInstance;				\
		public:											\
		static CLASSNAME*	GetInstance( void );		\
		static _ulong DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)					\
		CLASSNAME*	CLASSNAME::m_pInstance = nullptr;	\
		CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
			if(nullptr == m_pInstance) {				\
				m_pInstance = new CLASSNAME;			\
			}											\
			return m_pInstance;							\
		}												\
		_ulong CLASSNAME::DestroyInstance( void ) {		\
			_ulong dwRefCnt = 0;						\
			if(nullptr != m_pInstance)	{				\
				dwRefCnt = m_pInstance->Release();		\
				m_pInstance = nullptr;					\
			}											\
			return dwRefCnt;							\
		}


#define GET_INSTANCE(CLASSNAME)	[](){											\
	CLASSNAME*	pInstance = CLASSNAME::GetInstance();							\
	if(nullptr == pInstance) {													\
	char	szMessage[MAX_PATH] = "";											\
	strcpy_s(szMessage, typeid(CLASSNAME).name());								\
	strcat_s(szMessage, "is nullptr");											\
	MessageBoxA(0, szMessage, nullptr, MB_OK);}									\
	else {																		\
	pInstance->AddRef();}														\
	return pInstance;															\
	}();

#define RELEASE_INSTANCE(CLASSNAME)	[](){										\
	CLASSNAME*	pInstance = CLASSNAME::GetInstance();							\
	if(nullptr == pInstance) {													\
	char	szMessage[MAX_PATH] = "";											\
	strcpy_s(szMessage, typeid(CLASSNAME).name());								\
	strcat_s(szMessage, "is nullptr");											\
	MessageBoxA(0, szMessage, nullptr, MB_OK);}									\
	else {																		\
	pInstance->Release();}														\
	}();


// ����� üũ ��ũ��
// {__asm { int 3; }; �ڵ� �������� Break ����Ʈ �ɱ� 86��Ʈ ����
// __debugbreak(); �ڵ� �������� Break ����Ʈ �ɱ� 64��Ʈ ����

#define DEBUGBREAK __debugbreak()

// NULL üũ1 / �⺻ 
#define NULL_CHECK( _ptr) \
if( _ptr == 0){__debugbreak(); return;}


// NULL üũ2 / �� ���� 
#define NULL_CHECK_BREAK( _ptr) \
if( _ptr == 0){__debugbreak();}

// NULL üũ3 / ���� ���� 
#define NULL_CHECK_RETURN( _ptr, _return) \
if( _ptr == 0){__debugbreak(); return _return;}

// NULL üũ4 / �޼����ڽ�
#define NULL_CHECK_MSG( _ptr, _message) \
if( _ptr == 0){MessageBox(NULL, _message, L"System Message", MB_OK);__debugbreak();}

// NULL üũ4 / �޼����ڽ� / ���� ����
#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message ) \
if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__debugbreak();return _return;}

// IF üũ / TRUE
#define IF_CHECK_TRUE( _IF) \
if(_IF){__debugbreak();}

// IF üũ / FALSE
#define IF_CHECK_FALSE( _IF) \
if(_IF){__debugbreak();}


//#define IF_CHECK_MESSAGE( _IF, _message) \
//if( _IF){MessageBox(NULL, _message, L"System Message", MB_OK);__debugbreak();};


// HRESULT ����üũ

// HRESULT ����üũ1 / �⺻
#define FAILED_CHECK(_hr) \
if(((HRESULT)(_hr)) < 0) { MSGBOX("Fail"); __debugbreak();\
return E_FAIL;}

// HRESULT ����üũ2 / �븮��
#define FAILED_CHECK_NONERETURN(_hr) \
if(((HRESULT)(_hr)) < 0) { MSGBOX("Fail"); __debugbreak();}

// HRESULT ����üũ3 / ���� ����
#define FAILED_CHECK_RETURN(_hr, _return) if( ((HRESULT)(_hr)) < 0 ) \
{ MessageBox(NULL, L"Failed", L"System Error",MB_OK); __debugbreak();\
return _return;}

// HRESULT ����üũ4 / �޼��� ����
#define FAILED_CHECK_MSG( _hr, _message) if( ((HRESULT)(_hr)) < 0 ) \
{ MessageBox(NULL, _message, L"System Message",MB_OK); __debugbreak();return E_FAIL;}

// HRESULT ����üũ5 / ���� �޼��� ����
#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message) if( ((HRESULT)(_hr)) < 0 ) \
{ MessageBox(NULL, _message, L"System Message"sp,MB_OK); __debugbreak();return _return;}






static const char* Tag_ModelTextureTypeForEngine(unsigned int eTag)
{
	switch (eTag)
	{
	case aiTextureType_NONE:		return "None";
		break;
	case aiTextureType_DIFFUSE:	return "g_DiffuseTexture";
		break;
	case aiTextureType_SPECULAR:return "g_SpecularTexture";
		break;
	case aiTextureType_AMBIENT:return "g_AmbientTexture";
		break;
	case aiTextureType_EMISSIVE:return "g_EmissiveTexture";
		break;
	case aiTextureType_HEIGHT:return "g_HeightTexture";
		break;
	case aiTextureType_NORMALS:return "g_NormalTexture";
		break;
	case aiTextureType_SHININESS:return "g_ShininessTexture";
		break;
	case aiTextureType_OPACITY:return "g_OpacityTexture";
		break;
	case aiTextureType_DISPLACEMENT:return "g_DisplaceTexture";
		break;
	case aiTextureType_LIGHTMAP:return "g_LightMapTexture";
		break;
	case aiTextureType_REFLECTION:return "g_ReflectTexture";
		break;
	case aiTextureType_BASE_COLOR:return "g_BaseColorTexture";
		break;
	case aiTextureType_NORMAL_CAMERA:return "g_NormalCamTexture";
		break;
	case aiTextureType_EMISSION_COLOR:return "g_EmissionColorTexture";
		break;
	case aiTextureType_METALNESS:return "g_MetalTexture";
		break;
	case aiTextureType_DIFFUSE_ROUGHNESS:return "g_DiffuseRoughTexture";
		break;
	case aiTextureType_AMBIENT_OCCLUSION:return "g_AmbientOcculusionTexture";
		break;
	case aiTextureType_UNKNOWN:return "";
		break;
	case _aiTextureType_Force32Bit:return "";
		break;
	default:
		OutputDebugStringW(L"Wrong Type Texture");
		__debugbreak();
		return nullptr;
		break;
	}
}
#define  MODLETEXTYPEFORENGINE Tag_ModelTextureTypeForEngine

#define ThreadSleepRate 1