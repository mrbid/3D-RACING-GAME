#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


namespace utils
{

	//Convert a number to a string
	template<typename T>
	static inline std::string str( const T& n ) {
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	//Square Length of Vector
	template<typename T>
	static inline float SquareLength( const T& vect ) { return ( vect.x * vect.x ) + ( vect.y * vect.y ) + ( vect.z * vect.z ); }

	//Normalise Vector
	template<typename T>
	static inline T Normalise( T& vect )
	{
		float length = SquareLength( vect );
		if( length > 0.f ) // Divide by zero check
		{ 
			float oneOverLength = 1.f / sqrt( length );
			vect.x *= oneOverLength;
			vect.y *= oneOverLength;
			vect.z *= oneOverLength;
		}
		return vect;
	}

	//Dot Product
	template<typename T>
	static inline float dotProduct( const T& lhs, const T& rhs ) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;}

	//Cross Product
	template<typename T>
	static inline T crossProduct( const T& lhs, const T& rhs ) { return T( ( lhs.y * rhs.z ) - ( lhs.z * rhs.y ), ( lhs.z * rhs.x ) - ( lhs.x * rhs.z ), ( lhs.x * rhs.y ) - ( lhs.y * rhs.x ) ); }

	//Length of Vector
	template<typename T>
	static inline float length( const T& vect ) {	return sqrt( ( vect.x * vect.x ) + ( vect.y * vect.y ) + ( vect.z * vect.z ) );	}

	//Square Length of Vector
	template<typename T>
	static inline float squareLength( const T& vect ) {	return ( vect.x * vect.x ) + ( vect.y * vect.y ) + ( vect.z * vect.z );	}

	// Clamp
	template<typename T>
	static inline T clamp( const T val, const T a, const T b )
	{
		if( val < a ) return a;
		if( val > b ) return b;
		return val;
	}

} // end of namespace utils


