#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Random.h"
#include "Material.h"

class Dielectric : public Material
{

public:

	Dielectric( float refractionIndex );

	virtual bool scatter( const Ray& ray, const Hit& hit, Vector3& attenuation, Ray& scattered ) const;
	bool refract( const Vector3& v, const Vector3& normal, float refractionRatio, Vector3& refracted ) const;
	float schlick( float cosine, float refractionIndex ) const;

private:

	float refractionIndex;

};

Dielectric::Dielectric( float refractionIndex )
{
	this->refractionIndex = refractionIndex;
}

// Check Snell's law (https://en.wikipedia.org/wiki/Snell%27s_law) for an in-depth explanation.
bool Dielectric::scatter( const Ray& ray, const Hit& hit, Vector3& attenuation, Ray& scattered ) const
{
	Vector3 normal;
	float refractionRatio;
	float cosine;
	if( ray.direction().dot(hit.normal) > 0 )
	{
		normal = -hit.normal;
		refractionRatio = refractionIndex;
		cosine = ray.direction().dot(hit.normal) / ray.direction().magnitude();
		cosine = sqrt(1 - refractionIndex * refractionIndex * (1 - cosine * cosine));
	}
	else
	{
		normal = hit.normal;
		refractionRatio = 1 / refractionIndex;
		cosine = -ray.direction().dot(hit.normal) / ray.direction().magnitude();
	}

	Vector3 refracted;
	float reflectedProbability;
	if( refract(ray.direction(), normal, refractionRatio, refracted) )
	{
		reflectedProbability = schlick(cosine, refractionIndex);
	}
	else
	{
		reflectedProbability = 1;
	}

	Random random;
	Vector3 reflected = ray.direction().reflect(hit.normal);
	if( random.range() < reflectedProbability )
	{
		scattered = Ray(hit.point, reflected);
	}
	else
	{
		scattered = Ray(hit.point, refracted);
	}

	attenuation = Vector3::one;
	return true;
}

bool Dielectric::refract( const Vector3& v, const Vector3& normal, float refractionRatio, Vector3& refracted ) const
{
	Vector3 uv = v.normalized();
	float dt = uv.dot(normal);
	float discriminant = 1 - refractionRatio * refractionRatio * (1 - dt * dt);
	if( discriminant > 0 )
	{
		refracted = refractionRatio * (uv - normal * dt) - normal * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

// Polynomial approximation of the contribution of the fresnel factor in the specular reflection of light from a non-conducting interface (surface) between two media.
// Christophe Schlick (https://en.wikipedia.org/wiki/Schlick%27s_approximation).
float Dielectric::schlick( float cosine, float refractionIndex ) const
{
	float r0 = (1 - refractionIndex) / (1 + refractionIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

#endif /* DIELECTRIC_H */
