#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Math.hpp"
#include "Random.hpp"
#include "Ray.hpp"

class Camera
{

public:

	Camera( Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect, float aperture, float focusDistance )
	{
		// Field of view is vertical (top to bottom) in degrees.

		float theta = vfov * Math::DEGREES_TO_RADIANS;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect * halfHeight;
		origin = lookfrom;

		//w = (lookfrom - lookat).normalized();
		w = (lookat - lookfrom).normalized();
		u = vup.cross(w).normalized();
		v = w.cross(u);

		//bottomLeft = origin - half_width * focusDistance * u - half_height * focusDistance * v - focusDistance * w;
		bottomLeft = origin - halfWidth * focusDistance * u - halfHeight * focusDistance * v + focusDistance * w;
		horizontal = 2 * halfWidth * focusDistance * u;
		vertical = 2 * halfHeight * focusDistance * v;

		lensRadius = aperture / 2;
	}

	Ray getRay( float s, float t )
	{
		Random random;
		Vector3 randomPoint = lensRadius * random.circle();
		Vector3 offset = u * randomPoint.x() + v * randomPoint.y();
		return Ray(origin + offset, bottomLeft + s * horizontal + t * vertical - origin - offset);
	}

private:

	Vector3 origin;
	Vector3 bottomLeft;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 u, v, w;
	float lensRadius;

};

#endif /* CAMERA_HPP */