#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

using namespace std;

struct Vector3
{

public:

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 forward;
	static const Vector3 backward;

	Vector3();
	Vector3( float x, float y, float z );
	float x() const;
	float y() const;
	float z() const;

	float operator [] ( int i ) const;
	float& operator [] ( int i );
	const Vector3& operator + () const;
	Vector3 operator - () const;
	Vector3 operator + ( const Vector3& v ) const;
	Vector3 operator - ( const Vector3& v ) const;
	Vector3 operator * ( const Vector3& v ) const;
	Vector3 operator / ( const Vector3& v ) const;
	Vector3& operator += ( const Vector3& v );
	Vector3& operator -= ( const Vector3& v );
	Vector3& operator *= ( const Vector3& v );
	Vector3& operator /= ( const Vector3& v );
	Vector3& operator *= ( const float f );
	Vector3& operator /= ( const float f );
	istream& operator >> ( istream& is );
	ostream& operator << ( ostream& os );

	float magnitude() const;
	float squaredMagnitude() const;
	Vector3 normalized() const;
	void normalize();
	float dot( const Vector3& v ) const;
	Vector3 cross( const Vector3& v ) const;
	Vector3 reflect( const Vector3& normal ) const;

private:

	float e[3];

};

Vector3 operator * ( const float f, const Vector3& v );
Vector3 operator / ( const float f, const Vector3& v );
Vector3 operator * ( const Vector3& v, const float f );
Vector3 operator / ( const Vector3& v, const float f );

const Vector3 Vector3::zero = Vector3(0, 0, 0);
const Vector3 Vector3::one = Vector3(1, 1, 1);
const Vector3 Vector3::right = Vector3(1, 0, 0);
const Vector3 Vector3::left = Vector3(-1, 0, 0);
const Vector3 Vector3::up = Vector3(0, 1, 0);
const Vector3 Vector3::down = Vector3(0, -1, 0);
const Vector3 Vector3::forward = Vector3(0, 0, 1);
const Vector3 Vector3::backward = Vector3(0, 0, -1);

Vector3::Vector3()
{
	e[0] = 0;
	e[1] = 0;
	e[2] = 0;
}

Vector3::Vector3( float x, float y, float z )
{
	e[0] = x;
	e[1] = y;
	e[2] = z;
}

float Vector3::x() const
{
	return e[0];
}

float Vector3::y() const
{
	return e[1];
}

float Vector3::z() const
{
	return e[2];
}

float Vector3::operator [] ( int i ) const
{
	return e[i];
}

float& Vector3::operator [] ( int i )
{
	return e[i];
}

const Vector3& Vector3::operator + () const
{
	return *this;
}

Vector3 Vector3::operator - () const
{
	return Vector3(-e[0], -e[1], -e[2]);
}

Vector3 Vector3::operator + ( const Vector3& v ) const
{
	return Vector3(e[0] + v[0], e[1] + v[1], e[2] + v[2]);
}

Vector3 Vector3::operator - ( const Vector3& v ) const
{
	return Vector3(e[0] - v[0], e[1] - v[1], e[2] - v[2]);
}

Vector3 Vector3::operator * ( const Vector3& v ) const
{
	return Vector3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
}

Vector3 Vector3::operator / ( const Vector3& v ) const
{
	return Vector3(e[0] / v.e[0], e[1] / v.e[1], e[2] / v.e[2]);
}

Vector3& Vector3::operator += ( const Vector3& v )
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

Vector3& Vector3::operator *= ( const Vector3& v )
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

Vector3& Vector3::operator /= ( const Vector3& v )
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

Vector3& Vector3::operator -= ( const Vector3& v )
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

Vector3& Vector3::operator *= ( const float f )
{
	e[0] *= f;
	e[1] *= f;
	e[2] *= f;
	return *this;
}

Vector3& Vector3::operator /= ( const float f )
{
	float k = 1 / f;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

istream& Vector3::operator >> ( istream& is )
{
	is >> e[0] >> e[1] >> e[2];
	return is;
}

ostream& Vector3::operator << ( ostream& os )
{
	os << e[0] << " " << e[1] << " " << e[2];
	return os;
}

float Vector3::magnitude() const
{
	return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

float Vector3::squaredMagnitude() const
{
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

Vector3 Vector3::normalized() const
{
	return *this / magnitude();
}

void Vector3::normalize()
{
	float k = 1 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

float Vector3::dot( const Vector3& v ) const
{
	return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
}

Vector3 Vector3::cross( const Vector3& v ) const
{
	return Vector3((e[1] * v.e[2] - e[2] * v.e[1]), (-(e[0] * v.e[2] - e[2] * v.e[0])), (e[0] * v.e[1] - e[1] * v.e[0]));
}

Vector3 Vector3::reflect( const Vector3& normal ) const
{
	return (*this) - 2 * (*this).dot(normal) * normal;
}

Vector3 operator * ( const float f, const Vector3& v )
{
	return Vector3(f * v[0], f * v[1], f * v[2]);
}

Vector3 operator / ( const float f, const Vector3& v )
{
	return Vector3(f / v[0], f / v[1], f / v[2]);
}

Vector3 operator * ( const Vector3& v, const float f )
{
	return Vector3(f * v[0], f * v[1], f * v[2]);
}

Vector3 operator / ( const Vector3& v, const float f )
{
	return Vector3(v[0] / f, v[1] / f, v[2] / f);
}

#endif /* VECTOR3_H */