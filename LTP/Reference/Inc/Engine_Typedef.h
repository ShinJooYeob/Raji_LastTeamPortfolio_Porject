#pragma once

namespace Engine
{
	typedef unsigned char				_ubyte;
	typedef signed char					_byte;

	typedef unsigned short				_ushort;
	typedef signed short				_short;

	typedef unsigned int				_uint;
	typedef signed int					_int;

	typedef unsigned long				_ulong;
	typedef signed long					_long;

	typedef float						_float;
	typedef double						_double;

	typedef bool						_bool;

	typedef wchar_t						_tchar;



	typedef XMUINT2						_uint2;
	typedef XMUINT3						_uint3;
	typedef XMINT2						_int2;
	typedef XMINT3						_int3;

	typedef struct tagMyFloat4  _float4;
	typedef struct tagMyFloat3  _float3;
	typedef struct tagMyFloat2  _float2;
	typedef struct tagMyFloat4x4  _float4x4;




	typedef struct SimpleMath::Vector2				_Sfloat2;
	typedef struct SimpleMath::Vector3				_Sfloat3;
	typedef struct SimpleMath::Vector4				_Sfloat4;
	typedef struct SimpleMath::Matrix				_Sfloat4x4;
	typedef struct SimpleMath::Quaternion			_Squternion;
	typedef struct SimpleMath::Plane				_Splane;
	typedef struct SimpleMath::Rectangle			_Srectangle;


	typedef XMVECTOR					_Vector;
	typedef FXMVECTOR					_fVector;
	typedef GXMVECTOR					_gVector;

	typedef XMMATRIX					_Matrix;
	typedef FXMMATRIX					_fMatrix;
	typedef CXMMATRIX					_cMatrix;



	struct tagMyFloat4x4 : public XMFLOAT4X4
	{
		tagMyFloat4x4() { };
		tagMyFloat4x4(const XMFLOAT4X4& _Param) : XMFLOAT4X4(_Param) {  };
		tagMyFloat4x4(const FXMMATRIX& _XMatrix)	{ XMStoreFloat4x4(this, _XMatrix);}
		tagMyFloat4x4(
			_float m00, _float m01, _float m02, _float m03,
			_float m10, _float m11, _float m12, _float m13,
			_float m20, _float m21, _float m22, _float m23,
			_float m30, _float m31, _float m32, _float m33)
			:XMFLOAT4X4(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33)	{	};



		XMMATRIX XMatrix() 	{return XMLoadFloat4x4(this); };

		//�����
		XMMATRIX InverseXMatrix()
		{

#ifdef _DEBUG
			XMVECTOR pDeterminate;
			XMMATRIX InversMatrix= XMMatrixInverse(&pDeterminate, this->XMatrix());
			

			if (XMVectorGetX(pDeterminate) != 0)
				return InversMatrix;
			else
			{
				//__debugbreak();
				//MessageBox(0, TEXT("Failed to Make Inverse Matrix"), TEXT("System Message"), MB_OK);
				OutputDebugStringW(L"Failed to Make Inverse Matrix\n");
			}

			return InversMatrix;

#else

			XMMATRIX InversMatrix = XMMatrixInverse(nullptr, this->XMatrix());
			return InversMatrix;
#endif


		}

		//��ġ���
		XMMATRIX TransposeXMatrix() 
		{return XMMatrixTranspose(this->XMatrix());	}



		//(�Ű�����)��ġ ���ͷ� �����ϰ� ���� ��İ� ���Ͽ� ����� ��ȯ
		XMVECTOR Multiply_PosVector(const FXMVECTOR& _param) 
		{	return XMVector3TransformCoord(_param, this->XMatrix());	}

		//(�Ű�����)���� ���ͷ� �����ϰ� ���� ��İ� ���Ͽ� ����� ��ȯ
		XMVECTOR Multiply_DirVector(const FXMVECTOR& _param)
		{ return XMVector3TransformNormal(_param, this->XMatrix());}

		//��ĳ����� �� (�ڱ��ڽ� X �Ű�����)
		XMMATRIX Multiply(const FXMMATRIX& _XMatrix)
		{	return XMMatrixMultiply(this->XMatrix(), _XMatrix);	}



	};
	struct tagMyFloat4 : public XMFLOAT4
	{
		tagMyFloat4() :XMFLOAT4(0, 0, 0, 0) {};
		tagMyFloat4(const XMFLOAT4& _Param) :XMFLOAT4(_Param.x, _Param.y, _Param.z, _Param.w) {	};
		tagMyFloat4(const XMFLOAT3& _Param, _float w) :XMFLOAT4(_Param.x, _Param.y, _Param.z, w) {};
		tagMyFloat4(const XMFLOAT3& _Param) :XMFLOAT4(_Param.x, _Param.y, _Param.z, 0) {};
		tagMyFloat4(const XMFLOAT2& _Param) :XMFLOAT4(_Param.x, _Param.y, 0, 0) {};
		

		explicit tagMyFloat4(const aiQuaternion& _Param) :XMFLOAT4(_Param.x, _Param.y, _Param.z, _Param.w) {};
		explicit tagMyFloat4(const _float& _Param) :XMFLOAT4(_Param, _Param, _Param, _Param) {};
		tagMyFloat4(float _X, float _Y, float _Z, float _W) :XMFLOAT4(_X, _Y, _Z, _W) {	};

		tagMyFloat4(const FXMVECTOR& _Param) { XMStoreFloat4(this, _Param); };


		XMVECTOR XMVector() { return XMLoadFloat4(this); }
		XMVECTOR InverseXMVector() { return (XMLoadFloat4(this) * -1.f); }

		_float Get_Lenth()
		{
			return XMVectorGetX(XMVector4Length(this->XMVector()));
		}

		_float Get_LenthSq()
		{
			return XMVectorGetX(XMVector4LengthSq(this->XMVector()));
		}

		//���� ���� ��ȯ
		XMVECTOR Get_Nomalize()
		{
			return XMVector4Normalize(this->XMVector());
		}



		//(�Ű� ����)���Ϳ� ����(XMVector4Dot) ��Į��(float) ��ȯ
		_float Get_Dot(const XMVECTOR& _Param)
		{
			return XMVectorGetX(XMVector4Dot(this->XMVector(), _Param));
		}

		//�ڱ��ڽ� X �Ű� ���� ������ ����(XMVector3Cross)�� ����(XMVECTOR) ��ȯ XMVector4Cross �ƴ� �򰥸�������
		XMVECTOR Get_Cross(const XMVECTOR& _Param)
		{
			return XMVector3Cross(this->XMVector(), _Param);
		}


		//(�Ű� ����)���Ϳ��� �Ÿ�(XMVector4Length) ��ȯ
		_float Get_Distance(const XMVECTOR& _Param)
		{
			return	XMVectorGetX(XMVector4Length(_Param - this->XMVector()));
		}


		//�ڽ��� (�Ű�����)��İ� ��(XMVectorTransfrom)�Ͽ� ����� ��ȯ
		XMVECTOR Multiply_Matrix(const FXMMATRIX& _XMatrix)
		{
			return XMVector4Transform(this->XMVector(), _XMatrix);
		}


	};
	struct tagMyFloat3 : public XMFLOAT3
	{

		tagMyFloat3() :XMFLOAT3(0, 0, 0) {};
		tagMyFloat3(const XMFLOAT4& _Param) :XMFLOAT3(_Param.x, _Param.y, _Param.z) {};
		tagMyFloat3(const XMFLOAT3& _Param) :XMFLOAT3(_Param.x, _Param.y, _Param.z) {};
		tagMyFloat3(const XMFLOAT2& _Param) :XMFLOAT3(_Param.x, _Param.y, 0) {};


		explicit tagMyFloat3(const aiVector3D& _Param) :XMFLOAT3(_Param.x, _Param.y, _Param.z) {};
		explicit tagMyFloat3(const _float& _Param) :XMFLOAT3(_Param, _Param, _Param) {};
		tagMyFloat3(float _X, float _Y, float _Z) : XMFLOAT3(_X, _Y, _Z) {};

		tagMyFloat3(const FXMVECTOR& _Param) { XMStoreFloat3(this, _Param); };


		_bool operator==(tagMyFloat3& _Param)
		{
			return (x == _Param.x && y == _Param.y && z == _Param.z);
		}

		_bool operator!=(tagMyFloat3& _Param)
		{
			return (x != _Param.x || y != _Param.y || z != _Param.z);
		}


		/*
		//////////////////////������ �����ε�/////////////////

		//_float3 operator-(_float3& _Param)
		//{
		//	return tagMyVector3(x - _Param.x, y - _Param.y, z - _Param.z);
		//}
		//_float3 operator-(D3DXVECTOR3& _Param)
		//{
		//	return _float3(x - _Param.x, y - _Param.y, z - _Param.z);
		//}
		//_float3 operator+(D3DXVECTOR3& _Param)
		//{
		//	return _float3(x + _Param.x, y + _Param.y, z + _Param.z);
		//}

		//_float3& operator=(_float3 _Param)
		//{
		//	x = _Param.x;		y = _Param.y; 		z = _Param.z;
		//	return (*this);
		//}
		//_float3& operator=(D3DXVECTOR3& _Param)
		//{
		//	x = _Param.x;		y = _Param.y; 		z = _Param.z;
		//	return (*this);
		//}


		*/

		//////////////////////������ �Լ� ����/////////////////


		XMVECTOR XMVector() { return XMLoadFloat3(this); }
		XMVECTOR InverseXMVector() { return (XMLoadFloat3(this) * -1.f); }

		_float Get_Lenth()
		{
			return XMVectorGetX(XMVector3Length(this->XMVector()));
		}

		_float Get_LenthSq()
		{
			return XMVectorGetX(XMVector3LengthSq(this->XMVector()));
		}

		//���� ���� ��ȯ
		XMVECTOR Get_Nomalize()
		{
			return XMVector3Normalize(this->XMVector());
		}

		//(�Ű� ����)���Ϳ� ����(XMVector3Dot) ��Į��(float) ��ȯ
		_float Get_Dot(const XMVECTOR& _Param)
		{
			return XMVectorGetX(XMVector3Dot(this->XMVector(), _Param));
		}

		//�ڱ��ڽ� X �Ű� ���� ������ ����(XMVector3Cross)�� ����(XMVECTOR) ��ȯ
		XMVECTOR Get_Cross(const XMVECTOR& _Param)
		{
			return XMVector3Cross(this->XMVector(), _Param);
		}

		XMFLOAT3 Get_Scale(int x)
		{
			XMFLOAT3 returna;
			returna.x = this->x*x;
			returna.y = this->y*x;
			returna.z = this->z*x;

			return returna;
		}

		XMFLOAT3 Get_Scale(float x)
		{
			XMFLOAT3 returna;
			returna.x = this->x*x;
			returna.y = this->y*x;
			returna.z = this->z*x;

			return returna;
		}



		//(�Ű� ����)���Ϳ��� �Ÿ�(XMVector3Length) ��ȯ
		_float Get_Distance(const XMVECTOR& _Param)
		{
			return	XMVectorGetX(XMVector3Length(_Param - this->XMVector()));
		}


		//�ڽ��� ��ġ ���ͷ� �����ϰ� (�Ű�����)��İ� ���Ͽ� ����� ��ȯ
		XMVECTOR Multiply_Matrix_AsPosVector(const FXMMATRIX& _XMatrix)
		{
			return XMVector3TransformCoord(this->XMVector(), _XMatrix);
		}

		//�ڽ��� ���� ���ͷ� �����ϰ� (�Ű�����)��İ� ���Ͽ� ����� ��ȯ
		XMVECTOR Multiply_Matrix_AsDirVector(const FXMMATRIX& _XMatrix)
		{
			return XMVector3TransformNormal(this->XMVector(), _XMatrix);
		}

		static tagMyFloat3 One() { return _float3(1, 1, 1); }
		static tagMyFloat3 Zero() { return _float3(0, 0, 0); }
		static tagMyFloat3 Left() { return _float3(-1, 0, 0); }
		static tagMyFloat3 Right() { return _float3(1, 0, 0); }
		static tagMyFloat3 Up() { return _float3(0, 1, 0); }
		static tagMyFloat3 Down() { return _float3(0, -1, 0); }
		static tagMyFloat3 Front() { return _float3(0, 0, 1); }
		static tagMyFloat3 Back() { return _float3(0, 0, -1); }

	};
	struct tagMyFloat2 : public XMFLOAT2
	{
		tagMyFloat2() :XMFLOAT2(0, 0) { };
		tagMyFloat2(const XMFLOAT4& _Param) :XMFLOAT2(_Param.x, _Param.y) { };
		tagMyFloat2(const XMFLOAT3& _Param) :XMFLOAT2(_Param.x, _Param.y) { };
		tagMyFloat2(const XMFLOAT2& _Param) :XMFLOAT2(_Param.x, _Param.y) { };

		explicit tagMyFloat2(const _float& _Param) :XMFLOAT2(_Param, _Param) { };
		tagMyFloat2(float _X, float _Y) :XMFLOAT2(_X,_Y){};

		tagMyFloat2(const XMVECTOR& _Param) { XMStoreFloat2(this, _Param); };




		XMVECTOR XMVector() { return XMLoadFloat2(this); }
		XMVECTOR InverseXMVector() { return (XMLoadFloat2(this) * -1.f); }

		_float Get_Lenth()
		{
			return XMVectorGetX(XMVector2Length(this->XMVector()));
		}

		_float Get_LenthSq()
		{
			return XMVectorGetX(XMVector2LengthSq(this->XMVector()));
		}

		//���� ���� ��ȯ
		XMVECTOR Get_Nomalize()
		{
			return XMVector2Normalize(this->XMVector());
		}

		//(�Ű� ����)���Ϳ� ����(XMVector2Dot) ��Į��(float) ��ȯ
		_float Get_Dot(const XMVECTOR& _Param)
		{
			return XMVectorGetX(XMVector2Dot(this->XMVector(), _Param));
		}

		//�ڱ��ڽ� X �Ű� ���� ������ ����(XMVector2Cross)�� ����(XMVECTOR) ��ȯ
		XMVECTOR Get_Cross(const XMVECTOR& _Param)
		{
			return XMVector2Cross(this->XMVector(), _Param);
		}


		//(�Ű� ����)���Ϳ��� �Ÿ�(XMVector3Length) ��ȯ
		_float Get_Distance(const XMVECTOR& _Param)
		{
			return	XMVectorGetX(XMVector2Length(_Param - this->XMVector()));
		}
	};

};

