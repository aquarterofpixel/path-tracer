#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Random.h"
#include "Material.h"

class Lambertian : public Material
{

public:

	Lambertian( const Vector3& albedo );

	virtual bool scatter( const Ray& ray, const Hit& hit, Vector3& attenuation, Ray& scattered ) const;

private:

	Vector3 albedo;

};

Lambertian::Lambertian( const Vector3& albedo )
{
	this->albedo = albedo;
}

bool Lambertian::scatter( const Ray& ray, const Hit& hit, Vector3& attenuation, Ray& scattered ) const
{
	Random random;
	Vector3 target = hit.point + hit.normal + random.sphere();
	scattered = Ray(hit.point, target - hit.point);
	attenuation = albedo;
	return true;
}

#endif /* LAMBERTIAN_H */