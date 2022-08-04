#pragma once

#include "VIBuffer_Terrain.h"
#include "VIBuffer_EditorTerrain.h"
#include "VIBuffer_Point_Instance.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Cube.h"
#include "VIBuffer_Triangle.h"
#include "VIBuffer_Plat.h"
#include "Model.h"

#include "Transform.h"
#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "Collider.h"
#include "Navigation.h"

#include "HierarchyNode.h"
#include "MotionTrail.h"
#include "SwordTrail.h"
#include "ModelInstance.h"
#include "Dissolve.h"


BEGIN(Engine)
class CComponent;

class CComponentMgr final : public CBase
{
	DECLARE_SINGLETON(CComponentMgr);
private:
	explicit CComponentMgr();

public:
	HRESULT			Reserve_Container(_uint	eMaxSceneNum);
	HRESULT			Add_Component_Prototype(_uint eSceneIdx, const _tchar* tagComPrototype, CComponent* pComponenet);
	CComponent*		Clone_Component(_uint eSceneIdx, const _tchar* tagComPrototype, void* pArg);
	HRESULT			Clear_Scene_Componenets(_uint eSceneIdx);


private:
	map<const _tchar*, CComponent* >*		m_mapComPrototype = nullptr;
	typedef map<const _tchar*, CComponent*>			COMPROTOTYPES;
		
	_uint								m_iMaxScenenNum;

private:
	CComponent* Find_Component(_uint eScenenIdx, const _tchar* tagComPrototype);

public:
	virtual void Free()override;

};

END	