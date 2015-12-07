#pragma once
#include <iostream>
#include <sstream>

template <typename T>
class Vector3
{
	friend 	std::ostream& operator<<(std::ostream& os, Vector3<T>& p)
	{
		os <<  p.x << " " <<  p.y << " " <<  p.z;
		return os;
	};

	friend 	std::istream& operator>>(std::istream& in, Vector3<T>& p)
	{
		in >> p.x >> p.y >> p.z;
		return in;
	};

public:

	T x;
	T y;
	T z;
						//nautin t‰stÅE		void setShitBooleanPaskafixJustForJPCozHeLovesThis(T t, T tt, T ttt){ x = t; y = tt; z = ttt;};

	Vector3(){};

	Vector3(T X, T Y, T Z)
	{
		x = X; y = Y; z = Z;
	}

	Vector3<T> operator + (const Vector3<T>& right)
	{
		x = x + right.x;
		y = y + right.y;
		z = z + right.z;

		return *this;
	}
	Vector3<T> operator - (const Vector3<T>& right)
	{
		x = x - right.x;
		y = y - right.y;
		z = z - right.z;

		return *this;
	}
	bool operator == (const Vector3<T>& right)
	{
		return x == right.x && y == right.y && x == right.x && y == right.y;
	}

	Vector3<T> operator *=(Vector3<T>& left)
	{
		x *= left.x;
		y *= left.y;
		z *= left.z;

		return *this;
	}
	Vector3<T> operator /=(Vector3<T>& left)
	{
		x /= left.x;
		y /= left.y;
		z /= left.z;

		return *this;
	}
	Vector3<T> operator +=(Vector3<T>& left)
	{
		x += left.x;
		y += left.y;
		z += left.z;

		return *this;
	}
	Vector3<T> operator -=(Vector3<T>& left)
	{
		x -= left.x;
		y -= left.y;
		z -= left.z;

		return *this;
	}
};