// Check Stephan T. Lavavej talk https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful for an in-depth explanation.

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cfloat>
#include <random>

#include "Vector3.hpp"

using namespace std;

class Random
{

public:

	Random();
	Random( int seed );

	float range();
	float range( const float min, const float max );
	Vector3 circle();
	Vector3 sphere();

private:

	int seed;
	random_device rd;
	mt19937 mt;

};

Random::Random()
{
	mt = mt19937(rd());
}

Random::Random( int seed )
{
	this->seed = seed;
	mt = mt19937(seed);
}

float Random::range()
{
	uniform_real_distribution<float> distribution = uniform_real_distribution<float>(0, nextafter(1, FLT_MAX));
	return distribution(mt);
}

float Random::range( const float min, const float max )
{
	uniform_real_distribution<float> distribution = uniform_real_distribution<float>(min, nextafter(max, FLT_MAX));
	return distribution(mt);
}

Vector3 Random::circle()
{
	Vector3 p;
	do
	{
		p = 2.0 * Vector3(range(), range(), 0) - Vector3(1, 1, 0);
	}
	while( p.dot(p) >= 1 );

	return p;
}

Vector3 Random::sphere()
{
	Vector3 p;
	do
	{
		p = 2 * Vector3(range(), range(), range()) - Vector3(1, 1, 1);
	}
	while( p.squaredMagnitude() >= 1 );

	return p;
}

#endif /* RANDOM_HPP */