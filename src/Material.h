#ifndef MATERIAL_H
#define MATERIAL_H

#include "Random.h"
#include "Ray.h"
#include "Hitable.h"

struct Hit;

class Material
{

public:

	virtual bool scatter( const Ray& ray, const Hit& hit, Vector3& attenuation, Ray& scattered ) const = 0;

};

#endif /* MATERIAL_H */