#ifndef HITABLE_LIST_HPP
#define HITABLE_LIST_HPP

#include "Hitable.hpp"

class HitableList : public Hitable
{

public:

	HitableList();
	HitableList( Hitable** list, int n );

	virtual bool hit( const Ray& ray, float min, float max, Hit& hit ) const;

private:

	Hitable** list;
	int size;

};

HitableList::HitableList()
{
}

HitableList::HitableList( Hitable** list, int n )
{
	this->list = list;
	size = n;
}

bool HitableList::hit( const Ray& ray, float min, float max, Hit& hit ) const
{
	Hit tmpHit;
	bool isHit = false;
	double closestDistance = max;
	for( int i = 0; i < size; i++ )
	{
		if( list[i]->hit(ray, min, closestDistance, tmpHit) )
		{
			isHit = true;
			closestDistance = tmpHit.t;
			hit = tmpHit;
		}
	}

	return isHit;
}

#endif /* HITABLE_LIST_HPP */