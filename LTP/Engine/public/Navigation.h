#pragma once

#include "Component.h"
#include "Cell.h"

BEGIN(Engine)

class ENGINE_DLL CNavigation final : public CComponent
{
public:
	typedef struct tagNaviDesc
	{
		_uint	iCurrentIndex;
	}NAVIDESC;

private:
	CNavigation(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CNavigation(const CNavigation& rhs);
	virtual ~CNavigation() = default;

public:
	virtual HRESULT Initialize_Prototype(const _tchar* pNaviDataFilePath);
	virtual HRESULT Initialize_Clone(void* pArg) override;

public:
	CCell::CELL_OPTION	Get_CurCellOption();
	_uint				Get_CurNavCellIndex();
	_Vector				Get_IndexPosition(_uint iIndex);
	void				Set_CurNavCellIndex(_uint iIndex);
public:
	_bool Move_OnNavigation(_fVector vPosition, _Vector vDir, _Vector* vSlidingVec);
	_Vector Get_NaviPosition(_fVector vTargetPos);
	_float	Get_NaviHeight(_fVector vTargetPos);
	HRESULT	FindCellIndex(_Vector Pos);
	


#ifdef _DEBUG
#endif // _DEBUG
public:

	HRESULT Render(class CTransform* pTransform = nullptr);


private:
	vector<class CCell*>			m_Cells;
	typedef vector<class CCell*>	CELLS;

#ifdef _DEBUG
#endif // _DEBUG
private:
	class CVIBuffer_Triangle*		m_pVIBuffer = nullptr;
	class CShader*					m_pShader = nullptr;


private:
	/*네비메시를 사용하는 객체가 존재하고 있는 셀의 인덱스.*/
	NAVIDESC						m_NaviDesc;
	_float4							m_vPreviousPos;

private:
	HRESULT SetUp_Neighbor();

public:
	static CNavigation* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const _tchar* pNaviDataFilePath);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END