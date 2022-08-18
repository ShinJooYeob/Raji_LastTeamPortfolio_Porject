#include "stdafx.h"
#include "..\Public\PhysX\Collider_PhysX_Joint.h"



CCollider_PhysX_Joint::CCollider_PhysX_Joint(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	:CCollider_PhysX_Base(pDevice, pDeviceContext)
{
	mePhysX_ID = E_PHYTYPE_JOINT;

}

CCollider_PhysX_Joint::CCollider_PhysX_Joint(const CCollider_PhysX_Joint & rhs)
	: CCollider_PhysX_Base(rhs)
{

}


HRESULT CCollider_PhysX_Joint::Initialize_Prototype(void * pArg)
{
	if (FAILED(__super::Initialize_Prototype(pArg)))
		return E_FAIL;


	return S_OK;
}

HRESULT CCollider_PhysX_Joint::Initialize_Clone(void * pArg)
{
	if (FAILED(__super::Initialize_Clone(pArg)))
		return E_FAIL;

	if (pArg != nullptr)
		memcpy(&mColDesc, pArg, sizeof(CColider_PX_Desc));

	// Head Offset

	BlenderMat[0] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(-0.024161f, -0.5f , -127.25f);


	BlenderMat[1] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(0, 5.7499f, -133.2f);


	BlenderMat[2] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(0, 10.315f, -133.2f);


	BlenderMat[3] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(0, 14.229f, -133.21f);


	BlenderMat[4] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(0, 23.251f, -133.25f);


	BlenderMat[5] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(0, 35.752f, -133.28f);


	BlenderMat[6] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(0, 52.818f, -133.21f);


	BlenderMat[7] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(0, 64.212f, -133.21f);


	BlenderMat[8] = XMMatrixScaling(1, 1, 1)
		*XMMatrixRotationX(XMConvertToRadians(0))
		*XMMatrixRotationY(XMConvertToRadians(0))
		*XMMatrixRotationZ(XMConvertToRadians(0))
		* XMMatrixTranslation(0, 79.901f, -133.14f);






	return S_OK;
}


HRESULT CCollider_PhysX_Joint::Update_BeforeSimulation()
{
	FAILED_CHECK(__super::Update_BeforeSimulation());

	if (mMainTransform == nullptr)
		return E_FAIL;

	if (mBodyActor)
	{
		PxVec3 bodyoffset = PxVec3(0, 0, 0);
		bodyoffset.y = -0.3f;
		bodyoffset.z = -0;

		PxTransform playerTrans = PxTransform(FLOAT3TOPXVEC3(mMainTransform->Get_MatrixState(CTransform::STATE_POS)));
		playerTrans.p += bodyoffset;
		playerTrans.q = PxQuat(PxPi/2,PxVec3(0,0,1));
		mBodyActor->setGlobalPose(playerTrans);

	}



#pragma region CODE


//	PxVec3 Value1;
//	PxVec3 Value2;

//	memcpy((_float3*)(&Value1), &DEBUGVALUE1, sizeof(_float3));
//	memcpy((_float3*)(&Value2), &DEBUGVALUE2, sizeof(_float3));


	//PxRigidBodyExt::updateMassAndInertia(*(PxRigidBody*)mMain_Actor, Value2.x, &Value1);

//
//	if (mType == 0)
//	{
//
//
//		_Matrix HM = mVecHier[0]->Get_UpdatedMatrix();
//		_Matrix WorldHM = BlenderMat[0].XMatrix() * HM * mAttachModel->Get_DefaiultPivotMat().XMatrix()
//			* mMainTransform->Get_WorldMatrix();
//
//		PxVec3 pxvec = FLOAT3TOPXVEC3(WorldHM.r[3]);
//		mMain_Actor->setGlobalPose(PxTransform(pxvec));
//
//
//
//#pragma region ���� �Ӹ���ġ ���߱�
//
//		// ���� ��ġ�� ������
//		for (_uint i = 1; i < mVecActors.size(); ++i)
//		{
//
//			PxTransform trans = mVecActors[i]->getGlobalPose();
//			PxMat44 px4 = PxMat44(trans);
//			_Matrix mat = (PXMATTOMAT4x4(px4)).XMatrix();
//
//
//			_Matrix HM = mVecHier[i]->Get_UpdatedMatrix();
//			_Matrix WorldHM = BlenderMat[i].XMatrix() * HM * mAttachModel->Get_DefaiultPivotMat().XMatrix() 
//				* mMainTransform->Get_WorldMatrix();
//
//
//			//if (g_pGameInstance->Get_DIKeyState(DIK_Z)&DIS_Down)
//			//{
//			//	_float4 Pos = WorldHM.r[3];
//			//	wstring str = to_wstring(i) + L" -> Hair : " + to_wstring(Pos.x) + L" , " + to_wstring(Pos.y) + L" , " + to_wstring(Pos.z) + L" \n";
//			//	OutputDebugStringW(str.c_str());
//
//			//	Pos = mat.r[3];
//			//	str = to_wstring(i) + L" -> Px : " + to_wstring(Pos.x) + L" , " + to_wstring(Pos.y) + L" , " + to_wstring(Pos.z) + L" \n";
//			//	OutputDebugStringW(str.c_str());
//			//}
//
//			//mat.r[0] = XMVector3Normalize(mat.r[0]) * XMVector3Length(WorldHM.r[0]);
//			//mat.r[1] = XMVector3Normalize(mat.r[1]) * XMVector3Length(WorldHM.r[1]);
//			//mat.r[2] = XMVector3Normalize(mat.r[2]) * XMVector3Length(WorldHM.r[2]);
//
//
//			mat.r[0] =WorldHM.r[0];
//			mat.r[1] =WorldHM.r[1];
//			mat.r[2] =WorldHM.r[2];
//
//			mat = XMMatrixInverse(nullptr, BlenderMat[i].XMatrix()) *
//				(
//				(mat) *
//
//					(mMainTransform->Get_InverseWorldMatrix())
//					) * mAttachModel->Get_DefaiultPivotMat().InverseXMatrix();
//
//			mVecHier[i]->Set_UpdateTransform(mat);
//
//		}


	//	mVecActors[0]->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);

//	mPxMainMatrix4x4 = MAT4X4TOPXMAT(mMainTransform->Get_WorldMatrix());
//	PxTransform trans = PxTransform(mPxMainMatrix4x4);
	//PxTransform tt = mVecActors[0]->getGlobalPose();
//	trans.p += PxVec3(0, 1.5f, 0);
//	mVecActors[0]->setGlobalPose(trans);
			//memcpy((_float3*)(&ffMat.m[1][0]), &DEBUGVALUE2, sizeof(_float3));
	//memcpy((_float3*)(&ffMat.m[2][0]), &DEBUGVALUE3, sizeof(_float3));
	//memcpy((_float3*)(&ffMat.m[3][0]), &DEBUGVALUE4, sizeof(_float3));

	// BoneUpdate
	//PxVec3 APos = mVecActors[1]->getGlobalPose().p;
	//PxVec3 BPos = mVecActors[0]->getGlobalPose().p;
	//PxVec3 DIr = APos - BPos;
	//DIr = DIr.getNormalized();
	//_Sfloat4x4 newmat = mVecHier[1]->Get_UpdatedMatrix();
	//int Debug = 5;

	// Bone Rot
		// _Sfloat4x4 rotmat = _Sfloat4x4();
		// PxRigidDynamic* act = mVecActors[i];
		// _Squternion quternian = _Squternion(act->getGlobalPose().q.x, act->getGlobalPose().q.y, act->getGlobalPose().q.z, act->getGlobalPose().q.w);
		// _float4x4 mat =  _Sfloat4x4::CreateFromQuaternion(quternian);
		// 
		// mVecHier[i]->Set_UpdateTransform(mat.XMatrix());


		//_Sfloat4x4 mat = mVecHier[i]->Get_UpdatedMatrix();
		//PxVec3 APos = mVecActors[i - 1]->getGlobalPose().p;
		//PxVec3 BPos = mVecActors[i]->getGlobalPose().p;
		//PxVec3 DIr = APos - BPos;
		//DIr *= ffMat._11;

		//_Sfloat4x4 DirMat = _Sfloat4x4::CreateTranslation(PXVEC3TOFLOAT3(DIr));
		//mVecHier[i]->Set_UpdateTransform(DirMat* mat);

#pragma endregion 


	return S_OK;
}



HRESULT CCollider_PhysX_Joint::Update_AfterSimulation()
{

	FAILED_CHECK(__super::Update_AfterSimulation());


	if (mType == JOINT_HAIR)
	{
		// ���� ��ġ�� ������ġ�� �ٷ��� ��ġ�� ������ ���ؼ� 
		_Matrix HM = mVecHier[0]->Get_UpdatedMatrix();
		_Matrix WorldHM = BlenderMat[0].XMatrix() * HM * mAttachModel->Get_DefaiultPivotMat().XMatrix()
			* mMainTransform->Get_WorldMatrix();

		// Main�� ��ġ�� �־��ְ� ����
		_Matrix worldmat = mMainTransform->Get_WorldMatrix();
		worldmat.r[3] = WorldHM.r[3];

		// PxVec3 pxvec = FLOAT3TOPXVEC3(worldmat.Translation());
		PxTransform mainPxTrans(MAT4X4TOPXMAT(worldmat));

		mMain_Actor->setGlobalPose(mainPxTrans);


		mNew_WorldPxTransform[8];

		for (_uint i = 0; i < mVecActors.size(); ++i)
		{
			mNew_WorldPxTransform[i] = mVecActors[i]->getGlobalPose();
		}

		//_float3 value1;
		//_float3 value2;
		//memcpy((_float3*)(&value1), &DEBUGVALUE1, sizeof(_float3));
		//memcpy((_float3*)(&value2), &DEBUGVALUE2, sizeof(_float3));

		// �׽�Ʈ�� ���� 1�� 2�� ����
		PxVec3 PreDir;
		//	PreDir = New_WorldPxTransform[2].p - New_WorldPxTransform[1].p;
		//	PreDir = PreDir.getNormalized();
		//	New_WorldPxTransform[2].p = New_WorldPxTransform[1].p + PreDir * value1.x;;

		for (_uint i = 0; i < mVecActors.size(); ++i)
		{
			PreDir = mNew_WorldPxTransform[i + 1].p - mNew_WorldPxTransform[i].p;
			PreDir = PreDir.getNormalized();
			mNew_WorldPxTransform[i + 1].p = mNew_WorldPxTransform[i].p+ PreDir * mOffsetScale[i] * HairLength;
		}


		for (_uint i = 1; i < mVecActors.size(); ++i)
		{
			// ������ ��ġ�� ȸ���� �ȸ��δ�
		//	PreDir = New_WorldPxTransform[i+1].p - New_WorldPxTransform[i].p;
		//	PreDir = PreDir.getNormalized();
			//New_WorldPxTransform[i+1].p = New_WorldPxTransform[i].p + PreDir * myOffsetScale[i]* value1.x;;

			if (i == 7)
			{
				mNew_WorldPxTransform[i] = mNew_WorldPxTransform[i - 1];
			}
			else
			{
				PxMat44 CurrentMat = PxMat44(mNew_WorldPxTransform[i]);
				PxMat44 NextMat = PxMat44(mNew_WorldPxTransform[i + 1]);
				//CurrentMat.column3 = NextMat.column3 = PxVec4(0, 0, 0,1);

				PxVec3 UpDir = (NextMat.column3.getXYZ() - CurrentMat.column3.getXYZ()).getNormalized();
				PxVec3 RightDir = (UpDir == PxVec3(0, 1, 0)) ?
					PxVec3(0.0000001f, 1, 0).getNormalized().cross(UpDir).getNormalized()
					: PxVec3(0, 1, 0).cross(UpDir).getNormalized();
				PxVec3 LookDir = RightDir.cross(UpDir).getNormalized();
				PxVec3 Pos2 = CurrentMat.column3.getXYZ();
				mNew_WorldPxTransform[i] = PxTransform(PxMat44(RightDir, UpDir, LookDir, Pos2));
			}

			//if (i == 1)continue;


			PxTransform trans = mNew_WorldPxTransform[i];
			PxMat44 px4 = PxMat44(trans);

			// ���� ��ġ�� ��ȯ ��ġ�� ���� �������Ѵ�.
			_Matrix mat = (PXMATTOMAT4x4(px4)).XMatrix() ;
			_Vector Pos = mat.r[3];

			_Matrix HM = mVecHier[i]->Get_UpdatedMatrix();
			_Matrix WorldHM = BlenderMat[i].XMatrix() * HM * mAttachModel->Get_DefaiultPivotMat().XMatrix()
				* mMainTransform->Get_WorldMatrix();

		
			mat.r[0] = XMVector3Normalize(mat.r[0]) * XMVector3Length(WorldHM.r[0]);
			mat.r[1] = XMVector3Normalize(mat.r[1]) * XMVector3Length(WorldHM.r[1]);
			mat.r[2] = XMVector3Normalize(mat.r[2]) * XMVector3Length(WorldHM.r[2]);


			//WorldHM =  XMMatrixRotationX(XMConvertToRadians(value2.x)) *
			//	XMMatrixRotationY(XMConvertToRadians(value2.y))*
			//	XMMatrixRotationZ(XMConvertToRadians(value2.z))*
			//	mat ;


			//mat.r[0] = XMMatrixRotationX(XMConvertToRadians(value2.x)).r[0] * WorldHM.r[0];
			//mat.r[1] = XMMatrixRotationY(XMConvertToRadians(value2.y)).r[1] * WorldHM.r[1];
			//mat.r[2] = XMMatrixRotationZ(XMConvertToRadians(value2.z)).r[2] * WorldHM.r[2];

			// mat.r[0] = WorldHM.r[0];
			// mat.r[1] = WorldHM.r[1];
			// mat.r[2] = WorldHM.r[2];
			// 


			mat.r[3] = Pos;
			mat = XMMatrixInverse(nullptr, BlenderMat[i].XMatrix()) *
				(
				(mat) *

					(mMainTransform->Get_InverseWorldMatrix())
					) * mAttachModel->Get_DefaiultPivotMat().InverseXMatrix();

			mVecHier[i]->Set_UpdateTransform(mat);

		}

	}


#pragma region PRE CODE

	// Bone Pos
	//_float NewRatio = 0.5f;

		//for (_uint i = 1; i < mVecActors.size(); ++i)
		//{
		//	PxTransform trans = mVecActors[i]->getGlobalPose();
		//	PxMat44 px4 = PxMat44(trans);

		//	if (i != 1)
		//	{
		//		_Sfloat3 inver = -myOffset[i-1];
		//		PxVec4 NewOffset = PxVec4(FLOAT3TOPXVEC3(inver),0);
		//		px4.column3 += NewOffset;
		//	}
		//

		//	_Matrix mat = (PXMATTOMAT4x4(px4)).XMatrix();


		//	_Matrix HM = mVecHier[i]->Get_UpdatedMatrix();
		//	_Matrix WorldHM = BlenderMat[i].XMatrix() * HM * mAttachModel->Get_DefaiultPivotMat().XMatrix()
		//		* mMainTransform->Get_WorldMatrix();


		//	mat.r[0] = WorldHM.r[0];
		//	mat.r[1] = WorldHM.r[1];
		//	mat.r[2] = WorldHM.r[2];

		//	mat = XMMatrixInverse(nullptr, BlenderMat[i].XMatrix()) *
		//		(
		//		(mat) *

		//			(mMainTransform->Get_InverseWorldMatrix())
		//			) * mAttachModel->Get_DefaiultPivotMat().InverseXMatrix();

		//	mVecHier[i]->Set_UpdateTransform(mat);

		//}

	//	actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);


		//mPxMainMatrix4x4 = MAT4X4TOPXMAT(mMainTransform->Get_WorldMatrix());
		//PxTransform trans = PxTransform(mPxMainMatrix4x4);
		//
		//PxVec3 offset(mPhysXDesc.mSeparation / 2, 0, 0);
		//PxTransform localTm(offset);
		//mVecActors[0]->setGlobalPose(trans);

		//for (_uint i=0; i<mVecActors.size();++i)
		//{
		//	if(i==0)
		//		mVecActors[i]->setGlobalPose(trans);
		//	else
		//		mVecActors[i]->setGlobalPose(trans*localTm);
		//
		//}


	//	mAttachDesc.Set_DefaultBonePivot(_float3 (0), _float3 (90,0,0), _float3 (0.f, 132.0f, -5.80000f ));;
		//mDebugMat = mAttachDesc.Caculate_AttachedBoneMatrix();
	//	mDebugMat = XMMatrixIdentity();
	//	memcpy(&mDebugMat._41, &_float3(mAttachDesc.Get_AttachedBoneWorldPosition()), sizeof(_float3));

		// ���� ������Ʈ
		//_uint size = mVecActors.size();
		//for (int i = 0; i < size; ++i)
		//{
		//	//	mMain_Actor->setGlobalPose(mPxMainTransform);
		//	// PxMat44(PxMat33(t.q), t.p); // ȸ�� �����ϴ� ��

		//	PxMat44 mat = PxMat44(mVecActors[i]->getGlobalPose());
		//	_fMatrix getPos =(PXMATTOMAT4x4(mat)).XMatrix() *  mDebugMat.XMatrix();
		//	mVecHier[i]->Set_UpdateTransform(getPos);
		//}
		//int Debug = 5;


		// 1 ù���� ���� ������Ʈ
	//	CHierarchyNode* hier1  = mVecHier.front();
	//	mMain_Actor->getGlobalPose()

	//	mDebugMat = mMainTransform->Get_WorldMatrix() * mAttachModel->Caculate_AttachedBone(mVecHier.front());
	//	mAttachDesc.Get_AttachedBoneWorldPosition();


		//PxMat44 mat = PxMat44(mVecActors[0]->getGlobalPose());
		//PxMat44 mm = MAT4X4TOPXMAT(mMainTransform->Get_InverseWorldMatrix())*mat;
		//_Sfloat4x4 getPos = PXMATTOMAT4x4(mm);

		//mVecHier[0]->Set_UpdateTransform(getPos);

	

	//CHierarchyNode* hier1 = mVecHier[0];
	//CHierarchyNode* hier2 = mVecHier[1];
	//CHierarchyNode* hier3 = mVecHier[2];
	//_float4x4 ffMat = _Sfloat4x4::Identity;
	//
	//memcpy((_float3*)(&ffMat.m[0][0]), &DEBUGVALUE1, sizeof(_float3));
	//memcpy((_float3*)(&ffMat.m[1][0]), &DEBUGVALUE2, sizeof(_float3));
	//memcpy((_float3*)(&ffMat.m[2][0]), &DEBUGVALUE3, sizeof(_float3));
	//memcpy((_float3*)(&ffMat.m[3][0]), &DEBUGVALUE4, sizeof(_float3));


	//if (bTestflag == 0)
	//{
	////	PxMat44 mat = PxMat44(mMain_Actor->getGlobalPose());
	////	_Sfloat4x4 getPos = PXMATTOMAT4x4(mat);
	////	mMainBone->Set_UpdateTransform(getPos);
	//}
	//else if(bTestflag == 1)
	//{
	//	mPxMainTransform = mMain_Actor->getGlobalPose();
	//	_float3 vec3 = PXVEC3TOFLOAT3(mPxMainTransform.p);
	//	mMainTransform->Set_MatrixState(CTransform::STATE_POS, vec3);
	//
	//}
	//else if (bTestflag == 2)
	//{
	//
	//	if (mbKeyUpdate)
	//	{
	//		mMain_Actor->setGlobalPose(mPxMainTransform);
	//
	//		//mPxMainTransform = PxTransform(FLOAT3TOPXVEC3(mMainTransform->Get_MatrixState_Float3(CTransform::STATE_POS)));
	//		//mMain_Actor->setGlobalPose(mPxMainTransform);
	//		//_float3 vec3 = PXVEC3TOFLOAT3(mPxMainTransform.p);
	//	//	mMainTransform->Set_MatrixState(CTransform::STATE_POS, vec3);
	//	}
	//	else
	//	{
	//	//	mPxMainTransform = mMain_Actor->getGlobalPose();
	//	}
	//
	//	// _float3 vec3 = PXVEC3TOFLOAT3(mPxMainTransform.p);
	//	// mMainTransform->Set_MatrixState(CTransform::STATE_POS, vec3);
	//
	//}
	//int debig = 5;

	//_uint size = mVecActors.size();
	//for (int i =0; i<size;++i)
	//{
	//	PxMat44 mat = PxMat44(mVecActors[i]->getGlobalPose());
	//	_Sfloat4x4 getPos = PXMATTOMAT4x4(mat);
	//	mVecHier[i]->Set_UpdateTransform(getPos);
	//}

	//	_float4x4 DMat1 = _Sfloat4x4::CreateTranslation(DEBUGVALUE1);
//	_float4x4 DMat2 = _Sfloat4x4::CreateTranslation(DEBUGVALUE2);
//	_float4x4 DMat3 = _Sfloat4x4::CreateTranslation(DEBUGVALUE3);


	//	hier2->Set_UpdateTransform(XMLoadFloat4x4(&DMat2));
	//	hier3->Set_UpdateTransform(XMLoadFloat4x4(&DMat3));

	//	mPxMainTransform = mAttachDesc.Get_AttachObjectTransform();

	//mPxMainTransform = mMainTransform;

	//mPxTransform = PxTransform(*(PxVec3*)&Trans->Get_MatrixState_Float3(CTransform::STATE_POS));

	//_float4x4 mat = mAttachDesc.Caculate_AttachedBoneMatrix();
	//mPxTransform = PxTransform(MAT4X4TOPXMAT(mat));

	// Pos
	//PxVec3 pxpos = mMain_Actor->getGlobalPose().p;
	//
	//mPxMainTransform = mMain_Actor->getGlobalPose();
	//_float3 vec3 = *(_float3*)&mPxMainTransform.p;
	//mMainTransform->Set_MatrixState(CTransform::STATE_POS, vec3);

	// �ִϸ��̼��� �����̼� ������ ����
//	_float4x4 DMat = _Sfloat4x4::CreateRotationX(DEBUGVALUE1.x);

	//	_Sfloat4x4 DMat = _Sfloat4x4::CreateTranslation(DEBUGVALUE1);
	//	_Sfloat4x4 DMat = _Sfloat4x4::CreateTranslation(DEBUGVALUE1);
	//

	//	_float3 pos = PXVEC3TOFLOAT3(pxpos);
	//	_Sfloat4x4 matpos = _Sfloat4x4::CreateTranslation(pos);

	//	PxMat44 mat = PxMat44(mMain_Actor->getGlobalPose());
	//	_Sfloat4x4 getPos = PXMATTOMAT4x4(mat);


//	_uint size = mVecActors.size();
//	for (int i =0; i<size;++i)
//	{
//	//	mMain_Actor->setGlobalPose(mPxMainTransform);
//		// PxMat44(PxMat33(t.q), t.p); // ȸ�� �����ϴ� ��
//		/*mVecHier[i]->set*/
//		PxMat44 mat = PxMat44(mVecActors[i]->getGlobalPose());
//		_Sfloat4x4 getPos = PXMATTOMAT4x4(mat);
//		mVecHier[i]->Set_UpdateTransform(getPos);
//	}



//	_float3 vec3 = *(_float3*)&mPxMainTransform.p;
//	mMainTransform->Set_MatrixState(CTransform::STATE_POS, vec3);
#pragma endregion �����ڵ�

	return S_OK;
}


#ifdef _DEBUG

HRESULT CCollider_PhysX_Joint::Render()
{

	// ����� �� �� �׸���

	// ��翡 ���� �����
	m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);
	m_pDeviceContext->IASetInputLayout(m_pInputLayout);
	m_pBasicEffect->SetWorld(XMMatrixIdentity());

	//	m_pBasicEffect->SetWorld(mDebugMat.XMatrix());
	m_pBasicEffect->SetView(GetSingle(CGameInstance)->Get_Transform_Matrix(PLM_VIEW));
	m_pBasicEffect->SetProjection(GetSingle(CGameInstance)->Get_Transform_Matrix(PLM_PROJ));
	m_pBasicEffect->Apply(m_pDeviceContext);


	m_pBatch->Begin();

	//mRenderColor = DirectX::Colors::Blue;
	PxShape* shapes[1];

	//mMain_Actor->getShapes(shapes, 1);
	//const PxShape& shape = *shapes[0];
	//const PxMat44 shpaeWorld(PxShapeExt::getGlobalPose(shape, *mMain_Actor));
	//const PxGeometryHolder h = shape.getGeometry();
	//RenderShape(h, shpaeWorld, mRenderColor); 
	
	mRenderColor = DirectX::Colors::Blue;

	// ���� ��ġ
	for (auto actor : mVecActors)
	{
		actor->getShapes(shapes, 1);
		const PxShape& shape = *shapes[0];
		const PxMat44 shpaeWorld(PxShapeExt::getGlobalPose(shape, *actor));
		const PxGeometryHolder h = shape.getGeometry();
		RenderShape(h, shpaeWorld, mRenderColor);

	}

	mRenderColor = DirectX::Colors::Red;

	// ���� ��ġ
	for (PxTransform newPxTrans : mNew_WorldPxTransform)
	{
		RenderDebugSphere(PXMATTOMAT4x4(PxMat44(newPxTrans)), _float3(0.1f, 0.1f, 0.1f), mRenderColor, PxGeometryType::eBOX);
	}


	m_pBatch->End();

	return S_OK;
}

#endif



HRESULT CCollider_PhysX_Joint::Set_ColiderDesc_Hair(PHYSXDESC_JOINT desc)
{
	// ������ ���� ������ ������ �׽�Ʈ ��
	mType = CCollider_PhysX_Joint::JOINT_HAIR;

	// �浹 �� �ʱ�ȭ
	memcpy(&mPhysXDesc, &desc, sizeof(PHYSXDESC_JOINT));

	if (desc.mAttachModel == nullptr || desc.mLength == 0 || desc.mBoneNames == nullptr || desc.mGameObject == nullptr)
		return E_FAIL;

	// 0 Head ~ Hair_End
	for (int i = 0; i < int(desc.mLength); ++i)
	{
		CHierarchyNode* findBone = desc.mAttachModel->Find_HierarchyNode(desc.mBoneNames[i].c_str());
		NULL_CHECK_BREAK(findBone);
		mVecHier.push_back(findBone);
	}

	mAttachModel = desc.mAttachModel;
	mAttachModel->Update_AnimationClip(g_fDeltaTime, true);
	mMainGameObject = desc.mGameObject;
	mMainTransform = (CTransform*)mMainGameObject->Get_Component(TAG_COM(Com_Transform));

	NULL_CHECK_BREAK(mMainTransform);

	if (mMain_Actor)
		return E_FAIL;

	PxGeometry* mainGemo = nullptr;
	PxGeometry* gemo = nullptr;
	PxGeometry* bofygemo = nullptr;
	mainGemo = gemo = NEW PxBoxGeometry(FLOAT3TOPXVEC3(mPhysXDesc.mMainScale));
	
	//Create_Geometry(E_GEOMAT_TYPE::E_GEOMAT_BOX, mPhysXDesc.mMainScale);
	gemo = Create_Geometry(desc.eShapeType, mPhysXDesc.mActorScale);
	_float bodysize = 0.4f;
	bofygemo = NEW PxCapsuleGeometry(PxReal(bodysize), PxReal(bodysize*1.5f));


	

	NULL_CHECK_BREAK(mainGemo);
	NULL_CHECK_BREAK(gemo);
	NULL_CHECK_BREAK(bofygemo);

	// �⺻ ���͸� �����Ŀ� ���⿡ ������ �޾ƾ��Ѵ�.
	PxTransform dummyTransform = PxTransform(1, 1, 1);
	mMain_Actor = GetSingle(CPhysXMgr)->CreateDynamic_BaseActor(dummyTransform, *mainGemo, 10);
	mBodyActor = GetSingle(CPhysXMgr)->CreateDynamic_BaseActor(dummyTransform, *bofygemo, 100);

	// CreateD6Joint CreateMYJoint
	Create_HairJoint((PxRigidDynamic*)mMain_Actor, PxTransform(0,0,0), desc.mLength-1, *gemo, desc.mSeparation, CreateD6Joint);
	
	((PxRigidDynamic*)mMain_Actor)->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	((PxRigidDynamic*)mBodyActor)->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	((PxRigidDynamic*)mBodyActor)->setRigidBodyFlag(PxRigidBodyFlag::eFORCE_KINE_KINE_NOTIFICATIONS, true);
	
	NULL_CHECK_BREAK(mMain_Actor);
	Safe_Delete(gemo);
	Safe_Delete(mainGemo);
	Safe_Delete(bofygemo);
	return S_OK;
}

HRESULT CCollider_PhysX_Joint::Add_ForceDir(_float3 dir, _float force)
{
	for (int i=2;i< mVecActors.size();++i)
	{
		mVecActors[i]->addForce(PxVec3(dir.x * force, dir.y * force, dir.z * force), PxForceMode::Enum::eFORCE, true);
	}

	return S_OK;
}

PxJoint * CCollider_PhysX_Joint::CreateMYJoint(PxRigidActor * a0, const PxTransform & t0, PxRigidActor * a1, const PxTransform & t1)
{
	// ������ ���� ���� ����

	// PxFixedJoint ���� ���� ���� �� ���Ͱ� �پ��ִ�.
	//PxFixedJoint* j = PxFixedJointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	//j->setProjectionLinearTolerance(0.01f);
	//j->setProjectionAngularTolerance(0.01f);

	//j->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
	//j->setConstraintFlag(PxConstraintFlag::eDRIVE_LIMITS_ARE_FORCES, true);
	//j->setConstraintFlag(PxConstraintFlag::eDISABLE_PREPROCESSING, true);

	// D6
	//	PxD6Joint* j = PxD6JointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	//	j->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLIMITED);
	//	j->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);
	//	j->setMotion(PxD6Axis::eTWIST, PxD6Motion::eLIMITED);
	//	j->setDrive(PxD6Drive::eSLERP, PxD6JointDrive(0, 1000, FLT_MAX, true));
	//	j->setDistanceLimit(
	//		PxJointLinearLimit(CPhysXMgr::gToleranceScale, 100.f, 15.f));

	//j->setConstraintFlag(PxConstraintFlag::ePROJECT_TO_ACTOR0, true);
	//j->setConstraintFlag(PxConstraintFlag::ePROJECT_TO_ACTOR1, false);
	//j->setConstraintFlag(PxConstraintFlag::ePROJECTION, true);		 
	//j->setConstraintFlag(PxConstraintFlag::eDRIVE_LIMITS_ARE_FORCES, true);
																	 
	//	j->setTwistLimit(
	//		PxJointLinearLimit(CPhysXMgr::gToleranceScale, 100.f, 15.f));
	
	//j->setProjectionAngularTolerance()


	//PxD6Joint* j = PxD6JointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	//j->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLOCKED);
	//j->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);
	//j->setMotion(PxD6Axis::eTWIST, PxD6Motion::eLIMITED);
	//j->setDrive(PxD6Drive::eSLERP, PxD6JointDrive(0, 1, 0.01f, true));



	// ȸ�� ����Ʈ �������� ������ x���� �Բ� �����ϰ� �� ���� ���� �߽����� ���� ȸ���� ����մϴ�.
	//PxRevoluteJoint* j = PxRevoluteJointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	//j->setDriveForceLimit(3);
	//j->setDriveVelocity(5);
	//j->setDriveGearRatio(0.5f);

	//j->setInvMassScale0(1000);
	//j->setInvMassScale1(1000);

	//j->setProjectionLinearTolerance(1000);
	//j->setProjectionAngularTolerance(200);

	//j->setConstraintFlag(PxConstraintFlag::Enum::ePROJECTION, true);
	//j->setConstraintFlag(PxConstraintFlag::Enum::eCOLLISION_ENABLED, false);
	//j->setConstraintFlag(PxConstraintFlag::eDRIVE_LIMITS_ARE_FORCES, true);
	//j->setConstraintFlag(PxConstraintFlag::eDISABLE_PREPROCESSING, true);



	// ������ ������ �����ϰ� ���������� �� �������� ������ ���� x���� ���� �����Ӱ� �̲��������� ����մϴ�.
	//PxPrismaticJoint* j = PxPrismaticJointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);

	//j->setInvMassScale0(1.f);
	//j->setInvMassScale1(1.f);

	//j->setInvInertiaScale0(1.f);
	//j->setInvInertiaScale1(1.f);
	//j->setProjectionLinearTolerance(5);



	// �Ÿ� ����
	//PxD6Joint* j = PxD6JointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	//j->setMotion(PxD6Axis::eX, PxD6Motion::eLIMITED);
	//j->setMotion(PxD6Axis::eY, PxD6Motion::eLIMITED);
	//j->setMotion(PxD6Axis::eZ, PxD6Motion::eLIMITED);
	//j->setDistanceLimit(PxJointLinearLimit(1, PxSpring(5000, 5)));


	//PxDistanceJoint* j = PxDistanceJointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	//j->setMaxDistance(100.0f);
	//j->setDistanceJointFlag(PxDistanceJointFlag::eMAX_DISTANCE_ENABLED,true);

	//j->setMotion(PxD6Axis::eX, PxD6Motion::eFREE);
	//j->setMotion(PxD6Axis::eY, PxD6Motion::eFREE);
	//j->setMotion(PxD6Axis::eZ, PxD6Motion::eFREE);
	

	//PxFixedJoint* j = PxFixedJointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);

	//j->setInvMassScale0(1000);
	//j->setInvMassScale1(1000);

	//j->setProjectionLinearTolerance(1000);
	//j->setProjectionAngularTolerance(200);



	PxSphericalJoint* j = PxSphericalJointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	j->setLimitCone(PxJointLimitCone(0.05f, PxPi / 2, PxPi / 2));
	j->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);

	return j;
}

void CCollider_PhysX_Joint::SetBodyCapsuleShape(PxVec3 scale)
{
	if (mBodyActor)
	{
		/*mBodyActor->getShapes();

		mBodyActor->detachShape();
*/
	}
}


PxJoint* CCollider_PhysX_Joint::CreateD6Joint(PxRigidActor* a0, const PxTransform& t0, PxRigidActor* a1, const PxTransform& t1)
{
	//PxD6Joint* j = PxD6JointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	//j->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLOCKED);
	//j->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);
	//j->setMotion(PxD6Axis::eTWIST, PxD6Motion::eLIMITED);
	//j->setDrive(PxD6Drive::eSLERP, PxD6JointDrive(0, 1, 0.01f, true));

	PxD6Joint* j = PxD6JointCreate(*GetSingle(CPhysXMgr)->gPhysics, a0, t0, a1, t1);
	//j->setMotion(PxD6Axis::eX, PxD6Motion::eLOCKED);
	//j->setMotion(PxD6Axis::eY, PxD6Motion::eLOCKED);
	//j->setMotion(PxD6Axis::eZ, PxD6Motion::eLOCKED);

	j->setMotion(PxD6Axis::eSWING1, PxD6Motion::eFREE);
	j->setMotion(PxD6Axis::eSWING2, PxD6Motion::eFREE);
	j->setMotion(PxD6Axis::eTWIST, PxD6Motion::eFREE);
	j->setDrive(PxD6Drive::eSLERP, PxD6JointDrive(100, 1000, 200, true));
	return j;

}

#pragma region CREATEJOINT TEST

//PxRigidDynamic* CCollider_PhysX_Joint::CreateChain(
//	const PxTransform& t, PxU32 length,
//	const PxGeometry& g, PxReal separation, JointCreateFunction createJoint)
//{
//	// ���� ������Ʈ ����
//
//	PxVec3 offset(-separation / 2, 0, 0);
//	PxTransform localTm(offset);
//	PxRigidDynamic* prev = NULL;
//	PxRigidDynamic* first = NULL;
//
//	// N���� ���� ����
//	// ���Ϳ� 
//	for (PxU32 i = 0; i < length; i++)
//	{
//		PxRigidDynamic* current = PxCreateDynamic(*mPhysics, t*localTm, g, *mNormalMaterial, 1.0f);
//		(*createJoint)(prev, prev ? PxTransform(offset) : t, current, PxTransform(-offset));
//		mScene->addActor(*current);
//		if (prev == nullptr)
//			first = current;
//		prev = current;
//		localTm.p.x += separation;
//	}
//	return first;
//}
//
//PxRigidDynamic* CCollider_PhysX_Joint::Create_DemoChain(PxRigidDynamic* actor,const PxTransform& t, PxU32 length, const PxGeometry& g, PxReal separation, JointCreateFunction createJoint)
//{
//	PxVec3 offset(0, 0, separation);
//	PxTransform localTm(offset);
//	PxRigidDynamic* prev = actor;
//
//
//	for (PxU32 i = 0; i < length; i++)
//	{
//		PxRigidDynamic* current = PxCreateDynamic(*mPhysics, t*localTm, g, *mNormalMaterial, 1);
//		current->setMass(0.05f);
//		current->setSleepThreshold(PX_MAX_F32);
//		current->setStabilizationThreshold(PX_MAX_F32);
//		current->setWakeCounter(PX_MAX_F32);
//		current->setLinearDamping(5.f);
//
//
//		(*createJoint)(prev, prev ? PxTransform(offset) : t, current, PxTransform(-offset));
//		GetSingle(CPhysXMgr)->Get_PhysicsScene()->addActor(*current);
//		prev = current;
//		localTm.p.z += separation;
//	}
//	return nullptr;
//}
//
//PxRigidDynamic* CCollider_PhysX_Joint::Create_DemoChain2(PxRigidDynamic* mainactor, const PxTransform& t, PxU32 length, const PxGeometry& g, PxReal separation, JointCreateFunction createJoint)
//{
//	
//	_float3 WorldPos[9];
//	_float3 distarr[8];
//	_float3	fdistarr[8];
//
//	for (_uint i = 0; i < 9; i++)
//	{
//		_Matrix HM = mVecHier[i]->Get_UpdatedMatrix();
//		_Matrix WorldHM = BlenderMat[i].XMatrix() * HM * mAttachModel->Get_DefaiultPivotMat().XMatrix()
//			* mMainTransform->Get_WorldMatrix();
//
//		WorldPos[i] = WorldHM.r[3];
//	}
//
//	for (_uint i = 0; i < 8; i++)
//	{
//		distarr[i] = WorldPos[i + 1 ].XMVector() - WorldPos[i].XMVector();
//		fdistarr[i] = _float3(XMVectorGetX(XMVector3Length(distarr[i].XMVector())), 0, 0);
//	}
//
//
//
//	PxRigidDynamic* prev = mainactor;
//
//	mVecJoints.clear();
//
////	mainactor->setMass(0);
//	for (PxU32 i = 0; i < length; i++)
//	{
//		PxRigidDynamic* current = PxCreateDynamic(*mPhysics, PxTransform(FLOAT3TOPXVEC3(WorldPos[i+1])), g, *mNormalMaterial, 1.0f);
//		mVecActors.push_back(current);
//
//		PxJoint* j = (*createJoint)(prev, prev ? PxTransform(FLOAT3TOPXVEC3(distarr[i])) : t, current, PxTransform(FLOAT3TOPXVEC3(-distarr[i].XMVector())));
//		mVecJoints.push_back(j);
//
//		// ��� ��ȯ ���� ���� ����: 
//		j->setConstraintFlag(PxConstraintFlag::Enum::ePROJECTION, true);
//		j->setConstraintFlag(PxConstraintFlag::Enum::eCOLLISION_ENABLED, false);
//		j->setConstraintFlag(PxConstraintFlag::eDRIVE_LIMITS_ARE_FORCES, true);
//		j->setConstraintFlag(PxConstraintFlag::eDISABLE_PREPROCESSING, true);
//
//
//		GetSingle(CPhysXMgr)->Get_PhysicsScene()->addActor(*current);
//		prev = current;
//	}
//
//	return mainactor;
//}

PxRigidDynamic* CCollider_PhysX_Joint::CreateChain(vector<PxRigidDynamic*>& listPxRig, const PxTransform& t, PxU32 length, const PxGeometry& g, PxReal separation, JointCreateFunction createJoint)
{
	// ���� ������Ʈ ����
	listPxRig.clear();
	PxVec3 offset(separation / 2, 0, 0);
	PxTransform localTm(offset);
	PxRigidDynamic* prev = NULL;

	// N���� ���� ����
	// ���Ϳ� 
	for (PxU32 i = 0; i < length; i++)
	{
		PxRigidDynamic* current = PxCreateDynamic(*GetSingle(CPhysXMgr)->gPhysics, t*localTm, g, *GetSingle(CPhysXMgr)->gMaterial, 1.0f);
		(*createJoint)(prev, prev ? PxTransform(offset) : t, current, PxTransform(-offset));
		GetSingle(CPhysXMgr)->Get_PhysicsScene()->addActor(*current);
		listPxRig.push_back(current);
		prev = current;
		localTm.p.x += separation;
	}

	return prev;
}

PxRigidDynamic * CCollider_PhysX_Joint::CreateChain_BaseActor(PxRigidActor* baseActor, vector<PxRigidDynamic*>& listPxRig, const PxTransform & t, PxU32 length, const PxGeometry & g, PxReal separation, JointCreateFunction createJoint)
{
	// �⺻ ������Ʈ�� ����������Ʈ�� �����ؼ� ����ؾ�
	// ���� ������Ʈ ����
	listPxRig.clear();
	PxVec3 offset(0, 0, separation);
	PxTransform localTm(offset);
	PxRigidActor* prev = baseActor;
	((PxRigidDynamic*)baseActor)->setMass(0);

	// N���� ���� ����
	// ���Ϳ� 
	for (PxU32 i = 0; i < length; i++)
	{
		PxRigidDynamic* current = PxCreateDynamic(*GetSingle(CPhysXMgr)->gPhysics, t*localTm, g, *GetSingle(CPhysXMgr)->gMaterial, 1.f);
		current->setMass(1);
		current->setSleepThreshold(PX_MAX_F32);
		current->setStabilizationThreshold(PX_MAX_F32);
		current->setWakeCounter(PX_MAX_F32);
		current->setLinearDamping(15.f);

		(*createJoint)(prev, prev ? PxTransform(offset) : t, current, PxTransform(-offset));
		GetSingle(CPhysXMgr)->Get_PhysicsScene()->addActor(*current);
		listPxRig.push_back(current);
		prev = current;
		localTm.p.z += separation;
	}
	return (PxRigidDynamic*)baseActor;
}

#pragma endregion CREATEJOINT TEST


PxRigidDynamic* CCollider_PhysX_Joint::Create_HairJoint(PxRigidDynamic* mainactor, const PxTransform& t, PxU32 length, const PxGeometry& g, PxReal separation, JointCreateFunction createJoint)
{
	// �����ڵ�� �׽�Ʈ
	// �Ӹ� 1�� �ڴ´�.

	_float3 WorldPos[9];
	mOffset[8]; // ����
	mOffsetScale[8]; // ���� ũ��
	_float ratio = 2.0f;


	for (_uint i = 0; i < 9; i++)
	{
		// Head~ HairEnd������ world ��ġ
		_Matrix HM = mVecHier[i]->Get_UpdatedMatrix();
		_Matrix WorldHM = BlenderMat[i].XMatrix() * HM * mAttachModel->Get_DefaiultPivotMat().XMatrix()
			* mMainTransform->Get_WorldMatrix();
		WorldPos[i] = WorldHM.r[3];
	}

	// �Ÿ� ���
	for (_uint i = 0; i < 8; i++)
	{
		mOffset[i] = WorldPos[i + 1].XMVector() - WorldPos[i].XMVector();
		mOffsetScale[i] = mOffset[i].Length();
		mOffset[i] *= ratio;
	//	fdistarr[i] = _float3(XMVectorGetX(XMVector3Length(distarr[i].XMVector())), 0, 0);
	}

	// mainActor = Hair1
	PxTransform trans = PxTransform(FLOAT3TOPXVEC3(WorldPos[1]));
	mainactor->setGlobalPose(trans);


	PxRigidDynamic* prev = mainactor;

	mVecJoints.clear();
	mVecActors.push_back(mainactor);

	//	mainactor->setMass(0);
	for (PxU32 i = 1; i < length; i++)
	{
		// �� ���� ���� ����

		PxRigidDynamic* current = PxCreateDynamic(*mPhysics, PxTransform(FLOAT3TOPXVEC3(WorldPos[i + 1])), g, *mNormalMaterial, 1.0f);
	//	current->setMass(1.0f);
		current->setSleepThreshold(PX_MAX_F32);
		current->setStabilizationThreshold(PX_MAX_F32);
		current->setWakeCounter(PX_MAX_F32);
	//	current->setLinearDamping(15.f);

		mVecActors.push_back(current);

		PxTransform newoffset = PxTransform(FLOAT3TOPXVEC3(mOffset[i]));

		PxJoint* j = (*createJoint)(prev, newoffset, current, newoffset.getInverse());
		mVecJoints.push_back(j);
		//j->setInvMassScale0(0.1f);
		//if (i == 0)
		//{
		//	j->setInvMassScale0(1);
		//}

		// ��� ��ȯ ���� ���� ����: 
		j->setConstraintFlag(PxConstraintFlag::Enum::ePROJECTION, true);
		j->setConstraintFlag(PxConstraintFlag::Enum::eCOLLISION_ENABLED, false);
		j->setConstraintFlag(PxConstraintFlag::eDRIVE_LIMITS_ARE_FORCES, true);
		j->setConstraintFlag(PxConstraintFlag::eDISABLE_PREPROCESSING, true);

		GetSingle(CPhysXMgr)->Get_PhysicsScene()->addActor(*current);
		prev = current;
	}

	return mainactor;
}

CCollider_PhysX_Joint * CCollider_PhysX_Joint::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void * pArg)
{

	CCollider_PhysX_Joint* pInstance = NEW CCollider_PhysX_Joint(pDevice, pDeviceContext);

	if (FAILED(pInstance->Initialize_Prototype(pArg)))
	{
		MSGBOX("Failed to Create Transform Prototype");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CCollider_PhysX_Joint::Clone(void * pArg)
{


	CCollider_PhysX_Joint* pInstance = NEW CCollider_PhysX_Joint((*this));

	if (FAILED(pInstance->Initialize_Clone(pArg)))
	{
		MSGBOX("Failed to Create Transform");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCollider_PhysX_Joint::Free()
{

	__super::Free();

#ifdef _DEBUG
	if (m_bIsClone == false)
	{
		Safe_Delete(m_pBasicEffect);
		Safe_Delete(m_pBatch);
	}

	Safe_Release(m_pInputLayout);

#endif // _DEBUG

	if (m_bIsClone)
	{
		auto scene = GetSingle(CPhysXMgr)->Get_PhysicsScene();
		if (scene)
		{
			for (auto& ss : mVecActors)
			{
				PX_RELEASE(ss);
			}
			PX_RELEASE(mBodyActor);
		}
	}

}