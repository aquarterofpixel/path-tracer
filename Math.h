#ifndef MATH_H
#define MATH_H

class Math
{

public:

	static const float PI;
	static const float DEGREES_TO_RADIANS;
	static const float RADIANS_TO_DEGREES;

private:

	Math();

};

const float Math::PI = 3.14159265358979323846;
const float Math::DEGREES_TO_RADIANS = (Math::PI * 2) / 360;
const float Math::RADIANS_TO_DEGREES = 360 / (Math::PI * 2);

Math::Math()
{
}

#endif /* MATH_H */