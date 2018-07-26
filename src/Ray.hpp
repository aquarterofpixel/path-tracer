#ifndef RAY_HPP
#define RAY_HPP

#include "Vector3.hpp"

class Ray
{

public:

	Ray();
	Ray( const Vector3& origin, const Vector3& direction );

	Vector3 origin() const;
	Vector3 direction() const;
	Vector3 getPoint( float distance ) const;

private:

	Vector3 a;
	Vector3 b;

};

Ray::Ray()
{
}

Ray::Ray( const Vector3& origin, const Vector3& direction )
{
	a = origin;
	b = direction;
}

Vector3 Ray::origin() const
{
	return a;
}

Vector3 Ray::direction() const
{
	return b;
}

Vector3 Ray::getPoint( float distance ) const
{
	return a + distance * b;
}

#endif /* RAY_HPP */