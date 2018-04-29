#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"

class Material;

struct Hit
{
	float t;
	Vector3 point;
	Vector3 normal;
	Material* material;
};

class Hitable
{

public:

	virtual bool hit( const Ray& ray, float min, float max, Hit& hit ) const = 0;

};

#endif /* HITABLE_H */