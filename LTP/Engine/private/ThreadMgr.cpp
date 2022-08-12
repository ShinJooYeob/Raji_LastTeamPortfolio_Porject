#include "ThreadMgr.h"


IMPLEMENT_SINGLETON(CThreadMgr)


//�پ� �����带 �����Ϸ��� ���� ������
void CALLBACK EraseFinishedThread(void* _Prameter)
{
	THREADARG tThreadArg{};
	memcpy(&tThreadArg, _Prameter, sizeof(THREADARG));
	delete _Prameter;

	vector<HANDLE>*	 vecThread = ((CThreadMgr*)(tThreadArg.pArg))->Get_vecThread();

	BOOL	bResult = false;
	DWORD	dwExitCode = 0;

	while (true)
	{
		//�Ź� ���� �ʿ� �����ϱ� 1�ʿ� �ѹ��� ������... �ٵ� �̰� ���� Ÿ�̹� �� �� ���߸� ���������Ű���
		//�ٵ� �پ� �����带 �����ϴ� �ڵ�� ����� Free �Լ��� �ۿ� ���� ������ �������Ű���
		Sleep(10);
		if ((*tThreadArg.IsClientQuit))
			break;


		//������ ������ �÷��ʹ� ��� ���״ϱ� 1�� �̻��ϋ��� ������
		if (vecThread->size() > 1) 
		{

			//���� ���鼭 ���� �����������Ű��� ex �ٸ������� �߰��ϴٰ� ���� �ʰ��ؼ� �Ѿ�� �� �� ���� ������ ������
			auto iter = vecThread->begin();

			for (; iter != vecThread->end();)
			{
				bResult = false;
				dwExitCode = 0;

				bResult = GetExitCodeThread((*iter), &dwExitCode);
				//�۵� ���̶�� �Ѿ��
				if (dwExitCode == STILL_ACTIVE)
				{
					iter++;
					continue;
				}

				//�۾��� ���� �༮�� ��������

				WaitForSingleObject((*iter), INFINITE);
				CloseHandle((*iter));
				DeleteObject((*iter));

				iter = vecThread->erase(iter);
			}

		}

	}

}

CThreadMgr::CThreadMgr()
	:m_bIsClientQuit(false)
{
	InitializeCriticalSection(&m_CriSec);
	m_vecThread.reserve(10);

	//������ �ʴ� �����带 �����ϴ� �ݷ���
	PlayThread(EraseFinishedThread, this,nullptr);
}


//Client���� Thread�Լ� ���� �� ������ �������� Ŭ�� ���Ḧ �˸��� bool ������ Mutex Pointer�� �ɹ� ������ ���� ��
HRESULT CThreadMgr::PlayThread(void* _ThreadFunc, void* _pArg, void* pDesc)
{
	//�����ͷ� �����Ҳ��� ���ε� �Ἥ ����� �ɵ�
	if (_ThreadFunc == nullptr)
	{
		__debugbreak();
		return E_FAIL;
	}

	THREADARG* pArg = new THREADARG;
	pArg->pArg			= _pArg;
	pArg->CriSec			= &m_CriSec;
	pArg->IsClientQuit	= &m_bIsClientQuit;
	pArg->Desc = pDesc;

	m_vecThread.emplace_back(
		(HANDLE)_beginthreadex(nullptr, 0, _beginthreadex_proc_type(_ThreadFunc), pArg, 0, nullptr)
	);

	return S_OK;

}


void CThreadMgr::Free()
{
	m_bIsClientQuit = true;
	Sleep(500);
	for (auto& Handle : m_vecThread)
	{
		WaitForSingleObject(Handle, INFINITE);
		CloseHandle(Handle);
		DeleteObject(Handle);
	}

	m_vecThread.clear();
	m_vecThread.swap(vector<HANDLE>());

	DeleteCriticalSection(&m_CriSec);

}
