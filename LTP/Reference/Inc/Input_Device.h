#pragma once

#include "Base.h"

BEGIN(Engine)

class CInput_Device final : public CBase
{
	DECLARE_SINGLETON(CInput_Device)

public:
	enum MOUSEMOVESTATE { MMS_X, MMS_Y, MMS_WHEEL, MMS_END };
	enum MOUSEBUTTONSTATE { MBS_LBUTTON, MBS_RBUTTON, MBS_WHEEL, MBS_END };

private:
	CInput_Device();
	virtual ~CInput_Device() = default;

public:
	_byte Get_DIKeyState(_ubyte eKeyID);

	_long Get_DIMouseMoveState(MOUSEMOVESTATE eMouseMoveState) {	return *((_long*)&m_MouseState + eMouseMoveState);  }

	_byte Get_DIMouseButtonState(MOUSEBUTTONSTATE eMouseButtonState);
	

public:
	HRESULT Ready_Input_Device(HINSTANCE hInst, HWND hWnd, _double fDoubleTimeInterver);
	HRESULT SetUp_InputDeviceState(_double fDeltaTime);

private:
	LPDIRECTINPUT8				m_pInput = nullptr;
	LPDIRECTINPUTDEVICE8		m_pKeyboard = nullptr;
	LPDIRECTINPUTDEVICE8		m_pMouse = nullptr;	


	
private:
	_byte					m_byKeyState[256];
	_byte					m_byOldKeyState[256];			//���� �����ӻ��¸� ���� (�ٿ� üũ�� ���� ü���ϱ� ����)
	_double					m_byDoubleKeyState[256];		//���� Ű �Է� �ð� ������ üũ�ϱ� ���� �迭
	_bool					m_bIsKeyPulsDeltaTime[256];		//���� Ű �Է��� ������ �޴� ���� �����ϱ� ���� ����

	DIMOUSESTATE			m_MouseState;
	_byte					m_byOldMouseState[MBS_END];						//���� �����ӻ��¸� ���� (�ٿ� üũ�� ���� ü���ϱ� ����)
	_double					m_byDoubleMouseState[MBS_END];			//���� Ű �Է� �ð� ������ üũ�ϱ� ���� �迭
	_bool					m_bIsMousePulsDeltaTime[MBS_END];		//���� Ű �Է��� ������ �޴� ���� �����ϱ� ���� ����

	_double					m_DoubleInterver;
	_double					m_fDeltaTime;

public:
	virtual void Free() override;
};

END