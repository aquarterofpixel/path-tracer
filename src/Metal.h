#ifndef METAL_H
#define METAL_H

#include "Random.h"
#include "Material.h"

class Metal : public Material
{

public:

	Metal( const Vector3& albedo, float fuzziness );

	virtual bool scatter( const Ray& ray, const Hit& hit, Vector3& attenuation, Ray& scattered ) const;

private:

	Vector3 albedo;
	float fuzziness;

};

Metal::Metal( const Vector3& albedo, float fuzziness )
{
	this->albedo = albedo;
	this->fuzziness = (fuzziness < 1) ? fuzziness : 1;
}

bool Metal::scatter( const Ray& ray, const Hit& hit, Vector3& attenuation, Ray& scattered ) const
{
	Random random;
	Vector3 reflected = ray.direction().normalized().reflect(hit.normal);
	scattered = Ray(hit.point, reflected + fuzziness * random.sphere());
	attenuation = albedo;
	return scattered.direction().dot(hit.normal) > 0;
}

#endif /*METAL_H */