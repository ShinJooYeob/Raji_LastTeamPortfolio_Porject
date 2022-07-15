#pragma once
#include "GameObject.h"
#include "Collider_PhysX_Base.h"



BEGIN(Client)
// For PHysX


class CTestObject_PhysX final : public CGameObject
{
public:
	enum E_MODEL
	{
		MODEL_GEMETRY,
		MODEL_STATICMAPOBJ,
		MODEL_PLAYER,
		MODEL_MONSTER,
		MODEL_EMPTY,
		MODEL_END,
	};

	enum E_TESTTYPE
	{
		TESTTYPE_NOMAL,
		TESTTYPE_PHYSX,
		TESTTYPE_SOUND,
		TESTTYPE_END,
	};


private:
	CTestObject_PhysX(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CTestObject_PhysX(const CTestObject_PhysX& rhs);
	virtual ~CTestObject_PhysX() = default;

public:
	virtual HRESULT Initialize_Prototype(void* pArg)override;
	virtual HRESULT Initialize_Clone(void* pArg)override;

public:
	virtual _int Update(_double fDeltaTime)override;
	virtual _int LateUpdate(_double fDeltaTime)override;
	virtual _int Render()override;
	virtual _int LateRender()override;


	CCollider_PhysX_Base* Get_ComCollider() { return mCom_ColliderBase; }
public:
	void	Set_Trigger(bool b) { mbTrigger = b; };
	void	Set_Postition(_float3 position);
	void	Set_Scale(_float3 scale);

	virtual void CollisionPhysX_Trigger(CGameObject* pTriggerObj, _uint objectid, COLLIDERTYPE_PhysXID eConflictedObjCollisionType)override;
	virtual void CollisionPhysX_Rigid(CGameObject* pOtherObject, _uint objectid,  COLLIDERTYPE_PhysXID eConflictedObjCollisionType)override;



	// ������ �׽�Ʈ�ø� ���
	HRESULT	Set_ColSetID(E_PHYTYPE id);

	// Model Setting
	HRESULT	Set_ModelSetting(E_MODEL id);
	void	Set_TYPE(E_TESTTYPE e)
	{
		meTestType = e;
	}

	HRESULT	Set_Kinect(bool b);

private:
	HRESULT Set_PlayerMeshair();

private:
	HRESULT Update_Player(_double time);
	HRESULT Update_Static(_double time);
	HRESULT Update_Dynamic(_double time);
	HRESULT Update_Joint(_double time);

private:
	// ������ ����
	CTransform*			mCom_Transform = nullptr;
	CShader*			mCom_Shader = nullptr;
	CRenderer*			mCom_Renderer = nullptr;
	CModel*				mCom_Model = nullptr;


	class CCollider_PhysX_Base*	mCom_ColliderBase = nullptr;
	class CCollider_PhysX_Base*	mCom_ColliderHair = nullptr;

	bool				mbTrigger = false;
	int					mColID = 0;
	E_MODEL				meModelID= MODEL_END;
	E_TESTTYPE			meTestType =TESTTYPE_NOMAL;




private:
	HRESULT SetUp_Components();
	// ���� ��翡 ���� ����
	void Set_ChainTest();
	


public:
	static CTestObject_PhysX* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg = nullptr);
	virtual CTestObject_PhysX* Clone(void* pArg);
	virtual void Free() override;
};
END
