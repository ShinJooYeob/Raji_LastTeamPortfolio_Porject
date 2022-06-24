#include "..\public\AnimationClip.h"
#include "ClipBone.h"

CAnimationClip::CAnimationClip()
{
}

HRESULT CAnimationClip::Initialize_AnimationClip(const char * pName, _double Duration, _double UpdatePerSecond)
{

	m_szAnimationClipName = pName;

	m_Duration = Duration;
	m_UpdatePerSecond = UpdatePerSecond;

	return S_OK;
}

HRESULT CAnimationClip::Update_TransformMatrices_byClipBones(_bool* bIsFinished,_double TimeDelta, _double* PlayTimeAcc, 
	const vector<CHierarchyNode*>* pVecHierarchyNodes,  vector<_uint>* pVecCurrentKeyFrameIndex, _bool IsUpdateAll)
{
	/* ���� �� �ִϸ��̼��� ���� ����. */
	(*PlayTimeAcc) += m_UpdatePerSecond * TimeDelta;

	if ((*PlayTimeAcc) >= m_Duration)
	{
		(*PlayTimeAcc) = m_Duration;
		*bIsFinished =  true;
		return S_OK;
	}

	if (IsUpdateAll)
	{

		//�ִϸ��̼� ���������� ���� ũ���� ��� ���
		_Vector			vScale, vRotation, vPosition;

		//��� ������ ���鼭
		for (_uint i = 0; i < m_iNumClipBones; ++i)
		{

			//if (*bIsFinished)
			//	(*pVecCurrentKeyFrameIndex)[i] = 0;


			//�ش� ������ Ű�����ӵ��� �޾ƿ���
			const vector<KEYFRAME*>*	pvecKeyFrames = m_vecClipBones[i]->Get_KeyFrameContainor();

			NULL_CHECK_RETURN(pvecKeyFrames, E_FAIL);

			_uint iNumKeyFrame = _uint(pvecKeyFrames->size());
			_uint iCurrentKeyFrameIndex = (*pVecCurrentKeyFrameIndex)[i];

			/* ���� �ִϸ��̼� ���൵�� ������ Ű�������� �ð��� �Ѿ��. */
			if ((*PlayTimeAcc) >= (*pvecKeyFrames)[iNumKeyFrame - 1]->Time)
			{
				//������ Ű���������� �������ش�.
				vScale = XMLoadFloat3(&(*pvecKeyFrames)[iNumKeyFrame - 1]->vScale);
				vRotation = XMLoadFloat4(&(*pvecKeyFrames)[iNumKeyFrame - 1]->vRotation);
				vPosition = XMLoadFloat3(&(*pvecKeyFrames)[iNumKeyFrame - 1]->vPosition);
			}

			else
			{
				//���� ���൵�� �������� ���� �ʾҴٸ� ���� ���൵ ���ķ� �󸶳� �� ����������� Ȯ���Ͽ� �����ϰ�
				while ((*PlayTimeAcc) >= (*pvecKeyFrames)[iCurrentKeyFrameIndex + 1]->Time)
					(*pVecCurrentKeyFrameIndex)[i] = iCurrentKeyFrameIndex = iCurrentKeyFrameIndex + 1;


				//���� ���� ��Ȳ�� ���� �����Ӱ� ���� ������ ���̿� �󸶳� ����Ǿ��ִ����� �ľ��ϰ�
				_double		Ratio = ((*PlayTimeAcc) - (*pvecKeyFrames)[iCurrentKeyFrameIndex]->Time)
					/ ((*pvecKeyFrames)[iCurrentKeyFrameIndex + 1]->Time - (*pvecKeyFrames)[iCurrentKeyFrameIndex]->Time);


				//�� ũ���̸� �޾ƿͼ� ���������� ���ش�.
				_Vector		vSourScale, vDestScale;
				_Vector		vSourRotation, vDestRotation;
				_Vector		vSourPosition, vDestPosition;


				vSourScale = XMLoadFloat3(&(*pvecKeyFrames)[iCurrentKeyFrameIndex]->vScale);
				vSourRotation = XMLoadFloat4(&(*pvecKeyFrames)[iCurrentKeyFrameIndex]->vRotation);
				vSourPosition = XMLoadFloat3(&(*pvecKeyFrames)[iCurrentKeyFrameIndex]->vPosition);

				vDestScale = XMLoadFloat3(&(*pvecKeyFrames)[iCurrentKeyFrameIndex + 1]->vScale);
				vDestRotation = XMLoadFloat4(&(*pvecKeyFrames)[iCurrentKeyFrameIndex + 1]->vRotation);
				vDestPosition = XMLoadFloat3(&(*pvecKeyFrames)[iCurrentKeyFrameIndex + 1]->vPosition);


				//���� �Ҷ� ������ ���� �����̼��� ���ʹϾ����� �Ϲ����� ���� ������ �ƴ� ���ʹϾ� ������ ������ ������Ѵ�.
				vScale = XMVectorLerp(vSourScale, vDestScale, _float(Ratio));
				vRotation = XMQuaternionSlerp(vSourRotation, vDestRotation, _float(Ratio));
				vPosition = XMVectorLerp(vSourPosition, vDestPosition, _float(Ratio));

			}
			//�������� w���� 1�̿����ϴϱ� ä���ְ�
			vPosition = XMVectorSetW(vPosition, 1.f);

			//������ ���������� �޾ƿԴ�, ��Ű������ ���̿� ������ �ߴ� �����̸� ��������� �̸� ���� ����� �����
			_Matrix		TransformationMatrix = XMMatrixAffineTransformation(vScale, XMVectorSet(0.f, 0.f, 0.f, 1.f), vRotation, vPosition);
			//�� ����� Ŭ�� ���� ��Ī�Ǵ� ���̾Ű ����� Transformation�� �������ش�.
			m_vecClipBones[i]->Set_TransformationMatrix_ToHierarchyNode(TransformationMatrix, pVecHierarchyNodes);

		}

	}
	else
	{		//��� ������ ���鼭
		for (_uint i = 0; i < m_iNumClipBones; ++i)
		{
			//�ش� ������ Ű�����ӵ��� �޾ƿ���
			const vector<KEYFRAME*>*	pvecKeyFrames = m_vecClipBones[i]->Get_KeyFrameContainor();

			NULL_CHECK_RETURN(pvecKeyFrames, E_FAIL);
			_uint iNumKeyFrame = _uint(pvecKeyFrames->size());
			_uint iCurrentKeyFrameIndex = (*pVecCurrentKeyFrameIndex)[i];

			if ((*PlayTimeAcc) < (*pvecKeyFrames)[iNumKeyFrame - 1]->Time)
			{
				//���� ���൵�� �������� ���� �ʾҴٸ� ���� ���൵ ���ķ� �󸶳� �� ����������� Ȯ���Ͽ� �����ϰ�
				while ((*PlayTimeAcc) >= (*pvecKeyFrames)[iCurrentKeyFrameIndex + 1]->Time)
					(*pVecCurrentKeyFrameIndex)[i] = iCurrentKeyFrameIndex = iCurrentKeyFrameIndex + 1;
			}


		}

	}

	return S_OK;
}

HRESULT CAnimationClip::Update_TransformMatrices_byEasing_OldAnim(_uint iNewAnimIndex, CAnimationClip * pOldAnimationClip, _uint iOldAnimIndex, _double OldTimeAcc, _double MixRatio,
	const vector<CHierarchyNode*>* pVecHierarchyNodes, vector<vector<_uint>>* pVecAllAnimKeyFrameIndex)
{

	NULL_CHECK_RETURN(pOldAnimationClip, E_FAIL);

	//�ִϸ��̼� ���������� ���� ũ���� ��� ���
	_Vector			vScale, vRotation, vPosition;

	if (m_iNumClipBones != pOldAnimationClip->Get_NumClipBone())
	{
		__debugbreak();
		return E_FAIL;
	}

	for (_uint i = 0; i < m_iNumClipBones; ++i)
	{
		_float4x4 OldSRT, NewSRT;

		FAILED_CHECK(pOldAnimationClip->Get_SRT_CertainClipNTime(&OldSRT,OldTimeAcc, i, &((*pVecAllAnimKeyFrameIndex)[iOldAnimIndex])));
		FAILED_CHECK(this->Get_SRT_CertainClipNTime(&NewSRT, 0, i, &((*pVecAllAnimKeyFrameIndex)[iNewAnimIndex])));


		_Vector		vSourScale, vDestScale;
		_Vector		vSourRotation, vDestRotation;
		_Vector		vSourPosition, vDestPosition;

		vSourScale = (*(_float3*)OldSRT.m[0]).XMVector();
		vDestScale = (*(_float3*)NewSRT.m[0]).XMVector();

		vSourRotation = (*(_float4*)OldSRT.m[1]).XMVector();
		vDestRotation = (*(_float4*)NewSRT.m[1]).XMVector();

		vSourPosition = (*(_float3*)OldSRT.m[2]).XMVector();
		vDestPosition = (*(_float3*)NewSRT.m[2]).XMVector();

		//���� �Ҷ� ������ ���� �����̼��� ���ʹϾ����� �Ϲ����� ���� ������ �ƴ� ���ʹϾ� ������ ������ ������Ѵ�.
		vScale = XMVectorLerp(vSourScale, vDestScale, _float(MixRatio));
		vRotation = XMQuaternionSlerp(vSourRotation, vDestRotation, _float(MixRatio));
		vPosition = XMVectorLerp(vSourPosition, vDestPosition, _float(MixRatio));


		vPosition = XMVectorSetW(vPosition, 1.f);

		//������ ���������� �޾ƿԴ�, ��Ű������ ���̿� ������ �ߴ� �����̸� ��������� �̸� ���� ����� �����
		_Matrix		TransformationMatrix = XMMatrixAffineTransformation(vScale, XMVectorSet(0.f, 0.f, 0.f, 1.f), vRotation, vPosition);
		//�� ����� Ŭ�� ���� ��Ī�Ǵ� ���̾Ű ����� Transformation�� �������ش�.
		m_vecClipBones[i]->Set_TransformationMatrix_ToHierarchyNode(TransformationMatrix, pVecHierarchyNodes);
	}


	return S_OK;
}

_double CAnimationClip::Get_PlayRate(_double NowAnimPlayAcc)
{
	return NowAnimPlayAcc / m_Duration;
}



HRESULT CAnimationClip::Get_SRT_CertainClipNTime(_float4x4* pOut,_double TimeAcc, _uint iClipBoneIndex, vector<_uint>* pVecKeyFrameIndex)
{


	const vector<KEYFRAME*>* pVecKeyFrame = m_vecClipBones[iClipBoneIndex]->Get_KeyFrameContainor();

	NULL_CHECK_RETURN(pVecKeyFrame, E_FAIL);

	_uint iNumKeyFrame = _uint(pVecKeyFrame->size());
	_uint iCurrentKeyFrameIndex = (*pVecKeyFrameIndex)[iClipBoneIndex];

	_float3			vScale, vPosition;
	_float4			vRotation;

	if ((TimeAcc) >= (*pVecKeyFrame)[iNumKeyFrame - 1]->Time || iCurrentKeyFrameIndex >= iNumKeyFrame - 1)
	{
		//������ Ű���������� �������ش�.
		vScale = XMLoadFloat3(&(*pVecKeyFrame)[iNumKeyFrame - 1]->vScale);
		vRotation = XMLoadFloat4(&(*pVecKeyFrame)[iNumKeyFrame - 1]->vRotation);
		vPosition = XMLoadFloat3(&(*pVecKeyFrame)[iNumKeyFrame - 1]->vPosition);
	}
	else if(TimeAcc == 0)
	{
		//ù��° Ű���������� �������ش�.
		vScale = XMLoadFloat3(&(*pVecKeyFrame)[0]->vScale);
		vRotation = XMLoadFloat4(&(*pVecKeyFrame)[0]->vRotation);
		vPosition = XMLoadFloat3(&(*pVecKeyFrame)[0]->vPosition);
	}
	else
	{

		vScale = XMLoadFloat3(&(*pVecKeyFrame)[iCurrentKeyFrameIndex]->vScale);
		vRotation = XMLoadFloat4(&(*pVecKeyFrame)[iCurrentKeyFrameIndex]->vRotation);
		vPosition = XMLoadFloat3(&(*pVecKeyFrame)[iCurrentKeyFrameIndex]->vPosition);

		/*
		//������ ������ ������ �������� ���ִ°Ŵ� �ʹ� ������ ����� ���� �Ͱ��Ƽ� ���� ���������� ������
		////���� ���� ��Ȳ�� ���� �����Ӱ� ���� ������ ���̿� �󸶳� ����Ǿ��ִ����� �ľ��ϰ�
		//_double		Ratio = ((TimeAcc) - (*pVecKeyFrame)[iCurrentKeyFrameIndex]->Time)
		//	/ ((*pVecKeyFrame)[iCurrentKeyFrameIndex + 1]->Time - (*pVecKeyFrame)[iCurrentKeyFrameIndex]->Time);


		////�� ũ���̸� �޾ƿͼ� ���������� ���ش�.
		//_Vector		vSourScale, vDestScale;
		//_Vector		vSourRotation, vDestRotation;
		//_Vector		vSourPosition, vDestPosition;


		//vSourScale = XMLoadFloat3(&(*pVecKeyFrame)[iCurrentKeyFrameIndex]->vScale);
		//vSourRotation = XMLoadFloat4(&(*pVecKeyFrame)[iCurrentKeyFrameIndex]->vRotation);
		//vSourPosition = XMLoadFloat3(&(*pVecKeyFrame)[iCurrentKeyFrameIndex]->vPosition);

		//vDestScale = XMLoadFloat3(&(*pVecKeyFrame)[iCurrentKeyFrameIndex + 1]->vScale);
		//vDestRotation = XMLoadFloat4(&(*pVecKeyFrame)[iCurrentKeyFrameIndex + 1]->vRotation);
		//vDestPosition = XMLoadFloat3(&(*pVecKeyFrame)[iCurrentKeyFrameIndex + 1]->vPosition);


		////���� �Ҷ� ������ ���� �����̼��� ���ʹϾ����� �Ϲ����� ���� ������ �ƴ� ���ʹϾ� ������ ������ ������Ѵ�.
		//vScale = XMVectorLerp(vSourScale, vDestScale, _float(Ratio));
		//vRotation = XMQuaternionSlerp(vSourRotation, vDestRotation, _float(Ratio));
		//vPosition = XMVectorLerp(vSourPosition, vDestPosition, _float(Ratio));
		*/
	}

	ZeroMemory(pOut, sizeof(_float4x4));

	memcpy(&(pOut->m[0]), &vScale, sizeof(_float3));
	memcpy(&(pOut->m[1]), &vRotation, sizeof(_float4));
	memcpy(&(pOut->m[2]), &vPosition, sizeof(_float3));



	return S_OK;
}



CAnimationClip * CAnimationClip::Create(const char * pAnimationClipName, _double Duration, _double UpdatePerSecond)
{
	CAnimationClip*	pInstance = new CAnimationClip();

	if (FAILED(pInstance->Initialize_AnimationClip(pAnimationClipName, Duration, UpdatePerSecond)))
	{
		MSGBOX("Failed to Created CAnimation");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CAnimationClip::Free()
{

	for (auto& pClipBone : m_vecClipBones)
		Safe_Release(pClipBone);

	m_vecClipBones.clear();
	
}
