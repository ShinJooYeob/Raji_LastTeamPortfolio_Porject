#pragma once
#include "Base.h"


// �н� ���δ�
BEGIN(Engine)

class CFileInfoMgr
	:public CBase
{
	DECLARE_SINGLETON(CFileInfoMgr);

private:
	CFileInfoMgr() = default;
	~CFileInfoMgr() = default;

public:
	// ������ Ž���ϸ鼭 ��� ���� ����Ʈ ����
	HRESULT			FolderFinder(const wstring& FileFolder);

	// TXT ���Ϸ� MYFILEPATH ���� ���� // ��� �����̸� Ȯ����
	void SaveVectorToDat(wstring savetxtName, wstring ExtensionName = L"");
	void SaveVectorToDat_Particle(wstring savetxtName, wstring ExtensionName = L"");
	
	// �ش� Txt������ �о Path ����Ʈ ����
	list<MYFILEPATH*> Load_ExtensionList(wstring txtfilepath, string exe, bool bFlag =true);

	// Full �н��� ��θ� ����
	wstring Get_PathData(wstring Fullpath);

private:
	void SaveFilePathByVector(MYFILEPATH * path, wstring filepath, wstring filename);

private:
	list<MYFILEPATH*>		mListFilePathData;

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
END


