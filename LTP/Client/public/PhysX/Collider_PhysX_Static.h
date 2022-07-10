#pragma once

#include "Collider_PhysX_Base.h"

BEGIN(Client)



class CCollider_PhysX_Static : public CCollider_PhysX_Base
{
public:
	enum E_STATICTYPE
	{
		E_STATIC_BUFFER,
		E_STATIC_STATIC,
		E_STATIC_END,
	};

	//enum E_STATITRIGGERID
	//{
	//	E_STATITRIGGERID_0,
	//	E_STATITRIGGERID_1,
	//	E_STATITRIGGERID_2,
	//	E_STATITRIGGERID_3,
	//	E_STATITRIGGERID_END,
	//};

	//enum E_STATICID
	//{
	//	E_STATICID_STATIC,
	//	E_STATICID_TRIGGER,
	//	E_STATICID_END,
	//};



private:
	explicit CCollider_PhysX_Static(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext);
	explicit CCollider_PhysX_Static(const CCollider_PhysX_Static& rhs);
	virtual ~CCollider_PhysX_Static() = default;

public:
	HRESULT Initialize_Prototype(void * pArg);
	HRESULT Initialize_Clone(void * pArg);

	virtual HRESULT Update_BeforeSimulation()override;
	virtual HRESULT Update_AfterSimulation()override;

public:
	const PHYSXDESC_STATIC& Get_PhysXDesc() const { return mPhysXDesc; }
	HRESULT Set_ColiiderDesc(PHYSXDESC_STATIC desc);
	HRESULT Set_ColiiderBufferDesc(PHYSXDESC_STATIC desc);
	HRESULT	Set_eDISABLE_SIMULATION(bool b = true);
	
public:
#ifdef _DEBUG
	virtual HRESULT Render() override;

#endif // _DEBUG
	// static �浹ü ����

protected:
	E_STATICTYPE			mStaticID = E_STATIC_END;
	PHYSXDESC_STATIC		mPhysXDesc;
	PxRigidStatic*			mPxRigStaticActor;

public:
	static CCollider_PhysX_Static* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void* pArg = nullptr);
	virtual CComponent* Clone(void* pArg)override;
	virtual void Free()override;

	// CCollider_PhysX_Base��(��) ���� ��ӵ�
};

END