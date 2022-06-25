#include "stdafx.h"
#include "..\Public\Camera_Main.h"


_uint CALLBACK CameraEffectThread(void* _Prameter)
{
	THREADARG tThreadArg{};
	memcpy(&tThreadArg, _Prameter, sizeof(THREADARG));
	delete _Prameter;


	CCamera_Main* pCamemra = (CCamera_Main*)(tThreadArg.pArg);

	switch (pCamemra->Get_EffectID())
	{
	case CCamera_Main::CAM_EFT_SHAKE:
		pCamemra->Progress_Shaking_Thread(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	default:
		MSGBOX("worng Cam Eft");
		break;
	}

	return 0;
}

CCamera_Main::CCamera_Main(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CCamera(pDevice,pDeviceContext)
{
}

CCamera_Main::CCamera_Main(const CCamera_Main & rhs)
	:CCamera(rhs)
{
}
//1
HRESULT CCamera_Main::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));

	return S_OK;
}

HRESULT CCamera_Main::Initialize_Clone(void * pArg)
{

	FAILED_CHECK(__super::Initialize_Clone(pArg));


	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

_bool CCamera_Main::CamActionStart(CAMERAACTION Act)
{
	if (m_bCamActionStart)return false;

	m_bCamActionStart = true;
	m_tCamAction = Act;
	m_ActionPassedTime = 0;
	m_tCamAction.TotalTime = 0;

	_float TotalTime = 0;
	for (auto& iter : m_tCamAction.vecCamPos)
		TotalTime += iter.fDuration;
	if (m_tCamAction.TotalTime < TotalTime)m_tCamAction.TotalTime = TotalTime;
	TotalTime = 0;
	for (auto& iter : m_tCamAction.vecLookAt)
		TotalTime += iter.fDuration;
	if (m_tCamAction.TotalTime < TotalTime)m_tCamAction.TotalTime = TotalTime;


	m_ReturnPos = m_pTransform->Get_MatrixState_Float3(CTransform::STATE_POS);
	m_ReturnLook = m_ReturnPos.XMVector() + m_pTransform->Get_MatrixState(CTransform::STATE_LOOK);
	m_iNowPosIndex = 0;
	m_iNowLookIndex = 0;


	return true;
}

_int CCamera_Main::Update(_double fDeltaTime)
{
	__super::Update(fDeltaTime);


	FAILED_CHECK(Update_CamAction(fDeltaTime));


	return _int();
}

_int CCamera_Main::LateUpdate(_double fDeltaTime)
{	
	__super::LateUpdate(fDeltaTime);


	return _int();
}

_int CCamera_Main::Render()
{



	return _int();
}

_int CCamera_Main::LateRender()
{


	return _int();
}


HRESULT CCamera_Main::Start_CameraShaking_Thread(_double TotalTime, _float Power)
{
	if (m_bIsStartedShaking) return S_FALSE;

	m_eEffectID = CAM_EFT_SHAKE;
	m_TargetTime = TotalTime;
	m_fShakingPower = Power;
	m_bIsStartedShaking = true;

	GetSingle(CGameInstance)->PlayThread(CameraEffectThread, this);

	return S_OK;
}

HRESULT CCamera_Main::Progress_Shaking_Thread(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	DWORD  NowTick = GetTickCount();
	DWORD  OldTick = NowTick;

	CUtilityMgr* pUtil = GetSingle(CUtilityMgr);

	_bool	bIsReturnVector = false;
	_float3 vReturnVector = _float3(0);
	_float  vReturnPower = 0;

	_double ThreadPassedTime = 0;

	while (true)
	{
		if (*_IsClientQuit == true)
			return S_OK;

		//if (m_bCamActionStart )	break;

		NowTick = GetTickCount();
		if ((NowTick - OldTick) <= g_fDeltaTime * 1000)
			continue;
		ThreadPassedTime += (NowTick - OldTick) * 0.001f;
		OldTick = NowTick;



		if (!bIsReturnVector)
		{
			_float Rate = pUtil->RandomFloat(0, 1);
			vReturnPower = pUtil->RandomFloat(-m_fShakingPower, m_fShakingPower);


			EnterCriticalSection(_CriSec);
			vReturnVector = m_pTransform->Get_MatrixState(CTransform::STATE_RIGHT) * Rate + m_pTransform->Get_MatrixState(CTransform::STATE_UP) * (1 - Rate);
			LeaveCriticalSection(_CriSec);

			bIsReturnVector = true;
		}
		else
		{
			vReturnPower = -vReturnPower;
			bIsReturnVector = false;
		}


		EnterCriticalSection(_CriSec);
		m_pTransform->MovetoDir_bySpeed(vReturnVector.XMVector(), vReturnPower, 1);
		LeaveCriticalSection(_CriSec);


		if (m_TargetTime < ThreadPassedTime) break;

	}

	EnterCriticalSection(_CriSec);
	m_bIsStartedShaking = false;
	m_eEffectID = CAM_EFT_END;
	LeaveCriticalSection(_CriSec);

	return S_OK;
}

HRESULT CCamera_Main::Set_ViewMatrix()
{
	CGameInstance* pIsntance = GetSingle(CGameInstance);
	pIsntance->Set_Transform(PLM_VIEW, m_pTransform->Get_InverseWorldMatrix());
	pIsntance->Set_TargetPostion(PLV_CAMERA, *((_float4*)(m_pTransform->Get_WorldFloat4x4().m[3])));
	pIsntance->Set_TargetPostion(PLV_CAMLOOK, *((_float4*)(m_pTransform->Get_WorldFloat4x4().m[2])));


	m_vOldPos = m_pTransform->Get_MatrixState_Float3(CTransform::STATE_POS);
	return S_OK;
}

HRESULT CCamera_Main::SetUp_Components()
{

	//if (FAILED(__super::Add_Component(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_ComRenderer)))
	//	return E_FAIL;

	//if (FAILED(__super::Add_Component(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Texture_Blank), TAG_COM(Com_Texture), (CComponent**)&m_ComTexture)))
	//	return E_FAIL;

	//if (FAILED(__super::Add_Component(SCENEID::SCENE_STATIC, TAG_CP(Prototype_VIBuffer_Rect), TAG_COM(Com_VIBuffer), (CComponent**)&m_ComVIBuffer)))
	//	return E_FAIL;



	return S_OK;
}

#define EASINGTYPE TYPE_SinInOut

HRESULT CCamera_Main::Update_CamAction(_double fDeltaTime)
{
	if (!m_bCamActionStart)return S_FALSE;

	_Matrix NewCamMat = XMMatrixIdentity();
	CGameInstance* pInstance = g_pGameInstance;



	m_ActionPassedTime += fDeltaTime;

	if (m_ActionPassedTime > m_tCamAction.TotalTime)
		//������ �����ӱ��� ���Ҵٸ� ���� ��ġ�� �ǵ�����
	{
		m_ActionPassedTime = 0;
		m_bCamActionStart = false;

		//_float3 EasedPos;
		//_float3 EasedLookAt;


		//_float3 Old = m_tCamAction.vecCamPos[m_tCamAction.vecCamPos.size() - 1].vPosition;
		//_float3 Now = m_ReturnPos;

		//EasedPos = pInstance->Easing_Vector(EASINGTYPE, Old, Now, _float(m_ActionPassedTime - m_tCamAction.TotalTime), 0.5f);

		//Old = m_tCamAction.vecLookAt[m_tCamAction.vecLookAt.size() - 1].vPosition;
		//Now = m_ReturnLook;

		//EasedLookAt = pInstance->Easing_Vector(EASINGTYPE, Old, Now, _float(m_ActionPassedTime - m_tCamAction.TotalTime), 0.5f);

		//if (m_ActionPassedTime > m_tCamAction.TotalTime + 0.5f)
		//{
		//	EasedPos = m_ReturnPos;
		//	EasedLookAt = m_ReturnLook;
		//	m_ActionPassedTime = 0;
		//	m_bCamActionStart = false;
		//}

		//m_pTransform->Set_MatrixState(CTransform::STATE_POS, EasedPos);
		//m_pTransform->LookAt(EasedLookAt.XMVector());
	}
	else
		//������ �����ӱ��� ���� �ʾҴٸ� �����ϸ鼭 ��������� ���ض�
	{
		_float3 EasedPos;
		_float3 EasedLookAt;


		_float3 Old = m_ReturnPos;
		_float3 Now = m_tCamAction.vecCamPos[0].vPosition;
		_float	Rate = 0;
		_float	TargetTime = 0;
		_uint	iTargetIndex = _uint(m_tCamAction.vecCamPos.size() - 1);

		for (_uint i = 0; i < m_tCamAction.vecCamPos.size(); i++)
		{
			if (TargetTime + m_tCamAction.vecCamPos[i].fDuration > m_ActionPassedTime)
			{
				iTargetIndex = i;
				break;
			}

			TargetTime += m_tCamAction.vecCamPos[i].fDuration;
			Old = m_tCamAction.vecCamPos[i].vPosition;
		}

		Now = m_tCamAction.vecCamPos[iTargetIndex].vPosition;
		_float TempPassedTime = min(_float(m_ActionPassedTime - TargetTime), m_tCamAction.vecCamPos[iTargetIndex].fDuration);

		EasedPos = pInstance->Easing_Vector(EASINGTYPE, Old, Now, TempPassedTime, m_tCamAction.vecCamPos[iTargetIndex].fDuration);


		//////////////////////////////////////////////////////////////////////////
		Old = m_ReturnLook;
		Now = m_tCamAction.vecLookAt[0].vPosition;
		Rate = 0;
		TargetTime = 0;
		iTargetIndex = _uint(m_tCamAction.vecLookAt.size() - 1);
		TempPassedTime = 0;

		for (_uint i = 0; i < m_tCamAction.vecLookAt.size(); i++)
		{
			if (TargetTime + m_tCamAction.vecLookAt[i].fDuration > m_ActionPassedTime)
			{
				iTargetIndex = i;
				break;
			}

			TargetTime += m_tCamAction.vecLookAt[i].fDuration;
			Old = m_tCamAction.vecLookAt[i].vPosition;
		}

		Now = m_tCamAction.vecLookAt[iTargetIndex].vPosition;
		TempPassedTime = min(_float(m_ActionPassedTime - TargetTime), m_tCamAction.vecLookAt[iTargetIndex].fDuration);

		EasedLookAt = pInstance->Easing_Vector(EASINGTYPE, Old, Now, TempPassedTime, m_tCamAction.vecLookAt[iTargetIndex].fDuration);



		m_pTransform->Set_MatrixState(CTransform::STATE_POS, EasedPos);
		m_pTransform->LookAt(EasedLookAt.XMVector());

	}


	return S_OK;
}



CCamera_Main * CCamera_Main::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CCamera_Main* pInstance = new CCamera_Main(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg))) {
		MSGBOX("Failed to Create CCamera_Main");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CGameObject * CCamera_Main::Clone(void * pArg)
{
	CCamera_Main* pInstance = new CCamera_Main(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg))) {
		MSGBOX("Failed to Create CCamera_Main");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCamera_Main::Free()
{
	__super::Free();


}