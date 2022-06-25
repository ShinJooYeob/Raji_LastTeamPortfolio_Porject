#include "stdafx.h"
//#include "FIleIO/ObjectIO.h"
//
//HRESULT CObjectIO::NativeConstruct()
//{
//	return S_OK;
//}
//
//HRESULT CObjectIO::SaverObject(E_OBJECT_TYPE type, wstring FolderPath, wstring filename, CGameObject_Base* obj)
//{
//	// #SAVE ������Ʈ ����
//
//	_ulong			dwByte = 0;
//	wstring datPath = FolderPath + L"\\" + filename + L".dat";
//
//	HANDLE			hFile = CreateFile(datPath.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
//	if (0 == hFile)
//		return E_FAIL;
//
//	WriteFile(hFile, &(obj->Get_ObjectTypeID()), sizeof(E_OBJECT_TYPE), &dwByte, nullptr);
//
//	// 1. ������ ����
//	// 2. ������Ʈ ���� ������ ������ �б�
//
//	// Ÿ�� ����
//
//	// ������Ʈ ����� �� �����͵� ���� �����Ѵ�. Save_DESC();
//
//	switch (type)
//	{
//	case OBJECT_TYPE_2D:
//	{
//		CGameObject_2D* oobj = static_cast<CGameObject_2D*>(obj);
//		WriteFile(hFile, &(oobj->Get_UIDesc()), sizeof(UI_DESC), &dwByte, nullptr);
//		WriteFile(hFile, &(oobj->Get_TextureDesc()), sizeof(TEXTURE_NAMES_DESC), &dwByte, nullptr);
//
//		if (dwByte == 0)
//			return S_OK;	
//	}
//	break;
//	case OBJECT_TYPE_3D_STATIC:
//	{
//		CGameObject_3D_Static* oobj = static_cast<CGameObject_3D_Static*>(obj);
//		WriteFile(hFile, &(oobj->Get_ModelDESC()), sizeof(MODEL_STATIC_DESC), &dwByte, nullptr);
//		WriteFile(hFile, &(oobj->Get_ColliderDESC()), sizeof(COLLIDER_DESC), &dwByte, nullptr);
//
//		// desc
//		Save_DESC(DESC_DATA_STRNAME, FolderPath, filename, (void*) &(oobj->Get_ModelDESC()));
//		Save_DESC(DESC_DATA_COLLIDER, FolderPath, filename, (void*)&(oobj->Get_ColliderDESC()));
//
//	}
//	break;
//	case OBJECT_TYPE_3D_DYNAMIC:
//	{
//		CGameObject_3D_Dynamic* oobj = static_cast<CGameObject_3D_Dynamic*>(obj);
//		WriteFile(hFile, &(oobj->Get_ModelDESC()), sizeof(MODEL_DYNAMIC_DESC), &dwByte, nullptr);
//
//		// desc
//		Save_DESC(DESC_DATA_STRNAME, FolderPath, filename, (void*)&(oobj->Get_ModelDESC()));
//
//	}
//	break;
//
//	case OBJECT_TYPE_3D_STATIC_PARENT:
//	{
//		CGameObject_3D_Static2* oobj = static_cast<CGameObject_3D_Static2*>(obj);
//
//		auto childList = oobj->Get_ChildList();
//
//		for (auto& childObj: *childList)
//		{
//			WriteFile(hFile, &(childObj->Get_ModelDESC()), sizeof(MODEL_STATIC_DESC), &dwByte, nullptr);
//			WriteFile(hFile, &(childObj->Get_ColliderDESC()), sizeof(COLLIDER_DESC), &dwByte, nullptr);
//		}		
//	}
//	break;
//
//	case OBJECT_TYPE_TERRAIN:
//	{
//		CGameObject_MyTerrain* oobj = static_cast<CGameObject_MyTerrain*>(obj);
//		Save_DESC(DESC_DATA_TERRAIN, FolderPath, filename, (void*)&(oobj->Get_TerrainDESC()));
//	}
//
//	break;
//	case OBJECT_TYPE_END:
//
//		break;
//	default:
//		break;
//	}
//
//	// 3. ���� �ݱ�
//	CloseHandle(hFile);
//
//	return S_OK;
//}
//
//// 1. ��ü�� ������ �� ���� ����
//// 2. ���� ����/���� �����ϰ� IMGUI �Ǵ�.
//HRESULT CObjectIO::Save_DESC(E_DESC_DATA descid, wstring FolderPath, wstring filename, void* voidDesc)
//{
//	// #SAVE DESC ���� ����
//	// Ȯ���ڷ� ������ // �� 
//	_ulong			dwByte = 0;
//
//	wstring ExeName = DESCEXE(descid);
//	wstring DescPath = FolderPath + L"\\DESC\\" + filename + ExeName;
//	HANDLE			hFile = CreateFile(DescPath.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
//	if (0 == hFile)
//		return E_FAIL;
//
//	switch (descid)
//	{
//	case DESC_DATA_WORLD:
//		break;
//	case DESC_DATA_TEXTURENAME:
//		break;
//	case DESC_DATA_STRNAME:
//		break;
//	case DESC_DATA_COLLIDER:
//		break;
//	case DESC_DATA_TERRAIN:
//	{
//		TERRAIN_DESC desc = (*(TERRAIN_DESC*)(voidDesc));
//		WriteFile(hFile, &desc.meTerrainSize, sizeof(E_TERRAINSIZE), &dwByte, nullptr);
//		WriteFile(hFile, &desc.mTextureMultiSize, sizeof(_uint), &dwByte, nullptr);
//
//		WriteFile(hFile, &desc.mTileSize, sizeof(_uint), &dwByte, nullptr);
//		for (int i = 0; i < desc.mTileSize; ++i)
//		{
//			WriteFile(hFile, &desc.mArrayIndes[i], sizeof(_uint), &dwByte, nullptr);
//		}
//
//		WriteFile(hFile, &desc.mObjectSize, sizeof(_uint), &dwByte, nullptr);
//		for (int i = 0; i < desc.mObjectSize; ++i)
//		{
//			WriteFile(hFile, &desc.mArrayModelObjects[i], sizeof(MODEL_WORLD_DESC), &dwByte, nullptr);
//		}
//	}
//		break;
//	case DESC_DATA_END:
//		break;
//	default:
//		break;
//	}
//
//	CloseHandle(hFile);
//
//	return S_OK;
//}
//
//HRESULT CObjectIO::Load_DESC(E_DESC_DATA descid, wstring FolderPath, wstring filename, wstring Extension)
//{
//	// #LOADDESC ���� �ε� �׽�Ʈ �ʿ�
//	CGameObject_Creater* creater = GetSingle(CGameManager)->Get_CreaterManager();
//
//	_ulong			dwByte = 0;
//
//	wstring ExeName = Get_EXEDescName(descid);
//
//	if ((Extension != ExeName))
//		return S_FALSE;
//
//	wstring DescPath = FolderPath + L"\\DESC\\" + filename;
//
//	HANDLE			hFile = CreateFile(DescPath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
//	if (0 == hFile)
//		return E_FAIL;
//
//	// ���� ���� �о DESC MAP�� �����صд�.
//
//	switch (descid)
//	{
//	case DESC_DATA_TERRAIN:
//		TERRAIN_DESC* desc = NEW TERRAIN_DESC;
//
//		ReadFile(hFile, &desc->meTerrainSize, sizeof(_uint), &dwByte, nullptr);
//		ReadFile(hFile, &desc->mTextureMultiSize, sizeof(_uint), &dwByte, nullptr);
//
//		ReadFile(hFile, &desc->mTileSize, sizeof(_uint), &dwByte, nullptr);
//		if (desc->mTileSize != 0)
//		{
//			desc->mArrayIndes = NEW _uint[desc->mTileSize];
//			for (int i = 0; i < desc->mTileSize; ++i)
//			{
//				ReadFile(hFile, &desc->mArrayIndes[i], sizeof(_uint), &dwByte, nullptr);
//			}
//		}
//
//		ReadFile(hFile, &desc->mObjectSize, sizeof(_uint), &dwByte, nullptr);
//		if (desc->mObjectSize != 0)
//		{
//			desc->mArrayModelObjects = NEW MODEL_WORLD_DESC[desc->mObjectSize];
//			for (int i = 0; i < desc->mObjectSize; ++i)
//			{
//				ReadFile(hFile, &desc->mArrayModelObjects[i], sizeof(MODEL_WORLD_DESC), &dwByte, nullptr);
//			}
//		}
//
//		// Desc ���� ����
//		Add_TerrainDesc(filename, desc);
//		break;
//	}
//
//
//	if (dwByte == 0)
//	{
//		CloseHandle(hFile);
//		return E_FAIL;
//	}
//
//
//	CloseHandle(hFile);
//
//	return S_OK;
//}
//
//wstring CObjectIO::Get_EXEDescName(E_DESC_DATA descid)
//{
//
//	wstring exestr = STR_DATADESC_EXE(descid);
//	if (exestr.empty())
//		return exestr;
//	exestr = exestr.substr(1, exestr.size());
//	return exestr;
//
//}
//
//
//HRESULT CObjectIO::LoadObject_Create(wstring FolderPath, wstring filename)
//{
//	// �ε�� ������ ���� �Ѵ�.
//	wstring path = FolderPath + L"\\" + filename;
//
//	HANDLE			hFile = CreateFile(path.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
//	if (0 == hFile)
//		return E_FAIL;
//
//	if (false == Create_CreateMap_ProtoType(hFile, filename))
//		return E_FAIL;
//
//	CloseHandle(hFile);
//
//	return S_OK;
//}
//
//bool CObjectIO::Create_CreateMap_ProtoType(HANDLE& hFile, wstring keyname)
//{
//	// #LOADOBJECT ����� ��ü ������Ÿ������ ����.
//
//	CGameManager* GameInstance = GetSingle(CGameManager);
//	CGameObject_Creater* creater =  GameInstance->Get_CreaterManager();
//
//	CGameObject_Base* emptyObject = nullptr;
//
//	E_OBJECT_TYPE	TypeDESC = OBJECT_TYPE_NONE;
//	_ulong			dwByte = 0;
//
//	ReadFile(hFile, &TypeDESC, sizeof(E_OBJECT_TYPE), &dwByte, nullptr);
//
//	if (TypeDESC == OBJECT_TYPE_NONE)
//		return S_FALSE;
//
//	switch (TypeDESC)
//	{
//	case OBJECT_TYPE_2D:
//	{
//		UI_DESC uiDesc;
//		TEXTURE_NAMES_DESC texDesc;
//
//		ReadFile(hFile, &uiDesc, sizeof(UI_DESC), &dwByte, nullptr);
//		ReadFile(hFile, &texDesc, sizeof(TEXTURE_NAMES_DESC), &dwByte, nullptr);
//
//		if (dwByte == 0)
//			return false;
//
//		emptyObject = creater->CreateEmptyObject(GAMEOBJECT_2D);
//		CGameObject_2D* oobj = static_cast<CGameObject_2D*>(emptyObject);
//		oobj->Set_LoadUIDesc(uiDesc);
//		oobj->Set_LoadTexDesc(texDesc);
//	}
//		break;
//	case OBJECT_TYPE_3D_STATIC:
//	{
//		MODEL_STATIC_DESC modelDesc;
//		COLLIDER_DESC colDesc;
//
//		ReadFile(hFile, &modelDesc, sizeof(MODEL_STATIC_DESC), &dwByte, nullptr);
//		ReadFile(hFile, &colDesc, sizeof(COLLIDER_DESC), &dwByte, nullptr);
//
//		if (dwByte == 0)
//			return false;
//
//		emptyObject = creater->CreateEmptyObject(GAMEOBJECT_3D_STATIC);
//		CGameObject_3D_Static* oobj = static_cast<CGameObject_3D_Static*>(emptyObject);
//
//		oobj->Set_LoadModelDESC(modelDesc);
//		oobj->Set_LoadColliderDESC(colDesc);
//	}
//		break;
//	case OBJECT_TYPE_3D_STATIC_PARENT:
//	{
//		while (true)
//		{
//			MODEL_STATIC_DESC modelDesc;
//			COLLIDER_DESC colDesc;
//
//
//			ReadFile(hFile, &modelDesc, sizeof(MODEL_STATIC_DESC), &dwByte, nullptr);
//			ReadFile(hFile, &colDesc, sizeof(COLLIDER_DESC), &dwByte, nullptr);
//			if (dwByte == 0)
//				break;
//			if(emptyObject == nullptr)
//				emptyObject = creater->CreateEmptyObject(GAMEOBJECT_3D_STATIC2);
//
//			CGameObject_3D_Static* newchildObj = static_cast<CGameObject_3D_Static*>(creater->CreateEmptyObject(GAMEOBJECT_3D_STATIC));
//			newchildObj->Set_LoadModelDESC(modelDesc);
//			newchildObj->Set_LoadColliderDESC(colDesc);
//
//			CGameObject_3D_Static2* oobj = static_cast<CGameObject_3D_Static2*>(emptyObject);
//
//			oobj->Add_StaticObejct(newchildObj);
//		}	
//	}
//		break;
//	case OBJECT_TYPE_3D_DYNAMIC:
//	{
//
//	}
//		break;
//	case OBJECT_TYPE_TERRAIN:
//	{
//		
//	}
//
//	case OBJECT_TYPE_END:
//		break;
//	default:
//		break;
//	}
//
//	if (emptyObject != nullptr)
//	{
//		creater->Add_MapObject(keyname, emptyObject);
//		return true;
//	}
//	else
//		return false;
//}
//
//CObjectIO * CObjectIO::Create()
//{
//	CObjectIO*	pInstance = NEW CObjectIO();
//
//	if (FAILED(pInstance->NativeConstruct()))
//	{
//		MSGBOX("Failed to Creating CObjectIO");
//		Safe_Release(pInstance);
//	}
//	return pInstance;
//}
//
//void CObjectIO::Free()
//{
//
//}