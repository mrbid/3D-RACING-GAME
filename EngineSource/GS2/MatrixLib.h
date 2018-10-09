/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include "precom.h"
#include "Vector3.h"

namespace mat4
{
	/*
		******************************************************************************************************************
													MATRIX4 CLASS
		******************************************************************************************************************
	*/

	class MATRIX4
	{
	public:
		
		//Constructors
		MATRIX4()
		{
			_11 = 0.f, _12 = 0.f, _13 = 0.f, _14 = 0.f;
			_21 = 0.f, _22 = 0.f, _23 = 0.f, _24 = 0.f;
			_31 = 0.f, _32 = 0.f, _33 = 0.f, _34 = 0.f;
			_41 = 0.f, _42 = 0.f, _43 = 0.f, _44 = 0.f;
		}

		MATRIX4(float i11, float i12, float i13, float i14,
				float i21, float i22, float i23, float i24,
				float i31, float i32, float i33, float i34,
				float i41, float i42, float i43, float i44)
		{
			_11 = i11, _12 = i12, _13 = i13, _14 = i14;
			_21 = i21, _22 = i22, _23 = i23, _24 = i24;
			_31 = i31, _32 = i32, _33 = i33, _34 = i34;
			_41 = i41, _42 = i42, _43 = i43, _44 = i44;
		}

		MATRIX4(const mat4::MATRIX4& m)
		{
			_11 = m._11, _12 = m._12, _13 = m._13, _14 = m._14;
			_21 = m._21, _22 = m._22, _23 = m._23, _24 = m._24;
			_31 = m._31, _32 = m._32, _33 = m._33, _34 = m._34;
			_41 = m._41, _42 = m._42, _43 = m._43, _44 = m._44;
		}

		MATRIX4(const D3DXMATRIX& m)
		{
			_11 = m._11, _12 = m._12, _13 = m._13, _14 = m._14;
			_21 = m._21, _22 = m._22, _23 = m._23, _24 = m._24;
			_31 = m._31, _32 = m._32, _33 = m._33, _34 = m._34;
			_41 = m._41, _42 = m._42, _43 = m._43, _44 = m._44;
		}

		MATRIX4(const D3DMATRIX& m)
		{
			_11 = m._11, _12 = m._12, _13 = m._13, _14 = m._14;
			_21 = m._21, _22 = m._22, _23 = m._23, _24 = m._24;
			_31 = m._31, _32 = m._32, _33 = m._33, _34 = m._34;
			_41 = m._41, _42 = m._42, _43 = m._43, _44 = m._44;
		}

		MATRIX4(const D3DXMATRIXA16& m)
		{
			_11 = m._11, _12 = m._12, _13 = m._13, _14 = m._14;
			_21 = m._21, _22 = m._22, _23 = m._23, _24 = m._24;
			_31 = m._31, _32 = m._32, _33 = m._33, _34 = m._34;
			_41 = m._41, _42 = m._42, _43 = m._43, _44 = m._44;
		}

		MATRIX4(const float* m)
		{
			_11 = m[0], _12 = m[1], _13 = m[2], _14 = m[3];
			_21 = m[4], _22 = m[5], _23 = m[6], _24 = m[7];
			_31 = m[8], _32 = m[9], _33 = m[10], _34 = m[11];
			_41 = m[12], _42 = m[13], _43 = m[14], _44 = m[15];
		}


		//Operator Overloads
		MATRIX4 operator*(const mat4::MATRIX4& rhs)
		{
			return mat4::MATRIX4(
							(_11 * rhs._11) + (_12 * rhs._21) + (_13 * rhs._31) + (_14 * rhs._41),
							(_11 * rhs._12) + (_12 * rhs._22) + (_13 * rhs._32) + (_14 * rhs._42),
							(_11 * rhs._13) + (_12 * rhs._23) + (_13 * rhs._33) + (_14 * rhs._43),
							(_11 * rhs._14) + (_12 * rhs._24) + (_13 * rhs._34) + (_14 * rhs._44),

							(_21 * rhs._11) + (_22 * rhs._21) + (_23 * rhs._31) + (_24 * rhs._41),
							(_21 * rhs._12) + (_22 * rhs._22) + (_23 * rhs._32) + (_24 * rhs._42),
							(_21 * rhs._13) + (_22 * rhs._23) + (_23 * rhs._33) + (_24 * rhs._43),
							(_21 * rhs._14) + (_22 * rhs._24) + (_23 * rhs._34) + (_24 * rhs._44),

							(_31 * rhs._11) + (_32 * rhs._21) + (_33 * rhs._31) + (_34 * rhs._41),
							(_31 * rhs._12) + (_32 * rhs._22) + (_33 * rhs._32) + (_34 * rhs._42),
							(_31 * rhs._13) + (_32 * rhs._23) + (_33 * rhs._33) + (_34 * rhs._43),
							(_31 * rhs._14) + (_32 * rhs._24) + (_33 * rhs._34) + (_34 * rhs._44),

							(_41 * rhs._11) + (_42 * rhs._21) + (_43 * rhs._31) + (_44 * rhs._41),
							(_41 * rhs._12) + (_42 * rhs._22) + (_43 * rhs._32) + (_44 * rhs._42),
							(_41 * rhs._13) + (_42 * rhs._23) + (_43 * rhs._33) + (_44 * rhs._43),
							(_41 * rhs._14) + (_42 * rhs._24) + (_43 * rhs._34) + (_44 * rhs._44)
						   );
		}

		MATRIX4& operator*=(mat4::MATRIX4& rhs)
		{
			(*this) = (*this) * rhs;
			return *this;
		}

		MP_INLINE bool operator==(const mat4::MATRIX4& rhs)
		{
			if( _11 == rhs._11 && _12 == rhs._12 && _13 == rhs._13 && _14 == rhs._14 &&
				_21 == rhs._21 && _22 == rhs._22 && _23 == rhs._23 && _24 == rhs._24 &&
				_31 == rhs._31 && _32 == rhs._32 && _33 == rhs._33 && _34 == rhs._34 &&
				_41 == rhs._41 && _42 == rhs._42 && _43 == rhs._43 && _44 == rhs._44 )
			{
				return true;
			}

			return false;
		}

		MP_INLINE bool operator!=(const mat4::MATRIX4& rhs)
		{
			if( _11 != rhs._11 && _12 != rhs._12 && _13 != rhs._13 && _14 != rhs._14 &&
				_21 != rhs._21 && _22 != rhs._22 && _23 != rhs._23 && _24 != rhs._24 &&
				_31 != rhs._31 && _32 != rhs._32 && _33 != rhs._33 && _34 != rhs._34 &&
				_41 != rhs._41 && _42 != rhs._42 && _43 != rhs._43 && _44 != rhs._44 )
			{
				return true;
			}

			return false;
		}

		//Casting Overloads
		operator float*() const
		{
			return (float*)&_11;
		}

		//Data Members
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};


	/*
		******************************************************************************************************************
													MATRIX4 FUNCTIONS
		******************************************************************************************************************
	*/
	
	MP_INLINE vec3::Vector3 GetDirection(MATRIX4 m)
	{
		return vec3::Vector3(m._31, m._32, m._33);
	}

	MP_INLINE vec3::Vector3 GetPosition(MATRIX4 m)
	{
		return vec3::Vector3(m._41, m._42, m._43);
	}

	MP_INLINE void SwapROW(MATRIX4* matrixdest, int rowindexdest, const MATRIX4* matrixsrc, int rowindexsrc)
	{
		float r1,r2,r3,r4;

		//Get row
		if(rowindexsrc == 1)
			r1 = matrixsrc->_11, r2 = matrixsrc->_12, r3 = matrixsrc->_13, r4 = matrixsrc->_14;

		if(rowindexsrc == 2)
			r1 = matrixsrc->_21, r2 = matrixsrc->_22, r3 = matrixsrc->_23, r4 = matrixsrc->_24;

		if(rowindexsrc == 1)
			r1 = matrixsrc->_31, r2 = matrixsrc->_32, r3 = matrixsrc->_33, r4 = matrixsrc->_34;

		if(rowindexsrc == 1)
			r1 = matrixsrc->_41, r2 = matrixsrc->_42, r3 = matrixsrc->_43, r4 = matrixsrc->_44;

		//Set row
		if(rowindexdest == 1)
			matrixdest->_11 = r1, matrixdest->_12 = r2, matrixdest->_13 = r1, matrixdest->_14 = r1;

		if(rowindexdest == 2)
			matrixdest->_21 = r1, matrixdest->_22 = r2, matrixdest->_23 = r1, matrixdest->_24 = r1;

		if(rowindexdest == 1)
			matrixdest->_31 = r1, matrixdest->_32 = r2, matrixdest->_33 = r1, matrixdest->_34 = r1;

		if(rowindexdest == 1)
			matrixdest->_41 = r1, matrixdest->_42 = r2, matrixdest->_43 = r1, matrixdest->_44 = r1;
	}

	MP_INLINE void SwapCOLUMN(MATRIX4* matrixdest, int columindexdest, const MATRIX4* matrixsrc, int columindexsrc)
	{
		float r1,r2,r3,r4;

		//Get column
		if(columindexsrc == 1)
			r1 = matrixsrc->_11, r2 = matrixsrc->_21, r3 = matrixsrc->_31, r4 = matrixsrc->_41;

		if(columindexsrc == 2)
			r1 = matrixsrc->_12, r2 = matrixsrc->_22, r3 = matrixsrc->_32, r4 = matrixsrc->_42;

		if(columindexsrc == 1)
			r1 = matrixsrc->_13, r2 = matrixsrc->_23, r3 = matrixsrc->_33, r4 = matrixsrc->_43;

		if(columindexsrc == 1)
			r1 = matrixsrc->_14, r2 = matrixsrc->_24, r3 = matrixsrc->_34, r4 = matrixsrc->_44;
		
		//Set column
		if(columindexdest == 1)
			matrixdest->_11 = r1, matrixdest->_21 = r2, matrixdest->_31 = r1, matrixdest->_41 = r1;

		if(columindexdest == 2)
			matrixdest->_12 = r1, matrixdest->_22 = r2, matrixdest->_32 = r1, matrixdest->_42 = r1;

		if(columindexdest == 1)
			matrixdest->_13 = r1, matrixdest->_23 = r2, matrixdest->_33 = r1, matrixdest->_43 = r1;

		if(columindexdest == 1)
			matrixdest->_14 = r1, matrixdest->_24 = r2, matrixdest->_34 = r1, matrixdest->_44 = r1;
	}

	//Xytor GameDev Modification
	MP_INLINE vec3::Vector3 GetYawPitchRoll(const MATRIX4* mat)
	{
		vec3::Vector3 angles;

		if(mat->_31 != 1 && mat->_31 != -1)
		{
			const float rcos = 1.f / cos(angles.x);
			angles.x = -asin(mat->_31);
			angles.y = atan2(mat->_32 * rcos, mat->_33 * rcos);
			angles.z = atan2(mat->_21 * rcos, mat->_11 * rcos);
		}
		else
		{
			angles.z = 0;
			if(mat->_31 == -1)
			{
				angles.x = M_PI_2;
				angles.y = atan2(mat->_12, mat->_13);
			}
			else
			{
				angles.x = -M_PI_2;
				angles.y = atan2(-mat->_12, mat->_13);
			}
		}
		angles *= M_PI_180;
		return angles;
	}

	MP_INLINE MATRIX4 Translate(float x, float y, float z)
	{
		return MATRIX4( 1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						x, y, z, 1 );
	}

	MP_INLINE MATRIX4 Scale(float x, float y, float z)
	{
		return MATRIX4( x, 0, 0, 0,
						0, y, 0, 0,
						0, 0, z, 0,
						0, 0, 0, 1 );
	}

	MP_INLINE MATRIX4 Scale(float x)
	{
		return MATRIX4( x, 0, 0, 0,
						0, x, 0, 0,
						0, 0, x, 0,
						0, 0, 0, 1 );
	}

	MP_INLINE MATRIX4 RotateX(float angle)
	{
		const float s = sin(angle);
		const float c = cos(angle);
		return MATRIX4( c, 0, s, 0,
						0, 1, 0, 0,
						-s, 0, c, 0,
						0, 0, 0, 1 );
	}

	MP_INLINE MATRIX4 RotateY(float angle)
	{
		const float s = sin(angle);
		const float c = cos(angle);
		return MATRIX4( 1, 0, 0, 0,
						0, c, -s, 0,
						0, s, c, 0,
						0, 0, 0, 1 );
	}

	MP_INLINE MATRIX4 RotateZ(float angle)
	{
		const float s = sin(angle);
		const float c = cos(angle);
		return MATRIX4( c, -s, 0, 0,
						s, c, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 );
	}

	MP_INLINE MATRIX4 Identity()
	{
		return MATRIX4( 1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 );
	}

	inline MATRIX4 Rotate(float h, float p, float r)
	{
		const float cosh = cosf(h), sinh = sinf(h);
		const float cosp = cosf(p), sinp = sinf(p);
		const float cosr = cosf(r), sinr = sinf(r);
		return MATRIX4( cosr * cosh - sinr * sinp * sinh, sinr * cosh + cosr * sinp * sinh, -cosp * sinh, 0.0f,
						-sinr * cosp, cosr * cosp, sinp, 0.0f,
						cosr * sinh + sinr * sinp * cosh, sinr * sinh - cosr * sinp * cosh, cosp * cosh, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );
	}

	inline MATRIX4 LookAt(vec3::Vector3 Eye, vec3::Vector3 At, vec3::Vector3 Up)
	{
		const vec3::Vector3 zaxis = vec3::I_Normalize(At - Eye);
		const vec3::Vector3 xaxis = vec3::I_Normalize(vec3::CrossProduct(Up, zaxis));
		const vec3::Vector3 yaxis = vec3::CrossProduct(zaxis, xaxis);
		return MATRIX4( xaxis.x, yaxis.x, zaxis.x, 0,
						xaxis.y, yaxis.y, zaxis.y, 0,
						xaxis.z, yaxis.z, zaxis.z, 0,
						-vec3::DotProduct(xaxis, Eye), 
						-vec3::DotProduct(yaxis, Eye), 
						-vec3::DotProduct(zaxis, Eye), 1 );
	}

	inline MATRIX4 PerspectiveFOV(float fovy, float aspect, float nearplane, float farplane)
	{
		float yScale = 1.0f / tan(fovy*0.5f);
		float xScale = yScale / aspect;
		float fmn = farplane / (farplane-nearplane);
		return MATRIX4( xScale, 0, 0, 0,
						0, yScale, 0, 0,
						0, 0, fmn, 1,
						0, 0, -nearplane*fmn, 0 );
	}

	//reference: ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf
	void CramerInvert(float *mat, float *dst);
	void PIII_Inverse_4x4(float* src);

	/*MP_INLINE mat4::MATRIX4 Invert(const mat4::MATRIX4& im)
	{
		mat4::MATRIX4 ret;
		CramerInvert((float*)im, (float*)&ret);
		return ret;
	}*/

	MP_INLINE MATRIX4 I_Invert(const mat4::MATRIX4& im)
	{
		float r[]={ im._11, im._12, im._13, im._14,
					im._21, im._22, im._23, im._24,
					im._31, im._32, im._33, im._34,
					im._41, im._42, im._43, im._44 };
		PIII_Inverse_4x4(r);
		return MATRIX4(r);
	}

	MATRIX4 Frenet(vec3::Vector3 pos, vec3::Vector3 dir, vec3::Vector3 up);
	MATRIX4 Frenet_roll(vec3::Vector3 pos, vec3::Vector3 dir, vec3::Vector3 up, float roll);
};

#endif




