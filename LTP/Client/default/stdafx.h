#pragma once


#ifdef _DEBUG
 // #define USE_IMGUI
#endif // _DEBUG

#ifndef USE_IMGUI
#include "GameInstance.h"
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
//#define NEW new


#endif

#endif // _DEBUG

#endif //USE_IMGUI

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>




// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#ifdef USE_IMGUI
#include "GameInstance.h"
#endif //USE_IMGUI


#include "Client_Define.h"