#include "..\public\Shader.h"

CShader::CShader(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	: CComponent(pDevice, pDeviceContext)
{
}

CShader::CShader(const CShader & rhs)
	: CComponent(rhs)
	, m_pEffect(rhs.m_pEffect)
	, m_ShaderDescList(rhs.m_ShaderDescList)
{
	Safe_AddRef(m_pEffect);
}

HRESULT CShader::Initialize_Prototype(const _tchar * pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC * pElements, _uint iNumElements)
{
	FAILED_CHECK(__super::Initialize_Prototype(nullptr));

	_tchar szShaderFullPath[MAX_PATH] = L"../Bin/ShaderFiles/";

	lstrcat(szShaderFullPath, pShaderFilePath);

	_uint		iFlag = 0;

#ifdef _DEBUG
	iFlag = D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG;
#else
	iFlag = D3DCOMPILE_OPTIMIZATION_LEVEL1;
#endif
	ID3DBlob*			pShaderBinaryCodes = nullptr;
	ID3DBlob*			pErrorMessage = nullptr;

	FAILED_CHECK(D3DCompileFromFile(szShaderFullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, nullptr, "fx_5_0", iFlag, 0, &pShaderBinaryCodes, &pErrorMessage));
	//�����Ϸ��� �̿��� hlsl ������ ���̳ʸ� �ڵ�� �о��

	FAILED_CHECK(D3DX11CreateEffectFromMemory(pShaderBinaryCodes->GetBufferPointer(), pShaderBinaryCodes->GetBufferSize(), 0, m_pDevice, &m_pEffect));
	//�о�� ���̳ʸ� ������ cpp���� ����� �� �ִ� Effect��ü�� ġȯ�ص�

	ID3DX11EffectTechnique*			pTechnique = m_pEffect->GetTechniqueByIndex(0);
	NULL_CHECK_RETURN(pTechnique, E_FAIL);
	//ġȯ�� Effect��ü�� ���� ��ũ��Ŀ(pass�� ����)�� ���� ������ �޾ƿ�
	
	D3DX11_TECHNIQUE_DESC		TechniqueDesc;
	ZeroMemory(&TechniqueDesc, sizeof(D3DX11_TECHNIQUE_DESC));

	FAILED_CHECK(pTechnique->GetDesc(&TechniqueDesc));
	//��ũ��Ŀ Desc�� �޾ƿ´�(�ش� ��ũ��Ŀ ���� pass�� �� ������ �˰�;)


	for (_uint i = 0; i < TechniqueDesc.Passes; ++i)
	{
		SHADERDESC*		pShaderDesc = new SHADERDESC;
		ZeroMemory(pShaderDesc, sizeof(SHADERDESC));

		pShaderDesc->pPass = pTechnique->GetPassByIndex(i);
		NULL_CHECK_RETURN(pShaderDesc->pPass, E_FAIL);

		D3DX11_PASS_DESC		PassDesc;
		ZeroMemory(&PassDesc, sizeof(D3DX11_PASS_DESC));
		pShaderDesc->pPass->GetDesc(&PassDesc);

		/*
		D3D11_INPUT_ELEMENT_DESC �� �츮�� ���� ������Ʈ���� ������� ������ ���� �˷��ִ� ����ü�̴�.
		���� �迭�� ������ �ϱ� ������ iNumElements �� ���� ������ ��� ���� ������ ����ϴ��� �˷�����Ѵ�.
		
		�߰������� 9 ���������� VS_IN�� ���� ����� ������ ������ �ٸ����� ���������� �˾Ƽ� �����ְ� �Ǿ��µ�
		11���ʹ� �ٸ��� ������ �ȴ�. 
		�׷��� 1,2 ���ڴ� �츮�� ����ϴ� ������ ���� ����
		2,3 ���ڴ� pass���� VS�� Input���� �޾Ƶ��̴� ���� ������ ���� ������ �Ѱ��ִ� ��

		*/
		FAILED_CHECK(m_pDevice->CreateInputLayout(pElements, iNumElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &(pShaderDesc->pInputLayout)));
		//�̷��� ���̾ƿ�(���̴����� �Ѱ��� ������ �԰ݵ鿡 ���� ����)�� ����


		m_ShaderDescList.push_back(pShaderDesc);
	}

	return S_OK;
}

HRESULT CShader::Initialize_Clone(void * pArg)
{
	FAILED_CHECK(__super::Initialize_Clone(pArg));

	return S_OK;
}

HRESULT CShader::Apply(_uint iPassIndex)
{
	if (iPassIndex >= m_ShaderDescList.size())
		return E_FAIL;

	return m_ShaderDescList[iPassIndex]->pPass->Apply(0, m_pDeviceContext);
}

HRESULT CShader::Set_InputLayout(_uint iPassIndex)
{
	if (iPassIndex >= m_ShaderDescList.size())
		return E_FAIL;

	m_pDeviceContext->IASetInputLayout(m_ShaderDescList[iPassIndex]->pInputLayout);

	return S_OK;
}

HRESULT CShader::Set_RawValue(const char * pValueName, const void * pData, _uint iLength)
{
	ID3DX11EffectVariable*		pValue = m_pEffect->GetVariableByName(pValueName);
	NULL_CHECK_RETURN(pValue, E_FAIL);

	return pValue->SetRawValue(pData, 0, iLength);
}

HRESULT CShader::Set_Texture(const char * pValueName, ID3D11ShaderResourceView * pShaderResourceView)
{
	ID3DX11EffectVariable*		pValue = m_pEffect->GetVariableByName(pValueName);
	NULL_CHECK_RETURN(pValue, E_FAIL);

	ID3DX11EffectShaderResourceVariable*	pShaderResourceVariable = pValue->AsShaderResource();
	NULL_CHECK_RETURN(pShaderResourceVariable, E_FAIL);

	return pShaderResourceVariable->SetResource(pShaderResourceView);
}

CShader * CShader::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const _tchar * pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC * pElements, _uint iNumElements)
{
	CShader*	pInstance = new CShader(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pShaderFilePath, pElements, iNumElements)))
	{
		MSGBOX("Failed to Creating CShader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CShader::Clone(void * pArg)
{
	CShader*	pInstance = new CShader(*this);

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Creating CShader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CShader::Free()
{
	__super::Free();

	if (false == m_bIsClone)
	{
		for (auto& pPassDesc : m_ShaderDescList)
		{
			Safe_Release(pPassDesc->pPass);
			Safe_Release(pPassDesc->pInputLayout);

			Safe_Delete(pPassDesc);
		}

		m_ShaderDescList.clear();
	}


	Safe_Release(m_pEffect);
}
