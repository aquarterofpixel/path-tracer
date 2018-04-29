#include <iostream>
#include <fstream>
#include <cfloat>

#include "Math.h"
#include "Random.h"
#include "Vector3.h"
#include "Ray.h"
#include "Camera.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

using namespace std;

Vector3 raycast( const Ray& ray, Hitable* world, int depth )
{
	Hit hit;
	if( world->hit(ray, 0.001, FLT_MAX, hit) )
	{
		Ray scattered;
		Vector3 attenuation;
		if( depth < 50 && hit.material->scatter(ray, hit, attenuation, scattered) )
		{
			return attenuation * raycast(scattered, world, depth + 1);
		}
		else
		{
			return Vector3::zero;
		}
	}
	else
	{
		Vector3 direction = ray.direction().normalized();
		float t = 0.5 * (direction.y() + 1);
		return (1 - t) * Vector3::one + t * Vector3(0.5, 0.7, 1.0);
	}
}

Hitable* randomScene()
{
	Random random;

	int n = 500;
	Hitable** list = new Hitable*[n + 1];
	list[0] = new Sphere(Vector3(0, -1000, 0), 1000, new Lambertian(Vector3(0.5, 0.5, 0.5)));

	int i = 1;
	for( int a = -11; a < 11; a++ )
	{
		for( int b = -11; b < 11; b++ )
		{
			float value = random.range();
			Vector3 center(a + 0.9 * random.range(), 0.2, b + 0.9 * random.range());
			if( (center - Vector3(4, 0.2, 0)).magnitude() > 0.9 )
			{
				if( value < 0.8 )
				{
					// Diffuse.
					list[i++] = new Sphere(center, 0.2, new Lambertian(Vector3(random.range() * random.range(), random.range() * random.range(), random.range() * random.range())));
				}
				else if( value < 0.95 )
				{
					// Metal.
					list[i++] = new Sphere(center, 0.2, new Metal(Vector3(0.5 * (1 + random.range()), 0.5 * (1 + random.range()), 0.5 * (1 + random.range())), 0.5 * random.range()));
				}
				else
				{
					// Glass.
					list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new Sphere(Vector3(0, 1, 0), 1.0, new Dielectric(1.5));
	list[i++] = new Sphere(Vector3(-4, 1, 0), 1.0, new Lambertian(Vector3(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(Vector3(4, 1, 0), 1.0, new Metal(Vector3(0.7, 0.6, 0.5), 0.0));

	return new HitableList(list, i);
}

int main()
{
	ofstream out("output.ppm");
	int nx = 600;
	int ny = 300;
	int ns = 100;

	Hitable* list[5];
	list[0] = new Sphere(Vector3(0, 0, -1), 0.5, new Lambertian(Vector3(0.1, 0.2, 0.5)));
	list[1] = new Sphere(Vector3(0, -100.5, -1), 100, new Lambertian(Vector3(0.8, 0.8, 0.0)));
	list[2] = new Sphere(Vector3(1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.6, 0.2), 0.0));
	list[3] = new Sphere(Vector3(-1, 0, -1), 0.5, new Dielectric(1.5));
	list[4] = new Sphere(Vector3(-1, 0, -1), -0.45, new Dielectric(1.5));
	Hitable *world = new HitableList(list, 5);
	world = randomScene();

	Vector3 lookfrom(13, 2, 3);
	Vector3 lookat(0, 0, 0);
	float focusDistance = 10;
	float aperture = 0.1;
	Camera camera(lookfrom, lookat, Vector3(0, 1, 0), 20, float(nx) / float(ny), aperture, focusDistance);

	/*
	Hitable* spheres[4];
	spheres[0] = new Sphere(Vector3::zero, 0.5, new Lambertian(Vector3(1, 1, 1)));
	spheres[1] = new Sphere(Vector3(1, 0, 0), 0.5, new Lambertian(Vector3(1, 0, 0)));
	spheres[2] = new Sphere(Vector3(0, 1, 0), 0.5, new Lambertian(Vector3(0, 1, 0)));
	spheres[3] = new Sphere(Vector3(0, 0, 1), 0.5, new Lambertian(Vector3(0, 0, 1)));
	Hitable* world = new HitableList(spheres, 4);

	Vector3 lookfrom(10, 4, 5);
	Vector3 lookat(0, 0, 0);
	float focusDistance = 10;
	float aperture = 0.1;
	Camera camera(lookfrom, lookat, Vector3(0, 1, 0), 20, float(nx) / float(ny), aperture, focusDistance);
	*/

	Random random;
	out << "P3\n" << nx << " " << ny << "\n255\n";
	for( int j = ny - 1; j >= 0; j-- )
	{
		for( int i = 0; i < nx; i++ )
		{
			Vector3 color(0, 0, 0);
			for( int s = 0; s < ns; s++ )
			{
				float u = float(i + random.range()) / float(nx);
				float v = float(j + random.range()) / float(ny);
				Ray ray = camera.getRay(u, v);
				color += raycast(ray, world, 0);
			}

			color /= float(ns);
			color = Vector3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
			int r = int(255.99 * color[0]);
			int g = int(255.99 * color[1]);
			int b = int(255.99 * color[2]);
			out << r << " " << g << " " << b << "\n";
		}
	}

	cout << "Press enter to exit..." << endl;
	cin.get();
}