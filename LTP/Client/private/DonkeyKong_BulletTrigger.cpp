#include "stdafx.h"
#include "..\public\DonkeyKong_BulletTrigger.h"
#include "DonkeyKong_Bullet.h"


CDonkeyKong_BulletTrigger::CDonkeyKong_BulletTrigger(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CGameObject(pDevice, pDeviceContext)
{
}

CDonkeyKong_BulletTrigger::CDonkeyKong_BulletTrigger(const CDonkeyKong_BulletTrigger & rhs)
	: CGameObject(rhs)
{
}

HRESULT CDonkeyKong_BulletTrigger::Initialize_Prototype(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Prototype(pArg));


	return S_OK;
}

HRESULT CDonkeyKong_BulletTrigger::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	FAILED_CHECK(SetUp_Components());

	SetUp_Info();

	m_pRendererCom->OnOff_PostPorcessing_byParameter(POSTPROCESSING_DEBUGCOLLIDER, true);

	return S_OK;
}

_int CDonkeyKong_BulletTrigger::Update(_double dDeltaTime)
{
	if (__super::Update(dDeltaTime) < 0)return -1;


	Update_Collider(dDeltaTime);

	return _int();
}

_int CDonkeyKong_BulletTrigger::LateUpdate(_double dDeltaTime)
{
	if (__super::LateUpdate(dDeltaTime) < 0)return -1;


	FAILED_CHECK(m_pRendererCom->Add_DebugGroup(m_pColliderCom));

	return _int();
}

_int CDonkeyKong_BulletTrigger::Render()
{
	if (__super::Render() < 0)
		return -1;

	return _int();
}

_int CDonkeyKong_BulletTrigger::LateRender()
{
	if (__super::LateRender() < 0)
		return -1;


	return _int();
}

void CDonkeyKong_BulletTrigger::CollisionTriger(CCollider * pMyCollider, _uint iMyColliderIndex, CGameObject * pConflictedObj, CCollider * pConflictedCollider, _uint iConflictedObjColliderIndex, CollisionTypeID eConflictedObjCollisionType)
{
	CDonkeyKong_Bullet* pBullet = static_cast<CDonkeyKong_Bullet*>(pConflictedObj);

	CTransform* pBulletTransform = static_cast<CTransform*>(pBullet->Get_Component(TAG_COM(Com_Transform)));

	_float3 fBulletPos = pBulletTransform->Get_MatrixState_Float3(CTransform::STATE_POS);
	_float3 fColliderPos = pMyCollider->Get_ColliderPosition(iMyColliderIndex);

	switch (iMyColliderIndex)
	{
	case 1:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x <= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(9);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
			}
		}
		break;
	}
	case 3:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x <= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(9);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
			}
		}
		break;
	}
	case 5:
	{
		if (fColliderPos.x <= fBulletPos.x + 0.2)
		{
			pBullet->Set_NaviIndex(9);
			pBullet->Set_MovoToHeightOn(true);
			pBullet->Set_MovoToWidthOn(false);

			pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
		}
		break;
	}
	case 7:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x >= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(7);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::RIGHT);
			}
		}
		break;
	}
	case 9:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x >= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(7);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::RIGHT);
			}
		}
		break;
	}
	case 11:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x >= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(7);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::RIGHT);
			}
		}
		break;
	}
	case 13:
	{
		if (fColliderPos.x + 0.2 >= fBulletPos.x)
		{
			pBullet->Set_NaviIndex(7);
			pBullet->Set_MovoToHeightOn(true);
			pBullet->Set_MovoToWidthOn(false);

			pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::RIGHT);
		}
		break;
	}
	case 15:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x <= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(5);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
			}
		}
		break;
	}
	case 17:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x <= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(5);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
			}
		}
		break;
	}
	case 19:
	{
		if (fColliderPos.x <= fBulletPos.x + 0.2)
		{
			pBullet->Set_NaviIndex(5);
			pBullet->Set_MovoToHeightOn(true);
			pBullet->Set_MovoToWidthOn(false);

			pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
		}
		break;
	}
	case 21:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x >= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(3);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::RIGHT);
			}
		}
		break;
	}
	case 23:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x >= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(3);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::RIGHT);
			}
		}
		break;
	}
	case 25:
	{
		if (fColliderPos.x + 0.2 >= fBulletPos.x)
		{
			pBullet->Set_NaviIndex(3);
			pBullet->Set_MovoToHeightOn(true);
			pBullet->Set_MovoToWidthOn(false);

			pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::RIGHT);
		}
		break;
	}
	case 27:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x <= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(1);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
			}
		}
		break;
	}
	case 29:
	{
		pBullet->Set_NewColliderIndex(iMyColliderIndex);

		if (pBullet->Get_bDescent() == true)
		{
			if (fColliderPos.x <= fBulletPos.x)
			{
				pBullet->Set_NaviIndex(1);
				pBullet->Set_MovoToHeightOn(true);
				pBullet->Set_MovoToWidthOn(false);

				pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
			}
		}
		break;
	}
	case 31:
	{
		if (fColliderPos.x <= fBulletPos.x + 0.2)
		{
			pBullet->Set_NaviIndex(1);
			pBullet->Set_MovoToHeightOn(true);
			pBullet->Set_MovoToWidthOn(false);

			pBullet->Set_MoveToDirIndex(CDonkeyKong_Bullet::LEFT);
		}
		break;
	}
	case 33:
	{
		pBullet->Set_IsDead();
		break;
	}
	}
}

_float CDonkeyKong_BulletTrigger::Take_Damage(CGameObject * pTargetObject, _float fDamageAmount, _fVector vDamageDir, _bool bKnockback, _float fKnockbackPower)
{
	return _float();
}

HRESULT CDonkeyKong_BulletTrigger::SetUp_Components()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Renderer), TAG_COM(Com_Renderer), (CComponent**)&m_pRendererCom));
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Transform), TAG_COM(Com_Transform), (CComponent**)&m_pTransformCom));

	SetUp_Collider();

	return S_OK;
}

HRESULT CDonkeyKong_BulletTrigger::SetUp_Collider()
{
	FAILED_CHECK(Add_Component(SCENE_STATIC, TAG_CP(Prototype_Collider), TAG_COM(Com_Collider), (CComponent**)&m_pColliderCom));

	COLLIDERDESC			ColliderDesc;

	//Index == 0;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(30.f, 30.f, 30.f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(40.f, 40.f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));

	////////////////////////ù��°
	//Index == 1;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(40.46f, 44.771f, 40.f, 1.f);	//_float4(40.346f, 44.92f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 2;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(40.46f, 42.596f, 40.f, 1.f);	//_float4(40.346f, 42.639f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////�ι�°
	//Index == 3;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(46.32f, 44.617f, 40.f, 1.f);  //_float4(46.475f, 44.838f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 4;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(46.32f, 42.745f, 40.f, 1.f);  //_float4(46.475f, 42.768f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////����°
	//Index == 5;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(47.809f, 44.578f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 6;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(47.809f, 42.783f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////�׹�°
	//Index == 7;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(44.32f, 42.694f, 40.f, 1.f);  //_float4(44.567f, 42.728f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 8;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(44.32f, 40.244f, 40.f, 1.f);  //_float4(44.567f, 40.238f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////�ټ���°
	//Index == 9;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(36.56f, 42.497f, 40.f, 1.f);  //_float4(36.451f, 42.557f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 10;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(36.56f, 40.438f, 40.f, 1.f);  //_float4(36.451f, 40.441f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////������°
	//Index == 11;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(30.72f, 42.349f, 40.f, 1.f);	//_float4(30.389f, 42.43f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 12;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(30.72f, 40.585f, 40.f, 1.f);  //_float4(30.389f, 40.593f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////�ϰ���°
	//Index == 13;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(28.055f, 42.281f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 14;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(28.055f, 40.652f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////������°
	//Index == 15;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(35.57f, 40.464f, 40.f, 1.f); //_float4(35.41f, 40.468f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 16;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(35.57f, 37.814f, 40.f, 1.f);  //_float4(35.41f, 37.811f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////��ȩ��°
	//Index == 17;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(41.46f, 40.316f, 40.f, 1.f);  //_float4(41.499f, 40.315f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 18;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(41.46f, 37.936f, 40.f, 1.f);  //_float4(41.499f, 37.936f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////����°
	//Index == 19;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(48.835f, 40.131f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 20;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(48.835f, 38.087f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////���ѹ�°
	//Index == 21;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(39.417f, 37.894f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 22;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(39.417f, 35.67f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////���ι�°
	//Index == 23;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(31.68f, 37.734f, 40.f, 1.f);  //_float4(31.413f, 37.729f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 24;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(31.68f, 35.872f, 40.f, 1.f);  //_float4(31.413f, 35.879f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////������°
	//Index == 25;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(29.081f, 37.681f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 26;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(29.081f, 35.94f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////���׹�°
	//Index == 27;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(37.55f, 35.719f, 40.f, 1.f);  //_float4(37.405f, 35.723f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 28;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(37.55f, 33.226f, 40.f, 1.f);  //_float4(37.405f, 33.223f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////���ټ���°
	//Index == 29;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(50.25f, 35.388f, 40.f, 1.f);  //_float4(50.535f, 35.388f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 30;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(50.25f, 33.437f, 40.f, 1.f);  //_float4(50.535f, 33.442f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	////////////////////////��������°
	//Index == 31;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(52.836f, 35.32f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();

	//Index == 32;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(52.836f, 33.481f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	//Index == 33;
	ZeroMemory(&ColliderDesc, sizeof(COLLIDERDESC));
	ColliderDesc.vScale = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vRotation = _float4(0.f, 0.f, 0.f, 1.f);
	ColliderDesc.vPosition = _float4(30.032f, 33.601f, 40.f, 1.f);
	FAILED_CHECK(m_pColliderCom->Add_ColliderBuffer(COLLIDER_SPHERE, &ColliderDesc));
	m_pColliderCom->Set_ParantBuffer();
	////////////////////////

	return S_OK;

}

HRESULT CDonkeyKong_BulletTrigger::SetUp_Info()
{
	m_pTransformCom->Set_MatrixState(CTransform::STATE_POS, XMVectorSet(0.f, 0.f, 0.f, 1.f));

	return S_OK;
}

HRESULT CDonkeyKong_BulletTrigger::Update_Collider(_double dDeltaTime)
{
	NULL_CHECK_RETURN(m_pColliderCom, E_FAIL);

	m_pColliderCom->Update_ConflictPassedTime(dDeltaTime);

	_uint iNumCollider = m_pColliderCom->Get_NumColliderBuffer();
	for (_uint i = 0; i < iNumCollider; i++)
	{
		m_pColliderCom->Update_Transform(i, m_pTransformCom->Get_WorldMatrix());
	}
	FAILED_CHECK(g_pGameInstance->Add_CollisionGroup(CollisionType_PlayerWeapon, this, m_pColliderCom));

	return S_OK;
}


CDonkeyKong_BulletTrigger * CDonkeyKong_BulletTrigger::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{
	CDonkeyKong_BulletTrigger*	pInstance = NEW CDonkeyKong_BulletTrigger(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Created CDonkeyKong_BulletTrigger");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CDonkeyKong_BulletTrigger::Clone(void * pArg)
{
	CDonkeyKong_BulletTrigger*	pInstance = NEW CDonkeyKong_BulletTrigger(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Created CDonkeyKong_BulletTrigger");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDonkeyKong_BulletTrigger::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pColliderCom);

}