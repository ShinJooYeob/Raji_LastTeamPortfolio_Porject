//#pragma once
//
//#include "Base.h"
//
//BEGIN(Client)
//
//// Ŭ���̾�Ʈ�� DESC ���� ���� �ҷ����� Ŭ����
//// ���̳ʸ��� DESC���� ���� �� �ҷ����� ����
//
//// �ҷ��� ������ ���� ����
//class CGameObject_Base;
//
//class CObjectIO final
//	:public CBase
//{
//private:
//	explicit	CObjectIO() = default;
//	explicit	CObjectIO(const CObjectIO& rhs) = default;
//	virtual		~CObjectIO() = default;
//
//public:
//	HRESULT NativeConstruct();
//
//public:
//	// ������Ʈ Ÿ�Ժ��� ���� ����
////	HRESULT SaverObject(E_OBJECT_TYPE type, wstring FolderPath, wstring filename, CGameObject_Base* obj);
//
//	// �����͸� �ҷ��ͼ� �����⿡ �ѱ�
//	HRESULT LoadObject_Create(wstring FolderPath, wstring filename);
//
//	// Creater �ʿ� ���� ����
//	bool Create_CreateMap_ProtoType(HANDLE& hFile, wstring keyname);
//	
//	// ������Ʈ�� descŸ�� ���� ������ �����Ѵ�.
//	// ������ Ŭ������ ���� �Ŷ� enum��� �ɵ�
//	HRESULT				Save_DESC(wstring FolderPath, wstring filename, void* desc);
//	HRESULT				Load_DESC(wstring FolderPath, wstring filename, wstring Extension);
//	wstring				Get_EXEDescName();
//
//
//
//public:
//	static CObjectIO* Create();
//	virtual void Free() override;
//};
//
//END