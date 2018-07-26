#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Hitable.hpp"
#include "Material.hpp"

class Sphere : public Hitable
{

public:

	Sphere();
	Sphere( Vector3 center, float radius, Material* material );
	virtual bool hit( const Ray& ray, float min, float max, Hit& hit ) const;

private:

	Vector3 center;
	float radius;
	Material* material;

};

Sphere::Sphere()
{
}

Sphere::Sphere( Vector3 center, float radius, Material* material )
{
	this->center = center;
	this->radius = radius;
	this->material = material;
}

bool Sphere::hit( const Ray& ray, float min, float max, Hit& hit ) const
{
	Vector3 oc = ray.origin() - center;
	float a = ray.direction().dot(ray.direction());
	float b = oc.dot(ray.direction());
	float c = oc.dot(oc) - radius * radius;
	float discriminant = b * b - a * c;
	if( discriminant > 0 )
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if( temp < max && temp > min )
		{
			hit.t = temp;
			hit.point = ray.getPoint(hit.t);
			hit.normal = (hit.point - center) / radius;
			hit.material = material;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;
		if( temp < max && temp > min )
		{
			hit.t = temp;
			hit.point = ray.getPoint(hit.t);
			hit.normal = (hit.point - center) / radius;
			hit.material = material;
			return true;
		}
	}

	return false;
}

#endif /* SPHERE_HPP */