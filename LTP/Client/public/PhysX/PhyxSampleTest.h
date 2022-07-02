#pragma once

#include "Base.h"

BEGIN(Client)

// ���� �׽�Ʈ
class CPhyxSampleTest:public CBase
{
private:
	explicit CPhyxSampleTest();
	explicit CPhyxSampleTest(const CPhyxSampleTest& rhs)=default;
	virtual ~CPhyxSampleTest() = default;


public:
	virtual HRESULT Initialize_Prototype();

public:
	virtual _int Update(_double dDeltaTime);
	virtual _int LateUpdate(_double dDeltaTime);
	virtual _int Render();

private:
	// snip ����
	HRESULT SnipTestCreate_Func1();
	HRESULT SnipTestCreate_Func2();
	HRESULT SnipTestCreate_Func3();

	HRESULT CreateStack(const PxTransform& t, PxU32 size, PxReal halfExtent);



private:
	PxFoundation*			mFoundation = nullptr;
	PxPhysics*				mPhysics = nullptr;
	PxCooking*				mCooking = nullptr;

	PxScene*					mScene = nullptr;
	PxMaterial*					mMaterial = nullptr;





public:
	static CPhyxSampleTest* Create();
	virtual void Free()override;


};
END

