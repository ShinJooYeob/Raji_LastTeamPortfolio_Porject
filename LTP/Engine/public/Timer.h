#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CTimer final : public CBase
{
private:
	explicit CTimer();
	virtual ~CTimer() = default;
public:
	_double Get_DeltaTime(void);


private:

	LARGE_INTEGER		m_CurrentTime;				
	LARGE_INTEGER		m_OldTime;					
	LARGE_INTEGER		m_OriginTime;				
	LARGE_INTEGER		m_CpuTick;					

	_double				m_fDeltaTime;

public:
	static CTimer* Create();
	virtual void Free() override;
};

END
