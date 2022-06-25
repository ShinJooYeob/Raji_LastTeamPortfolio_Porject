#pragma once
#include "Base.h"

// �� �δ� �Ŵ���

class CAssimpMgr
	:public CBase
{
	DECLARE_SINGLETON(CAssimpMgr);

private:
	CAssimpMgr() = default;
	~CAssimpMgr() = default;

public:
	HRESULT Initialize(ID3D11Device* d, ID3D11DeviceContext* c);
	HRESULT ReleaseMap();

	HRESULT Initialize_FbxSetting();

	HRESULT Save_MODELDESC(wstring FolderPath, wstring filename, MODELDESC* desc);



private:
	ID3D11Device*			mDevice = nullptr;
	ID3D11DeviceContext*	mDeviceContext = nullptr;
private:
	map<string, class CModel*>		mMap_ComponentModel;

	// ���̸����� ����
	map<string, MODELDESC*>			mMap_ModelDesc;

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

