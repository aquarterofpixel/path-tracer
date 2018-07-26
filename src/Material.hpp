#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Random.hpp"
#include "Ray.hpp"
#include "Hitable.hpp"

struct Hit;

class Material
{

public:

	virtual bool scatter( const Ray& ray, const Hit& hit, Vector3& attenuation, Ray& scattered ) const = 0;

};

#endif /* MATERIAL_HPP */